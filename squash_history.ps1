# PowerShell script to squash all Git history into a single commit
# WARNING: This rewrites history and is irreversible. Ensure you have a backup!

Write-Host "Starting Git history squash process..." -ForegroundColor Yellow

# Step 1: Ensure on main branch and pull latest
Write-Host "Step 1: Checking out main and pulling latest changes..." -ForegroundColor Green
git checkout main
if ($LASTEXITCODE -ne 0) { Write-Host "Error: Could not checkout main branch." -ForegroundColor Red; exit 1 }
git pull origin main
if ($LASTEXITCODE -ne 0) { Write-Host "Error: Could not pull from origin main." -ForegroundColor Red; exit 1 }

# Step 2: Create orphan branch
Write-Host "Step 2: Creating orphan branch 'squashed-main'..." -ForegroundColor Green
git checkout --orphan squashed-main
if ($LASTEXITCODE -ne 0) { Write-Host "Error: Could not create orphan branch." -ForegroundColor Red; exit 1 }

# Step 3: Add all files and commit
Write-Host "Step 3: Adding all files and committing..." -ForegroundColor Green
git add -A
if ($LASTEXITCODE -ne 0) { Write-Host "Error: Could not add files." -ForegroundColor Red; exit 1 }
git commit -m "Initial commit: Squashed all history"
if ($LASTEXITCODE -ne 0) { Write-Host "Error: Could not commit." -ForegroundColor Red; exit 1 }

# Step 4: Replace main branch
Write-Host "Step 4: Replacing main branch..." -ForegroundColor Green
git branch -D main
if ($LASTEXITCODE -ne 0) { Write-Host "Error: Could not delete main branch." -ForegroundColor Red; exit 1 }
git branch -m main
if ($LASTEXITCODE -ne 0) { Write-Host "Error: Could not rename branch to main." -ForegroundColor Red; exit 1 }

# Step 5: Force push to remote
Write-Host "Step 5: Force pushing to origin main..." -ForegroundColor Green
git push -f origin main
if ($LASTEXITCODE -ne 0) { Write-Host "Error: Could not force push to origin." -ForegroundColor Red; exit 1 }

Write-Host "History squash completed successfully!" -ForegroundColor Green
Write-Host "Note: Collaborators will need to re-clone or reset their local repos." -ForegroundColor Yellow