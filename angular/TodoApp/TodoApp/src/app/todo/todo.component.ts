import { Component, OnInit } from '@angular/core';
import { TodoService } from './shared/todo.service';

@Component({
  selector: 'app-todo',
  templateUrl: './todo.component.html',
  styleUrls: ['./todo.component.css'],
  providers: [TodoService]
})
export class TodoComponent implements OnInit {

  _todoList: Array<any>;

  constructor(private todoService: TodoService) { }

  ngOnInit() {
    this._todoList = this.todoService.getTodoList();
  }

  onAdd(itemTitle) {
    console.log('call onAdd function');
    if (!!itemTitle.value && itemTitle.value.length > 0) {
      this.todoService.addTitle(itemTitle.value);
      itemTitle.value = null;
    }
  }

  alterCheck(title: string, isChecked: boolean) {
    this.todoService.checkOrUncheckTitle(title, !isChecked);
  }

  onDelete(title: string) {
    this.todoService.removeTitle(title);
  }

  onKeyDownEnter(event: any) {
    console.log(`nKeyDownEnter:\t${event.target.value}`);
  }
}
