# Public WASM

Static WASM files served directly by the browser.

## Why here?

Files in `/public` are served as-is at the root URL.
Place your compiled `.wasm` files here if you want to load them via fetch.

```
public/wasm/
  module.wasm    # Your compiled WebAssembly binary
```

## Alternative: Build folder

You can also keep WASM in `/wasm/build/` and import it directly.
This folder is useful when you want to:

- Serve pre-built WASM files
- Load WASM via `fetch('/wasm/module.wasm')`
- Cache WASM files separately from JS

## Loading from public

```typescript
// In your worker or composable
const response = await fetch('/wasm/module.wasm');
const bytes = await response.arrayBuffer();
const { instance } = await WebAssembly.instantiate(bytes, imports);
```

## Learning Resources

1. **Nuxt Public Directory**
   - https://nuxt.com/docs/guide/directory-structure/public

2. **WebAssembly.instantiate**
   - https://developer.mozilla.org/en-US/docs/WebAssembly/JavaScript_interface/instantiate_static
