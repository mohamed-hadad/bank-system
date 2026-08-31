# Bank System

A console-based banking management system written in C++. It provides full client
account management, financial transactions, and a role-based user permission
system, all backed by flat-file storage.

> **Note:** This is an educational project. It is not intended for production use.
> Security measures such as password hashing, input sanitization, and encryption
> are intentionally out of scope.

---

## Features

- **Authentication** – Username/password login with session handling.
- **Client Management** – Add, delete, update, search, and list client accounts.
- **Transactions** – Deposit, withdraw, and view total balances across all accounts.
- **User Management** – Create, delete, update, search, and list system users.
- **Role-Based Permissions** – Bit-flag permission system that controls access
  to every module independently (list, add, delete, update, find, transactions,
  manage users).
- **Persistent Storage** – All data is stored in and loaded from plain-text files
  (`ClientsData.txt`, `Users.txt`).

---

## Permissions

| Permission    | Value  |
|---------------|-------:|
| Full Access   |   -1   |
| List Clients  |    1   |
| Add Client    |    2   |
| Delete Client |    4   |
| Update Client |    8   |
| Find Client   |   16   |
| Transactions  |   32   |
| Manage Users  |   64   |

---

## Built With

| Component  | Detail                        |
|------------|-------------------------------|
| Language   | C++ (C++17)                   |
| Compiler   | MSVC (Visual Studio 2022)     |
| Platform   | Windows 11                    |
| Storage    | Flat-file (`.txt`)            |
| Libraries  | Standard Library only         |

---

## Files
- `BankSystem.cpp`: source code
- `ClientsData.txt`: client records
- `Users.txt`: user records

## Data Format

Client record:
`AccountNumber#//#PinCode#//#Name#//#Phone#//#Balance`

User record:
`Username#//#Password#//#Permissions`

### Default Credentials

| Field       | Value    |
|-------------|----------|
| Username    | `Admin`  |
| Password    | `1234`   |
| Permissions | Full access (`-1`) |

## How to Run
1. Open the project in a C++ IDE.
2. Make sure ClientsData.txt and Users.txt exist.
3. Verify that Users.txt contains at least one valid user
   (a default `Admin` account is included).
4. Build and run the program.
5. Log in with a valid username and password.

## Note
This project is for learning purposes only.

- Passwords and PIN codes are stored as **plain text**.
- The application is **Windows-only** (`system("cls")` is used for screen clearing).
- No encryption, input sanitization, or concurrent-access safety is implemented.