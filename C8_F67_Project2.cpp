#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

const string Clients = "Clients.txt";
void PerformATMMenueOptins(short);
void Login();

struct stClient
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double Balance = 0;
};

stClient CurrentClient;

enum enATM
{
	enaQuickWithdraw = 1,
	enaNormalWithdarw = 2,
	enaDeposit = 3,
	enaCheckBalance = 4,
	enaLogout = 5
};

string ReadString(string message)
{
	string str = "";
	cout << message;
	getline(cin, str);
	return str;
}

vector<string> Spilt(string str, string delim = " ")
{
	vector<string> vec = {};
	int pos = 0;
	string word = "";
	while ((pos = str.find(delim)) != std::string::npos)
	{
		word = str.substr(0, pos);
		if (word != "")
			vec.push_back(word);
		str.erase(0, pos + delim.length());
	}
	if (str != "")
		vec.push_back(str);
	return vec;
}

stClient LineToStructure(string line)
{
	vector<string> vec = Spilt(line, "#//#");
	stClient Client;
	Client.AccountNumber = vec[0];
	Client.PinCode = vec[1];
	Client.Name = vec[2];
	Client.Phone = vec[3];
	Client.Balance = stod(vec[4]);
	return Client;
}

string StructureToLine(stClient Client, string delim = "#//#")
{
	string str = "";
	str += Client.AccountNumber + delim;
	str += Client.PinCode + delim;
	str += Client.Name + delim;
	str += Client.Phone + delim;
	str += to_string(Client.Balance);
	return str;
}

vector<stClient> LoadFileData(string fileName)
{
	vector<stClient> vecClinent {};
	stClient Client;
	fstream MyFile;
	string line = "";
	MyFile.open(fileName, ios::in);
	if (MyFile.is_open())
	{
		while (getline(MyFile, line))
		{
			Client = LineToStructure(line);
			vecClinent.push_back(Client);
		}
	}
	MyFile.close();
	return vecClinent;
}

bool IsValidAccountNumber(string fileName, string accountNumber)
{
	vector<stClient> vClients = LoadFileData(fileName);
	for (stClient Client : vClients)
	{
		if (Client.AccountNumber == accountNumber)
			return true;
	}
	return false;
}

stClient LoadClient(string fileName, string accountNumber)
{
	vector<stClient> vClients = LoadFileData(fileName);
	for (stClient& Client : vClients)
	{
		if (Client.AccountNumber == accountNumber)
			return Client;
	}
}

void ATMMenue()
{
	system("cls");
	cout << "=============================================\n";
	cout << "             ATM Menue Screen\n";
	cout << "=============================================\n";
	cout << "   [1] Quick Withdraw.\n";
	cout << "   [2] Normal Withdraw.\n";
	cout << "   [3] Deposit.\n";
	cout << "   [4] Check Balance.\n";
	cout << "   [5] Logout.\n";
	cout << "=============================================\n";
	PerformATMMenueOptins(stoi(ReadString("Choose what do you want to do [1 to 5] : ")));
}

void backATMMenue()
{
	cout << "\nPress any key to go back to ATM Menue...";
	system("pause>0");
	ATMMenue();
}

void SaveDateUpdated(string fileName)
{
	vector<stClient> vec = LoadFileData(fileName);
	for (stClient &i : vec)
	{
		if (i.AccountNumber == CurrentClient.AccountNumber)
			i.Balance = CurrentClient.Balance;
	}
	
	fstream MyFile;
	MyFile.open(fileName, ios::out);
	MyFile << "";
	MyFile.close();

	MyFile.open(fileName, ios::out);
	for (stClient& i : vec)
	{
		MyFile << StructureToLine(i) << "\n";
	}
	MyFile.close();
}

void Withdraw(double amount)
{
	if (::CurrentClient.Balance < amount)
		cout << "The amount exceeds your balance, make another choice.\n";
	else
	{
		::CurrentClient.Balance -= amount;
		cout << "Done Successfully.";
	}
}

void Deposit(double amount)
{
	if (amount > 0)
	{
		::CurrentClient.Balance += amount;
		cout << "Done Successfully.";
	}
	else
	{
		cout << "Invalid Amount.";
	}
}

