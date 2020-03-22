package chegde.sorry.server.javascriptMsg;

import org.springframework.data.annotation.Id
import java.util.*
import kotlin.collections.ArrayList

data class JavascriptMsg(

        @Id
        val _id: String? = null,

        val token: String? = null,
        val project: String? = null,

        val userAgent: String?,
        val location: String?,
        val store: ArrayList<Store>?,
        val error: MsgErrorType?,
        val createTime: Date? = Date()

)