#include "HospitalSystem.h"
#include <windows.h>

//Private Methods

HospitalSystem::HospitalSystem() : currentUser{ nullptr } {
	load_all_data();
}

HospitalSystem::~HospitalSystem() {
	save_all_data();
}

User* HospitalSystem::find_user_anywhere(const String& id) {
	if (id.Length() < 3) { return nullptr; }
	if (id[0] == 'D' && id[1] == 'O' && id[2] == 'C') return docs.find_ptr(id);
	if (id[0] == 'P' && id[1] == 'A' && id[2] == 'T') return pats.find_ptr(id);
	if (id[0] == 'A' && id[1] == 'D' && id[2] == 'M') return admins.find_ptr(id);
	return nullptr;
}

void HospitalSystem::handle_patient_flow(Patient* p) {
	int choice;
	do {
		p->show_menu();
		std::cin >> choice;
		system("cls");
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "Invalid Input. Please enter a number.\n";
			choice = 0;
			system("cls");
			continue;
		}
		switch (choice) {
		case 1: p->view_appointments(this->appts); break;
		case 2: p->book_appointment(this->docs, this->appts); break;
		case 3: p->cancel_appointment(this->appts); break;
		case 4: p->view_medical_history(); break;
		case 5: p->pay_outstanding_dues(); break;
		case 6: prompt_change_password(p); break;
		case 7: std::cout << "\nLogging out...\n"; this->currentUser = nullptr; break;
		default: std::cout << "Invalid choice! Enter a number between 1 and 4.\n"; break;
		}
	} while (choice != 7);
}

void HospitalSystem::handle_doctor_flow(Doctor* d) {
	int choice;
	do {
		d->show_menu();
		std::cin >> choice;
		system("cls");
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "Invalid Input. Please enter a number.\n";
			choice = 0;
			system("cls");
			continue;
		}
		switch (choice) {
		case 1: d->view_appointments(this->appts); break;
		case 2: d->diagnose_patient(this->appts, this->pats); break;
		case 3: prompt_change_password(d); break;
		case 4: std::cout << "\nLogging out...\n"; this->currentUser = nullptr; break;
		default: std::cout << "Invalid choice! Enter a number between 1 and 3.\n"; break;
		}
	} while (choice != 4);
}

void HospitalSystem::handle_admin_flow(Admin* a) {
	int choice;
	do {
		a->show_menu();
		std::cin >> choice;
		system("cls");
		if (std::cin.fail()) {
			std::cin.clear(); 
			std::cin.ignore(1000, '\n');
			std::cout << "Invalid Input. Please enter a number.\n";
			choice = 0;
			system("cls");
			continue;
		}
		switch (choice) {
		case 1: a->add_doctor(this->docs); break;
		case 2: a->add_patient(this->pats); break;
		case 3: { 
			String tempID = a->get_user_id();
			a->add_admin(this->admins);
			this->currentUser = find_user_anywhere(tempID);
			a = static_cast<Admin*>(this->currentUser);
			break; 
		}
		case 4: a->lock_user(this->docs, this->pats, this->admins); break;
		case 5: a->unlock_user(this->docs, this->pats, this->admins); break;
		case 6: a->view_all_records(this->docs, this->pats, this->admins, this->appts); break;
		case 7: prompt_change_password(a); break;
		case 8: std::cout << "\nLogging out...\n"; this->currentUser = nullptr; break;
		default: std::cout << "Invalid choice! Enter a number between 1 and 7.\n"; break;
		}
	} while (choice != 8);
}

void HospitalSystem::prompt_change_password(User* user) {
	system("cls");
	std::cin.ignore(1000, '\n');
	String oldPass, newPass, confirmPass;
	std::cout << "==================================================\n";
	std::cout << "               PASSWORD SECURITY PORTAL             \n";
	std::cout << "==================================================\n\n";

	std::cout << "Enter your current password (or '0' to cancel) : ";
	std::cin >> oldPass;
	oldPass = oldPass.trim();
	if (oldPass == "0") {
		system("cls");
		return;
	}
	if (hash_password(oldPass) != user->get_password()) {
		std::cout << "\nError : Incorrect current password. Access Denied.\n";
		std::cout << "\nPress any key to exit.";
		std::cin.get();
		system("cls");
		return;
	}
	system("cls");
	std::cout << "==================================================\n";
	std::cout << "               PASSWORD SECURITY PORTAL             \n";
	std::cout << "==================================================\n";
	while (true) {
		std::cout << "\nEnter new password (or '0' to cancel): ";
		std::cin >> newPass;
		newPass = newPass.trim();
		if (newPass.Length() == 0) {
			system("cls");
			std::cout << "==================================================\n";
			std::cout << "               PASSWORD SECURITY PORTAL             \n";
			std::cout << "==================================================\n\n";
			std::cout << "Error : Password cannot be blank.\n";
			continue;
		}
		if (newPass == "0") {
			system("cls");
			return;
		}
		std::cout << "\nConfirm new password : ";
		std::cin >> confirmPass;
		confirmPass = confirmPass.trim();
		if (newPass != confirmPass) {
			system("cls");
			std::cout << "==================================================\n";
			std::cout << "               PASSWORD SECURITY PORTAL             \n";
			std::cout << "==================================================\n\n";
			std::cout << "Error : Passwords do not match.\n";
			continue;
		}
		break;
	}

	user->change_password(hash_password(newPass));

	std::cout << "Password changed successfully.\n";
	std::cout << "\nPress any key to exit.";
	std::cin.get();
	system("cls");
}
//Public Methods

