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
	std::cout << "\n======================================\n";
	std::cout << "ADMIN COMMAND CENTER | Name : " << this->name << " | Department : " << this->department << "\n";
	std::cout << "======================================\n";
	std::cout << "1. Add Doctor\n";
	std::cout << "2. Add Patient\n";
	std::cout << "3. Add Admin\n";
	std::cout << "4. Lock User\n";
	std::cout << "5. Unlock User\n";
	std::cout << "6. View All Records\n";
	std::cout << "7. Change Password\n";
	std::cout << "8. Exit\n";
	std::cout << "======================================\n";
	std::cout << "Enter your choice: ";
}

String Admin::serialize() {
	return this->UserID + "," + this->name + "," + this->passwordHash + "," + this->role + "," + this->UserID.itos(this->attempts) + "," + this->UserID.itos(this->locked) + "," + this->adminLevel + "," + this->department;
}

void Admin::add_doctor(Storage<Doctor>& dr_store) {
	std::cout << "\n ---Add Doctor Dashboard--- \n";
	
	std::cin.ignore(1000, '\n');

	std::cout << " --- Existing Doctors in the System--- \n";
	int ct = dr_store.get_count();
	for (int i = 0; i < ct; i++) {
		Doctor& doc = dr_store.get_at(i);
		std::cout << "ID : " << doc.get_user_id() << " | Name : " << doc.get_user_name() << std::endl;
	}
	String ID;
	Doctor* tempDoc = nullptr;
	while (true) {
		std::cout << "Enter Doctor ID to Add (Format : DOC_XX, Enter '0' to exit) : ";
		std::cin >> ID;
		ID = ID.trim();
		if (ID == "0") return;
		if (!HospitalSystem::is_valid_id(ID, "DOC_")) {
			std::cout << "Error : Invalid ID Format!\n";
			continue;
		}
		tempDoc = dr_store.find_ptr(ID);
		if (tempDoc != nullptr) {
			std::cout << "Error : Doctor ID already exists in system, Try a different ID.\n";
			continue;
		}
		break;
	}
	String name, pass, spec;
	double cF;
	int shiftInt;
	std::cout << "Enter Doctor Name : ";
	std::cin >> name;
	std::cout << "Enter a temporary Password : ";
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
}

void Admin::add_patient(Storage<Patient>& pat_store) {
	std::cout << "\n ---Add Patient Dashboard--- \n";

	std::cin.ignore(1000, '\n');

	std::cout << " --- Existing Patients in the System--- \n";
	int ct = pat_store.get_count();
	for (int i = 0; i < ct; i++) {
		Patient& pat = pat_store.get_at(i);
		std::cout << "ID : " << pat.get_user_id() << " | Name : " << pat.get_user_name() << std::endl;
	}
	String ID;
	Patient* tempPat = nullptr;
	while (true) {
		std::cout << "Enter Patient ID to Add (Format : PAT_XX, Enter '0' to exit) : ";
		std::cin >> ID;
		ID = ID.trim();
		if (ID == "0") return;
		if (!HospitalSystem::is_valid_id(ID, "PAT_")) {
			std::cout << "Error : Invalid ID Format!\n";
			continue;
		}
		tempPat = pat_store.find_ptr(ID);
		if (tempPat != nullptr) {
			std::cout << "Error : Patient ID already exists in system, Try a different ID.\n";
			continue;
		}
		break;
	}
	String name, pass;
	int age;
	std::cout << "Enter Patient Name : ";
	std::cin >> name;
	std::cout << "Enter a temporary Password : ";
	std::cin >> pass;
	pass = pass.trim();
	std::cout << "Enter Patient Age : ";
	std::cin >> age;
	pat_store.add(Patient(ID, name, HospitalSystem::hash_password(pass), "Patient", 0, false, age, 0.0, ""));
	std::cout << "\nSUCCESS Patient " << name << " successfully registered in the system!\n";
}

