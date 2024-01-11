#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "library-system.cpp" // Include your source file directly

TEST_CASE("Date Class Test", "[Date]")
{
    // Your Date class tests go here
    // Example:
    Date date(10, 1, 2023);

    REQUIRE(date.getYear() == 2023);
    // Add more test cases as needed
}

TEST_CASE("Book Class Test", "[Book]")
{
    // Your Book class tests go here
    // Example:
    Book book(1, "Test Book", "John", "Doe");

    REQUIRE(book.getBookID() == 1);
    REQUIRE(book.getBookName() == "Test Book");
    // Add more test cases as needed
}

TEST_CASE("Librarian Class Test", "[Librarian]")
{
    // Your Librarian class tests go here
    // Example:
    Librarian librarian(1, 50000, "John Librarian", "Library St", "john.librarian@example.com");

    REQUIRE(librarian.getStaffID() == 1);
    REQUIRE(librarian.getSalary() == 50000);
    // Add more test cases as needed
}

// Add more test cases for other classes and functions as needed
