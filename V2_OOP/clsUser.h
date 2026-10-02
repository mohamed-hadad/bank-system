#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsDate.h"
#include "clsString.h"
#include "clsUtility.h"
#include <vector>
#include <fstream>

inline const string UsersFileName = "Users.txt";
inline const string LoginRegisterFileName = "LoginRegister.txt";

using namespace std;

class clsUser : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;
    string _LoginDateAndTime;
    string _Username;
    string _Password;
    int _Permissions;

    bool _MarkedForDelete = false;

    static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData;
        vUserData = clsString::Split(Line, Seperator);

        return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
            vUserData[3], vUserData[4], clsUtility::DecryptText(vUserData[5], 5), stoi(vUserData[6]));

    }

    static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
    {

        string UserRecord = "";
        UserRecord += User.FirstName + Seperator;
        UserRecord += User.LastName + Seperator;
        UserRecord += User.Email + Seperator;
        UserRecord += User.PhoneNumber + Seperator;
        UserRecord += User.Username + Seperator;
        UserRecord += clsUtility::EncryptText(User.Password, 5) + Seperator;
        UserRecord += to_string(User.Permissions);

        return UserRecord;

    }

    static  vector <clsUser> _LoadUsersDataFromFile()
    {

        vector <clsUser> vUsers;

        fstream MyFile;
        MyFile.open(UsersFileName, ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {
                if (Line != "")
                {
                    clsUser User = _ConvertLinetoUserObject(Line);
                    vUsers.push_back(User);
                }
            }

            MyFile.close();

        }

        return vUsers;

    }

    static void _SaveUsersDataToFile(vector <clsUser> vUsers)
    {

        fstream MyFile;
        MyFile.open(UsersFileName, ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsUser U : vUsers)
            {
                if (U.MarkedForDeleted() == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConverUserObjectToLine(U);
                    MyFile << DataLine << endl;

                }

            }

            MyFile.close();

        }

    }

    void _UpdateFileData()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.Username == Username)
            {
                U = *this;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);

    }

    void _AddNewUserToDataFile()
    {

        _AddDataLineToFile(_ConverUserObjectToLine(*this));
    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open(UsersFileName, ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    string _PrepareLoginRegisterRecord()
    {
        string Delim = "#//#";
        return clsDate::FormatDate(clsDate::GetSystemDate()) + " - " + clsDate::GetSystemTime() + Delim + Username + Delim + to_string(Permissions);
    }
    struct stLoginRegisterRecord;
    static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
    {
        vector <string> vLoginInfo = clsString::Split(Line, Seperator);

        stLoginRegisterRecord LoginInfo;

        LoginInfo._LoginDateAndTime = vLoginInfo[0];
        LoginInfo._Username = vLoginInfo[1];
        LoginInfo._Permissions = vLoginInfo[2];

        return LoginInfo;
    }
public:

    enum enUserPermissions {
        eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64, pLoginRegister = 128
    };

    struct stLoginRegisterRecord {
        string _LoginDateAndTime;
        string _Username;
        string _Permissions;
    };

    clsUser(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string Username, string Password,
        int Permissions) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _Username = Username;
        _Password = Password;
        _Permissions = Permissions;
    }


    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    string GetLoginDateAndTime() const
    {
        return _LoginDateAndTime;
    }
    __declspec(property(get = GetLoginDateAndTime)) string LoginDateAndTime;

    void SetUsername(string Username)
    {
        _Username = Username;
    }
    string GetUsername() const
    {
        return _Username;
    }
    __declspec(property(get = GetUsername, put = SetUsername)) string Username;

    void SetPassword(string Password)
    {
        _Password = Password;
    }
    string GetPassword() const
    {
        return _Password;
    }
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;

    void SetPermissions(short Permissions)
    {
        _Permissions = Permissions;
    }
    int GetPermissions() const
    {
        return _Permissions;
    }
    __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;


    static clsUser Find(string Username)
    {
        fstream MyFile;
        MyFile.open(UsersFileName, ios::in); 

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.Username == Username)
                {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();

        }

        return _GetEmptyUserObject();
    }
    static clsUser Find(string Username, string Password)
    {

        fstream MyFile;
        MyFile.open(UsersFileName, ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.Username == Username && User.Password == Password)
                {
                    MyFile.close();
                    return User;
                }

            }

            MyFile.close();

        }
        return _GetEmptyUserObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };
    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {
                return enSaveResults::svFaildEmptyObject;
            }
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
            if (clsUser::IsUserExist(_Username))
            {
                return enSaveResults::svFaildUserExists;
            }
            else
            {
                _AddNewUserToDataFile();
                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
        }

    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }
    static bool IsUserExist(string Username)
    {

        clsUser User = clsUser::Find(Username);
        return (!User.IsEmpty());
    }

    static vector <clsUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }

    static clsUser GetAddNewUserObject(string Username)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", Username, "", 0);
    }

    bool Delete()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.Username == _Username)
            {
                U._MarkedForDelete = true;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);

        *this = _GetEmptyUserObject();

        return true;

    }

    void RegisterLogin()
    {
        string stDataLine = _PrepareLoginRegisterRecord();

        fstream file;
        file.open(LoginRegisterFileName, ios::out | ios::app);

        if (file.is_open()) 
        {
            file << stDataLine << endl;
            file.close();
        }
    }

    static vector <stLoginRegisterRecord> GetLoginRegisterList(string FileName)
    {
        vector <stLoginRegisterRecord> vLoginLog;
        fstream MyFile;
        MyFile.open(FileName, ios::in);
        if (MyFile.is_open())
        {
            string sLine;
            while (getline(MyFile, sLine))
            {
                vLoginLog.push_back(_ConvertLoginRegisterLineToRecord(sLine));
            }
            MyFile.close();
        }
        return vLoginLog;
    }

    };

