#include <iostream>
#include <fstream>
using namespace std;

class Student {
public:
    int id;
    char name[50];
    int age;

    void input() {
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Age: ";
        cin >> age;
    }

    void display() {
        cout << "ID: " << id << ", Name: " << name << ", Age: " << age << endl;
    }
};

// Add Student
void addStudent() {
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);
    s.input();
    file.write((char*)&s, sizeof(s));
    file.close();
    cout << "Student added successfully!\n";
}

// Display Students
void displayStudents() {
    Student s;
    ifstream file("students.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        s.display();
    }
    file.close();
}

// Search & Update Student
void updateStudent() {
    Student s;
    fstream file("students.dat", ios::binary | ios::in | ios::out);
    int id, found = 0;

    cout << "Enter ID to update: ";
    cin >> id;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id == id) {
            cout << "Record Found. Enter new details:\n";
            s.input();
            int pos = -1 * sizeof(s);
            file.seekp(pos, ios::cur);
            file.write((char*)&s, sizeof(s));
            found = 1;
            break;
        }
    }

    if (!found)
        cout << "Record not found!\n";

    file.close();
}

// Delete Student
void deleteStudent() {
    Student s;
    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    int id, found = 0;
    cout << "Enter ID to delete: ";
    cin >> id;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id != id) {
            temp.write((char*)&s, sizeof(s));
        } else {
            found = 1;
        }
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "Record deleted successfully!\n";
    else
        cout << "Record not found!\n";
}

// Main Menu
int main() {
    int choice;

    do {
        cout << "\n--- Student Management System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addStudent(); break;
        case 2: displayStudents(); break;
        case 3: updateStudent(); break;
        case 4: deleteStudent(); break;
        case 5: cout << "Exiting...\n"; break;
        default: cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}