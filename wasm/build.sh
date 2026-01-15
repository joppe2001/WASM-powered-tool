#!/bin/bash

# WASM Build Script
# Usage: ./build.sh

set -e  # Exit on error

echo "╔════════════════════════════════════╗"
echo "║     WASM Image Processor Build     ║"
echo "╚════════════════════════════════════╝"
echo ""

# Source files - add new .cpp files here
SOURCES=(
    "src/main.cpp"
    "src/greyscaleImage.cpp"
    "src/invertColors.cpp"
    "src/brightness.cpp"
    "src/blurImage.cpp"        # uncomment when ready
    # "src/contrast.cpp"    # uncomment when ready
)

# Output
OUTPUT="build/module.js"
PUBLIC_DIR="../public/wasm"

echo "[1/3] Compiling..."
echo "      Sources: ${SOURCES[@]}"
echo ""

emcc ${SOURCES[@]} -o $OUTPUT \
    -lembind \
    -s WASM=1 \
    -s MODULARIZE=1 \
    -s ALLOW_MEMORY_GROWTH=1 \
    -s EXPORT_NAME='Module' \
    -s ENVIRONMENT='web' \
    -O3

echo "[2/3] Copying to public folder..."
cp build/module.js $PUBLIC_DIR/
cp build/module.wasm $PUBLIC_DIR/

echo "[3/3] Done!"
echo ""
echo "╔════════════════════════════════════╗"
echo "║  Build complete!                   ║"
echo "║  Output: public/wasm/module.js     ║"
echo "╚════════════════════════════════════╝"
