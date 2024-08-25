#include"clsScreen.cpp"
#include"Books.h"
#include <iomanip>
enum enOption {showBooks=1,findBook,addBook,editBook,removeBook,chechoutBook,returnBook,EXIT};
class clsStartLibrary
{
    static void showBooksScreen(const std::vector<Book>& books)
    {
        if (books.empty()) {
            std::cout << "No books found." << std::endl;
            return;
        }

        // Print table header
        std::cout << std::string(135, '-') << std::endl;
        std::cout<< "|" << std::left << std::setw(30) << "title"
                << " | " << std::setw(30) << "author"
                << " | " << std::setw(16) << "isbn"
                << " | " << std::setw(10) << "available"
                << " | " << std::setw(16) << "check out date"
                << " | " << std::setw(16) << "return date" << "|"
                << std::endl;
        std::cout << std::string(135, '-') << std::endl;

        // Print each task
            char buffer1[11];
            char buffer2[11];
        for (const Book& book : books) {
            auto checkoutDate=book.getCheckoutDate();
            auto returnDate=std::time(nullptr);
            returnDate=checkoutDate+(2 * 24 * 60 * 60);
            struct tm* timeinfo = std::localtime(&checkoutDate);
            strftime(buffer1, sizeof(buffer1), "%d/%m/%Y", timeinfo);
            timeinfo = std::localtime(&returnDate);
            strftime(buffer2, sizeof(buffer2), "%d/%m/%Y", timeinfo);
            std::cout<< "|" << std::left << std::setw(30) << book.getTitle()
                    << " | " << std::setw(30) << book.getAuthor()
                    << " | " << std::setw(16) << book.getISBN()
                    << " | " << std::setw(10) << (book.isAvailable() ? "Yes" : "No")
                    << " | " << std::setw(16) << (checkoutDate ? buffer1 : "")
                    << " | " << std::setw(16) << (checkoutDate ? buffer2 : "") <<"|"
                    << std::endl;
        }
        std::cout << std::string(135, '-') << std::endl;
    }

    static void checkOutScreen(Books& library)
    {
        std::string isbn;
        std::cout<<"Enter ISBN: ";
        std::cin>>isbn;
            try {
                library.checkoutBook(isbn);
                std::cout<<"[System] -> the book is checkout return it after 2 days from now..\n";
            } 
            catch (const std::runtime_error& e) {
                std::cerr << "[System]-> " << e.what() << std::endl;
            }

    }
    
    static void returnBookScreen(Books& library) {
        std::string isbn;
        std::cout << "Enter ISBN: ";
        std::cin >> isbn;
        
        try {
            std::time_t now = std::time(nullptr);
            std::time_t checkoutDate = library.getBooksBy(enSearchWay::byISBN,isbn)[0].getCheckoutDate()+( 2*24 * 60 * 60); 
            library.returnBook(isbn);

            if (checkoutDate > now) {
                std::cout << "[System] -> The book is returned on time.\n";
            } else {
                char buffer[11];
                struct tm* timeinfo = std::localtime(&checkoutDate);
                strftime(buffer, sizeof(buffer), "%d/%m/%Y", timeinfo);
                std::cout << "[System] -> You are late. Original return date: " << buffer << std::endl;
            }
        } 
        catch (const std::runtime_error& e) {
            std::cerr << "[System] -> " << e.what() << std::endl;
        }
    }
    static void deleteBookScreen(Books& library)
    {
        std::string isbn;
        std::cout<<"Enter ISBN: ";
        std::cin>>isbn;
            try {
                auto test=library.getBooksBy(enSearchWay::byISBN,isbn);
                if(test.empty())
                {
                    std::cout<<"[System] -> book is found \n";
                    return;
                }
                std::cout<<test[0].getDetails();
                std::cout<<"\n[System] -> Enter y/Y for confirm delete";
                char c = clsScreen::pressKey();
                if(c == 'y' || c=='Y')
                {
                    library.removeBook(isbn);
                    std::cout<<"\n[System] -> the book is deleted\n";
                }
                else
                    std::cout<<"\n[System] -> the book is not deleted\n";
            } 
            catch (const std::runtime_error& e) {
                std::cerr << "[System]-> " << e.what() << std::endl;
            }

    }
    static void selectOption(enOption option , Books& books)
    {
        system("cls");
        switch (option)
        {
            case enOption::showBooks:
                showBooksScreen(books.getBooks());
                break;
            case enOption::findBook:
                break;
            case enOption::addBook:
                break;
            case enOption::editBook:
                break;
            case enOption::removeBook:
                deleteBookScreen(books);
                break;
            case enOption::chechoutBook:
                checkOutScreen(books);
                break;
            case enOption::returnBook:
                returnBookScreen(books);
                break;
            case enOption::EXIT:
                exit(0);
                break;
        }
        std::cout<<"Press Any key to coninue";
        clsScreen::pressKey();
    }
    static void pStart()
    {
        std::vector<std::string> menuOptions = {
            "1. Show Books",
            "2. Find Book",
            "3. Add Book",
            "4. Edit Book",
            "5. Remove Book",
            "6. Checkout Book",
            "7. Return Book",
            "8. Exit"
        };
        sqlite3* db;
        int rc = sqlite3_open("library.db", &db);
        if (rc) {
            std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
            exit(1);
        }
        Books library(db);
        library.loadBooksFromDB();
        selectOption((enOption)clsScreen::getOptions(menuOptions),library);
    }

    public:
        static void start()
        {
            while(1)
                pStart();
        }
};