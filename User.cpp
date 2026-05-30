#include "User.h"

String User::get_user_id() {
	return this->UserID;
}

String User::get_user_name() {
	return this->name;
}

String User::get_password() {
	return this->passwordHash;
}

String User::get_user_role() {
	return this->role;
}

int User::get_attempts() {
	return this->attempts;
}

bool User::is_locked() {
	return this->locked;
}

User::User() : UserID{ "UNINITIALIZED" }, name{ "" }, passwordHash{ "" }, role{ "" }, attempts{ 0 }, locked{ false } {}

User::User(String id, String n, String p, String r, int a, bool l) : UserID{ id }, name{ n }, passwordHash{ p }, role{ r }, attempts{ a }, locked{ l } {}

User::User(const User& u) : UserID{ u.UserID }, name{ u.name }, passwordHash{ u.passwordHash }, role{ u.role }, attempts{ u.attempts }, locked{ u.locked } {}

User& User::operator=(const User& u) {
	this->UserID = u.UserID;
	this->name = u.name;
	this->passwordHash = u.passwordHash;
	this->role = u.role;
	this->attempts = u.attempts;
	this->locked = u.locked;
	return *this;
}

bool User::authenticate(String pass) {
	if (this->passwordHash == pass) return true;
	return false;
}

void User::display_info() {
	std::cout << this->UserID << " " << this->name << " " << this->role;
}

void User::change_password(String newPass) {
	this->passwordHash = newPass;
}

void User::set_name(String newName) {
	this->name = newName;
}