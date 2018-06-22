import * as mongoose from 'mongoose';

export const LogSchema = new mongoose.Schema({
  name: String,
  age: Number,
});
