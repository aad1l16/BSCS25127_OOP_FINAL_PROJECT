#include "Admin.h"
#include "HospitalSystem.h"

Admin::Admin() : User(), adminLevel{""}, department{""} {}

Admin::Admin(String id, String n, String p, String r, int a, bool l, String aL, String d) : User(id, n, p, r, a, l), adminLevel{ aL }, department{ d } {}

Admin::Admin(const Admin& a) : User( a ), adminLevel{ a.adminLevel }, department{ a.department } {}

Admin& Admin::operator=(const Admin& a) {
	User::operator=(a);
	this->adminLevel = a.adminLevel;
	this->department = a.department;
	return *this;
}

String Admin::get_admin_level() {
	return this->adminLevel;
}

String Admin::get_department() {
	return this->department;
}

void Admin::show_menu() {
	std::cout << "==================================================\n";
	std::cout << "ADMIN COMMAND CENTER | Name : " << this->name << " | Department : " << this->department << "\n";
	std::cout << "==================================================\n";
	std::cout << "1. Add Doctor\n";
	std::cout << "2. Add Patient\n";
	std::cout << "3. Add Admin\n";
	std::cout << "4. Lock User\n";
	std::cout << "5. Unlock User\n";
	std::cout << "6. View All Records\n";
	std::cout << "7. Change Password\n";
	std::cout << "8. Exit\n";
	std::cout << "==================================================\n";
	std::cout << "Enter your choice: ";
}

String Admin::serialize() {
	return this->UserID + "," + this->name + "," + this->passwordHash + "," + this->role + "," + this->UserID.itos(this->attempts) + "," + this->UserID.itos(this->locked) + "," + this->adminLevel + "," + this->department;
}

void Admin::add_doctor(Storage<Doctor>& dr_store) {
	std::cin.ignore(1000, '\n');
	std::cout << "==================================================\n";
	std::cout << "               ADD DOCTOR DASHBOARD               \n";
	std::cout << "==================================================\n";

	std::cout << "--------------------------------------------------\n";
	std::cout << "               DOCTORS IN THE SYSTEM              \n";
	std::cout << "--------------------------------------------------\n";
	int ct = dr_store.get_count();
	for (int i = 0; i < ct; i++) {
		Doctor& doc = dr_store.get_at(i);
		std::cout << "ID : " << doc.get_user_id() << " | Name : " << doc.get_user_name() << std::endl;
	}
	if (ct == 0) {
		std::cout << "\nNo Doctors currently registered in the system.\n\n";
	}
	else std::cout << std::endl;
	String ID;
	Doctor* tempDoc = nullptr;
	while (true) {
		std::cout << "Enter Doctor ID to Add (Format : DOC_XX, Enter '0' to exit) : ";
		std::cin >> ID;
		ID = ID.trim();
		if (ID == "0") {
			system("cls");
			return;
		}
		if (!HospitalSystem::is_valid_id(ID, "DOC_")) {
			system("cls");
			std::cout << "==================================================\n";
			std::cout << "               ADD DOCTOR DASHBOARD               \n";
			std::cout << "==================================================\n";

			std::cout << "--------------------------------------------------\n";
			std::cout << "               DOCTORS IN THE SYSTEM              \n";
			std::cout << "--------------------------------------------------\n";
			int ct = dr_store.get_count();
			for (int i = 0; i < ct; i++) {
				Doctor& doc = dr_store.get_at(i);
				std::cout << "ID : " << doc.get_user_id() << " | Name : " << doc.get_user_name() << std::endl;
			}
			if (ct == 0) {
				std::cout << "\nNo Doctors currently registered in the system.\n";
			}
			std::cout << "\nError : Invalid ID Format!\n\n";
			continue;
		}
		tempDoc = dr_store.find_ptr(ID);
		if (tempDoc != nullptr) {
			system("cls");
			std::cout << "==================================================\n";
			std::cout << "               ADD DOCTOR DASHBOARD               \n";
			std::cout << "==================================================\n";

			std::cout << "--------------------------------------------------\n";
			std::cout << "               DOCTORS IN THE SYSTEM              \n";
			std::cout << "--------------------------------------------------\n";
			int ct = dr_store.get_count();
			for (int i = 0; i < ct; i++) {
				Doctor& doc = dr_store.get_at(i);
				std::cout << "ID : " << doc.get_user_id() << " | Name : " << doc.get_user_name() << std::endl;
			}
			if (ct == 0) {
				std::cout << "\nNo Doctors currently registered in the system.\n";
			}
			std::cout << "\nError : Doctor ID already exists in system, Try a different ID.\n\n";
			continue;
		}
		break;
	}
	String name, pass, spec;
	double cF;
	int shiftInt;
	std::cout << "Enter Doctor Name : ";
	std::cin >> name;
	std::cout << "Enter a Temporary Password : ";
	std::cin >> pass;
	pass = pass.trim();
	std::cout << "Enter Specialization : ";
	std::cin >> spec;
	spec = spec.trim();
	std::cout << "Enter a Consultation Fee : ";
	std::cin >> cF;
	do {
		std::cout << "Enter a assigned working shift (1 for (Morning)/ 2 for (Evening)) : ";
		std::cin >> shiftInt;
		if (shiftInt != 1 && shiftInt != 2) std::cout << "Invalid input. Try Again.\n";
	} while (shiftInt != 1 && shiftInt != 2);
	dr_store.add(Doctor(ID, name, HospitalSystem::hash_password(pass), "Doctor", 0, false, spec, cF, shiftInt));
	std::cout << "\nSUCCESS Doctor " << name << " successfully registered in the system!\n";
	
	std::cin.ignore(1000, '\n');
	std::cout << "\nPress any key to exit.";
	std::cin.get();
	system("cls");
}

