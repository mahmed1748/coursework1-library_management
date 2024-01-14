#include <string>
using namespace std;
#include <vector>
#include "person.hpp"
#include "member.hpp"
#include <fstream>
#include <iomanip>

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

        int bookID, pageCount;
        std::string bookName, authorFirstName, authorLastName, bookType;

        // Assuming the first line in the CSV file contains headers and should be ignored
        std::string header;
        std::getline(fin, header);

        while (fin >> bookID >> std::quoted(bookName) >> pageCount >> std::quoted(authorFirstName) >> std::quoted(authorLastName) >> std::quoted(bookType))
        {
            // You can use the extracted data to create your Book object
            Book newBook(bookID, bookName, authorFirstName + " " + authorLastName, ""); // Assuming 'owner' is not present in the CSV file
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
