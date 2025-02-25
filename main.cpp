#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

template<typename T>
struct Node
{
    T data;
    Node* next;
    Node(T val) : data(val), next(nullptr) {}
};

template<typename T>
class SchoolList
{
    Node<T>* head;
public:
    SchoolList() : head(nullptr) {}
    void append(T data)
    {
        Node<T>* newNode = new Node<T>(data);
        if(head==nullptr)
        {
            head = newNode;
        }else
        {
            Node<T>* temp = head;
            while(temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
    void printList()
    {
        Node<T>* temp = head;
        while(temp!=nullptr)
        {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "nullptr" << endl;
    }
};

struct School {
    string name;
    string address;
    string city;
    string state;
    string county;
    School* next;

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
