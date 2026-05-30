#pragma once
#include "String.h"
#include "User.h"
#include "Storage.h"
#include "Appointment.h"
#include "Patient.h"

class Doctor : public User {
private:
	String specialization;
	double consultationFee;
public:
	Doctor();
	Doctor(String, String, String, String, int, bool, String, double);
	Doctor(const Doctor&);
	Doctor& operator=(const Doctor&);
	void show_menu() override;
	String serialize() override;
	void view_appointments(Storage<Appointment>&);
	void diagnose_patient(Storage<Appointment>&, Storage<Patient>&);
};