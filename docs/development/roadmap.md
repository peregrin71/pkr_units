# Development Roadmap

Priorities, planned features, and development tracking for pkr_units.

**Last Updated:** March 2026

---

## 🚨 Critical Work (High Priority)

Security, reliability, and contributor experience. Complete these first.

- [x] Add `CONTRIBUTING.md` with contribution process and PR checklist
- [x] Add `CODE_OF_CONDUCT.md`
- [x] Add `SECURITY.md` (vulnerability reporting instructions)
- [ ] Add `CHANGELOG.md` and adopt release note policy
- [ ] Add GitHub Actions release workflow (automate tagging, release notes)
- [ ] Add CI coverage reporting (Codecov or similar)
- [x] Add UBSan/ASan CI jobs (non-gating tests)
- [x] Add clang-tidy and clang-format checks in CI
- [ ] Provide CMake install/export targets (`install(EXPORT ...)`)
- [ ] Add API doc generation (Doxygen/Sphinx) and publish from CI
- [ ] Add GitHub issue and PR templates

---

## ⚙️ Platform & Packaging (Medium Priority)

Expand distribution channels and automate testing.

- [ ] Add `dependabot.yml` for dependency updates
- [ ] Enable GitHub CodeQL / SCA scanning
- [ ] Add CI workflow for packaging validation (Conan, vcpkg)
- [ ] Implement and test Conan recipes, automate publishing to ConanCenter
- [ ] Implement vcpkg port validation workflow
- [ ] Add release badges and CI status/coverage badges to `README.md`

---

## ✅ Testing & Quality (Medium Priority)

Strengthen test coverage and measurable quality.

- [ ] Add coverage threshold targets (fail builds if below target)
- [ ] Add more sanitizers: ASan, UBSan, MSan (split by job to avoid conflicts)
- [ ] Add fuzzing and property-based tests (libFuzzer / OSS-Fuzz for parsing)
- [ ] Expand test matrix: Windows + Linux + macOS in CI
- [ ] Add integration tests (real-world physics scenarios)
- [ ] Add parsing edge-case and invalid input tests

---

## 📚 Documentation (Medium Priority)

Improve discoverability and usability.

- [ ] Complete auto-generated API reference (headers, all functions)
- [ ] Add more examples: Eigen integration, Python bindings, chrono, formatting
- [ ] Add "Best Practices" guide (affine units, when to use `measurement_t`, stability)
- [ ] Add FAQ and troubleshooting section
- [ ] Publish docs to GitHub Pages or docs site via CI

### Restructuring (In Progress)

- [x] Reorganize docs into user-facing and developer documentation
- [x] Create `docs/development/` for contributor resources
- [x] Consolidate overlapping design documents
- [x] Create architecture overview for users
- [ ] Remove obsolete `design/` folder (move all content to `docs/`)

---

## 🧩 Features & Library Work (Low Priority)

Functional improvements and requested features.

- [x] Implement string parsing API for unit expressions ("5 m", "10 m/s", "100 m²")
- [ ] Add `si_cast<>` and value-type conversion helpers
- [ ] Add matrix/vector containers (vectors of units, matrices of units)
- [ ] Ensure temperature affine behavior is well-specified and documented
- [ ] Add named quantities / quantity types (semantic wrappers)
- [ ] Expand non-SI units: CGS completeness, Imperial, astronomical
- [ ] Add decibel-aware `unit_cast` specializations

---

## ⚡ Performance & Benchmarks (Low Priority)

Measure and optimize.

- [ ] Add runtime performance benchmarks (Google Benchmark vs. raw doubles)
- [ ] Add compile-time performance measurement (template instantiation timing)
- [ ] Add binary size / memory layout benchmarks
- [ ] Add microbenchmarks for storage policies (stack vs. arena)

---

## 🧾 Housekeeping (Low Priority)

Maintenance and process improvements.

- [ ] Add CONTRIBUTING checklists for reviewers/maintainers
- [ ] Add issue labels and milestone templates
- [ ] Keep `packaging/version.txt` as single source of truth
- [ ] Enforce `CHANGELOG.md` updates in release PRs
- [ ] Add license, build, coverage, release badges to `README.md`

---

## ✅ Recently Completed

- [x] Quick start guide in README
- [x] Cross-compiler testing (GCC, Clang, MSVC)
- [x] Clang-format configuration and integration
- [x] Build orchestration (`build/build.py`, conda, cross-platform)
- [x] Compile-time type safety via static assertions in tests
- [x] Documentation reorganization (user vs. developer docs)
- [x] Consolidated overlapping design documentation

---

## Notes for Maintainers

- **Release process:** Bump `packaging/version.txt`, run tests, create GitHub release tag
- **CI/CD:** Runs on every PR; builds for MSVC, GCC, Clang on Windows, Linux
- **Package recipes:** Conan profile in `build/profiles/`; vcpkg port TBD
- **Contributing:** See [CONTRIBUTING.md](../../CONTRIBUTING.md)

---

## Next Up

1. Consolidate remaining design docs into `docs/development/`
2. Add API documentation generation (Doxygen)
3. Implement `CHANGELOG.md` and release workflow
4. Expand test matrix to include macOS

