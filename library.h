#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>

class Book {
private:
    std::string id;
    std::string title;
    std::string author;
    bool available;

public:
    Book(std::string id, std::string title, std::string author, bool available = true);

    std::string getId() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    bool isAvailable() const;

    void setAvailable(bool status);
    std::string serialize() const;
    static Book deserialize(const std::string& line);
};

class Member {
private:
    std::string memberId;
    std::string name;

public:
    Member(std::string memberId, std::string name);

    std::string getMemberId() const;
    std::string getName() const;

    std::string serialize() const;
    static Member deserialize(const std::string& line);
};

class Loan {
private:
    std::string loanId;
    std::string bookId;
    std::string memberId;
    std::string dueDate;

public:
    Loan(std::string loanId, std::string bookId, std::string memberId, std::string dueDate);

    std::string getLoanId() const;
    std::string getBookId() const;
    std::string getMemberId() const;
    std::string getDueDate() const;

    std::string serialize() const;
    static Loan deserialize(const std::string& line);
};

class LibraryManager {
private:
    std::vector<Book> books;
    std::vector<Member> members;
    std::vector<Loan> loans;

    std::string booksFile;
    std::string membersFile;
    std::string loansFile;

    void loadData();
    void saveData() const;

public:
    LibraryManager(std::string bFile = "books.csv", std::string mFile = "members.csv", std::string lFile = "loans.csv");

    void addBook(const Book& book);
    void addMember(const Member& member);
    void issueBook(const std::string& loanId, const std::string& bookId, const std::string& memberId, const std::string& dueDate);
    void returnBook(const std::string& bookId);

    void searchBooks(const std::string& query) const;
    void listBooks() const;
    void listMembers() const;
    void listLoans() const;
};

#endif
