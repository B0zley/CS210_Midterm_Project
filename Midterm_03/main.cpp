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
        if (node == nullptr || node ->school.name == name) return node;
        if (name < node->school.name) return search(node->left, name);
        return search(node->right, name);
    }

    void inorder(Node* node) {
        if (node == nullptr) return;
        inorder(node->left);
        displaySchoolInfo(node->school);
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (node == nullptr) return;
        displaySchoolInfo(node->school);
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) {
        if (node == nullptr) return;
        postorder(node->left);
        postorder(node->right);
        displaySchoolInfo(node->school);
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


    void displayInOrder() {
        cout << "Displaying schools in alphabetical order:\n";
        inorder(root);
    }

    void displayPreOrder() {
        cout << "Displaying schools in pre-order traversal:\n";
        preorder(root);
    }

    void displayPostOrder() {
        cout << "Displaying schools in post-order traversal:\n";
        postorder(root);
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