void Admin::add_patient(Storage<Patient>& pat_store) {
	std::cin.ignore(1000, '\n');
	std::cout << "==================================================\n";
	std::cout << "               ADD PATIENT DASHBOARD               \n";
	std::cout << "==================================================\n";

	std::cout << "--------------------------------------------------\n";
	std::cout << "               PATIENTS IN THE SYSTEM              \n";
	std::cout << "--------------------------------------------------\n";
	int ct = pat_store.get_count();
	for (int i = 0; i < ct; i++) {
		Patient& pat = pat_store.get_at(i);
		std::cout << "ID : " << pat.get_user_id() << " | Name : " << pat.get_user_name() << std::endl;
	}
	if (ct == 0) {
		std::cout << "\nNo Patients currently registered in the system.\n\n";
	}
	else std::cout << std::endl;
	String ID;
	Patient* tempPat = nullptr;
	while (true) {
		std::cout << "Enter Patient ID to Add (Format : PAT_XX, Enter '0' to exit) : ";
		std::cin >> ID;
		ID = ID.trim();
		if (ID == "0") {
			system("cls");
			return;
		}
		if (!HospitalSystem::is_valid_id(ID, "PAT_")) {
			system("cls");
			std::cout << "==================================================\n";
			std::cout << "               ADD PATIENT DASHBOARD               \n";
			std::cout << "==================================================\n";

			std::cout << "--------------------------------------------------\n";
			std::cout << "               PATIENTS IN THE SYSTEM              \n";
			std::cout << "--------------------------------------------------\n";
			int ct = pat_store.get_count();
			for (int i = 0; i < ct; i++) {
				Patient& pat = pat_store.get_at(i);
				std::cout << "ID : " << pat.get_user_id() << " | Name : " << pat.get_user_name() << std::endl;
			}
			if (ct == 0) {
				std::cout << "\nNo Patients currently registered in the system.\n";
			}
			std::cout << "\nError : Invalid ID Format!\n\n";
			continue;
		}
		tempPat = pat_store.find_ptr(ID);
		if (tempPat != nullptr) {
			system("cls");
			std::cout << "==================================================\n";
			std::cout << "               ADD PATIENT DASHBOARD               \n";
			std::cout << "==================================================\n";

			std::cout << "--------------------------------------------------\n";
			std::cout << "               PATIENTS IN THE SYSTEM              \n";
			std::cout << "--------------------------------------------------\n";
			int ct = pat_store.get_count();
			for (int i = 0; i < ct; i++) {
				Patient& pat = pat_store.get_at(i);
				std::cout << "ID : " << pat.get_user_id() << " | Name : " << pat.get_user_name() << std::endl;
			}
			if (ct == 0) {
				std::cout << "\nNo Patients currently registered in the system.\n";
			}
			std::cout << "\nError : Patient ID already exists in system, Try a different ID.\n\n";
			continue;
		}
		break;
	}
	String name, pass;
	int age;
	std::cout << "Enter Patient Name : ";
	std::cin >> name;
	std::cout << "Enter a Temporary Password : ";
	std::cin >> pass;
	pass = pass.trim();
	std::cout << "Enter Patient Age : ";
	std::cin >> age;
	pat_store.add(Patient(ID, name, HospitalSystem::hash_password(pass), "Patient", 0, false, age, 0.0, ""));
	std::cout << "\nSUCCESS Patient " << name << " successfully registered in the system!\n";
	
	std::cin.ignore(1000, '\n');
	std::cout << "\nPress any key to exit.";
	std::cin.get();
	system("cls");
}

