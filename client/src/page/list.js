
import React, { useState, useEffect } from 'react';
import {
    Redirect,
    useParams
} from "react-router-dom";
import { getList } from "../data";
import { ListItem } from '../component/listItem';


export function ListPage() {
    let { page } = useParams();
    page = parseInt(page);

    let [list, setList] = useState([]);
    let [toNext, setToNext] = useState(null);

    useEffect(() => {
        if (list.length === 0) {
            getList(page).then(r => {
                setList(r.data)
            })
        }
    })

    const setPage = (page) => {
        setList([])
        setToNext(page)
    }

    return <div>
        {list.map(p => {
            return <ListItem i={p} key={p.createTime}></ListItem>
        })}

        {
            page === 0 ?
                <div>
                    <div onClick={() => {
                        setPage(page + 1)
                    }}>next</div>
                </div> :
                <div>
                    <div onClick={() => {
                        setPage(page + 1)
                    }}>next</div>
                    <div onClick={() => {
                        setPage(page - 1)
                    }}>prev</div>
                </div>
        }

        {toNext !== null ? <Redirect replace to={`/list/${toNext}`}></Redirect> : undefined}

    </div >;
}
