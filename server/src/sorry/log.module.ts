import { Module } from '@nestjs/common';
import { MongooseModule } from '@nestjs/mongoose';
import { LogController } from './log.controller';
import { LogService } from './log.service';
import { LogSchema } from './schemas/log.schema';

@Module({
imports: [MongooseModule.forFeature([{ name: 'Log', schema: LogSchema }])],
	controllers: [LogController],
	components: [LogService],
})
export class LogModule {}
