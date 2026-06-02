# BSCS25127_OOP_FINAL_PROJECT

Aadil Jawad Husain
BSCS25127
OOP FINAL PROJECT

This is a Hospital Management System. It is made up of 7 classes. It uses an abstract base class User from which 3 classes are derived. Admin, Doctor and Patient. All 3 use the IS-A inheritance. Each derived class has a different user experience and responsibilities.  The Appointment class is used to connect Doctor to Patients for scheduled appoinments. The Storage class is a template based class that stores the datatype its built for in a vector based format. The HospitalSystem class is the main class it owns all storage arrays, tracks who is currently logged in and controls the flow of data at start up and shut down.

At start up HospitalSystem loads data stored when program was last closed from file. If system detects no admin is created at bootup, It adds an admin by default. After that User enters their ID and Password. If ID and Password are valid User is successfully logged in. Using polymorphism the system runs specific to the type of User that is logged in. At shut down, all files are written to again to save any changes made during the excecution of the program.

String :

Custom Built String Class used throughout this project.

MyVector :

Custom Built Template Based Vector Class used throughout this project


User (Abstract Base Class) :

Imports and Uses custom built String.

Protected Attributes :

    String UserID; #This is the ID used to refer to the user across the whole program. Cannot be changed once set.
    String name; #This is the name of the User that will be use to refer to them across the whole program. Can be changed.
    String passwordHash; #This is the password of the User hashed so it is unreadable in this form. Can be changed.
    String role; #This is the User's role in the system. Cannot be changed once set.
    int attempts; #These are the User's failed attempts after which the account will be locked.
    bool locked; #Stores the current state of the account. Active/Locked.

Public Methods :

    Constructors : 
        User(); #Default Constructor, Useful when creating Storage.
        User(String, String, String, String, int, bool); #Parameterized constructor.
        User(const User&); #Copy Constructor.
    Other Methods : 
        void operator=(const User&); #Assignment Function.
        String get_user_id(); #returns UserID.
        String get_user_name(); #returns name.
        String get_password(); #returns passwordHash.
        String get_user_role(); #returns role.
        int get_attempts(); #returns attempts.
        bool is_locked(); #returns locked.
        bool authenticate(String); #Check whether password passed as arugument is same as User password.
        virtual void display_info(); #Outputs User Information, Can be overridden by derived classes to customise the information to output.
        void change_password(String); #Updates current password.
        void set_name(String); #Updates current name.
        void set_locked(bool); #Updates locked to argument.
        void increment_attempts(); #Increments attempts by 1.
        void reset_attempts(); #Resets attempts to 0.
        virtual void show_menu() = 0; #Pure Virtual Function will be defined in derived classes.
        virtual void serialize() = 0; #Pure Virtual Function will be defined in derived classes.
        virtual void deserialize(String) = 0; #Pure Virtual Function will be defined in derived classes.


Storage<T> :
Template Based Class used as a container to store and manage Objects.

Imports and Uses custom built String and Vector.

Private Attributes : 

    myVector<T> items; #Holds the Objects in a Vector.

Public Methods :

    Constructors : 
        Storage() : items(T(), 0); #Creates an empty Vector with Capacity 0 of the desired Type.
    Other Functions :
        void add(const T& item); #Adds an Object to the Vector items.
        int get_count(); #Returns the number of items currently in the Vector items.
        T& get_at(int pos) #Returns the Object at pos, if it exists.
        T* find_ptr(const String& id); #Checks the Vector items for the desired id, if it exists returns it else returns nullptr.
        void save_to_file(const char* filename); #Saves all the current Object's data to the file provided as argument.
        void clear_storage(); #Clears all Objects currently in Vector items.


Apppointment : 

Used to track Appointments Patients have with Doctors. 

Imports and Uses custom built String.

Private Attributes : 

    String appointmentID; #Unique for each appointment.
    String patientID; #ID of the patient the appoinment is for.
    String doctorID; #ID of the doctor responsible for the patient.
    String dateStr;  #Date of when the appointment is scheduled.
    String timeStr; #Time of when the appointment is scheduled.
    String status; #Status of the appointment whether it is completed or pending.

