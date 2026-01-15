# Learning: Connecting the UI to WASM

Your C++ works. Now let's get images flowing through it.

---

## The Pipeline

```
┌─────────────┐     ┌─────────────┐     ┌─────────────┐
│  User drops │ ──▶ │   Canvas    │ ──▶ │    WASM     │
│    image    │     │  extracts   │     │  processes  │
│             │     │   pixels    │     │   pixels    │
└─────────────┘     └─────────────┘     └─────────────┘
                                               │
                                               ▼
┌─────────────┐     ┌─────────────┐     ┌─────────────┐
│  User sees  │ ◀── │   Canvas    │ ◀── │   Result    │
│   result    │     │   renders   │     │   pixels    │
└─────────────┘     └─────────────┘     └─────────────┘
```

---

## Challenge 1: Load an Image

When a user drops or selects an image, you need to load it into JavaScript.

**Think about:**
- How do you get the file from a drop event or input?
- How do you convert a File to something you can draw?

**Hints:**
- `FileReader` can read files as data URLs
- `new Image()` can load from a data URL
- Images have an `onload` event

**Pseudocode:**
```
on file drop:
    reader = new FileReader()
    reader.readAsDataURL(file)
    reader.onload = () => {
        img = new Image()
        img.src = reader.result
        img.onload = () => {
            // now you have a loaded image
        }
    }
```

**Your task:** Create a composable `useImageLoader` that takes a File and returns a loaded Image.

---

## Challenge 2: Extract Pixels with Canvas

Canvas is the bridge between images and raw pixel data.

**Think about:**
- How do you create a canvas element?
- How do you draw an image onto it?
- How do you get the pixel data out?

**Key APIs:**
```javascript
const canvas = document.createElement('canvas');
const ctx = canvas.getContext('2d');
ctx.drawImage(img, x, y);
const imageData = ctx.getImageData(x, y, width, height);
// imageData.data = Uint8ClampedArray [R,G,B,A,R,G,B,A,...]
```

**Your task:** Create a function that takes an Image and returns its pixel data + dimensions.

---

## Challenge 3: Convert Between JS and WASM Formats

Your WASM expects `VectorRGBA`, but Canvas gives you a flat `Uint8ClampedArray`.

**The formats:**
```
Canvas:  [R, G, B, A, R, G, B, A, ...]  (flat array)
WASM:    [{r,g,b,a}, {r,g,b,a}, ...]    (vector of structs)
```

**Think about:**
- How do you loop through the flat array 4 items at a time?
- How do you push RGBA objects into a VectorRGBA?
- How do you convert back after processing?

**Pseudocode (JS to WASM):**
```
input = new wasm.VectorRGBA()
for i from 0 to pixels.length, step 4:
    input.push_back({
        r: pixels[i],
        g: pixels[i+1],
        b: pixels[i+2],
        a: pixels[i+3]
    })
```

**Pseudocode (WASM to JS):**
```
output = new Uint8ClampedArray(result.size() * 4)
for i from 0 to result.size():
    pixel = result.get(i)
    output[i*4] = pixel.r
    output[i*4+1] = pixel.g
    output[i*4+2] = pixel.b
    output[i*4+3] = pixel.a
```

**Your task:** Write two functions: `pixelsToVector(pixels, wasm)` and `vectorToPixels(vector)`.

---

## Challenge 4: Render the Result

Now put the processed pixels back on a canvas and show it.

**Key APIs:**
```javascript
const newImageData = new ImageData(pixels, width, height);
ctx.putImageData(newImageData, 0, 0);
```

**Think about:**
- Where do you render? A visible canvas in your component?
- How do you size the canvas to match the image?

**Your task:** Display both original and processed images side by side.

---

## Challenge 5: Download the Result

Let the user save their processed image.

**Think about:**
- Canvas has a `toDataURL()` method
- You can create an `<a>` element with `download` attribute
- Clicking it programmatically triggers a download

**Pseudocode:**
```
dataUrl = canvas.toDataURL('image/png')
link = document.createElement('a')
link.download = 'processed.png'
link.href = dataUrl
link.click()
```

**Your task:** Add a download button that saves the processed image.

---

## Suggested File Structure

```
app/
  composables/
    useWasm.ts          # Load WASM module
    useImageLoader.ts   # File → Image
    useImageProcessor.ts # Image → pixels → WASM → pixels → Image
  components/
    ImageDropzone.vue   # Drag and drop area
    ImagePreview.vue    # Display before/after
    DownloadButton.vue  # Save result
  pages/
    index.vue           # Main page, wires everything together
```

---

## Loading WASM in Nuxt

WASM should be loaded once when the app starts. Use a composable:

```typescript
// composables/useWasm.ts
export const useWasm = () => {
    // Think about:
    // - How do you store the module so it's shared?
    // - How do you handle the loading state?
    // - What if someone calls this before it's ready?
    
    // Hints:
    // - useState() for shared state in Nuxt
    // - async/await for loading
    // - Return { wasm, isReady, error }
}
```

---

## Testing Incrementally

Don't build everything at once. Test each step:

1. Can you load an image and display it on a canvas?
2. Can you extract pixels and log them?
3. Can you pass pixels to WASM and get results back?
4. Can you render the processed pixels?
5. Can you download the result?

---

## Common Gotchas

**CORS issues with images:**
If loading external images, you may hit CORS. For local files (dropped/selected), you're fine.

**Memory cleanup:**
Always call `.delete()` on WASM vectors when done:
```javascript
input.delete();
result.delete();
```

**Canvas sizing:**
Set canvas width/height attributes, not just CSS:
```javascript
canvas.width = img.width;   // actual pixel size
canvas.height = img.height;
```

---

## Resources

- FileReader: https://developer.mozilla.org/en-US/docs/Web/API/FileReader
- Canvas: https://developer.mozilla.org/en-US/docs/Web/API/Canvas_API
- ImageData: https://developer.mozilla.org/en-US/docs/Web/API/ImageData
- Nuxt useState: https://nuxt.com/docs/api/composables/use-state
- Vue refs: https://vuejs.org/guide/essentials/template-refs.html

---

## When You're Stuck

1. Console.log everything - check what you actually have at each step
2. Test with a tiny image first (like 2x2 pixels)
3. Check the browser Network tab - is the WASM loading?
4. Check for memory leaks - are you cleaning up vectors?

Start with Challenge 1. Get a dropped image displaying before you touch WASM.
