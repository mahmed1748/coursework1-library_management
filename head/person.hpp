#include <string>
#include <iostream>
using namespace std;
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