Public Methods :

    Constructors : 
        Appointment(); #Default constructor, Useful when creating store for Appointment.
        Appointment(String, String, String, String, String, String = "Pending"); #Parameterized Constructor, Status is set as Pending by Default.
        Appointment(const Appointment&); #Copy Constructor.
    Other Methods :
        void operator=(const Appointment&); #Assignment Function.
        String get_user_id(); #Returns the appointmentID, named get_user_id so it works polymorphically when Storage is created and find_ptr is called.
        String get_patient_id(); #returns patiendID.
        String get_doctor_id(); #returns doctorID.
        String get_date(); #returns dateStr;
        String get_time(); #returns timeStr;
        String get_status(); #returns status.
        void update_status(const String&); #Changes status to argument passed.
        String serialize(); #Formats data into a String in CSV format to be stored in files. Returns the String.


Doctor : 

Derived from User. Is a User in the System. Manages appointments with Patients and diagnoses them.

Imports and Uses custom built String.

Private Attributes : 

    String specialization; #The field the doctor specializes in.
    double consultationFee; #The fee the doctor charges for consultation.
    int shift; #The shift in which the doctor attends a patient(1 = Morning/ 2 = Evening).

Public Methods : 

    Constructors : 
        Doctor(); #Default constructor, Useful when creating store for Doctor.
        Doctor(String, String, String, String, int, bool, String, double); #Parameterized constructor.
        Doctor(const Doctor&); #Copy constructor.
    Other Methods :
        Doctor& operator=(const Doctor&); #Assignment Function.
        void show_menu() override; #Shows a the menu relevant for Doctor.
        String get_specialization(); #Returns specialization.
        double get_consultation_fee(); #Returns consultationFee.
        int get_shift(); #Return the shift in integer form (1/2).
        String get_shift_string(); #Returns the shift in String form(Morning/Evening).
        String serialize() override; #Returns all Doctor attributes in a single String in CSV format to be stored in files.
        void view_appointments(Storage<Appointment>&); #Displays all appointments for the current Doctor.
        void diagnose_patient(Storage<Appointment>&, Storage<Patient>&); #Allows Doctor to diagnose any patient they are responsible for.


Patient : 

Derived from User. Is a User in the System. Books appointments with doctors.

Imports and Uses custom built String.

Private Attributes : 

    int age; #Age of the patient.
    double outstandingBill; #The remaining due Patient still has to clear.
    String medicalHistory; #Patient's Medical History.

Public Methods : 

    Constructors : 
        Patient(); #Default constructor, Useful when creating store for Patient.
        Patient(String, String, String, String, int, bool, int, double, String); #Parameterized Constructor.
        Patient(const Patient&); #Copy constructor.
    Other Methods : 
        Patient& operator=(const Patient&); #Assignment Function.
        int get_age(); #Returns age.
        double get_outstanding_bill(); #Returns outstandingBill.
        String get_medical_history(); #Returns medicalHistory.
        void show_menu() override; #Shows the menu relevant for Patient.
        String serialize() override; #Returns all Patient attributes in a single String in CSV format to be stored in files.
        void view_medical_history(); #Displays the medicalHistory if it exists.
        void book_appointment(Storage<Doctor> &, Storage<Appointment>&); #Allows Patient to book an appointment.
        void pay_outstanding_dues(double); #Allows Patient to clear their dues. 
        void add_medical_record(const String&, const String&); #Function used by doctor to add notes to Patient's medicalHistory.


Admin : 

Derived from User. Is a User in the System. Manages all accounts, adding new accounts, unlocking and locking accounts.

Imports and Uses custom built String.

Private Attributes : 

    String adminLevel; #Stores what the type of the Admin is to enforce heirarchical structure.
    String department; #Which department the admin belongs to.

Public Methods :

    Constructors : 
        Admin(); #Default constructor, Useful when creating store for Admin.
        Admin(String, String, String, String, int, bool, String, String); #Parameterized Constructor
        Admin(const Admin&); #Copy Constructor
    Other Methods :
        Admin& operator=(const Admin&); #Assignment Function
        String get_admin_level(); #Returns adminLevel.
        String get_department(); #Returns department.
        void show_menu() override; #Shows the menu relevant for Admin.
        String serialize() override; #Returns all Admin attributes in a single String in CSV format to be stored in files.
        void add_doctor(Storage<Doctor>&); #Adds a new Doctor into the system.
        void add_patient(Storage<Patient>&); #Adds a new Patient into the system.
        void add_admin(Storage<Admin>&); #Adds a new Admin into the system.
        void unlock_user(Storage<Doctor>&, Storage<Patient>&, Storage<Admin>&); #Unlocks a locked account.
        void lock_user(Storage<Doctor>&, Storage<Patient>&, Storage<Admin>&); #Locks an unlocked account.
        void view_all_records(Storage<Doctor>&, Storage<Patient>&, Storage<Admin>&, Storage<Appointment>&); #Displays all users and appointments in the system.