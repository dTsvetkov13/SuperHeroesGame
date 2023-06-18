#include "Admin.h"

Admin::Admin()
	: Admin("", "") {}

Admin::Admin(const MyString& username, const MyString& password)
	: Admin("", username, password) {}

Admin::Admin(const MyString& name, const MyString& username, const MyString& password)
	: Admin(name, "", username, password) {}

Admin::Admin(const MyString& name, const MyString& email, const MyString& username, const MyString& password)
	: User(name, email, username, password, UserRole::Admin) {}