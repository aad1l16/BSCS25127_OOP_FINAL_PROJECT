#pragma once
#include "String.h"
#include "Storage.h"
#include "Doctor.h"
#include "User.h"
#include <ctime>

class Doctor;

class Patient : public User {
	int age;
	double outstandingBill;
	String medicalHistory;
public:
	Patient();
	Patient(String, String, String, String, int, bool, int, double, String);
	Patient(const Patient&);
	Patient& operator=(const Patient&);
	void add_outstanding_balance(double);
	int get_age();
	double get_outstanding_bill();
	String get_medical_history();
	void show_menu() override;
	String serialize() override;
	void view_medical_history();
	void view_appointments(Storage<Appointment>&);
	void book_appointment(Storage<Doctor> &, Storage<Appointment>&);
	void cancel_appointment(Storage<Appointment>&);
	void pay_outstanding_dues();
	void add_medical_record(const String&, const String&);
};