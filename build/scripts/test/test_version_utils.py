"""
Unit tests for build environment version matching.

Tests version parsing and comparison logic without filesystem operations.
All test data is embedded in the test file itself.
"""

import unittest
import sys
from pathlib import Path

# Add parent directory (build/scripts/) to path to import version_utils
sys.path.insert(0, str(Path(__file__).parent.parent))

from version_utils import YmlVersionParser, VersionMatcher, parse_yml_dependencies, check_versions


class TestYmlVersionParser(unittest.TestCase):
    """Test parsing of yml content."""
    
    def test_parse_simple_versions(self):
        """Test parsing simple version specifications."""
        yml = """name: test_env
dependencies:
  - python=3.12
  - cmake>=4.2
  - ninja>=1.13"""
        
        versions = YmlVersionParser.parse_yml_content(yml)
        
        self.assertEqual(versions["python"], "3.12")
        self.assertEqual(versions["cmake"], "4.2")
        self.assertEqual(versions["ninja"], "1.13")
    
    def test_parse_with_whitespace(self):
        """Test parsing handles extra whitespace."""
        yml = """  - python  =  3.12
  - cmake   >=   4.2"""
        
        versions = YmlVersionParser.parse_yml_content(yml)
        
        self.assertEqual(versions["python"], "3.12")
        self.assertEqual(versions["cmake"], "4.2")
    
    def test_parse_hyphenated_tool_names(self):
        """Test parsing tool names with hyphens."""
        yml = """- llvm-tools>=21
- clang-tools>=21
- gcc>=13"""
        
        versions = YmlVersionParser.parse_yml_content(yml)
        
        self.assertEqual(versions["llvm-tools"], "21")
        self.assertEqual(versions["clang-tools"], "21")
        self.assertEqual(versions["gcc"], "13")
    
    def test_parse_ignores_non_version_lines(self):
        """Test that non-version lines are ignored."""
        yml = """name: build_env
channels:
  - conda-forge
dependencies:
  - python=3.12
  - cmake>=4.2"""
        
        versions = YmlVersionParser.parse_yml_content(yml)
        
        # Should only parse the actual version lines
        self.assertEqual(len(versions), 2)
        self.assertIn("python", versions)
        self.assertIn("cmake", versions)
        self.assertNotIn("conda-forge", versions)
    
    def test_parse_conan_version(self):
        """Test parsing conan (package name) from yml."""
        yml = "- conan>=2.24"
        
        versions = YmlVersionParser.parse_yml_content(yml)
        
        self.assertEqual(versions["conan"], "2.24")
    
    def test_parse_empty_content(self):
        """Test parsing empty content."""
        versions = YmlVersionParser.parse_yml_content("")
        
        self.assertEqual(len(versions), 0)
    
    def test_parse_full_yml(self):
        """Test parsing a full yml file."""
        yml = """# SI Units Build Environment
name: build_si_units_1.0
channels:
  - conda-forge
dependencies:
  # Core tools
  - python=3.12
  - cmake>=4.2
  - conan>=2.24
  
  # LLVM/Clang toolchain
  - llvm-tools>=21
  - clang>=21
  - clang-tools>=21
  - lld>=21
  
  # GCC toolchain
  - gcc>=13
  - gxx>=13
  
  # Build utilities
  - ninja>=1.13"""
        
        versions = YmlVersionParser.parse_yml_content(yml)
        
        # Verify all expected tools are parsed
        expected_tools = [
            "python", "cmake", "conan",
            "llvm-tools", "clang", "clang-tools", "lld",
            "gcc", "gxx", "ninja"
        ]
        
        for tool in expected_tools:
            self.assertIn(tool, versions)
        
        # Verify specific versions
        self.assertEqual(versions["python"], "3.12")
        self.assertEqual(versions["cmake"], "4.2")
        self.assertEqual(versions["conan"], "2.24")
        self.assertEqual(versions["clang"], "21")
        self.assertEqual(versions["gcc"], "13")


