<template>
    <div class="terminal">
        <!-- Window chrome -->
        <div class="window-bar">
            <div class="window-buttons">
                <NuxtLink to="/" class="btn close"></NuxtLink>
                <span class="btn minimize"></span>
                <span class="btn maximize"></span>
            </div>
            <span class="window-title">image-processor</span>
            <div class="window-status">
                <span class="dot" :class="{ ready: wasmReady }"></span>
            </div>
        </div>

        <!-- Terminal content -->
        <div class="terminal-body">
            <!-- Init log -->
            <div class="log-line">
                <span class="prompt">$</span>
                <span class="cmd">./image-processor --init</span>
            </div>
            <div class="log-line output">
                <span class="success" v-if="wasmReady"
                    >module loaded successfully</span
                >
                <span class="loading" v-else>loading wasm module...</span>
            </div>

            <!-- Function selector as code -->
            <div class="log-line" style="margin-top: 1rem">
                <span class="prompt">$</span>
                <span class="cmd">processor.setFunction(</span>
                <select v-model="selectedFunction" class="inline-select">
                    <option
                        v-for="fn in availableFunctions"
                        :key="fn.name"
                        :value="fn.name"
                    >
                        "{{ fn.name }}"
                    </option>
                </select>
                <!-- Parameter controls -->
                <div
                    v-if="chosenFunction?.params.length"
                    class="params-section"
                >
                    <div class="log-line">
                        <span class="prompt">$</span>
                        <span class="cmd">processor.setParams({</span>
                    </div>
                    <div
                        v-for="param in chosenFunction.params"
                        :key="param.name"
                        class="param-row"
                    >
                        <span class="param-name">{{ param.name }}:</span>
                        <input
                            type="range"
                            class="param-slider"
                            :min="param.min"
                            :max="param.max"
                            v-model.number="paramValues[param.name]"
                            @input="onParamChange"
                        />
                        <span class="param-value">{{
                            paramValues[param.name] ?? param.default
                        }}</span>
                    </div>
                    <div class="log-line">
                        <span class="cmd">})</span>
                    </div>
                </div>

                <span class="cmd">)</span>
            </div>
            <div class="log-line output">
                <span class="muted">// {{ currentFunctionDescription }}</span>
            </div>

            <!-- File upload area -->
            <div class="log-line" style="margin-top: 1rem">
                <span class="prompt">$</span>
                <span class="cmd">processor.loadImage()</span>
            </div>

            <FileUpload @file="handleFile" />

            <!-- Results -->
            <template v-if="originalImage">
                <div class="log-line" style="margin-top: 1rem">
                    <span class="prompt">$</span>
                    <span class="cmd">processor.run()</span>
                </div>
                <div class="log-line output">
                    <span class="muted">// processing {{ imageInfo }}</span>
                </div>

                <div class="image-grid">
                    <div class="image-panel">
                        <div class="panel-header">
                            <span class="muted">/* input */</span>
                        </div>
                        <img :src="originalImage" alt="input" />
                    </div>
                    <div class="image-panel">
                        <div class="panel-header">
                            <span class="muted">/* output */</span>
                        </div>
                        <canvas ref="outputCanvas"></canvas>
                    </div>
                </div>

                <div class="log-line output success" v-if="processed">
                    done in {{ processingTime }}ms
                </div>

                <!-- Action buttons as commands -->
                <div class="action-row">
                    <button class="cmd-btn" @click="reprocess">
                        <span class="prompt">$</span> reprocess()
                    </button>
                    <button
                        class="cmd-btn"
                        @click="downloadResult"
                        :disabled="!processed"
                    >
                        <span class="prompt">$</span> download()
                    </button>
                </div>
            </template>

            <!-- Cursor -->
            <div class="log-line cursor-line">
                <span class="prompt">$</span>
                <span class="cursor">_</span>
            </div>
        </div>
    </div>
</template>

<script setup lang="ts">
let wasm: any = null;
const wasmReady = ref(false);
const originalImage = ref<string | null>(null);
const processed = ref(false);
const outputCanvas = ref<HTMLCanvasElement | null>(null);
const selectedFunction = ref("greyscaleImage");
const processingTime = ref(0);
const imageInfo = ref("");
const paramValues = ref<Record<string, number>>({});

