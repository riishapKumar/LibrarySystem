// LibrarySystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>

class Book
{
public:
    std::string title{ "" };
    std::string author{ "" };
    int ibsn{ 0 };
    int year{ 0 };
    bool availability;

    Book() = default;

    Book(std::string ptitle = "unkown", std::string pauthor = "unkown", int pibsn = 111, int pyear = 0, bool  pavailability = true) :
        title{ ptitle }, author{ pauthor }, ibsn{ pibsn }, year{ pyear }, availability{ pavailability } {}

    /*void print()
    {
        std::cout << year << " " << author << " " << title << " " << ibsn << " ";
        if (availability == true) { std::cout << "true\n"; }
    }*/

    //int getISBN() { return ibsn; }

};

class Member {
private:
    std::string name;
    int memberID;
    std::vector<int> borrowedBooks;

public:
    Member(const std::string& name, int memberID) : name(name), memberID(memberID) {}

    std::string getName() const { return name; }
    int getMemberID() const { return memberID; }
    std::vector<int> getBorrowedBooks() const { return borrowedBooks; }

    void borrowBook(int isbn) {
        borrowedBooks.push_back(isbn);
    }

    bool returnBook(int isbn) {
        for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
            if (*it == isbn) {
                borrowedBooks.erase(it);
                return true;
            }
        }
        return false;
    }
};

class Library 
{
private:
    std::vector<Book> books;
    std::map<int, Member> members;
public:

    void addBook() {
        char ask;
        do {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

            std::cout << "Enter book title: ";
            std::string title;
            std::getline(std::cin >> std::ws, title);

            std::cout << "Enter book author: ";
            std::string author;
            std::getline(std::cin >> std::ws, author);

            int ISBN;
            while (true) {
                std::cout << "Enter book ISBN: ";
                std::cin >> ISBN;

                if (ISBN >= 0) {
                    break;
                }
                std::cout << "Invalid ISBN. Please enter a non-negative value.\n";
            }

            int publicationYear;
            while (true) {
                std::cout << "Enter book publication year: ";
                std::cin >> publicationYear;

                if (publicationYear >= 0) {
                    break;
                }
                std::cout << "Invalid publication year. Please enter a non-negative value.\n";
            }

            std::cout << "Is the book available? (y/n): ";
            char availabilityInput;
            std::cin >> availabilityInput;
            bool isAvailable = (availabilityInput == 'y' || availabilityInput == 'Y');

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

            Book newBook(title, author, ISBN, publicationYear, isAvailable);
            books.push_back(newBook);

            std::cout << "Book added successfully.\n";
            std::cout << "Do you want to add another book (y/n): ";
            std::cin >> ask;
            std::cout << '\n';
        } while (ask == 'y');

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
    }

    void printbook()
    {
        for (const auto& obj : books) {

            std::cout << " " << obj.author << " " << obj.title << " " << obj.year << " " << obj.ibsn << " ";
            if (obj.availability == true) { std::cout << "true\n"; 
            }else { std::cout << "false\n"; }
        }
    }

