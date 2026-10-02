#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
//#include "clsDate.h"
using namespace std;

class clsUtility
{
public:
	enum enCharType { SmallLetters = 1, CapitalLetters, Digits, MixChars, SpecialCharacter};

	static void Srand()
	{
		//Seeds the random number generator in C++, called only once
		srand((unsigned)time(NULL));
	}

	// Get Random Number In Range
	static int RandomNum(const int& From, const int& To) {
		int RandNum = rand() % (To - From + 1) + From;
		return RandNum;
	}
	static char GetRandomCharacter(enCharType CharType) {
		switch (CharType) {
			case enCharType::SmallLetters:
			{
				return char(RandomNum(97, 122));
				break;
			}
			case enCharType::CapitalLetters:
			{
				return char(RandomNum(65, 90));
				break;
			}
			case enCharType::SpecialCharacter:
			{
				return char(RandomNum(33, 47));
				break;
			}
			case enCharType::Digits:
			{
				return char(RandomNum(48, 57));
				break;
			}
			case enCharType::MixChars:
			{
				return GetRandomCharacter((enCharType)RandomNum(1,3));
				break;
			}
			default:
			{
				return char(RandomNum(65, 90));
				break;
			}
		}
	}
	// Generate Keys
	static string GenerateWord(enCharType CharType, short WordLength) {
		string Word = "";
		for (int i = 1; i <= WordLength; i++) {
			Word += GetRandomCharacter(CharType);
		}
		return Word;
	}
	static string GenerateKey(enCharType CharType = CapitalLetters) {
		string Key = "";
		for (int i = 1; i <= 4; i++) {
			Key += GenerateWord(CharType, 4);
			if (i != 4)
				Key += "-";
		}
		return Key;
	}
	static void GenerateKeys(short NumberOfKeys, enCharType CharType)
	{

		for (int i = 1; i <= NumberOfKeys; i++)
		{
			cout << "Key [" << i << "] : ";
			cout << GenerateKey(CharType) << endl;
		}
	}
	static void FillArrayWithRandomNumbers(int arr[100], int arrLength, int From, int To)
	{
		for (int i = 0; i < arrLength; i++)
			arr[i] = RandomNum(From, To);
	}
	static void FillArrayWithRandomWords(string arr[100], int arrLength, enCharType CharType, short Wordlength)
	{
		for (int i = 0; i < arrLength; i++)
			arr[i] = GenerateWord(CharType, Wordlength);

	}
	static void FillArrayWithRandomKeys(string arr[100], int arrLength, enCharType CharType)
	{
		for (int i = 0; i < arrLength; i++)
			arr[i] = GenerateKey(CharType);
	}
	static void ShuffleArray(int arr[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
			Swap(arr[RandomNum(1, arrLength) - 1], arr[RandomNum(1, arrLength) - 1]);

	}

	static void ShuffleArray(string arr[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
			Swap(arr[RandomNum(1, arrLength) - 1], arr[RandomNum(1, arrLength) - 1]);
	}

	static string Tabs(short NumberOfTabs)
	{
		string t = "";

		for (int i = 1; i < NumberOfTabs; i++)
			t = t + "\t";

		return t;
	}

	static string EncryptText(string Text, short EncryptionKey)
	{
		for (int i = 0; i <= Text.length(); i++)
			Text[i] = char((int)Text[i] + EncryptionKey);

		return Text;
	}
	static string DecryptText(string Text, short DecryptionKey)
	{
		for (int i = 0; i <= Text.length(); i++)
			Text[i] = char((int)Text[i] - DecryptionKey);

		return Text;
	}
	static string NumberToText(int Number)
	{

		if (Number == 0)
		{
			return "";
		}

		if (Number >= 1 && Number <= 19)
		{
			string arr[] = { "", "One","Two","Three","Four","Five","Six","Seven",
							"Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
							"Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };

			return  arr[Number] + " ";
		}

		if (Number >= 20 && Number <= 99)
		{
			string arr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
			return  arr[Number / 10] + " " + NumberToText(Number % 10);
		}

		if (Number >= 100 && Number <= 199)
		{
			return  "One Hundred " + NumberToText(Number % 100);
		}

		if (Number >= 200 && Number <= 999)
		{
			return   NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
		}

		if (Number >= 1000 && Number <= 1999)
		{
			return  "One Thousand " + NumberToText(Number % 1000);
		}

		if (Number >= 2000 && Number <= 999999)
		{
			return   NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
		}

		if (Number >= 1000000 && Number <= 1999999)
		{
			return  "One Million " + NumberToText(Number % 1000000);
		}

		if (Number >= 2000000 && Number <= 999999999)
		{
			return   NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
		}

		if (Number >= 1000000000 && Number <= 1999999999)
		{
			return  "One Billion " + NumberToText(Number % 1000000000);
		}
		else
		{
			return   NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
		}


	}

	static void Swap(int& A, int& B)
	{
		int Temp;

		Temp = A;
		A = B;
		B = Temp;
	}
	static void Swap(double& A, double& B)
	{
		double Temp;

		Temp = A;
		A = B;
		B = Temp;
	}
	static void Swap(bool& A, bool& B)
	{
		bool Temp;

		Temp = A;
		A = B;
		B = Temp;
	}
	static void Swap(char& A, char& B)
	{
		char Temp;

		Temp = A;
		A = B;
		B = Temp;
	}
	static void Swap(string& A, string& B)
	{
		string Temp;

		Temp = A;
		A = B;
		B = Temp;
	}

	
	/*static void Swap(clsDate& A, clsDate& B)
	{
		clsDate::SwapDates(A, B);
	}*/

};

