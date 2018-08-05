import { Component } from '@angular/core';
import { Http } from "@angular/http";


@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'client';
  list;
  constructor(public http: Http) {
    this.getList();
  }
  getList() {
    this.http.get('http://127.0.0.1:5525/result').subscribe((res) => {
      this.list = res;
    });
  }
}
