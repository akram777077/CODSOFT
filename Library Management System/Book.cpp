#include "Book.h"
#include <sstream>

// Constructor
Book::Book(const std::string& bookTitle, const std::string& bookAuthor, const std::string& bookISBN, bool isAvailable, std::time_t checkoutTime)
    : title(bookTitle), author(bookAuthor), isbn(bookISBN), available(isAvailable), checkoutDate(checkoutTime) {}

// Getters
std::string Book::getTitle() const {
    return title;
}

std::string Book::getAuthor() const {
    return author;
}

std::string Book::getISBN() const {
    return isbn;
}

bool Book::isAvailable() const {
    return available;
}

std::time_t Book::getCheckoutDate() const {
    return checkoutDate;
}

// Setters
void Book::setTitle(const std::string& bookTitle) {
    title = bookTitle;
}

void Book::setAuthor(const std::string& bookAuthor) {
    author = bookAuthor;
}

void Book::setISBN(const std::string& bookISBN) {
    isbn = bookISBN;
}

void Book::setAvailability(bool isAvailable) {
    available = isAvailable;
}

void Book::setCheckoutDate(std::time_t checkoutTime) {
    checkoutDate = checkoutTime;
}

// Return book details as a string
std::string Book::getDetails() const {
    std::ostringstream details;
    details << "Title: " << title << "\n"
            << "Author: " << author << "\n"
            << "ISBN: " << isbn << "\n"
            << "Available: " << (available ? "Yes" : "No") << "\n"
            << "Checkout Date: " << (checkoutDate ? std::ctime(&checkoutDate) : "Not checked out")
            <<"\n";
    return details.str();
}
