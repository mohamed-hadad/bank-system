#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <limits>
using namespace std;

const string ClientsFileName = "ClientsData.txt";
const string UsersFileName = "Users.txt";

enum enMainMenuOption { eShowClients = 1, eAddClients, eDeleteClient, eUpdateClient, eFindClient, eTransactions, eManageUsers, eLogOut, eExit};
enum enUserPermissions { eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4, pUpdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64 };
enum enManageUsersOption { eListUsers = 1, eAddUser, eDeleteUser, eUpdateUser, eFindUser, MainMenu };
enum enTransactionOption { eDeposit = 1, eWithdraw, eTotalBalances, eMainMenu };

struct stClient {
	string AccNum;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance = 0;
	bool MarkForDelete = false;
};
struct stUser {
	string Username;
	string Password;
	short Permissions = 0;
	bool MarkForDelete = false;
};
stUser CurrentUser;

void Pause() {
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
}
void FlushInput() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/* Print & Read Functions */
void PrintMainMenuScreen() {
	cout << "=================================================\n";
	cout << "\t    Main Menu Screen\n";
	cout << "=================================================\n";
	cout << "   [1] Show Clients List\n";
	cout << "   [2] Add New Client\n";
	cout << "   [3] Delete Client\n";
	cout << "   [4] Update Client Info\n";
	cout << "   [5] Find Client\n";
	cout << "   [6] Transactions\n";
	cout << "   [7] Manage Users\n";
	cout << "   [8] Logout\n";
	cout << "   [9] Exit\n";
	cout << "=================================================\n";
}
void PrintManageUsersScreen() {
	cout << "=================================================\n";
	cout << "\t\tManage Users Menu Screen\n";
	cout << "=================================================\n";
	cout << "   [1] List Users\n";
	cout << "   [2] Add New User\n";
	cout << "   [3] Delete User\n";
	cout << "   [4] Update User Info\n";
	cout << "   [5] Find User\n";
	cout << "   [6] Main Menu\n";
	cout << "=================================================\n";
}
void PrintClientCard(const stClient& Client)
{
	cout << "\nClient Info:";
	cout << "\n----------------------------------------";
	cout << "\nAccount Number  : " << Client.AccNum;
	cout << "\nName            : " << Client.Name;
	cout << "\nPhone Number    : " << Client.Phone;
	cout << "\nAccount Balance : " << Client.AccountBalance;
	cout << "\n----------------------------------------\n";
}

enMainMenuOption ReadMenuOption() {
	short n;
	cout << "Select an Option [1 to 9]: ";
	while (!(cin >> n) || n < 1 || n > 9) {
		FlushInput();
		cout << "Incorrect Option. Please Enter a Value Between [1 To 9]: ";
	}
	return (enMainMenuOption)n;
}
enManageUsersOption ReadManageUsersOption() {
	short n;
	cout << "Select an Option [1 to 6]: ";
	while (!(cin >> n) || n < 1 || n > 6) {
		FlushInput();
		cout << "Incorrect Option. Please Enter a Value Between [1 To 6]: ";
	}
	return (enManageUsersOption)n;
}
enTransactionOption ReadTransactionOption() {
	short n;
	cout << "Select an Option [1 to 4]: ";
	while (!(cin >> n) || n < 1 || n > 4) {
		FlushInput();
		cout << "Incorrect Option. Please Enter a Value Between [1, 4]: ";
	}
	return (enTransactionOption)n;
}
void ReadNewDataForExistingAcc(stClient& Client) {
	cout << "Enter PinCode        : ";  cin >> Client.PinCode;
	cout << "Enter Name           : ";  getline(cin >> ws, Client.Name);
	cout << "Enter Phone          : ";  cin >> Client.Phone;
	cout << "Enter Account Balance: ";  cin >> Client.AccountBalance;
}
string ReadAccNum() {
	string AccNum;
	cout << "\nEnter Account Number : ";
	cin >> AccNum;
	return AccNum;
}


