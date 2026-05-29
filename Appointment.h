#pragma once
#include "String.h"

class Appointment {
private:
	String appointmentID;
	String patientID;
	String doctorID;
	String dateStr;
	String timeStr;
	String status;

public:
	Appointment();
	Appointment(String, String, String, String, String, String = "Pending");
	Appointment(const Appointment&);
	void operator=(const Appointment&);
	String get_user_id();
	String get_patient_id();
	String get_doctor_id();
	String get_status();
	void update_status(const String&);
	String serialize();
};