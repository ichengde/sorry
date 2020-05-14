const requestApiBase = process.env.REACT_APP_SORRY_REPORT_API_HOST;
const requestFileBase = process.env.REACT_APP_SORRY_REPORT_FILE_HOST;
export function getList(page) {
    return fetch(`${requestApiBase}/analyse/list/${page}`)
        .then(e => e.json())
}

export function getDetail(id) {
    return fetch(`${requestApiBase}/analyse/detail/${id}`)
        .then(e => e.json())
}

export function getRead(project, version, filename) {
    if (window.location.host.includes('localhost')) {
        const test = `${requestApiBase}/analyse/read/pulin-prod/hfuasilhdusiy3783137819423hjak/index.490ee8fd.js`;
        return fetch(test)
            .then(e => e.text())
    }

    return fetch(`${requestFileBase}/${project}/${version}/${filename}.map`).then(e => e.text())
}