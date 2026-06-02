#pragma once
#include "User.h"
#include "Patient.h"
#include "Doctor.h"
#include "Appointment.h"
#include "String"

class Admin : public User {
private:
	String adminLevel;
	String department;
public:
	Admin();
	Admin(String, String, String, String, int, bool, String, String);
	Admin(const Admin&);
	Admin& operator=(const Admin&);
	String get_admin_level();
	String get_department();
	void show_menu() override;
	String serialize() override;
	void add_doctor(Storage<Doctor>&);
	void add_patient(Storage<Patient>&);
	void add_admin(Storage<Admin>&);
	void unlock_user(Storage<Doctor>&, Storage<Patient>&, Storage<Admin>&);
	void lock_user(Storage<Doctor>&, Storage<Patient>&, Storage<Admin>&);
	void view_all_records(Storage<Doctor>&, Storage<Patient>&, Storage<Admin>&, Storage<Appointment>&);
};