class TestVersionMatcher(unittest.TestCase):
    """Test version matching logic."""
    
    def setUp(self):
        """Set up test fixtures."""
        self.current_versions = {
            "python": "3.12",
            "cmake": "4.2",
            "conan2": "2.24",
            "llvm": "21",
            "clang": "21",
            "gcc": "13",
            "gxx": "13",
            "ninja": "1.13",
        }
    
    def test_matching_versions(self):
        """Test that matching versions return True."""
        file_versions = {
            "python": "3.12",
            "cmake": "4.2",
            "conan": "2.24",  # Note: conan (not conan2)
            "llvm-tools": "21",
            "clang": "21",
            "gcc": "13",
            "gxx": "13",
            "ninja": "1.13",
        }
        
        match, mismatches = VersionMatcher.versions_match(
            self.current_versions, file_versions
        )
        
        self.assertTrue(match)
        self.assertEqual(len(mismatches), 0)
    
    def test_mismatched_python_version(self):
        """Test detection of mismatched python version."""
        file_versions = {
            "python": "3.11",  # Wrong version
            "cmake": "4.2",
            "conan": "2.24",
            "llvm-tools": "21",
            "clang": "21",
            "gcc": "13",
            "gxx": "13",
            "ninja": "1.13",
        }
        
        match, mismatches = VersionMatcher.versions_match(
            self.current_versions, file_versions
        )
        
        self.assertFalse(match)
        self.assertTrue(any("python" in m for m in mismatches))
    
    def test_missing_tool_in_yml(self):
        """Test detection of missing tool in yml."""
        file_versions = {
            "python": "3.12",
            "cmake": "4.2",
            # Missing conan
            "llvm-tools": "21",
            "clang": "21",
            "gcc": "13",
            "gxx": "13",
            "ninja": "1.13",
        }
        
        match, mismatches = VersionMatcher.versions_match(
            self.current_versions, file_versions
        )
        
        self.assertFalse(match)
        self.assertTrue(any("conan" in m for m in mismatches))
    
    def test_conan2_to_conan_mapping(self):
        """Test that conan2 in config maps to conan in yml."""
        # Current config has conan2, yml has conan
        file_versions = {
            "python": "3.12",
            "cmake": "4.2",
            "conan": "2.24",  # Package name
            "llvm-tools": "21",
            "clang": "21",
            "gcc": "13",
            "gxx": "13",
            "ninja": "1.13",
        }
        
        match, mismatches = VersionMatcher.versions_match(
            self.current_versions, file_versions
        )
        
        # Should match despite internal/package name difference
        self.assertTrue(match)
    
    def test_mismatched_cmake_version(self):
        """Test detection of mismatched cmake version."""
        file_versions = {
            "python": "3.12",
            "cmake": "3.28",  # Old version
            "conan": "2.24",
            "llvm-tools": "21",
            "clang": "21",
            "gcc": "13",
            "gxx": "13",
            "ninja": "1.13",
        }
        
        match, mismatches = VersionMatcher.versions_match(
            self.current_versions, file_versions
        )
        
        self.assertFalse(match)
        self.assertTrue(any("cmake" in m and "3.28" in m for m in mismatches))
    
    def test_mismatched_llvm_tools(self):
        """Test detection of mismatched llvm-tools version."""
        file_versions = {
            "python": "3.12",
            "cmake": "4.2",
            "conan": "2.24",
            "llvm-tools": "20",  # Wrong version
            "clang": "21",
            "gcc": "13",
            "gxx": "13",
            "ninja": "1.13",
        }
        
        match, mismatches = VersionMatcher.versions_match(
            self.current_versions, file_versions
        )
        
        self.assertFalse(match)
        self.assertTrue(any("llvm-tools" in m for m in mismatches))
    
    def test_mismatched_clang_version(self):
        """Test detection of mismatched clang version."""
        file_versions = {
            "python": "3.12",
            "cmake": "4.2",
            "conan": "2.24",
            "llvm-tools": "21",
            "clang": "20",  # Wrong version
            "gcc": "13",
            "gxx": "13",
            "ninja": "1.13",
        }
        
        match, mismatches = VersionMatcher.versions_match(
            self.current_versions, file_versions
        )
        
        self.assertFalse(match)
        self.assertTrue(any("clang" in m and "20" in m for m in mismatches))
    
    def test_mismatched_gcc_version(self):
        """Test detection of mismatched gcc version."""
        file_versions = {
            "python": "3.12",
            "cmake": "4.2",
            "conan": "2.24",
            "llvm-tools": "21",
            "clang": "21",
            "gcc": "12",  # Wrong version
            "gxx": "13",
            "ninja": "1.13",
        }
        
        match, mismatches = VersionMatcher.versions_match(
            self.current_versions, file_versions
        )
        
        self.assertFalse(match)
        self.assertTrue(any("gcc" in m and "12" in m for m in mismatches))
    
    def test_mismatched_ninja_version(self):
        """Test detection of mismatched ninja version."""
        file_versions = {
            "python": "3.12",
            "cmake": "4.2",
            "conan": "2.24",
            "llvm-tools": "21",
            "clang": "21",
            "gcc": "13",
            "gxx": "13",
            "ninja": "1.12",  # Wrong version
        }
        
        match, mismatches = VersionMatcher.versions_match(
            self.current_versions, file_versions
        )
        
        self.assertFalse(match)
        self.assertTrue(any("ninja" in m and "1.12" in m for m in mismatches))
    
    def test_multiple_mismatches(self):
        """Test detection of multiple mismatches."""
        file_versions = {
            "python": "3.11",  # Wrong
            "cmake": "3.28",   # Wrong
            "conan": "2.24",
            "llvm-tools": "21",
            "clang": "21",
            "gcc": "13",
            "gxx": "13",
            "ninja": "1.13",
        }
        
        match, mismatches = VersionMatcher.versions_match(
            self.current_versions, file_versions
        )
        
        self.assertFalse(match)
        # Should report both mismatches
        self.assertGreaterEqual(len(mismatches), 2)
    
    def test_empty_file_versions(self):
        """Test with empty file versions."""
        file_versions = {}
        
        match, mismatches = VersionMatcher.versions_match(
            self.current_versions, file_versions
        )
        
        self.assertFalse(match)
        self.assertTrue(len(mismatches) > 0)
    
    def test_minimal_config(self):
        """Test with minimal tool configuration."""
        minimal_config = {
            "python": "3.12",
            "cmake": "4.2",
            "conan2": "2.24",
        }
        
        file_versions = {
            "python": "3.12",
            "cmake": "4.2",
            "conan": "2.24",
        }
        
        match, mismatches = VersionMatcher.versions_match(
            minimal_config, file_versions
        )
        
        self.assertTrue(match)
        self.assertEqual(len(mismatches), 0)


