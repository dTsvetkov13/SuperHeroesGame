#include "Market.h"

Market::Market()
{

}

void Market::addSuperHero(const SuperHero& superhero)
{
    superheroes.pushBack(superhero);
}

const SuperHero& Market::getSuperHeroByIndex(int index)
{
    return superheroes[index];
}

const Vector<SuperHero>& Market::getAllSuperHeroes()
{
    return superheroes;
}

void Market::removeSuperHeroByIndex(int index)
{
    superheroes.popAt(index);
}