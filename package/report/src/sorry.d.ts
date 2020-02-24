interface logInfoType {
    logType: string;
    logs: any;
    noOrigin?: boolean;
}

interface settings {
    vconsoleUrl?: string;
    reportUrl?: string;
    project: string;
    id?: string;
    reportKey: string;
    otherReport: object;
    entry: string;
}

interface sorryType {
    settings: settings;
    store: logInfoType[];
    logs: any;
    config: (config: any) => void;
    entry: (selector: string) => void;
    vconsole: (show: boolean) => void;

    // setClient: () => void;
    getCookie: (name: string) => void;
    getParameter: (n: string) => void;
    loadScript: (src: string, cb: () => {}) => void;
}

declare global {
    interface Window {
        vConsole: any;
    }
}

export { sorryType };
