rm -rf ./emsdk
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk || exit
git checkout main
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
cd ..
emcc process.cpp -s LINKABLE=1 -s WASM=0 -s  EXPORTED_RUNTIME_METHODS='["ccall","cwrap"]'
