# Pages

File-based routing. Each `.vue` file becomes a route.

## Structure

```
pages/
  index.vue      # / (home page - main tool UI)
  about.vue      # /about (optional)
```

## Example: Main Tool Page

```vue
<!-- index.vue -->
<template>
  <div class="container">
    <h1>WASM Image Tool</h1>
    
    <FileDropzone 
      accept="image/*" 
      @file="handleFile" 
    />
    
    <ProcessingStatus 
      v-if="isProcessing" 
      :progress="progress" 
    />
    
    <ResultPreview 
      v-if="result" 
      :data="result" 
    />
    
    <DownloadButton 
      v-if="result" 
      :data="result" 
      filename="processed.png" 
    />
  </div>
</template>

<script setup lang="ts">
const { isReady, process } = useWasm();
const { readAsArrayBuffer } = useFileHandler();

const isProcessing = ref(false);
const progress = ref(0);
const result = ref<ArrayBuffer | null>(null);

async function handleFile(file: File) {
  if (!isReady.value) return;
  
  isProcessing.value = true;
  progress.value = 0;
  
  try {
    const buffer = await readAsArrayBuffer(file);
    progress.value = 50;
    
    result.value = await process(buffer);
    progress.value = 100;
  } finally {
    isProcessing.value = false;
  }
}
</script>
```

## Learning Resources

1. **Nuxt Pages**
   - https://nuxt.com/docs/guide/directory-structure/pages

2. **Nuxt Routing**
   - https://nuxt.com/docs/getting-started/routing
