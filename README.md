# WASM-Powered Browser Tool

A client-side tool built with Nuxt 4 + C++ compiled to WebAssembly.

## Project Structure

```
WASM-powered-tool/
  app/
    components/      # Vue components (auto-imported)
    composables/     # Reusable composition functions (auto-imported)
    pages/           # File-based routing
    assets/css/      # Global styles
  wasm/
    src/             # C++ source code
    build/           # Compiled WASM output
  workers/           # Web Workers for off-thread processing
  server/api/        # Backend API routes (optional)
  public/wasm/       # Static WASM files
```

Each folder has a README.md explaining what goes there and links to learn more.

## Prerequisites

1. **Node.js / Bun** - For running Nuxt
2. **Emscripten** - For compiling C++ to WASM

### Install Emscripten

```bash
# Clone the SDK
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk

# Install and activate
./emsdk install latest
./emsdk activate latest

# Add to PATH (run every session, or add to .bashrc/.zshrc)
source ./emsdk_env.sh
```

## Development

```bash
# Install dependencies
bun install

# Start dev server
bun run dev
```

## Build WASM

```bash
cd wasm
emcc src/main.cpp -o build/module.js \
  -lembind \
  -s WASM=1 \
  -s ALLOW_MEMORY_GROWTH=1 \
  -s EXPORTED_RUNTIME_METHODS='["ccall","cwrap"]' \
  -O3
```

## Key Resources

| Topic | Link |
|-------|------|
| Nuxt 4 Docs | https://nuxt.com/docs |
| Emscripten | https://emscripten.org/docs |
| embind (C++/JS bridge) | https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html |
| Web Workers | https://developer.mozilla.org/en-US/docs/Web/API/Web_Workers_API |
| WebAssembly | https://developer.mozilla.org/en-US/docs/WebAssembly |

## Next Steps

1. Decide what your tool will do (image processing, compression, etc.)
2. Write C++ code in `wasm/src/`
3. Compile to WASM with Emscripten
4. Create a Web Worker in `workers/` to run WASM off-thread
5. Build the UI in `app/pages/index.vue`
6. Add composables for file handling and WASM communication
