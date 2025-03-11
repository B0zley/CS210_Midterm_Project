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
        if (school.name < node -> school.name) {
            node->left = insert(node->left, school);
        }
        else if (school.name > node -> school.name) {
            node->right = insert(node->right, school);
        }
        return node;
    }
};