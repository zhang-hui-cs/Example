import {Component, OnInit} from '@angular/core';
import {Hero} from '../hero';
import {HeroService} from '../hero.service';

@Component({
  selector: 'app-heroes',
  templateUrl: './heroes.component.html',
  styleUrls: ['./heroes.component.css']
})
export class HeroesComponent implements OnInit {
  heroes: Hero[];

  constructor(private heroSvc: HeroService) {
  }

  selectedHero: Hero;

  ngOnInit() {
    this.heroSvc.getHeroes().subscribe(ii => this.heroes = ii);
  }

  onSelect(hero: Hero): void {
    this.selectedHero = hero;
  }
}
