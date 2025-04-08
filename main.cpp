#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Timer.h" // Ensure Timer.h is included for timing operations
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

class SchoolList {
    School* head;

public:
    SchoolList() : head(nullptr) {}

    void insertFirst(School school) {
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
    string filename = "Illinois_Schools.csv";

    // Made-up school details
    string name = "Test High School";
    string address = "123 Testing Lane";
    string city = "Faketown";
    string state = "IL";
    string county = "Imaginary";

    // Step 1: Write made-up school to CSV file
    ofstream outFile(filename, ios::app); // Open file in append mode
    if (!outFile.is_open()) {
        cerr << "Failed to open " << filename << " for writing.\n";
        return 1;
    }


    SchoolList list;

    cout << "Loading from CSV...\n";
    list.loadFromCSV(filename);

    School testSchool(name, address, city, state, county);

    // Insert timing
    cout << "Inserting test school...\n";
    double insertTime = Timer::time_function([&]() {
        list.insertFirst(testSchool);
    });
    cout << "Insert Time: " << insertTime << " microseconds\n\n";
    // Step 3: Measure the search time
    cout << "Searching for test school...\n";
    double searchTime = Timer::time_function([&]() {
        list.findByName(name);
    });
    cout << "Search Time: " << searchTime << " microseconds\n\n";

    // Step 4: Measure the delete time
    cout << "Deleting test school...\n";
    double deleteTime = Timer::time_function([&]() {
        list.deleteByName(name);
    });
    cout << "Delete Time: " << deleteTime << " microseconds\n";

    return 0;
}
