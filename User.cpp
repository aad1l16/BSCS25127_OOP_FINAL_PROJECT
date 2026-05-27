#include "User.h"

String User::get_user_id() {
	return this->UserID;
}

String User::get_user_name() {
	return this->name;
}

String User::get_user_role() {
	return this->role;
}

User::User(String id, String n, String p, String r) : UserID{ id }, name{ n }, passwordHash{ p }, role{ r } {}

User::User(const User& u) : UserID{ u.UserID }, name{ u.name }, passwordHash{ u.passwordHash }, role{ u.role } {}

void User::operator=(const User& u) {
	this->UserID = u.UserID;
	this->name = u.name;
	this->passwordHash = u.passwordHash;
	this->role = u.role;
}

bool User::authenticate(String pass) {
	if (this->passwordHash == pass) return true;
	return false;
}

void User::display_info() {
	std::cout << this->UserID << " " << this->name << " " << this->role;
}