/*Transfer Client-Data Between Line-Record String and Vectors*/
vector <string> SplitString(string S1, string delim = " ") {
	vector <string> vWords;
	string sWord;
	size_t pos = 0;

	while ((pos = S1.find(delim)) != string::npos) {
		sWord = S1.substr(0, pos);
		if (sWord != "")
			vWords.push_back(sWord);
		S1.erase(0, pos + delim.length());
	}
	if (S1 != "") {
		vWords.push_back(S1);
	}
	return vWords;
}
stClient ConvertLineToRecord(string sLineRecord, string delim = "#//#")
{
	stClient ClientData;
	vector <string> vClientData = SplitString(sLineRecord, delim);
	if (vClientData.size() < 5) return ClientData;

	ClientData.AccNum = vClientData[0];
	ClientData.PinCode = vClientData[1];
	ClientData.Name = vClientData[2];
	ClientData.Phone = vClientData[3];
	ClientData.AccountBalance = stod(vClientData[4]);
	return ClientData;
}
string ConvertRecordToLine(const stClient& ClientData, string delim = "#//#")
{
	string stClientRecord = "";
	stClientRecord += ClientData.AccNum + delim;
	stClientRecord += ClientData.PinCode + delim;
	stClientRecord += ClientData.Name + delim;
	stClientRecord += ClientData.Phone + delim;
	stClientRecord += to_string(ClientData.AccountBalance);

	return stClientRecord;
}

/* Dealing With Files */
void SaveClientsDataToFile(string FileName, vector <stClient>& vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	if (MyFile.is_open())
	{
		for (stClient& n : vClients)
		{
			if (n.MarkForDelete == false)
				MyFile << ConvertRecordToLine(n) << '\n';
		}
		MyFile.close();
	}
}
vector <stClient> LoadClientsFromFileToVector(string FileName)
{
	vector <stClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode
	if (MyFile.is_open())
	{
		string sLine;
		while (getline(MyFile, sLine))
		{
			vClients.push_back(ConvertLineToRecord(sLine));
		}
		MyFile.close();
	}
	return vClients;
}


/*Another Functions*/
void GoBackToMainMenu() {
	cout << "\nPress any key to go back to Main Menu...";
	Pause();
}
void GoBackToTransactionsMenu() {
	cout << "\n\nPress any key to go back to Transactions Menu...";
	Pause();
}
void GoBackToManageUsersMenu() {
	cout << "\n\nPress any key to go back to Manage Users Menu...";
	Pause();
}
bool IsAccountExist(const string& AccNum, const vector <stClient>& vClients, stClient& Client) {
	for (const stClient& n : vClients)
		if (n.AccNum == AccNum) {
			Client = n;
			return true;
		}
	return false;
}



// 1- Show Accounts List
void PrintClientRecordLine(const stClient& Client)
{
	cout << "| " << setw(15) << left << Client.AccNum;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}
void ShowAllAccListScreen()
{

	vector <stClient> vClients = LoadClientsFromFileToVector(ClientsFileName);
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n________________________________________________________________________________________________\n\n";
	cout << "| " << setw(15) << left << "Account Number";
	cout << "| " << setw(40) << left << "Client Name";
	cout << "| " << setw(12) << left << "Phone";
	cout << "| " << setw(12) << left << "Balance";
	cout << "\n________________________________________________________________________________________________\n\n";
	for (const stClient& Client : vClients)
	{
		PrintClientRecordLine(Client);
		cout << endl;
	}
	cout << "________________________________________________________________________________________________\n\n";
}

