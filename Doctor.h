#pragma once
#include "String.h"
#include "User.h"
#include "Storage.h"
#include "Appointment.h"
#include "Patient.h"

class Patient;

class Doctor : public User {
private:
	String specialization;
	double consultationFee;
	int shift;
public:
	Doctor();
	Doctor(String, String, String, String, int, bool, String, double, int);
	Doctor(const Doctor&);
	Doctor& operator=(const Doctor&);
	String get_specialization();
	double get_consultation_fee();
	int get_shift();
	String get_shift_string();
	void show_menu() override;
	String serialize() override;
	void view_appointments(Storage<Appointment>&);
	void diagnose_patient(Storage<Appointment>&, Storage<Patient>&);
};