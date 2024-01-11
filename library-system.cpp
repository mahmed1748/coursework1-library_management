#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

// myfirst comment
// testing git because error when push
// now works well
using namespace std;

// Class representing a date
class Date
{
private:
    int day;
    int month;
    int year;

public:
    // Constructors

    Date() : day(0), month(0), year(0) {}

    Date(int dd, int mm, int yyyy)
        : day(dd), month(mm), year(yyyy) {}

    // Function to set due date (increment by 3 days)

    void setDueDate()
    {
        day += 3;
        if (day > 31)
        {
            day -= 31;
            month += 1;
        }
        if (month > 12)
        {
            month -= 12;
            year += 1;
        }
    }

    // Getter for the year

    int getYear() const
    {
        return year;
    }
};

class Member;

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

// Class representing a person

class Person
{
private:
    string name, address, email;

public:
    // Constructors

    Person() {}

    Person(string n, string addr, string e)
        : name(n), address(addr), email(e) {}

    // Getter functions for person attributes

    string getName() const
    {
        return name;
    }

    string getAddress() const
    {
        return address;
    }

    string getEmail() const
    {
        return email;
    }

    // Setter functions for person attributes

    void setName(string n)
    {
        name = n;
    }

    void setAddress(string addr)
    {
        address = addr;
    }

    void setEmail(string e)
    {
        email = e;
    }
};

// Class representing a library member, inheriting from Person

class Member : public Person
{
private:
    int memberID;
    vector<Book> booksBorrowed;

public:
    // Constructor

    Member(int id, string n, string addr, string e)
        : memberID(id), Person(n, addr, e) {}

    // Getter functions for member attributes

    int getMemberID() const
    {
        return memberID;
    }

    vector<Book> getBooksBorrowed() const
    {
        return booksBorrowed;
    }

    // Function to set books borrowed by a member

    void setBooksBorrowed(const Book &book)
    {
        booksBorrowed.push_back(book);
    }
};

// Class representing a librarian, inheriting from Person

class Librarian : public Person
{
private:
    int staffID, salary;
    std::vector<Member> members;
    std::vector<Book> books;

public:
    // Constructor

    Librarian(int id, int sal, string n, string addr, string e)
        : staffID(id), salary(sal), Person(n, addr, e) {}

    // Getter functions for librarian attributes

    int getStaffID() const
    {
        return staffID;
    }

    int getSalary() const
    {
        return salary;
    }

    // Setter functions for librarian attributes

    void setStaffID(int id)
    {
        staffID = id;
    }

    void setSalary(int sal)
    {
        salary = sal;
    }

    // Function to read books data from a CSV file

    void readBooksFromCSV(const std::string &filename)
    {
        std::ifstream fin(filename);

        if (!fin.is_open())
        {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        int bookID;
        std::string bookName, author, owner;

        while (fin >> bookID >> std::quoted(bookName) >> std::quoted(author) >> std::quoted(owner))
        {
            Book newBook(bookID, bookName, author, owner);
            this->books.push_back(newBook);
        }

        fin.close();
    }

    // Getter functions for books and members

    const std::vector<Book> &getBooks() const
    {
        return books;
    }
    const std::vector<Member> &getMembers() const
    {
        return members;
    }

    // Function to create a new library member
    void createMember();

    // Function to issue a book to a library member
    void issueBookToMember(int bookID, int memberId);

    // Function to return a book from a library member
    void returnBookFromMember(Book &book, Member &member);

    // Function to display books borrowed by a member
    void displayBorrowedBooks();

    // Function to calculate fine for a member
    void calculateFine(const Member &member);
};

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