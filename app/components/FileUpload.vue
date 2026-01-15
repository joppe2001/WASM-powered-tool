<template>
    <UFileUpload
        v-slot="{ open, dragging }"
        v-model="files"
        accept="image/*"
        :multiple="false"
        :preview="false"
        @change="handleFile"
    >
        <div class="dropzone" :class="{ dragging }" @click="open()">
            <div class="ascii-art">
                <pre>
  +-------------+
  |    IMAGE    |
  |   [?.png]   |
  +-------------+
                </pre>
            </div>
            <div class="hint">
                <span class="muted">// </span>
                <span class="text">drag & drop or click to select</span>
            </div>
            <div class="formats">
                <span class="muted">// supported: </span>
                <span class="keyword">png</span>
                <span class="muted"> | </span>
                <span class="keyword">jpg</span>
                <span class="muted"> | </span>
                <span class="keyword">webp</span>
            </div>
        </div>
    </UFileUpload>
</template>

<script setup lang="ts">
const files = ref<File | null>(null);

const emit = defineEmits<{
    file: [file: File];
}>();

function handleFile(event: Event) {
    if (files.value) {
        emit("file", files.value);
    }
}
</script>

<style scoped>
.dropzone {
    border: 1px dashed #333;
    border-radius: 4px;
    padding: 1.5rem;
    text-align: center;
    cursor: pointer;
    transition: all 0.2s ease;
    background: #141414;
    margin: 0.5rem 0;
}

.dropzone:hover {
    border-color: #28ca41;
    background: #1a1a1a;
}

.dropzone.dragging {
    border-color: #28ca41;
    background: #0f1f0f;
}

.ascii-art {
    color: #525252;
    font-size: 11px;
    line-height: 1.2;
}

.ascii-art pre {
    margin: 0;
}

.dropzone:hover .ascii-art,
.dropzone.dragging .ascii-art {
    color: #28ca41;
}

.hint, .formats {
    font-size: 12px;
    margin-top: 0.25rem;
}

.muted {
    color: #525252;
}

.text {
    color: #a1a1aa;
}

.keyword {
    color: #f59e0b;
}
</style>
