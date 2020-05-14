const requestBase = process.env.REACT_APP_SORRY_REPORT_HOST;

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

    return fetch(`https://sorry-file.ihook.center:888/${project}/${version}/${filename}.map`).then(e => e.text())
}