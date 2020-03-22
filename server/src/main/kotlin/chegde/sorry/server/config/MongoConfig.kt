package chegde.sorry.server.config


import com.mongodb.client.MongoClient
import com.mongodb.client.MongoClients
import com.mongodb.client.MongoDatabase
import org.springframework.beans.factory.annotation.Autowired
import org.springframework.beans.factory.annotation.Value
import org.springframework.context.annotation.Bean
import org.springframework.context.annotation.Configuration
import org.springframework.core.env.Environment
import org.springframework.data.mongodb.core.MongoTemplate

@Configuration
class MongoConfig {

    @Value("\${mongo_username}")
    val mongo_username: String = ""

    @Value("\${mongo_password}")
    val mongo_password: String = ""

    @Bean()
    fun mongoClient(): MongoClient {
        return MongoClients.create("mongodb://$mongo_username:$mongo_password@127.0.0.1:27017/config?authSource=admin")
    }


    fun mongoTemplate(db: String): MongoTemplate {
        return MongoTemplate(mongoClient(), db)
    }
}
