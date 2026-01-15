# Components

Vue components for your UI. Nuxt auto-imports these.

## Structure

```
components/
  FileDropzone.vue     # Drag-and-drop file upload area
  ProcessingStatus.vue # Loading/progress indicator
  ResultPreview.vue    # Display processed output
  DownloadButton.vue   # Export/download results
```

## Example: File Dropzone

```vue
<template>
  <div
    class="dropzone"
    :class="{ 'drag-over': isDragging }"
    @drop.prevent="handleDrop"
    @dragover.prevent="isDragging = true"
    @dragleave="isDragging = false"
  >
    <p>Drop your file here or click to select</p>
    <input type="file" @change="handleFileSelect" :accept="accept" />
  </div>
</template>

<script setup lang="ts">
const props = defineProps<{
  accept?: string
}>();

const emit = defineEmits<{
  file: [file: File]
}>();

const isDragging = ref(false);

function handleDrop(e: DragEvent) {
  isDragging.value = false;
  const file = e.dataTransfer?.files[0];
  if (file) emit('file', file);
}

function handleFileSelect(e: Event) {
  const file = (e.target as HTMLInputElement).files?.[0];
  if (file) emit('file', file);
}
</script>
```

## Learning Resources

1. **Nuxt Components**
   - https://nuxt.com/docs/guide/directory-structure/components

2. **Vue 3 Composition API**
   - https://vuejs.org/guide/essentials/component-basics.html

3. **File API**
   - https://developer.mozilla.org/en-US/docs/Web/API/File_API