const availableFunctions = [
    {
        name: "greyscaleImage",
        description: "converts RGB to luminance greyscale",
        params: [],
    },
    {
        name: "invertColors",
        description: "inverts each color channel (255 - value)",
        params: [],
    },
    {
        name: "brightness",
        description: "Increases or lowers the brightness of the pixels",
        params: [
            {
                name: "amount",
                type: "range",
                min: -255,
                max: 255,
                default: 0,
            },
        ],
    },
    {
        name: "blurImage",
        description: "Uses Gaussian blur to blur the image",
        params: [
            {
                name: "amount",
                type: "range",
                min: 0,
                max: 50,
                default: 0,
            },
        ],
    },
    {
        name: "boxBlurImage",
        description: "Uses box blur blur to blur the image",
        params: [
            {
                name: "amount",
                type: "range",
                min: 0,
                max: 50,
                default: 0,
            },
        ],
    },
    {
        name: "noiseGeneration",
        description: "Adds noise to the image",
        params: [
            {
                name: "amount",
                type: "range",
                min: 0,
                max: 200,
                default: 0,
            },
        ],
    },
];

const currentFunctionDescription = computed(() => {
    const fn = availableFunctions.find(
        (f) => f.name === selectedFunction.value,
    );
    return fn?.description || "";
});

// Reprocess when function changes
watch(selectedFunction, () => {
    // Set default param values
    const fn = availableFunctions.find(
        (f) => f.name === selectedFunction.value,
    );
    fn?.params.forEach((p) => {
        if (paramValues.value[p.name] === undefined) {
            paramValues.value[p.name] = p.default;
        }
    });

    if (originalImage.value) {
        reprocess();
    }
});

function onParamChange() {
    if (originalImage.value) {
        reprocess();
    }
}

const chosenFunction = computed(() =>
    availableFunctions.find((f) => f.name === selectedFunction.value),
);

async function loadWasm() {
    const script = document.createElement("script");
    script.src = "/wasm/module.js";
    document.head.appendChild(script);
    await new Promise((resolve) => (script.onload = resolve));
    // @ts-ignore
    return await Module();
}

onMounted(async () => {
    wasm = await loadWasm();
    wasmReady.value = true;
});

function processImage(img: HTMLImageElement) {
    const canvas = outputCanvas.value;
    if (!canvas || !wasm) return;

    const start = performance.now();

    canvas.width = img.width;
    canvas.height = img.height;
    imageInfo.value = `${img.width}x${img.height}px`;

    const ctx = canvas.getContext("2d")!;
    ctx.drawImage(img, 0, 0);

    const imageData = ctx.getImageData(0, 0, img.width, img.height);
    const pixels = imageData.data;

    const input = new wasm.VectorRGBA();
    for (let i = 0; i < pixels.length; i += 4) {
        input.push_back({
            r: pixels[i],
            g: pixels[i + 1],
            b: pixels[i + 2],
            a: pixels[i + 3],
        });
    }

    const args =
        chosenFunction.value?.params.map((p) => paramValues.value[p.name]) ||
        [];
    let result;
    if (
        selectedFunction.value === "blurImage" ||
        selectedFunction.value === "boxBlurImage"
    ) {
        result = wasm[selectedFunction.value](
            input,
            canvas.width,
            canvas.height,
            ...args,
        );
    } else {
        result = wasm[selectedFunction.value](input, ...args);
    }

    const output = new Uint8ClampedArray(result.size() * 4);
    for (let i = 0; i < result.size(); i++) {
        const pixel = result.get(i);
        output[i * 4] = pixel.r;
        output[i * 4 + 1] = pixel.g;
        output[i * 4 + 2] = pixel.b;
        output[i * 4 + 3] = pixel.a;
    }

    ctx.putImageData(new ImageData(output, img.width, img.height), 0, 0);
    input.delete();
    result.delete();

    processingTime.value = Math.round(performance.now() - start);
    processed.value = true;
}

function handleFile(file: File) {
    if (!wasm) return;
    const reader = new FileReader();

    reader.onload = () => {
        originalImage.value = reader.result as string;
        nextTick(() => {
            const img = new Image();
            img.onload = () => processImage(img);
            img.src = originalImage.value!;
        });
    };
    reader.readAsDataURL(file);
}

function reprocess() {
    if (!originalImage.value) return;
    processed.value = false;
    const img = new Image();
    img.onload = () => processImage(img);
    img.src = originalImage.value;
}

function downloadResult() {
    const canvas = outputCanvas.value;
    if (!canvas) return;
    const link = document.createElement("a");
    link.download = `${selectedFunction.value}-output.png`;
    link.href = canvas.toDataURL("image/png");
    link.click();
}
</script>

