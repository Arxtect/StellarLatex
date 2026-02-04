const TEXCACHEROOT = "/tex";
const TEXPKGCACHEROOT = "/tex/pkg";
const WORKROOT = "/work";
const OUTPUTROOT = "/output";
var Module = {};
self.memlog = "";
self.initmem = undefined;
self.mainfile = "main.tex";
self.texlive_endpoint = "https://latex.arxtect.cn/latex6/arxtect_version_20251120/";
self.ctan_mirror = "https://mirrors.ustc.edu.cn/CTAN/";
Module['print'] = function(a) {
    if (a.includes("Package epstopdf Warning: Shell escape feature is not enabled")) {
        // ignore --shell-escape or --enable-write18
        return;
    }
    if (a.startsWith("[WASM ENGINE]")) {
        console.log("[Compile Engine] " + a);
        return;
    }
    const engineIndex = a.indexOf("[WASM ENGINE]");
    if (engineIndex > 0) {
        a = a.substring(0, engineIndex);
    }
    self.memlog += (a + "\n");
};

Module['printErr'] = function(a) {
    if (a.includes("Package epstopdf Warning: Shell escape feature is not enabled")) {
        // ignore --shell-escape or --enable-write18
        return;
    }
    if (a.startsWith("[WASM ENGINE]")) {
        console.log("[Compile Engine] " + a);
        return;
    }
    const engineIndex = a.indexOf("[WASM ENGINE]");
    if (engineIndex > 0) {
        a = a.substring(0, engineIndex);
    }
    self.memlog += (a + "\n");
    console.log("[Compile Engine] " + a);
};
Module['preRun'] = function() {
    FS.mkdir(TEXCACHEROOT);
    FS.mkdir(TEXPKGCACHEROOT);
    FS.mkdir(WORKROOT);
    FS.mkdir(OUTPUTROOT);
};
function _allocate(content) {
    let res = _malloc(content.length);
    HEAPU8.set(new Uint8Array(content), res);
    return res; 
}

function dumpHeapMemory() {
    var src = wasmMemory.buffer;
    var dst = new Uint8Array(src.byteLength);
    dst.set(new Uint8Array(src));
    // console.log("Dumping " + src.byteLength);
    return dst;
}

function restoreHeapMemory() {
    if (self.initmem) {
        var dst = new Uint8Array(wasmMemory.buffer);
        dst.set(self.initmem);
    }
}

function closeFSStreams() {
    for (var i = 0; i < FS.streams.length; i++) {
        var stream = FS.streams[i];
        if (!stream || stream.fd <= 2) {
            continue;
        }
        FS.close(stream);
    }
}

function prepareExecutionContext() {
    self.memlog = ''; // [DEBUG]
    restoreHeapMemory();
    // closeFSStreams();
    FS.chdir(WORKROOT);
    return 0;
}

Module['postRun'] = function() {
    self.postMessage({
        'result': 'ok',
    });
    self.initmem = dumpHeapMemory();
};

function cleanDir(dir) {
    let l = FS.readdir(dir);
    for (let i in l) {
        let item = l[i];
        if (item === "." || item === "..") {
            continue;
        }
        item = dir + "/" + item;
        let fsStat = undefined;
        try {
            fsStat = FS.stat(item);
        } catch (err) {
            console.error("Not able to fsstat " + item);
            continue;
        }
        if (FS.isDir(fsStat.mode)) {
            cleanDir(item);
        } else {
            try {
                FS.unlink(item);
            } catch (err) {
                console.error("Not able to unlink " + item);
            }
        }
    }

    if (dir !== WORKROOT && dir !== TEXCACHEROOT && dir !== TEXPKGCACHEROOT && dir !== OUTPUTROOT && dir !== "/tmp") {
        try {
            FS.rmdir(dir);
        } catch (err) {
            console.error("Not able to top level " + dir);
        }
    }
}

Module['onAbort'] = function() {
    self.memlog += 'Engine crashed';
    self.postMessage({
        'result': 'failed',
        'status': -254,
        'log': self.memlog,
        'cmd': 'compile'
    });
    return;
};

