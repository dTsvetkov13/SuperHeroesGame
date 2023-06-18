#include "Validator.h"

const size_t Validator::MAX_USERNAME_LENGTH = 16;

bool Validator::isLower(char c)
{
	return 'a' <= c && c <= 'z';
}

bool Validator::isUpper(char c)
{
	return 'A' <= c && c <= 'Z';
}

bool Validator::isDigit(char c)
{
	return '0' <= c && c <= '9';
}

bool Validator::validateUsername(const MyString& username)
{
	if (username.length() > MAX_USERNAME_LENGTH)
	{
		return false;
	}

	for (int i = 0; i < username.length(); i++)
	{
		if (!isLower(username[i]))
		{
			return false;
		}
	}

	return true;
}

bool Validator::validatePassword(const MyString& password)
{
	bool hasLower = false, hasDigit = false, hasUpper = false;

	for (int i = 0; i < password.length(); i++)
	{
		hasLower = hasLower || isLower(password[i]);
		hasDigit = hasDigit || isDigit(password[i]);
		hasUpper = hasUpper || isUpper(password[i]);
	}

	return (hasUpper && hasLower && hasDigit);
}