// 2- Add New Accounts
void AddNewAcc()
{
	string AccNum = ReadAccNum();
	vector <stClient> vClients = LoadClientsFromFileToVector(ClientsFileName);

	stClient Client;
	while (IsAccountExist(AccNum, vClients, Client)) {
		cout << "\nClient with [" << AccNum << "] already exists, Enter another Account Number: ";
		cin >> AccNum;
	}
	Client.AccNum = AccNum;
	ReadNewDataForExistingAcc(Client);
	vClients.push_back(Client);
	SaveClientsDataToFile(ClientsFileName, vClients);
}
void ShowAddNewAccScreen() {
	char AddMoreClients = 'N';
	do {
		system("cls");
		cout << "=================================================\n";
		cout << "\t\tAdd New Clients Screen\n";
		cout << "=================================================\n";
		cout << "Adding New Client:\n\n";

		AddNewAcc();

		cout << "\nClient Added Successfully, do you want to add more clients (Y/N) : ";
		cin >> AddMoreClients;

	} while (toupper(AddMoreClients) == 'Y');
}

// 3- Delete Account
void MarkAccForDeleteByAccNum(const string& AccNum, vector <stClient>& vClients)
{
	for (stClient& n : vClients) {
		if (n.AccNum == AccNum) {
			n.MarkForDelete = true;
		}
	}
}
void DeleteAccByAccNum(const string& AccNum, vector <stClient>& vClients)
{
	stClient Client;
	char Answer = 'N';

	if (IsAccountExist(AccNum, vClients, Client))
	{
		PrintClientCard(Client);
		cout << "\nAre you sure you want delete this Account? (Y/N): "; cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			MarkAccForDeleteByAccNum(AccNum, vClients);
			SaveClientsDataToFile(ClientsFileName, vClients);

			//Refresh Clients in Vector After Delete
			vClients = LoadClientsFromFileToVector(ClientsFileName);

			cout << "\n\nAccount Deleted Successfully.\n";
		}
		else {
			cout << "\n\nAction canceled. Your account was not deleted.\n";
		}
		return;
	}

	cout << "\nClient with Account Number [" << AccNum << "] Not Found!\n";
}
void ShowDeleteAccScreen() {
	cout << "=================================================\n";
	cout << "\t\tDelete Client Screen\n";
	cout << "=================================================\n";

	vector <stClient> vClients = LoadClientsFromFileToVector(ClientsFileName);
	string AccNum = ReadAccNum();
	DeleteAccByAccNum(AccNum, vClients);
}

// 4- Update Account
void UpdateAccInfoByAccNum(const string& AccNum, vector <stClient>& vClients)
{

	stClient Client;
	char Answer = 'N';

	if (IsAccountExist(AccNum, vClients, Client))
	{
		PrintClientCard(Client);
		cout << "\nAre you Sure You Want Update This Account? (Y/N): "; cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			for (stClient& n : vClients) {
				if (n.AccNum == Client.AccNum) {
					ReadNewDataForExistingAcc(n);
					break;
				}
			}

			SaveClientsDataToFile(ClientsFileName, vClients);
			cout << "\n\nClient Updated Successfully.\n";
		}
		return;
	}

	cout << "\nClient with Account Number [" << AccNum << "] Not Found!\n";
}
void ShowUpdateAccScreen() {

	cout << "=================================================\n";
	cout << "\t   Update Account Info Screen\n";
	cout << "=================================================\n";
	vector <stClient> vClients = LoadClientsFromFileToVector(ClientsFileName);
	string AccNum = ReadAccNum();
	UpdateAccInfoByAccNum(AccNum, vClients);
}

// 5- Find an Account
void FindAcc() {

	cout << "=================================================\n";
	cout << "\t       Find Account Screen\n";
	cout << "=================================================\n";
	vector <stClient> vClients = LoadClientsFromFileToVector(ClientsFileName);
	string AccNum = ReadAccNum();
	stClient Client;

	if (IsAccountExist(AccNum, vClients, Client)) {
		PrintClientCard(Client);
		return;
	}
	cout << "Client with Account Number [" << AccNum << "] Not Found!\n";
}

