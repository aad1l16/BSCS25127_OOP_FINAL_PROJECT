#pragma once
#include "String.h"
#include "Admin.h"
#include "Doctor.h"
#include "Patient.h"
#include "Appointment.h"
#include "Storage.h"
#include <fstream>
#include <iostream>


class HospitalSystem {
private:
	Storage<Patient> pats;
	Storage<Doctor> docs;
	Storage<Admin> admins;
	Storage<Appointment> appts;
	User* currentUser;

	HospitalSystem();
	~HospitalSystem();
	User* find_user_anywhere(const String&);
	void handle_patient_flow(Patient*);
	void handle_doctor_flow(Doctor*);
	void handle_admin_flow(Admin*);
	void prompt_change_password(User*);
public:
	HospitalSystem(const HospitalSystem&) = delete;
	HospitalSystem& operator=(const HospitalSystem&) = delete;
	static HospitalSystem& get_instance();
	static bool is_valid_id(const String&, const String&);
	static String hash_password(const String&);
	void load_all_data();
	void save_all_data();
	int execute_login();
	void start_system_loop();
};