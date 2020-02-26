import { sorryType } from "./sorry";

import { getCookie, getParameter, isOBJByType, loadScript, processStackMsg } from "./util";
const methodList = ["log", "info", "warn", "debug",]; // "error"

export const sorry: sorryType = {
    settings: {
        vconsoleUrl: "",
        reportUrl: null,
        project: "",
        token: "",
        reportKey: "msg",
        otherReport: null,
        entry: null,
    },
    store: [],
    logs: [],
    entry: (selector) => {
        let count = 0;
        const entry = document.querySelector(selector);

        if (entry) {
            entry.addEventListener("click", () => {
                count = count + 1;
                if (count > 5) {
                    count = count - 10000;
                    sorry.vconsole(true);
                }
            });
        }
    },
    config: (config) => {
        for (const i in config) {
            if (config.hasOwnProperty(i)) {
                sorry.settings[i] = config[i];
            }
        }

        if (config.entry) {
            window.addEventListener("load", () => {
                sorry.entry(config.entry);
            });
        }

        const parameter = getParameter("vconsole");

        if (parameter) {
            if (parameter === "show") {
                sorry.vconsole(true);
            } else {
                sorry.vconsole(false);
            }
        }
    },
    vconsole: (show) => {
        loadScript(sorry.settings.vconsoleUrl, () => {
            if (typeof (window as any).vConsole === "undefined") {
                (window as any).vConsole = new (window as any).VConsole({
                    defaultPlugins: ["system", "network", "element", "storage"],
                    maxLogNumber: 5000,
                });
            }
        });

        let i = 0;
        const len = sorry.store.length;

        for (; i < len; i++) {
            const item = sorry.store[i];
            item.noOrigin = true;
            (window as any).vConsole.pluginList.default.printLog(item);
        }

        if (show) {
            try {
                (window as any).vConsole.show();
            } catch (e) { }

            window.addEventListener("load", () => {
                (window as any).vConsole.show();
            });
        }
    },
    getCookie,
    getParameter,
    loadScript,

};

const getReportContent = () => {
    return {
        userAgent: navigator.userAgent,
        location: location.href,

        project: sorry.settings.project,
        token: sorry.settings.token,
        store: sorry.store,
        error: sorry.logs
    }
}

methodList.forEach(function (item) {
    const method = console[item];

    console[item] = function () {
        const argumentsArray = [];
        for (let i = 0; i < arguments.length; i++) {
            argumentsArray.push(arguments[i]);
        }

        sorry.store.push({
            logType: item,
            logs: argumentsArray,
        });

        method.apply(console, arguments);
    };
});


export const errorHandler = (ev: ErrorEvent, info?: any) => {
    const { message, filename, lineno, colno, error } = ev;
    let newMsg = message;

    if (error && error.stack) {
        newMsg = processStackMsg(error);
    }

    if (info) {
        newMsg = processStackMsg(ev);
    }

    sorry.logs = {
        msg: newMsg,
        target: filename,
        rowNum: lineno,
        colNum: colno,
    };

    if (message.toLowerCase().indexOf("script error") > -1) {
        console.error("Script Error: See Brower Console For Detail");
    } else {
        console.error(message);
    }


    const ss = sorry.settings;
    const reportUrl = ss.reportUrl

    if (reportUrl) {
        fetch(reportUrl, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json;charset=utf-8'
            },
            body: JSON.stringify(getReportContent()),
        })
            .then(res => {
                return res.json();
            })
            .catch(err => {
            });

    }
}

window.addEventListener("error", errorHandler)
