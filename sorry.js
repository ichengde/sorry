; (function (root, factory) {
    if (typeof exports === 'object' && typeof module === 'object')
        module.exports = factory()
    else if (typeof define === 'function' && define.amd)
        define([], factory)
    else if (typeof exports === 'object')
        exports['sorry'] = factory()
    else
        root['sorry'] = factory()
})(this, function () {
    var sorry = {}
    sorry.settings = {
        vconsoleUrl: '',
        reportUrl: null,
        reportPrefix: '',
        reportKey: 'msg',
        otherReport: null,
        entry: null
    }

    sorry.store = []

    var methodList = ['log', 'info', 'warn', 'debug', 'error'];
    methodList.forEach(function (item) {
        var method = console[item];

        console[item] = function () {
            sorry.store.push({
                logType: item,
                logs: arguments
            });

            method.apply(console, arguments);
        }
    });

    sorry.logs = []
    sorry.config = function (config) {
        for (var i in config) {
            if (config.hasOwnProperty(i)) {
                sorry.settings[i] = config[i]
            }
        }

        if (config.entry) {
            window.addEventListener('load', function () {
                sorry.entry(config.entry)
            })
        }

        var parameter = getParameter('vconsole')

        if (parameter) {
            if (parameter === 'show') {
                sorry.vconsole(true)
            } else {
                sorry.vconsole(false)
            }
        }
    }

    sorry.vconsole = function (show) {
        loadScript(sorry.settings.vconsoleUrl, function () {

            if (typeof vConsole === 'undefined') {
                vConsole = new VConsole({
                    defaultPlugins: ['system', 'network', 'element', 'storage'],
                    maxLogNumber: 5000
                })
            }
        })

        var i = 0, len = sorry.store.length

        for (; i < len; i++) {
            var item = sorry.store[i]
            item.noOrigin = true
            vConsole.pluginList.default.printLog(item)
        }

        if (show) {
            try {
                vConsole.show()
            } catch (e) {

            }

            window.addEventListener('load', function () {
                vConsole.show()
            })
        }
    }

    sorry.entry = function (selector) {
        var count = 0,
            entry = document.querySelector(selector)

        if (entry) {
            entry.addEventListener('click', function () {
                count++
                if (count > 5) {
                    count = -10000
                    sorry.vConsole(true)
                }
            })
        }
    }

    window.onerror = function (msg, url, line, col, error) {
        var newMsg = msg

        if (error && error.stack) {
            newMsg = processStackMsg(error)
        }

        if (isOBJByType(newMsg, "Event")) {
            newMsg += newMsg.type ?
                ('--' + newMsg.type + "--" + (newMsg.target ?
                    (newMsg.target.tagName + "::" + newMsg.target.src) : "")) : ""
        }

        newMsg = (newMsg + "" || "").substr(0, 500)

        sorry.logs.push({
            msg: newMsg,
            target: url,
            rowNum: line,
            colNum: col
        })

        if (msg.toLowerCase().indexOf('script error') > -1) {
            console.error("Script Error: See Brower Console For Detail")
        } else {
            console.error(newMsg)
        }

        var ss = sorry.settings
        if (ss.reportUrl) {
            var src = ss.reportUrl + (ss.reportUrl.indexOf('?') > -1 ? '&' : "?") + ss.reportKey + '=' + (ss.reportPrefix ? ('[' + ss.reportPrefix + ']') : '') + newMsg + '&t=' + new Date().getTime()
            if (ss.otherReport) {
                for (var i in ss.otherReport) {
                    if (ss.otherReport.hasOwnProperty(i)) {
                        src += '&' + i + '=' ss.otherReport[i]
                    }
                }
            }

            new Image().src = src
        }
    }

    function loadScript(src, callback) {
        var s,
            r,
            t
        r = false
        s = document.createElement('script')
        s.type = 'text/javascript'
        s.src = src
        s.onload = s.onreadystatechange = function () {
            //console.log( this.readyState ); //uncomment this line to see which ready states are called.
            if (!r && (!this.readyState || this.readyState == 'complete')) {
                r = true
                callback()
            }
        }
        t = document.getElementsByTagName('script')[0]
        t.parentNode.insertBefore(s, t)
    }

    function getParameter(n) {
        var m = window.location.hash.match(new RegExp('(?:#|&)' + n + '=([^&]*)(&|$)')),
            result = !m ? '' : decodeURIComponent(m[1])
        return result || getParameterByName(n)
    }

    function getParameterByName(name, url) {
        if (!url) url = window.location.href
        name = name.replace(/[\[\]]/g, "\\$&")
        var regex = new RegExp("[?&]" + name + "(=([^&#]*)|&|#|$)"),
            results = regex.exec(url)
        if (!results) return null
        if (!results[2]) return ''
        return decodeURIComponent(results[2].replace(/\+/g, " "))
    }

    function isOBJByType(o, type) {
        return Object.prototype.toString.call(o) === "[object " + (type || "Object") + "]"
    }

    function processStackMsg(error) {
        var stack = error.stack
            .replace(/\n/gi, "")
            .split(/\bat\b/)
            .slice(0, 9)
            .join("@")
            .replace(/\?[^:]+/gi, "")
        var msg = error.toString()
        if (stack.indexOf(msg) < 0) {
            stack = msg + "@" + stack
        }
        return stack
    }

    function getCookie(name) {
        var arr, reg = new RegExp("(^| )" + name + "=([^;]*)(;|$)")

        if (arr = document.cookie.match(reg))
            return unescape(arr[2])
        else
            return null
    }

    sorry.getCookie = getCookie
    sorry.getParameter = getParameter
    sorry.loadScript = loadScript

    return sorry
});