// 6- Show Transactions Screen
void DepositBalanceToAccByAccNum(const string& AccNum, double BalanceAmount, vector <stClient>& vClients) {
	char PerformTransaction = 'N';
	cout << "\nAre you sure you want perform this transaction (Y/N) ? ";
	cin >> PerformTransaction;

	if (toupper(PerformTransaction) == 'Y') {
		for (stClient& n : vClients) {
			if (n.AccNum == AccNum) {
				n.AccountBalance += BalanceAmount;
				SaveClientsDataToFile(ClientsFileName, vClients);
				cout << "\nDone successfully. Now Account Balance is " << n.AccountBalance << endl;
				return;
			}
		}
	}
	cout << "\nTransaction canceled. ";
}
void ShowDepositScreen() {
	cout << "----------------------------------------\n";
	cout << "\t    Deposit Screen\n";
	cout << "----------------------------------------\n";

	vector <stClient> vClients = LoadClientsFromFileToVector(ClientsFileName);
	stClient Client;
	string AccNum = ReadAccNum();

	while (!IsAccountExist(AccNum, vClients, Client)) {
		cout << "\nClient with [" << AccNum << "] does NOT exist, Please Enter another Account Number: ";
		cin >> AccNum;
	}

	PrintClientCard(Client);
	double DepositAmount;
	cout << "\nPlease Enter Deposit Amount: ";
	cin >> DepositAmount;
	while (DepositAmount <= 0) {
		cout << "Invalid Amount! Please enter a positive value: ";
		cin >> DepositAmount;
	}
	DepositBalanceToAccByAccNum(AccNum, DepositAmount, vClients);
}
void ShowWithdrawScreen() {
	cout << "----------------------------------------\n";
	cout << "\t    Withdraw Screen\n";
	cout << "----------------------------------------\n";

	vector <stClient> vClients = LoadClientsFromFileToVector(ClientsFileName);
	stClient Client;
	string AccNum = ReadAccNum();

	while (!IsAccountExist(AccNum, vClients, Client)) {
		cout << "\nClient with [" << AccNum << "] does NOT exist, Please Enter another Account Number: ";
		cin >> AccNum;
	}

	PrintClientCard(Client);
	double WithdrawAmount;
	cout << "\nPlease Enter Withdraw Amount: ";
	cin >> WithdrawAmount;

	while (WithdrawAmount <= 0 || WithdrawAmount > Client.AccountBalance) {
		if (Client.AccountBalance == 0) {
			cout << "\nSorry! There is NO Balance in Your Account.\n";
			return;
		}
		else if (WithdrawAmount > Client.AccountBalance) {
			cout << "\nAmount Exceeds the balance, you can withdraw up to: " << Client.AccountBalance;
			cout << "\nPlease Enter another Withdraw Amount: ";
			cin >> WithdrawAmount;
		}
		else {
			cout << "Invalid Amount! Please enter a positive value: ";
			cin >> WithdrawAmount;
		}
	}
	DepositBalanceToAccByAccNum(AccNum, WithdrawAmount * -1, vClients);
}
void PrintAccTotalBalances(const stClient& Client)
{
	cout << "| " << setw(15) << left << Client.AccNum;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}
