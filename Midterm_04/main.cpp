#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Timer.h"
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

    void findByName(const string& name) {
        int index = hashFunction(name);
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

    void deleteByName(const string& name) {
        int index = hashFunction(name);
        School* current = table[index];
        School* prev = nullptr;

        while (current != nullptr) {
            if (current->name == name) {
                if (prev == nullptr) {
                    table[index] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                cout << "School '" << name << "' deleted.\n";
                return;
            }
            prev = current;
            current = current->next;
        }
        cout << "School '" << name << "' not found.\n";
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
    // CSV file to work with
    string filename = "Test_Schools.csv";

    // Made-up school details
    string name = "Test High School";
    string address = "123 Testing Lane";
    string city = "Faketown";
    string state = "IL";
    string county = "Imaginary";

    // Step 1: Write made-up school to the CSV file
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Failed to open " << filename << " for writing.\n";
        return 1;
    }

    SchoolHashTable hashTable;

    // Step 2: Time the insertion (loading from CSV)
    cout << "Loading from CSV...\n";
        hashTable.loadFromCSV(filename);

    School testSchool(name, address, city, state, county);

    // Insert timing
    cout << "Inserting test school...\n";
    double insertTime = Timer::time_function([&]() {
        hashTable.insert(testSchool);
    });
    cout << "Insert Time: " << insertTime << " microseconds\n\n";


    // Step 3: Time the search
    cout << "Searching for test school...\n";
    double searchTime = Timer::time_function([&]() {
        hashTable.findByName(name);
    });
    cout << "Search Time: " << searchTime << " microseconds\n\n";

    // Step 4: Time the delete
    cout << "Deleting test school...\n";
    double deleteTime = Timer::time_function([&]() {
        hashTable.deleteByName(name);
    });
    cout << "Delete Time: " << deleteTime << " microseconds\n";

    return 0;
}


