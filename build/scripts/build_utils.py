"""
Common build utilities and helper functions
"""

import subprocess
import sys
from typing import List, Optional


class BuildException(Exception):
    """Exception raised during build process"""

    pass


def print_header(text: str) -> None:
    """Print a header message"""
    print(f"\033[36m{text}\033[0m")  # Cyan


def print_step(text: str) -> None:
    """Print a step message"""
    print(f"\033[33m{text}...\033[0m")  # Yellow


def print_success(text: str) -> None:
    """Print a success message"""
    print(f"\033[32m{text}\033[0m")  # Green


def print_error(text: str) -> None:
    """Print an error message"""
    print(f"\033[31m{text}\033[0m", file=sys.stderr)  # Red


def print_info(text: str) -> None:
    """Print an info message"""
    print(f"\033[36m{text}\033[0m")  # Cyan


def run_command(
    cmd: List[str], cwd: Optional[str] = None, capture_output: bool = False
) -> str:
    """
    Run a shell command and handle errors
    
    Args:
        cmd: List of command arguments
        cwd: Working directory to run command in
        capture_output: If True, return output as string
        
    Returns:
        Command output if capture_output is True, else empty string
        
    Raises:
        BuildException: If command fails
    """
    try:
        if capture_output:
            result = subprocess.run(
                cmd, cwd=cwd, capture_output=True, text=True, check=True
            )
            return result.stdout.strip()
        else:
            subprocess.run(cmd, cwd=cwd, check=True)
            return ""
    except subprocess.CalledProcessError as e:
        raise BuildException(f"Command failed: {' '.join(cmd)}\n{e.stderr}")
    except FileNotFoundError:
        raise BuildException(f"Command not found: {cmd[0]}")
