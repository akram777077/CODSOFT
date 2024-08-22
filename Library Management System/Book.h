#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
private:
    std::string title;
    std::string author;
    std::string isbn;
    bool available;

public:
    Book(const std::string& bookTitle, const std::string& bookAuthor, const std::string& bookISBN, bool isAvailable);

    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getISBN() const;
    bool isAvailable() const;

    void setTitle(const std::string& bookTitle);
    void setAuthor(const std::string& bookAuthor);
    void setISBN(const std::string& bookISBN);
    void setAvailability(bool isAvailable);

    void printDetails() const;
};

#endif // BOOK_H
