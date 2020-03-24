
// export const page = new Subject();
const requestBase = window.location.protocol + (window.location.host.includes('localhost') ? `//localhost:18889` : process.env.sorry_report_url);

export function getList(page) {
    return fetch(`${requestBase}/analyse/list/${page}`)
        .then(e => e.json())
}

export function getDetail(id) {
    return fetch(`${requestBase}/analyse/detail/${id}`)
        .then(e => e.json())
}

export function getRead(project, version, filename) {
    if (window.location.host.includes('localhost')) {
        const test = `${requestBase}/analyse/read/pulin-prod/hfuasilhdusiy3783137819423hjak/index.490ee8fd.js`;
        return fetch(test)
            .then(e => e.text())
    }

    return fetch(`${requestBase}/analyse/read/${project}/${version}/${filename}`)
        .then(e => e.text())
}