void ShowTotalBalancesScreen()
{
	vector <stClient> vClients = LoadClientsFromFileToVector(ClientsFileName);
	cout << "\n\t\t\t\t  Client List (" << vClients.size() << ") Client(s).";
	cout << "\n________________________________________________________________________________________________\n";
	cout << "| " << setw(15) << left << "Account Number";
	cout << "| " << setw(40) << left << "Client Name";
	cout << "| " << setw(12) << left << "Balance";
	cout << "\n________________________________________________________________________________________________\n";
	double TotalBalances = 0;
	for (const stClient& Client : vClients)
	{
		TotalBalances += Client.AccountBalance;
		PrintAccTotalBalances(Client);
		cout << endl;
	}
	cout << "________________________________________________________________________________________________\n";
	cout << "\n\t\t\t\t  Total Balances = " << TotalBalances << endl;

}
void PerformTransactionOptionScreen(const enTransactionOption& Option) {
	system("cls");
	switch (Option) {
	case enTransactionOption::eDeposit:
		ShowDepositScreen();
		GoBackToTransactionsMenu();
		break;
	case enTransactionOption::eWithdraw:
		ShowWithdrawScreen();
		GoBackToTransactionsMenu();
		break;
	case enTransactionOption::eTotalBalances:
		ShowTotalBalancesScreen();
		GoBackToTransactionsMenu();
		break;
	case enTransactionOption::eMainMenu:
		break;
	}
}
void ShowTransactionsScreen() {
	enTransactionOption Option;
	do {
		system("cls");
		cout << "=================================================\n";
		cout << "\t       Transactions Screen\n";
		cout << "=================================================\n";
		cout << "   [1] Deposit\n";
		cout << "   [2] Withdraw\n";
		cout << "   [3] Total Balances\n";
		cout << "   [4] Main Menu\n";
		cout << "=================================================\n";
		Option = ReadTransactionOption();
		PerformTransactionOptionScreen(Option);
	} while (Option != enTransactionOption::eMainMenu);

}



// 7- Manage Users
stUser ConvertUserLineToRecord(string sLineRecord, string delim = "#//#")
{
	stUser UsersData;
	vector <string> vUsersData = SplitString(sLineRecord, delim);
	if (vUsersData.size() < 3) return UsersData;
	UsersData.Username = vUsersData[0];
	UsersData.Password = vUsersData[1];
	UsersData.Permissions = stoi(vUsersData[2]);
	return UsersData;
}
vector <stUser> LoadLoginRegisterFromFileToVector(string FileName)
{
	vector <stUser> vUsers;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode
	if (MyFile.is_open())
	{
		string sLine;
		while (getline(MyFile, sLine))
		{
			vUsers.push_back(ConvertUserLineToRecord(sLine));
		}
		MyFile.close();
	}
	return vUsers;
}
void ReadPermissionsForUser(stUser& User) {
	User.Permissions = 0;
	char Answer = 'N';
	cout << "\nDo You Want To Give Full Access (Y/N) ? "; cin >> Answer;
	if (toupper(Answer) == 'Y') {
		User.Permissions = enUserPermissions::eAll;
		return;
	}

	cout << "\nDo You Want To Give Access To: \n";

	cout << "\nShow Clients List (Y/N) ? "; cin >> Answer;
	if (toupper(Answer) == 'Y')
		User.Permissions += enUserPermissions::pListClients;

	cout << "Add New Clients (Y/N) ? "; cin >> Answer;
	if (toupper(Answer) == 'Y')
		User.Permissions += enUserPermissions::pAddNewClient;

	cout << "Delete Clients (Y/N) ? "; cin >> Answer;
	if (toupper(Answer) == 'Y')
		User.Permissions += enUserPermissions::pDeleteClient;

	cout << "Update Clients Info (Y/N) ? "; cin >> Answer;
	if (toupper(Answer) == 'Y')
		User.Permissions += enUserPermissions::pUpdateClient;

	cout << "Find Clients (Y/N) ? "; cin >> Answer;
	if (toupper(Answer) == 'Y')
		User.Permissions += enUserPermissions::pFindClient;

	cout << "Transactions (Y/N) ? "; cin >> Answer;
	if (toupper(Answer) == 'Y')
		User.Permissions += enUserPermissions::pTransactions;

	cout << "Manage Users (Y/N) ? "; cin >> Answer;
	if (toupper(Answer) == 'Y')
		User.Permissions += enUserPermissions::pManageUsers;


}
string ReadUsername() {
	string Username;
	cout << "\nEnter Username : ";
	getline(cin >> ws, Username);
	return Username;
}
void PrintUserCard(const stUser& User)
{
	cout << "\nUser Info:";
	cout << "\n----------------------------------------";
	cout << "\nUsername    : " << User.Username;
	cout << "\nPermissions : " << User.Permissions;
	cout << "\n----------------------------------------\n";
}
void ReadNewDataForExistingUser(stUser& User) {
	cout << "Enter Password: "; cin >> User.Password;
	ReadPermissionsForUser(User);
}
stUser ReadUser() {
	stUser User;
	cout << "Enter Username: "; cin >> User.Username;
	cout << "Enter Password: "; cin >> User.Password;
	return User;
}
bool IsUsernameExist(const string& Username) {
	vector <stUser> vUsers = LoadLoginRegisterFromFileToVector(UsersFileName);
	for (const stUser& n : vUsers)
		if (n.Username == Username) {
			return true;
		}
	return false;
}
bool FindUserByUsername(const string& Username, stUser& User) {
	vector <stUser> vUsers = LoadLoginRegisterFromFileToVector(UsersFileName);
	for (const stUser& n : vUsers)
		if (n.Username == Username) {
			User = n;
			return true;
		}
	return false;
}
bool CheckUser(const string& Username, const string& Password, stUser& User) {
	vector <stUser> vUsers = LoadLoginRegisterFromFileToVector(UsersFileName);
	for (const stUser& n : vUsers)
		if (n.Username == Username && n.Password == Password) {
			User = n;
			return true;
		}
	return false;
}
string ConvertUserRecordToLine(const stUser& User, string delim = "#//#")
{
	string stUserRecord = "";
	stUserRecord += User.Username + delim;
	stUserRecord += User.Password + delim;
	stUserRecord += to_string(User.Permissions);

	return stUserRecord;
}
void SaveUsersDataToFile(const string& FileName, vector <stUser>& vUsers)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	if (MyFile.is_open())
	{
		for (stUser& n : vUsers)
		{
			if (n.MarkForDelete == false)
				MyFile << ConvertUserRecordToLine(n) << '\n';
		}
		MyFile.close();
	}
}
void AddDataLineToFile(const string& FileName, string stDataLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::app);
	if (MyFile.is_open())
	{
		MyFile << stDataLine << '\n';
		MyFile.close();
	}
}