function compileLaTeXRoutine() {
    prepareExecutionContext();
    closeFSStreams();
    let lastSlash = self.mainfile.lastIndexOf("/");
    let filename = (lastSlash >= 0) ? self.mainfile.substring(lastSlash + 1) : self.mainfile;
    let pdfurl = OUTPUTROOT + "/" + filename.substring(0, filename.lastIndexOf(".")) + ".pdf";
    let synctexurl = OUTPUTROOT + "/" + filename.substring(0, filename.lastIndexOf(".")) + ".synctex.gz";
    FS.writeFile("/tmp/mainfile.txt", self.mainfile);
    const compileLaTeXFunction = cwrap('compileLaTeX', 'number');
    let status = compileLaTeXFunction();
    if (status === 0) {
        if (FS.analyzePath("/tmp/no_compile").exists) {
            FS.unlink("/tmp/no_compile");
            self.postMessage({
                'result': 'ok',
                'status': 0,
                'log': 'not compiled',
                'cmd': 'compile'
            });
        }
        let pdfArrayBuffer = null;
        let synctexArrayBuffer = null;
        try {
            pdfArrayBuffer = FS.readFile(pdfurl, {
                encoding: 'binary'
            });
            synctexArrayBuffer = FS.readFile(synctexurl, {
                encoding: 'binary'
            });
        } catch (err) {
            console.error("Fetch content failed. " + pdfurl);
            status = -253;
            self.postMessage({
                'result': 'failed',
                'status': status,
                'log': self.memlog,
                'cmd': 'compile'
            });
            return;
        }
        self.postMessage({
            'result': 'ok',
            'status': status,
            'log': self.memlog,
            'pdf': pdfArrayBuffer.buffer,
            'synctex': synctexArrayBuffer.buffer,
            'cmd': 'compile'
        }, [pdfArrayBuffer.buffer]);
    } else {
        let pdfArrayBuffer = null;
        let synctexArrayBuffer = null;
        try {
            pdfArrayBuffer = FS.readFile(pdfurl, {
                encoding: 'binary'
            });
            synctexArrayBuffer = FS.readFile(synctexurl, {
                encoding: 'binary'
            });
        } catch (err) {
            console.error("Fetch content failed. " + pdfurl);
            status = -253;
            self.postMessage({
                'result': 'failed',
                'status': status,
                'log': self.memlog,
                'cmd': 'compile'
            });
            return;
        }
        console.error("Compilation failed, with status code " + status);
        self.postMessage({
            'result': 'failed',
            'status': status,
            'log': self.memlog,
            'pdf': pdfArrayBuffer.buffer,
            'synctex': synctexArrayBuffer.buffer,
            'cmd': 'compile'
        }, [pdfArrayBuffer.buffer]);
    }
}

function compileFormatRoutine() {
    prepareExecutionContext();
    FS.writeFile("/tmp/mainfile.txt", "*xelatex.ini");
    const compileLaTeXFunction = cwrap('compileLaTeX', 'number');
    let status = compileLaTeXFunction();
    let pdfArrayBuffer = null;
    let pdfurl = OUTPUTROOT + "/xelatex.fmt";
    try {
        pdfArrayBuffer = FS.readFile(pdfurl, {
            encoding: 'binary'
        });
    } catch (err) {
        console.error("Fetch content failed." + pdfurl);
        status = -253;
        self.postMessage({
            'result': 'failed',
            'status': status,
            'log': self.memlog,
            'cmd': 'compile'
        });
        return;
    }
    if (status === 0) {
        self.postMessage({
            'result': 'ok',
            'status': status,
            'log': self.memlog,
            'pdf': pdfArrayBuffer.buffer,
            'cmd': 'compile'
        }, [pdfArrayBuffer.buffer]);
    } else {
        console.error("Compilation format failed, with status code " + status);
        self.postMessage({
            'result': 'failed',
            'status': status,
            'log': self.memlog,
            'pdf': pdfArrayBuffer.buffer,
            'cmd': 'compile'
        }, [pdfArrayBuffer.buffer]);
    }
}

