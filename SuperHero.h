#pragma once

#include "MyString.h";

#include <fstream>

enum class PowerType { Fire, Earth, Water };

enum class HeroAttackMode { None, Defense, Attack };

class SuperHero 
{
private:
    MyString name;
    MyString surname;
    MyString heroName;
    PowerType powerType;
    double power;
    double buyPrice;
    HeroAttackMode attackMode;

public:
    SuperHero();
    SuperHero(const MyString& n, const MyString& s, const MyString& hn,
        PowerType pt, double p, double bp, HeroAttackMode am);

    MyString getName() const;
    MyString getSurname() const;
    MyString getHeroName() const;
    PowerType getPowerType() const;
    double getPower() const;
    double getBuyPrice() const;
    HeroAttackMode getAttackMode() const;

    void setName(const MyString& n);
    void setSurname(const MyString& s);
    void setHeroName(const MyString& hn);
    void setPowerType(PowerType pt);
    void setPower(double p);
    void setBuyPrice(double bp);
    void setAttackMode(HeroAttackMode am);

    void displayInfo() const;

    friend std::ifstream& operator>>(std::ifstream& ifs, SuperHero& player);
};