void Admin::add_admin(Storage<Admin>& adm_store) {
	std::cin.ignore(1000, '\n');
	if (this->adminLevel != "SuperAdmin") {
		std::cout << "Access Denied! Only Super Admins can add admins.\n";
		std::cout << "\nPress any key to exit.";
		std::cin.get();
		system("cls");
		return;
	}
	std::cout << "==================================================\n";
	std::cout << "               ADD ADMIN DASHBOARD               \n";
	std::cout << "==================================================\n";
	std::cout << "--------------------------------------------------\n";
	std::cout << "               ADMINS IN THE SYSTEM              \n";
	std::cout << "--------------------------------------------------\n";
	int ct = adm_store.get_count();
	for (int i = 0; i < ct; i++) {
		Admin& adm = adm_store.get_at(i);
		std::cout << "ID : " << adm.get_user_id() << " | Name : " << adm.get_user_name() << std::endl;
	}
	if (ct == 0) {
		std::cout << "\nNo Admins currently registered in the system.\n\n";
	}
	else std::cout << std::endl;
	String ID;
	Admin* tempAdm = nullptr;
	while (true) {
		std::cout << "Enter Admin ID to Add (Format : ADM_XX, Enter '0' to exit) : ";
		std::cin >> ID;
		ID = ID.trim();
		if (ID == "0") {
			system("cls");
			return;
		}
		if (!HospitalSystem::is_valid_id(ID, "ADM_")) {
			system("cls");
			std::cout << "==================================================\n";
			std::cout << "               ADD ADMIN DASHBOARD               \n";
			std::cout << "==================================================\n";

			std::cout << "--------------------------------------------------\n";
			std::cout << "               ADMINS IN THE SYSTEM              \n";
			std::cout << "--------------------------------------------------\n";
			int ct = adm_store.get_count();
			for (int i = 0; i < ct; i++) {
				Admin& adm = adm_store.get_at(i);
				std::cout << "ID : " << adm.get_user_id() << " | Name : " << adm.get_user_name() << std::endl;
			}
			if (ct == 0) {
				std::cout << "\nNo Admins currently registered in the system.\n";
			}
			std::cout << "\nError : Invalid ID Format!\n\n";
			continue;
		}
		tempAdm = adm_store.find_ptr(ID);
		if (tempAdm != nullptr) {
			system("cls");
			std::cout << "==================================================\n";
			std::cout << "               ADD ADMIN DASHBOARD               \n";
			std::cout << "==================================================\n";

			std::cout << "--------------------------------------------------\n";
			std::cout << "               ADMINS IN THE SYSTEM              \n";
			std::cout << "--------------------------------------------------\n";
			int ct = adm_store.get_count();
			for (int i = 0; i < ct; i++) {
				Admin& adm = adm_store.get_at(i);
				std::cout << "ID : " << adm.get_user_id() << " | Name : " << adm.get_user_name() << std::endl;
			}
			if (ct == 0) {
				std::cout << "\nNo Admins currently registered in the system.\n";
			}
			std::cout << "\nError : Admin ID already exists in system, Try a different ID.\n\n";
			continue;
		}
		break;
	}
	String name, pass, level, dept;
	std::cout << "Enter Admin Name : ";
	std::cin >> name;
	name = name.trim();
	std::cout << "Enter a Temporary Password : ";
	std::cin >> pass;
	pass = pass.trim();
	std::cout << "Enter a Admin Level : ";
	std::cin >> level;
	level = level.trim();
	std::cout << "Enter a Department : ";
	std::cin >> dept;
	dept = dept.trim();

	adm_store.add(Admin(ID, name, HospitalSystem::hash_password(pass), "Admin", 0, false, level, dept));
	std::cout << "\nSUCCESS Admin " << name << " successfully registered in the system!\n";
	std::cout << "\nPress any key to exit.";
	std::cin.get();
	system("cls");
}

