import { Injectable } from '@angular/core';
import { HeroService } from './hero.service';
import { MessageService } from './message.service';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';
import { Hero } from './hero';

@Injectable({
  providedIn: 'root'
})
export class BetterHeroService extends HeroService {

  constructor(protected http: HttpClient
    , protected messageService: MessageService) {
    super(http, messageService);
    console.log(`${new Date()}\tnew Better HeroService`);
  }

  getHeroes(): Observable<Hero[]> {
    return super.getHeroes();
  }
}
