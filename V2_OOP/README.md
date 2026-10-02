# 🏦 Bank Management System — C++ / OOP

A complete **Bank Management System** built from scratch in **C++**, designed fully around **Object-Oriented Programming** principles.
This project is the practical application of the course **"OOP as it Should Be – Applications"** (Programming Advices roadmap by **Dr. Mohamed Abu Hadhoud**) — a full OOP rebuild of an earlier procedural version of the same system: same business, completely different design.

---

## ✨ Features

### 👥 Client Management
- Add / Update / Delete / Find clients
- Full clients list with detailed client cards

### 💸 Transactions
- Deposit & Withdraw with balance validation
- Client-to-client **Transfer** with a complete **Transfer Log** (date, time, sender, receiver, amount, and the username who performed it)
- Total Balances screen — with the total written out in words (Number-To-Text)

### 🔐 Users, Permissions & Security
- Full user management (Add / Update / Delete / Find / List)
- **Bitmask-based permissions system** (per-screen access control)
- **Login Register** — every login is logged with date, time, and permissions
- Account lockout after **3 failed login attempts**
- **Passwords & PIN codes are stored encrypted in the data files** (see [Security Notes](#-security-notes-password-encryption))

### 💱 Currency Exchange Module
- List all currencies
- Find currency by **code** or by **country**
- Update currency rates
- Currency calculator (convert between any two currencies via USD)

### 🧰 Custom Utility Libraries (built from scratch)
- `clsString` — string manipulation toolkit
- `clsDate` — full date library (validation, comparisons, calendars, business days, vacations…)
- `clsUtility` — helpers (random generation, encryption, number-to-text…)
- `clsValidateInput` — robust template-based input validation

---

## 🏗️ Architecture

The system is organized into **three logical layers**:

| Layer | Classes | Responsibility |
|---|---|---|
| **UI (Screens)** | `clsLoginScreen`, `clsMainScreen`, `clsTransactionsScreen`, `clsManageUsersScreen`, `clsCurrencyExchangeMainScreen`, + 19 more screens | Console presentation only |
| **Domain (Entities)** | `clsPerson` → `clsBankClient`, `clsUser`, and `clsCurrency` | Business rules, state, and persistence |
| **Utilities** | `clsString`, `clsDate`, `clsUtility`, `clsValidateInput` | Reusable helper libraries |

All screens inherit from a common `clsScreen` base class (shared header & pause logic), and the entire program entry point is just:

```cpp
int main()
{
    clsLoginScreen::ShowLoginScreen();
    return 0;
}
```

### OOP concepts applied
- **Encapsulation** — all data members are `private`, exposed only through controlled properties (getters/setters).
- **Inheritance** — `clsBankClient` and `clsUser` inherit from `clsPerson`; all screens inherit from `clsScreen`.
- **Abstraction** — all file I/O (load / save / line↔object conversion) is hidden inside private methods; screens only see a clean public API.
- **Overloading / Polymorphism** — e.g. `Find()` overloads, static vs. instance operations across the libraries.
- **Objects own their behavior** — `Client.Deposit()`, `Client.Withdraw()`, `Client.Transfer()` enforce their own rules (a withdraw that exceeds the balance is refused by the object itself).
- **Mode (state) pattern** — every object knows its mode (`EmptyMode / AddNewMode / UpdateMode`), and `Save()` behaves accordingly, returning a typed `enSaveResults`.
- **Static factory methods** — `Find()`, `IsClientExist()`, `GetAddNewClientObject()`… the class creates and manages its own instances.

---

## 🔒 Security Notes (Password Encryption)

Passwords and PIN codes are **not stored in plain text** in the data files.
They are stored using a simple **character-shift (Caesar-style) encryption** with:

> **Encryption Key = 5**

**Example:**

| Username | Real Password | Stored in `Users.txt` as |
|---|---|---|
| `User2` | `1234` | `6789` |

Each character is shifted by **+5** when saved (`EncryptText`) and shifted back by **−5** when loaded (`DecryptText`).

> ⚠️ **Disclaimer:** this encryption is intentionally simple and exists for **learning purposes** — to demonstrate encapsulating security logic inside the classes. In a production system, passwords should be protected with one-way **hashing** (e.g. bcrypt / SHA-256), not reversible encryption.

---

## 🚀 How to Run

1. **Requirements:** Windows + Visual Studio (the project uses the MSVC-specific `__declspec(property)` extension for C#-style properties).
2. Clone the repository:
   ```bash
   git clone <your-repo-url>
   ```
3. Open `BankSystem(OOP).sln` in Visual Studio.
4. Build & Run.
5. Sample data files (`Clients.txt`, `Users.txt`, `Currencies.txt`, …) are included — the system runs out of the box.

### 🔑 Demo Login

| Username | Password |
|---|---|
| `User2` | `1234` |

*(Remember: inside `Users.txt` it appears as `6789` because of the encryption.)*

---

## 📁 Project Structure

```
BankSystem_OOP/
├── BankSystem(OOP).sln          ← Visual Studio solution
├── BankSystem(OOP).cpp          ← Entry point (3 lines)
├── Global.h                     ← Session state (CurrentUser)
│
├── clsPerson.h                  ← Domain: base class
├── clsBankClient.h              ← Domain: clients, transactions, transfer log
├── clsUser.h                    ← Domain: users, permissions, login register
├── clsCurrency.h                ← Domain: currency exchange engine
│
├── clsString.h                  ← Utility library
├── clsDate.h                    ← Utility library
├── clsUtility.h                 ← Utility library
├── clsValidateInput.h           ← Utility library
│
├── clsScreen.h                  ← UI: base screen
├── clsLoginScreen.h             ← UI: 24 screen classes total
├── clsMainScreen.h                 (Login, Main, Transactions, Manage Users,
├── …                               Currency Exchange, …)
│
└── *.txt                        ← Sample data files (encrypted passwords)
```

---

## 🧠 Lessons Learned & Future Improvements

- **Separation of Concerns (SRP):** domain classes currently handle their own file I/O; the next step is extracting a **Repository / Data-Access layer**.
- **Session state:** `CurrentUser` is a global object; future versions should use **Dependency Injection** or a **Singleton session** for better testability.
- **Cross-platform:** replace MSVC-specific `__declspec(property)` with standard C++ getters/setters.
- **Security:** upgrade the shift cipher to real one-way **hashing** (bcrypt / SHA-256).

---


## 📄 License

Educational project — free to use for learning purposes.