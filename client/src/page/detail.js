
import React, { useState, useEffect } from 'react';
import {
    BrowserRouter,
    Switch,
    Route,
    useParams
} from "react-router-dom";
import './detail.css';
import { getDetail } from "../data";


export function DetailPage() {
    let { id } = useParams();
    let [content, setContent] = useState(null);

    useEffect(() => {
        if (!content) {
            getDetail(id).then(r => {
                setContent(r.data);
            })
        }
    })

    return content ? <div className="error-stack">

        <div>
            {content.project}
        </div>


        <div>
            {content.version}
        </div>


        <div>
            {content.location}
        </div>

        <div>
            {content.userAgent}
        </div>

        <div>
            {Array.isArray(content.error.msg) ? content.error.msg.map((i, idx) => <div key={idx}>{i.replace('@', ` (at `)}</div>) : <div>{content.error.msg}</div>}
        </div>
    </div> : <div></div>;
}
