Set-ExecutionPolicy RemoteSigned -scope CurrentUser

$Env:QT_INSTALL_CMAKE_PATH = "C:\Qt\5.15.2\msvc2019_64"
$Env:QT_ROOT = "C:\Qt"

mkdir build
cd build

Invoke-Expression "cmake -DCMAKE_BUILD_TYPE=Release ../ -GNinja"
cmake --build . --config Release --target squeexedex-wallet
Copy-Item "C:\Dev_Squeexe\squeexe-wallet-desktop\build\bin" -Destination "C:\Users\Shaun\Documents\Squeexe\Builds\bin" -force
git restore
cmd /c 'pause'