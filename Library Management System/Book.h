#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <ctime>

class Book {
private:
    std::string title;
    std::string author;
    std::string isbn;
    bool available;
    std::time_t checkoutDate; // Time of checkout

public:
    Book(const std::string& bookTitle, const std::string& bookAuthor, const std::string& bookISBN, bool isAvailable, std::time_t checkoutTime = 0);

    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getISBN() const;
    bool isAvailable() const;
    std::time_t getCheckoutDate() const;

    void setTitle(const std::string& bookTitle);
    void setAuthor(const std::string& bookAuthor);
    void setISBN(const std::string& bookISBN);
    void setAvailability(bool isAvailable);
    void setCheckoutDate(std::time_t checkoutTime);

    std::string getDetails() const; // Returns book details as a string
};

#endif // BOOK_H
