import { getCookie, getParameter, processStackMsg } from './util'
import { historyWatch } from './history'
const methodList = ['log', 'info', 'warn', 'debug'] // "error"

export const sorry: sorryType = {
    settings: {
        vconsoleUrl: '',
        reportUrl: null,
        project: '',
        version: '',
        token: '',
        reportKey: 'msg',
        otherReport: null,
        entry: null
    },
    store: [],
    logs: [],
    config: (config) => {
        for (const i in config) {
            if (Object.prototype.hasOwnProperty.call(config, i)) {
                sorry.settings[i] = config[i]
            }
        }

        document.addEventListener("click", (e) => {
            const target = e.target as HTMLElement;
            if (target) {
                sorry.store.push({
                    logType: e.type,
                    logs: [target.outerHTML]
                })
            }
        })

        historyWatch(() => {
            sorry.store.push({
                logType: 'nav',
                logs: [location.hash]
            })
        })
    },
    getCookie,
    getParameter,
}

const getReportContent = () => {
    return {
        userAgent: navigator.userAgent,
        location: location.href,

        version: sorry.settings.version,
        project: sorry.settings.project,
        token: sorry.settings.token,

        store: sorry.store,
        error: sorry.logs
    }
}

methodList.forEach(function (item) {
    const method = console[item]

    console[item] = function () {
        const argumentsArray = []
        for (let i = 0; i < arguments.length; i++) {
            argumentsArray.push(arguments[i])
        }

        sorry.store.push({
            logType: item,
            logs: argumentsArray
        })

        method.apply(console, arguments)
    }
})

export const errorHandler = (ev: ErrorEvent, info?: any) => {
    const { message, filename, lineno, colno, error } = ev
    let newMsg = message

    if (error && error.stack) {
        newMsg = processStackMsg(error)
    }

    if (info) {
        newMsg = processStackMsg(ev)
    }

    sorry.logs = {
        msg: newMsg,
        target: filename,
        rowNum: lineno,
        colNum: colno
    }

    if (message.toLowerCase().indexOf('script error') > -1) {
        console.error('Script Error: See Brower Console For Detail')
    } else {
        console.error(message)
    }

    const ss = sorry.settings
    const reportUrl = ss.reportUrl

    if (reportUrl) {
        fetch(reportUrl, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json;charset=utf-8'
            },
            body: JSON.stringify(getReportContent())
        })
            .then(res => {
                return res.json()
            })

    }
}

