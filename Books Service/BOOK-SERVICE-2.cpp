#include <iostream>
#include <string>
#include <ctime>
#include <sstream>


// Helper function to convert an integer to a string
template <typename T>
std::string to_string(T value) {
    std::ostringstream os;
    os << value;
    return os.str();
}

using namespace std;
char choice;

// Structure for storing book information
struct Book {
    string title;
    string author;
    int year;
    int semester;
    string edition;
    bool available;
    Book* next;
};

// Structure for storing student information
struct Student {
    string name;
    string id;
    int year;
    int semester;
    string borrowingDate;
    Book* borrowedBook;
    Student* next;
};

// The starting(first) node Linked list for storing books--
Book* bookList = NULL;

//The starting (first) Linked list for storing students--
Student* studentList = NULL;

// Function to find a book by title
Book* findBook(string title) {
    Book* temp = bookList;
    while (temp != NULL) {
        if (temp->title == title) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL; // Book not found
}

// A Function to display login form
bool login() {
    string username, password;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    // Check if the username and password match the admin credentials
    if (username == "ASTU" && password == "DSA123") {
        cout << "Login successful!" << endl;
        return true;
    } else {
        cout << "          username and  password are incorrect..please try again." << endl;
        cout<<'\n';
        cout<<'\n';
        return false;
    }
}

// Function to add a book
void addBook() {
    cout << "=== Add Book ===" << endl;

    int numBooks;
    cout << "Enter the number of books you want to add: ";
    cin >> numBooks;

    int year, semester;
    cout << "Enter the year: ";
    cin >> year;
    cout << "Enter the semester: ";
    cin >> semester;

    cin.ignore(); // the purpose of  .igonre ->to Ignore the newline character

    for (int i = 0; i < numBooks; i++) {
        string title, author, edition;

        cout << "\nBook " << i+1 << ":\n";
        cout << "Enter the book title: ";
        getline(cin, title);
        cout << "Enter the author: ";
        getline(cin, author);
        cout << "Enter the edition: ";
        getline(cin, edition);

        Book* newBook = new Book();
        newBook->year = year;
        newBook->semester = semester;
        newBook->title = title;
        newBook->author = author;
        newBook->edition = edition;
        newBook->available = true;
        newBook->next = NULL;

        if (bookList == NULL) {
            bookList = newBook;
        } else {
            Book* temp = bookList;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newBook;
        }

        cout << "Book added successfully!" << endl;
    }
}

//==================================================this Function is to remove a book===================================================================
void removeBook() {
    string title;
    cout << "=== Remove Book ===" << endl;
    cout << "Enter the title of the book to remove: ";
    cin.ignore();
    getline(cin, title);

    Book* temp = bookList;
    Book* prev = NULL;
    bool found = false;

    while (temp != NULL) {
        if (temp->title == title) {
            found = true;
            break;
        }
        prev = temp;
        temp = temp->next;
    }

    if (found) {
        if (prev == NULL) {
            bookList = temp->next;
        } else {
            prev->next = temp->next;
        }
        delete temp;
        cout << "Book removed successfully!" << endl;
    } else {
        cout << "Book not found!" << endl;
    }
}

//====================================================================== This is a Function to borrow a book==================================================
void LendBook() {
    int year, semester;
    cout << "=== Lend A Book ===" << endl;
    cout << "Enter student's year: ";
    cin >> year;
    cout << "Enter student's semester: ";
    cin >> semester;

    Book* temp = bookList;
    bool found = false;

    while (temp != NULL) {
        if (temp->year == year && temp->semester == semester && temp->available == true) {
            found = true;
            break;
        }
        temp = temp->next;
    }

    if (found) {
        string name, id;
        cout << "Enter student's name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter student's ID: ";
        getline(cin, id);

        // Get current date and time
        time_t now = time(0);
        tm* currentDate = localtime(&now);
        string borrowingDate = to_string(currentDate->tm_mday) + "/" + to_string(currentDate->tm_mon + 1) + "/" + to_string(currentDate->tm_year + 2014);

        // Display available books for borrowing
        cout << "\nAvailable Books for Lending:" << endl;
        int bookCount = 0;
        int optionNumber = 1; // Added optionNumber variable
        while (temp != NULL) {
            if (temp->year == year && temp->semester == semester && temp->available == true) {
                cout << optionNumber << ". " << temp->title << " by " << temp->author << endl; // Display option number
                optionNumber++; // Increment option number
                bookCount++;
            }
            temp = temp->next;
        }

        if (bookCount > 0) {
            int selectedOption; // Added selectedOption variable
            cout << "Enter the number of the book you want to Lend: ";
            cin >> selectedOption;

            // Find the selected book
            temp = bookList;
            Book* selectedBook = NULL;
            int currentOption = 1;
            while (temp != NULL) {
                if (temp->year == year && temp->semester == semester && temp->available == true) {
                    if (currentOption == selectedOption) {
                        selectedBook = temp;
                        break;
                    }
                    currentOption++;
                }
                temp = temp->next;
            }

            if (selectedBook != NULL) {
                // Create a new student record
                Student* newStudent = new Student();
                newStudent->name = name;
                newStudent->id = id;
                newStudent->year = year;
                newStudent->semester = semester;
                newStudent->borrowingDate = borrowingDate;
                newStudent->borrowedBook = selectedBook;
                newStudent->next = NULL;

                // Update book availability
                selectedBook->available = false;

                // Add student to the linked list
                if (studentList == NULL) {
                    studentList = newStudent;
                } else {
                    Student* temp2 = studentList;
                    while (temp2->next != NULL) {
                        temp2 = temp2->next;
                    }
                    temp2->next = newStudent;
                }

                cout << "Book Lended successfully!" << endl;
            } else {
                cout << "Book not available or invalid option number!" << endl;
            }
        } else {
            cout << "No available books for Lending." << endl;
        }
    } else {
        cout << "Book not available!" << endl;
    }
}

// ==========================================================This Function  is to return a book==============================================================
void returnBook() {
    cout << "=== Return Book ===" << endl;
    string name, id;
    cout << "Enter student's name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter student's ID: ";
    getline(cin, id);

    // Find the student record
    Student* temp = studentList;
    Student* previous = NULL;
    bool found = false;

    while (temp != NULL) {
        if (temp->name == name && temp->id == id) {
            found = true;
            break;
        }
        previous = temp;
        temp = temp->next;
    }

    if (found) {
        string bookTitle;
        cout << "Enter the name of the book you want to return: ";
        getline(cin, bookTitle);

        // Find the borrowed book
        Book* borrowedBook = temp->borrowedBook;

        if (borrowedBook != NULL && borrowedBook->title == bookTitle) {
            // Update book availability
            borrowedBook->available = true;

            // Delete the student record
            if (previous == NULL) {
                studentList = temp->next;
            } else {
                previous->next = temp->next;
            }
            delete temp;

            cout << "Book returned successfully!" << endl;
        } else {
            cout << "Invalid book title or book not borrowed by you!" << endl;
        }
    } else {
        cout << "No record found for the provided name and ID!" << endl;
    }
}


//===============================================================Function to search for a book===============================================================
void searchBook() {
int year, semester;
cout << "=== Search Book ===" << endl;
cout << "Enter the year: ";
cin >> year;
cout << "Enter the semester: ";
cin >> semester;
Book* temp = bookList;
bool found = false;

cout << "==== Book Search Results ====" << endl;
cout << "Title\t\tAuthor" << endl;

while (temp != NULL) {
    if (temp->year == year && temp->semester == semester) {
        cout << temp->title << "\t\t" << temp->author << endl;
        found = true;
    }
    temp = temp->next;
}

if (!found) {
    cout << "No books found for the given year and semester." << endl;
}
}

//=========================================================Function to display bookstore information=========================================================
void displayBookstore() {
cout << "=== Bookstore Information ===" << endl;
cout << "Title\t\tAuthor\t\tYear\t\tSemester\tAvailability" << endl;
Book* temp = bookList;
while (temp != NULL) {
    cout << temp->title << "\t\t" << temp->author << "\t\t" << temp->year << "\t\t" << temp->semester << "\t\t";
    if (temp->available) {
        cout << "Available" << endl;
    } else {
        cout << "Not Available" << endl;
    }
    temp = temp->next;
}
}



// ==========================================================Function to display borrow information===============================
void displayLendInfo() {
cout << "=== Lend Information ===" << endl;
cout << "Name\t\tID\t\tYear\t\tSemester\tLending Date\t\tBook Title\t\tAuthor" << endl;
if (studentList == NULL) {
    cout << "No Lend records available." << endl;
    return;
}

Student* temp = studentList;
while (temp != NULL) {
    cout << temp->name << "\t\t" << temp->id << "\t\t" << temp->year << "\t\t" << temp->semester << "\t\t" << temp->borrowingDate;
    if (temp->borrowedBook != NULL) {
        cout << "\t\t" << temp->borrowedBook->title << "\t\t" << temp->borrowedBook->author;
    } else {
        cout << "\t\tN/A\t\tN/A"; // If no book is borrowed
    }
    cout << endl;
    temp = temp->next;
}
}
void Abouttheproject(){
   cout<<"This project is designed to help manage books and borrowing information in a university bookstore. It provides a user-friendly interface for bookstore staff and students to perform various tasks. With this platform, you can ADD a book,REMOVE a book, LEND a book for a student  ,RECORD the borrowed information, DISPALY the bookstore(the avaialable book information) the  BORROWED student information and like this:platform aims to streamline the book management process, ensuring efficient borrowing and tracking of books within the university bookstore."<<endl;




}
// Function to display the main menu
void displayMenu() {
cout << "\n                     ===== ASTU - BOOK - SERVICE  =====" << endl;

cout<<"What  would you like to do today?"<<endl;
cout << "                           1. Add Book" << endl;
cout << "                           2. Remove Book" << endl;
cout << "                           3. Lend Book" << endl;
cout << "                           4. Return Book" << endl;
cout << "                           5. Search Book" << endl;
cout << "                           6. Display Bookstore Information" << endl;
cout << "                           7. Display Lend Information" << endl;
cout << "                           8. About the project" << endl;
cout << "                           9. Exit" << endl;
cout << "                   =====================================" << endl;
}

int main() {
// Login
cout << "                        === WELCOME TO ASTU CLASSIC SERVICE SYSTEM ===" << endl;
bool b = login();
while (!b) {
b=login();
}

int choice;
do {
       displayMenu();
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            addBook();
            break;
        case 2:
            removeBook();
            break;
        case 3:
            LendBook();
            break;
        case 4:
            returnBook();
            break;
        case 5:
            searchBook();
            break;
        case 6:
            displayBookstore();
            break;
        case 7:
            displayLendInfo();
            break;
        case 8:
           Abouttheproject();
            break;
        case 9:
            cout << "HAVE A GOOD TIME.. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
    }


} while (choice != 8);

return 0;

}

