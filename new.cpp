#include <bits/stdc++.h>
#include <conio.h>

using namespace std;

void clearInputBuffer() {
    cin.clear();
    while (cin.get() != '\n');
}

unordered_map<string, string> readUserDatafromfilelogin(const string& filename) {
    unordered_map<string, string> userMap;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file for reading.\n";
        return userMap;
    }

    string line;
    while (getline(file, line)) {
        size_t delimiterPos = line.find('|');
        if (delimiterPos != string::npos) {
            string username = line.substr(0, delimiterPos);
            string password = line.substr(delimiterPos + 1);
            userMap[username] = password;
        }
    }

    file.close();
    return userMap;
}

void writeUserDatatofilelogin(const string& filename, const unordered_map<string, string>& a) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file for writing.\n";
        return;
    }

    for (const auto& pair : a) {
        file << pair.first << '|' << pair.second << '\n';
    }

    file.close();
}

struct Student {
    int rollNumber;
    string name;
    float cgpa;
    char gender;
};

unordered_map<int, Student> students;
int boysCount = 0;
int girlsCount = 0;

void writeStudentsToFile() {
    ofstream file("students.txt");
    if (!file) {
        cout << "Error opening file for writing.\n";
        return;
    }
    for (const auto& [rollNumber, student] : students) {
        file << student.rollNumber << " " << student.name << " " << student.cgpa << " " << student.gender << "\n";
    }
    file.close();
}

void addStudent(int rollNumber, const string& name, float cgpa, char gender) {
    while (true) {
        if (students.find(rollNumber) != students.end()) {
            cout << "Error: Roll number " << rollNumber << " already exists. Please enter a unique roll number.\n";
            cout << "Enter a new roll number: ";
            if (!(cin >> rollNumber) || rollNumber <= 0) {
                cout << "Invalid input. Roll number must be a positive integer.\n";
                clearInputBuffer();
            } else {
                break;
            }
        } else {
            break;
        }
    }

    Student newStudent = {rollNumber, name, cgpa, gender};

    if (gender == 'M' || gender == 'm') {
        boysCount++;
    } else if (gender == 'F' || gender == 'f') {
        girlsCount++;
    }

    students[rollNumber] = newStudent;

    writeStudentsToFile();

    cout << "Student added successfully.\n";
}

void findStudentByRollNumber(int rollNumber) {
    auto it = students.find(rollNumber);
    if (it != students.end()) {
        const Student& student = it->second;
        cout << "\nStudent found:\n";
        cout << "Roll Number: " << student.rollNumber << ", Name: " << student.name << ", CGPA: " << student.cgpa << ", Gender: " << student.gender << endl;
    } else {
        cout << "Student with roll number " << rollNumber << " not found.\n";
    }
}

int countStudents() {
    return students.size();
}

void deleteStudent(int rollNumber) {
    auto it = students.find(rollNumber);
    if (it != students.end()) {
        const Student& student = it->second;
        if (student.gender == 'M' || student.gender == 'm') {
            if (boysCount > 0) {
                boysCount--;
            }
        } else if (student.gender == 'F' || student.gender == 'f') {
            if (girlsCount > 0) {
                girlsCount--;
            }
        }
        students.erase(it);
        cout << "Student with roll number " << rollNumber << " deleted successfully.\n";

        writeStudentsToFile();
    } else {
        cout << "Student with roll number " << rollNumber << " not found.\n";
    }
}

