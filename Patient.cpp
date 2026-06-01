#define _CRT_SECURE_NO_WARNINGS
#include "Patient.h"

Patient::Patient() : User(), age{ 0 }, outstandingBill{ 0.0 }, medicalHistory{ "" } {}

Patient::Patient(String id, String n, String p, String r, int a, bool l, int _age, double oB, String mH) : User(id, n, p, r, a, l), age{ _age }, outstandingBill{ oB }, medicalHistory{ mH } {}

Patient::Patient(const Patient& p) : User(p), age{ p.age }, outstandingBill{ p.outstandingBill }, medicalHistory{ p.medicalHistory } {}

Patient& Patient::operator=(const Patient& p) {
	User::operator=(p);
	this->age = p.age;
	this->outstandingBill = p.outstandingBill;
	this->medicalHistory = p.medicalHistory;
	return *this;
}

int Patient::get_age() {
	return this->age;
}

double Patient::get_outstanding_bill() {
	return this->outstandingBill;
}

String Patient::get_medical_history() {
	return this->medicalHistory;
}

void Patient::show_menu() {
	std::cout << "\n======================================\n";
	std::cout << "PATIENT DASHBOARD | " << this->get_user_name() << "\n";
	std::cout << "======================================\n";
	std::cout << "1. Book an Appointment\n";
	std::cout << "2. View Medical History\n";
	std::cout << "3. Pay Outstanding Dues\n";
	std::cout << "4. Exit / Logout\n";
	std::cout << "======================================\n";
	std::cout << "Enter your choice: ";
}

String Patient::serialize() {
	return this->UserID + "," + this->name + "," + this->passwordHash + "," + this->role + "," + this->UserID.itos(this->attempts) + "," + this->UserID.itos(this->locked) + "," + this->UserID.itos(this->age) + "," + this->UserID.dtos(this->outstandingBill) + "," + this->medicalHistory;
}

void Patient::view_medical_history() {
	std::cout << "\n==================================================\n";
	std::cout << "          MEDICAL HISTORY LOG | " << this->get_user_name() << "\n";
	std::cout << "==================================================\n";

	if (this->medicalHistory.empty()) {
		std::cout << "No medical records found on file for this patient.\n";
	}
	else {
		std::cout << this->medicalHistory << std::endl;
	}
}

void Patient::book_appointment(Storage<Doctor>& dr_store, Storage<Appointment>& appt_store) {
	std::cout << "\n ---Available Doctors--- \n";

	int ct = dr_store.get_count();

	if (ct == 0) {
		std::cout << "No doctors registered in the system.\n";
		return;
	}

	for (int i = 0; i < ct; i++) {
		Doctor& doc = dr_store.get_at(i);
		std::cout << "ID : " << doc.get_user_id() << " | Name : " << doc.get_user_name() << " | Dept : " << doc.get_specialization() << " | Shift : " << doc.get_shift_string() << " | Fee : " << doc.get_consultation_fee() << std::endl;
	}

	String docID;
	std::cout << "\nEnter the Doctor ID you wish to book with (or '0' to cancel): ";
	std::cin >> docID;
	docID = docID.trim();

	if (docID == "0") {
		std::cout << "Booking Cancelled :(.\n";
		return;
	}

	Doctor* tempDoc = dr_store.find_ptr(docID);

	if (tempDoc == nullptr) {
		std::cout << "Doctor not found. Appointment Scheduling Failed :(.\n";
		return;
	}

	int idx = appt_store.get_count() + 1;
	String apptID = "APT_" + this->UserID.itos(idx);

	String date, time, tempShift = tempDoc->get_shift_string();
	bool isSlotOccup, isPastDate;
	std::time_t t = std::time(nullptr);
	std::tm* now = std::localtime(&t);
	char dateArr[11];
	std::strftime(dateArr, 11, "%Y-%m-%d", now);
	String currentDate(dateArr);

	do {
		isSlotOccup = false;
		isPastDate = false;

		std::cout << "Enter Date for Booking (YYYY-MM-DD, or '0' to exit) : ";
		std::cin >> date;
		date = date.trim();

		if (date == "0") return;

		if (date < currentDate) {
			std::cout << "Error : Cannot book an appointment in the past! Today is " << currentDate << ". Please try again.\n\n";
			isPastDate = true;
			continue;
		}

		int totalAppt = appt_store.get_count();

		for (int i = 0; i < totalAppt; i++) {
			Appointment& appt = appt_store.get_at(i);
			if (appt.get_doctor_id() == tempDoc->get_user_id() && appt.get_date() == date && appt.get_time() == tempShift && appt.get_status() != "Cancelled") {
				isSlotOccup = true;
				break;
			}
		}

		if (isSlotOccup) {
			std::cout << "\nError : Dr " << tempDoc->get_user_name() << " already has a booking for the " << tempShift << " on " << date << ". Try another date.\n";
 		}

	} while (isSlotOccup || isPastDate);

	this->outstandingBill += tempDoc->get_consultation_fee();
	Appointment newAppt(apptID, this->UserID, tempDoc->get_user_id(), date, tempShift, "Pending");
	appt_store.add(newAppt);

	std::cout << "\n==================================================\n";
	std::cout << "Appointment successfully registered!\n";
	std::cout << "Generated Appointment ID : " << apptID << "\n";
	std::cout << "Confirmed with Doctor   : Dr. " << tempDoc->get_user_name() << "\n";
	std::cout << "Assigned Working Shift   : " << tempShift << "\n";
	std::cout << "Consultation Fee Added   : " << tempDoc->get_consultation_fee() << "\n";
	std::cout << "==================================================\n";
}

void Patient::pay_outstanding_dues(double amt) {
	if (amt <= 0) {
		std::cout << "Invalid Amount.\n";
		return;
	}
	if (amt > this->outstandingBill) {
		std::cout << "Payment exceeds current outstanding dues of " << this->outstandingBill << std::endl;
		return;
	}
	this->outstandingBill -= amt;
	std::cout << "Payment successful ;)! Remaining Dues : " << this->outstandingBill << std::endl;
}

void Patient::add_medical_record(const String& date, const String& newNotes) {
	this->medicalHistory += " | ";
	this->medicalHistory += date;
	this->medicalHistory += " ";
	this->medicalHistory += newNotes;
}