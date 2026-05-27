#pragma once
#include "String.h"

class User {
protected:
	String UserID;
	String name;
	String passwordHash;
	String role;
	
	String get_user_id();
	String get_user_name();
	String get_user_role();
public:
	User(String, String, String, String);
	User(const User&);
	void operator=(const User&);
	bool authenticate(String);
	virtual void display_info();
	virtual void show_menu() = 0;
	virtual void serialize() = 0;
	virtual void deserialize(String) = 0;
};