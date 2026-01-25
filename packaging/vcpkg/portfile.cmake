vcpkg_minimum_required(VERSION 2022-10-27)

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO peregrin71/pkr_si_units
    REF "v${VERSION}"
    SHA512 0
    HEAD_REF main
)

# Header-only library - nothing to build
vcpkg_cmake_get_vars(INSTALL_PREFIX)

file(INSTALL "${SOURCE_PATH}/sdk/include/si_units"
    DESTINATION "${CURRENT_PACKAGES_DIR}/include"
)

file(INSTALL "${SOURCE_PATH}/LICENSE"
    DESTINATION "${CURRENT_PACKAGES_DIR}/share/si-units"
    RENAME copyright
)

set(VCPKG_POLICY_EMPTY_PACKAGE enabled)
