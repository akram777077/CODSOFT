#include "Book.h"
#include <iostream>

Book::Book(const std::string& bookTitle, const std::string& bookAuthor, const std::string& bookISBN, bool isAvailable)
    : title(bookTitle), author(bookAuthor), isbn(bookISBN), available(isAvailable) {}



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

void Book::printDetails() const {
    std::cout << "Title: " << title << "\n"
              << "Author: " << author << "\n"
              << "ISBN: " << isbn << "\n"
              << "Available: " << (available ? "Yes" : "No") << "\n";
}
