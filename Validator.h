#pragma once

#include "MyString.h";

class Validator
{
private:
	static const size_t MAX_USERNAME_LENGTH;

	static bool isLower(char c);
	static bool isUpper(char c);
	static bool isDigit(char c);

public:
	static bool validateUsername(const MyString& username);
	static bool validatePassword(const MyString& password);
};

