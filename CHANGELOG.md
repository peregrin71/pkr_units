# Changelog

All notable changes to the pkr_units project are documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

---

## [0.1.0-alpha] - 2026-03-07

### 🎯 Release Overview

**First alpha release** of pkr_units with comprehensive documentation reorganization and new intellectual property protections.

**Key Updates:**
- ✅ Reorganized documentation for clarity and maintainability
- ✅ Consolidated overlapping design documents into focused guides
- ✅ Implemented IP protection layer (robots.txt, AI_POLICY.md, AI_USE_LICENCE.md)
- ✅ Established clear licensing terms for commercial AI use

---

### � Code Changes

#### Added

**C++20 Modernization:**
- Upgraded entire codebase to C++20 standard
- Leveraged modern C++ features:
  - Concepts for type constraints
  - Ranges library for efficient iteration
  - Modules support (where applicable)
  - Designated initializers
  - Spaceship operator (`<=>`) for comparisons
  - Coroutines support (future use)

**Time Series Support:**
- New time-series data handling system
  - Efficient temporal data collections
  - Time-indexed measurements
  - Chronological data validation
  - See [`docs/development/time-series.md`](docs/development/time-series.md) for architecture details
  - See [`docs/development/timelike-system.md`](docs/development/timelike-system.md) for timestamp representation

#### Improved

- Performance optimizations from C++20 features
- Better type safety with concepts
- Enhanced compile-time computations with `constexpr`
- Cleaner, more expressive syntax

#### Changed

- **Minimum Compiler Requirement:** C++20 or later
  - GCC 11+
  - Clang 13+
  - MSVC 2019+

---

### �📚 Documentation Changes

#### Added

**New Documentation Structure (`docs/development/`):**
- [`docs/development/index.md`](docs/development/index.md) — Central hub for developer documentation
- [`docs/development/architecture-deep-dive.md`](docs/development/architecture-deep-dive.md) — Comprehensive internal architecture and design patterns
- [`docs/development/design-decisions.md`](docs/development/design-decisions.md) — Rationale and trade-offs for key architectural decisions
- [`docs/development/time-series.md`](docs/development/time-series.md) — Temporal systems and time-series data handling
- [`docs/development/timelike-system.md`](docs/development/timelike-system.md) — Flexible timestamp representation system
- [`docs/development/storage-policies.md`](docs/development/storage-policies.md) — Memory management and storage optimization strategies
- [`docs/development/roadmap.md`](docs/development/roadmap.md) — Development tracking and future direction

**New User-Facing Documentation:**
- [`docs/guides/parsing.md`](docs/guides/parsing.md) — Practical guide to parsing measurements and units
- [`docs/reference/architecture.md`](docs/reference/architecture.md) — User-friendly overview of library architecture

**Updated Documentation:**
- [`docs/index.md`](docs/index.md) — Improved landing page with clear separation between user and contributor navigation

#### Reorganized

- **Consolidated overlapping design documents** into focused, single-purpose files
  - `design/DESIGN.md` → Split into `docs/development/architecture-deep-dive.md` + `design-decisions.md`
  - `design/TIME_SERIES_DESIGN.md` → Integrated into `docs/development/time-series.md`
  - `design/TIMELIKE_DESIGN.md` → Integrated into `docs/development/timelike-system.md`
  - `design/STORAGE_POLICIES_SUMMARY.md` → Integrated into `docs/development/storage-policies.md`
  - `design/TODO.md` → Moved to `docs/development/roadmap.md`

#### Improved

- Removed duplicate and conflicting documentation
- Established clear organizational hierarchy (user docs vs. developer docs)
- Enhanced cross-references between related documentation
- Aligned documentation structure with industry standards (following nlohmann/json library pattern)

---

### 🔐 IP Protection & Licensing

#### Added

**New Legal & Policy Documents:**

