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

    School(string n, string a, string c, string s, string co)
    : name(n), address(a), city(c), state(s), county(co) {}
};

struct Node {
    School school;
    Node* left;
    Node* right;

    Node(School s) : school(s), left(nullptr), right(nullptr) {}
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

class SchoolBST {
private:
    Node* root;

    Node* insert(Node* node, School school) {
        if (node == nullptr) return new Node(school);
        if (school.name < node->school.name) {
            node->left = insert(node->left, school);
        }
        else if (school.name > node->school.name) {
            node->right = insert(node->right, school);
        }
        return node;
    }

    Node* deleteNode(Node* node, string name) {
        if (node == nullptr) return node;

        if (name < node->school.name) {
            node->left = deleteNode(node->left, name);
        } else if (name > node->school.name) {
            node->right = deleteNode(node->right, name);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = minValueNode(node->right);
            node->school = temp->school;
            node->right = deleteNode(node->right, temp->school.name);
        }
        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* search(Node* node, string name) {
        if (node == nullptr || node->school.name == name) return node;
        if (name < node->school.name) return search(node->left, name);
        return search(node->right, name);
    }

    void inorder(Node* node) {
        if (node == nullptr) return;
        inorder(node->left);
        displaySchoolInfo(node->school);
        inorder(node->right);
    }

    void displaySchoolInfo(School s) {
        cout << "Name: " << s.name << "\nAddress: " << s.address
             << "\nCity: " << s.city << "\nState: " << s.state
             << "\nCounty: " << s.county << "\n-------------------------\n";
    }

public:
    SchoolBST() : root(nullptr) {}

    void insert(School school) {
        root = insert(root, school);
    }

    void findByName(string name) {
        Node* result = search(root, name);
        if (result) {
            cout << "School found:\n";
            displaySchoolInfo(result->school);
        } else {
            cout << "Name: " << name << " is not in the list.\n";
        }
    }

    void deleteByName(string name) {
        root = deleteNode(root, name);
        cout << "School deleted (if found).\n";
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

    SchoolBST bst;

    cout << "Loading from CSV...\n";
    bst.loadFromCSV(filename);

    School testSchool(name, address, city, state, county);

    // Insert timing
    cout << "Inserting test school...\n";
    double insertTime = Timer::time_function([&]() {
        bst.insert(testSchool);
    });
    cout << "Insert Time: " << insertTime << " microseconds\n\n";
    // Measure the search time
    cout << "Searching for test school...\n";
    double searchTime = Timer::time_function([&]() {
        bst.findByName(name);
    });
    cout << "Search Time: " << searchTime << " microseconds\n\n";

    // Measure the delete time
    cout << "Deleting test school...\n";
    double deleteTime = Timer::time_function([&]() {
        bst.deleteByName(name);
    });
    cout << "Delete Time: " << deleteTime << " microseconds\n";

    return 0;
}
