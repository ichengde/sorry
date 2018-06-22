import { Model } from 'mongoose';
import { Component } from '@nestjs/common';
import { InjectModel } from '@nestjs/mongoose';
import { Log } from './interfaces/log.interface';
import { CreateLogDto } from './dto/create-log.dto';
import { LogSchema } from './schemas/log.schema';

@Component()
export class LogService {
constructor(@InjectModel(LogSchema) private readonly logModel: Model<Log>) {}

	async create(createLogDto: CreateLogDto): Promise<Log> {
		const createdLog = new this.logModel(createLogDto);
		return await createdLog.save();
	}

	async findAll(): Promise<Log[]> {
		return await this.logModel.find().exec();
	}
}
