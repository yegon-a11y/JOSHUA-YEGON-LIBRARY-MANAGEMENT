#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ------------------ Book Class ------------------
class Book {
private:
    string title;
    string author;
    string ISBN;
    bool isBorrowed;

public:
    Book(string t, string a, string i) : title(t), author(a), ISBN(i), isBorrowed(false) {}

    string getTitle() { return title; }
    string getAuthor() { return author; }
    string getISBN() { return ISBN; }
    bool getStatus() { return isBorrowed; }

    void borrowBook() {
        if (!isBorrowed) {
            isBorrowed = true;
            cout << "Book borrowed successfully: " << title << endl;
        } else {
            cout << "Book is already borrowed." << endl;
        }
    }

    void returnBook() {
        if (isBorrowed) {
            isBorrowed = false;
            cout << "Book returned successfully: " << title << endl;
        } else {
            cout << "Book was not borrowed." << endl;
        }
    }
};

// ------------------ User Class ------------------
class User {
private:
    string name;
    int userId;
    vector<string> borrowedBooks;

public:
    User(string n, int id) : name(n), userId(id) {}

    string getName() { return name; }
    int getId() { return userId; }

    void borrowBook(Book &book) {
        if (!book.getStatus()) {
            book.borrowBook();
            borrowedBooks.push_back(book.getTitle());
        } else {
            cout << "Sorry, " << book.getTitle() << " is unavailable." << endl;
        }
    }

    void returnBook(Book &book) {
        book.returnBook();
        // Remove from borrowed list
        for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
            if (*it == book.getTitle()) {
                borrowedBooks.erase(it);
                break;
            }
        }
    }

    void showBorrowedBooks() {
        cout << "Books borrowed by " << name << ": ";
        if (borrowedBooks.empty()) {
            cout << "None" << endl;
        } else {
            for (auto &b : borrowedBooks) cout << b << ", ";
            cout << endl;
        }
    }
};

// ------------------ Library Class ------------------
class Library {
private:
    vector<Book> books;
    vector<User> users;

public:
    void addBook(Book book) {
        books.push_back(book);
        cout << "Book added: " << book.getTitle() << endl;
    }

    void removeBook(string ISBN) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->getISBN() == ISBN) {
                cout << "Book removed: " << it->getTitle() << endl;
                books.erase(it);
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    void searchBook(string title) {
        for (auto &b : books) {
            if (b.getTitle() == title) {
                cout << "Found: " << b.getTitle() << " by " << b.getAuthor();
                cout << (b.getStatus() ? " [Borrowed]" : " [Available]") << endl;
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    void addUser(User user) {
        users.push_back(user);
        cout << "User added: " << user.getName() << endl;
    }
};

// ------------------ Main Function ------------------
Int main(){
    Library lib;

    // Add books
    Book b1("TESTBOOK", "TESTAUTHOR", "ISBN123");
    Book b2("1984", "George Orwell", "ISBN002");
    lib.addBook(b1);
    lib.addBook(b2);

    // Add users
    User u1("TESTUSER", 1);
    User u2("Bob", 2);
    lib.addUser(u1);
    lib.addUser(u2);

    // Simulate borrowing and returning
    u1.borrowBook(b1);
    u1.showBorrowedBooks();

    u1.returnBook(b1);
    u1.showBorrowedBooks();

    // Search for a book
    lib.searchBook("TESTYEAR");

    return 0;
}
