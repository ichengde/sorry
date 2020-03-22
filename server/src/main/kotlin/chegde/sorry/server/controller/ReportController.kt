package chegde.sorry.server.controller

import chegde.sorry.server.config.MongoConfig
import chegde.sorry.server.javascriptMsg.JavascriptMsg
import chegde.sorry.server.javascriptMsg.Response
import org.springframework.web.bind.annotation.*


@RestController
@RequestMapping("/error")
class ReportController(val connect: MongoConfig) {

    @PostMapping("/report")
    fun report(@RequestBody msg: JavascriptMsg): Response {
        connect.mongoTemplate("log").insert(msg)

        return Response(0)
    }

}