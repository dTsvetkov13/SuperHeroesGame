#pragma once

#include "User.h";

class Admin : public User
{
private:
public:
	Admin();
	Admin(const MyString& username, const MyString& password);
	Admin(const MyString& name, const MyString& username, const MyString& password);
	Admin(const MyString&, const MyString&, const MyString&, const MyString&);
};

