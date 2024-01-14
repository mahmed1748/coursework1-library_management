#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "date.hpp"
#include "book.hpp"
#include "person.hpp"
#include "member.hpp"
#include "librarian.hpp"

// myfirst comment
// testing git because error when push
// now works well
using namespace std;

class Member;

// Function to return a book

void Book::returnBook()
{
    borrower = nullptr;
}

// Function to borrow a book by a member

void Book::borrowBook(Member &member)
{
    borrower = &member;
    setDueDate();
    member.setBooksBorrowed(*this);
}

// Function to create a new library member

void Librarian::createMember()
{
    int memberId;
    std::string name, address, email;

    std::cout << "Enter Member ID: ";
    std::cin >> memberId;
    std::cin.ignore();

    std::cout << "Enter Member Name: ";
    std::getline(std::cin, name);

    std::cout << "Enter Member Address: ";
    std::getline(std::cin, address);

    std::cout << "Enter Member Email: ";
    std::getline(std::cin, email);

    Member newMember(memberId, name, address, email);

    this->members.push_back(newMember);

    std::cout << "\nNew Member Created Successfully:\n";
    std::cout << "Member ID: " << newMember.getMemberID() << std::endl;
    std::cout << "Name: " << newMember.getName() << std::endl;
    std::cout << "Address: " << newMember.getAddress() << std::endl;
    std::cout << "Email: " << newMember.getEmail() << std::endl;
}

// Function to issue a book to a library member

void Librarian::issueBookToMember(int bookID, int memberId)
{
    // Find the book by ID
    auto bookIter = std::find_if(books.begin(), books.end(),
                                 [bookID](const Book &book)
                                 { return book.getBookID() == bookID; });

    // Find the member by ID
    auto memberIter = std::find_if(members.begin(), members.end(),
                                   [memberId](const Member &member)
                                   { return member.getMemberID() == memberId; });

    // Check if both book and member exist
    if (bookIter != books.end() && memberIter != members.end())
    {
        // Check if the book is available
        if (bookIter->getDueDate().getYear() == 0)
        {
            // Borrow the book
            bookIter->borrowBook(*memberIter);
            std::cout << "Book issued successfully to Member ID " << memberId << ".\n";
        }
        else
        {
            std::cout << "Book is already borrowed.\n";
        }
    }
    else
    {
        std::cout << "Book or Member not found.\n";
    }
}

// Function to return a book from a library member

void Librarian::returnBookFromMember(Book &book, Member &member)
{
    // Check if the book is borrowed by the given member
    auto iter = std::find_if(member.getBooksBorrowed().begin(), member.getBooksBorrowed().end(),
                             [&book](const Book &borrowedBook)
                             { return borrowedBook.getBookID() == book.getBookID(); });

    if (iter != member.getBooksBorrowed().end())
    {
        // Return the book
        book.returnBook();
        member.getBooksBorrowed().erase(iter);
        std::cout << "Book returned successfully by Member ID " << member.getMemberID() << ".\n";
    }
    else
    {
        std::cout << "Member did not borrow this book.\n";
    }
}

// Function to display books borrowed by a member

void Librarian::displayBorrowedBooks()
{
    int memberId;
    std::cout << "Enter Member ID to display borrowed books: ";
    std::cin >> memberId;

    auto it = std::find_if(members.begin(), members.end(), [memberId](const Member &m)
                           { return m.getMemberID() == memberId; });

    if (it != members.end())
    {
        const Member &member = *it;
        const vector<Book> &borrowedBooks = member.getBooksBorrowed();

        cout << "Books borrowed by Member '" << member.getName() << "':\n";

        if (borrowedBooks.empty())
        {
            cout << "No books borrowed.\n";
            return;
        }

        for (const Book &book : borrowedBooks)
        {
            cout << "Book ID: " << book.getBookID() << ", Title: " << book.getBookName() << endl;
        }
    }
    else
    {
        std::cout << "Member with ID " << memberId << " not found.\n";
    }
}
// Function to calculate fine for a member

void Librarian::calculateFine(const Member &member)
{
    cout << "Calculating fine for Member '" << member.getName() << "':\n";
    const vector<Book> &borrowedBooks = member.getBooksBorrowed();
    const Date currentDate(10, 1, 2023); // Assuming the current date is 10th January 2023

    for (const Book &book : borrowedBooks)
    {
        int daysDifference = currentDate.getYear() - book.getDueDate().getYear();

        if (daysDifference > 3)
        {
            int daysOverdue = daysDifference - 3;
            int fineAmount = daysOverdue * 1;

            cout << "Fine for Book '" << book.getBookName() << "': £" << fineAmount << endl;
        }
    }
}

int main()
{
    // instance of a librarian
    Librarian librarian(1, 50000, "John Librarian", "Library St", "john.librarian@example.com");

    // Menu
    while (true)
    {
        cout << "LIBRARY MANAGEMENT SYSTEM\n\n";
        cout << "[1] Add Member\n";
        cout << "[2] Issue Book\n";
        cout << "[3] Display Borrowed Books\n";
        cout << "[4] Calculate Fine\n";
        cout << "[5] Quit\n\n";

        cout << "Enter Choice: ";
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            librarian.createMember();
            break;

        case 2:
        {
            const std::vector<Book> &allBooks = librarian.getBooks();

            if (!allBooks.empty())
            {
                std::cout << "Available Books:\n";
                for (const Book &book : allBooks)
                {
                    std::cout << "Book ID: " << book.getBookID() << ", Title: " << book.getBookName() << std::endl;
                }

                int bookID;
                std::cout << "Enter Book ID to issue the book: ";
                std::cin >> bookID;

                int memberId;
                std::cout << "Enter Member ID to issue the book: ";
                std::cin >> memberId;

                librarian.issueBookToMember(bookID, memberId);
            }
            else
            {
                std::cout << "No books available. Please add books first.\n";
            }
            break;
        }
        case 3:
        {
            librarian.displayBorrowedBooks();
            break;
        }

        case 4:
        {
            const std::vector<Member> &allMembers = librarian.getMembers();

            if (!allMembers.empty())
            {
                cout << "Available Members:\n";
                for (const Member &member : allMembers)
                {
                    cout << "Member ID: " << member.getMemberID() << ", Name: " << member.getName() << endl;
                }

                int selectedMemberID;
                cout << "Enter Member ID to calculate fine for: ";
                cin >> selectedMemberID;

                auto memberIt = find_if(allMembers.begin(), allMembers.end(), [selectedMemberID](const Member &m)
                                        { return m.getMemberID() == selectedMemberID; });

                if (memberIt != allMembers.end())
                {
                    const Member &selectedMember = *memberIt;

                    const vector<Book> &borrowedBooks = selectedMember.getBooksBorrowed();

                    if (!borrowedBooks.empty())
                    {
                        librarian.calculateFine(selectedMember);
                    }
                    else
                    {
                        cout << "No books borrowed by Member '" << selectedMember.getName() << "'. No fine to calculate.\n";
                    }
                }
                else
                {
                    cout << "Selected Member not found.\n";
                }
            }
            else
            {
                cout << "No members available. Please create a member first.\n";
            }

            break;
        }

        case 5:
            cout << "Quitting the program.\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }

        cout << "\nPress Enter to continue . . .";
        cin.ignore();
        cin.get();
        system("clear");
    }

    return 0;
}
// end