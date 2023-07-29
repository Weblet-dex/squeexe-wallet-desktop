Set-ExecutionPolicy RemoteSigned -scope CurrentUser

$Env:QT_INSTALL_CMAKE_PATH = "C:\Qt\5.15.2\msvc2019_64"
$Env:QT_ROOT = "C:\Qt"

git clone https://github.com/Weblet-dex/coins/ -b master
mkdir -p atomic_defi_design\assets\images\coins
Get-Item -Path "coins\icons\*.png" | Move-Item -Destination "atomic_defi_design\assets\images\coins"

mkdir build
cd build

Invoke-Expression "cmake -DCMAKE_BUILD_TYPE=Release ../ -GNinja"
cmake --build . --config Release --target squeexedex-wallet
cmd /c 'pause'