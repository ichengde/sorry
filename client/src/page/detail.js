
import React, { useState, useEffect } from 'react';
import {
    BrowserRouter,
    Switch,
    Route,
    useParams
} from "react-router-dom";
import './detail.css';
import { getDetail, getRead } from "../data";
import { SourceMapConsumer } from 'source-map';

export function DetailPage() {
    let { id } = useParams();
    let [content, setContent] = useState(null);
    let [sourceContent, setSourceContent] = useState(null);

    useEffect(() => {
        if (!content) {
            getDetail(id).then(r => {
                setContent(r.data);
            })
        }
    })

    return content ? <div className="error-stack">

        <div>
            {content.project}  {content.version}
        </div>

        <div>
            {content.location}
        </div>

        <div>
            {content.userAgent}
        </div>

        <div>
            {Array.isArray(content.error.msg) ? content.error.msg.map((i, idx) => <div key={idx} onClick={() => {
                setSourceContent(null);
                const lineMatch = i.match(/(?<=js\:).*?(?=\:)/);
                if (!lineMatch) {
                    setSourceContent(null);

                    console.info('不符预期 无分隔行数');
                    return;
                }

                const line = i.match(/(?<=js\:).*?(?=\:)/).pop();
                const col = i.slice(i.lastIndexOf(':') + 1);

                getRead(content.project, content.version, i.match(/(?<=\/js\/).*?(?=\:)/)).then((rawSourceMap) => {
                    if (rawSourceMap === 'no such file') {
                        setSourceContent(rawSourceMap);

                        return;
                    }

                    SourceMapConsumer.initialize({
                        "lib/mappings.wasm": "https://unpkg.com/source-map@0.7.3/lib/mappings.wasm"
                    });

                    new SourceMapConsumer(rawSourceMap).then((consumer) => {
                        const position = consumer.originalPositionFor({
                            line: parseInt(line),
                            column: parseInt(col)
                        })

                        console.log(position)

                        const sourceIndex = consumer.sources.findIndex(i => i === position.source);
                        const souceMapContent = consumer.sourcesContent[sourceIndex];

                        if (souceMapContent) {
                            let a1 = souceMapContent.split('\n');
                            a1.splice(position.line + 1, 0, '---------------------------------------------------------------------------------------------------- error');
                            const a2 = a1.join('\n');

                            setSourceContent(a2);
                        } else {
                            setSourceContent('解析出错');
                        }

                        consumer.destroy();
                    });


                })
            }}>{i.replace('@', ` (at `)}</div>) : <div>{content.error.msg}</div>}
        </div>

        {sourceContent ? <pre>
            {sourceContent}
        </pre> : <div></div>}


        <div>
            {content.store.map((i, idx) => <div key={idx} className="store-log-stack">
                <div>{i.logType}</div>
                <div>{JSON.stringify(i.logs)}</div>
            </div>)}
            {/* <div></div> */}
        </div>
    </div> : <div></div>;
}
