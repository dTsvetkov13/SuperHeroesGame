#include "SuperHero.h"

//TODO: scopes

SuperHero::SuperHero() = default;

SuperHero::SuperHero(const MyString& n, const MyString& s, const MyString& hn,
    PowerType pt, double p, double bp, HeroAttackMode am)
    : name(n), surname(s), heroName(hn), powerType(pt), power(p), buyPrice(bp), attackMode(am) {}


MyString SuperHero::getName() const
{
    return name;
}

MyString SuperHero::getSurname() const
{
    return surname;
}

MyString SuperHero::getHeroName() const
{
    return heroName;
}

PowerType SuperHero::getPowerType() const
{
    return powerType;
}

double SuperHero::getPower() const
{
    return power;
}

double SuperHero::getBuyPrice() const
{
    return buyPrice;
}

HeroAttackMode SuperHero::getAttackMode() const
{
    return attackMode;
}

void SuperHero::setName(const MyString& n)
{
    name = n;
}

void SuperHero::setSurname(const MyString& s)
{
    surname = s;
}

void SuperHero::setHeroName(const MyString& hn)
{
    heroName = hn;
}

void SuperHero::setPowerType(PowerType pt)
{
    powerType = pt;
}

void SuperHero::setPower(double p)
{
    power = p;
}

void SuperHero::setBuyPrice(double bp)
{
    buyPrice = bp;
}

void SuperHero::setAttackMode(HeroAttackMode am)
{
    attackMode = am;
}

void SuperHero::displayInfo() const
{
    std::cout << "Name: " << name << std::endl;
    std::cout << "Surname: " << surname << std::endl;
    std::cout << "Hero Name: " << heroName << std::endl;
    std::cout << "Power Type: " << static_cast<int>(powerType) << std::endl;
    std::cout << "Power: " << power << std::endl;
    std::cout << "Buy Price: " << buyPrice << std::endl;
    std::cout << "Attack Mode: " << static_cast<int>(attackMode) << std::endl;
}