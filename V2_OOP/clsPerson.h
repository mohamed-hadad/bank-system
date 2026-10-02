#pragma once
#include <iostream>
using namespace std;
class clsPerson
{

private:
    string _FirstName;
    string _LastName;
    string _Email;
    string _PhoneNumber;

public:
    clsPerson(string FirstName, string LastName, string Email, string PhoneNum)
    {
        _FirstName = FirstName;
        _LastName = LastName;
        _Email = Email;
        _PhoneNumber = PhoneNum;
    }

    //Properties
    string GetFullName() const
    {
        return _FirstName + " " + _LastName;
    }
    __declspec(property(get = GetFullName)) string FullName;

    void SetFirstName(string FirstName)
    {
        _FirstName = FirstName;
    }
    string GetFirstName() const
    {
        return _FirstName;
    }
    __declspec(property(get = GetFirstName, put = SetFirstName)) string FirstName;

    void SetLastName(string LastName)
    {
        _LastName = LastName;
    }
    string GetLastName() const
    {
        return _LastName;
    }
    __declspec(property(get = GetLastName, put = SetLastName)) string LastName;

    void SetEmail(string Email)
    {
        _Email = Email;
    }
    string GetEmail() const
    {
        return _Email;
    }
    __declspec(property(get = GetEmail, put = SetEmail)) string Email;

    void SetPhoneNumber(string PhoneNum)
    {
        _PhoneNumber = PhoneNum;
    }
    string GetPhoneNumber() const
    {
        return _PhoneNumber;
    }
    __declspec(property(get = GetPhoneNumber, put = SetPhoneNumber)) string PhoneNumber;

    void Print()
    {
        cout << "\nInfo:";
        cout << "\n___________________";
        cout << "\nFirstName: " << _FirstName;
        cout << "\nLastName : " << _LastName;
        cout << "\nFull Name: " << GetFullName();
        cout << "\nEmail    : " << _Email;
        cout << "\nPhone    : " << _PhoneNumber;
        cout << "\n___________________\n";

    }

    void SendEmail(string Subject, string Body)
    {

        cout << "\nThe following message sent successfully to email: " << _Email;
        cout << "\nSubject: " << Subject;
        cout << "\nBody: " << Body << endl;

    }
    void SendSMS(string TextMessage)
    {
        cout << "\nThe following SMS sent successfully to phone: " << _PhoneNumber;
        cout << "\n" << TextMessage << endl;
    }


};