class TestConvenienceFunctions(unittest.TestCase):
    """Test convenience wrapper functions."""
    
    def test_parse_yml_dependencies(self):
        """Test parse_yml_dependencies convenience function."""
        yml = "- python=3.12\n- cmake>=4.2"
        
        versions = parse_yml_dependencies(yml)
        
        self.assertEqual(versions["python"], "3.12")
        self.assertEqual(versions["cmake"], "4.2")
    
    def test_check_versions_matching(self):
        """Test check_versions with matching versions."""
        current = {
            "python": "3.12",
            "cmake": "4.2",
            "conan2": "2.24",
            "gcc": "13",
            "gxx": "13",
            "ninja": "1.13",
        }
        
        yml = """- python=3.12
- cmake>=4.2
- conan>=2.24
- gcc>=13
- gxx>=13
- ninja>=1.13"""
        
        match, mismatches = check_versions(current, yml)
        
        self.assertTrue(match)
        self.assertEqual(len(mismatches), 0)
    
    def test_check_versions_mismatch(self):
        """Test check_versions with mismatching versions."""
        current = {
            "python": "3.12",
            "cmake": "4.2",
            "conan2": "2.24",
            "gcc": "13",
            "gxx": "13",
            "ninja": "1.13",
        }
        
        yml = """- python=3.11
- cmake>=4.2
- conan>=2.24
- gcc>=13
- gxx>=13
- ninja>=1.13"""
        
        match, mismatches = check_versions(current, yml)
        
        self.assertFalse(match)
        self.assertTrue(any("python" in m for m in mismatches))


class TestEdgeCases(unittest.TestCase):
    """Test edge cases and special scenarios."""
    
    def test_yml_with_comments(self):
        """Test parsing yml with comments."""
        yml = """# This is a comment
- python=3.12  # Python version
# Another comment
- cmake>=4.2   # CMake version"""
        
        versions = YmlVersionParser.parse_yml_content(yml)
        
        self.assertEqual(versions["python"], "3.12")
        self.assertEqual(versions["cmake"], "4.2")
    
    def test_yml_with_tabs(self):
        """Test parsing yml with tab indentation."""
        yml = """\t- python=3.12
\t- cmake>=4.2"""
        
        versions = YmlVersionParser.parse_yml_content(yml)
        
        self.assertEqual(versions["python"], "3.12")
        self.assertEqual(versions["cmake"], "4.2")
    
    def test_version_with_patch_number(self):
        """Test parsing versions with patch numbers."""
        yml = "- python=3.12.5\n- cmake>=4.2.1"
        
        versions = YmlVersionParser.parse_yml_content(yml)
        
        self.assertEqual(versions["python"], "3.12.5")
        self.assertEqual(versions["cmake"], "4.2.1")
    
    def test_different_operators(self):
        """Test parsing different version operators."""
        yml = """- python=3.12
- cmake>=4.2
- ninja>1.11
- gcc<=13
- clang<22"""
        
        versions = YmlVersionParser.parse_yml_content(yml)
        
        self.assertEqual(versions["python"], "3.12")
        self.assertEqual(versions["cmake"], "4.2")
        self.assertEqual(versions["ninja"], "1.11")
        self.assertEqual(versions["gcc"], "13")
        self.assertEqual(versions["clang"], "22")


if __name__ == '__main__':
    unittest.main()
