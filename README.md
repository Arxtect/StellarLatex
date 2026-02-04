# StellarLatex

[**English**](#english) | [**中文**](#chinese)

---

## <span id="english"></span> StellarLatex

🌐 **Demo Website**: [https://arxtect.github.io/StellarLatexLanding/](https://arxtect.github.io/StellarLatexLanding/)

### What is StellarLatex?

StellarLatex brings LaTeX compilation to your browser, powered by WebAssembly. Everything runs locally — your documents, fonts, and images never leave your machine. No servers, no uploads, just pure client-side typesetting.

### Key Features

- **🔒 Privacy by design** – All processing happens inside your browser. Your files stay on your device.
- **⚡ Blazing fast** – Our WebAssembly engines are about 20% faster than traditional TeX Live.
- **📦 Easy integration** – Drop a `<script>` tag and start using pdfTeX, XeTeX, or LuaTeX (coming soon) in your own web pages.
- **✅ Compatible** – Produces output identical to TeX Live or MiKTeX. Works seamlessly in browsers and VS Code.
- **📦 Zero installation** – Traditional TeX distributions weigh over 15 GB and take an hour to install. StellarLatex is just **<10 MB** – download, unzip, and you're ready to compile.

### Getting Started in 5 Steps

1. **Download** the [latest release](https://github.com/Arxtect/StellarLatex/releases) from GitHub and extract the files into your project folder.
2. **Include the engine** in your HTML:

   ```html
   <script src="PdfTeXEngine.js"></script>
   ```

3. **Initialize** the engine asynchronously:

   ```js
   const engine = new PdfTeXEngine();
   await engine.loadEngine();
   ```

4. **Feed it your files** – write `.tex` sources, images, or fonts into the in-memory file system:

   ```js
   engine.writeMemFSFile("main.tex", "\\documentclass{article} ...");
   ```

5. **Set the entry point and compile**:

   ```js
   engine.setEngineMainFile("main.tex");
   const result = await engine.compileLaTeX(); // { pdf: Uint8Array, log: string }
   ```

### API Reference

| Method | Description |
|--------|-------------|
| `loadEngine(): Promise<void>` | Loads the WebAssembly module. Call once before any compilation. |
| `isReady(): boolean` | Checks if the engine is initialized and ready to compile. |
| `writeMemFSFile(name: string, data: string \| Uint8Array)` | Writes a file (source or binary) into the engine’s virtual file system. |
| `makeMemFSFolder(path: string)` | Creates a directory inside the virtual file system. |
| `setEngineMainFile(name: string)` | Specifies which file should be treated as the root LaTeX document. |
| `compileLaTeX(): Promise<CompileResult>` | Runs LaTeX on the main file. Returns PDF and log. |
| `flushCache()` | Removes all previously written files from the virtual file system. |
| `closeWorker()` | Terminates the engine and releases resources. |
| `setTexliveEndpoint(url: string)` | (Optional) Configures a custom TeX Live server to fetch packages from. |
| `compileFormat(): Promise<...>` | (Advanced) Generates a TeX engine format file using a custom TeX Live server. |

### Building the Engines Yourself

StellarLatex compiles pdfTeX and XeTeX to WebAssembly. **XeTeX is recommended** because it supports UTF‑8 and OpenType fonts out of the box.

#### Prerequisites

- A Linux environment (WSL works on Windows)
- [Prettier](https://prettier.io/) (`sudo npm install -g prettier`) – used during the build process.

#### Build Steps

##### If you already have Emscripten SDK (emsdk) installed

```bash
EMSDK_PATH=/path/to/emsdk cmake -B build
cmake --build build
```

##### If you don’t have emsdk, don’t worry – CMake will download it automatically

```bash
cmake -B build
cmake --build build
```

On the first run, CMake fetches several third‑party libraries from GitHub and Google Drive (for emsdk). After a successful build, the generated `.js` and `.wasm` files can be found inside the `build/` directory.

### Where Do LaTeX Packages Come From?

StellarLatex doesn’t bundle a full TeX Live distribution. Instead, it fetches required files on‑the‑fly from CTAN mirrors (the Comprehensive TeX Archive Network). You can also point the engine to your own TeX Live server using the `setTexliveEndpoint()` API – useful for offline or customised environments.

## <span id="chinese"></span> StellarLatex - 全新的 Latex 编译器

🌐 **在线演示**: [https://arxtect.github.io/StellarLatexLanding/](https://arxtect.github.io/StellarLatexLanding/)

### 项目简介

StellarLatex 让你在浏览器中直接运行 LaTeX 引擎，所有计算均在本地完成——你的文档、字体和图片永远不会上传到任何服务器。基于 WebAssembly 技术，我们致力于提供安全、快速且易于集成的 LaTeX 编译方案。

### 核心特性

- **🔒 隐私安全** – 引擎完全在浏览器内运行，文件绝不离开你的设备。
- **⚡ 速度优势** – 编译器性能比传统 TeX Live 提升约 20%，甚至更高。
- **📦 轻松集成** – 只需一行 `<script>` 标签，即可在你的网页中使用 pdfTeX、XeTeX 及未来将支持的 LuaTeX。
- **✅ 完美兼容** – 生成的 PDF 与 TeX Live、MiKTeX 完全一致，且同时支持浏览器和 VS Code 环境。
- **📦 无需安装** – 传统 TeX 发行版体积超过 15GB，安装耗时约一小时。StellarLatex 解压后 **不到 10MB**，下载解压即可直接使用。

### 快速上手（5 步搞定）

1. **下载** [最新发行版本](https://github.com/Arxtect/StellarLatex/releases) 并解压到你的项目目录。
2. **引入引擎脚本**：

   ```html
   <script src="PdfTeXEngine.js"></script>
   ```

3. **初始化引擎**（异步）：

   ```js
   const engine = new PdfTeXEngine();
   await engine.loadEngine();
   ```

4. **写入文件** – 将 `.tex` 源码、图片或字体写入引擎的内存文件系统：

   ```js
   engine.writeMemFSFile("main.tex", "\\documentclass{article} ...");
   ```

5. **指定主文件并编译**：

   ```js
   engine.setEngineMainFile("main.tex");
   const result = await engine.compileLaTeX(); // 返回 { pdf: Uint8Array, log: string }
   ```

### API 文档

| 方法 | 说明 |
|------|------|
| `loadEngine(): Promise<void>` | 加载 WebAssembly 引擎（仅需调用一次）。 |
| `isReady(): boolean` | 检查引擎是否已就绪，可开始编译。 |
| `writeMemFSFile(name: string, data: string \| Uint8Array)` | 向虚拟文件系统写入文件（源码或二进制）。 |
| `makeMemFSFolder(path: string)` | 在虚拟文件系统中创建目录。 |
| `setEngineMainFile(name: string)` | 设置 LaTeX 编译的入口文件。 |
| `compileLaTeX(): Promise<CompileResult>` | 执行 LaTeX 编译，返回 PDF 二进制数据和日志。 |
| `flushCache()` | 清空虚拟文件系统中的所有文件。 |
| `closeWorker()` | 关闭引擎，释放资源。 |
| `setTexliveEndpoint(url: string)` | （可选）配置自定义 TeX Live 服务器，用于获取宏包。 |
| `compileFormat(): Promise<...>` | （高级）在自定义服务器上生成 TeX 引擎格式文件。 |

### 自行编译引擎

StellarLatex 将 pdfTeX 和 XeTeX 编译为 WebAssembly。**推荐使用 XeTeX**，因为它原生支持 UTF‑8 和 OpenType 字体。

#### 环境要求

- Linux 系统（Windows 用户可使用 WSL）
- [Prettier](https://prettier.io/)（`sudo npm install -g prettier`）——编译过程中需要。

#### 编译步骤

##### 如果你已安装 Emscripten SDK (emsdk)

```bash
EMSDK_PATH=/path/to/emsdk cmake -B build
cmake --build build
```

##### 如果没有 emsdk，CMake 会自动下载

```bash
cmake -B build
cmake --build build
```

首次运行时会自动从 GitHub 和 Google Drive（用于 emsdk）下载依赖库，因此您需要有相关网站的访问权限。编译成功后，`build/` 目录下会生成 `.js` 和 `.wasm` 文件。

### LaTeX 宏包从何而来？

StellarLatex 并未内置完整的 TeX Live 发行版，而是在编译时动态从 CTAN 镜像（Comprehensive TeX Archive Network）获取所需文件。你也可以通过 `setTexliveEndpoint()` API 指定自己的 TeX Live 服务器，方便离线环境或定制化需求。
