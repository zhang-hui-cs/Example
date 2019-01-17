import { Injectable } from '@angular/core';
import {ajax} from 'rxjs/ajax';

@Injectable({
  providedIn: 'root'
})
export class TodoService {

  _todoList: Array<any>;
  constructor() {
    this._todoList = new Array<any>();
  }

  getTodoList() {
    const apiData = ajax('http://localhost/api/TodoList');
    apiData.subscribe(res => {
      console.log(res.status, res.response);
      this._todoList = res.response;
    });

    console.log('execute getTodoList()');

    return this._todoList;
  }

  addTitle(title: string)  {
    this._todoList.push({title: title, isChecked: false});
  }

  removeTitle(title: string) {
    for (let i = 0 ; i < this._todoList.length; i++) {
      if (this._todoList[i].title === title) {
        this._todoList.splice(i, 1);
      }
    }
  }

  checkOrUncheckTitle(title: string, flag: boolean) {
    for (let i = 0; i < this._todoList.length; i++) {
      if (this._todoList[i].title === title) {
        this._todoList[i].isChecked = flag;
      }
    }
  }
}
