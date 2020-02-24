
export function loadScript(src, callback) {
    let s;
    let r;
    let t;
    r = false;
    s = document.createElement("script");
    s.type = "text/javascript";
    s.src = src;
    s.onload = s.onreadystatechange = function () {
        //console.log( this.readyState ); //uncomment this line to see which ready states are called.
        if (!r && (!this.readyState || this.readyState === "complete")) {
            r = true;
            callback();
        }
    };
    t = document.getElementsByTagName("script")[0];
    t.parentNode.insertBefore(s, t);
}

export function getParameter(n) {
    const m = window.location.hash.match(new RegExp("(?:#|&)" + n + "=([^&]*)(&|$)"));
    const result = !m ? "" : decodeURIComponent(m[1]);
    return result || getParameterByName(n);
}

export function getParameterByName(name, url?) {
    if (!url) { url = window.location.href; }
    name = name.replace(/[\[\]]/g, "\\$&");
    const regex = new RegExp("[?&]" + name + "(=([^&#]*)|&|#|$)");
    const results = regex.exec(url);
    if (!results) { return null; }
    if (!results[2]) { return ""; }
    return decodeURIComponent(results[2].replace(/\+/g, " "));
}

export function isOBJByType(o, type) {
    return Object.prototype.toString.call(o) === "[object " + (type || "Object") + "]";
}

export function processStackMsg(error) {
    let stack = error.stack
        .split(/\n/)
        .map(i => i.replace(/\s{4}/g, ''))
        .slice(0, 9)

    const msg = error.toString();
    if (stack.indexOf(msg) < 0) {
        stack = msg + "@" + stack;
    }
    return stack;
}

export function getCookie(name) {
    let arr;
    const reg = new RegExp("(^| )" + name + "=([^;]*)(;|$)");
    arr = document.cookie.match(reg);
    if (arr) {
        return unescape(arr[2]);
    } else {
        return null;
    }
}
