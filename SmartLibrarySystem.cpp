#include <iostream>
#include <unordered_map>
#include <stack>
#include <queue>
#include <string>
#include <iomanip>

using namespace std;

// 📚 Book structure
struct Book {
    string title;
    string author;
    bool isIssued;
};

// 🗂️ Global data
unordered_map<int, Book> library;
stack<int> recentIssued;
queue<string> waitlist;

// 🌸 Add a new book
void addBook(int id, const string& title, const string& author) {
    if (library.find(id) != library.end()) {
        cout << "⚠️  Book ID already exists. Try again.\n";
        return;
    }
    library[id] = {title, author, false};
    cout << "✅ \"" << title << "\" by " << author << " added successfully!\n";
}

// 🔍 Search a book
void searchBook(const string& keyword) {
    cout << "\n🔍 Search Results:\n";
    bool found = false;
    for (auto& pair : library) {
        const Book& b = pair.second;
        if (b.title.find(keyword) != string::npos || b.author.find(keyword) != string::npos) {
            cout << "📖 ID: " << pair.first
                 << " | Title: " << b.title
                 << " | Author: " << b.author
                 << " | Status: " << (b.isIssued ? "❌ Issued" : "✅ Available") << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "💔 No matching books found.\n";
    }
}

// 📕 Issue a book
void issueBook(int id, const string& userName) {
    if (library.find(id) == library.end()) {
        cout << "❌ Book ID not found.\n";
        return;
    }

    Book& b = library[id];
    if (!b.isIssued) {
        b.isIssued = true;
        recentIssued.push(id);
        cout << "🎉 \"" << b.title << "\" issued to " << userName << ".\n";
    } else {
        waitlist.push(userName);
        cout << "⏳ Already issued. " << userName << " added to waitlist.\n";
    }
}

// 📗 Return a book
void returnBook(int id) {
    if (library.find(id) == library.end()) {
        cout << "❌ Book ID not found.\n";
        return;
    }

    Book& b = library[id];
    if (!b.isIssued) {
        cout << "⚠️  Book wasn't issued.\n";
        return;
    }

    b.isIssued = false;
    cout << "📦 \"" << b.title << "\" has been returned.\n";

    if (!waitlist.empty()) {
        string nextUser = waitlist.front();
        waitlist.pop();
        issueBook(id, nextUser);
    }
}

// 🧾 View recently issued books
void viewRecentIssued() {
    cout << "\n🧾 Recently Issued Books:\n";
    if (recentIssued.empty()) {
        cout << "📭 No books have been issued yet.\n";
        return;
    }

    stack<int> temp = recentIssued;
    int count = 1;
    while (!temp.empty()) {
        int id = temp.top();
        temp.pop();
        Book b = library[id];
        cout << count++ << ". " << b.title << " by " << b.author << "\n";
    }
}

// 🌟 Main menu
void showMenu() {
    cout << "\n📚 Smart Library Menu:\n";
    cout << "1. ➕ Add Book\n";
    cout << "2. 🔍 Search Book\n";
    cout << "3. 📕 Issue Book\n";
    cout << "4. 📗 Return Book\n";
    cout << "5. 🧾 View Recently Issued\n";
    cout << "6. ❌ Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;

    while (true) {
        showMenu();
        cin >> choice;
        cin.ignore(); // Clear buffer

        if (choice == 1) {
            int id;
            string title, author;

            cout << "Enter Book ID: ";
            cin >> id;
            cin.ignore();

            cout << "Enter Book Title: ";
            getline(cin, title);

            cout << "Enter Author Name: ";
            getline(cin, author);

            addBook(id, title, author);
        }

        else if (choice == 2) {
            string keyword;
            cout << "Enter keyword to search (title/author): ";
            getline(cin, keyword);
            searchBook(keyword);
        }

        else if (choice == 3) {
            int id;
            string user;

            cout << "Enter Book ID to issue: ";
            cin >> id;
            cin.ignore();

            cout << "Enter Your Name: ";
            getline(cin, user);

            issueBook(id, user);
        }

        else if (choice == 4) {
            int id;
            cout << "Enter Book ID to return: ";
            cin >> id;
            returnBook(id);
        }

        else if (choice == 5) {
            viewRecentIssued();
        }

        else if (choice == 6) {
            cout << "\n🌸 Thank you for using the Smart Library System. See you again!\n";
            break;
        }

        else {
            cout << "❗ Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
