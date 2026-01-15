# Learning: From Numbers to Pixels

You just doubled numbers. Now let's think about how to apply the same logic to images.

---

## What is an image, really?

An image is just an array of numbers. Each pixel has 4 values:

```
[R, G, B, A, R, G, B, A, R, G, B, A, ...]
 └─pixel 1─┘  └─pixel 2─┘  └─pixel 3─┘
```

- **R** = Red (0-255)
- **G** = Green (0-255)
- **B** = Blue (0-255)
- **A** = Alpha/transparency (0-255)

A 2x2 image = 4 pixels = 16 numbers.

---

## Your current function

```cpp
std::vector<int> doubleNumbers(std::vector<int> numbers) {
    for (int& n : numbers) {
        n *= 2;
    }
    return numbers;
}
```

You loop through numbers and transform each one.

---

## Challenge 1: Grayscale

To make a pixel grayscale, you average its R, G, B values and set all three to that average.

**Think about:**
- How do you access every 4th element? (hint: loop by 4, not by 1)
- How do you calculate an average of 3 numbers?
- What should happen to the Alpha value?

**Pseudocode:**
```
for each pixel:
    gray = average of R, G, B
    set R = gray
    set G = gray
    set B = gray
    keep A unchanged
```

**Your task:** Write a function `grayscale(std::vector<uint8_t> pixels)` that returns grayscale pixels.

*Hint: `uint8_t` is better than `int` for pixel values (0-255 range)*

---

## Challenge 2: Invert Colors

Inverting means: `new_value = 255 - old_value`

White becomes black, red becomes cyan, etc.

**Your task:** Write `invert(std::vector<uint8_t> pixels)`

*Hint: Should you invert the Alpha channel?*

---

## Challenge 3: Brightness

To brighten, add a value to R, G, B. To darken, subtract.

**Think about:**
- What happens if R is 250 and you add 20? (hint: clamping)
- How do you prevent values going below 0 or above 255?

**Your task:** Write `brightness(std::vector<uint8_t> pixels, int amount)`

*Hint: Look up `std::clamp` or write your own*

---

## Exposing to JavaScript

Remember to update your embind bindings:

```cpp
EMSCRIPTEN_BINDINGS(module) {
    emscripten::register_vector<uint8_t>("Uint8Vector");
    emscripten::function("grayscale", &grayscale);
    // add more functions here
}
```

---

## Testing in browser

JavaScript gives you image pixels via Canvas:

```javascript
// Get pixels from an image
ctx.drawImage(img, 0, 0);
const imageData = ctx.getImageData(0, 0, width, height);
const pixels = imageData.data; // Uint8ClampedArray [R,G,B,A,R,G,B,A,...]
```

Figure out how to:
1. Convert this to a format your WASM function accepts
2. Call your function
3. Put the result back on the canvas

---

## Resources

- C++ vectors: https://cplusplus.com/reference/vector/vector/
- uint8_t type: https://en.cppreference.com/w/cpp/types/integer
- Canvas ImageData: https://developer.mozilla.org/en-US/docs/Web/API/ImageData

---

## When you're stuck

1. Print values to understand what you're working with
2. Test with a tiny "image" (4 pixels = 16 numbers) before real images
3. Check if your loop indices are correct (off-by-one errors are common)

Good luck. Start with grayscale - it's the foundation for everything else.