    void searchBook()
    {
        std::string input;
        int choice;
        char searchAgain;

        do {
            bool bookFound = false;

            std::cout << "Choose the search type:\n";
            std::cout << "1. ISBN\n";
            std::cout << "2. Title\n";
            std::cout << "3. Author\n";
            std::cout << "4. Publication Year\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            std::cin.ignore(); // clear the input buffer

            std::cout << "Enter your search query: ";
            std::getline(std::cin, input);

            switch (choice) {
            case 1: { // Search by ISBN
                int isbn;
                std::istringstream iss(input);
                if (!(iss >> isbn)) {
                    std::cout << "Invalid ISBN format. Please enter a number.\n";
                    break;
                }
                for (const auto& book : books) {
                    if (book.ibsn == isbn) {
                        std::cout << "Book found: " << book.ibsn << ", " << book.title << ", " << book.year << ", " << book.author << ", " << (book.availability ? "Available" : "Not Available") << "\n";
                        bookFound = true;
                        break;
                    }
                }
                if (!bookFound) {
                    std::cout << "No book found with ISBN " << isbn << "\n";
                }
                break;
            }
            case 2: { // Search by Title
                for (const auto& book : books) {
                    if (book.title == input) {
                        std::cout << "Book found: " << book.ibsn << ", " << book.title << ", " << book.year << ", " << book.author << ", " << (book.availability ? "Available" : "Not Available") << "\n";
                        bookFound = true;
                        break;
                    }
                }
                if (!bookFound) {
                    std::cout << "No book found with title " << input << "\n";
                }
                break;
            }
            case 3: { // Search by Author
                for (const auto& book : books) {
                    if (book.author == input) {
                        std::cout << "Book found: " << book.ibsn << ", " << book.title << ", " << book.year << ", " <<book.author << ", " << (book.availability ? "Available" : "Not Available") << "\n";
                        bookFound = true;
                        break;
                    }
                }
                if (!bookFound) {
                    std::cout << "No book found by author " << input << "\n";
                }
                break;
            }
            case 4: { // Search by Publication Year
                int year;
                std::istringstream iss(input);
                if (!(iss >> year)) {
                    std::cout << "Invalid year format. Please enter a number.\n";
                    break;
                }
                for (const auto& book : books) {
                    if (book.year == year) {
                        std::cout << "Book found: " << book.ibsn << ", " << book.title << ", " << book.year << ", " << book.author << ", " << (book.availability ? "Available" : "Not Available") << "\n";
                        bookFound = true;
                        break;
                    }
                }
                if (!bookFound) {
                    std::cout << "No book found published in year " << year << "\n";
                }
                break;
            }
            default: {
                std::cout << "Invalid choice.\n";
                break;
            }
            }

            std::cout << "Would you like to search for another book? (Y/N): ";
            std::cin >> searchAgain;
            std::cin.ignore(); // clear the input buffer
        } while (toupper(searchAgain) == 'Y');

    }

    void removeBook() 
    {
        int isbn;

        std::cout << "Enter the ISBN of the book you want to remove: ";
        std::cin >> isbn;

        int index = -1;
        for (int i = 0; i < books.size(); ++i) {
            if (books[i].ibsn == isbn) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            books.erase(books.begin() + index);
            std::cout << "Book with ISBN " << isbn << " removed successfully.\n";
        }
        else {
            std::cout << "Book with ISBN " << isbn << " not found.\n";
        }
    }
    
    void updateBook()
    {
        char ask;
        do {
            int isbn;
            bool found = false; // Initiate found as false
            std::cout << "Enter the ISBN of the book you want to update: ";
            std::cin >> isbn;
            std::cin.ignore(); // Ignore remaining newline character in the input buffer

            for (Book& book : books) {
                if (book.ibsn == isbn) {
                    found = true;

                    std::string title, author;
                    int publicationYear;
                    char availabilityInput;
                    bool isAvailable;

                    std::cout << "Enter new book title: ";
                    std::getline(std::cin, title);
                    book.title = title; // Update the title

                    std::cout << "Enter new book author: ";
                    std::getline(std::cin, author);
                    book.author = author; // Update the author

                    std::cout << "Enter new book publication year: ";
                    std::cin >> publicationYear;
                    book.year = publicationYear; // Update the publication year

                    std::cout << "Is the book available? (y/n): ";
                    std::cin >> availabilityInput;
                    std::cin.ignore(); // Ignore remaining newline character in the input buffer
                    isAvailable = (availabilityInput == 'y' || availabilityInput == 'Y');
                    book.availability = isAvailable; // Update the availability

                    std::cout << "Book updated successfully.\n";
                    std::cout << "Do you want to update another book (y/n): ";
                    std::cin >> ask;
                    std::cin.ignore();
                    break; // Once the book is found and updated, break the loop
                }
            }

            if (!found) {
                std::cout << "Book with ISBN " << isbn << " not found.\n";
                std::cout << "Do you want to update another book (y/n): ";
                std::cin >> ask;
                std::cin.ignore();
            }
        } while (ask == 'y' || ask == 'Y'); // Update this condition to accept uppercase Y
    }