HospitalSystem& HospitalSystem::get_instance() {
	static HospitalSystem instance;
	return instance;
}

bool HospitalSystem::is_valid_id(const String& id, const String& check) {
	if (id.Length() <= check.Length()) return false;

	for (int i = 0; i < check.Length(); i++) {
		if (id[i] != check[i]) return false;
	}

	for (int i = check.Length(); i < id.Length(); i++) {
		if (id[i] < '0' || id[i] > '9') return false;
	}

	return true;
}

String HospitalSystem::hash_password(const String& pass) {
	if (pass.Length() == 0) return "EMPTY HASH";
	unsigned int hash = 19;
	for (int i = 0; i < pass.Length(); i++) {
		hash = (hash * 37) + pass[i];
	}

	hash = hash % 1000000007;
	String helper;
	return helper.itos(hash);
}

void HospitalSystem::load_all_data() {
	std::ifstream fin;
	String temp;
	fin.clear();
	fin.open("doctors.txt");
	if(!fin) {
		std::cout << "doctors.txt file not found. Auto-Generating a doctors.txt file.\n";
		std::ofstream fout("doctors.txt");
		fout.close();
	}
	else {
		while (fin >> temp) {
			temp = temp.trim();
			if (temp.Length() == 0) continue;
			int ct = 0;
			String* tempPtr = temp.split(',', ct);
			if (ct == 9) {
				docs.add(Doctor(tempPtr[0], tempPtr[1], tempPtr[2], tempPtr[3], tempPtr[4].stoi(), tempPtr[5] == "1", tempPtr[6], tempPtr[7].stod(), tempPtr[8].stoi()));
			}
			delete[] tempPtr;
			
		}
		fin.close();
	}
	fin.clear();
	fin.open("patients.txt");
	if (!fin) {
		std::cout << "patients.txt file not found. Auto-Generating a patients.txt file.\n";
		std::ofstream fout("patients.txt");
		fout.close();
	}
	else {
		while (fin >> temp) {
			temp = temp.trim();
			if (temp.Length() == 0) continue;
			int ct = 0;
			String* tempPtr = temp.split(',', ct);
			if (ct == 9) {
				pats.add(Patient(tempPtr[0], tempPtr[1], tempPtr[2], tempPtr[3], tempPtr[4].stoi(), tempPtr[5] == "1", tempPtr[6].stoi(), tempPtr[7].stod(), tempPtr[8]));
			}
			delete[] tempPtr;
		}
		fin.close();
	}
	fin.clear();
	fin.open("admins.txt");
	if (!fin) {
		std::cout << "admins.txt file not found. Auto-Generating a admins.txt file.\n";
		std::ofstream fout("admins.txt");
		fout << "ADM_01,System Admin," << hash_password("adminPass") << ",Admin,0,0,SuperAdmin,IT Security\n";
		fout.close();
		admins.add(Admin("ADM_01", "System Admin", hash_password("adminPass"), "Admin", 0, false, "SuperAdmin", "IT Security"));
	}
	else {
		while (fin >> temp) {
			temp = temp.trim();
			if (temp.Length() == 0) continue;
			int ct = 0;
			String* tempPtr = temp.split(',', ct);
			if (ct == 8) {
				admins.add(Admin(tempPtr[0], tempPtr[1], tempPtr[2], tempPtr[3], tempPtr[4].stoi(), tempPtr[5] == "1", tempPtr[6], tempPtr[7]));
			}
			delete[] tempPtr;
		}
		fin.close();
	}
	fin.clear();
	fin.open("appointments.txt");
	if (!fin) {
		std::cout << "appointments.txt file not found. Auto-Generating a appointments.txt file.\n";
		std::ofstream fout("appointments.txt");
		fout.close();
	}
	else {
		while (fin >> temp) {
			temp = temp.trim();
			if (temp.Length() == 0) continue;
			int ct = 0;
			String* tempPtr = temp.split(',', ct);
			if (ct == 6) {
				appts.add(Appointment(tempPtr[0], tempPtr[1], tempPtr[2], tempPtr[3], tempPtr[4], tempPtr[5]));
			}
			delete[] tempPtr;
		}
		fin.close();
	}
}

