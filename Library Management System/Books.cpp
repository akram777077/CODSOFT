#include "Books.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>

// Constructor: Initialize the Books object with a database connection
Books::Books(sqlite3* database) : db(database) {}

// Helper function to execute an SQL statement
void Books::executeSQL(const std::string& sql) {
    char* errorMessage = nullptr;
    int result = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage);
    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        throw std::runtime_error("Failed to execute SQL: " + sql);
    }
}

// Load books from the database into the bookList
void Books::loadBooksFromDB() {
    std::string sql = "SELECT title, author, isbn, available FROM Books";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare statement");
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string author = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string isbn = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        bool available = sqlite3_column_int(stmt, 3);

        bookList.emplace_back(title, author, isbn, available);
    }

    sqlite3_finalize(stmt);
}

// Add a new book to the database and the bookList
void Books::addBook(const Book& book) {
    std::string sql = "INSERT INTO Books (title, author, isbn, available) VALUES ('" +
                      book.getTitle() + "', '" +
                      book.getAuthor() + "', '" +
                      book.getISBN() + "', " +
                      (book.isAvailable() ? "1" : "0") + ")";

    executeSQL(sql);
    bookList.push_back(book);
}

// Remove a book from the database and the bookList based on ISBN
void Books::removeBook(const std::string& bookISBN) {
    std::string sql = "DELETE FROM Books WHERE isbn = '" + bookISBN + "'";
    executeSQL(sql);

    bookList.erase(
        std::remove_if(bookList.begin(), bookList.end(), [&bookISBN](const Book& book) {
            return book.getISBN() == bookISBN;
        }),
        bookList.end()
    );
}

// Update a book's details in the database and the bookList
void Books::updateBook(const Book& book) {
    std::string sql = "UPDATE Books SET title = '" + book.getTitle() +
                      "', author = '" + book.getAuthor() +
                      "', available = " + (book.isAvailable() ? "1" : "0") +
                      " WHERE isbn = '" + book.getISBN() + "'";

    executeSQL(sql);

    for (auto& b : bookList) {
        if (b.getISBN() == book.getISBN()) {
            b.setTitle(book.getTitle());
            b.setAuthor(book.getAuthor());
            b.setAvailability(book.isAvailable());
            break;
        }
    }
}

// Get all books in the bookList
const std::vector<Book>& Books::getBooks() const {
    return bookList;
}

// Get books by search way (byTitle, byAuthor, byISBN) and input
const std::vector<Book>& Books::getBooksBy(enSearchWay way, const std::string& input) const {
    static std::vector<Book> filteredBooks;
    filteredBooks.clear();

    switch (way) {
        case byTitle:
            std::copy_if(bookList.begin(), bookList.end(), std::back_inserter(filteredBooks),
                         [&input](const Book& book) {
                             return book.getTitle() == input;
                         });
            break;
        case byAuthor:
            std::copy_if(bookList.begin(), bookList.end(), std::back_inserter(filteredBooks),
                         [&input](const Book& book) {
                             return book.getAuthor() == input;
                         });
            break;
        case byISBN:
            std::copy_if(bookList.begin(), bookList.end(), std::back_inserter(filteredBooks),
                         [&input](const Book& book) {
                             return book.getISBN() == input;
                         });
            break;
    }

    return filteredBooks;
}