    void bookIssue() {
        int isbn;
        std::string input;
        char choice;

        do {
            std::cin.ignore();
            std::cout << "Enter the ISBN of the book you want to borrow: ";
            std::getline(std::cin, input);

            std::istringstream iss(input);
            if (iss >> isbn) {
                bool bookFound = false;
                for (Book& book : books) {
                    if (book.ibsn == isbn) {
                        bookFound = true;
                        if (book.availability == true) {
                            book.availability = false;
                            std::cout << "Book issued successfully.\n";
                        }
                        else {
                            std::cout << "Book is currently not available.\n";
                        }
                        break;
                    }
                }
                if (!bookFound) {
                    std::cout << "Book with ISBN " << isbn << " not found.\n";
                }
            }
            else {
                std::cout << "Invalid ISBN entered, please try again.\n";
            }

            std::cout << "Would you like to issue a book? (Y/N): ";
            std::cin >> choice;
            std::cout << '\n';
        } while (choice == 'Y' || choice == 'y');

    }

    void bookReturn() {
        int isbn;
        std::string input;
        char choice;

        do {
            std::cin.ignore();
            std::cout << "Enter the ISBN of the book you want to return: ";
            std::getline(std::cin, input);

            std::istringstream iss(input);
            if (iss >> isbn) {
                bool bookFound = false;
                for (Book& book : books) {
                    if (book.ibsn == isbn) {
                        bookFound = true;
                        if (book.availability == false) {
                            book.availability = true;
                            std::cout << "Book returned successfully.\n";
                        }
                        else {
                            std::cout << "Book is currently available.\n";
                        }
                        break;
                    }
                }
                if (!bookFound) {
                    std::cout << "Book with ISBN " << isbn << " not found.\n";
                }
            }
            else {
                std::cout << "Invalid ISBN entered, please try again.\n";
            }

            std::cout << "Would you like to return a book? (Y/N): ";
            std::cin >> choice;
            std::cout << '\n';
        } while (choice == 'Y' || choice == 'y');

    }

    void loadData() {
        std::ifstream inFile("library.txt");
        std::string dummyLine;  // For consuming leftover newline characters

        if (inFile.is_open()) {
            books.clear(); // Clear any existing books
            int isbn, pubYear;
            std::string title, author;
            bool availability;
            while (inFile >> isbn) {
                std::getline(inFile, dummyLine);  // Consume leftover newline
                std::getline(inFile, title);
                std::getline(inFile, author);
                inFile >> pubYear;
                std::getline(inFile, dummyLine);  // Consume leftover newline
                inFile >> std::boolalpha >> availability; // read bool as text (true/false)
                books.push_back(Book(title, author, isbn, pubYear, availability));
            }
            inFile.close();
        }
        else {
            std::cout << "Unable to open file for loading.\n";
        }
    }

    void saveData() const {
        std::ofstream outFile("library.txt");

        if (outFile.is_open()) {
            for (const Book& book : books) {
                outFile << book.ibsn << "\n";
                outFile << book.title << "\n";
                outFile << book.author << "\n";
                outFile << book.year << "\n";
                outFile << book.availability << "\n";
            }
            outFile.close();
        }
        else {
            std::cout << "Unable to open file for saving.\n";
        }
    }

    void addMember() {
        std::string name;
        int memberID;
        std::cout << "Enter member name: ";
        std::cin >> name;
        std::cout << "Enter member ID: ";
        std::cin >> memberID;

        Member newMember(name, memberID);
        members.insert({ memberID, newMember });
    }

    void removeMember() {
        int memberID;
        std::cout << "Enter member ID: ";
        std::cin >> memberID;
        members.erase(memberID);
    }

};

class Screen
{
public:
    int option{};

    void transistion() {
        char back;
        std::cout << "Hit q to quit and go back to the main menu: ";
        std::cin >> back;
        system("CLS");

    }

