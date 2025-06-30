const TEXCACHEROOT = "/tex";
const TEXPKGCACHEROOT = "/tex/pkg";
const WORKROOT = "/work";
var Module = {};
self.memlog = "";
self.mainfile = "main.tex";
self.texlive_endpoint = "https://magic.pointer.ai/latex3/arxtect_version_20250626/";
self.ctan_mirror = "https://mirrors.ustc.edu.cn/CTAN/";
Module['print'] = function(a) {
    self.memlog += (a + "\n");
    console.log(a);
};

Module['printErr'] = function(a) {
    self.memlog += (a + "\n");
    console.log(a);
};

Module['preRun'] = function() {
    FS.mkdir(TEXCACHEROOT);
    FS.mkdir(TEXPKGCACHEROOT);
    FS.mkdir(WORKROOT);
};

function _allocate(content) {
    let res = _malloc(content.length);
    HEAPU8.set(new Uint8Array(content), res);
    return res; 
}

function prepareExecutionContext() {
    self.memlog = '';
    FS.chdir(WORKROOT);
}

Module['postRun'] = function() {
    self.postMessage({
        'result': 'ok',
    });
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

    if (dir !== WORKROOT) {
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

function compilePDFRoutine() {
    prepareExecutionContext();
    const setMainFunction = cwrap('setMainEntry', 'number', ['string']);
    setMainFunction(self.mainfile);
    let status = _compilePDF();
    let pdfArrayBuffer = null;
    let pdfurl = WORKROOT + "/" + self.mainfile.substr(0, self.mainfile.length - 4) + ".pdf"
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
        console.error("Compilation failed, with status code " + status);
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
        //console.log("removing " + item);
        FS.mkdir(WORKROOT + "/" + dirname);
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
    if (cmd === 'compilepdf') {
        compilePDFRoutine();
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
    } else if (cmd === "flushcache") {
        cleanDir(WORKROOT);
    } else {
        console.error("Unknown command " + cmd);
    }
};

let texlive404_cache = {};
let texlive200_cache = {};

function kpse_find_file_impl(nameptr, format, _mustexist) {

    let reqname = UTF8ToString(nameptr);

    // It is a hack , since webassembly version latex engine stores 
    // all templates file inside /tex/, therefore, we have to fetch it again
    if (reqname.startsWith("/tex/")) {
        reqname = reqname.substr(5);
    }

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
    console.log("Start downloading texlive file " + remote_url);
    try {
        xhr.send();
    } catch (err) {
        console.log("TexLive Download Failed " + remote_url);
        return 0;
    }

    if (xhr.status === 200) {
        let arraybuffer = xhr.response;
        const fileid = xhr.getResponseHeader('fileid');
        const savepath = TEXCACHEROOT + "/" + fileid;
        FS.writeFile(savepath, new Uint8Array(arraybuffer));
        texlive200_cache[cacheKey] = savepath;
        return _allocate(intArrayFromString(savepath));

    } else if (xhr.status === 301) {
        console.log("TexLive File not exists " + remote_url);
        texlive404_cache[cacheKey] = 1;
        return 0;
    } 
    return 0;
}

function ctan_download_pkg_impl(urlsuffix, _download_location) {
    const fetch_url = self.ctan_mirror + UTF8ToString(urlsuffix);
    const download_location = TEXPKGCACHEROOT + "/" + UTF8ToString(_download_location);
    // fetch file from ctan server
    let xhr = new XMLHttpRequest();
    xhr.open("GET", fetch_url, false);
    xhr.timeout = 150000;
    xhr.responseType = "arraybuffer";
    console.log("Start downloading CTAN package " + fetch_url);
    try {
        xhr.send();
    } catch (err) {
        console.log("CTAN Download Failed: " + fetch_url);
        return 1;
    }
    if (xhr.status === 200) {
        let arraybuffer = xhr.response;
        FS.writeFile(download_location, new Uint8Array(arraybuffer));
        return 0;
    } else {
        console.log("CTAN Download Failed with status " + xhr.status + " " + fetch_url);
        return 1;
    }
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

    const remote_url = self.texlive_endpoint + 'pdftex/pk/' + cacheKey;
    let xhr = new XMLHttpRequest();
    xhr.open("GET", remote_url, false);
    xhr.timeout = 150000;
    xhr.responseType = "arraybuffer";
    console.log("Start downloading texlive file " + remote_url);
    try {
        xhr.send();
    } catch (err) {
        console.log("TexLive Download Failed " + remote_url);
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
        console.log("TexLive File not exists " + remote_url);
        pk404_cache[cacheKey] = 1;
        return 0;
    } 
    return 0;

}
