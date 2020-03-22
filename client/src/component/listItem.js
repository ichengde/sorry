import React, { useState, useEffect } from 'react';

import {
    Redirect,
} from "react-router-dom";
import './listItem.css';

export const ListItem = ({ i }) => {
    let [detailId, setDetailId] = useState(null);

    return <div className="error-list" onClick={() => {
        setDetailId(i._id)
    }}>


        <div>
            {i.project}
        </div>

        <div>
            {`${new Date(i.createTime).getMonth()}-${new Date(i.createTime).getUTCDate()} ${new Date(i.createTime).getHours()}:${new Date(i.createTime).getMinutes()}`}
        </div>

        <div>
            {i.error.msg[0]}
        </div>

        {
            detailId !== null ?
                <Redirect push to={`/detail/${detailId}`}></Redirect> :
                undefined
        }
    </div>
}