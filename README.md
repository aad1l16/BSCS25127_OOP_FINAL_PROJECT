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

Imports and uses custom built String

Protected Attributes :

    String UserID : This is the ID used to refer to the user across the whole program. Cannot be changed once set.
    String name : This is the name of the User that will be use to refer to them across the whole program. Can be changed.
    String passwordHash : This is the password of the User hashed so it is unreadable in this form. Can be changed.
    String role : This is the User's role in the system. Cannot be changed once set.
    int attempts : These are the User's failed attempts after which the account will be locked.
    bool locked : Stores the current state of the account. Active/Locked.

Protected Functions :

    String get_user_id() : returns UserID.
    String get_user_name() : returns name.
    String get_password() : returns passwordHash.
    String get_user_role() : returns role.
    int get_attempts() : returns attempts.
    bool is_locked() : returns locked.

Public Functions :

    Constructors : 
        User(String, String, String, String, int, bool) : Parameterized constructor.
        User(const User&) : Copy Constructor.
    Other Functions : 
        void operator=(const User&) : Assignment Function.
        bool authenticate(String);
        virtual void display_info() : Outputs User Information, Can be overridden by derived classes to customise the information to output.
        void change_password(String) : Updates current password.
        void set_name(String) : Updates current name.
        virtual void show_menu() = 0 : Pure Virtual Function will be defined in derived classes.
        virtual void serialize() = 0 : Pure Virtual Function will be defined in derived classes.
        virtual void deserialize(String) = 0 : Pure Virtual Function will be defined in derived classes.
