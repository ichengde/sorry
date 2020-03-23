package chegde.sorry.server.controller;

import chegde.sorry.server.config.MongoConfig
import chegde.sorry.server.javascriptMsg.JavascriptMsg
import chegde.sorry.server.javascriptMsg.Response
import org.springframework.beans.factory.annotation.Value
import org.springframework.data.domain.Sort
import org.springframework.data.mongodb.core.query.BasicQuery
import org.springframework.data.mongodb.core.query.Query
import org.springframework.util.StringUtils
import org.springframework.web.bind.annotation.*
import org.springframework.web.multipart.MultipartFile
import java.io.File
import java.nio.file.Files
import java.nio.file.Path
import java.nio.file.Paths
import java.nio.file.StandardCopyOption


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

    @Value("\${sorry_upload_dir:\${user.home}}")
    var uploadDir: String? = null
    @PostMapping("/upload/{project}/{version}")
    fun upload(@RequestParam("file") file: MultipartFile): Response {

        try {
            val copyLocation: Path = Paths
                    .get(uploadDir + File.separator + StringUtils.cleanPath(file.name))
            Files.copy(file.inputStream, copyLocation, StandardCopyOption.REPLACE_EXISTING)
        } catch (e: Exception) {
            e.printStackTrace()
        }


        return Response(0)
    }

}