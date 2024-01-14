#include <string>
#include <vector>
using namespace std;
#include "book.hpp"
#include "person.hpp"
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