void updateStudent(int rollNumber) {
    auto it = students.find(rollNumber);
    if (it != students.end()) {
        Student& student = it->second;
        int choice;
        cout << "\nUpdate Menu:\n";
        cout << "1. Update Name\n";
        cout << "2. Update CGPA\n";
        cout << "3. Update Gender\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice) || choice < 1 || choice > 4) {
            cout << "Invalid choice. Please enter a number between 1 and 4.\n";
            clearInputBuffer();
            return;
        }

        switch (choice) {
            case 1:
                cout << "Enter new name: ";
                cin.ignore();
                getline(cin, student.name);
                break;
            case 2:
                do {
                    cout << "Enter new CGPA: ";
                    if (!(cin >> student.cgpa) || student.cgpa < 0 || student.cgpa > 4) {
                        cout << "Invalid input. CGPA should be between 0 and 4.\n";
                        clearInputBuffer();
                    } else {
                        break;
                    }
                } while (true);
                break;
            case 3:
                do {
                    if (student.gender == 'M' || student.gender == 'm') {
                        boysCount--;
                    } else if (student.gender == 'F' || student.gender == 'f') {
                        girlsCount--;
                    }

                    cout << "Enter new gender (M/F): ";
                    cin >> student.gender;
                    if (student.gender != 'M' && student.gender != 'm' && student.gender != 'F' && student.gender != 'f') {
                        cout << "Invalid input. Please enter 'M' or 'F'.\n";
                        clearInputBuffer();
                    } else {
                        if (student.gender == 'M' || student.gender == 'm') {
                            boysCount++;
                        } else if (student.gender == 'F' || student.gender == 'f') {
                            girlsCount++;
                        }
                        break;
                    }
                } while (true);
                break;
            case 4:
                return;
        }

        writeStudentsToFile();
        cout << "Student with roll number " << rollNumber << " updated successfully.\n";
    } else {
        cout << "Student with roll number " << rollNumber << " not found.\n";
    }
}

void printGenderCounts() {
    cout << "\nCount of Students:\n";
    cout << "Boys: " << boysCount << endl;
    cout << "Girls: " << girlsCount << endl;
}

void printStudents() {
    cout << "\nList of Students:\n";
    for (const auto& [rollNumber, student] : students) {
        cout << "Roll Number: " << student.rollNumber << ", Name: " << student.name << ", CGPA: " << student.cgpa << ", Gender: " << student.gender << endl;
    }
}

void menu() {
    int rollNumber, choice;
    string name;
    char gender;
    float cgpa;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Student\n";
        cout << "2. Find Student by Roll Number\n";
        cout << "3. Count of Students\n";
        cout << "4. Delete Student\n";
        cout << "5. Update Student\n";
        cout << "6. Print Gender Counts\n";
        cout << "7. Print Students\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                do {
                    cout << "Enter Roll Number: ";
                    if (!(cin >> rollNumber) || rollNumber <= 0) {
                        cout << "Invalid input. Roll number must be a positive integer.\n";
                        clearInputBuffer();
                    } else {
                        break;
                    }
                } while (true);

                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, name);

                do {
                    cout << "Enter CGPA: ";
                    if (!(cin >> cgpa) || cgpa < 0 || cgpa > 4) {
                        cout << "Invalid input. CGPA should be between 0 and 4.\n";
                        clearInputBuffer();
                    } else {
                        break;
                    }
                } while (true);

                do {
                    cout << "Enter Gender (M/F): ";
                    cin >> gender;
                    if (gender != 'M' && gender != 'm' && gender != 'F' && gender != 'f') {
                        cout << "Invalid input. Please enter 'M' or 'F'.\n";
                        clearInputBuffer();
                    } else {
                        break;
                    }
                } while (true);

                addStudent(rollNumber, name, cgpa, gender);
                break;

            case 2:
                cout << "Enter Roll Number: ";
                cin >> rollNumber;
                findStudentByRollNumber(rollNumber);
                break;

            case 3:
                cout << "Total number of students: " << countStudents() << endl;
                break;

            case 4:
                cout << "Enter Roll Number: ";
                cin >> rollNumber;
                deleteStudent(rollNumber);
                break;

            case 5:
                cout << "Enter Roll Number: ";
                cin >> rollNumber;
                updateStudent(rollNumber);
                break;

            case 6:
                printGenderCounts();
                break;

            case 7:
                printStudents();
                break;

            case 8:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Please enter a number between 1 and 8.\n";
                break;
        }

    } while (choice != 8);
}


unordered_map<string, string> readUserDatafromfilelogin(const string& filename);
void writeUserDatatofilelogin(const string& filename, const unordered_map<string, string>& a);
void menu(); 