<style scoped>
.terminal {
    max-width: 900px;
    margin: 0 auto;
    background: #0d0d0d;
    border-radius: 8px;
    border: 1px solid #262626;
    overflow: hidden;
    font-family: "JetBrains Mono", "Fira Code", "SF Mono", monospace;
    font-size: 13px;
}

.window-bar {
    display: flex;
    align-items: center;
    padding: 0.75rem 1rem;
    background: #1a1a1a;
    border-bottom: 1px solid #262626;
}

.window-buttons {
    display: flex;
    gap: 8px;
}

.window-buttons .btn {
    width: 12px;
    height: 12px;
    border-radius: 50%;
    display: block;
}

.btn.close {
    background: #ff5f57;
    cursor: pointer;
    transition: opacity 0.2s;
}

.btn.close:hover {
    opacity: 0.8;
}

.btn.minimize {
    background: #ffbd2e;
}
.btn.maximize {
    background: #28ca41;
}

.window-title {
    flex: 1;
    text-align: center;
    color: #666;
    font-size: 12px;
}

.window-status {
    display: flex;
    align-items: center;
}

.dot {
    width: 8px;
    height: 8px;
    border-radius: 50%;
    background: #ff5f57;
}

.dot.ready {
    background: #28ca41;
}

.terminal-body {
    padding: 1.5rem;
}

.log-line {
    display: flex;
    align-items: center;
    gap: 0.5rem;
    margin-bottom: 0.25rem;
    line-height: 1.6;
}

.log-line.output {
    padding-left: 1.25rem;
}

.prompt {
    color: #28ca41;
    font-weight: bold;
}

.cmd {
    color: #e4e4e7;
}

.success {
    color: #28ca41;
}

.loading {
    color: #ffbd2e;
}

.muted {
    color: #525252;
}

.inline-select {
    background: transparent;
    border: none;
    color: #f59e0b;
    font-family: inherit;
    font-size: inherit;
    cursor: pointer;
    outline: none;
    padding: 0;
}

.inline-select option {
    background: #1a1a1a;
    color: #f59e0b;
}

.params-section {
    margin: 0.75rem 0;
    padding-left: 1.25rem;
}

.param-row {
    display: flex;
    align-items: center;
    gap: 0.75rem;
    padding: 0.25rem 0;
    padding-left: 1rem;
}

.param-name {
    color: #60a5fa;
    min-width: 80px;
}

.param-slider {
    -webkit-appearance: none;
    appearance: none;
    width: 150px;
    height: 4px;
    background: #262626;
    border-radius: 2px;
    outline: none;
    cursor: pointer;
}

.param-slider::-webkit-slider-thumb {
    -webkit-appearance: none;
    appearance: none;
    width: 12px;
    height: 12px;
    background: #28ca41;
    border-radius: 50%;
    cursor: pointer;
    transition: transform 0.1s;
}

.param-slider::-webkit-slider-thumb:hover {
    transform: scale(1.2);
}

.param-slider::-moz-range-thumb {
    width: 12px;
    height: 12px;
    background: #28ca41;
    border-radius: 50%;
    border: none;
    cursor: pointer;
}

.param-value {
    color: #f59e0b;
    min-width: 40px;
    text-align: right;
    font-size: 12px;
}

.image-grid {
    display: grid;
    grid-template-columns: 1fr 1fr;
    gap: 1rem;
    margin: 1rem 0;
}

.image-panel {
    background: #141414;
    border: 1px solid #262626;
    border-radius: 4px;
    overflow: hidden;
}

.panel-header {
    padding: 0.5rem 0.75rem;
    border-bottom: 1px solid #262626;
    font-size: 11px;
}

.image-panel img,
.image-panel canvas {
    width: 100%;
    height: auto;
    display: block;
}

.action-row {
    display: flex;
    gap: 1rem;
    margin-top: 1rem;
}

.cmd-btn {
    background: #1a1a1a;
    border: 1px solid #262626;
    color: #a1a1aa;
    padding: 0.5rem 1rem;
    border-radius: 4px;
    font-family: inherit;
    font-size: 12px;
    cursor: pointer;
    transition: all 0.15s;
}

.cmd-btn:hover:not(:disabled) {
    border-color: #28ca41;
    color: #28ca41;
}

.cmd-btn:disabled {
    opacity: 0.3;
    cursor: not-allowed;
}

.cmd-btn .prompt {
    margin-right: 0.25rem;
}

.cursor-line {
    margin-top: 1rem;
}

.cursor {
    color: #28ca41;
    animation: blink 1s step-end infinite;
}

@keyframes blink {
    0%,
    100% {
        opacity: 1;
    }
    50% {
        opacity: 0;
    }
}
</style>
