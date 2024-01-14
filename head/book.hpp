#include <string>
#include <iostream>
using namespace std;
// Class representing a book
class Book
{
private:
    int bookID;
    string bookName, authorFirstName, authorLastName, bookType;
    Date dueDate;
    Member *borrower;

public:
    // Constructors

    Book(int id, string name, string firstName, string lastName)
        : bookID(id), bookName(name), authorFirstName(firstName),
          authorLastName(lastName), borrower(nullptr), dueDate(0, 0, 0) {}
    Book()
        : bookID(0), bookName(""), authorFirstName(""),
          authorLastName(""), borrower(nullptr), dueDate(0, 0, 0) {}

    // Getter functions for book attributes

    int getBookID() const
    {
        return bookID;
    }

    string getBookName() const
    {
        return bookName;
    }

    string getAuthorFirstName() const
    {
        return authorFirstName;
    }

    string getAuthorLastName() const
    {
        return authorLastName;
    }

    Date getDueDate() const
    {
        return dueDate;
    }

    // Function to set due date for borrowing

    void setDueDate()
    {
        dueDate.setDueDate();
    }

    // Function to return a book

    void returnBook();

    // Function to borrow a book by a member

    void borrowBook(Member &member);
};
