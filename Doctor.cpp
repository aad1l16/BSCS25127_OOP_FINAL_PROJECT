#include "Doctor.h"

Doctor::Doctor() : User(), specialization{ "" }, consultationFee{ 0.0 } {}

Doctor::Doctor(String id, String n, String p, String r, int a, bool l, String spec, double cF, int shiftTime) : User(id, n, p, r, a, l), specialization{ spec }, consultationFee{ cF }, shift{ shiftTime } {}

Doctor::Doctor(const Doctor& d) : User(d.UserID, d.name, d.passwordHash, d.role, d.attempts, d.locked), specialization{ d.specialization }, consultationFee{ d.consultationFee }, shift{ d.shift } {}

Doctor& Doctor::operator=(const Doctor& d) {
	User::operator=(d);
	this->specialization = d.specialization;
	this->consultationFee = d.consultationFee;
	this->shift = d.shift;
	return *this;
}

String Doctor::get_specialization() {
	return this->specialization;
}

double Doctor::get_consultation_fee() {
	return this->consultationFee;
}

int Doctor::get_shift() {
	return this->shift;
}

String Doctor::get_shift_string() {
	if (this->shift == 1) {
		return "Morning";
	}
	else if (this->shift == 2) return "Evening";
	else return "Unknown";
}

void Doctor::show_menu() {
	std::cout << "\n======================================\n";
	std::cout << "WELCOME DR. " << this->get_user_name() << "\n";
	std::cout << "======================================\n";
	std::cout << "1. View Assigned Appointments\n";
	std::cout << "2. Diagnose Patient\n";
	std::cout << "3. Exit / Logout\n";
	std::cout << "======================================\n";
	std::cout << "Enter your choice: ";
}

String Doctor::serialize() {
	return this->UserID + "," + this->name + "," + this->passwordHash + "," + this->role + "," + this->UserID.itos(this->attempts) + "," + this->UserID.itos(this->locked) + "," + this->specialization + "," + this->UserID.dtos(this->consultationFee) + "," + this->UserID.itos(this->shift);
}

void Doctor::view_appointments(Storage<Appointment>& appt_store) {
	int ct = appt_store.get_count();
	for (int i = 0; i < ct; i++) {
		if (this->UserID == appt_store.get_at(i).get_doctor_id()) {
			std::cout << appt_store.get_at(i).get_user_id() << " " << appt_store.get_at(i).get_patient_id() << " " << appt_store.get_at(i).get_doctor_id() << " " << appt_store.get_at(i).get_date() << " " << appt_store.get_at(i).get_time() << " " << appt_store.get_at(i).get_status() << std::endl;
		}
	}
}

void Doctor::diagnose_patient(Storage<Appointment>& appt_store, Storage<Patient>& pat_store) {
	view_appointments(appt_store);
	Appointment* tempAppt = nullptr;
	String tempStr;
	do {
		std::cout << "Enter Appointment ID ( or type '0' to cancel ): ";
		std::cin >> tempStr;
		tempStr = tempStr.trim();

		if (tempStr == "0") {
			std::cout << "Diagnosis cancelled returning to main menu...\n";
			return;
		}

		tempAppt = appt_store.find_ptr(tempStr);
		if (tempAppt == nullptr) {
			std::cout << "Invalid ID. Try Again.\n";
			continue;
		}
		if (tempAppt->get_doctor_id() != this->UserID) {
			std::cout << "This appointment does not belong to you. Try Again.\n";
			tempAppt = nullptr;
			continue;
		}
	} while (tempAppt == nullptr);
	tempStr.clear();
	std::cout << "Enter Notes : ";
	std::cin >> tempStr;
	Patient* tempPat = pat_store.find_ptr(tempAppt->get_patient_id());
	if (tempPat != nullptr) {
		tempPat->add_medical_record(tempAppt->get_date(), tempStr);
		tempPat = nullptr;
		tempAppt->update_status("Completed");
		tempAppt = nullptr;
		std::cout << "Diagnosis has successfully been logged.\n";
		return;
	}
	std::cout << "Patient not found in system.\n";
	tempAppt = nullptr;
	return;
}