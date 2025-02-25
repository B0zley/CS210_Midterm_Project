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
        }
        else {
            newSchool->next = head;
            head = newSchool;
        }
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
