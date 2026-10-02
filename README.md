# 🏦 Bank System — From Procedural to OOP (C++)

> **I built the same bank system twice.**
> Once with **Procedural Programming**, and once with **Object-Oriented Programming**.
> This repository is the story of that transformation — same business, two completely different designs.


---

## 📁 Repository Structure

```
Bank-System-Procedural-to-OOP/
├── README.md                  ← You are here (the journey & the comparison)
├── .gitignore
│
├── V1_Procedural/             ← Version 1: Procedural Programming
│   ├── BankSystem.cpp            (the entire system in one single file)
│   ├── ClientsData.txt           (sample data)
│   └── Users.txt                 (sample data — plain-text passwords)
│
└── V2_OOP/                    ← Version 2: Object-Oriented Programming
    ├── BankSystem(OOP).sln       (Visual Studio solution)
    ├── 36 source files           (Screens / Domain / Utilities layers)
    ├── *.txt                     (sample data — encrypted passwords)
    └── README.md                 (full architecture & features deep-dive)
```

- **V1 has no separate README on purpose** — everything about it is explained in the comparison below.
- **For the full OOP architecture, features & security notes → see [V2_OOP/README.md](V2_OOP/README.md).**

---

## ⚖️ Before / After — The Same System, Two Designs

| Aspect | V1 — Procedural | V2 — OOP |
|---|---|---|
| **Code organization** | One single `.cpp` file (~700 lines) | 36 files across 3 layers (Screens / Domain / Utilities) |
| **Data** | Passive structs (`stClient`, `stUser`) passed by reference everywhere | Real objects (`clsBankClient`, `clsUser`) inheriting from `clsPerson` |
| **Behavior** | Free functions acting on data | Objects owning their own rules (`Client.Deposit()`, `Client.Withdraw()`, `Client.Transfer()`) |
| **Withdraw logic** | Implemented as `Deposit(Amount * -1)` 😅 | A real `Withdraw()` that validates and defends the balance itself |
| **UI vs Logic** | Fully coupled — every function prints and reads | Fully separated — 24 screen classes talking to a clean domain API |
| **Encapsulation** | None — all struct fields exposed | All members private, accessed through controlled properties |
| **File I/O** | Scattered load/save functions | Hidden inside the classes (private static converters & loaders) |
| **Passwords in files** | Plain text | Encrypted (simple shift cipher, **Key = 5**) |
| **Extra features** | — | Transfer Log, Login Register, lockout after 3 failed logins, Currency Exchange module, Number-To-Text |
| **Entry point** | `main()` with login + menu loops | `main()` is 3 lines: `clsLoginScreen::ShowLoginScreen();` |

---

## 🔐 A Note on Password Encryption (V2)

In V2, passwords and PIN codes are stored **encrypted** in the data files using a simple character-shift cipher with **Key = 5**:

| Username | Real Password | Stored in `Users.txt` as |
|---|---|---|
| `User2` | `1234` | `6789` |

> ⚠️ Educational-purpose encryption (demonstrating encapsulated security logic). A production system should use one-way hashing (bcrypt / SHA-256). Full details in [V2_OOP/README.md](V2_OOP/README.md#-security-notes-password-encryption).

---

## 🚀 How to Run

### V1 — Procedural
1. Compile `V1_Procedural/BankSystem.cpp` with any C++ compiler.
2. Keep the sample `ClientsData.txt` & `Users.txt` next to the executable.
3. Run — log in with any user from `Users.txt` (passwords are plain text there).

### V2 — OOP
1. **Requirements:** Windows + Visual Studio (the project uses MSVC's `__declspec(property)`).
2. Open `V2_OOP/BankSystem(OOP).sln`, build & run.
3. Sample data files are included — the system runs out of the box.
4. **Demo login:** `User2` / `1234`

Full feature list & architecture: [V2_OOP/README.md](V2_OOP/README.md)

---

## 🧭 Why is V1 still here?

Because the journey matters. V1 is the honest "before" picture: global state, coupled UI, passive data, and a withdraw implemented as a negative deposit. Keeping it next to V2 makes the transformation **visible and reviewable — not just claimed**.

---

## 🙏 Acknowledgments

Special thanks to **Dr. Mohamed Abu Hadhoud** — *Programming Advices* — for the courses, the roadmap, and for teaching OOP as a way of thinking, not just a syntax.

---


## 📄 License

Educational project — free to use for learning purposes.