// 7.1- Show Users List
void PrintUsersRecordLine(const stUser& User)
{
	cout << "| " << setw(15) << left << User.Username;
	cout << "| " << setw(5) << left << User.Permissions;
}
void ShowAllUsersListScreen()
{
	vector <stUser> vUsers = LoadLoginRegisterFromFileToVector(UsersFileName);
	cout << "\n\t\t\t\t\tUser List (" << vUsers.size() << ") User(s).";
	cout << "\n________________________________________________________________________________________________\n\n";
	cout << "| " << setw(15) << left << "Username";
	cout << "| " << setw(5) << left << "Permissions";
	cout << "\n________________________________________________________________________________________________\n\n";
	for (const stUser& User : vUsers)
	{
		PrintUsersRecordLine(User);
		cout << endl;
	}
	cout << "________________________________________________________________________________________________\n\n";
}

// 7.2- Add New User
void ReadNewUser(stUser& User) {
	cout << "Enter Username: "; getline(cin >> ws, User.Username);
	while (IsUsernameExist(User.Username)) {
		cout << "\nUser with username[" << User.Username << "] already exists, Enter another username: ";
		cin >> User.Username;
	}
	cout << "Enter Password: "; getline(cin >> ws, User.Password);
	ReadPermissionsForUser(User);
}
void AddNewUser()
{
	stUser User;
	ReadNewUser(User);
	AddDataLineToFile(UsersFileName, ConvertUserRecordToLine(User));
}
void ShowAddNewUsersScreen() {
	char AddMoreUsers = 'N';
	do {
		system("cls");
		cout << "=================================================\n";
		cout << "\t\tAdd New Users Screen\n";
		cout << "=================================================\n";
		cout << "Adding New User:\n\n";

		AddNewUser();

		cout << "\nUser Added Successfully, do you want to add more users (Y/N) ? ";
		cin >> AddMoreUsers;

	} while (toupper(AddMoreUsers) == 'Y');
}