void HospitalSystem::save_all_data() {
	std::ofstream fout;
	int ct;
	fout.open("doctors.txt");
	if (!fout) {
		std::cout << "doctors.txt could not be opened\n";
	}
	else {
		ct = docs.get_count();
		for (int i = 0; i < ct; i++) {
			fout << docs.get_at(i).serialize() << std::endl;
		}
		fout.close();
	}
	fout.clear();
	fout.open("patients.txt");
	if (!fout) {
		std::cout << "patients.txt could not be opened\n";
	}
	else {
		ct = pats.get_count();
		for (int i = 0; i < ct; i++) {
			fout << pats.get_at(i).serialize() << std::endl;
		}
		fout.close();
	}
	fout.clear();
	fout.open("admins.txt");
	if (!fout) {
		std::cout << "admins.txt could not be opened\n";
	}
	else {
		ct = admins.get_count();
		for (int i = 0; i < ct; i++) {
			fout << admins.get_at(i).serialize() << std::endl;
		}
		fout.close();
	}
	fout.clear();
	fout.open("appointments.txt");
	if (!fout) {
		std::cout << "appointments.txt could not be opened\n";
	}
	else {
		ct = appts.get_count();
		for (int i = 0; i < ct; i++) {
			fout << appts.get_at(i).serialize() << std::endl;
		}
		fout.close();
	}
}

int HospitalSystem::execute_login() {
	system("cls");
	std::cout << "==================================================\n";
	std::cout << "                   SIGN IN PORTAL             \n";
	std::cout << "==================================================\n\n";
	String ID, pass;
	User* temp = nullptr;
	while (true) {
		std::cout << "Enter ID (Enter '0' to exit) : ";
		std::cin >> ID;
		ID = ID.trim();
		if (ID == "0") {
			std::cout << "Exiting login terminal...\n";
			return 1;
		}
		temp = find_user_anywhere(ID);
		if (temp == nullptr) {
			system("cls");
			std::cout << "==================================================\n";
			std::cout << "                   SIGN IN PORTAL             \n";
			std::cout << "==================================================\n\n";
			std::cout << "ID does not exist!\n\n";
			continue;
		}
		else if (temp->is_locked()) {
			system("cls");
			std::cout << "==================================================\n";
			std::cout << "                   SIGN IN PORTAL             \n";
			std::cout << "==================================================\n\n";
			std::cout << "Account is LOCKED! Contact Admin to get it unlocked!\n\n";
			continue;
		}
		else break;
	}
	while (temp->get_attempts() < 3) {
		std::cout << "\nEnter password : ";
		std::cin >> pass;
		pass = pass.trim();
		if (hash_password(pass) != temp->get_password()) {
			temp->increment_attempts();
			if (temp->get_attempts() == 3) {
				if (temp->get_user_id() == "ADM_01") {
					std::cout << "\n[CRITICAL] Root SuperAdmin password threshold reached. Core access preserved.\n";
					temp->reset_attempts();
					continue;
				}
				system("cls");
				std::cout << "\nEntered the incorrect password too many times. Account LOCKED!\nContact an Admin to get it unlocked!\n";
				temp->set_locked(true);
				return 2;
			}
			std::cout << "\nInvalid password entered! Remaining Attempts : " << 3 - temp->get_attempts() << "\n";
			continue;
		}
		else {
			std::cout << "Successful Login!\n";
			temp->reset_attempts();
			this->currentUser = temp;
			return 0;
		}
	}
	return 4;
}

void HospitalSystem::start_system_loop() {
	while (true) {
		int i = execute_login();
		system("cls");
		if (i == 0) {
			String id = this->currentUser->get_user_id();
			if (id[0] == 'P' && id[1] == 'A' && id[2] == 'T') {
				Patient* patPtr = static_cast<Patient*>(this->currentUser);
				handle_patient_flow(patPtr);
			}
			else if (id[0] == 'D' && id[1] == 'O' && id[2] == 'C') {
				Doctor* docPtr = static_cast<Doctor*>(this->currentUser);
				handle_doctor_flow(docPtr);
			}
			else if (id[0] == 'A' && id[1] == 'D' && id[2] == 'M') {
				Admin* admPtr = static_cast<Admin*>(this->currentUser);
				handle_admin_flow(admPtr);
			}
		}
		else if (i == 1) {
			break;
		}
		std::cin.ignore(1000, '\n');
	}

	std::cout << "\nProgram Suspended. Safely Exiting...\n";
}