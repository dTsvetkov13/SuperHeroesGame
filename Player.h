#pragma once

#include "User.h";
#include "SuperHero.h";
#include "Vector.hpp";

#include <fstream>

class Player : public User
{
private:
	double money;
	Vector<SuperHero> heroes;
	uint8_t timeLogged;
public:
	Player();
	Player(const MyString& username, const MyString& password);
	Player(const MyString& name, const MyString& username, const MyString& password);
	Player(const MyString& name, const MyString& email, const MyString& username, const MyString& password);

	double getBalance() const;
	const Vector<SuperHero>& getSuperHeroes() const;
	const SuperHero& getSuperHero(const MyString& heroName) const;
	int getSuperHeroIndex(const MyString& heroName) const;
	void changeSuperHeroAtackMode(const MyString& heroName, HeroAttackMode mode);

	void addSuperHero(const SuperHero&);
	void addSuperHero(SuperHero&&);

	bool removeHero(const MyString& heroName);

	void addMoney(double value);

	inline void logged() { timeLogged++; }
	inline uint8_t getTimeLogged() const { return timeLogged; }

	friend std::ifstream& operator>>(std::ifstream& ifs, Player& player);
};