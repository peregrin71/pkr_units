# SI Units Library - Development Roadmap

This file organizes ongoing work into clear priorities and actionable checklists. Use it to track repo hygiene, build/CI improvements, documentation, packaging, testing, and feature work.

---

## 🚨 Critical (High priority)
These items improve security, reliability, and contributor experience. Complete these first.

- [x] Add `CONTRIBUTING.md` with contribution process and PR checklist
- [x] Add `CODE_OF_CONDUCT.md`
- [x] Add `SECURITY.md` (vulnerability reporting instructions / contact)
- [ ] Add `CHANGELOG.md` and adopt a release note policy (Keep a `CHANGELOG.md` for user-facing changes)
- [ ] Add a GitHub Actions release workflow to automate tagging and release notes
- [ ] Add CI coverage reporting (build with coverage enabled and upload to Codecov or similar)
- [x] Add UBSan/ASan CI jobs (Linux/Clang) to catch undefined behavior and memory issues (examples-only, tests avoided due to GTest incompatibilities)
- [x] Add CI job(s) to run `clang-tidy` and `clang-format` checks and fail on regressions (non-gating; runs on Ubuntu/Clang)
- [ ] Provide proper `CMake` install/export targets for header-only packaging (`install(EXPORT ...)`, `target_include_directories`, `install(FILES ...)`)
- [ ] Add API doc generation (Doxygen / Sphinx) and publish artifacts from CI
- [ ] Add basic Issue and PR templates (`.github/ISSUE_TEMPLATE`, `.github/PULL_REQUEST_TEMPLATE`)

---

## ⚙️ Platform & Packaging (Medium priority)
Improve package consumption and automation.

- [ ] Add `dependabot.yml` for dependency updates (or equivalent automation)
- [ ] Add GitHub CodeQL / SCA scanning enabled
- [ ] Add CI workflow to validate packaging (Conan, vcpkg) and optionally publish artifacts
- [ ] Implement and test `conan` recipes and automate publishing checks (ConanCenter) in CI
- [ ] Implement `vcpkg` port validation workflow
- [ ] Add release badges and CI status/coverage badges to `README.md`
- [ ] Add a `packaging/CHANGELOG` or release notes automation step in release workflow

---

## ✅ Testing & Quality (Medium priority)
Strengthen tests and measurable quality metrics.

- [ ] Add coverage threshold targets and fail builds if below threshold
- [ ] Add sanitizers: ASan, UBSan, MSan where feasible (split jobs to avoid GTest incompatibilities)
- [ ] Add fuzzing and property-based tests for parsing and unit math (libFuzzer / AFL / OSS-Fuzz pipeline)
- [ ] Expand test matrix to cover Windows + Linux + macOS in CI
- [ ] Add integration/end-to-end examples in tests (real-world physics scenarios)
- [ ] Add targeted tests for parsing edge-cases and invalid inputs

---

## 📚 Documentation & Examples (Medium priority)
Improve discoverability and API quality.

- [ ] Complete API reference for all headers (auto-generated and published)
- [ ] Add more examples covering: Eigen integration, Python bindings usage, chrono integration, formatting
- [ ] Add a Best Practices guide (affine units, when to use `measurement_t`, numeric stability tips)
- [ ] Add FAQ and troubleshooting section to docs
- [ ] Add docs generation and publish to GitHub Pages or docs site via CI

---

## 🧩 Features & Library Work (Medium to Low priority)
Functional improvements and feature requests.

- [ ] Implement string parsing API for unit expressions: "5 m", "10 m/s", "100 m²"
- [ ] Add `si_cast<>` and value-type conversion helpers
- [ ] Add matrix/vector formatting & containers (vectors of units, matrices of units/measurements)
- [ ] Ensure temperature affine behavior is well-specified and documented
- [ ] Add named quantities / quantity types if needed (semantic wrappers)
- [ ] Expand non-SI units: CGS, Imperial completeness, astronomical units
- [ ] Add decibel-aware `unit_cast` specializations and tests (#decibel-unit-cast)

---

## ⚡ Performance & Benchmarks (Low priority)
Measure and optimize performance and compile-time costs.

- [ ] Add runtime performance benchmarks (Google Benchmark) vs raw doubles
- [ ] Add compile-time performance measurement (template instantiation timing) and CI checks
- [ ] Add binary size / memory layout benchmarks for critical paths
- [ ] Add microbenchmarks for storage policies (stack vs arena) and matrix operations

---

## 🧾 Housekeeping & Maintenance (Low priority)
Miscellaneous improvements that keep the repo healthy.

- [ ] Add CONTRIBUTING checklists for reviewers and maintainers
- [ ] Add issue labels and milestone templates for release planning
- [ ] Keep `packaging/version.txt` as single source of truth and ensure recipes read from it
- [ ] Add more changelog discipline: enforce `CHANGELOG.md` updates in release PRs
- [ ] Add badges for license, build, coverage, and release status to `README.md`

---

## ✅ Completed / Already in progress
- [x] Quick start guide in README
- [x] Cross-compiler testing in CI (GCC, Clang, MSVC)
- [x] Formatting rules (`.clang-format`) and local clang-format integration
- [x] Build orchestration (`build/build.py`, conda env, cross-platform)

---

## Next immediate steps (short-term plan)
1. Add `CONTRIBUTING.md`, `CODE_OF_CONDUCT.md`, and `SECURITY.md` (one PR)
2. Add `CHANGELOG.md` and a scripted release job (action + template) (one PR)
3. Add CI coverage job and Codecov upload (one PR)
4. Add sanitizer jobs (ASan/UBSan) and a `clang-tidy` check in CI (one PR)

---

If you'd like, I can open a PR that adds the `CONTRIBUTING.md`, `CODE_OF_CONDUCT.md`, `SECURITY.md`, and a small CI stub for coverage — pick which chunk you want first and I'll prepare the changes.

