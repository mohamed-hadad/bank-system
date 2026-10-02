#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "Global.h"
#include "clsUtility.h"
#include <vector>
#include <fstream>
using namespace std;

inline string ClientsFileName = "Clients.txt";
inline string TransferLogFileName = "TransferLog.txt";

class clsBankClient : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode, AddNewMode, DeleteMode};
    enMode _Mode;
    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkedForDelete = false;

    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], clsUtility::DecryptText(vClientData[5], 24), stod(vClientData[6]));

    }
    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += Client.FirstName + Seperator;
        stClientRecord += Client.LastName + Seperator;
        stClientRecord += Client.Email + Seperator;
        stClientRecord += Client.PhoneNumber + Seperator;
        stClientRecord += Client.AccountNumber + Seperator;
        stClientRecord += clsUtility::EncryptText(Client.PinCode, 24) + Seperator;
        stClientRecord += to_string(Client.AccountBalance);

        return stClientRecord;

    }
    static vector <clsBankClient> _LoadClientsDataFromFile()
    {

        vector <clsBankClient> vClients;

        fstream MyFile(ClientsFileName, ios::in);

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {
                if (Line != "")
                {
                 clsBankClient Client = _ConvertLinetoClientObject(Line);
                 vClients.push_back(Client);
                }
            }

            MyFile.close();

        }

        return vClients;

    }
    static void _SaveCleintsDataToFile(vector <clsBankClient> vClients)
    {

        fstream MyFile(ClientsFileName, ios::out);
        string DataLine;

        if (MyFile.is_open())
        {

            for (const clsBankClient& C : vClients)
            {
                if (C.MarkedForDelete == false)
                {
                    DataLine = _ConverClientObjectToLine(C);
                    MyFile << DataLine << endl;
                }
            }

            MyFile.close();

        }

    }
    static clsBankClient _GetEmptyClient()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }
    static clsBankClient _Find(string accountNum, string pinCode, bool withPinCode) 
    {
        fstream file(ClientsFileName, ios::in);
        
        if (file.is_open()) 
        {
            string line;
            while (getline(file, line)) 
            {
                if (line != "")
                {
                    clsBankClient client = _ConvertLinetoClientObject(line);
                    if (client.AccountNumber == accountNum && (!withPinCode || client.PinCode == pinCode)) {
                        file.close();
                        return client;
                    }
                }
            }
            file.close();
        }
        return _GetEmptyClient();
    }

    void _AddDataLineToFile(string stDataLine)
    {
        fstream MyFile;
        MyFile.open(ClientsFileName, ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }
    void _AddNewClientToDataFile()
    {

        _AddDataLineToFile(_ConverClientObjectToLine(*this));
    }

    void _UpdateFileData()
    {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber == _AccountNumber)
            {
                C = *this;
                break;
            }

        }

        _SaveCleintsDataToFile(_vClients);

    }

    string _PrepareTransferRecord(double TransferAmount, const clsBankClient& DestinationClient)
    {
        string Delim = "#//#";
        string DateAndTime = clsDate::FormatDate(clsDate::GetSystemDate()) + " - " + clsDate::GetSystemTime();

        return DateAndTime + Delim + AccountNumber + Delim + DestinationClient.AccountNumber + Delim + to_string(TransferAmount) + Delim + CurrentUser.Username;
    }
    void _LogTransfer(double TransferAmount, const clsBankClient& DestinationClient)
    {
        string stDataLine = _PrepareTransferRecord(TransferAmount, DestinationClient);

        fstream file;
        file.open(TransferLogFileName, ios::out | ios::app);

        if (file.is_open())
        {
            file << stDataLine << endl;
            file.close();
        }
    }

    struct stTransferLog;
    static stTransferLog _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
    {
        vector <string> vTransferLog = clsString::Split(Line, Seperator);

        stTransferLog TransferLog;

        TransferLog._DateAndTime = vTransferLog[0];
        TransferLog._SenderAccNum = vTransferLog[1];
        TransferLog._ReceiverAccNum = vTransferLog[2];
        TransferLog._Amount = vTransferLog[3];
        TransferLog._Username = vTransferLog[4];

        return TransferLog;
    }
