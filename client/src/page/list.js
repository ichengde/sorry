
import React, { useEffect, useState } from 'react';
import { Redirect, useParams } from "react-router-dom";
import { ListItem } from '../component/listItem';
import { getList } from "../data";


export function ListPage() {
    let { page } = useParams();
    page = parseInt(page);

    let [list, setList] = useState([]);
    let [toNext, setToNext] = useState(null);

    useEffect(() => {
        getList(page).then(r => {
            setList(r.data)
        })
    }, [page])

    return <div>
        {
            <div>
                <div onClick={() => {
                    setToNext(page + 1);
                }}>next</div>
                {page > 0 ? <div onClick={() => {
                    setToNext(page - 1);
                }}>prev</div> : undefined}
            </div>
        }

        {toNext !== null ? <Redirect replace to={`/list/${toNext}`}></Redirect> : undefined}

        {list.map(p => {
            return <ListItem i={p} key={p.createTime}></ListItem>
        })}

    </div >;
}