function mkdirRoutine(dirname) {
    try {
        const targetDir = WORKROOT + "/" + dirname;
        if (FS.analyzePath(targetDir).exists) {
            self.postMessage({
                'result': 'ok',
                'cmd': 'mkdir'
            });
            return;
        }
        FS.mkdir(targetDir);
        self.postMessage({
            'result': 'ok',
            'cmd': 'mkdir'
        });
    } catch (err) {
        console.error("Not able to mkdir " + dirname);
        self.postMessage({
            'result': 'failed',
            'cmd': 'mkdir'
        });
    }
}

function writeFileRoutine(filename, content) {
    try {
        FS.writeFile(WORKROOT + "/" + filename, content);
        self.postMessage({
            'result': 'ok',
            'cmd': 'writefile'
        });
    } catch (err) {
        console.error("Unable to write mem file");
        self.postMessage({
            'result': 'failed',
            'cmd': 'writefile'
        });
    }
}

function synctexViewRoutine(pdf_path, tex_path, line, column) {
    const synctexViewFunction = cwrap('synctex_view', 'string', ['string', 'string', 'number', 'number']);
    try {
        let res = synctexViewFunction(pdf_path, tex_path, line, column);
        if (res) { 
            let parts = res.split('\x1F');
            if (parts.length === 7) {
                self.postMessage({
                    'result': 'ok',
                    'page': parseInt(parts[0]),
                    'x': parseFloat(parts[1]),
                    'y': parseFloat(parts[2]),
                    'h': parseFloat(parts[3]),
                    'v': parseFloat(parts[4]),
                    'W': parseFloat(parts[5]),
                    'H': parseFloat(parts[6]),
                    'cmd': 'synctex_view'
                });
                return;
            }
        }
        self.postMessage({
            'result': 'failed',
            'cmd': 'synctex_view'
        });
        return;
    } catch (err) {
        console.error("Unable to run synctex view");
        self.postMessage({
            'result': 'failed',
            'cmd': 'synctex_view'
        });
    }
}

function synctexEditRoutine(pdf_path, page, x, y) {
    const synctexEditFunction = cwrap('synctex_edit', 'string', ['string', 'number', 'number', 'number']);
    try {
        let res = synctexEditFunction(pdf_path, page, x, y);
        if (res) {
            let parts = res.split('\x1F');
            if (parts.length === 3) {
                let file = parts[0];
                let line = parseInt(parts[1]);
                let column = parseInt(parts[2]);
                self.postMessage({
                    'result': 'ok',
                    'file': file,
                    'line': line,
                    'column': column,
                    'cmd': 'synctex_edit'
                });
                return;
            }
        }
        self.postMessage({
            'result': 'failed',
            'cmd': 'synctex_edit'
        });
        return;
    } catch (err) {
        console.error("Unable to run synctex edit");
        self.postMessage({
            'result': 'failed',
            'cmd': 'synctex_edit'
        });
    }
}

function setTexliveEndpoint(url) {
    if(url) {
        if (!url.endsWith("/")) {
            url += '/';
        }
        self.texlive_endpoint = url;
    }
}

self['onmessage'] = function(ev) {
    let data = ev['data'];
    let cmd = data['cmd'];
    if (cmd === 'compilelatex') {
        compileLaTeXRoutine();
    } else if (cmd === 'compileformat') {
        compileFormatRoutine();
    } else if (cmd === "settexliveurl") {
        setTexliveEndpoint(data['url']);
    } else if (cmd === "mkdir") {
        mkdirRoutine(data['url']);
    } else if (cmd === "writefile") {
        writeFileRoutine(data['url'], data['src']);
    } else if (cmd === "setmainfile") {
        self.mainfile = data['url'];
    } else if (cmd === "grace") {
        console.error("Gracefully Close");
        self.close();
    } else if (cmd === "flushwork") {
        cleanDir(WORKROOT);
    } else if (cmd === "flushbuild") {
        cleanDir(OUTPUTROOT);
        cleanDir("/tmp");
    } else if (cmd == "predownload") {
        // my api
        self.postMessage({
            'result': 'failed',
            'cmd': 'predownload'
        });
    } else if (cmd == "synctex_view") {
        synctexViewRoutine(data['pdfPath'], data['texPath'], data['line'], data['column']);
    } else if (cmd == "synctex_edit") {
        synctexEditRoutine(data['pdfPath'], data['page'], data['x'], data['y']);
    } else {
        console.error("Unknown command " + cmd);
    }
};

