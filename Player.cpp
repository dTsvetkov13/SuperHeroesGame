#include "Player.h"
#include "Game.h";

Player::Player()
	: Player("", "") {}

Player::Player(const MyString& username, const MyString& password)
	: Player("", username, password) {}

Player::Player(const MyString& name, const MyString& username, const MyString& password)
	: Player(name, "", username, password) {}


Player::Player(const MyString& name, const MyString& email, const MyString& username, const MyString& password)
	: User(name, email, username, password, UserRole::Player)
{
	this->money = Game::getInstance().getConfig().startingMoney;
	this->timeLogged = 0;
}

double Player::getBalance() const
{
	return this->money;
}

const Vector<SuperHero>& Player::getSuperHeroes() const
{
	return heroes;
}

const SuperHero& Player::getSuperHero(const MyString& heroName) const
{
	for (int i = 0; i < heroes.getSize(); i++)
	{
		if (heroes[i].getHeroName() == heroName)
		{
			return heroes[i];
		}
	}

	//TODO: This should be with return value, not exception
	throw std::out_of_range("");
}

void Player::changeSuperHeroAtackMode(const MyString& heroName, HeroAttackMode mode)
{
	if (mode == HeroAttackMode::None) return;

	for (int i = 0; i < heroes.getSize(); i++)
	{
		if (heroes[i].getHeroName() == heroName)
		{
			heroes[i].setAttackMode(mode);
		}
	}
}

void Player::addSuperHero(const SuperHero& hero)
{
	this->heroes.pushBack(hero);
	this->heroes[this->heroes.getSize() - 1].setAttackMode(HeroAttackMode::Attack);
}

void Player::addSuperHero(SuperHero&& hero)
{
	hero.setAttackMode(HeroAttackMode::Attack);
	this->heroes.pushBack(std::move(hero));
}

int Player::getSuperHeroIndex(const MyString& heroName) const
{
	for (int i = 0; i < heroes.getSize(); i++)
	{
		if (heroes[i].getHeroName() == heroName)
		{
			return i;
		}
	}

	return -1;
}

bool Player::removeHero(const MyString& heroName)
{
	int index = getSuperHeroIndex(heroName);

	if (index < 0)
	{
		return false;
	}

	this->heroes.popAt(index);
	return true;
}

void Player::addMoney(double value)
{
	money += value;

	if (money < 0) money = 0;
}

std::ifstream& operator>>(std::ifstream& ifs, Player& player)
{
	MyString temp;

	ifs >> temp;
	player.setUserName(temp);

	ifs >> temp;
	ifs >> temp;

	player.setNames(temp);

	ifs >> temp;

	if (temp != "!&")
	{
		player.setNames(player.getNames() + temp);

		ifs >> temp;
	}

	ifs >> temp;
	player.setPassword(temp);

	ifs >> temp;
	player.setEmail(temp);

	ifs >> player.money;

	return ifs;
}