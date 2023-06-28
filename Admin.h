#pragma once

#include "User.h";

#include <fstream>

class Admin : public User
{
private:
public:
	Admin();
	Admin(const MyString& username, const MyString& password);
	Admin(const MyString& name, const MyString& username, const MyString& password);
	Admin(const MyString&, const MyString&, const MyString&, const MyString&);

	friend std::ifstream& operator>>(std::ifstream& ifs, Admin& player);
};

