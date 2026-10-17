#include <iostream>
#include "library.h"

int main() {
    LibraryManager manager;
    int choice;

    do {
        std::cout << "\n=== OBJECT-ORIENTED LIBRARY MANAGER ===\n";
        std::cout << "1. List Books\n";
        std::cout << "2. List Members\n";
        std::cout << "3. List Active Loans\n";
        std::cout << "4. Search Books\n";
        std::cout << "5. Add Book\n";
        std::cout << "6. Add Member\n";
        std::cout << "7. Issue Book (Loan)\n";
        std::cout << "8. Return Book\n";
        std::cout << "9. Exit\n";
        std::cout << "Enter your choice (1-9): ";
        
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        std::cin.ignore(10000, '\n');

        switch (choice) {
            case 1: manager.listBooks(); break;
            case 2: manager.listMembers(); break;
            case 3: manager.listLoans(); break;
            case 4: {
                std::string query;
                std::cout << "Enter search query (title or author): ";
                std::getline(std::cin, query);
                manager.searchBooks(query);
                break;
            }
            case 5: {
                std::string id, title, author;
                std::cout << "Enter Book ID: "; std::getline(std::cin, id);
                std::cout << "Enter Title: "; std::getline(std::cin, title);
                std::cout << "Enter Author: "; std::getline(std::cin, author);
                manager.addBook(Book(id, title, author, true));
                std::cout << "Book added successfully!\n";
                break;
            }
            case 6: {
                std::string mId, name;
                std::cout << "Enter Member ID: "; std::getline(std::cin, mId);
                std::cout << "Enter Name: "; std::getline(std::cin, name);
                manager.addMember(Member(mId, name));
                std::cout << "Member added successfully!\n";
                break;
            }
            case 7: {
                std::string lId, bId, mId, date;
                std::cout << "Enter Loan ID: "; std::getline(std::cin, lId);
                std::cout << "Enter Book ID to issue: "; std::getline(std::cin, bId);
                std::cout << "Enter Member ID: "; std::getline(std::cin, mId);
                std::cout << "Enter Due Date (YYYY-MM-DD): "; std::getline(std::cin, date);
                manager.issueBook(lId, bId, mId, date);
                break;
            }
            case 8: {
                std::string bId;
                std::cout << "Enter Book ID to return: "; std::getline(std::cin, bId);
                manager.returnBook(bId);
                break;
            }
            case 9:
                std::cout << "Exiting Library Manager. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please select between 1 and 9.\n";
        }
    } while (choice != 9);

    return 0;
}
