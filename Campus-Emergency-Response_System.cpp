#include <iostream>
#include <string>
using namespace std;

// Base class
class Emergency {
protected:
    int id;
    string studentName, location, description, status;

public:
    Emergency() {
        id = 0;
        status = "Pending";
    }

    void setDetails(int i, string name, string loc, string desc) {
        id = i;
        studentName = name;
        location = loc;
        description = desc;
        status = "Pending";
    }

    int getId() {
        return id;
    }

    string getStatus() {
        return status;
    }

    void updateStatus(string s) {
        status = s;
    }

    virtual string getType() {
        return "General";
    }

    virtual void display() {
        cout << "\nEmergency ID: " << id;
        cout << "\nStudent Name: " << studentName;
        cout << "\nLocation: " << location;
        cout << "\nDescription: " << description;
        cout << "\nStatus: " << status;
    }

    virtual ~Emergency() {}
};

// Derived class
class MedicalEmergency : public Emergency {
public:
    string getType() override {
        return "Medical";
    }
};

// Derived class
class FireEmergency : public Emergency {
public:
    string getType() override {
        return "Fire";
    }
};

// Derived class
class SecurityEmergency : public Emergency {
public:
    string getType() override {
        return "Security";
    }
};

// Display main menu
void showMenu() {
    cout << "\n\n===== CAMPUS EMERGENCY RESPONSE SYSTEM =====";
    cout << "\n1. Report Emergency";
    cout << "\n2. View All Emergencies";
    cout << "\n3. Search Emergency";
    cout << "\n4. Update Emergency Status";
    cout << "\n5. Emergency Summary";
    cout << "\n6. Exit";
    cout << "\nEnter your choice: ";
}

// Create emergency object
Emergency* createEmergency(int type) {
    if (type == 1) {
        return new MedicalEmergency();
    }
    else if (type == 2) {
        return new FireEmergency();
    }
    else if (type == 3) {
        return new SecurityEmergency();
    }

    return nullptr;
}

// Report emergency
void reportEmergency(Emergency* records[], int &count) {
    if (count >= 100) {
        cout << "\nRecord limit reached!";
        return;
    }

    int type;
    string name, location, description;

    cout << "\n1. Medical Emergency";
    cout << "\n2. Fire Emergency";
    cout << "\n3. Security Emergency";
    cout << "\nSelect type: ";
    cin >> type;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\nInvalid input!";
        return;
    }

    if (type < 1 || type > 3) {
        cout << "\nInvalid emergency type!";
        return;
    }

    cin.ignore(10000, '\n');

    cout << "Enter student name: ";
    getline(cin, name);

    cout << "Enter campus location: ";
    getline(cin, location);

    cout << "Describe the emergency: ";
    getline(cin, description);

    records[count] = createEmergency(type);

    records[count]->setDetails(
        count + 1, name, location, description
    );

    cout << "\nEmergency reported successfully!";
    cout << "\nEmergency ID: " << count + 1;

    count++;
}

// View all emergencies
void viewEmergencies(Emergency* records[], int count) {
    if (count == 0) {
        cout << "\nNo emergencies reported.";
        return;
    }

    for (int i = 0; i < count; i++) {
        cout << "\n\nEmergency Type: "
             << records[i]->getType();

        records[i]->display();

        cout << "\n----------------------------";
    }
}

// Search emergency by ID
void searchEmergency(Emergency* records[], int count) {
    int searchId;
    bool found = false;

    cout << "\nEnter Emergency ID: ";
    cin >> searchId;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\nInvalid ID!";
        return;
    }

    for (int i = 0; i < count; i++) {
        if (records[i]->getId() == searchId) {
            cout << "\nEmergency found!";
            cout << "\nType: " << records[i]->getType();

            records[i]->display();

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nEmergency not found.";
    }
}

// Update emergency status
void updateEmergency(Emergency* records[], int count) {
    int searchId, choice;
    bool found = false;

    cout << "\nEnter Emergency ID: ";
    cin >> searchId;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\nInvalid ID!";
        return;
    }

    for (int i = 0; i < count; i++) {
        if (records[i]->getId() == searchId) {
            found = true;

            cout << "\n1. Pending";
            cout << "\n2. In Progress";
            cout << "\n3. Resolved";
            cout << "\nSelect new status: ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\nInvalid input!";
                return;
            }

            if (choice == 1) {
                records[i]->updateStatus("Pending");
            }
            else if (choice == 2) {
                records[i]->updateStatus("In Progress");
            }
            else if (choice == 3) {
                records[i]->updateStatus("Resolved");
            }
            else {
                cout << "\nInvalid status choice!";
                return;
            }

            cout << "\nStatus updated successfully!";
            break;
        }
    }

    if (!found) {
        cout << "\nEmergency not found.";
    }
}

// Display emergency summary
void showSummary(Emergency* records[], int count) {
    int medical = 0;
    int fire = 0;
    int security = 0;

    int pending = 0;
    int progress = 0;
    int resolved = 0;

    for (int i = 0; i < count; i++) {
        if (records[i]->getType() == "Medical") {
            medical++;
        }
        else if (records[i]->getType() == "Fire") {
            fire++;
        }
        else if (records[i]->getType() == "Security") {
            security++;
        }

        if (records[i]->getStatus() == "Pending") {
            pending++;
        }
        else if (records[i]->getStatus() == "In Progress") {
            progress++;
        }
        else if (records[i]->getStatus() == "Resolved") {
            resolved++;
        }
    }

    cout << "\n\n===== EMERGENCY SUMMARY =====";
    cout << "\nTotal Emergencies: " << count;

    cout << "\nMedical Emergencies: " << medical;
    cout << "\nFire Emergencies: " << fire;
    cout << "\nSecurity Emergencies: " << security;

    cout << "\n\nPending: " << pending;
    cout << "\nIn Progress: " << progress;
    cout << "\nResolved: " << resolved;
    cout << "\n=============================";
}

// Main function
int main() {
    Emergency* records[100];

    int count = 0;
    int choice = 0;

    do {
        showMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nPlease enter a valid number!";
            continue;
        }

        try {
            if (choice < 1 || choice > 6) {
                throw "Choose a number between 1 and 6!";
            }

            switch (choice) {
                case 1:
                    reportEmergency(records, count);
                    break;

                case 2:
                    viewEmergencies(records, count);
                    break;

                case 3:
                    searchEmergency(records, count);
                    break;

                case 4:
                    updateEmergency(records, count);
                    break;

                case 5:
                    showSummary(records, count);
                    break;

                case 6:
                    cout << "\nThank you for using the system!";
                    break;
            }
        }
        catch (const char* message) {
            cout << "\nError: " << message;
        }

    } while (choice != 6);

    // Release allocated memory
    for (int i = 0; i < count; i++) {
        delete records[i];
    }

    return 0;
}