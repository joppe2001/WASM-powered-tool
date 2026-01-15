#include <emscripten/bind.h>
#include "greyscaleImage.hpp"
#include "invertColors.hpp"
#include "brightness.hpp"
#include "blurImage.hpp"

EMSCRIPTEN_BINDINGS(module) {
    emscripten::value_object<RGBA>("RGBA")
        .field("r", &RGBA::r)
        .field("g", &RGBA::g)
        .field("b", &RGBA::b)
        .field("a", &RGBA::a);
    emscripten::register_vector<RGBA>("VectorRGBA");
    emscripten::function("greyscaleImage", &greyscaleImage);
    emscripten::function("invertColors", &invertColors);
    emscripten::function("brightness", &brightness);
    emscripten::function("blurImage", &blurImage);
}
