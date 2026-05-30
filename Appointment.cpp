#include "Appointment.h"

Appointment::Appointment() : appointmentID{ "UNINITIALIZED" }, patientID{ "" }, doctorID{ "" }, dateStr{ "" }, timeStr{ "" }, status{ "Pending" } {}

Appointment::Appointment(String apptID, String patID, String docID, String date, String time, String stat) : appointmentID{ apptID }, patientID{ patID }, doctorID{ docID }, dateStr{ date }, timeStr{ time }, status{ stat } {}

Appointment::Appointment(const Appointment& a) : appointmentID{ a.appointmentID }, patientID{ a.patientID }, doctorID{ a.doctorID }, dateStr{ a.dateStr }, timeStr{ a.timeStr }, status{ a.status } {}

Appointment& Appointment::operator=(const Appointment& a) {
	this->appointmentID = a.appointmentID;
	this->patientID = a.patientID;
	this->doctorID = a.doctorID;
	this->dateStr = a.dateStr;
	this->timeStr = a.timeStr;
	this->status = a.status;
	return *this;
}

String Appointment::get_user_id() {
	return this->appointmentID;
}

String Appointment::get_patient_id() {
	return this->patientID;
}

String Appointment::get_doctor_id() {
	return this->doctorID;
}

String Appointment::get_date() {
	return this->dateStr;
}

String Appointment::get_time() {
	return this->timeStr;
}

String Appointment::get_status() {
	return this->status;
}

void Appointment::update_status(const String& next_status) {
	this->status = next_status;
}

String Appointment::serialize() {
	return this->appointmentID + "," + this->patientID + "," + this->doctorID + "," + this->dateStr + "," + this->timeStr + "," + this->status;
}