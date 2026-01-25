#!/usr/bin/env python
"""
Simple test runner for build script tests.

Usage:
    python run_tests.py              # Run all tests
    python run_tests.py -v           # Verbose output
    python run_tests.py -q           # Quiet output
"""

import sys
import unittest
from pathlib import Path

# Make sure we can import from this directory
test_dir = Path(__file__).parent
sys.path.insert(0, str(test_dir))

if __name__ == '__main__':
    # Discover and run all tests in this directory
    loader = unittest.TestLoader()
    suite = loader.discover(str(test_dir), pattern='test_*.py')
    
    # Determine verbosity from command line
    verbosity = 2  # Default to verbose
    if len(sys.argv) > 1:
        if sys.argv[1] == '-q':
            verbosity = 1
        elif sys.argv[1] == '-qq':
            verbosity = 0
    
    runner = unittest.TextTestRunner(verbosity=verbosity)
    result = runner.run(suite)
    
    # Exit with appropriate code
    sys.exit(0 if result.wasSuccessful() else 1)
