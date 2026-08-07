/*
 * Employee Management System
 * A console-based C++ application demonstrating Object-Oriented Programming
 * and File Handling concepts.
 *
 * Features: Add, View, Update, and Delete employee records — persisted
 * to a text file using file I/O (no database required).
 *
 * Author: Muhammad Arsalan Baig
 * Student ID: FA24-BSCS-0229
 */

#include <iostream>
#include <fstream>
#include <limits>
#include <cstring>
using namespace std;

class Employee {
private:
    int id;
    char name[50];
    char department[30];
    float salary;

public:
    void display() {
        cout << id << "\t" << name << "\t" << department << "\t" << salary << endl;
    }

    // Add Employee
    void addEmployee() {
        ofstream file("employees.txt", ios::app);
        if (!file) {
            cout << "Cannot open file!" << endl;
            return;
        }

        cout << "Enter ID: ";
        cin >> id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Name: ";
        cin.getline(name, 50);

        cout << "Enter Department: ";
        cin.getline(department, 30);

        cout << "Enter Salary: ";
        cin >> salary;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Write to file in | separated format
        file << id << "|" << name << "|" << department << "|" << salary << "\n";
        file.close();

        cout << "Employee added successfully!\n";
    }

    // View Employees
    void viewEmployees() {
        ifstream file("employees.txt");
        if (!file) {
            cout << "File could not be opened!" << endl;
            return;
        }

        cout << "\nID\tName\tDepartment\tSalary\n";
        cout << "---------------------------------------------\n";

        int tempId;
        char tempName[50];
        char tempDept[30];
        float tempSalary;

        while (true) {
            if (!(file >> tempId)) break;
            file.ignore(numeric_limits<streamsize>::max(), '|');
            file.getline(tempName, 50, '|');
            file.getline(tempDept, 30, '|');
            if (!(file >> tempSalary)) break;
            file.ignore(numeric_limits<streamsize>::max(), '\n');

            id = tempId;
            strcpy(name, tempName);
            strcpy(department, tempDept);
            salary = tempSalary;

            display();
        }

        file.close();
    }

    // Update Employee
    void updateEmployee(int searchId) {
        ifstream infile("employees.txt");
        ofstream tempFile("temp.txt");

        if (!infile || !tempFile) {
            cout << "File error!" << endl;
            return;
        }

        int tempId;
        char tempName[50];
        char tempDept[30];
        float tempSalary;
        bool found = false;

        while (true) {
            if (!(infile >> tempId)) break;
            infile.ignore(numeric_limits<streamsize>::max(), '|');
            infile.getline(tempName, 50, '|');
            infile.getline(tempDept, 30, '|');
            if (!(infile >> tempSalary)) break;
            infile.ignore(numeric_limits<streamsize>::max(), '\n');

            if (tempId == searchId) {
                found = true;
                cout << "Updating Employee ID " << searchId << endl;

                cout << "Enter new Name: ";
                cin.ignore();
                cin.getline(tempName, 50);

                cout << "Enter new Department: ";
                cin.getline(tempDept, 30);

                cout << "Enter new Salary: ";
                cin >> tempSalary;
            }

            tempFile << tempId << "|" << tempName << "|" << tempDept << "|" << tempSalary << "\n";
        }

        infile.close();
        tempFile.close();

        remove("employees.txt");
        rename("temp.txt", "employees.txt");

        if (found)
            cout << "Employee updated successfully!\n";
        else
            cout << "Employee not found!\n";
    }

    // Delete Employee
    void deleteEmployee(int searchId) {
        ifstream infile("employees.txt");
        ofstream tempFile("temp.txt");

        if (!infile || !tempFile) {
            cout << "File error!" << endl;
            return;
        }

        int tempId;
        char tempName[50];
        char tempDept[30];
        float tempSalary;
        bool found = false;

        while (true) {
            if (!(infile >> tempId)) break;
            infile.ignore(numeric_limits<streamsize>::max(), '|');
            infile.getline(tempName, 50, '|');
            infile.getline(tempDept, 30, '|');
            if (!(infile >> tempSalary)) break;
            infile.ignore(numeric_limits<streamsize>::max(), '\n');

            if (tempId == searchId) {
                found = true;
                continue; // skip writing this record to delete it
            }

            tempFile << tempId << "|" << tempName << "|" << tempDept << "|" << tempSalary << "\n";
        }

        infile.close();
        tempFile.close();

        remove("employees.txt");
        rename("temp.txt", "employees.txt");

        if (found)
            cout << "Employee deleted successfully!\n";
        else
            cout << "Employee not found!\n";
    }
};

int main() {
    Employee emp;
    int choice;
    int id;

    do {
        cout << "\n--- Employee Management System ---\n";
        cout << "1. Add Employee\n";
        cout << "2. View Employees\n";
        cout << "3. Update Employee\n";
        cout << "4. Delete Employee\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                emp.addEmployee();
                break;
            case 2:
                emp.viewEmployees();
                break;
            case 3:
                cout << "Enter Employee ID to update: ";
                cin >> id;
                emp.updateEmployee(id);
                break;
            case 4:
                cout << "Enter Employee ID to delete: ";
                cin >> id;
                emp.deleteEmployee(id);
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
