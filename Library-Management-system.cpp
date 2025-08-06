#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Structure to store student information
struct Student {
    string name;
    string department;
    int semester;
    string email;
};

// Structure to store book information
struct Book {
    string title;
    string author;
    string edition;
};

// Structure to store date
struct Date {
    int day;
    int month;
    int year;
};
// Function to register a student
void registerStudent(Student& student, ofstream& outfile) {
    cout << "Enter your name: ";
    getline(cin, student.name);
    outfile << "Enter your name: " << student.name << endl;

    cout << "Enter your department: ";
    getline(cin, student.department);
    outfile << "Enter your department: " << student.department << endl;

    cout << "Enter your semester: ";
    cin >> student.semester;
    cin.ignore();
    outfile << "Enter your semester: " << student.semester << endl;

    while (true) {
        cout << "Enter your email (must end with @gmail.com): ";
        getline(cin, student.email);
        outfile << "Enter your email: " << student.email << endl;

        if (student.email.size() >= 10 &&
            student.email.substr(student.email.size() - 10) == "@gmail.com") {
            break;
        } else {
            cout << "Invalid email. Please enter a Gmail address.\n";
            outfile << "Invalid email. Please enter a Gmail address.\n";
        }
    }

    cout << "Registration Successful!\n";
    outfile << "Registration Successful!\n";
}

// Display books
void displayBooks(Book books[], int size, ofstream& outfile) {
    cout << "\nAvailable Books:\n";
    outfile << "\nAvailable Books:\n";
    for (int i = 0; i < size; i++) {
        cout << "Book #" << (i + 1) << ": " << books[i].title << " by " << books[i].author
             << " (" << books[i].edition << ")\n";
        outfile << "Book #" << (i + 1) << ": " << books[i].title << " by " << books[i].author
                << " (" << books[i].edition << ")\n";
    }
}

// Search book with manual validation (no exceptions)
int searchBook(Book books[], int size, ofstream& outfile) {
    string title, author, edition;
    int attempt = 0;
    const int maxAttempts = 3;

    while (attempt < maxAttempts) {
        cout << "\nEnter book title to search: ";
        getline(cin, title);
        outfile << "\nBook Title Searched: " << title << endl;

        cout << "Enter author name: ";
        getline(cin, author);
        outfile << "Author: " << author << endl;

        cout << "Enter edition: ";
        getline(cin, edition);
        outfile << "Edition: " << edition << endl;

        if (title.empty() || author.empty() || edition.empty()) {
            cout << "Error: All fields are required. Please try again.\n";
            outfile << "Error: Empty field detected. Retrying.\n";
            attempt++;
            continue;
        }

        for (int i = 0; i < size; i++) {
            if (books[i].title == title &&
                books[i].author == author &&
                books[i].edition == edition) {
                cout << "Book is available!\n";
                outfile << "Book is available!\n";
                return i;
            }
        }

        cout << "Book not found. Try again.\n";
        outfile << "Book not found. Try again.\n";
        attempt++;
    }

    cout << "Maximum attempts reached. Book search failed.\n";
    outfile << "Maximum attempts reached. Book search failed.\n";
    return -1;
}

// Input date
void inputDate(Date& date, const string& prompt, ofstream& outfile) {
    cout << prompt << " (dd mm yyyy): ";
    outfile << prompt << " (dd mm yyyy): ";
    cin >> date.day >> date.month >> date.year;
    cin.ignore();
    outfile << date.day << "-" << date.month << "-" << date.year << endl;
}

// Convert date to days
int convertToDays(Date date) {
    return date.year * 360 + date.month * 30 + date.day;
}

// Calculate fine
void calculateFine(const Date& borrowDate, const Date& dueDate, const Date& returnDate, ofstream& outfile) {
    int dueDays = convertToDays(dueDate);
    int returnDays = convertToDays(returnDate);

    if (returnDays > dueDays) {
        int overdue = returnDays - dueDays;
        int fine = overdue * 10;
        cout << "You are " << overdue << " days late.\n";
        cout << "Fine: " << fine << " PKR\n";
        outfile << "You are " << overdue << " days late.\n";
        outfile << "Fine: " << fine << " PKR\n";
    } else {
        cout << "Book returned on time. No fine!\n";
        outfile << "Book returned on time. No fine!\n";
    }
}

// ---------------- MAIN FUNCTION ----------------
int main() {
 cout<<"***************************"<<endl;
 cout<<"*Library Management System*"<<endl;
 cout<<"***************************"<<endl;
 cout<<"Group Member"<<endl;
 cout<<"M.Umer Shafqat";

    ofstream outfile("LibraryManagmentSystem.txt", ios::app);
    if (!outfile) {
        cerr << "Error: Could not open file.\n";
        return 1;
    }

    Student student;
    cout<<"Enter the Detail for Registration"<<endl;
    registerStudent(student, outfile);

    Book books[5] = {
        {"C++", "Kaleemullah", "1st"},
        {"Atomic Physics", "Nasir", "2nd"},
        {"Database", "Ms. Qurat", "3rd"},
        {"Applied Physics", "Nasir", "4th"},
        {"ICT", "Bilal", "5th"}
    };

    displayBooks(books, 5, outfile);

    int bookIndex = searchBook(books, 5, outfile);
    if (bookIndex == -1) {
        outfile << "Exiting program due to failed book search.\n";
        outfile.close();
        return 1;
    }

    Date borrowDate, dueDate, returnDate;
    inputDate(borrowDate, "Enter borrow date", outfile);
    inputDate(dueDate, "Enter due date", outfile);
    inputDate(returnDate, "Enter actual return date", outfile);

    calculateFine(borrowDate, dueDate, returnDate, outfile);

    outfile << "-----------------------------------------\n";
    outfile.close();

    return 0;
}
