# SI Units Build Environment Setup (PowerShell)
# Sets up Miniconda and creates build_si_units_1.0 virtual environment
# No Python required - PowerShell is always available on Windows

param(
    [switch]$Update,
    [switch]$ShowVersions,
    [switch]$ForceRecreate
)

$ErrorActionPreference = "Stop"

# ============================================================================
# CONFIGURATION: Tool versions
# ============================================================================

$ENV_NAME = "build_si_units_1.0"
$CONDA_CHANNEL = "conda-forge"

$TOOL_VERSIONS = @{
    "clang"   = "18"
    "cmake"   = "4.2"
    "conan2"  = "2.24"
    "gcc"     = "13"
    "gxx"     = "13"
    "llvm"    = "18"
    "ninja"   = "1.13"
    "python"  = "3.12"
}

# ============================================================================
# COLOR OUTPUT
# ============================================================================

function Write-Header {
    param([string]$Text)
    Write-Host $Text -ForegroundColor Cyan
}

function Write-Step {
    param([string]$Text)
    Write-Host "$Text..." -ForegroundColor Yellow
}

function Write-Success {
    param([string]$Text)
    Write-Host $Text -ForegroundColor Green
}

function Write-Error-Custom {
    param([string]$Text)
    Write-Host $Text -ForegroundColor Red -ErrorAction Continue
}

function Write-Info {
    param([string]$Text)
    Write-Host $Text -ForegroundColor Cyan
}

# ============================================================================
# MINICONDA DETECTION AND INSTALLATION
# ============================================================================

function Find-CondaExecutable {
    $condaPaths = @(
        "$env:USERPROFILE\miniconda3\conda.exe",
        "$env:USERPROFILE\miniconda3\bin\conda.exe",
        "$env:USERPROFILE\Miniconda3\conda.exe",
        "$env:USERPROFILE\Miniconda3\bin\conda.exe",
        "C:\miniconda3\conda.exe",
        "C:\miniconda3\Scripts\conda.exe"
    )

    foreach ($path in $condaPaths) {
        if (Test-Path $path) {
            return $path
        }
    }

    return $null
}

function Test-CondaInPath {
    try {
        $null = & conda --version 2>$null
        return $true
    } catch {
        return $false
    }
}

function Install-Miniconda {
    Write-Step "Installing Miniconda3"
    
    $tempDir = Join-Path $env:TEMP "miniconda_install"
    New-Item -ItemType Directory -Path $tempDir -Force | Out-Null
    
    $installerPath = Join-Path $tempDir "Miniconda3-latest-Windows-x86_64.exe"
    $installerUrl = "https://repo.anaconda.com/miniconda/Miniconda3-latest-Windows-x86_64.exe"
    
    $installDir = Join-Path $env:USERPROFILE "miniconda3"
    
    # Remove partial/existing installation if present
    if (Test-Path $installDir) {
        Write-Info "Removing existing Miniconda installation at $installDir..."
        try {
            Remove-Item -Path $installDir -Recurse -Force -ErrorAction Stop
            Write-Success "Removed existing installation"
        } catch {
            Write-Error-Custom "Failed to remove existing installation at $installDir"
            Write-Info "Please manually remove this directory and try again"
            exit 1
        }
    }
    
    Write-Info "Downloading Miniconda installer..."
    try {
        $ProgressPreference = 'SilentlyContinue'
        Invoke-WebRequest -Uri $installerUrl -OutFile $installerPath -ErrorAction Stop
    } catch {
        Write-Error-Custom "Failed to download Miniconda installer"
        Write-Info "Please install Miniconda manually from: https://docs.conda.io/en/latest/miniconda.html"
        exit 1
    }
    
    Write-Info "Running Miniconda installer (this may take a few minutes)..."
    
    # Use silent installation with /S flag and /D for install directory
    $process = Start-Process -FilePath $installerPath -ArgumentList "/S /D=$installDir" -NoNewWindow -Wait -PassThru
    
    if ($process.ExitCode -ne 0) {
        Write-Error-Custom "Miniconda installation failed with exit code $($process.ExitCode)"
        Write-Info "Please install Miniconda manually from: https://docs.conda.io/en/latest/miniconda.html"
        exit 1
    }
    
    Write-Success "Miniconda installed to $installDir"
    
    # Add conda to PATH for current session
    $env:PATH = "$installDir;$installDir\Scripts;$installDir\Library\bin;$env:PATH"
    
    # Initialize conda
    Write-Info "Initializing Conda..."
    & "$installDir\Scripts\conda.exe" init powershell 2>&1 | Out-Null
    
    Write-Success "Miniconda installation complete"
    return "$installDir\Scripts\conda.exe"
}

