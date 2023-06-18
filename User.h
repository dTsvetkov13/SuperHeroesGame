#pragma once
#include "MyString.h"
#include "UserRole.h"

class User
{
private:
	MyString _names;
	MyString _email;
	MyString _userName;
	MyString _password;
	UserRole _role;
public:
	User();
	User(const MyString&, const MyString&, const MyString&, const MyString&, UserRole);

	UserRole getRole() const;

	void setNames(const MyString& names);
	void setEmail(const MyString& email);
	void setUserName(const MyString& userName);
	void setPassword(const MyString& password);
	void setRole(UserRole role);

	const MyString& getUserName() const;
	const MyString& getPassword() const;
	const MyString& getNames() const;
	const MyString& getEmail() const;
};

