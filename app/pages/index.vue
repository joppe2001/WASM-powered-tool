<template>
    <div class="home">
        <div class="hero">
            <pre class="ascii-logo">
 __      __  _    ____  __  __
 \ \    / / / \  / ___||  \/  |
  \ \/\/ / / _ \ \___ \| |\/| |
   \_/\_/ /_/ \_\|____/|_|  |_|
            </pre>
            <h1 class="tagline">
                <span class="muted">// </span>
                native-speed processing in the browser
            </h1>
        </div>

        <div class="categories">
            <NuxtLink to="/process/image" class="category-card">
                <div class="card-icon">
                    <pre>
+-------+
| IMAGE |
| .png  |
+-------+
                    </pre>
                </div>
                <div class="card-info">
                    <h2>image.process()</h2>
                    <p class="muted">// greyscale, invert, brightness, blur</p>
                    <div class="card-status">
                        <span class="dot ready"></span>
                        <span>4 functions available</span>
                    </div>
                </div>
            </NuxtLink>

            <div class="category-card disabled">
                <div class="card-icon">
                    <pre>
+-------+
| AUDIO |
| .wav  |
+-------+
                    </pre>
                </div>
                <div class="card-info">
                    <h2>audio.process()</h2>
                    <p class="muted">// waveform, normalize, reverse</p>
                    <div class="card-status">
                        <span class="dot"></span>
                        <span>coming soon</span>
                    </div>
                </div>
            </div>

            <div class="category-card disabled">
                <div class="card-icon">
                    <pre>
+-------+
| VIDEO |
| .mp4  |
+-------+
                    </pre>
                </div>
                <div class="card-info">
                    <h2>video.process()</h2>
                    <p class="muted">// extract frames, convert, compress</p>
                    <div class="card-status">
                        <span class="dot"></span>
                        <span>coming soon</span>
                    </div>
                </div>
            </div>

            <div class="category-card disabled">
                <div class="card-icon">
                    <pre>
+-------+
|  PDF  |
| .pdf  |
+-------+
                    </pre>
                </div>
                <div class="card-info">
                    <h2>pdf.process()</h2>
                    <p class="muted">// merge, split, compress, extract</p>
                    <div class="card-status">
                        <span class="dot"></span>
                        <span>coming soon</span>
                    </div>
                </div>
            </div>
        </div>

        <div class="info-section">
            <div class="info-card">
                <h3>
                    <span class="muted">/*</span> how it works
                    <span class="muted">*/</span>
                </h3>
                <div class="code-block">
                    <div class="line">
                        <span class="line-num">1</span
                        ><span class="keyword">const</span> wasm =
                        <span class="keyword">await</span>
                        <span class="func">loadModule</span>();
                    </div>
                    <div class="line">
                        <span class="line-num">2</span
                        ><span class="keyword">const</span> input =
                        <span class="func">readFile</span>(file);
                    </div>
                    <div class="line">
                        <span class="line-num">3</span
                        ><span class="keyword">const</span> output = wasm.<span
                            class="func"
                            >process</span
                        >(input);
                    </div>
                    <div class="line">
                        <span class="line-num">4</span
                        ><span class="func">download</span>(output);
                    </div>
                </div>
            </div>

            <div class="info-card">
                <h3>
                    <span class="muted">/*</span> features
                    <span class="muted">*/</span>
                </h3>
                <ul class="feature-list">
                    <li>
                        <span class="bullet">&gt;</span> 100% client-side
                        processing
                    </li>
                    <li>
                        <span class="bullet">&gt;</span> files never leave your
                        browser
                    </li>
                    <li>
                        <span class="bullet">&gt;</span> C++ compiled to
                        WebAssembly
                    </li>
                    <li>
                        <span class="bullet">&gt;</span> near-native performance
                    </li>
                </ul>
            </div>
        </div>
    </div>
</template>

<style scoped>
.home {
    max-width: 900px;
    margin: 0 auto;
}

.hero {
    text-align: center;
    margin-bottom: 3rem;
}

.ascii-logo {
    color: #28ca41;
    font-size: 0.7rem;
    line-height: 1.2;
    margin-bottom: 1rem;
}

.tagline {
    font-size: 1rem;
    font-weight: 400;
    color: #a1a1aa;
}

.muted {
    color: #525252;
}

.categories {
    display: grid;
    grid-template-columns: repeat(2, 1fr);
    gap: 1rem;
    margin-bottom: 3rem;
}

.category-card {
    background: #0d0d0d;
    border: 1px solid #262626;
    border-radius: 8px;
    padding: 1.5rem;
    display: flex;
    gap: 1rem;
    transition: all 0.2s;
    cursor: pointer;
    text-decoration: none;
    color: inherit;
}

.category-card:hover:not(.disabled) {
    border-color: #28ca41;
    background: #0f1a0f;
}

.category-card.disabled {
    opacity: 0.4;
    cursor: not-allowed;
}

.card-icon pre {
    color: #525252;
    font-size: 10px;
    line-height: 1.2;
    margin: 0;
}

.category-card:hover:not(.disabled) .card-icon pre {
    color: #28ca41;
}

.card-info {
    flex: 1;
}

.card-info h2 {
    font-size: 1rem;
    font-weight: 500;
    color: #e4e4e7;
    margin-bottom: 0.25rem;
}

.card-info p {
    font-size: 0.75rem;
    margin-bottom: 0.75rem;
}

.card-status {
    display: flex;
    align-items: center;
    gap: 0.5rem;
    font-size: 0.7rem;
    color: #525252;
}

.dot {
    width: 6px;
    height: 6px;
    border-radius: 50%;
    background: #525252;
}

.dot.ready {
    background: #28ca41;
}

.info-section {
    display: grid;
    grid-template-columns: repeat(2, 1fr);
    gap: 1rem;
}

.info-card {
    background: #0d0d0d;
    border: 1px solid #262626;
    border-radius: 8px;
    padding: 1.5rem;
}

.info-card h3 {
    font-size: 0.85rem;
    font-weight: 400;
    margin-bottom: 1rem;
    color: #a1a1aa;
}

.code-block {
    font-size: 0.75rem;
}

.line {
    display: flex;
    gap: 1rem;
    padding: 0.25rem 0;
}

.line-num {
    color: #333;
    user-select: none;
    width: 1rem;
}

.keyword {
    color: #c084fc;
}

.func {
    color: #60a5fa;
}

.feature-list {
    list-style: none;
    font-size: 0.8rem;
}

.feature-list li {
    padding: 0.35rem 0;
    color: #a1a1aa;
}

.bullet {
    color: #28ca41;
    margin-right: 0.5rem;
}

@media (max-width: 640px) {
    .categories,
    .info-section {
        grid-template-columns: 1fr;
    }
}
</style>
