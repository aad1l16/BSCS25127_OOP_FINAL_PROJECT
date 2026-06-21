#define _CRT_SECURE_NO_WARNINGS
#include "Patient.h"
#include "HospitalSystem.h"

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

void Patient::add_outstanding_balance(double amt) {
	this->outstandingBill += amt;
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
	std::cout << "==================================================\n";
	std::cout << "PATIENT DASHBOARD | " << this->get_user_name() << "\n";
	std::cout << "==================================================\n";
	std::cout << "1. View Appointment\n";
	std::cout << "2. Book an Appointment\n";
	std::cout << "3. Cancel an Appointment\n";
	std::cout << "4. View Medical History\n";
	std::cout << "5. Pay Outstanding Dues\n";
	std::cout << "6. Change Password\n";
	std::cout << "7. Exit / Logout\n";
	std::cout << "==================================================\n";
	std::cout << "Enter your choice: ";
}

String Patient::serialize() {
	return this->UserID + "," + this->name + "," + this->passwordHash + "," + this->role + "," + this->UserID.itos(this->attempts) + "," + this->UserID.itos(this->locked) + "," + this->UserID.itos(this->age) + "," + this->UserID.dtos(this->outstandingBill) + "," + this->medicalHistory;
}

void Patient::view_medical_history() {
	std::cout << "==================================================\n";
	std::cout << "          MEDICAL HISTORY LOG | " << this->get_user_name() << "\n";
	std::cout << "==================================================\n";

	if (this->medicalHistory.empty()) {
		std::cout << "\nNo medical records found on file for this patient.\n";
	}
	else {
		int ct = 0;
		String* medHis = this->medicalHistory.split('|', ct);
		for (int i = 0; i < ct; i++) {
			std::cout << medHis[i] << std::endl;
		}
		//std::cout << this->medicalHistory << std::endl;
	}
	std::cin.ignore(1000, '\n');
	std::cout << "\nPress any key to exit.";
	std::cin.get();
	system("cls");
}

void Patient::view_appointments(Storage<Appointment>& appt_store) {
	std::cin.ignore(1000, '\n');
	std::cout << "==================================================\n";
	std::cout << "               PENDING APPOINTMENTS               \n";
	std::cout << "==================================================\n\n";
	int ct = appt_store.get_count(), tempCt = 0;
	for (int i = 0; i < ct; i++) {
		Appointment& temp = appt_store.get_at(i);
		if (this->UserID == temp.get_patient_id() && temp.get_status() == "Pending") {
			std::cout << temp.get_user_id() << " " << temp.get_patient_id() << " " << temp.get_doctor_id() << " " << temp.get_date() << " " << temp.get_time() << std::endl;
			tempCt++;
		}
	}
	if (tempCt == 0) {
		std::cout << "No Pending Appointments.\n";
	}
	tempCt = 0;
	std::cout << "\n==================================================\n";
	std::cout << "               COMPLETED APPOINTMENTS               \n";
	std::cout << "==================================================\n\n";
	for (int i = 0; i < ct; i++) {
		Appointment& temp = appt_store.get_at(i);
		if (this->UserID == temp.get_patient_id() && temp.get_status() == "Completed") {
			std::cout << temp.get_user_id() << " " << temp.get_patient_id() << " " << temp.get_doctor_id() << " " << temp.get_date() << " " << temp.get_time() << std::endl;
			tempCt++;
		}
	}
	if (tempCt == 0) {
		std::cout << "No Completed Appointments.\n";
	}
	tempCt = 0;
	std::cout << "\n==================================================\n";
	std::cout << "               CANCELLED APPOINTMENTS               \n";
	std::cout << "==================================================\n\n";
	for (int i = 0; i < ct; i++) {
		Appointment& temp = appt_store.get_at(i);
		if (this->UserID == temp.get_patient_id() && temp.get_status() == "Cancelled") {
			std::cout << temp.get_user_id() << " " << temp.get_patient_id() << " " << temp.get_doctor_id() << " " << temp.get_date() << " " << temp.get_time() << std::endl;
			tempCt++;
		}
	}
	if (tempCt == 0) {
		std::cout << "No Cancelled Appointments.\n";
	}
	std::cout << "\nPress any key to exit.";
	std::cin.get();
	system("cls");
}

