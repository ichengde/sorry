package chegde.sorry.server.controller;

import chegde.sorry.server.config.MongoConfig
import chegde.sorry.server.javascriptMsg.JavascriptMsg
import chegde.sorry.server.javascriptMsg.Response
import org.springframework.data.domain.Sort
import org.springframework.data.mongodb.core.query.BasicQuery
import org.springframework.data.mongodb.core.query.Criteria
import org.springframework.data.mongodb.core.query.Query
import org.springframework.web.bind.annotation.GetMapping
import org.springframework.web.bind.annotation.PathVariable
import org.springframework.web.bind.annotation.RequestMapping
import org.springframework.web.bind.annotation.RestController


@RestController
@RequestMapping("/analyse")
class AnalyseController(val connect: MongoConfig) {

    @GetMapping("/list/{page}")
    fun list(@PathVariable page: Int): Response {
        val query = Query().with(Sort.by(Sort.Direction.DESC, "createTime"))
                .skip((page * 30).toLong()).limit(30)

        query.fields().include("_id")
        query.fields().include("project")
        query.fields().include("createTime")
        query.fields().include("error")

        val list = connect.mongoTemplate("log").find(query, JavascriptMsg::class.java);

        return Response(0, data = list)
    }

    @GetMapping("/detail/{id}")
    fun detail(@PathVariable id: String): Response {
        val query = BasicQuery("{_id : \"${id}\"}")
//        val query = Query(Criteria.where("_id").`is`(id))
        val item = connect.mongoTemplate("log").findOne(query, JavascriptMsg::class.java);

        return Response(0, data = item)
    }

}