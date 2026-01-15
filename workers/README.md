# Workers - Web Workers for WASM

This folder contains Web Worker scripts that run your WASM code off the main thread.

## Why Web Workers?

WASM operations can be CPU-intensive. Running them on the main thread blocks the UI.
Web Workers run in a separate thread, keeping your app responsive.

## Structure

```
workers/
  wasm.worker.ts    # Main worker that loads and runs WASM
```

## Example Worker

```typescript
// wasm.worker.ts

// Load the WASM module
let wasmModule: any = null;

self.onmessage = async (event) => {
  const { type, payload } = event.data;

  switch (type) {
    case 'init':
      // Load WASM module once
      const Module = await import('../wasm/build/module.js');
      wasmModule = await Module.default();
      self.postMessage({ type: 'ready' });
      break;

    case 'process':
      // Run your WASM function
      const result = wasmModule.grayscale(payload.pixels, payload.width, payload.height);
      self.postMessage({ type: 'result', payload: result });
      break;
  }
};
```

## Using the Worker in Vue

```typescript
// composables/useWasm.ts
export function useWasm() {
  const worker = new Worker(new URL('../workers/wasm.worker.ts', import.meta.url), {
    type: 'module'
  });

  const isReady = ref(false);

  worker.onmessage = (event) => {
    if (event.data.type === 'ready') {
      isReady.value = true;
    }
  };

  // Initialize
  worker.postMessage({ type: 'init' });

  return { worker, isReady };
}
```

## Learning Resources

1. **Web Workers API**
   - https://developer.mozilla.org/en-US/docs/Web/API/Web_Workers_API

2. **Comlink** (simplifies worker communication)
   - https://github.com/GoogleChromeLabs/comlink

3. **Nuxt + Web Workers**
   - https://nuxt.com/docs/guide/directory-structure/public

4. **Using WASM in Workers**
   - https://developer.mozilla.org/en-US/docs/WebAssembly/Loading_and_running