void Patient::book_appointment(Storage<Doctor>& dr_store, Storage<Appointment>& appt_store) {
	std::cout << "==================================================\n";
	std::cout << "                BOOK APPOINTMENT               \n";
	std::cout << "==================================================\n";
	std::cout << "--------------------------------------------------\n";
	std::cout << "               AVAILABLE DOCTORS               \n";
	std::cout << "--------------------------------------------------\n\n";
	
	std::cin.ignore(1000, '\n');

	int ct = dr_store.get_count();

	if (ct == 0) {
		std::cout << "No doctors registered in the system.\n";
		std::cout << "\nPress any key to exit.";
		std::cin.get();
		system("cls");
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
		system("cls");
		return;
	}

	Doctor* tempDoc = dr_store.find_ptr(docID);

	if (tempDoc == nullptr) {
		std::cout << "\nDoctor not found. Appointment Scheduling Failed.\n";
		std::cout << "\nPress any key to exit.";
		std::cin.get();
		system("cls");
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

		std::cout << "\nEnter Date for Booking (YYYY-MM-DD, or '0' to exit) : ";
		std::cin >> date;
		date = date.trim();

		if (date == "0") {
			system("cls");
			return;
		}

		if (date < currentDate) {
			system("cls");
			std::cout << "==================================================\n";
			std::cout << "                BOOK APPOINTMENT               \n";
			std::cout << "==================================================\n";
			std::cout << "--------------------------------------------------\n";
			std::cout << "               AVAILABLE DOCTORS               \n";
			std::cout << "--------------------------------------------------\n\n";
			for (int i = 0; i < ct; i++) {
				Doctor& doc = dr_store.get_at(i);
				std::cout << "ID : " << doc.get_user_id() << " | Name : " << doc.get_user_name() << " | Dept : " << doc.get_specialization() << " | Shift : " << doc.get_shift_string() << " | Fee : " << doc.get_consultation_fee() << std::endl;
			}
			std::cout << "\nEnter the Doctor ID you wish to book with (or '0' to cancel): " << docID << std::endl;
			std::cout << "\nError : Cannot book an appointment in the past! Today is " << currentDate << ". Please try again.\n";
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
			system("cls");
			std::cout << "==================================================\n";
			std::cout << "                BOOK APPOINTMENT               \n";
			std::cout << "==================================================\n";
			std::cout << "--------------------------------------------------\n";
			std::cout << "               AVAILABLE DOCTORS               \n";
			std::cout << "--------------------------------------------------\n\n";
			for (int i = 0; i < ct; i++) {
				Doctor& doc = dr_store.get_at(i);
				std::cout << "ID : " << doc.get_user_id() << " | Name : " << doc.get_user_name() << " | Dept : " << doc.get_specialization() << " | Shift : " << doc.get_shift_string() << " | Fee : " << doc.get_consultation_fee() << std::endl;
			}
			std::cout << "\nEnter the Doctor ID you wish to book with (or '0' to cancel): " << docID << std::endl;
			std::cout << "\nError : Dr " << tempDoc->get_user_name() << " already has a booking for the " << tempShift << " on " << date << ". Try another date.\n";
 		}

	} while (isSlotOccup || isPastDate);

	Appointment newAppt(apptID, this->UserID, tempDoc->get_user_id(), date, tempShift, "Pending");
	appt_store.add(newAppt);

	std::cout << "==================================================\n";
	std::cout << "Appointment successfully registered!\n";
	std::cout << "Generated Appointment ID : " << apptID << "\n";
	std::cout << "Confirmed with Doctor   : Dr. " << tempDoc->get_user_name() << "\n";
	std::cout << "Assigned Working Shift   : " << tempShift << "\n";
	std::cout << "==================================================\n";
	std::cout << "\nPress any key to exit.";
	std::cin.get();
	system("cls");
}

