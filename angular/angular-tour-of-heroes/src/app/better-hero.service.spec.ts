import { TestBed } from '@angular/core/testing';

import { BetterHeroService } from './better-hero.service';

describe('BetterHeroService', () => {
  beforeEach(() => TestBed.configureTestingModule({}));

  it('should be created', () => {
    const service: BetterHeroService = TestBed.get(BetterHeroService);
    expect(service).toBeTruthy();
  });
});