// 7.3- Delete User
void MarkUserForDelete(const string& Username, vector <stUser>& vUsers)
{
	for (stUser& n : vUsers) {
		if (n.Username == Username) {
			n.MarkForDelete = true;
		}
	}
}
void DeleteUserByUsername(const string& Username, vector <stUser>& vUsers)
{
	if (Username == "Admin") {
		cout << "\nThis User Can't be Deleted.";
		return;
	}
	char Answer = 'N';
	stUser User;
	if (FindUserByUsername(Username, User)) {
		PrintUserCard(User);
		cout << "\nAre you sure you want delete this Account? (Y/N): "; cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			MarkUserForDelete(Username, vUsers);
			SaveUsersDataToFile(UsersFileName, vUsers);

			//Refresh Clients in Vector After Delete
			vUsers = LoadLoginRegisterFromFileToVector(UsersFileName);

			cout << "\n\nUser Deleted Successfully.\n";
		}
		else {
			cout << "\n\nAction canceled.\n";
		}
		return;
	}

	cout << "\nUser with Username [" << Username << "] Not Found!\n";
}
void ShowDeleteUserScreen()
{
	cout << "=================================================\n";
	cout << "\t\tDelete User Screen\n";
	cout << "=================================================\n";

	vector <stUser> vUsers = LoadLoginRegisterFromFileToVector(UsersFileName);
	string Username = ReadUsername();
	DeleteUserByUsername(Username, vUsers);
}

// 7.4- Update User
void UpdateUserInfoByUsername(const string& Username, vector <stUser>& vUsers)
{
	if (Username == "Admin") {
		cout << "\nThis User Can't be Updated.";
		return;
	}
	stUser User;
	char Answer = 'N';

	if (FindUserByUsername(Username, User))
	{
		PrintUserCard(User);
		cout << "\nAre you Sure You Want Update This User? (Y/N): "; cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			for (stUser& n : vUsers) {
				if (n.Username == User.Username) {
					ReadNewDataForExistingUser(n);
					break;
				}
			}

			SaveUsersDataToFile(UsersFileName, vUsers);
			cout << "\n\nUser Updated Successfully.\n";
		}
		return;
	}

	cout << "\nUser with Username [" << Username << "] Not Found!\n";
}
void ShowUpdateUserScreen() {
	cout << "=================================================\n";
	cout << "\t      Update User Info Screen\n";
	cout << "=================================================\n";
	vector <stUser> vUser = LoadLoginRegisterFromFileToVector(UsersFileName);
	string Username = ReadUsername();
	UpdateUserInfoByUsername(Username, vUser);
}

