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
    static void showBooksWithOptions(enSearchWay option,Books& books,const std::string& text)
    {
        std::string input;
        std::cout<<text;
        std::getline(std::cin,input);
        system("cls");
        showBooksScreen(books.getBooksBy(option,input));

    }
    static void selectOptionFind(Books& books)
    {
        do 
        {
            system("cls");
            std::vector<std::string> options =
            {
                "1. find by title",
                "2. find by author",
                "3. find by ISBN",
                "4. return Main"
            };
            int selected = clsScreen::getOptions(options);
            if(selected==4)
                return;
            selectOptionFind((enSearchWay)selected,books);
        }while(1);

    }
    static void selectOptionFind(enSearchWay options,Books& books)
    {
        system("cls");
        switch(options)
        {
            case enSearchWay::byISBN:
                showBooksWithOptions(options,books,"Enter ISBN: ");
                break;
            case enSearchWay::byTitle:
                showBooksWithOptions(options,books,"Enter Title: ");
                break;
            case enSearchWay::byAuthor:
                showBooksWithOptions(options,books,"Enter Author: ");
                break;   
        }
        std::cout<<"Press Any key to coninue";
        clsScreen::pressKey();
    }
    static void addBook(Books& books)
    {
        bool validate = 1; 
        std::string input,title,author;
        do 
        {
            std::cout<<"Enter ISBN: ";
            std::getline(std::cin>>std::ws,input);
            validate=books.getBooksBy(enSearchWay::byISBN,input).empty();
            if(!validate)
                std::cout<<"[System] -> the book is in the system\n";
        }while(!validate);
        std::cout<<"Enter title: ";
        std::getline(std::cin,title);
        std::cout<<"Enter author: ";
        std::getline(std::cin,author);
        std::cout<<"press y/Y to save the book";
        char ch = _getch();
        std::cout<<"\n[System] -> ";
        if(ch=='y' || ch=='Y')
        {
            
            books.addBook(Book(title,author,input,1));
            std::cout<<"The book is adding in the system\n";
        }
        else
            std::cout<<"The book is not adding in the system\n";
    }
    static void editBook(Books& books)
    {
        bool validate = 1; 
        std::string input,title,author,isbn;
        Book* target=nullptr;
        std::vector<Book> result;
        do
        {
            std::cout<<"Enter ISBN: ";
            std::getline(std::cin>>std::ws,input);
            result = books.getBooksBy(enSearchWay::byISBN,input);

            target=(result.empty())?nullptr:&result[0];
            if(!target)
                std::cout<<"[System] -> the book is not in the system\n";
        }while(!target);
        std::cout<<target->getDetails();
        std::cout<<"press y/Y if you want update the book";
        if(char ch = _getch();ch != 'y' && ch != 'Y')
            return;
        system("cls");
        std::cout<<"\n[System] -> press Enter if you want keep the old naming..";
        std::cout<<"\nEnter New ISBN: ";
        std::getline(std::cin,title);
        std::cout<<"Enter title: ";
        std::getline(std::cin,title);
        std::cout<<"Enter author: ";
        std::getline(std::cin,author);
        std::cout<<"press y/Y to edit the book";
        char ch = _getch();
        std::cout<<"\n[System] -> ";
        if(ch=='y' || ch=='Y')
        {
            if(!title.empty())
                target->setTitle(title);
            if(!isbn.empty())
                target->setISBN(isbn);
            if(!author.empty())
                target->setAuthor(author);
            books.updateBook(input,*target);
            std::cout<<"The book update in the system";
        }
        else
            std::cout<<"The book is not update in the system";
        std::cout<<std::endl;
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
                selectOptionFind(books);
                return;
            case enOption::addBook:
                addBook(books);
                break;
            case enOption::editBook:
                editBook(books);
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