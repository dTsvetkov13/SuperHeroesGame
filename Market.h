#pragma once

#include "SuperHero.h";
#include "Vector.hpp";

class Market {
private:
    Vector<SuperHero> superheroes;

public:
    Market();

    void addSuperHero(const SuperHero& superhero);
    const SuperHero& getSuperHeroByIndex(int index);
    const Vector<SuperHero>& getAllSuperHeroes();
    void removeSuperHeroByIndex(int index);
};

