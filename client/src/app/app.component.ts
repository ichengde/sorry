import { Component } from '@angular/core';
import { HttpHeaders, HttpClient, HttpParams } from '@angular/common/http';


@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'client';
  list;
  constructor(
    private http: HttpClient,
  ) {
    this.getList();
  }
  getList() {
    this.http.get('http://127.0.0.1:5525/result').subscribe((res: any) => {
      this.list = res.stack;
    });
  }
}
