import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { CardOverviewExampleComponent } from './card-overview-example.component';

describe('CardOverviewExampleComponent', () => {
  let component: CardOverviewExampleComponent;
  let fixture: ComponentFixture<CardOverviewExampleComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ CardOverviewExampleComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(CardOverviewExampleComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