int main() {
    string filename = "userdata.txt";
    unordered_map<string, string> a = readUserDatafromfilelogin(filename);

    int attempt_count = 0;
    int invalid_option_count = 0;
    int existing_username_count = 0;

    while (true) {
        cout << "1. Login\n2. Register\n3. Reset Password\n4. Exit\nEnter option: ";
        string option;
        cin >> option;
        cin.ignore();  

        if (option == "1") {
            invalid_option_count = 0;
            existing_username_count = 0;
            if (attempt_count >= 5) {
                cout << "You have tried 5 times and you cannot try anymore.\n";
                break;
            }

            cout << "Enter username: ";
            string username;
            getline(cin, username); 

            if (a.find(username) == a.end()) {
                cout << "Invalid username\n";
                attempt_count++;
                if (attempt_count >= 3 && attempt_count < 5) {
                    cout << "Attempt " << attempt_count << " failed. " << 5 - attempt_count << " attempt(s) left.\n";
                }
                continue;
            }

            cout << "Enter password: ";
            string password;
            char ch;
            while ((ch = _getch()) != '\r') { 
                if (ch == '\b') { 
                    if (!password.empty()) {
                        cout << "\b \b";
                        password.pop_back();
                    }
                } else {
                    password.push_back(ch);
                    cout << '*';
                }
            }
            cout << endl;

            if (a[username] == password) {
                cout << "Login successful\n";
                menu();  
                break;   
            } else {
                cout << "Invalid password\n";
                attempt_count++;
                if (attempt_count >= 3 && attempt_count < 5) {
                    cout << "Attempt " << attempt_count << " failed. " << 5 - attempt_count << " attempt(s) left.\n";
                }
            }
        } else if (option == "2") {
            invalid_option_count = 0;
            cout << "Enter new username: ";
            string username;
            getline(cin, username);  

            
            if (a.find(username) != a.end()) {
                cout << "Username already exists\n";
                existing_username_count++;
                if (existing_username_count >= 3 && existing_username_count < 5) {
                    cout << "Attempt " << existing_username_count << " failed. " << 5 - existing_username_count << " attempt(s) left.\n";
                } else if (existing_username_count >= 5) {
                    cout << "You have entered an existing username 5 times. You cannot register anymore.\n";
                    break;
                }
                continue; 
            }

            cout << "Enter new password: ";
            string password;
            char ch;
            while ((ch = _getch()) != '\r') { 
                if (ch == '\b') { 
                    if (!password.empty()) {
                        cout << "\b \b";
                        password.pop_back();
                    }
                } else {
                    password.push_back(ch);
                    cout << '*';
                }
            }
            cout << endl;

            a[username] = password;
            writeUserDatatofilelogin(filename, a);
            cout << "Registration successful\n";
        } else if (option == "3") {  
            invalid_option_count = 0;
            existing_username_count = 0;

            if (attempt_count >= 5) {
                cout << "You have tried 5 times and you cannot try anymore.\n";
                break;
            }

            cout << "Enter username for password reset: ";
            string username;
            getline(cin, username); 

            if (a.find(username) == a.end()) {
                cout << "Username not found\n";
                attempt_count++;
                if (attempt_count >= 3 && attempt_count < 5) {
                    cout << "Attempt " << attempt_count << " failed. " << 5 - attempt_count << " attempt(s) left.\n";
                }
                continue;
            }

            string newPassword, confirmPassword;

            cout << "Enter new password: ";
            char ch;
            while ((ch = _getch()) != '\r') { 
                if (ch == '\b') { 
                    if (!newPassword.empty()) {
                        cout << "\b \b";
                        newPassword.pop_back();
                    }
                } else {
                    newPassword.push_back(ch);
                    cout << '*';
                }
            }
            cout << endl;

            cout << "Confirm new password: ";
            while ((ch = _getch()) != '\r') { 
                if (ch == '\b') { 
                    if (!confirmPassword.empty()) {
                        cout << "\b \b";
                        confirmPassword.pop_back();
                    }
                } else {
                    confirmPassword.push_back(ch);
                    cout << '*';
                }
            }
            cout << endl;

            if (newPassword == confirmPassword) {
                a[username] = newPassword;
                writeUserDatatofilelogin(filename, a);
                cout << "Password reset successful.\n";
            } else {
                cout << "Passwords do not match. Please try again.\n";
            }

        } else if (option == "4") {
            cout << "Exiting\n";
            break;
        } else {
            invalid_option_count++;
            cout << "Invalid option, please try again\n";
            if (invalid_option_count >= 3 && invalid_option_count < 5) {
                cout << "Attempt " << invalid_option_count << " failed. " << 5 - invalid_option_count << " attempt(s) left.\n";
            } else if (invalid_option_count >= 5) {
                cout << "You have entered invalid options 5 times. You cannot choose anymore.\n";
                break;
            }
        }
    }

    return 0;
}