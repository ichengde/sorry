
export function loadScript(src, callback) {
    let s
    let r
    let t
    r = false
    s = document.createElement('script')
    s.type = 'text/javascript'
    s.src = src
    s.onload = s.onreadystatechange = function () {
        // console.log( this.readyState ); //uncomment this line to see which ready states are called.
        if (!r && (!this.readyState || this.readyState === 'complete')) {
            r = true
            callback()
        }
    }
    t = document.getElementsByTagName('script')[0]
    t.parentNode.insertBefore(s, t)
}

export function getParameter(n) {
    const params = new URLSearchParams(window.location.search);
    const result = decodeURIComponent(params.get(n));

    return result;
}

export function isOBJByType(o, type) {
    return Object.prototype.toString.call(o) === '[object ' + (type || 'Object') + ']'
}

export function processStackMsg(error) {
    const stack = error.stack
        .split(/\n/)
        .map(i => i.replace(/\s{4}/g, ''))
        .slice(0, 9)

    const msg = error.toString()
    if (stack.every(a => a.indexOf(msg) < 0)) {
        stack.unshift(msg)
    }

    return stack
}

export function getCookie(name) {
    let arr
    const reg = new RegExp('(^| )' + name + '=([^;]*)(;|$)')
    arr = document.cookie.match(reg)
    if (arr) {
        return unescape(arr[2])
    } else {
        return null
    }
}
