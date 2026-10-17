#include "library.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

// --- Book Implementation ---
Book::Book(std::string id, std::string title, std::string author, bool available)
    : id(id), title(title), author(author), available(available) {}

std::string Book::getId() const { return id; }
std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
bool Book::isAvailable() const { return available; }
void Book::setAvailable(bool status) { available = status; }

std::string Book::serialize() const {
    return id + "," + title + "," + author + "," + (available ? "1" : "0");
}

Book Book::deserialize(const std::string& line) {
    std::stringstream ss(line);
    std::string id, title, author, availStr;
    std::getline(ss, id, ',');
    std::getline(ss, title, ',');
    std::getline(ss, author, ',');
    std::getline(ss, availStr, ',');
    return Book(id, title, author, availStr == "1");
}

// --- Member Implementation ---
Member::Member(std::string memberId, std::string name) : memberId(memberId), name(name) {}

std::string Member::getMemberId() const { return memberId; }
std::string Member::getName() const { return name; }

std::string Member::serialize() const {
    return memberId + "," + name;
}

Member Member::deserialize(const std::string& line) {
    std::stringstream ss(line);
    std::string memberId, name;
    std::getline(ss, memberId, ',');
    std::getline(ss, name, ',');
    return Member(memberId, name);
}

// --- Loan Implementation ---
Loan::Loan(std::string loanId, std::string bookId, std::string memberId, std::string dueDate)
    : loanId(loanId), bookId(bookId), memberId(memberId), dueDate(dueDate) {}

std::string Loan::getLoanId() const { return loanId; }
std::string Loan::getBookId() const { return bookId; }
std::string Loan::getMemberId() const { return memberId; }
std::string Loan::getDueDate() const { return dueDate; }

std::string Loan::serialize() const {
    return loanId + "," + bookId + "," + memberId + "," + dueDate;
}

Loan Loan::deserialize(const std::string& line) {
    std::stringstream ss(line);
    std::string loanId, bookId, memberId, dueDate;
    std::getline(ss, loanId, ',');
    std::getline(ss, bookId, ',');
    std::getline(ss, memberId, ',');
    std::getline(ss, dueDate, ',');
    return Loan(loanId, bookId, memberId, dueDate);
}

// --- LibraryManager Implementation ---
LibraryManager::LibraryManager(std::string bFile, std::string mFile, std::string lFile)
    : booksFile(bFile), membersFile(mFile), loansFile(lFile) {
    loadData();
}

void LibraryManager::loadData() {
    std::ifstream bFile(booksFile);
    std::string line;
    if (bFile.is_open()) {
        while (std::getline(bFile, line)) {
            if (!line.empty()) books.push_back(Book::deserialize(line));
        }
        bFile.close();
    }

    std::ifstream mFile(membersFile);
    if (mFile.is_open()) {
        while (std::getline(mFile, line)) {
            if (!line.empty()) members.push_back(Member::deserialize(line));
        }
        mFile.close();
    }

    std::ifstream lFile(loansFile);
    if (lFile.is_open()) {
        while (std::getline(lFile, line)) {
            if (!line.empty()) loans.push_back(Loan::deserialize(line));
        }
        lFile.close();
    }
}

void LibraryManager::saveData() const {
    std::ofstream bFile(booksFile);
    for (const auto& b : books) bFile << b.serialize() << "\n";
    bFile.close();

    std::ofstream mFile(membersFile);
    for (const auto& m : members) mFile << m.serialize() << "\n";
    mFile.close();

    std::ofstream lFile(loansFile);
    for (const auto& l : loans) lFile << l.serialize() << "\n";
    lFile.close();
}

void LibraryManager::addBook(const Book& book) {
    books.push_back(book);
    saveData();
}

void LibraryManager::addMember(const Member& member) {
    members.push_back(member);
    saveData();
}

void LibraryManager::issueBook(const std::string& loanId, const std::string& bookId, const std::string& memberId, const std::string& dueDate) {
    auto bookIt = std::find_if(books.begin(), books.end(), [&](const Book& b) { return b.getId() == bookId; });
    if (bookIt == books.end()) {
        std::cout << "Error: Book ID not found.\n";
        return;
    }
    if (!bookIt->isAvailable()) {
        std::cout << "Error: Book is already checked out.\n";
        return;
    }
    bookIt->setAvailable(false);
    loans.push_back(Loan(loanId, bookId, memberId, dueDate));
    saveData();
    std::cout << "Book issued successfully!\n";
}

void LibraryManager::returnBook(const std::string& bookId) {
    auto bookIt = std::find_if(books.begin(), books.end(), [&](const Book& b) { return b.getId() == bookId; });
    if (bookIt == books.end()) {
        std::cout << "Error: Book ID not found.\n";
        return;
    }
    bookIt->setAvailable(true);
    loans.erase(std::remove_if(loans.begin(), loans.end(), [&](const Loan& l) { return l.getBookId() == bookId; }), loans.end());
    saveData();
    std::cout << "Book returned successfully!\n";
}

void LibraryManager::searchBooks(const std::string& query) const {
    std::cout << "\n--- Search Results for '" << query << "' ---\n";
    for (const auto& b : books) {
        if (b.getTitle().find(query) != std::string::npos || b.getAuthor().find(query) != std::string::npos) {
            std::cout << "ID: " << b.getId() << " | Title: " << b.getTitle() << " | Author: " << b.getAuthor() 
                      << " | Status: " << (b.isAvailable() ? "Available" : "Checked Out") << "\n";
        }
    }
}

void LibraryManager::listBooks() const {
    std::cout << "\n--- Library Inventory --- \n";
    for (const auto& b : books) {
        std::cout << "ID: " << b.getId() << " | Title: " << b.getTitle() << " | Author: " << b.getAuthor() 
                  << " | Status: " << (b.isAvailable() ? "Available" : "Checked Out") << "\n";
    }
}

void LibraryManager::listMembers() const {
    std::cout << "\n--- Registered Members --- \n";
    for (const auto& m : members) {
        std::cout << "Member ID: " << m.getMemberId() << " | Name: " << m.getName() << "\n";
    }
}

void LibraryManager::listLoans() const {
    std::cout << "\n--- Active Loans --- \n";
    for (const auto& l : loans) {
        std::cout << "Loan ID: " << l.getLoanId() << " | Book ID: " << l.getBookId() 
                  << " | Member ID: " << l.getMemberId() << " | Due: " << l.getDueDate() << "\n";
    }
}
