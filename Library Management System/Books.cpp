#include "Books.h"
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <ctime>

Books::Books(sqlite3* database) : db(database) {}

void Books::executeSQL(const std::string& sql) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::string error = "SQL error: ";
        error += errMsg;
        sqlite3_free(errMsg);
        throw std::runtime_error(error);
    }
}

void Books::loadBooksFromDB() {
    const char* sql = "SELECT Title, Author, ISBN, Available, CheckoutDate FROM Books;";
    sqlite3_stmt* stmt;
    
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        throw std::runtime_error("Failed to execute query: " + std::string(sqlite3_errmsg(db)));
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        std::string title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string author = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string isbn = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        bool available = sqlite3_column_int(stmt, 3);
        std::time_t checkoutDate = sqlite3_column_int64(stmt, 4);

        Book book(title, author, isbn, available, checkoutDate);
        bookList.push_back(book);
    }

    sqlite3_finalize(stmt);
}

void Books::addBook(const Book& book) {
    std::ostringstream oss;
    oss << "INSERT INTO Books (Title, Author, ISBN, Available, CheckoutDate) VALUES ('"
        << book.getTitle() << "', '"
        << book.getAuthor() << "', '"
        << book.getISBN() << "', "
        << book.isAvailable() << ", "
        << book.getCheckoutDate() << ");";
    
    executeSQL(oss.str());
    bookList.push_back(book);
}

void Books::removeBook(const std::string& bookISBN) {
    std::ostringstream oss;
    oss << "DELETE FROM Books WHERE ISBN='" << bookISBN << "';";
    executeSQL(oss.str());

    bookList.erase(std::remove_if(bookList.begin(), bookList.end(),
                  [&bookISBN](const Book& b) { return b.getISBN() == bookISBN; }), bookList.end());
}

void Books::updateBook(const Book& book) {
    std::ostringstream oss;
    oss << "UPDATE Books SET Title='" << book.getTitle()
        << "', Author='" << book.getAuthor()
        << "', Available=" << book.isAvailable()
        << ", CheckoutDate=" << book.getCheckoutDate()
        << " WHERE ISBN='" << book.getISBN() << "';";
    
    executeSQL(oss.str());
}

const std::vector<Book>& Books::getBooks() const {
    return bookList;
}

const std::vector<Book>& Books::getBooksBy(enSearchWay way, const std::string& input) const {
    static std::vector<Book> filteredBooks; // To store the search results
    filteredBooks.clear();

    // Lambda function to match the input with the appropriate field based on the search way
    auto match = [&input,&way](const Book book) -> bool{
        switch(way)
        {
            case enSearchWay::byAuthor:
                return input==book.getAuthor();
            case enSearchWay::byISBN:
                return input==book.getISBN();
            case enSearchWay::byTitle:
                return input==book.getTitle();
            default:
                return false;

        }
    };
    std::copy_if(bookList.begin(),bookList.end(),std::back_inserter(filteredBooks),match);

    return filteredBooks;
}


void Books::checkoutBook(const std::string& bookISBN) {
    auto it = std::find_if(bookList.begin(), bookList.end(),
                           [&bookISBN](const Book& b) { return b.getISBN() == bookISBN; });

    if (it != bookList.end()) {
        if (it->isAvailable()) {
            std::time_t now = std::time(nullptr);
            it->setAvailability(false);
            it->setCheckoutDate(now);

            std::ostringstream oss;
            oss << "UPDATE Books SET Available = 0, CheckoutDate = " << now
                << " WHERE ISBN = '" << bookISBN << "';";
            executeSQL(oss.str());
        } else {
            throw std::runtime_error("Book is already checked out.");
        }
    } else {
        throw std::runtime_error("Book with ISBN " + bookISBN + " not found.");
    }
}

void Books::returnBook(const std::string& bookISBN) {
    auto it = std::find_if(bookList.begin(), bookList.end(),
                           [&bookISBN](const Book& b) { return b.getISBN() == bookISBN; });

    if (it != bookList.end()) {
        if (!it->isAvailable()) {
            it->setAvailability(true);
            it->setCheckoutDate(0);  // Reset the checkout date

            std::ostringstream oss;
            oss << "UPDATE Books SET Available = 1, CheckoutDate = NULL"
                << " WHERE ISBN = '" << bookISBN << "';";
            executeSQL(oss.str());
        } else {
            throw std::runtime_error("Book is already available.");
        }
    } else {
        throw std::runtime_error("Book with ISBN " + bookISBN + " not found.");
    }
}

bool Books::isFound(const std::string &bookISBN)
{
    return !getBooksBy(enSearchWay::byISBN,bookISBN).empty();
}
