package chegde.sorry.server.util

import java.io.File

object DirUtil {
    fun makeDir(pathDir: String) {
        val dirFile = File(pathDir)

        if (!dirFile.exists()) {
            val doMakeDir = dirFile.mkdir()
        }
    }
}