void Admin::add_admin(Storage<Admin>& adm_store) {
	if (this->adminLevel != "SuperAdmin") {
		std::cout << "Access Denied! Only Super Admins can add admins.\n";
		return;
	}
	std::cout << "\n ---Add Admin Dashboard--- \n";

	std::cin.ignore(1000, '\n');

	std::cout << " --- Existing Admins in the System--- \n";
	int ct = adm_store.get_count();
	for (int i = 0; i < ct; i++) {
		Admin& adm = adm_store.get_at(i);
		std::cout << "ID : " << adm.get_user_id() << " | Name : " << adm.get_user_name() << std::endl;
	}
	String ID;
	Admin* tempAdm = nullptr;
	while (true) {
		std::cout << "Enter Admin ID to Add (Format : ADM_XX, Enter '0' to exit) : ";
		std::cin >> ID;
		ID = ID.trim();
		if (ID == "0") return;
		if (!HospitalSystem::is_valid_id(ID, "ADM_")) {
			std::cout << "Error : Invalid ID Format!\n";
			continue;
		}
		tempAdm = adm_store.find_ptr(ID);
		if (tempAdm != nullptr) {
			std::cout << "Error : Admin ID already exists in system, Try a different ID.\n";
			continue;
		}
		break;
	}
	String name, pass, level, dept;
	std::cout << "Enter Admin Name : ";
	std::cin >> name;
	name = name.trim();
	std::cout << "Enter a temporary Password : ";
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
}

void Admin::unlock_user(Storage<Doctor>& dr_store, Storage<Patient>& pat_store, Storage<Admin>& adm_store) {
	if (this->adminLevel != "SuperAdmin") {
		std::cout << "Access Denied! Only Super Admins can override security locks.\n";
		return;
	}
	std::cout << "\n ---Account Unlock Control Centre--- \n";

	std::cin.ignore(1000, '\n');

	std::cout << "\n --- Locked Accounts --- \n";
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
	
	if (ID == "0") return;

	User* lockedAccount = nullptr;

	Patient* tempPat = pat_store.find_ptr(ID);
	Doctor* tempDr = dr_store.find_ptr(ID);
	Admin* tempAdm = adm_store.find_ptr(ID);

	if (tempPat != nullptr) lockedAccount = tempPat;
	if (tempDr != nullptr) lockedAccount = tempDr;
	if (tempAdm != nullptr) lockedAccount = tempAdm;

	if (lockedAccount == nullptr) {
		std::cout << "Invalid ID entered. Does not exist in system.\n";
		return;
	}

	if (!lockedAccount->is_locked()) {
		std::cout << "Account entered is already active and unlocked.\n";
		return;
	}

	lockedAccount->set_locked(false);
	lockedAccount->reset_attempts();
	std::cout << "Account Unlocked Successfully!\n";
}

void Admin::lock_user(Storage<Doctor>& dr_store, Storage<Patient>& pat_store, Storage<Admin>& adm_store) {
	if (this->adminLevel != "SuperAdmin") {
		std::cout << "Access Denied! Only Super Admins can lock accounts.\n";
		return;
	}
	std::cout << "\n ---Account Lock Control Centre--- \n";

	std::cin.ignore(1000, '\n');

	std::cout << "\n --- Unlocked Accounts --- \n";
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

	if (ID == "0") return;
	
	User* Account = nullptr;

	Patient* tempPat = pat_store.find_ptr(ID);
	Doctor* tempDr = dr_store.find_ptr(ID);
	Admin* tempAdm = adm_store.find_ptr(ID);

	if (tempPat != nullptr) Account = tempPat;
	if (tempDr != nullptr) Account = tempDr;
	if (tempAdm != nullptr) Account = tempAdm;

	if (Account == nullptr) {
		std::cout << "Invalid ID entered. Does not exist in system.\n";
		return;
	}

	if (Account->get_user_id() == this->UserID) {
		std::cout << "Cannot lock your own account!\n";
		return;
	}

	if (Account->get_user_role() == "Admin" && static_cast<Admin*>(Account)->get_admin_level() == "SuperAdmin") {
		std::cout << "Security Exception: You cannot lock a SuperAdmin account!\n";
		return;
	}

	if (Account->is_locked()) {
		std::cout << "Account entered is already locked.\n";
		return;
	}

	Account->set_locked(true);
	std::cout << "Account Locked Successfully!\n";
}

void Admin::view_all_records(Storage<Doctor>& dr_store, Storage<Patient>& pat_store, Storage<Admin>& adm_store, Storage<Appointment>& appt_store) {
	
	std::cin.ignore(1000, '\n');

	std::cout << "\n===================================================\n";
	std::cout << "\n       Hospital System Master Register Audit       \n";
	std::cout << "\n===================================================\n";

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

	String temp;
	std::cout << "Press [Enter] to return to Admin Menu\n";
	std::cin >> temp;
}