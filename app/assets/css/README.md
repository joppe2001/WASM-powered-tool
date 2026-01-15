# Assets - CSS

Global styles and CSS files.

## Structure

```
assets/css/
  main.css       # Global styles
  variables.css  # CSS custom properties
```

## Example: main.css

```css
/* main.css */
@import './variables.css';

* {
  box-sizing: border-box;
  margin: 0;
  padding: 0;
}

body {
  font-family: system-ui, -apple-system, sans-serif;
  background: var(--bg-color);
  color: var(--text-color);
  min-height: 100vh;
}

.container {
  max-width: 800px;
  margin: 0 auto;
  padding: 2rem;
}

.dropzone {
  border: 2px dashed var(--border-color);
  border-radius: 8px;
  padding: 3rem;
  text-align: center;
  cursor: pointer;
  transition: border-color 0.2s;
}

.dropzone:hover,
.dropzone.drag-over {
  border-color: var(--accent-color);
}
```

## Example: variables.css

```css
/* variables.css */
:root {
  --bg-color: #0a0a0a;
  --text-color: #fafafa;
  --border-color: #333;
  --accent-color: #3b82f6;
}
```

## Using in Nuxt

Add to `nuxt.config.ts`:

```typescript
export default defineNuxtConfig({
  css: ['~/assets/css/main.css'],
})
```

## Learning Resources

1. **Nuxt Assets**
   - https://nuxt.com/docs/guide/directory-structure/assets

2. **Nuxt Styling**
   - https://nuxt.com/docs/getting-started/styling