function Get-CondaExecutable {
    # Check if conda is in PATH
    if (Test-CondaInPath) {
        return "conda"
    }

    # Check standard locations
    $condaExe = Find-CondaExecutable
    if ($condaExe) {
        Write-Info "Found Miniconda at: $condaExe"
        # Add to PATH for current session
        $installDir = Split-Path (Split-Path $condaExe)
        $env:PATH = "$installDir;$installDir\Scripts;$installDir\Library\bin;$env:PATH"
        return $condaExe
    }

    # Try to install Miniconda
    Write-Info "Conda not found in PATH or standard locations"
    $condaExe = Install-Miniconda
    return $condaExe
}

# ============================================================================
# ENVIRONMENT YAML GENERATION
# ============================================================================

function Generate-EnvironmentYml {
    $content = @"
# SI Units Build Environment
# Environment name: $ENV_NAME
# Auto-generated: Do not edit manually
# Update tool versions in build/setup_build_venv.ps1 or build/setup_build_venv.sh

name: $ENV_NAME
channels:
  - conda-forge
dependencies:
  # Core tools
  - python=$($TOOL_VERSIONS['python'])
  - cmake>=$($TOOL_VERSIONS['cmake'])
  - conan>=$($TOOL_VERSIONS['conan2'])
  
  # LLVM/Clang toolchain
  - llvm-tools>=$($TOOL_VERSIONS['llvm'])
  - clang>=$($TOOL_VERSIONS['clang'])
  - clang-tools>=$($TOOL_VERSIONS['clang'])
  - lld>=$($TOOL_VERSIONS['llvm'])
  
  # GCC toolchain with build tools
  - gcc>=$($TOOL_VERSIONS['gcc'])
  - gxx>=$($TOOL_VERSIONS['gxx'])
  - binutils
  
  # Build utilities
  - ninja>=$($TOOL_VERSIONS['ninja'])
"@
    return $content
}

function Write-EnvironmentYml {
    param([string]$ProjectRoot)

    $envFile = Join-Path $ProjectRoot "build_venv.yml"
    $content = Generate-EnvironmentYml

    Set-Content -Path $envFile -Value $content
    Write-Success "Generated build_venv.yml at $envFile"
    return $envFile
}

function Get-YmlVersions {
    param([string]$EnvFile)

    if (-not (Test-Path $envFile)) {
        return @{}
    }

    $versions = @{}
    $content = Get-Content $envFile

    foreach ($line in $content) {
        # Match lines like "- python=3.12" or "- cmake>=4.2"
        # Skip lines that don't have version operators (= or >=)
        if ($line -match '^\s*-\s+([\w-]+)\s*([><=]+)\s*(.+)$') {
            $tool = $matches[1]
            $operator = $matches[2]
            $version = $matches[3] -replace '^\s+|\s+$', ''
            $versions[$tool] = $version
        }
    }

    return $versions
}

