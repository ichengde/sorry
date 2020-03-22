import { Subject } from 'rxjs';

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