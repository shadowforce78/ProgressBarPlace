@echo off
cls
taskkill /f /im GeometryDash.exe
echo "Stopping Geometry Dash...."
echo "Updating...."	
@echo off
geode sdk update
echo "Update complete!"
echo "Installing binaries...."
@echo off
geode sdk install-binaries
echo "Binaries installed!"