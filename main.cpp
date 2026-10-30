
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Student Class
class Student {
private:
    string name;
    int rollNo;
    int semester;
    float marks;

public:
    // Constructor
    Student(string n, int r, int s, float m) {
        name = n;
        rollNo = r;
        semester = s;
        marks = m;
    }

    // Getter Functions
    string getName() {
        return name;
    }

    int getRollNo() {
        return rollNo;
    }

    int getSemester() {
        return semester;
    }

    float getMarks() {
        return marks;
    }

    // Calculate Pass or Fail
    string getResult() {
        if (marks >= 50) {
            return "PASS";
        } else {
            return "FAIL";
        }
    }

    // Update Student Information
    void updateDetails(string n, int s, float m) {
        name = n;
        semester = s;
        marks = m;
    }

    // Display Student
    void display() {
        cout << left << setw(20) << name
             << setw(15) << rollNo
             << setw(12) << semester
             << setw(10) << marks
             << getResult() << endl;
    }
};

// Student Management Class
class StudentManager {
private:
    vector<Student> students;

    // Search Student Index
    int findStudent(int rollNo) {
        for (int i = 0; i < students.size(); i++) {
            if (students[i].getRollNo() == rollNo) {
                return i;
            }
        }
        return -1;
    }

    // Save Records in File
    void saveToFile() {
        ofstream file("students.txt");

        for (int i = 0; i < students.size(); i++) {
            file << students[i].getName() << endl;
            file << students[i].getRollNo() << endl;
            file << students[i].getSemester() << endl;
            file << students[i].getMarks() << endl;
        }

        file.close();
    }

    // Load Records from File
    void loadFromFile() {
        ifstream file("students.txt");

        string name;
        int rollNo, semester;
        float marks;

        while (getline(file, name)) {
            if (!(file >> rollNo >> semester >> marks)) {
                break;
            }

            file.ignore();

            students.push_back(
                Student(name, rollNo, semester, marks)
            );
        }

        file.close();
    }

public:
    // Constructor
    StudentManager() {
        loadFromFile();
    }

    // Add Student
    void addStudent() {
        string name;
        int rollNo, semester;
        float marks;

        cout << "\nEnter Student Name: ";
        getline(cin, name);

        cout << "Enter Roll Number: ";
        cin >> rollNo;

        if (findStudent(rollNo) != -1) {
            cout << "Roll Number Already Exists!\n";
            cin.ignore(1000, '\n');
            return;
        }

        cout << "Enter Semester (1-8): ";
        cin >> semester;

        cout << "Enter Marks (0-100): ";
        cin >> marks;

        cin.ignore(1000, '\n');

        if (name.empty() || rollNo <= 0 ||
            semester < 1 || semester > 8 ||
            marks < 0 || marks > 100) {
            cout << "Invalid Student Information!\n";
            return;
        }

        students.push_back(
            Student(name, rollNo, semester, marks)
        );

        saveToFile();

        cout << "\nStudent Added Successfully!\n";
        cout << "Result: "
             << (marks >= 50 ? "PASS" : "FAIL") << endl;
    }

    // Display All Students
    void displayStudents() {
        if (students.empty()) {
            cout << "\nNo Records Found!\n";
            return;
        }

        cout << "\n";
        cout << left << setw(20) << "Name"
             << setw(15) << "Roll Number"
             << setw(12) << "Semester"
             << setw(10) << "Marks"
             << "Result" << endl;

        cout << "------------------------------------------------------------------\n";

        for (int i = 0; i < students.size(); i++) {
            students[i].display();
        }
    }

    // Search Student
    void searchStudent() {
        int rollNo;

        cout << "\nEnter Roll Number: ";
        cin >> rollNo;
        cin.ignore(1000, '\n');

        int index = findStudent(rollNo);

        if (index == -1) {
            cout << "Student Not Found!\n";
        } else {
            cout << "\nStudent Found:\n";

            cout << left << setw(20) << "Name"
                 << setw(15) << "Roll Number"
                 << setw(12) << "Semester"
                 << setw(10) << "Marks"
                 << "Result" << endl;

            cout << "------------------------------------------------------------------\n";

            students[index].display();
        }
    }

    // Update Student
    void updateStudent() {
        int rollNo;

        cout << "\nEnter Roll Number: ";
        cin >> rollNo;
        cin.ignore(1000, '\n');

        int index = findStudent(rollNo);

        if (index == -1) {
            cout << "Student Not Found!\n";
            return;
        }

        string name;
        int semester;
        float marks;

        cout << "Enter New Name: ";
        getline(cin, name);

        cout << "Enter New Semester: ";
        cin >> semester;

        cout << "Enter New Marks: ";
        cin >> marks;

        cin.ignore(1000, '\n');

        if (name.empty() || semester < 1 ||
            semester > 8 || marks < 0 || marks > 100) {
            cout << "Invalid Information!\n";
            return;
        }

        students[index].updateDetails(
            name, semester, marks
        );

        saveToFile();

        cout << "\nRecord Updated Successfully!\n";
        cout << "New Result: "
             << (marks >= 50 ? "PASS" : "FAIL") << endl;
    }

    // Delete Student
    void deleteStudent() {
        int rollNo;

        cout << "\nEnter Roll Number: ";
        cin >> rollNo;
        cin.ignore(1000, '\n');

        int index = findStudent(rollNo);

        if (index == -1) {
            cout << "Student Not Found!\n";
            return;
        }

        students.erase(students.begin() + index);

        saveToFile();

        cout << "Record Deleted Successfully!\n";
    }
};

// Main Function
int main() {
    StudentManager manager;
    int choice;

    do {
        cout << "\n========================================\n";
        cout << "     STUDENT RECORD MANAGEMENT SYSTEM\n";
        cout << "========================================\n";

        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "0. Exit\n";

        cout << "\nEnter Your Choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid Input!\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        cin.ignore(1000, '\n');

        switch (choice) {
            case 1:
                manager.addStudent();
                break;

            case 2:
                manager.displayStudents();
                break;

            case 3:
                manager.searchStudent();
                break;

            case 4:
                manager.updateStudent();
                break;

            case 5:
                manager.deleteStudent();
                break;

            case 0:
                cout << "\nThank You! Program Closed.\n";
                break;

            default:
                cout << "Invalid Choice! Try Again.\n";
        }

    } while (choice != 0);

    return 0;
}
