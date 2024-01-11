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
class Date
{
private:
    int day;
    int month;
    int year;

public:
    Date() : day(0), month(0), year(0) {}

    Date(int dd, int mm, int yyyy)
        : day(dd), month(mm), year(yyyy) {}

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

    int getYear() const
    {
        return year;
    }
};

class Member;
class Book
{
private:
    int bookID;
    string bookName, authorFirstName, authorLastName, bookType;
    Date dueDate;
    Member *borrower;

public:
    Book(int id, string name, string firstName, string lastName)
        : bookID(id), bookName(name), authorFirstName(firstName),
          authorLastName(lastName), borrower(nullptr), dueDate(0, 0, 0) {}
    Book()
        : bookID(0), bookName(""), authorFirstName(""),
          authorLastName(""), borrower(nullptr), dueDate(0, 0, 0) {}

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

    void setDueDate()
    {
        dueDate.setDueDate();
    }

    void returnBook();

    void borrowBook(Member &member);
};

class Person
{
private:
    string name, address, email;

public:
    Person() {}

    Person(string n, string addr, string e)
        : name(n), address(addr), email(e) {}

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

class Member : public Person
{
private:
    int memberID;
    vector<Book> booksBorrowed;

public:
    Member(int id, string n, string addr, string e)
        : memberID(id), Person(n, addr, e) {}

    int getMemberID() const
    {
        return memberID;
    }

    vector<Book> getBooksBorrowed() const
    {
        return booksBorrowed;
    }

    void setBooksBorrowed(const Book &book)
    {
        booksBorrowed.push_back(book);
    }
};

class Librarian : public Person
{
private:
    int staffID, salary;
    std::vector<Member> members;
    std::vector<Book> books;

public:
    Librarian(int id, int sal, string n, string addr, string e)
        : staffID(id), salary(sal), Person(n, addr, e) {}

    int getStaffID() const
    {
        return staffID;
    }

    int getSalary() const
    {
        return salary;
    }

    void setStaffID(int id)
    {
        staffID = id;
    }

    void setSalary(int sal)
    {
        salary = sal;
    }
    void readBooksFromCSV(const std::string &filename)
    {
        std::ifstream fin(filename);

        if (!fin.is_open())
        {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        // Assuming CSV structure: BookID,BookName,Author,Owner
        int bookID;
        std::string bookName, author, owner;

        while (fin >> bookID >> std::quoted(bookName) >> std::quoted(author) >> std::quoted(owner))
        {
            Book newBook(bookID, bookName, author, owner);
            this->books.push_back(newBook);
        }

        fin.close();
    }
    const std::vector<Book> &getBooks() const
    {
        return books;
    }
    const std::vector<Member> &getMembers() const
    {
        return members;
    }

    void createMember();

    void issueBookToMember(int bookID, int memberId); // Updated declaration

    void returnBookFromMember(Book &book, Member &member);

    void displayBorrowedBooks();

    void calculateFine(const Member &member);
};

void Book::returnBook()
{
    borrower = nullptr;
}

void Book::borrowBook(Member &member)
{
    borrower = &member;
    setDueDate();
    member.setBooksBorrowed(*this);
}
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

    // Store the created member in the vector
    this->members.push_back(newMember);

    std::cout << "\nNew Member Created Successfully:\n";
    std::cout << "Member ID: " << newMember.getMemberID() << std::endl;
    std::cout << "Name: " << newMember.getName() << std::endl;
    std::cout << "Address: " << newMember.getAddress() << std::endl;
    std::cout << "Email: " << newMember.getEmail() << std::endl;
}
void Librarian::issueBookToMember(int bookID, int memberId)
{
    auto bookIt = std::find_if(books.begin(), books.end(), [bookID](const Book &b)
                               { return b.getBookID() == bookID; });

    if (bookIt != books.end())
    {
        Book &book = *bookIt;

        if (book.getDueDate().getYear() != 0)
        {
            std::cout << "Book is already issued.\n";
            return;
        }

        auto memberIt = std::find_if(members.begin(), members.end(), [memberId](const Member &m)
                                     { return m.getMemberID() == memberId; });

        if (memberIt != members.end())
        {
            Member &member = *memberIt;
            std::cout << "Issuing book '" << book.getBookName() << "' to Member '" << member.getName() << "'.\n";
            book.borrowBook(member);
            std::cout << "Book Issued Successfully!\n";
        }
        else
        {
            std::cout << "Member with ID " << memberId << " not found.\n";
        }
    }
    else
    {
        std::cout << "Book with ID " << bookID << " not found.\n";
    }
}

void Librarian::returnBookFromMember(Book &book, Member &member)
{
    if (book.getDueDate().getYear() == 0 || book.getDueDate().getYear() > 0)
    {
        cout << "Book is not issued or already returned.\n";
        return;
    }

    cout << "Returning book '" << book.getBookName() << "' from Member '" << member.getName() << "'.\n";
    book.returnBook();
    cout << "Book Returned Successfully!\n";
}
void Librarian::displayBorrowedBooks()
{
    // Prompt the user to enter the Member ID
    int memberId;
    std::cout << "Enter Member ID to display borrowed books: ";
    std::cin >> memberId;

    // Find the member with the entered ID in the vector
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

void Librarian::calculateFine(const Member &member)
{
    cout << "Calculating fine for Member '" << member.getName() << "':\n";
    const vector<Book> &borrowedBooks = member.getBooksBorrowed();
    const Date currentDate(10, 1, 2023); // Assuming the current date is 10th January 2023

    for (const Book &book : borrowedBooks)
    {
        // Calculate the difference in days between the current date and the due date
        int daysDifference = currentDate.getYear() - book.getDueDate().getYear();

        // Check if the book is overdue (excluding the 3 days grace period)
        if (daysDifference > 3)
        {
            int daysOverdue = daysDifference - 3;
            int fineAmount = daysOverdue * 1; // 1£ fine for each additional day

            cout << "Fine for Book '" << book.getBookName() << "': £" << fineAmount << endl;
        }
    }
}

int main()
{
    Librarian librarian(1, 50000, "John Librarian", "Library St", "john.librarian@example.com");

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
            // Assuming books are already available (read from "library_books.csv")
            const std::vector<Book> &allBooks = librarian.getBooks();

            if (!allBooks.empty())
            {
                // Display available books
                std::cout << "Available Books:\n";
                for (const Book &book : allBooks)
                {
                    std::cout << "Book ID: " << book.getBookID() << ", Title: " << book.getBookName() << std::endl;
                }

                // Prompt the user to enter the Book ID
                int bookID;
                std::cout << "Enter Book ID to issue the book: ";
                std::cin >> bookID;

                // Prompt the user to enter the Member ID
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
            // Calculate fine for a specific member
            const std::vector<Member> &allMembers = librarian.getMembers();

            if (!allMembers.empty())
            {
                // Display available members
                cout << "Available Members:\n";
                for (const Member &member : allMembers)
                {
                    cout << "Member ID: " << member.getMemberID() << ", Name: " << member.getName() << endl;
                }

                // Prompt user to select a member
                int selectedMemberID;
                cout << "Enter Member ID to calculate fine for: ";
                cin >> selectedMemberID;

                // Find the selected member in the vector
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
        cin.ignore();    // Ignore newline character
        cin.get();       // Wait for Enter key
        system("clear"); // Clear screen
    }

    return 0;
}