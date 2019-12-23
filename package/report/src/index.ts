import { sorryType } from "./sorry";

import { getCookie, getParameter, isOBJByType, loadScript, processStackMsg } from "./util";
const methodList = ["log", "info", "warn", "debug", "error"];

const sorry: sorryType = {
    settings: {
        vconsoleUrl: "",
        reportUrl: null,
        reportPrefix: "",
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

methodList.forEach(function (item) {
    const method = console[item];

    console[item] = function () {
        sorry.store.push({
            logType: item,
            logs: arguments,
        });

        method.apply(console, arguments);
    };
});

window.onerror = (msg, url, line, col, error) => {
    let newMsg = msg;

    if (error && error.stack) {
        newMsg = processStackMsg(error);
    }

    if (isOBJByType(newMsg, "Event")) {
        newMsg += (newMsg as Event).type ?
            ("--" + (newMsg as Event).type + "--" + ((newMsg as Event).target ?
                (((newMsg as Event).target as any).tagName + "::" + ((newMsg as Event).target as any).src) : "")) : "";
    }

    newMsg = (newMsg + "" || "").substr(0, 500);

    sorry.logs.push({
        msg: newMsg,
        target: url,
        rowNum: line,
        colNum: col,
    });

    if ((msg as string).toLowerCase().indexOf("script error") > -1) {
        console.error("Script Error: See Brower Console For Detail");
    } else {
        console.error(newMsg);
    }

    const ss = sorry.settings;
    if (ss.reportUrl) {
        let src = ss.reportUrl + (ss.reportUrl.indexOf("?") > -1 ? "&" : "?") + ss.reportKey + "=" + (ss.reportPrefix ? ("[" + ss.reportPrefix + "]") : "") + newMsg + "&t=" + new Date().getTime();
        if (ss.otherReport) {
            for (const i in ss.otherReport) {
                if (ss.otherReport.hasOwnProperty(i)) {
                    src += "&" + i + "=" + (ss.otherReport[i] as string);
                }
            }
        }

        new Image().src = src;
    }
};
