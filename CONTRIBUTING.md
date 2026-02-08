# Contributing to pkr_units

Thank you for your interest in contributing to pkr_units. This document describes the expected workflow, code quality checks, and a PR checklist to help get contributions accepted quickly.

## How to contribute

- File an issue to discuss non-trivial changes or to propose new features before investing substantial effort.
- For small fixes (typos, docs, tests), open a pull request directly against the `main` branch.
- Use a feature branch per logical change: `fix/<short-desc>`, `feat/<short-desc>`, or `chore/<short-desc>`.

## Development workflow

1. Sync `main`, create a branch from the latest `main` and implement your changes. Main should always be in a releasable state.
2. Add or update tests for any functional change.
3. Keep commits small and focused; prefer descriptive commit messages.
4. Run the full test suite and formatting checks locally before opening a PR.

## Building and running tests

- Primary build helper: run the repository build script from the repository root.
  - Cross-platform (recommended):

    ```bash
    python build/build.py --help
    python build/build.py  # see available targets and options
    ```

  - On Windows you can use `py -3 build/build.py` or a PowerShell wrapper if preferred, but prefer `build/build.py` as the canonical entrypoint.

- Unit tests: the build script will configure, build and run the test suite. Use the script's options (see `--help`) to run tests and adjust build configuration.

## Code style and static checks

- The project uses `clang-format` rules. Please run `clang-format` on modified C++ files and match the repository style.
- The repository includes `clang-tidy` configurations; run `clang-tidy` locally where applicable and address warnings relevant to your change.
- Follow the naming and style guidelines in `design/agents.md` and `design/DESIGN.md` (type names, `constexpr`/`noexcept` usage, `_t` suffix for strong types, etc.).

## Tests and documentation

- Add unit tests for new functionality and bug fixes. Tests live under `tests/`.
- Update `README.md`, `docs/` or `design/` documents as appropriate for user-facing changes.

## Pull Request checklist

Before requesting review, ensure the following items are complete:

- [ ] The PR targets the `main` branch and has a clear, concise title and description.
- [ ] All new and existing tests pass locally and in CI.
- [ ] `clang-format` has been applied to modified files.
- [ ] `clang-tidy` warnings relevant to the change have been addressed or documented.
- [ ] New functionality includes unit tests and documentation updates where applicable.
- [ ] A short entry describing the user-facing change has been added to `CHANGELOG.md` (if applicable).
- [ ] CI passes (GH Actions) and the PR has at least one reviewer.

## Review process

- Reviews focus on correctness, API clarity, and long-term maintainability.
- The reviewer may request changes; please address them with follow-up commits or by rebasing/squashing as appropriate.

## License

By contributing, you agree that your contributions will be licensed under the project's MIT license.

## Contact

If you find a security issue, see `SECURITY.md` for reporting instructions (or open an issue if no sensitive data is involved).

Thank you for contributing to pkr_units!