public:
    clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string PhoneNum,string AccountNumber, string PinCode, float AccountBalance)
        : clsPerson(FirstName, LastName,  Email, PhoneNum)
    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;
    }

    struct stTransferLog{
        string _DateAndTime;
        string _SenderAccNum;
        string _ReceiverAccNum;
        string _Amount;
        string _Username;
    };
    
    // Properties
    bool GetMarkedForDelete() const
    {
        return _MarkedForDelete;
    }
    __declspec(property(get = GetMarkedForDelete)) bool MarkedForDelete;

    string GetAccountNumber() const
    {
        return _AccountNumber;
    }
    __declspec(property(get = GetAccountNumber)) string AccountNumber;

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }
    string GetPinCode() const
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }
    float GetAccountBalance() const
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;


    // Methods
    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }
    static bool IsClientExist(string AccountNumber)
    {

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return (!Client1.IsEmpty());
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded, svFaildAccountNumberExists};
    enSaveResults Save()
    {

        switch (_Mode)
        {
            case enMode::EmptyMode:
            {
                if(IsEmpty())
               return enSaveResults::svFaildEmptyObject;
            }

            case enMode::UpdateMode:
            {
                _UpdateFileData();
                return enSaveResults::svSucceeded;
                break;
            }
            case enMode::AddNewMode:
            {
                //This will add new record to file or database
                if (clsBankClient::IsClientExist(_AccountNumber))
                {
                    return enSaveResults::svFaildAccountNumberExists;
                }
                else
                {
                    _AddNewClientToDataFile();

                    //We need to set the mode to update after add new
                    _Mode = enMode::UpdateMode;
                    return enSaveResults::svSucceeded;
                }

                break;
            }
        }
    }

    static clsBankClient Find(string AccountNumber)
    {
        return _Find(AccountNumber, "", false);
    }
    static clsBankClient Find(string AccountNumber, string PinCode)
    {
        return _Find(AccountNumber, PinCode, true);
    }

    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    bool Delete()
    {

        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber == _AccountNumber)
            {
                C._MarkedForDelete = true;
                break;
            }

        }
        _SaveCleintsDataToFile(_vClients);

        *this = _GetEmptyClient();

        return true;

    }

    static vector <clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }

    static float GetTotalBalances()
    {
        vector <clsBankClient> vClients = _LoadClientsDataFromFile();

        double TotalBalances = 0;

        for (const clsBankClient& Client : vClients)
        {

            TotalBalances += Client.AccountBalance;
        }

        return TotalBalances;

    }

    void Deposit(double Amount)
    {
        _AccountBalance += Amount;
        Save();
    }
    bool Withdraw(double Amount)
    {
        if (Amount > _AccountBalance)
        {
            return false;
        }
        else
        {
            _AccountBalance -= Amount;
            Save();
            return true;
        }

    }

    bool Transfer(float TransferAmount, clsBankClient& DestinationClient)
    {
        if (TransferAmount > AccountBalance)
        {
            return false;
        }

        Withdraw(TransferAmount);
        DestinationClient.Deposit(TransferAmount);
        _LogTransfer(TransferAmount, DestinationClient);
        return true;
    }
    static vector <stTransferLog> GetTransferLogList(string FileName)
    {
        vector <stTransferLog> vTransferLog;
        fstream MyFile;
        MyFile.open(FileName, ios::in);
        if (MyFile.is_open())
        {
            string sLine;
            while (getline(MyFile, sLine))
            {
                vTransferLog.push_back(_ConvertTransferLogLineToRecord(sLine));
            }
            MyFile.close();
        }
        return vTransferLog;
    }
};

