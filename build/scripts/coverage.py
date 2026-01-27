"""
Coverage report generation
"""

from pathlib import Path
from typing import Optional
import glob

from build_utils import BuildException, run_command, print_info


def _find_test_binary(build_path: Path) -> Path:
    candidates = [
        build_path / "tests" / "si_units_test",
        build_path / "tests" / "si_units_test.exe",
        build_path / "si_units_test",
        build_path / "si_units_test.exe",
    ]
    for candidate in candidates:
        if candidate.exists():
            return candidate
    raise BuildException("si_units_test binary not found in build directory")


def generate_coverage_report(build_path: Path, coverage_dir: Path) -> None:
    """
    Generate coverage report using llvm-profdata and llvm-cov.
    Outputs:
      - coverage.txt (summary report)
      - html/ (HTML report)
    """
    test_binary = _find_test_binary(build_path)
    profdata_path = coverage_dir / "coverage.profdata"
    html_dir = coverage_dir / "html"
    html_dir.mkdir(parents=True, exist_ok=True)

    profraw_glob = str(coverage_dir / "*.profraw")

    print_info("Listing coverage directory")
    run_command(["ls", "-la", str(coverage_dir)], cwd=str(build_path))

    profraw_files = glob.glob(str(coverage_dir / "*.profraw"))
    if not profraw_files:
        raise BuildException(f"No profraw files found in {coverage_dir}")

    print_info("Merging coverage data")
    cmd = ["llvm-profdata-18", "merge", "-sparse"] + profraw_files + ["-o", str(profdata_path)]
    run_command(cmd, cwd=str(build_path))

    print_info("Generating coverage summary")
    report = run_command(
        ["llvm-cov-18", "report", str(test_binary), f"-instr-profile={profdata_path}"],
        cwd=str(build_path),
        capture_output=True,
    )
    (coverage_dir / "coverage.txt").write_text(report)

    print_info("Generating coverage HTML report")
    run_command(
        [
            "llvm-cov-18",
            "show",
            str(test_binary),
            f"-instr-profile={profdata_path}",
            "-format=html",
            f"-output-dir={html_dir}",
        ],
        cwd=str(build_path),
    )
