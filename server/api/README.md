# Server API

Backend API routes (optional for this project).

## When to use

Your WASM tool runs entirely client-side, so you might not need this.
But it's useful for:

- Saving user preferences
- Analytics
- Sharing processed results via URL
- Server-side WASM processing for large files

## Structure

```
server/api/
  health.get.ts     # GET /api/health
  process.post.ts   # POST /api/process (if doing server-side processing)
```

## Example: Health Check

```typescript
// health.get.ts
export default defineEventHandler(() => {
  return { status: 'ok', timestamp: Date.now() };
});
```

## Example: Server-side WASM (advanced)

You can run WASM on the server using Node.js:

```typescript
// process.post.ts
import { readFile } from 'fs/promises';
import { join } from 'path';

export default defineEventHandler(async (event) => {
  const body = await readBody(event);
  
  // Load WASM on server
  const wasmPath = join(process.cwd(), 'public/wasm/module.wasm');
  const wasmBuffer = await readFile(wasmPath);
  const { instance } = await WebAssembly.instantiate(wasmBuffer);
  
  // Process and return
  const result = instance.exports.process(body.data);
  return { result };
});
```

## Learning Resources

1. **Nuxt Server Routes**
   - https://nuxt.com/docs/guide/directory-structure/server

2. **Nitro (Nuxt's server engine)**
   - https://nitro.unjs.io/