- [`AI_POLICY.md`](AI_POLICY.md) — Comprehensive policy prohibiting use of this code for AI model training
  - Covers LLMs, code generation systems, fine-tuning, and derivative works
  - Establishes legal position on unauthorized AI use
  - Provides contact and enforcement procedures

- [`AI_USE_LICENCE.md`](AI_USE_LICENCE.md) — **NEW: Commercial AI Use License**
  - ⚠️ **Effective March 7, 2026, 00:00 UTC**
  - Clarifies permitted uses (MIT License, no cost)
  - Prohibits AI training use without commercial license (€100,000 fee)
  - Imposes liquidated damages for violations
  - MIT License remains unchanged for all non-AI uses
  - Pre-existing access (before March 7, 2026) not affected
  - Post-access (March 7, 2026+) constitutes acceptance of terms

- [`robots.txt`](robots.txt) — Technical crawler policy
  - 24-hour crawl delay (`Crawl-delay: 86400`)
  - Request rate limit (1 request per 24 hours)
  - Blocks AI/ML crawler bots: CCBot, GPTbot, anthropic-ai, Claude-Web, Apptis, Grok-1, Amazonbot, Bytespider, Petalbot, and others
  - References AI policies

---

### 🛡️ AI Training Protection Layer

**Three-layer approach implemented:**

1. **Policy Layer** (`AI_POLICY.md`, `AI_USE_LICENCE.md`)
   - Legal prohibition on AI model training
   - Clear communication of terms and consequences

2. **Technical Layer** (`robots.txt`)
   - Crawler blocking and rate limiting
   - Ethical signal to compliant services

3. **Legal Layer** (`AI_USE_LICENCE.md`)
   - Liquidated damages clause (€100,000 per breach)
   - Binding prospective terms (effective March 7, 2026)
   - Commercial licensing option available

**Important Notes:**
- Protections take effect **March 7, 2026, 00:00 UTC**
- Pre-existing access operates under standard MIT License (no restrictions)
- MIT License unchanged for all non-AI uses
- Commercial AI use available for €100,000 per license

---

### 📋 Technical Details

#### Version & Build

- **Version:** 0.1.0-alpha
- **Release Date:** March 7, 2026
- **Status:** Alpha release with documentation improvements and IP protections

#### Compatibility

- All existing functionality maintained
- No breaking changes to library API
- MIT License continues to apply for non-AI uses
- Backward compatible with pre-March-7 releases

---

### 🔗 Related Documentation

**For Users:**
- [Getting Started](docs/getting-started.md)
- [API Reference](docs/api/)
- [Unit Conversion Guide](docs/guides/parsing.md)

**For Contributors:**
- [Developer Documentation](docs/development/)
- [Architecture Deep Dive](docs/development/architecture-deep-dive.md)
- [Contributing Guidelines](CONTRIBUTING.md)

**For Licensing Questions:**
- [AI Use License](AI_USE_LICENCE.md)
- [AI Policy](AI_POLICY.md)
- [Code of Conduct](CODE_OF_CONDUCT.md)
- [Security Policy](SECURITY.md)

---

### 📝 Migration Guide (For Existing Users)

If you've been following development on earlier commits:

1. **Documentation URLs have moved:**
   ```
   OLD: design/DESIGN.md
   NEW: docs/development/architecture-deep-dive.md
   ```

2. **Check AI licensing:**
   - If you access this code for AI/ML purposes, review [AI_USE_LICENCE.md](AI_USE_LICENCE.md)
   - Commercial AI use requires €100,000 license

3. **All non-AI uses unchanged:**
   - Standard MIT License continues to apply
   - No impact on existing applications

---

### 🚀 What's Next

See [`docs/development/roadmap.md`](docs/development/roadmap.md) for upcoming features and improvements planned for future releases.

---

### 📢 Acknowledgments

This release incorporates feedback on documentation organization, licensing clarity, and intellectual property protection from the developer community.

---

## Previous Versions

No previous releases. This is the first alpha release.

---

**Questions?** Open an issue or contact maintainers via the repository.