void Admin::unlock_user(Storage<Doctor>& dr_store, Storage<Patient>& pat_store, Storage<Admin>& adm_store) {
	if (this->adminLevel != "SuperAdmin") {
		std::cout << "Access Denied! Only Super Admins can override security locks.\n";
		std::cout << "\nPress any key to exit.";
		std::cin.get();
		system("cls");
		return;
	}

	std::cin.ignore(1000, '\n');
	std::cout << "==================================================\n";
	std::cout << "           ACCOUNT UNLOCK CONTROL CENTRE      \n";
	std::cout << "==================================================\n";

	std::cout << "--------------------------------------------------\n";
	std::cout << "                  LOCKED ACCOUNTS              \n";
	std::cout << "--------------------------------------------------\n";
	int ct = dr_store.get_count();
	for (int i = 0; i < ct; i++) {
		Doctor& doc = dr_store.get_at(i);
		if(doc.is_locked()) std::cout << "ID : " << doc.get_user_id() << " | Name : " << doc.get_user_name() << std::endl;
	}
	ct = pat_store.get_count();
	for (int i = 0; i < ct; i++) {
		Patient& pat = pat_store.get_at(i);
		if (pat.is_locked()) std::cout << "ID : " << pat.get_user_id() << " | Name : " << pat.get_user_name() << std::endl;
	}
	ct = adm_store.get_count();
	for (int i = 0; i < ct; i++) {
		Admin& adm = adm_store.get_at(i);
		if (adm.is_locked()) std::cout << "ID : " << adm.get_user_id() << " | Name : " << adm.get_user_name() << std::endl;
	}

	String ID;
	std::cout << "\nEnter ID of locked account to restore (Enter '0' to exit) : ";
	std::cin >> ID;
	ID = ID.trim();
	
	if (ID == "0") {
		system("cls");
		return;
	}

	User* lockedAccount = nullptr;

	Patient* tempPat = pat_store.find_ptr(ID);
	Doctor* tempDr = dr_store.find_ptr(ID);
	Admin* tempAdm = adm_store.find_ptr(ID);

	if (tempPat != nullptr) lockedAccount = tempPat;
	if (tempDr != nullptr) lockedAccount = tempDr;
	if (tempAdm != nullptr) lockedAccount = tempAdm;

	if (lockedAccount == nullptr) {
		std::cout << "Invalid ID entered. Does not exist in system.\n";
		std::cout << "\nPress any key to exit.";
		std::cin.get();
		system("cls");
		return;
	}

	if (!lockedAccount->is_locked()) {
		std::cout << "Account entered is already active and unlocked.\n";
		std::cout << "\nPress any key to exit.";
		std::cin.get();
		system("cls");
		return;
	}

	lockedAccount->set_locked(false);
	lockedAccount->reset_attempts();
	std::cout << "Account Unlocked Successfully!\n";

	std::cout << "\nPress any key to exit.";
	std::cin.get();
	system("cls");
}

void Admin::lock_user(Storage<Doctor>& dr_store, Storage<Patient>& pat_store, Storage<Admin>& adm_store) {
	if (this->adminLevel != "SuperAdmin") {
		std::cout << "Access Denied! Only Super Admins can lock accounts.\n";
		std::cout << "\nPress any key to exit.";
		std::cin.get();
		system("cls");
		return;
	}

	std::cin.ignore(1000, '\n');
	std::cout << "==================================================\n";
	std::cout << "           ACCOUNT LOCK CONTROL CENTRE      \n";
	std::cout << "==================================================\n";

	std::cout << "--------------------------------------------------\n";
	std::cout << "                UNLOCKED ACCOUNTS              \n";
	std::cout << "--------------------------------------------------\n";
	int ct = dr_store.get_count();
	for (int i = 0; i < ct; i++) {
		Doctor& doc = dr_store.get_at(i);
		if (!doc.is_locked()) std::cout << "ID : " << doc.get_user_id() << " | Name : " << doc.get_user_name() << std::endl;
	}
	ct = pat_store.get_count();
	for (int i = 0; i < ct; i++) {
		Patient& pat = pat_store.get_at(i);
		if (!pat.is_locked()) std::cout << "ID : " << pat.get_user_id() << " | Name : " << pat.get_user_name() << std::endl;
	}
	ct = adm_store.get_count();
	for (int i = 0; i < ct; i++) {
		Admin& adm = adm_store.get_at(i);
		if (!adm.is_locked() && adm.get_user_id() != this->UserID && adm.get_admin_level() != "SuperAdmin") std::cout << "ID : " << adm.get_user_id() << " | Name : " << adm.get_user_name() << " | Admin Level : " << adm.get_admin_level() << std::endl;
	}

	String ID;
	std::cout << "\nEnter ID of account to lock (Enter '0' to exit) : ";
	std::cin >> ID;
	ID = ID.trim();

	if (ID == "0") {
		system("cls");
		return;
	}

	User* Account = nullptr;

	Patient* tempPat = pat_store.find_ptr(ID);
	Doctor* tempDr = dr_store.find_ptr(ID);
	Admin* tempAdm = adm_store.find_ptr(ID);

	if (tempPat != nullptr) Account = tempPat;
	if (tempDr != nullptr) Account = tempDr;
	if (tempAdm != nullptr) Account = tempAdm;

	if (Account == nullptr) {
		std::cout << "Invalid ID entered. Does not exist in system.\n";
		std::cout << "\nPress any key to exit.";
		std::cin.get();
		system("cls");
		return;
	}

	if (Account->get_user_id() == this->UserID) {
		std::cout << "Cannot lock your own account!\n";
		std::cout << "\nPress any key to exit.";
		std::cin.get();
		system("cls");
		return;
	}

	if (Account->get_user_role() == "Admin" && static_cast<Admin*>(Account)->get_admin_level() == "SuperAdmin") {
		std::cout << "Security Exception: You cannot lock a SuperAdmin account!\n";
		std::cout << "\nPress any key to exit.";
		std::cin.get();
		system("cls");
		return;
	}

	if (Account->is_locked()) {
		std::cout << "Account entered is already locked.\n";
		std::cout << "\nPress any key to exit.";
		std::cin.get();
		system("cls");
		return;
	}

	Account->set_locked(true);
	std::cout << "Account Locked Successfully!\n";
	std::cout << "\nPress any key to exit.";
	std::cin.get();
	system("cls");
}