function Test-VersionsMatch {
    param([hashtable]$CurrentVersions, [hashtable]$FileVersions)

    # If no file versions, needs update
    if ($FileVersions.Count -eq 0) {
        return $false
    }

    # Check all tools in TOOL_VERSIONS against what's in the yml file
    # Special mappings for tools with different names in yml vs TOOL_VERSIONS
    $toolMappings = @{
        "conan2"  = "conan"           # Internal name vs package name
        # All other tools map directly: gcc->gcc, python->python, etc.
    }
    
    foreach ($tool in $CurrentVersions.Keys) {
        # Skip LLVM/clang compound checks - they're checked separately
        if ($tool -eq "llvm" -or $tool -eq "clang") {
            continue
        }
        
        # Get the package name (handles special cases like conan2->conan)
        $packageName = if ($toolMappings.ContainsKey($tool)) { 
            $toolMappings[$tool] 
        } else { 
            $tool 
        }
        
        # Check if tool exists in file versions
        if (-not $FileVersions.ContainsKey($packageName)) {
            Write-Info "  Tool '$packageName' missing from build_venv.yml"
            return $false
        }
        
        # Check if version matches (exact match required)
        if ($CurrentVersions[$tool] -ne $FileVersions[$packageName]) {
            Write-Info "  Version mismatch for '$packageName': expected $($CurrentVersions[$tool]), found $($FileVersions[$packageName])"
            return $false
        }
    }

    # For LLVM/Clang, we check that at least llvm-tools and clang are present with matching versions
    if ($CurrentVersions.ContainsKey("llvm") -and $CurrentVersions.ContainsKey("clang")) {
        $llvmVersion = $CurrentVersions["llvm"]
        $clangVersion = $CurrentVersions["clang"]
        
        if ($FileVersions.ContainsKey("llvm-tools") -and $FileVersions["llvm-tools"] -ne $llvmVersion) {
            return $false
        }
        
        if ($FileVersions.ContainsKey("clang") -and $FileVersions["clang"] -ne $clangVersion) {
            return $false
        }
    }

    return $true
}

# ============================================================================
# ENVIRONMENT MANAGEMENT
# ============================================================================

function Test-EnvironmentExists {
    param([string]$CondaExe)

    try {
        $output = & $CondaExe env list --json 2>$null | ConvertFrom-Json
        $envNames = $output.envs | ForEach-Object { Split-Path $_ -Leaf }
        return $ENV_NAME -in $envNames
    } catch {
        return $false
    }
}

function Remove-Environment {
    param([string]$CondaExe)

    Write-Step "Removing existing environment '$ENV_NAME'"

    & $CondaExe env remove --name $ENV_NAME --yes
    
    if ($LASTEXITCODE -ne 0) {
        Write-Error-Custom "Failed to remove environment"
        exit 1
    }

    Write-Success "Environment '$ENV_NAME' removed"
}

function New-Environment {
    param([string]$CondaExe, [string]$EnvFile)

    Write-Step "Creating Conda environment '$ENV_NAME'"

    & $CondaExe env create --file $EnvFile
    
    if ($LASTEXITCODE -ne 0) {
        Write-Error-Custom "Failed to create environment"
        exit 1
    }

    Write-Success "Environment '$ENV_NAME' created successfully"
}

function Update-Environment {
    param([string]$CondaExe, [string]$EnvFile)

    Write-Step "Updating Conda environment '$ENV_NAME'"

    & $CondaExe env update --file $EnvFile --name $ENV_NAME
    
    if ($LASTEXITCODE -ne 0) {
        Write-Error-Custom "Failed to update environment"
        exit 1
    }

    Write-Success "Environment '$ENV_NAME' updated successfully"
}

