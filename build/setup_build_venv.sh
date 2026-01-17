#!/bin/bash
# SI Units Build Environment Setup (Bash)
# Sets up Miniconda and creates build_si_units_1.0 virtual environment
# No Python required - bash is always available on Linux/macOS

set -e

# ============================================================================
# CONFIGURATION: Tool versions
# ============================================================================

ENV_NAME="build_si_units_1.0"
CONDA_CHANNEL="conda-forge"

declare -A TOOL_VERSIONS=(
    ["python"]="3.12"
    ["cmake"]="4.2"
    ["conan2"]="2.24"
    ["llvm"]="21"
    ["clang"]="21"
    ["gcc"]="13"
    ["gxx"]="13"
    ["ninja"]="1.13"
)

# ============================================================================
# COLOR OUTPUT
# ============================================================================

CYAN='\033[36m'
YELLOW='\033[33m'
GREEN='\033[32m'
RED='\033[31m'
NC='\033[0m' # No Color

print_header() {
    echo -e "${CYAN}$1${NC}"
}

print_step() {
    echo -e "${YELLOW}$1...${NC}"
}

print_success() {
    echo -e "${GREEN}$1${NC}"
}

print_error() {
    echo -e "${RED}$1${NC}" >&2
}

print_info() {
    echo -e "${CYAN}$1${NC}"
}

# ============================================================================
# MINICONDA DETECTION AND INSTALLATION
# ============================================================================

find_conda_executable() {
    local conda_paths=(
        "$HOME/miniconda3/bin/conda"
        "$HOME/opt/miniconda3/bin/conda"
        "/opt/miniconda3/bin/conda"
    )

    for path in "${conda_paths[@]}"; do
        if [ -f "$path" ]; then
            echo "$path"
            return 0
        fi
    done

    return 1
}

test_conda_in_path() {
    command -v conda &> /dev/null
}

install_miniconda() {
    print_step "Installing Miniconda3"
    
    local temp_dir="/tmp/miniconda_install"
    mkdir -p "$temp_dir"
    
    local installer_path="$temp_dir/Miniconda3-latest-Linux-x86_64.sh"
    local installer_url="https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh"
    local install_dir="$HOME/miniconda3"
    
    # Remove partial/existing installation if present
    if [ -d "$install_dir" ]; then
        print_info "Removing existing Miniconda installation at $install_dir..."
        if ! rm -rf "$install_dir"; then
            print_error "Failed to remove existing installation at $install_dir"
            print_info "Please manually remove this directory and try again"
            exit 1
        fi
        print_success "Removed existing installation"
    fi
    
    print_info "Downloading Miniconda installer..."
    if ! curl -fSL -o "$installer_path" "$installer_url"; then
        print_error "Failed to download Miniconda installer"
        print_info "Please install Miniconda manually from: https://docs.conda.io/en/latest/miniconda.html"
        exit 1
    fi
    
    print_info "Running Miniconda installer (this may take a few minutes) to $install_dir..."
    
    if ! bash "$installer_path" -b -p "$install_dir"; then
        print_error "Miniconda installation failed"
        print_info "Please install Miniconda manually from: https://docs.conda.io/en/latest/miniconda.html"
        exit 1
    fi
    
    print_success "Miniconda installed to $install_dir"
    
    # Initialize conda and add to PATH
    print_info "Initializing Conda..."
    "$install_dir/bin/conda" init bash 2>/dev/null || true
    
    # Add to PATH for current session
    export PATH="$install_dir/bin:$PATH"
    
    print_success "Miniconda installation complete"
    echo "$install_dir/bin/conda"
}

get_conda_executable() {
    # Check if conda is in PATH
    if test_conda_in_path; then
        echo "conda"
        return 0
    fi

    # Check standard locations
    if conda_exe=$(find_conda_executable); then
        echo "$conda_exe"
        return 0
    fi

    # Try to install Miniconda
    print_info "Conda not found in PATH or standard locations"
    conda_exe=$(install_miniconda)
    echo "$conda_exe"
    return 0
}

# ============================================================================
# ENVIRONMENT YAML GENERATION
# ============================================================================

generate_environment_yml() {
    cat << EOF
# SI Units Build Environment
# Environment name: $ENV_NAME
# Auto-generated: Do not edit manually
# Update tool versions in build/setup_build_venv.ps1 or build/setup_build_venv.sh

name: $ENV_NAME
channels:
  - conda-forge
dependencies:
  # Core tools
  - python=${TOOL_VERSIONS[python]}
  - cmake>=${TOOL_VERSIONS[cmake]}
  - conan>=${TOOL_VERSIONS[conan2]}
  
  # LLVM/Clang toolchain
  - llvm-tools>=${TOOL_VERSIONS[llvm]}
  - clang>=${TOOL_VERSIONS[clang]}
  - clang-tools>=${TOOL_VERSIONS[clang]}
  - lld>=${TOOL_VERSIONS[llvm]}
  
  # GCC toolchain
  - gcc>=${TOOL_VERSIONS[gcc]}
  - gxx>=${TOOL_VERSIONS[gxx]}
  
  # Build utilities
  - ninja>=${TOOL_VERSIONS[ninja]}
EOF
}

write_environment_yml() {
    local project_root="$1"
    local env_file="$project_root/build_venv.yml"

    generate_environment_yml > "$env_file"
    print_success "Generated build_venv.yml at $env_file"
    echo "$env_file"
}

get_yml_versions() {
    local env_file="$1"
    
    if [ ! -f "$env_file" ]; then
        echo ""
        return
    fi

    grep "^\s*-\s" "$env_file" | grep -E "(python|cmake|conan|llvm|clang)" | \
        sed 's/.*-\s\+\([^=]*\)=\([^ ]*/\1=\2/' | \
        sed 's/[><=]*//g'
}

