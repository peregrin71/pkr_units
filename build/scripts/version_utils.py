"""
Version utilities for build environment management.

Handles parsing, comparing, and validating tool versions in conda yml files.
"""

import re
from typing import Dict, List, Tuple


class YmlVersionParser:
    """Parse tool versions from conda environment yml content."""
    
    @staticmethod
    def parse_yml_content(yml_content: str) -> Dict[str, str]:
        """
        Parse tool versions from yml content.
        
        Args:
            yml_content: Raw yml file content as string
            
        Returns:
            Dictionary mapping tool names to versions
            
        Example:
            >>> yml = "- python=3.12\\n- cmake>=4.2"
            >>> YmlVersionParser.parse_yml_content(yml)
            {'python': '3.12', 'cmake': '4.2'}
        """
        versions = {}
        
        for line in yml_content.split('\n'):
            # Match lines like "- python=3.12" or "- cmake>=4.2"
            # Format: - <tool_name> <operator> <version>
            match = re.match(r'^\s*-\s+([\w-]+)\s*([><=]+)\s*(.+)$', line)
            if match:
                tool = match.group(1)
                version = match.group(3).strip()
                # Remove inline comments (anything after #)
                if '#' in version:
                    version = version.split('#')[0].strip()
                versions[tool] = version
        
        return versions


class VersionMatcher:
    """Match versions between configuration and yml files."""
    
    # List of core tools to verify (the ones directly configured)
    CORE_TOOLS = ["python", "cmake", "conan2", "gcc", "gxx", "ninja"]
    
    # Map internal names to conda package names
    PACKAGE_NAME_MAP = {
        "conan2": "conan",  # Internal name for clarity, package is "conan"
    }
    
    @classmethod
    def _get_package_name(cls, tool: str) -> str:
        """Map internal tool name to conda package name."""
        return cls.PACKAGE_NAME_MAP.get(tool, tool)
    
    @classmethod
    def versions_match(
        cls,
        current_versions: Dict[str, str],
        file_versions: Dict[str, str]
    ) -> Tuple[bool, List[str]]:
        """
        Check if current tool versions match yml file versions.
        
        Args:
            current_versions: Dictionary of configured tool versions
            file_versions: Dictionary of versions parsed from yml
            
        Returns:
            Tuple of (match: bool, mismatches: List[str])
            If match is True, mismatches will be empty
        """
        mismatches = []
        
        if not file_versions:
            return False, ["No versions found in yml file"]
        
        # Check core tools exist and match
        for tool in cls.CORE_TOOLS:
            if tool not in current_versions:
                continue
            
            expected_version = current_versions[tool]
            package_name = cls._get_package_name(tool)
            
            if package_name not in file_versions:
                mismatches.append(f"{package_name} not found in yml")
                continue
            
            file_version = file_versions[package_name]
            if expected_version != file_version:
                mismatches.append(
                    f"{package_name}: expected {expected_version}, got {file_version}"
                )
        
        # Check LLVM/Clang toolchain
        llvm_version = current_versions.get("llvm")
        clang_version = current_versions.get("clang")
        
        if llvm_version and clang_version:
            # Check llvm-tools
            if "llvm-tools" in file_versions:
                if llvm_version != file_versions["llvm-tools"]:
                    mismatches.append(
                        f"llvm-tools: expected {llvm_version}, got {file_versions['llvm-tools']}"
                    )
            
            # Check clang version (avoid matching clang-tools)
            if "clang" in file_versions:
                if clang_version != file_versions["clang"]:
                    mismatches.append(
                        f"clang: expected {clang_version}, got {file_versions['clang']}"
                    )
        
        return len(mismatches) == 0, mismatches


def parse_yml_dependencies(yml_content: str) -> Dict[str, str]:
    """Convenience function to parse yml content."""
    return YmlVersionParser.parse_yml_content(yml_content)


def check_versions(
    current: Dict[str, str],
    yml: str
) -> Tuple[bool, List[str]]:
    """
    Convenience function to check if versions match.
    
    Args:
        current: Current tool versions dictionary
        yml: Raw yml file content
        
    Returns:
        Tuple of (match: bool, mismatches: List[str])
    """
    file_versions = YmlVersionParser.parse_yml_content(yml)
    return VersionMatcher.versions_match(current, file_versions)
