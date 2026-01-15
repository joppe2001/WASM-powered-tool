# WASM - C++ Source Code

This folder contains all your C++ code that will be compiled to WebAssembly.

## Structure

```
wasm/
  src/         # Your C++ source files (.cpp, .h)
  build/       # Compiled .wasm and .js glue files (generated)
```

## What goes here

- `src/main.cpp` - Your main C++ entry point
- `src/*.h` - Header files
- Any C++ libraries you want to use

## How to compile

You need **Emscripten** installed. Then run:

```bash
cd wasm
emcc src/main.cpp -o build/module.js \
  -s WASM=1 \
  -s EXPORTED_RUNTIME_METHODS='["ccall","cwrap"]' \
  -s ALLOW_MEMORY_GROWTH=1 \
  -O3
```

This generates:
- `build/module.js` - JavaScript glue code
- `build/module.wasm` - The actual WebAssembly binary

## Learning Resources

1. **Emscripten Setup**
   - https://emscripten.org/docs/getting_started/downloads.html

2. **Emscripten Tutorial**
   - https://emscripten.org/docs/getting_started/Tutorial.html

3. **Calling C++ from JS (embind)**
   - https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html

4. **Memory Management**
   - https://emscripten.org/docs/porting/emscripten-runtime-environment.html

## Example: Simple Image Grayscale

```cpp
// src/main.cpp
#include <emscripten/bind.h>
#include <vector>

std::vector<uint8_t> grayscale(std::vector<uint8_t> pixels, int width, int height) {
    std::vector<uint8_t> result(width * height * 4);
    
    for (int i = 0; i < width * height; i++) {
        int idx = i * 4;
        uint8_t gray = (pixels[idx] + pixels[idx+1] + pixels[idx+2]) / 3;
        result[idx] = gray;     // R
        result[idx+1] = gray;   // G
        result[idx+2] = gray;   // B
        result[idx+3] = pixels[idx+3]; // A (keep alpha)
    }
    
    return result;
}

EMSCRIPTEN_BINDINGS(module) {
    emscripten::function("grayscale", &grayscale);
    emscripten::register_vector<uint8_t>("Uint8Vector");
}
```

Compile with embind:
```bash
emcc src/main.cpp -o build/module.js \
  -lembind \
  -s WASM=1 \
  -s ALLOW_MEMORY_GROWTH=1 \
  -O3
```