void Admin::view_all_records(Storage<Doctor>& dr_store, Storage<Patient>& pat_store, Storage<Admin>& adm_store, Storage<Appointment>& appt_store) {
	
	std::cin.ignore(1000, '\n');

	std::cout << "==================================================\n";
	std::cout << "\n     Hospital System Master Register Audit       \n";
	std::cout << "==================================================\n";

	std::cout << "[1] ACTIVE CLINICAL STAFF\n";
	std::cout << "---------------------------------------------------\n";
	int ct = dr_store.get_count();
	if (ct == 0) {
		std::cout << "No Clinical Staff registered in the System.\n";
	}
	else {
		for (int i = 0; i < ct; i++) {
			Doctor& doc = dr_store.get_at(i);
			std::cout << "ID : " << doc.get_user_id() << " | Name : " << doc.get_user_name() << " | Specialization : " << doc.get_specialization() << " | Shift : " << doc.get_shift_string() << " | Fee : " << doc.get_consultation_fee() << " | Account State : ";
			if (doc.is_locked()) std::cout << "Locked\n";
			else std::cout << "Unlocked\n";
		}
	}

	std::cout << "[2] REGISTERED PATIENTS\n";
	std::cout << "---------------------------------------------------\n";
	ct = pat_store.get_count();
	if (ct == 0) {
		std::cout << "No Patients registered in the System.\n";
	}
	else {
		for (int i = 0; i < ct; i++) {
			Patient& pat = pat_store.get_at(i);
			std::cout << "ID : " << pat.get_user_id() << " | Name : " << pat.get_user_name() << " | Age : " << pat.get_age() << " | Outstanding Dues : " << pat.get_outstanding_bill() << " | Account State : ";
			if (pat.is_locked()) std::cout << "Locked\n";
			else std::cout << "Unlocked\n";
		}
	}

	std::cout << "[3] REGISTERED ADMINS\n";
	std::cout << "---------------------------------------------------\n";
	ct = adm_store.get_count();
	if (ct == 0) {
		std::cout << "No Admins registered in the System.\n";
	}
	else {
		for (int i = 0; i < ct; i++) {
			Admin& adm = adm_store.get_at(i);
			std::cout << "ID : " << adm.get_user_id() << " | Name : " << adm.get_user_name() << " | Level : " << adm.get_admin_level() << " | Department : " << adm.get_department() << " | Account State : ";
			if (adm.is_locked()) std::cout << "Locked\n";
			else std::cout << "Unlocked\n";
		}
	}

	std::cout << "[4] APPOINTMENTS SCHEDULED\n";
	std::cout << "---------------------------------------------------\n";
	ct = appt_store.get_count();
	if (ct == 0) {
		std::cout << "No Appointments Scheduled in the System.\n";
	}
	else {
		for (int i = 0; i < ct; i++) {
			Appointment& appt = appt_store.get_at(i);
			std::cout << "Appointment ID : " << appt.get_user_id() << " | Patient ID : " << appt.get_patient_id() << " | Doctor ID : " << appt.get_doctor_id() << " | Date : " << appt.get_date() << " | Slot : " << appt.get_time() << " | Status : " << appt.get_status() << std::endl;
		}
	}

	std::cout << "\nPress any key to exit.";
	std::cin.get();
	system("cls");
}