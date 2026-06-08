#include "Doctor.h"
#include "HospitalSystem.h"

Doctor::Doctor() : User(), specialization{ "" }, consultationFee{ 0.0 }, shift{ 0 } {}

Doctor::Doctor(String id, String n, String p, String r, int a, bool l, String spec, double cF, int shiftTime) : User(id, n, p, r, a, l), specialization{ spec }, consultationFee{ cF }, shift{ shiftTime } {}

Doctor::Doctor(const Doctor& d) : User(d), specialization{ d.specialization }, consultationFee{ d.consultationFee }, shift{ d.shift } {}

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
	std::cout << "1. View Appointments\n";
	std::cout << "2. Diagnose Patient\n";
	std::cout << "3. Change Password\n";
	std::cout << "4. Exit / Logout\n";
	std::cout << "======================================\n";
	std::cout << "Enter your choice: ";
}

String Doctor::serialize() {
	return this->UserID + "," + this->name + "," + this->passwordHash + "," + this->role + "," + this->UserID.itos(this->attempts) + "," + this->UserID.itos(this->locked) + "," + this->specialization + "," + this->UserID.dtos(this->consultationFee) + "," + this->UserID.itos(this->shift);
}

void Doctor::view_appointments(Storage<Appointment>& appt_store) {
	std::cin.ignore(1000, '\n');
	std::cout << "\n--- Pending Appointments ---\n";
	int ct = appt_store.get_count(), tempCt = 0;
	for (int i = 0; i < ct; i++) {
		Appointment& temp = appt_store.get_at(i);
		if (this->UserID == temp.get_doctor_id() && temp.get_status() == "Pending") {
			std::cout << temp.get_user_id() << " " << temp.get_patient_id() << " " << temp.get_doctor_id() << " " << temp.get_date() << " " << temp.get_time() << std::endl;
			tempCt++;
		}
	}
	if (tempCt == 0) {
		std::cout << "No Pending Appointments.\n";
	}
	tempCt = 0;
	std::cout << "\n--- Completed Appointments ---\n";
	for (int i = 0; i < ct; i++) {
		Appointment& temp = appt_store.get_at(i);
		if (this->UserID == temp.get_doctor_id() && temp.get_status() == "Completed") {
			std::cout << temp.get_user_id() << " " << temp.get_patient_id() << " " << temp.get_doctor_id() << " " << temp.get_date() << " " << temp.get_time() << std::endl;
			tempCt++;
		}
	}
	if (tempCt == 0) {
		std::cout << "No Completed Appointments.\n";
	}
	tempCt = 0;
	std::cout << "\n--- Cancelled Appointments ---\n";
	for (int i = 0; i < ct; i++) {
		Appointment& temp = appt_store.get_at(i);
		if (this->UserID == temp.get_doctor_id() && temp.get_status() == "Cancelled") {
			std::cout << temp.get_user_id() << " " << temp.get_patient_id() << " " << temp.get_doctor_id() << " " << temp.get_date() << " " << temp.get_time() << std::endl;
			tempCt++;
		}
	}
	if (tempCt == 0) {
		std::cout << "No Cancelled Appointments.\n";
	}
	String temp;
	std::cout << "Press [Enter] to return to Doctor Menu\n";
	std::cin >> temp;
}

void Doctor::diagnose_patient(Storage<Appointment>& appt_store, Storage<Patient>& pat_store) {
	std::cout << "\n--- Pending Appointments ---\n";
	int ct = appt_store.get_count();
	for (int i = 0; i < ct; i++) {
		Appointment& temp = appt_store.get_at(i);
		if (this->UserID == temp.get_doctor_id() && temp.get_status() == "Pending") {
			std::cout << temp.get_user_id() << " " << temp.get_patient_id() << " " << temp.get_doctor_id() << " " << temp.get_date() << " " << temp.get_time() << std::endl;
		}
	}
	std::cin.ignore(1000, '\n');
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
		if (!HospitalSystem::is_valid_id(tempStr, "APT_")) {
			std::cout << "Error: Invalid ID Format! Appointments must start with 'APT_'.\n\n";
			continue;
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
		if (tempAppt->get_status() == "Completed" || tempAppt->get_status() == "Cancelled") {
			std::cout << "Error: This appointment has already been " << tempAppt->get_status() << "!\n\n";
			tempAppt = nullptr;
			continue;
		}
	} while (tempAppt == nullptr);
	tempStr.clear();
	std::cout << "Enter Notes : ";
	std::cin >> tempStr;
	Patient* tempPat = pat_store.find_ptr(tempAppt->get_patient_id());
	if (tempPat != nullptr) {
		tempPat->add_medical_record(tempAppt->get_date(), tempStr + " Overseeing Diagnosis : Dr. " + this->name);
		tempPat->add_outstanding_balance(this->consultationFee);
		tempAppt->update_status("Completed");
		tempAppt = nullptr;
		std::cout << "Diagnosis has successfully been logged.\n";
		std::cout << "Consultation Fee of $" << this->consultationFee << " has been added to Patient " << tempPat->get_user_name() << "'s account balance.\n";
		tempPat = nullptr;
		return;
	}
	std::cout << "Patient not found in system.\n";
	tempAppt = nullptr;
	return;
}