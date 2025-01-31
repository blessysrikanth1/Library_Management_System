#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

struct Book {
    int id;
    string title, author;
    bool isIssued;

    void display() const {  // Marking display() as const to fix the error
        cout << left << setw(5) << id << setw(30) << title 
             << setw(20) << author << (isIssued ? "Issued" : "Available") << endl;
    }
};

class Library {
private:
    vector<Book> books;
    string filename = "library_data.txt";

    void loadBooks() {
        ifstream file(filename);
        if (!file) return;
        books.clear();
        Book book;
        while (file >> book.id) {
            file.ignore();
            getline(file, book.title);
            getline(file, book.author);
            file >> book.isIssued;
            books.push_back(book);
        }
        file.close();
    }

    void saveBooks() {
        ofstream file(filename);
        for (const auto &book : books) {
            file << book.id << "\n" << book.title << "\n" << book.author << "\n" << book.isIssued << "\n";
        }
        file.close();
    }

public:
    Library() {
        loadBooks();
    }

    void addBook() {
        Book book;
        cout << "Enter Book ID: ";
        cin >> book.id;
        cin.ignore();
        cout << "Enter Title: ";
        getline(cin, book.title);
        cout << "Enter Author: ";
        getline(cin, book.author);
        book.isIssued = false;
        books.push_back(book);
        saveBooks();
        cout << "Book added successfully!\n";
    }

    void displayBooks() {
        cout << "\nLibrary Books:\n";
        cout << left << setw(5) << "ID" << setw(30) << "Title" << setw(20) << "Author" << "Status\n";
        cout << "-----------------------------------------------------------------\n";
        for (const auto &book : books) {
            book.display();  // This works now, since display() is const
        }
    }

    void issueBook() {
        int bookId;
        cout << "Enter Book ID to Issue: ";
        cin >> bookId;
        for (auto &book : books) {
            if (book.id == bookId && !book.isIssued) {
                book.isIssued = true;
                saveBooks();
                cout << "Book Issued Successfully!\n";
                return;
            }
        }
        cout << "Book not found or already issued!\n";
    }

    void returnBook() {
        int bookId;
        cout << "Enter Book ID to Return: ";
        cin >> bookId;
        for (auto &book : books) {
            if (book.id == bookId && book.isIssued) {
                book.isIssued = false;
                saveBooks();
                cout << "Book Returned Successfully!\n";
                return;
            }
        }
        cout << "Invalid book ID or book was not issued!\n";
    }

    void searchBook() {
        string keyword;
        cout << "Enter title or author to search: ";
        cin.ignore();
        getline(cin, keyword);
        cout << "\nSearch Results:\n";
        cout << left << setw(5) << "ID" << setw(30) << "Title" << setw(20) << "Author" << "Status\n";
        cout << "-----------------------------------------------------------------\n";
        for (const auto &book : books) {
            if (book.title.find(keyword) != string::npos || book.author.find(keyword) != string::npos) {
                book.display();
            }
        }
    }
};

int main() {
    Library library;
    int choice;
    
    while (true) {
        cout << "\n📚 Library Management System\n";
        cout << "1. Add Book\n2. Display Books\n3. Issue Book\n4. Return Book\n5. Search Book\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: library.addBook(); break;
            case 2: library.displayBooks(); break;
            case 3: library.issueBook(); break;
            case 4: library.returnBook(); break;
            case 5: library.searchBook(); break;
            case 6: cout << "Exiting...\n"; return 0;
            default: cout << "Invalid choice, try again!\n";
        }
    }
}
