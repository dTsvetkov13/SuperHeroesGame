#pragma once

#include "MyString.h";

class GameMenu
{
private:
	void startMenuOperation(const MyString& oper) const;
	void showLoggedUserMenu() const;
	void loggedUserMenuOperation(const MyString&) const;

	void playerOperations(const MyString& operation) const;
	void adminOperations(const MyString& operation) const;

	void addPlayerFromMenu() const;
	bool addHero() const;
	void addHeroesWhenMarketEmpty() const;
	void gameConfig() const;
public:
	GameMenu();

	void menu() const;
};