void QuickWithdraw(short n)
{
	switch (n)
	{
	case 1:
		Withdraw(20);
		break;
	case 2:
		Withdraw(50);
		break;
	case 3:
		Withdraw(100);
		break;
	case 4:
		Withdraw(200);
		break;
	case 5:
		Withdraw(400);
		break;
	case 6:
		Withdraw(600);
		break;
	case 7:
		Withdraw(800);
		break;
	case 8:
		Withdraw(1000);
		break;
	}
}

void NormalWithdraw(int amount)
{
	if (amount % 5 == 0)
		Withdraw(amount);
	else
		cout << "The " << amount << " isn't multiple of 5's.";
}

void QuickWithdrawScreen()
{
	cout << "============================================\n";
	cout << "               Quick Withdraw\n";
	cout << "============================================\n";
	cout << "       [1] 20           [2] 50     \n";
	cout << "       [3] 100          [4] 200    \n";
	cout << "       [5] 400          [6] 600    \n";
	cout << "       [7] 800          [8] 1000   \n";
	cout << "       [9] Exit                    \n";
	cout << "=============================================\n";
	cout << "Your Balance is " << ::CurrentClient.Balance << "\n";
	QuickWithdraw(stoi(ReadString("Choose what to withdraw from [1] - [8]? ")));
	cout << "Your Balance become is " << ::CurrentClient.Balance << "\n";
}

void NormalWithdrawScreen()
{
	cout << "===========================================\n";
	cout << "             Normal Withdraw\n";
	cout << "===========================================\n";
	cout << "Your Balance is " << ::CurrentClient.Balance << "\n";
	NormalWithdraw(stoi(ReadString("Enter an amount multiple of 5's ? ")));
	cout << "Your Balance become is " << ::CurrentClient.Balance << "\n";
}

void DepositScreen()
{
	cout << "===========================================\n";
	cout << "                 Deposit\n";
	cout << "===========================================\n";
	cout << "Your Balance is " << ::CurrentClient.Balance << "\n";
	Deposit(stoi(ReadString("Enter a positve Deposit Amount ? ")));
	cout << "Your Balance become is " << ::CurrentClient.Balance << "\n";
}

void CheckBalanceScreen()
{
	cout << "===========================================\n";
	cout << "               Check Balance\n";
	cout << "===========================================\n";
	cout << "Your Balance is " << CurrentClient.Balance;
}

void PerformATMMenueOptins(short n)
{
	system("cls");
	switch (n)
	{
	case enATM::enaQuickWithdraw:
		QuickWithdrawScreen();
		SaveDateUpdated(Clients);
		backATMMenue();
		break;
	case enATM::enaNormalWithdarw:
		NormalWithdrawScreen();
		SaveDateUpdated(Clients);
		backATMMenue();
		break;
	case enATM::enaDeposit:
		DepositScreen();
		SaveDateUpdated(Clients);
		backATMMenue();
		break;
	case enATM::enaCheckBalance:
		CheckBalanceScreen();
		backATMMenue();
		break;
	case enATM::enaLogout:
		Login();
		break;
	defaulte:
		break;
	}
}

bool IsValidLogin(string accountNumber, string pinCode)
{
	stClient Client;
	if (IsValidAccountNumber(::Clients, accountNumber))
	{
		Client = LoadClient(::Clients, accountNumber);
		if (Client.PinCode == pinCode)
		{
			::CurrentClient = LoadClient(::Clients, accountNumber);
			return true;
		}
	}
	return false;
}

void Login()
{
	system("cls");
	cout << "________________________________\n";
	cout << "            Login\n";
	cout << "________________________________\n";
	string accountNumber = ReadString("Account Number: ");
	string password = ReadString("Pin Code: ");
	while (!IsValidLogin(accountNumber, password))
	{
		system("cls");
		cout << "______________________________________\n";
		cout << "               Login\n";
		cout << "______________________________________\n";
		cout << "Invalid Account Number / Pin Code!" << "\n";
		accountNumber = ReadString("Account Number: ");
		password = ReadString("Pin Code: ");
	}
	ATMMenue();
}

int main()
{
	Login();
	return 0;
}