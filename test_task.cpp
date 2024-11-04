#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib>
#include <algorithm>

enum class SortType { Title, Author, Year };

class Book {
private:
    std::string title;
    std::string author;
    int year;
    double price;

public:
    Book(const std::string& _title, const std::string& _author, int _year, double _price)
        : title(_title), author(_author), year(_year), price(_price) {}

    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    int getYear() const { return year; }
    double getPrice() const { return price; }

    bool operator<(const Book& other) const { return title < other.title; }
    bool operator>(const Book& other) const { return title > other.title; }
    bool operator==(const Book& other) const { return title == other.title; }

    bool compare(const Book& other, SortType type) const {
        switch (type) {
        case SortType::Title: return title < other.title;
        case SortType::Author: return author < other.author;
        case SortType::Year: return year < other.year;
        default: return false;
        }
    }
};

class BookStore {
private:
    std::vector<Book> books;

public:
    void addBook() {
        std::string title, author;
        int year;
        double price;

        std::cout << "Enter book title: ";
        std::getline(std::cin, title);

        std::cout << "Enter author name: ";
        std::getline(std::cin, author);

        while (true) {
            std::cout << "Enter year of publication: ";
            std::cin >> year;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error: please enter an integer for the year.\n";
            }
            else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
        }

        while (true) {
            std::cout << "Enter book price: ";
            std::cin >> price;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error: please enter a valid number for the price.\n";
            }
            else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
        }

        books.emplace_back(title, author, year, price);
        std::cout << "Book added successfully!\n";
    }

    void removeBook(const std::string& title) {
        if (books.empty()) {
            std::cout << "No books available to delete.\n";
            return;
        }

        auto it = std::find_if(books.begin(), books.end(),
            [&title](const Book& book) { return book.getTitle() == title; });

        if (it != books.end()) {
            books.erase(it);
            std::cout << "Book deleted successfully!\n";
        }
        else {
            std::cout << "Error: Book with title \"" << title << "\" not found.\n";
        }
    }

    void findBook(const std::string& title) const {
        if (books.empty()) {
            std::cout << "No books available.\n";
            return;
        }

        auto it = std::find_if(books.begin(), books.end(),
            [&title](const Book& book) { return book.getTitle() == title; });

        if (it != books.end()) {
            std::cout << "Book found:\n";
            std::cout << "Title: " << it->getTitle() << "\n"
                << "Author: " << it->getAuthor() << "\n"
                << "Year: " << it->getYear() << "\n"
                << "Price: " << it->getPrice() << " USD\n";
        }
        else {
            std::cout << "Error: Book with title \"" << title << "\" not found.\n";
        }
    }

    void listBooks(SortType sortType = SortType::Title) const {
        if (books.empty()) {
            std::cout << "No books available.\n";
            return;
        }

        auto sortedBooks = books;
        std::sort(sortedBooks.begin(), sortedBooks.end(),
            [sortType](const Book& a, const Book& b) { return a.compare(b, sortType); });

        std::cout << "\nList of all books:\n";
        for (const auto& book : sortedBooks) {
            std::cout << "Title: " << book.getTitle() << "\n"
                << "Author: " << book.getAuthor() << "\n"
                << "Year: " << book.getYear() << "\n"
                << "Price: " << book.getPrice() << "\n"
                << "-------------------------------\n";
        }
    }

    void findBooksInPriceRange(double minPrice, double maxPrice) const {
        if (books.empty()) {
            std::cout << "No books available.\n";
            return;
        }

        if (minPrice > maxPrice) {
            std::cout << "Error: Minimum price cannot be greater than maximum price.\n";
            return;
        }

        std::cout << "Books in price range " << minPrice << " - " << maxPrice << ":\n";
        bool found = false;
        for (const auto& book : books) {
            if (book.getPrice() >= minPrice && book.getPrice() <= maxPrice) {
                std::cout << "Title: " << book.getTitle() << "\n"
                    << "Author: " << book.getAuthor() << "\n"
                    << "Year: " << book.getYear() << "\n"
                    << "Price: " << book.getPrice() << "\n"
                    << "-------------------------------\n";
                found = true;
            }
        }

        if (!found) {
            std::cout << "No books found in the specified price range.\n";
        }
    }

    void exitProgram() const {
        std::cout << "Exiting program...\n";
        std::exit(0);
    }
};

void showMenu() {
    std::cout << "1. Add a book\n";
    std::cout << "2. Delete a book\n";
    std::cout << "3. Find a book\n";
    std::cout << "4. Show all books\n";
    std::cout << "5. Find books in price range\n";
    std::cout << "6. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    BookStore store;
    int choice;

    while (true) {
        system("cls");
        showMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error: please enter a valid option.\n";
            std::cin.get();
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            system("cls");
            store.addBook();
            break;
        case 2:
            system("cls");
            std::cout << "Enter the title of the book to delete: ";
            {
                std::string title;
                std::getline(std::cin, title);
                store.removeBook(title);
            }
            break;
        case 3:
            system("cls");
            std::cout << "Enter the title of the book to find: ";
            {
                std::string title;
                std::getline(std::cin, title);
                store.findBook(title);
            }
            break;
        case 4:
            system("cls");
            int sortOption;
            std::cout << "Sort by: 1. Title 2. Author 3. Year\nChoose an option: ";
            std::cin >> sortOption;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            store.listBooks(static_cast<SortType>(sortOption - 1));
            break;
        case 5:
            system("cls");
            double minPrice, maxPrice;
            while (true) {
                std::cout << "Enter minimum price: ";
                std::cin >> minPrice;

                if (std::cin.fail() || minPrice < 0) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Error: please enter a valid non-negative number for the minimum price.\n";
                }
                else {
                    break;
                }
            }
            while (true) {
                std::cout << "Enter maximum price: ";
                std::cin >> maxPrice;

                if (std::cin.fail() || maxPrice < 0) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Error: please enter a valid non-negative number for the maximum price.\n";
                }
                else {
                    break;
                }
            }
            store.findBooksInPriceRange(minPrice, maxPrice);
            break;
        case 6:
            system("cls");
            store.exitProgram();
            break;
        default:
            std::cout << "Invalid option, please try again.\n";
        }

        std::cout << "Press Enter to continue...";
        std::cin.get();
    }

    return 0;
}
