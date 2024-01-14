#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "library-system.cpp"

TEST_CASE("Date Class Test", "[Date]")
{
    Date date(10, 1, 2023);
    REQUIRE(date.getYear() == 2023);
}

// book test case
TEST_CASE("Book Class Test", "[Book]")
{
    Book book(1, "Test Book", "John", "Doe");
    REQUIRE(book.getBookID() == 1);
    REQUIRE(book.getBookName() == "Test Book");
}

// librarian test case
TEST_CASE("Librarian Class Test", "[Librarian]")
{
    Librarian librarian(1, 50000, "John Librarian", "Library St", "john.librarian@example.com");
    REQUIRE(librarian.getStaffID() == 1);
    REQUIRE(librarian.getSalary() == 50000);
}