// 7.5- Find a User
void FindUser() {
	cout << "=================================================\n";
	cout << "\t          Find User Screen\n";
	cout << "=================================================\n";
	vector <stUser> vUsers = LoadLoginRegisterFromFileToVector(UsersFileName);
	string Username = ReadUsername();
	stUser User;

	if (FindUserByUsername(Username, User)) {
		PrintUserCard(User);
		return;
	}
	cout << "User with Username [" << Username << "] Not Found!\n";
}
// Show Each Screen of the options
void PerformManageUsersOptionScreen(const enManageUsersOption& Option) {
	system("cls");
	switch (Option) {
	case enManageUsersOption::eListUsers:
		ShowAllUsersListScreen();
		GoBackToManageUsersMenu();
		break;
	case enManageUsersOption::eAddUser:
		ShowAddNewUsersScreen();
		GoBackToManageUsersMenu();
		break;
	case enManageUsersOption::eDeleteUser:
		ShowDeleteUserScreen();
		GoBackToManageUsersMenu();
		break;
	case enManageUsersOption::eUpdateUser:
		ShowUpdateUserScreen();
		GoBackToManageUsersMenu();
		break;
	case enManageUsersOption::eFindUser:
		FindUser();
		GoBackToManageUsersMenu();
		break;
	case enManageUsersOption::MainMenu:
		break;
	}
}
bool CheckUserPermissions(const enMainMenuOption& Option) {

	if (CurrentUser.Permissions == enUserPermissions::eAll)
		return true;

	switch (Option) {
	case enMainMenuOption::eShowClients:  return (CurrentUser.Permissions & enUserPermissions::pListClients);
	case enMainMenuOption::eAddClients:   return (CurrentUser.Permissions & enUserPermissions::pAddNewClient);
	case enMainMenuOption::eDeleteClient: return (CurrentUser.Permissions & enUserPermissions::pDeleteClient);
	case enMainMenuOption::eUpdateClient: return (CurrentUser.Permissions & enUserPermissions::pUpdateClient);
	case enMainMenuOption::eFindClient:   return (CurrentUser.Permissions & enUserPermissions::pFindClient);
	case enMainMenuOption::eTransactions: return (CurrentUser.Permissions & enUserPermissions::pTransactions);
	case enMainMenuOption::eManageUsers:  return (CurrentUser.Permissions & enUserPermissions::pManageUsers);
	case enMainMenuOption::eLogOut:       return true;
	case enMainMenuOption::eExit:         return true;
	default:                          return false;
	}

}
// Manage Users
void ManageUsers() {
	enManageUsersOption Option;
	do {
		system("cls");
		PrintManageUsersScreen();
		Option = ReadManageUsersOption();
		PerformManageUsersOptionScreen(Option);
	} while (Option != enManageUsersOption::MainMenu);
}
// Show Each Screen of the options
void ShowAccessDeniedMessage() {
	cout << "-----------------------------------------------\n";
	cout << "Access Denied,\n";
	cout << "You Don't Have Permissions To Do This,\n";
	cout << "Please Contact Your Admin.\n";
	cout << "-----------------------------------------------\n\n";
}
void PerformMainMenuOptionScreen(const enMainMenuOption& Option) {

	system("cls");
	if (!CheckUserPermissions(Option)) {
		ShowAccessDeniedMessage();
		GoBackToMainMenu();
		return;
	}

	switch (Option) {
	case enMainMenuOption::eShowClients:
		ShowAllAccListScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOption::eAddClients:
		ShowAddNewAccScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOption::eDeleteClient:
		ShowDeleteAccScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOption::eUpdateClient:
		ShowUpdateAccScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOption::eFindClient:
		FindAcc();
		GoBackToMainMenu();
		break;
	case enMainMenuOption::eTransactions:
		ShowTransactionsScreen();
		break;
	case enMainMenuOption::eManageUsers:
		ManageUsers();
		break;
	case enMainMenuOption::eLogOut:
		break;
	}
}
void ShowLoginScreenHeader() {
	cout << "=================================================\n";
	cout << "\t\tLogin Screen\n";
	cout << "=================================================\n";
}
// Open Bank System Interface
bool OpenBankSystem() {
	enMainMenuOption Option;
	do {
		system("cls");
		PrintMainMenuScreen();
		Option = ReadMenuOption();
		PerformMainMenuOptionScreen(Option);
		if (Option == enMainMenuOption::eExit)
			return false;
	} while (Option != enMainMenuOption::eLogOut);
	return true;
}
void Login() {
	 do{
		stUser User;
		bool LoginFailed = false;
		do
		{
			system("cls");
			ShowLoginScreenHeader();

			if (LoginFailed)
				cout << "Invalid Username/Password!\n";

			User = ReadUser();
			LoginFailed = !CheckUser(User.Username, User.Password, CurrentUser);

		} while (LoginFailed);
	 } while (OpenBankSystem());
}
int main()
{
	Login();

}