function Set-ClangPath {
    param([string]$CondaExe)

    Write-Step "Setting Clang PATH in environment"

    # Get the environment path
    $envInfo = & $CondaExe info --envs | Select-String $ENV_NAME
    if (-not $envInfo) {
        Write-Error-Custom "Could not find environment path"
        return
    }
    
    $envPath = ($envInfo.ToString().Trim() -split '\s+')[-1]
    $activateDir = Join-Path $envPath "etc\conda\activate.d"
    $deactivateDir = Join-Path $envPath "etc\conda\deactivate.d"
    
    # Create directories if they don't exist
    if (-not (Test-Path $activateDir)) {
        New-Item -ItemType Directory -Path $activateDir -Force | Out-Null
    }
    if (-not (Test-Path $deactivateDir)) {
        New-Item -ItemType Directory -Path $deactivateDir -Force | Out-Null
    }
    
    # Create activate script
    $activateScript = @"
# Set Clang PATH for Windows
`$env:PATH = "`$env:CONDA_PREFIX/Library/bin;`$env:PATH"
"@
    $activateScript | Out-File -FilePath (Join-Path $activateDir "set_clang_path.ps1") -Encoding UTF8
    
    # Create deactivate script (optional, to restore PATH)
    $deactivateScript = @"
# Restore PATH (basic implementation)
# Note: This is a simple restoration; complex PATH management may need more logic
"@
    $deactivateScript | Out-File -FilePath (Join-Path $deactivateDir "set_clang_path.ps1") -Encoding UTF8
    
    Write-Success "Clang PATH set in environment"
}

function Get-ActivationCommand {
    return "conda activate $ENV_NAME"
}

# ============================================================================
# MAIN SETUP FUNCTION
# ============================================================================

function Invoke-Setup {
    $projectRoot = Split-Path -Parent $PSScriptRoot

    Write-Header "SI Units Build Environment Setup"
    Write-Info "Environment: $ENV_NAME"
    Write-Info "Channel: $CONDA_CHANNEL"
    Write-Info "Tool Versions:"
    foreach ($tool in $TOOL_VERSIONS.Keys | Sort-Object) {
        Write-Info "  - $tool`: $($TOOL_VERSIONS[$tool])"
    }
    Write-Info ""

    # Step 1: Check Miniconda
    Write-Step "Checking Miniconda installation"
    try {
        $condaExe = Get-CondaExecutable
        $version = & $condaExe --version
        Write-Success "Found: $version"
    } catch {
        Write-Error-Custom "Miniconda not found"
        exit 1
    }

    Write-Info ""

    # Step 2: Generate/Check build_venv.yml
    Write-Step "Checking build_venv.yml"
    $projectEnvFile = Join-Path $projectRoot "build_venv.yml"
    
    $needsUpdate = $true
    if (Test-Path $projectEnvFile) {
        Write-Info "build_venv.yml exists, checking versions..."
        $fileVersions = Get-YmlVersions -EnvFile $projectEnvFile
        
        if (Test-VersionsMatch -CurrentVersions $TOOL_VERSIONS -FileVersions $fileVersions) {
            Write-Success "Tool versions match, no update needed"
            $needsUpdate = $false
            $envFile = $projectEnvFile
        } else {
            Write-Info "Tool versions mismatch, will update environment"
            $needsUpdate = $true
            $envFile = Write-EnvironmentYml -ProjectRoot $projectRoot
        }
    } else {
        Write-Info "build_venv.yml not found, generating..."
        $needsUpdate = $true
        $envFile = Write-EnvironmentYml -ProjectRoot $projectRoot
    }
    Write-Info ""

    # Step 3: Create or update environment
    if ($ForceRecreate) {
        if (Test-EnvironmentExists -CondaExe $condaExe) {
            Remove-Environment -CondaExe $condaExe
        }
        New-Environment -CondaExe $condaExe -EnvFile $envFile
        Set-ClangPath -CondaExe $condaExe
    } elseif (Test-EnvironmentExists -CondaExe $condaExe) {
        Write-Info "Environment '$ENV_NAME' already exists"
        
        if ($needsUpdate) {
            Write-Info "Updating environment with new tool versions..."
            Update-Environment -CondaExe $condaExe -EnvFile $envFile
        } else {
            Write-Success "Environment is up to date, skipping update"
        }
        # Always set Clang PATH
        Set-ClangPath -CondaExe $condaExe
    } else {
        New-Environment -CondaExe $condaExe -EnvFile $envFile
        Set-ClangPath -CondaExe $condaExe
    }

    Write-Info ""

    # Step 4: Display activation instructions
    Write-Success "Environment setup complete!"
    Write-Info ""
    Write-Info "To activate the environment, run:"
    Write-Header "  $(Get-ActivationCommand)"
    Write-Info ""
    Write-Info "To deactivate, run:"
    Write-Header "  conda deactivate"
    Write-Info ""
}

# ============================================================================
# MAIN
# ============================================================================

if ($ShowVersions) {
    Write-Header "SI Units Build Environment - Tool Versions"
    foreach ($tool in $TOOL_VERSIONS.Keys | Sort-Object) {
        Write-Info "$tool`: $($TOOL_VERSIONS[$tool])"
    }
    exit 0
}

Invoke-Setup
