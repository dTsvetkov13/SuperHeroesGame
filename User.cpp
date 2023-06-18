#include "User.h"

User::User() {}

User::User(const MyString& name, const MyString& email, const MyString& username, const MyString& password, UserRole role)
{
	_names = name;
	_email = email;
	_userName = username;
	_password = password;
	_role = role;
}

void User::setNames(const MyString& name)
{
	_names = name;
}

void User::setEmail(const MyString& email)
{
	_email = email;
}

void User::setUserName(const MyString& userName)
{
	_userName = userName;
}

void User::setPassword(const MyString& password)
{
	_password = password;
}

void User::setRole(UserRole role)
{
	_role = role;
}

UserRole User::getRole() const
{
	return _role;
}

const MyString& User::getUserName() const
{
	return _userName;
}

const MyString& User::getPassword() const
{
	return _password;
}

const MyString& User::getNames() const
{
	return _names;
}

const MyString& User::getEmail() const
{
	return _email;
}