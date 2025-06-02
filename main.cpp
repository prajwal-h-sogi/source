#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cctype>

using namespace std;

class Student {
public:
    int id;
    string name;
    int age;
    float marks;

    Student(int i, string n, int a, float m) : id(i), name(n), age(a), marks(m) {}

    void display() {
        cout << "ID: " << id << "\nName: " << name << "\nAge: " << age << "\nMarks: " << fixed << setprecision(2) << marks << "\n";
    }
};

class StudentManagement {
private:
    vector<Student> students;
    int nextId = 1;

    static string toLower(const string& str) {
        string result = str;
        transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }

public:
    void addStudent(string name, int age, float marks) {
        students.emplace_back(nextId++, name, age, marks);
        cout << "✅ Student added.\n";
    }

    Student* findStudent(int id) {
        for (auto& s : students)
            if (s.id == id) return &s;
        return nullptr;
    }

    void updateStudent(int id, string name, int age, float marks) {
        Student* s = findStudent(id);
        if (!s) {
            cout << "❌ Student not found.\n";
            return;
        }
        s->name = name;
        s->age = age;
        s->marks = marks;
        cout << "✅ Student updated.\n";
    }

    void deleteStudent(int id) {
        auto it = remove_if(students.begin(), students.end(), [id](Student& s) { return s.id == id; });
        if (it != students.end()) {
            students.erase(it, students.end());
            cout << "✅ Student deleted.\n";
        } else {
            cout << "❌ Student not found.\n";
        }
    }

    void listStudents() {
        if (students.empty()) {
            cout << "No students to display.\n";
            return;
        }
        for (const auto& s : students) {
            s.display();
            cout << "----------------------\n";
        }
    }

    void searchByName(const string& keyword) {
        string kw = toLower(keyword);
        bool found = false;
        for (const auto& s : students) {
            if (toLower(s.name).find(kw) != string::npos) {
                s.display();
                cout << "----------------------\n";
                found = true;
            }
        }
        if (!found) cout << "No student found with name containing '" << keyword << "'.\n";
    }

    void sortAndDisplay(bool byMarks) {
        if (students.empty()) {
            cout << "No students to sort.\n";
            return;
        }

        vector<Student> sorted = students;

        if (byMarks) {
            sort(sorted.begin(), sorted.end(), [](Student& a, Student& b) { return a.marks > b.marks; });
            cout << "📊 Students sorted by Marks:\n";
        } else {
            sort(sorted.begin(), sorted.end(), [](Student& a, Student& b) { return a.name < b.name; });
            cout << "📚 Students sorted by Name:\n";
        }

        for (const auto& s : sorted) {
            s.display();
            cout << "----------------------\n";
        }
    }

    void averageMarks() {
        if (students.empty()) {
            cout << "No students available.\n";
            return;
        }
        float total = 0;
        for (const auto& s : students)
            total += s.marks;
        cout << "📈 Average Marks: " << fixed << setprecision(2) << total / students.size() << "\n";
    }
};

void menu() {
    cout << "\n=== Student Management Menu ===\n";
    cout << "1. Add Student\n";
    cout << "2. Update Student\n";
    cout << "3. Delete Student\n";
    cout << "4. List All Students\n";
    cout << "5. Search Student by Name\n";
    cout << "6. Sort Students by Marks\n";
    cout << "7. Sort Students by Name\n";
    cout << "8. Average Marks\n";
    cout << "9. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    StudentManagement sm;
    int choice;

    do {
        menu();
        cin >> choice;

        switch (choice) {
            case 1: {
                string name;
                int age;
                float marks;
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Age: ";
                cin >> age;
                cout << "Enter Marks: ";
                cin >> marks;
                sm.addStudent(name, age, marks);
                break;
            }
            case 2: {
                int id;
                string name;
                int age;
                float marks;
                cout << "Enter ID to Update: ";
                cin >> id;
                cin.ignore();
                cout << "Enter New Name: ";
                getline(cin, name);
                cout << "Enter New Age: ";
                cin >> age;
                cout << "Enter New Marks: ";
                cin >> marks;
                sm.updateStudent(id, name, age, marks);
                break;
            }
            case 3: {
                int id;
                cout << "Enter ID to Delete: ";
                cin >> id;
                sm.deleteStudent(id);
                break;
            }
            case 4:
                sm.listStudents();
                break;
            case 5: {
                string keyword;
                cin.ignore();
                cout << "Enter Name or Partial Name: ";
                getline(cin, keyword);
                sm.searchByName(keyword);
                break;
            }
            case 6:
                sm.sortAndDisplay(true);
                break;
            case 7:
                sm.sortAndDisplay(false);
                break;
            case 8:
                sm.averageMarks();
                break;
            case 9:
                cout << "👋 Exiting Program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 9);

    return 0;
}

