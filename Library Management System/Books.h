#ifndef BOOKS_H
#define BOOKS_H

#include <vector>
#include "Book.h"
#include <sqlite3.h>
enum enSearchWay{byTitle=1,byAuthor,byISBN};
class Books {
private:
    std::vector<Book> bookList;
    sqlite3* db;

    void executeSQL(const std::string& sql);

public:
    Books(sqlite3* database);

    void loadBooksFromDB();
    void addBook(const Book& book);
    void removeBook(const std::string& bookISBN);
    void updateBook(const Book& book);
    const std::vector<Book>& getBooks() const;
    const std::vector<Book>& getBooksBy(enSearchWay way , const std::string& input) const;
};

#endif // BOOKS_H
