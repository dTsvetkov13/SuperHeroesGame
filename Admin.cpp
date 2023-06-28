#include "Admin.h"

Admin::Admin()
	: Admin("", "") {}

Admin::Admin(const MyString& username, const MyString& password)
	: Admin("", username, password) {}

Admin::Admin(const MyString& name, const MyString& username, const MyString& password)
	: Admin(name, "", username, password) {}

Admin::Admin(const MyString& name, const MyString& email, const MyString& username, const MyString& password)
	: User(name, email, username, password, UserRole::Admin) {}

std::ifstream& operator>>(std::ifstream& ifs, Admin& player)
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

	return ifs;
}