test_versions_match() {
    local env_file="$1"
    
    if [ ! -f "$env_file" ]; then
        return 1
    fi

    # Check each tool in TOOL_VERSIONS exists and matches in file
    for tool in "${!TOOL_VERSIONS[@]}"; do
        local expected_version="${TOOL_VERSIONS[$tool]}"
        
        # Extract version from yml file - handle various formats like "python=3.12" or "cmake>=3.28"
        local file_version=$(grep "^\s*-\s*$tool" "$env_file" 2>/dev/null | \
            sed "s/.*$tool[=>]*\([0-9.]*\).*/\1/" | head -1)
        
        if [ -z "$file_version" ]; then
            # Tool is new, not in yaml file
            return 1
        fi
        
        # Check version match
        if [ "${expected_version}" != "${file_version}" ]; then
            return 1
        fi
    done

    # Check if any tools in file are no longer in TOOL_VERSIONS
    # Extract all tool names from dependencies section
    local file_tools=$(grep "^\s*-\s" "$env_file" | \
        grep -E "(python|cmake|conan|llvm|clang|ninja|git)" | \
        sed 's/.*-\s*\([a-z-]*\).*/\1/' | sort -u)
    
    for file_tool in $file_tools; do
        # Check if this tool is in TOOL_VERSIONS
        if [ -z "${TOOL_VERSIONS[$file_tool]}" ] 2>/dev/null; then
            # Tool was removed from config
            return 1
        fi
    done

    return 0
}

# ============================================================================
# ENVIRONMENT MANAGEMENT
# ============================================================================

test_environment_exists() {
    local conda_exe="$1"
    
    if "$conda_exe" env list | grep -q "^$ENV_NAME "; then
        return 0
    fi
    return 1
}

new_environment() {
    local conda_exe="$1"
    local env_file="$2"

    print_step "Creating Conda environment '$ENV_NAME'"

    if ! "$conda_exe" env create --file "$env_file" --force; then
        print_error "Failed to create environment"
        exit 1
    fi

    print_success "Environment '$ENV_NAME' created successfully"
}

update_environment() {
    local conda_exe="$1"
    local env_file="$2"

    print_step "Updating Conda environment '$ENV_NAME'"

    if ! "$conda_exe" env update --file "$env_file" --name "$ENV_NAME"; then
        print_error "Failed to update environment"
        exit 1
    fi

    print_success "Environment '$ENV_NAME' updated successfully"
}

get_activation_command() {
    echo "conda activate $ENV_NAME"
}

# ============================================================================
# MAIN SETUP FUNCTION
# ============================================================================

invoke_setup() {
    local project_root=$(dirname "$SCRIPT_DIR")

    print_header "SI Units Build Environment Setup"
    print_info "Environment: $ENV_NAME"
    print_info "Channel: $CONDA_CHANNEL"
    print_info "Tool Versions:"
    for tool in $(echo "${!TOOL_VERSIONS[@]}" | tr ' ' '\n' | sort); do
        print_info "  - $tool: ${TOOL_VERSIONS[$tool]}"
    done
    print_info ""

    # Step 1: Check Miniconda
    print_step "Checking Miniconda installation"
    conda_exe=$(get_conda_executable)
    version=$("$conda_exe" --version)
    print_success "Found: $version"
    print_info ""

    # Step 2: Generate build_venv.yml
    # Step 2: Check/Generate build_venv.yml
    print_step "Checking build_venv.yml"
    local project_env_file="$project_root/build_venv.yml"
    local needs_update=true
    
    if [ -f "$project_env_file" ]; then
        print_info "build_venv.yml exists, checking versions..."
        
        if test_versions_match "$project_env_file"; then
            print_success "Tool versions match, no update needed"
            needs_update=false
            env_file="$project_env_file"
        else
            print_info "Tool versions mismatch, will update environment"
            env_file=$(write_environment_yml "$project_root")
        fi
    else
        print_info "build_venv.yml not found, generating..."
        env_file=$(write_environment_yml "$project_root")
    fi
    print_info ""

    # Step 3: Create or update environment (only if needed)
    if test_environment_exists "$conda_exe"; then
        print_info "Environment '$ENV_NAME' already exists"
        
        if [ "$needs_update" = true ]; then
            if [ "$UPDATE_FLAG" = true ]; then
                update_environment "$conda_exe" "$env_file"
            else
                read -p "Update environment with new versions? (y/n) [y]: " -r response
                if [[ ! $response =~ ^[Nn]$ ]]; then
                    update_environment "$conda_exe" "$env_file"
                fi
            fi
        else
            print_success "Environment is up to date, skipping update"
        fi
    else
        new_environment "$conda_exe" "$env_file"
    fi

    print_info ""

    # Step 4: Display activation instructions
    print_success "Environment setup complete!"
    print_info ""
    print_info "To activate the environment, run:"
    print_header "  $(get_activation_command)"
    print_info ""
    print_info "To deactivate, run:"
    print_header "  conda deactivate"
    print_info ""
}

# ============================================================================
# MAIN
# ============================================================================

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
UPDATE_FLAG=false
SHOW_VERSIONS=false

# Parse arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --update)
            UPDATE_FLAG=true
            shift
            ;;
        --show-versions)
            SHOW_VERSIONS=true
            shift
            ;;
        *)
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
done

if [ "$SHOW_VERSIONS" = true ]; then
    print_header "SI Units Build Environment - Tool Versions"
    for tool in $(echo "${!TOOL_VERSIONS[@]}" | tr ' ' '\n' | sort); do
        print_info "$tool: ${TOOL_VERSIONS[$tool]}"
    done
    exit 0
fi

invoke_setup
