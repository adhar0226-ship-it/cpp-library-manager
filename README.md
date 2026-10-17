# Object-Oriented Library Manager

An offline command-line library management application built in C++ using Object-Oriented Programming (OOP) principles, encapsulation, standard library containers, and local file persistence (`books.csv`, `members.csv`, `loans.csv`).

## Features
- **OOP Architecture**: Clear separation of responsibilities across `Book`, `Member`, `Loan`, and `LibraryManager` classes.
- **Inventory Management**: Add and search items by title or author.
- **Circulation Handling**: Issue and return books with availability validation.
- **Persistent Storage**: Automatically loads from and saves state to local CSV files.

## How to Compile and Run

1. Open your terminal in the directory containing all source files.
2. Compile using a C++ compiler:
   ```bash
   g++ -O3 main.cpp library.cpp -o library_manager
