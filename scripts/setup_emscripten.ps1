$EmsdkDir = Join-Path $PSScriptRoot "..\emsdk"

if (-not (Test-Path $EmsdkDir)) {
    git clone https://github.com/emscripten-core/emsdk.git $EmsdkDir
}

Push-Location $EmsdkDir
.\emsdk.bat install latest
.\emsdk.bat activate latest
Pop-Location