<template>
    <div class="app">
        <header class="header">
            <div class="header-content">
                <NuxtLink to="/" class="logo">
                    <span class="bracket">{</span>
                    <span class="logo-text">wasm</span>
                    <span class="bracket">}</span>
                </NuxtLink>
                <nav class="nav">
                    <NuxtLink to="/process/image" class="nav-link">
                        <span class="muted">//</span> image
                    </NuxtLink>
                    <span class="nav-link disabled">
                        <span class="muted">//</span> audio
                    </span>
                    <span class="nav-link disabled">
                        <span class="muted">//</span> video
                    </span>
                    <a href="https://github.com" target="_blank" class="nav-link">
                        <span class="muted">//</span> source
                    </a>
                </nav>
            </div>
        </header>

        <main class="main">
            <NuxtPage />
        </main>

        <footer class="footer">
            <div class="footer-content">
                <div class="footer-left">
                    <span class="muted">/*</span>
                    <span class="text">built with C++ & WebAssembly</span>
                    <span class="muted">*/</span>
                </div>
                <div class="footer-right">
                    <span class="muted">v1.0.0</span>
                    <span class="separator">|</span>
                    <span class="muted">emcc 4.0.23</span>
                </div>
            </div>
        </footer>
    </div>
</template>

<style>
/* Global reset & base */
*, *::before, *::after {
    box-sizing: border-box;
    margin: 0;
    padding: 0;
}

html, body {
    background: #0a0a0a;
    color: #a1a1aa;
    font-family: "JetBrains Mono", "Fira Code", "SF Mono", Consolas, monospace;
    font-size: 14px;
    line-height: 1.6;
    min-height: 100vh;
}

::selection {
    background: #28ca41;
    color: #0a0a0a;
}

a {
    color: inherit;
    text-decoration: none;
}
</style>

<style scoped>
.app {
    min-height: 100vh;
    display: flex;
    flex-direction: column;
    background: 
        radial-gradient(ellipse at top, #0f1a0f 0%, transparent 50%),
        linear-gradient(180deg, #0a0a0a 0%, #0d0d0d 100%);
}

/* Header */
.header {
    border-bottom: 1px solid #1a1a1a;
    padding: 1rem 0;
    background: rgba(10, 10, 10, 0.8);
    backdrop-filter: blur(10px);
    position: sticky;
    top: 0;
    z-index: 100;
}

.header-content {
    max-width: 900px;
    margin: 0 auto;
    padding: 0 1.5rem;
    display: flex;
    justify-content: space-between;
    align-items: center;
}

.logo {
    font-size: 1.25rem;
    font-weight: 600;
}

.bracket {
    color: #28ca41;
}

.logo-text {
    color: #e4e4e7;
    margin: 0 0.25rem;
}

.nav {
    display: flex;
    gap: 1.5rem;
}

.nav-link {
    font-size: 0.8rem;
    color: #525252;
    transition: color 0.2s;
}

.nav-link:hover:not(.disabled) {
    color: #28ca41;
}

.nav-link.disabled {
    opacity: 0.3;
    cursor: not-allowed;
}

.nav-link .muted {
    color: #333;
    margin-right: 0.25rem;
}

.logo {
    text-decoration: none;
}

/* Main */
.main {
    flex: 1;
    padding: 2rem 1rem;
}

/* Footer */
.footer {
    border-top: 1px solid #1a1a1a;
    padding: 1rem 0;
    margin-top: auto;
}

.footer-content {
    max-width: 900px;
    margin: 0 auto;
    padding: 0 1.5rem;
    display: flex;
    justify-content: space-between;
    align-items: center;
    font-size: 0.75rem;
}

.footer-left .muted {
    color: #333;
}

.footer-left .text {
    color: #525252;
    margin: 0 0.5rem;
}

.footer-right {
    color: #333;
}

.separator {
    margin: 0 0.5rem;
    color: #262626;
}
</style>