void Patient::cancel_appointment(Storage<Appointment>& appt_store) {
	std::cout << "==================================================\n";
	std::cout << "                CANCEL APPOINTMENT               \n";
	std::cout << "==================================================\n";
	std::cout << "--------------------------------------------------\n";
	std::cout << "               CURRENT APPOINTMENTS               \n";
	std::cout << "--------------------------------------------------\n\n";
	std::cin.ignore(1000, '\n');
	int ct = appt_store.get_count(), currentUserCount = 0;
	for (int i = 0; i < ct; i++) {
		Appointment& tempAppt = appt_store.get_at(i);
		if (this->UserID == tempAppt.get_patient_id()) {
			std::cout << "Appointment ID: " << tempAppt.get_user_id() << " | Date: " << tempAppt.get_date() << " | Status: " << tempAppt.get_status() << std::endl;
			currentUserCount++;
		}
	}
	if (currentUserCount == 0) {
		std::cout << "\nYou have no scheduled appointments.\n\n";
		std::cout << "\nPress any key to exit.";
		std::cin.get();
		system("cls");
		return;
	}
	String ID;
	Appointment* ptr = nullptr;
	while (true) {
		std::cout << "\nEnter Appointment ID to cancel (or '0' to exit) : ";
		std::cin >> ID;
		ID = ID.trim();
		if (ID == "0") {
			system("cls");
			return;
		}
		if (!HospitalSystem::is_valid_id(ID, "APT_")) {
			system("cls");
			std::cout << "==================================================\n";
			std::cout << "                CANCEL APPOINTMENT               \n";
			std::cout << "==================================================\n";
			std::cout << "--------------------------------------------------\n";
			std::cout << "               CURRENT APPOINTMENTS               \n";
			std::cout << "--------------------------------------------------\n\n";
			for (int i = 0; i < ct; i++) {
				Appointment& tempAppt = appt_store.get_at(i);
				if (this->UserID == tempAppt.get_patient_id()) {
					std::cout << "Appointment ID: " << tempAppt.get_user_id() << " | Date: " << tempAppt.get_date() << " | Status: " << tempAppt.get_status() << std::endl;
				}
			}
			std::cout << "\nError : Invalid ID entered. Format MUST be APT_XX.\n";
			continue;
		}
		ptr = appt_store.find_ptr(ID);
		if (ptr == nullptr) {
			system("cls");
			std::cout << "==================================================\n";
			std::cout << "                CANCEL APPOINTMENT               \n";
			std::cout << "==================================================\n";
			std::cout << "--------------------------------------------------\n";
			std::cout << "               CURRENT APPOINTMENTS               \n";
			std::cout << "--------------------------------------------------\n\n";
			for (int i = 0; i < ct; i++) {
				Appointment& tempAppt = appt_store.get_at(i);
				if (this->UserID == tempAppt.get_patient_id()) {
					std::cout << "Appointment ID: " << tempAppt.get_user_id() << " | Date: " << tempAppt.get_date() << " | Status: " << tempAppt.get_status() << std::endl;
				}
			}
			std::cout << "\nError : Appointment ID not found.\n";
			continue;
		}
		if (ptr->get_patient_id() != this->UserID) {
			system("cls");
			std::cout << "==================================================\n";
			std::cout << "                CANCEL APPOINTMENT               \n";
			std::cout << "==================================================\n";
			std::cout << "--------------------------------------------------\n";
			std::cout << "               CURRENT APPOINTMENTS               \n";
			std::cout << "--------------------------------------------------\n\n";
			for (int i = 0; i < ct; i++) {
				Appointment& tempAppt = appt_store.get_at(i);
				if (this->UserID == tempAppt.get_patient_id()) {
					std::cout << "Appointment ID: " << tempAppt.get_user_id() << " | Date: " << tempAppt.get_date() << " | Status: " << tempAppt.get_status() << std::endl;
				}
			}
			std::cout << "\nError : This appointment does not belong to you.\n";
			ptr = nullptr;
			continue;
		}
		if (ptr->get_status() == "Cancelled") {
			system("cls");
			std::cout << "==================================================\n";
			std::cout << "                CANCEL APPOINTMENT               \n";
			std::cout << "==================================================\n";
			std::cout << "--------------------------------------------------\n";
			std::cout << "               CURRENT APPOINTMENTS               \n";
			std::cout << "--------------------------------------------------\n\n";
			for (int i = 0; i < ct; i++) {
				Appointment& tempAppt = appt_store.get_at(i);
				if (this->UserID == tempAppt.get_patient_id()) {
					std::cout << "Appointment ID: " << tempAppt.get_user_id() << " | Date: " << tempAppt.get_date() << " | Status: " << tempAppt.get_status() << std::endl;
				}
			}
			std::cout << "\nError : This appointment is already cancelled.\n";
			continue;
		}
		if (ptr->get_status() == "Completed") {
			system("cls");
			std::cout << "==================================================\n";
			std::cout << "                CANCEL APPOINTMENT               \n";
			std::cout << "==================================================\n";
			std::cout << "--------------------------------------------------\n";
			std::cout << "               CURRENT APPOINTMENTS               \n";
			std::cout << "--------------------------------------------------\n\n";
			for (int i = 0; i < ct; i++) {
				Appointment& tempAppt = appt_store.get_at(i);
				if (this->UserID == tempAppt.get_patient_id()) {
					std::cout << "Appointment ID: " << tempAppt.get_user_id() << " | Date: " << tempAppt.get_date() << " | Status: " << tempAppt.get_status() << std::endl;
				}
			}
			std::cout << "\nError : Cannot cancel appointment already fulfilled.\n";
			continue;
		}
		break;
	}
	ptr->update_status("Cancelled");
	std::cout << "Appointment " << ID << " successfully cancelled.\n";
	std::cout << "\nPress any key to exit.";
	std::cin.get();
	system("cls");
}

