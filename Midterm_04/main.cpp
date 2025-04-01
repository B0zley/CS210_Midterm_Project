#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

const int TABLE_SIZE = 100;

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

class SchoolHashTable {
    private:
    vector<School*> table;

    int hashFunction(const string& key) {
        int hash = 0;
        for (char ch : key) {
            hash += ch;
        }
        return hash % TABLE_SIZE;
    }
public:

    SchoolHashTable() : table(TABLE_SIZE, nullptr) {}

    void insert(School school) {
        int index = hashFunction(school.name);
        School* newSchool = new School(school.name, school.address, school.city, school.state, school.county);

        if (!table[index]) {
            table[index] = newSchool;
        } else {
            School* current = table[index];
            while (current->next) {
                current = current->next;
            }
            current->next = newSchool;
        }
    }

    void findByName(const string* name) {
        int index = hashFunction(*name);
        School* current = table[index];

        while (current != nullptr) {
            if (current->name == name) {
                cout << "School found:\n";
                displaySchoolInfo(*current);
                return;
            }
            current = current->next;
        }
        cout << "School '" << name << "' not found.\n";
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i] != nullptr) {
                cout << "Index " << i << ":\n";
                School* current = table[i];
                while (current != nullptr) {
                    displaySchoolInfo(*current);
                    current = current->next;
                }
            }
        }
    }

    void displaySchoolInfo(const School& s) {
        cout << "Name: " << s.name << "\nAddress: " << s.address
             << "\nCity: " << s.city << "\nState: " << s.state
             << "\nCounty: " << s.county << "\n-------------------------\n";
    }

    void loadFromCSV(const string& filename) {
        vector<vector<string>> data = CSVReader::readCSV(filename);
        for (const auto& row : data) {
            if (row.size() == 5) {
                insert(School(row[0], row[1], row[2], row[3], row[4]));
            }
        }
    }

};

int main() {
    SchoolBST bst;
    string filename = "Illinois_Peoria_Schools.csv";

    cout << "Loading schools from CSV file...\n";
    bst.loadFromCSV(filename);
    cout << "Schools loaded successfully!\n\n";

    int choice;
    string schoolName;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Search for a school by name\n";
        cout << "2. Delete a school by name\n";
        cout << "3. Display all schools (In-Order)\n";
        cout << "4. Display all schools (Pre-Order)\n";
        cout << "5. Display all schools (Post-Order)\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter the school name to search: ";
            getline(cin, schoolName);
            bst.findByName(schoolName);
            break;
            case 2:
                cout << "Enter the school name to delete: ";
            getline(cin, schoolName);
            bst.deleteByName(schoolName);
            break;
            case 3:
                bst.displayInOrder();
            break;
            case 4:
                bst.displayPreOrder();
            break;
            case 5:
                bst.displayPostOrder();
            break;
            case 6:
                cout << "Exiting program.\n";
            return 0;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 6.\n";
        }
    }
}