let texlive404_cache = {};
let texlive200_cache = {};

function kpse_find_file_impl(nameptr, format, _mustexist) {

    const reqname = UTF8ToString(nameptr);

    if (reqname.includes("/")) {
        return 0;
    }

    const cacheKey = format + "/" + reqname ;

    if (cacheKey in texlive404_cache) {
        return 0;
    }

    if (cacheKey in texlive200_cache) {
        const savepath = texlive200_cache[cacheKey];
        return _allocate(intArrayFromString(savepath));
    }

    
    const remote_url = self.texlive_endpoint + 'xetex/' + cacheKey;
    let xhr = new XMLHttpRequest();
    xhr.open("GET", remote_url, false);
    xhr.timeout = 150000;
    xhr.responseType = "arraybuffer";
    postMessage({
        'cmd': 'engine_compiling_log',
        'level': 'info',
        'message': "Loading resource " + reqname,
    });
    console.log("[Compile Engine] Start downloading texlive file " + remote_url);
    try {
        xhr.send();
    } catch (err) {
        console.log("[Compile Engine] TexLive Download Failed " + remote_url);
        return 0;
    }

    if (xhr.status === 200) {
        let arraybuffer = xhr.response;
        const fileid = xhr.getResponseHeader('fileid');
        const savepath = (format === 99 ? TEXPKGCACHEROOT: TEXCACHEROOT) + "/" + fileid;
        FS.writeFile(savepath, new Uint8Array(arraybuffer));
        texlive200_cache[cacheKey] = savepath;
        return _allocate(intArrayFromString(savepath));

    } else if (xhr.status === 301) {
        console.log("[Compile Engine] TexLive File not exists " + remote_url);
        texlive404_cache[cacheKey] = 1;
        return 0;
    } 
    return 0;
}

let pk404_cache = {};
let pk200_cache = {};

function kpse_find_pk_impl(nameptr, dpi) {
    const reqname = UTF8ToString(nameptr);

    if (reqname.includes("/")) {
        return 0;
    }

    const cacheKey = dpi + "/" + reqname ;

    if (cacheKey in pk404_cache) {
        return 0;
    }

    if (cacheKey in pk200_cache) {
        const savepath = pk200_cache[cacheKey];
        return _allocate(intArrayFromString(savepath));
    }

    const remote_url = self.texlive_endpoint + 'xetex/pk/' + cacheKey;
    let xhr = new XMLHttpRequest();
    xhr.open("GET", remote_url, false);
    xhr.timeout = 150000;
    xhr.responseType = "arraybuffer";
    console.log("[Compile Engine] Start downloading texlive file " + remote_url);
    try {
        xhr.send();
    } catch (err) {
        console.log("[Compile Engine] TexLive Download Failed " + remote_url);
        return 0;
    }

    if (xhr.status === 200) {
        let arraybuffer = xhr.response;
        const pkid = xhr.getResponseHeader('pkid');
        const savepath = TEXCACHEROOT + "/" + pkid;
        FS.writeFile(savepath, new Uint8Array(arraybuffer));
        pk200_cache[cacheKey] = savepath;
        return _allocate(intArrayFromString(savepath));

    } else if (xhr.status === 301) {
        console.log("[Compile Engine] TexLive File not exists " + remote_url);
        pk404_cache[cacheKey] = 1;
        return 0;
    } 
    return 0;

}
