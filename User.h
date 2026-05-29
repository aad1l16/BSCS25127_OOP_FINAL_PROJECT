#pragma once
#include "String.h"

class User {
protected:
	String UserID;
	String name;
	String passwordHash;
	String role;
	int attempts;
	bool locked;

	String get_user_id();
	String get_user_name();
	String get_password();
	String get_user_role();
	int get_attempts();
	bool is_locked();
public:
	User();
	User(String, String, String, String, int, bool);
	User(const User&);
	void operator=(const User&);
	bool authenticate(String);
	virtual void display_info();
	void change_password(String);
	void set_name(String);
	virtual void show_menu() = 0;
	virtual String serialize() = 0;
};