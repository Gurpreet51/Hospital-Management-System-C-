#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// ========== Patient Class ==========
class Patient {
public:
    int id;
    string name;
    int age;
    string disease;

    void input() {
        cout << "Enter Patient ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cin.ignore();
        cout << "Enter Disease: ";
        getline(cin, disease);
    }

    string serialize() const {
        stringstream ss;
        ss << id << "," << name << "," << age << "," << disease;
        return ss.str();
    }

    void deserialize(const string& line) {
        stringstream ss(line);
        string temp;
        getline(ss, temp, ','); id = stoi(temp);
        getline(ss, name, ',');
        getline(ss, temp, ','); age = stoi(temp);
        getline(ss, disease, ',');
    }

    void display() const {
        cout << left << setw(5) << id << setw(20) << name
             << setw(5) << age << setw(15) << disease << endl;
    }
};

// ========== Doctor Class ==========
class Doctor {
public:
    int id;
    string name;
    string specialization;

    void input() {
        cout << "Enter Doctor ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Specialization: ";
        getline(cin, specialization);
    }

    string serialize() const {
        stringstream ss;
        ss << id << "," << name << "," << specialization;
        return ss.str();
    }

    void deserialize(const string& line) {
        stringstream ss(line);
        string temp;
        getline(ss, temp, ','); id = stoi(temp);
        getline(ss, name, ',');
        getline(ss, specialization, ',');
    }

    void display() const {
        cout << left << setw(5) << id << setw(20) << name
             << setw(20) << specialization << endl;
    }
};

// ========== Appointment Class ==========
class Appointment {
public:
    int id, patientId, doctorId;
    string date;

    void input() {
        cout << "Enter Appointment ID: ";
        cin >> id;
        cout << "Enter Patient ID: ";
        cin >> patientId;
        cout << "Enter Doctor ID: ";
        cin >> doctorId;
        cin.ignore();
        cout << "Enter Date (DD/MM/YYYY): ";
        getline(cin, date);
    }

    string serialize() const {
        stringstream ss;
        ss << id << "," << patientId << "," << doctorId << "," << date;
        return ss.str();
    }

    void deserialize(const string& line) {
        stringstream ss(line);
        string temp;
        getline(ss, temp, ','); id = stoi(temp);
        getline(ss, temp, ','); patientId = stoi(temp);
        getline(ss, temp, ','); doctorId = stoi(temp);
        getline(ss, date, ',');
    }

    void display() const {
        cout << left << setw(5) << id << setw(10) << patientId
             << setw(10) << doctorId << setw(15) << date << endl;
    }
};

// ========== File Utility Functions ==========
template <typename T>
void saveToFile(const string& filename, const T& obj) {
    ofstream out(filename, ios::app);
    out << obj.serialize() << "\n";
    out.close();
}

template <typename T>
vector<T> loadFromFile(const string& filename) {
    vector<T> records;
    ifstream in(filename);
    string line;
    while (getline(in, line)) {
        T obj;
        obj.deserialize(line);
        records.push_back(obj);
    }
    in.close();
    return records;
}

// ========== Menu Handlers ==========
void patientMenu() {
    int choice;
    do {
        cout << "\n--- Patient Menu ---\n";
        cout << "1. Add Patient\n2. View Patients\n0. Back to Main Menu\nChoice: ";
        cin >> choice;
        if (choice == 1) {
            Patient p;
            p.input();
            saveToFile("patients.txt", p);
            cout << "Patient Saved.\n";
        } else if (choice == 2) {
            vector<Patient> patients = loadFromFile<Patient>("patients.txt");
            cout << left << setw(5) << "ID" << setw(20) << "Name"
                 << setw(5) << "Age" << setw(15) << "Disease" << "\n";
            for (const auto& p : patients) p.display();
        }
    } while (choice != 0);
}

void doctorMenu() {
    int choice;
    do {
        cout << "\n--- Doctor Menu ---\n";
        cout << "1. Add Doctor\n2. View Doctors\n0. Back to Main Menu\nChoice: ";
        cin >> choice;
        if (choice == 1) {
            Doctor d;
            d.input();
            saveToFile("doctors.txt", d);
            cout << "Doctor Saved.\n";
        } else if (choice == 2) {
            vector<Doctor> doctors = loadFromFile<Doctor>("doctors.txt");
            cout << left << setw(5) << "ID" << setw(20) << "Name"
                 << setw(20) << "Specialization" << "\n";
            for (const auto& d : doctors) d.display();
        }
    } while (choice != 0);
}

void appointmentMenu() {
    int choice;
    do {
        cout << "\n--- Appointment Menu ---\n";
        cout << "1. Schedule Appointment\n2. View Appointments\n0. Back to Main Menu\nChoice: ";
        cin >> choice;
        if (choice == 1) {
            Appointment a;
            a.input();
            saveToFile("appointments.txt", a);
            cout << "Appointment Scheduled.\n";
        } else if (choice == 2) {
            vector<Appointment> appts = loadFromFile<Appointment>("appointments.txt");
            cout << left << setw(5) << "ID" << setw(10) << "PatientID"
                 << setw(10) << "DoctorID" << setw(15) << "Date" << "\n";
            for (const auto& a : appts) a.display();
        }
    } while (choice != 0);
}

// ========== Main Menu ==========
int main() {
    int choice;
    do {
        cout << "\n========= HOSPITAL MANAGEMENT SYSTEM =========\n";
        cout << "1. Manage Patients\n";
        cout << "2. Manage Doctors\n";
        cout << "3. Manage Appointments\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: patientMenu(); break;
            case 2: doctorMenu(); break;
            case 3: appointmentMenu(); break;
            case 0: cout << "Exiting... Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