    void main()
    {
        std::cout << "\n\t\t\t\t\t**************************************\n";
        std::cout << "\t\t\t\t\t\t\tMAIN MENU";
        std::cout << "\n\t\t\t\t\t**************************************\n";

        std::cout << "\n\t\t\t 1. BOOK ISSUE";
        std::cout << "\t\t\t\t 2. RETURN BOOK";
        std::cout << "\n\n\t\t\t 3. VIEW BOOKS/STATUS";
        std::cout << "\t\t\t 4. ADD BOOK";
        std::cout << "\n\n\t\t\t 5. REMOVE BOOK";
        std::cout << "\t\t\t\t 6. SEARCH BOOK";
        std::cout << "\n\n\t\t\t 7. ADD MEMBER";
        std::cout << "\t\t\t\t 8. REMOVE MEMBER";
        std::cout << "\n\n\t\t\t 9. UPDATE BOOK";
        std::cout << "\t\t\t\t [0]. EXIT";
        std::cout << "\n\n Enter Choice :";

        std::cin >> option;

    }

    void ADDBOOK()
    {
        std::cout << "\n\t\t\t\t\t**************************************\n";
        std::cout << "\t\t\t\t\t\t\tADD BOOK";
        std::cout << "\n\t\t\t\t\t**************************************\n";
    }

    void SEARCHBOOK()
    {
        std::cout << "\n\t\t\t\t\t**************************************\n";
        std::cout << "\t\t\t\t\t\t\tSEARCH BOOK";
        std::cout << "\n\t\t\t\t\t**************************************\n";
    }

    void REMOVEBOOK()
    {
        std::cout << "\n\t\t\t\t\t**************************************\n";
        std::cout << "\t\t\t\t\t\t\tREMOVE BOOK";
        std::cout << "\n\t\t\t\t\t**************************************\n";
    }

    void UPDATEBOOK()
    {
        std::cout << "\n\t\t\t\t\t**************************************\n";
        std::cout << "\t\t\t\t\t\t\tUPDATE BOOK";
        std::cout << "\n\t\t\t\t\t**************************************\n";
    }

    void BOOKISSUE()
    {
        std::cout << "\n\t\t\t\t\t**************************************\n";
        std::cout << "\t\t\t\t\t\t\tISSUE BOOK";
        std::cout << "\n\t\t\t\t\t**************************************\n";
    }

    void BOOKRETURN()
    {
        std::cout << "\n\t\t\t\t\t**************************************\n";
        std::cout << "\t\t\t\t\t\t\tRETURN BOOK";
        std::cout << "\n\t\t\t\t\t**************************************\n";
    }



};

int interface()
{
    Screen screen;
    Library library;
    
    while (true) {
        library.loadData();
        screen.main();
        system("CLS");

        if (screen.option == 1) {
            //std::cout << "Give Book";
            screen.BOOKISSUE();
            library.bookIssue();
            screen.transistion();

        }
        else if (screen.option == 2) {
            screen.BOOKRETURN();
            library.bookReturn();
            screen.transistion();

        }
        else if (screen.option == 3) {
            //std::cout << "VM Issue Book";
            library.printbook();
            screen.transistion();
        }
        else if (screen.option == 4) {
            //std::cout << "Add Book";
            screen.ADDBOOK();
            library.addBook();
            screen.transistion();
        }
        else if (screen.option == 5) {
            screen.REMOVEBOOK();
            library.removeBook();
            screen.transistion();

        }
        else if (screen.option == 6) {
            //std::cout << "BOOK BOOK BOOK";
            screen.SEARCHBOOK();
            library.searchBook();
            screen.transistion();
        }
        else if (screen.option == 7) {
            std::cout << "New member";
        }
        else if (screen.option == 8) {
            std::cout << "Cancel member";
        }
        else if (screen.option == 9) {
            screen.UPDATEBOOK();
            library.updateBook();
            screen.transistion();
        }
        else if (screen.option == 0) {
            library.saveData();
            std::cout << "BYE BYE";
            break;
        }
        else {
            std::cout << "Invalid option. Please try again." << std::endl;
        }
    }


    return 0;
}

int main()
{
    interface();




    return 0;
}

