#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Student {
public:
    int id;
    string name;
    int age;
    float marks;

    Student(int i, string n, int a, float m) : id(i), name(n), age(a), marks(m) {}

    void display() {
        cout << "ID: " << id << "\nName: " << name << "\nAge: " << age << "\nMarks: " << marks << "\n";
    }
};

class StudentManagement {
private:
    vector<Student> students;
    int nextId = 1;

public:
    void addStudent(string name, int age, float marks) {
        students.push_back(Student(nextId++, name, age, marks));
        cout << "Student added.\n";
    }

    Student* findStudent(int id) {
        for (auto &s : students)
            if (s.id == id) return &s;
        return nullptr;
    }

    void updateStudent(int id, string name, int age, float marks) {
        Student* s = findStudent(id);
        if (!s) {
            cout << "Student not found.\n";
            return;
        }
        s->name = name;
        s->age = age;
        s->marks = marks;
        cout << "Student updated.\n";
    }

    void deleteStudent(int id) {
        auto it = remove_if(students.begin(), students.end(), [id](Student &s) { return s.id == id; });
        if (it != students.end()) {
            students.erase(it, students.end());
            cout << "Student deleted.\n";
        } else {
            cout << "Student not found.\n";
        }
    }

    void displayAll() {
        cout << "Students:\n";
        for (auto &s : students) {
            s.display();
            cout << "----\n";
        }
    }

    void displayTopPerformers(int n) {
        sort(students.begin(), students.end(), [](Student &a, Student &b) {
            return a.marks > b.marks;
        });
        cout << "Top " << n << " performers:\n";
        for (int i = 0; i < n && i < (int)students.size(); i++) {
            students[i].display();
            cout << "----\n";
        }
    }

    void searchByName(string keyword) {
        bool found = false;
        for (auto &s : students) {
            if (s.name.find(keyword) != string::npos) {
                s.display();
                cout << "----\n";
                found = true;
            }
        }
        if (!found) cout << "No student found with name containing '" << keyword << "'.\n";
    }

    void displayAverageMarks() {
        if (students.empty()) {
            cout << "No students available to calculate average marks.\n";
            return;
        }
        float total = 0;
        for (auto &s : students) total += s.marks;
        cout << "Average Marks: " << total / students.size() << "\n";
    }

    void displayAboveMarks(float threshold) {
        bool found = false;
        for (auto &s : students) {
            if (s.marks > threshold) {
                s.display();
                cout << "----\n";
                found = true;
            }
        }
        if (!found) cout << "No student found with marks above " << threshold << ".\n";
    }
};

void showMenu() {
    cout << "\n--- Student Management System ---\n";
    cout << "1. Add Student\n";
    cout << "2. Update Student\n";
    cout << "3. Delete Student\n";
    cout << "4. Display All Students\n";
    cout << "5. Display Top Performers\n";
    cout << "6. Search Student by Name\n";
    cout << "7. Display Average Marks\n";
    cout << "8. Display Students with Marks Above Threshold\n";
    cout << "9. Exit\n";
    cout << "Enter choice: ";
}

int main() {
    StudentManagement sm;
    int choice;

    while (true) {
        showMenu();
        cin >> choice;
        cin.ignore();

        if (choice == 9) break;

        switch (choice) {
            case 1: {
                string name;
                int age;
                float marks;
                cout << "Enter name: ";
                getline(cin, name);
                cout << "Enter age: ";
                cin >> age;
                cout << "Enter marks: ";
                cin >> marks;
                cin.ignore();
                sm.addStudent(name, age, marks);
                break;
            }
            case 2: {
                int id, age;
                float marks;
                string name;
                cout << "Enter student ID to update: ";
                cin >> id;
                cin.ignore();
                cout << "Enter new name: ";
                getline(cin, name);
                cout << "Enter new age: ";
                cin >> age;
                cout << "Enter new marks: ";
                cin >> marks;
                cin.ignore();
                sm.updateStudent(id, name, age, marks);
                break;
            }
            case 3: {
                int id;
                cout << "Enter student ID to delete: ";
                cin >> id;
                cin.ignore();
                sm.deleteStudent(id);
                break;
            }
            case 4:
                sm.displayAll();
                break;
            case 5: {
                int n;
                cout << "Enter number of top performers to display: ";
                cin >> n;
                cin.ignore();
                sm.displayTopPerformers(n);
                break;
            }
            case 6: {
                string keyword;
                cout << "Enter name or part of name to search: ";
                getline(cin, keyword);
                sm.searchByName(keyword);
                break;
            }
            case 7:
                sm.displayAverageMarks();
                break;
            case 8: {
                float threshold;
                cout << "Enter mark threshold: ";
                cin >> threshold;
                cin.ignore();
                sm.displayAboveMarks(threshold);
                break;
            }
            default:
                cout << "Invalid choice.\n";
        }
    }

    cout << "Exiting...\n";
    return 0;
}

