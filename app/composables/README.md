# Composables

Reusable Vue composition functions. Nuxt auto-imports these.

## Structure

```
composables/
  useWasm.ts       # Load and interact with WASM module
  useFileHandler.ts # Read files as ArrayBuffer
  useDownload.ts    # Trigger file downloads
```

## Example: useWasm

```typescript
// useWasm.ts
export function useWasm() {
  const isLoading = ref(true);
  const isReady = ref(false);
  const error = ref<string | null>(null);

  let worker: Worker | null = null;
  let resolvers: Map<string, (value: any) => void> = new Map();

  onMounted(() => {
    worker = new Worker(
      new URL('../workers/wasm.worker.ts', import.meta.url),
      { type: 'module' }
    );

    worker.onmessage = (event) => {
      const { type, payload, id } = event.data;
      
      if (type === 'ready') {
        isLoading.value = false;
        isReady.value = true;
      }
      
      if (type === 'result' && resolvers.has(id)) {
        resolvers.get(id)!(payload);
        resolvers.delete(id);
      }
    };

    worker.postMessage({ type: 'init' });
  });

  onUnmounted(() => {
    worker?.terminate();
  });

  async function process(data: ArrayBuffer): Promise<ArrayBuffer> {
    const id = crypto.randomUUID();
    
    return new Promise((resolve) => {
      resolvers.set(id, resolve);
      worker?.postMessage({ type: 'process', payload: data, id });
    });
  }

  return { isLoading, isReady, error, process };
}
```

## Example: useFileHandler

```typescript
// useFileHandler.ts
export function useFileHandler() {
  async function readAsArrayBuffer(file: File): Promise<ArrayBuffer> {
    return new Promise((resolve, reject) => {
      const reader = new FileReader();
      reader.onload = () => resolve(reader.result as ArrayBuffer);
      reader.onerror = () => reject(reader.error);
      reader.readAsArrayBuffer(file);
    });
  }

  async function readAsDataURL(file: File): Promise<string> {
    return new Promise((resolve, reject) => {
      const reader = new FileReader();
      reader.onload = () => resolve(reader.result as string);
      reader.onerror = () => reject(reader.error);
      reader.readAsDataURL(file);
    });
  }

  return { readAsArrayBuffer, readAsDataURL };
}
```

## Learning Resources

1. **Nuxt Composables**
   - https://nuxt.com/docs/guide/directory-structure/composables

2. **Vue Composables**
   - https://vuejs.org/guide/reusability/composables.html