void Patient::pay_outstanding_dues() {
	std::cout << "==================================================\n";
	std::cout << "                    CLEAR DUES                    \n";
	std::cout << "==================================================\n\n";
	std::cout << "Current outstanding balance : " << this->outstandingBill << std::endl;
	
	std::cin.ignore(1000, '\n');

	if (this->outstandingBill == 0.0) {
		std::cout << "\nYou have no outstanding dues.\n";
		std::cout << "\nPress any key to exit.";
		std::cin.get();
		system("cls");
		return;
	}

	double amt = 0.0;
	while (true) {
		std::cout << "\nEnter payment amount (Enter '0' to exit) : ";
		std::cin >> amt;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			system("cls");
			std::cout << "==================================================\n";
			std::cout << "                    CLEAR DUES                    \n";
			std::cout << "==================================================\n\n";
			std::cout << "Current outstanding balance : " << this->outstandingBill << std::endl;
			std::cout << "\nEnter a decimal value.\n";
			continue;
		}
		if (amt == 0.0) {
			std::cout << "\nPayment transaction cancelled.\n";
			std::cout << "\nPress any key to exit.";
			std::cin.get();
			system("cls");
			return;
		}
		if (amt < 0.0) {
			system("cls");
			std::cout << "==================================================\n";
			std::cout << "                    CLEAR DUES                    \n";
			std::cout << "==================================================\n\n";
			std::cout << "Current outstanding balance : " << this->outstandingBill << std::endl;
			std::cout << "\nPayment cannot be negative!\n";
			continue;
		}
		if (amt > this->outstandingBill) {
			system("cls");
			std::cout << "==================================================\n";
			std::cout << "                    CLEAR DUES                    \n";
			std::cout << "==================================================\n\n";
			std::cout << "Current outstanding balance : " << this->outstandingBill << std::endl;
			std::cout << "\nPayment cannot exceed your total dues of $" << this->outstandingBill << "\n";
			continue;
		}
		break;
	}
	this->outstandingBill -= amt;
	std::cout << "Transaction Successful.\nSuccessfully processed payment of : $" << amt << "\nRemaining outstanding balance : $" << this->outstandingBill << std::endl;
	std::cin.ignore(1000, '\n');
	std::cout << "\nPress any key to exit.";
	std::cin.get();
	system("cls");
}

void Patient::add_medical_record(const String& date, const String& newNotes) {
	this->medicalHistory += "|";
	this->medicalHistory += date;
	this->medicalHistory += " ";
	this->medicalHistory += newNotes;
}