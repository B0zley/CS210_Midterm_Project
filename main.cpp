
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct School {
    string name;
    string address;
    string city;
    string state;
    string county;
    School* next;

    School(string n, string a, string c, string s, string co)
    : name(n), address(a), city(c), state(s), county(co), next(nullptr) {}

};

class CSVReader {
public:
    static vector<vector<string>> readCSV(const string& filename) {
        ifstream file(filename);
        vector<vector<string>> data;
        string line, word;

        if (!file.is_open()) {
            cerr << "Error: Could not open file " << filename << endl;
            return data;
        }

        while (getline(file, line)) {
            stringstream ss(line);
            vector<string> row;
            while (getline(ss, word, ',')) {
                row.push_back(word);
            }
            data.push_back(row);
        }
        file.close();
        return data;
    }

};

class SchoolList
{
    School* head;
public:
    SchoolList() : head(nullptr) {}

    void insertFirst(School school)
    {
        School* newSchool = new School(school);
        newSchool->next = head;
        head = newSchool;
    }

    void insertLast(School school) {
        School* newSchool = new School(school);
        newSchool->next = nullptr;

        if (head == nullptr) {
            head = newSchool;
            return;
        }

        School* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newSchool;
    }

    void deleteByName(const string name) {
        if (head == nullptr) {
            return;
        }

        if (head->name == name) {
            School* toDelete = head;
            head = head->next;
            delete toDelete;
            return;
        }

        School* current = head;
        while (current->next != nullptr && current->next->name != name) {
            current = current->next;
        }

        if (current->next == nullptr) return;

        School* toDelete = current->next;
        current->next = current->next->next;
        delete toDelete;
    }

    void findByName(const string name) {
        School* current = head;
        while (current != nullptr) {
            if (current->name == name) {
                cout << "Name: " << current->name << endl;
                cout << "Address: " << current->address << endl;
                cout << "City: " << current->city << endl;
                cout << "State: " << current->state << endl;
                cout << "County: " << current->county << endl;
                cout << "-------------------------" << endl;
                return;
            }
            current = current->next;
        }
        cout << "Name: " << name <<" is not in the list."<< endl;
        return;
    }

    void display() const {
        School* current = head;
        while (current != nullptr) {
            cout << "Name: " << current->name << endl;
            cout << "Address: " << current->address << endl;
            cout << "City: " << current->city << endl;
            cout << "State: " << current->state << endl;
            cout << "County: " << current->county << endl;
            cout << "-------------------------" << endl;
            current = current->next;
        }
    }

    void loadFromCSV(const string& filename) {
        vector<vector<string>> data = CSVReader::readCSV(filename);
        for (const auto& row : data) {
            if (row.size() == 5) {
                insertLast(School(row[0], row[1], row[2], row[3], row[4]));
            }
        }
    }
};

int main() {
    SchoolList list;
    string filename = "schools.csv";

    cout << "Loading schools from CSV file...\n";
    list.loadFromCSV(filename);
    cout << "Schools loaded successfully!\n\n";

    int choice;
    string schoolName;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Search for a school by name\n";
        cout << "2. Delete a school by name\n";
        cout << "3. Display all schools\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter the school name to search: ";
            getline(cin, schoolName);
            list.findByName(schoolName);
            break;
            case 2:
                cout << "Enter the school name to delete: ";
            getline(cin, schoolName);
            list.deleteByName(schoolName);
            cout << "School deleted (if found).\n";
            break;
            case 3:
                cout << "Displaying all schools:\n";
            list.display();
            break;
            case 4:
                cout << "Exiting program.\n";
            return 0;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 4.\n";
        }
    }
}
