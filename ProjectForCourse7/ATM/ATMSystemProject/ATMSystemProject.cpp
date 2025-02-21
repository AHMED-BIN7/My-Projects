#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

const string ClientsFile = "Clients.txt";
enum enAtmMainMenue { eQuickWithdraw = 1, eNormalWithdraw = 2, eDeposit = 3, eCheckBalance = 4, eLogout = 5 };
struct sClients
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double Balance;
};
static sClients CurrentClient;
void ATM();
void GoBackToMainMenue();
int CheckAmount();
void QuickWithdrawScreen();

string ConvertRecordToLine(sClients Clients, string delim = "#//#")
{
    string STR = Clients.AccountNumber + delim + Clients.PinCode + delim + 
        Clients.Name + delim + Clients.Phone + delim + to_string(Clients.Balance);

    return STR;
}
sClients ConvertLineToRecord(vector<string>vClients)
{
    sClients Clients;

    Clients.AccountNumber = vClients[0];
    Clients.PinCode = vClients[1];
    Clients.Name = vClients[2];
    Clients.Phone = vClients[3];
    Clients.Balance = stod(vClients[4]);

    return Clients;
}
vector<string>Split(string Line, string delim = "#//#")
{
    vector<string>vClients;
    short pos = 0;
    string sWord;

    while ((pos = Line.find(delim)) != std::string::npos){

        sWord = Line.substr(0, pos);

        if (sWord != " ")
            vClients.push_back(sWord);
        
        Line.erase(0, pos + delim.length());
    }

    if (Line != " ") 
        vClients.push_back(Line);
    
    return vClients;
}
vector<sClients> LoadDataFromFile1(string FileName)
{
    vector<sClients>vClients;
    sClients Client;
    string Line;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open()) {

        while (getline(MyFile,Line))
        {
            Client = ConvertLineToRecord(Split(Line));

            vClients.push_back(Client);
        }
        MyFile.close();
    }

    return vClients;
}
void LodaDataToFile(sClients Client)
{
    vector<sClients>vClient = LoadDataFromFile1(ClientsFile);

    fstream MyFile;
    MyFile.open(ClientsFile, ios::out);

    if (MyFile.is_open()) {

        for (sClients& C : vClient) {

            if (C.AccountNumber == CurrentClient.AccountNumber) 
                MyFile << ConvertRecordToLine(Client) << endl;
            else 
                MyFile << ConvertRecordToLine(C) << endl;
        }

        MyFile.close();
    }
}
double ReadPostiveNumber(string Message)
{
    double Number;

    do
    {
        cout << Message;
        cin >> Number;

    } while (Number < 0);

    return Number;
}
string ReadNumber(string Message)
{
    string Number;
    cout << Message;
    cin >> Number;

    return Number;
}
void LoginScreen()
{
    system("cls");
    cout << "-------------------------------------------------\n";
    cout << "\t\t Login Screen\n";
    cout << "-------------------------------------------------\n";
}
void Login()
{
    LoginScreen();
    vector<sClients> vClients = LoadDataFromFile1(ClientsFile);
    sClients Client;
    string AccoutNumber;
    string PinCode;

    do
    {
        AccoutNumber = ReadNumber("\nPlease Enter Accout Number : ");
        PinCode = ReadNumber("Please Enter PinCode : ");

        for (sClients& C : vClients) {

            if (C.AccountNumber == AccoutNumber && C.PinCode == PinCode) {

                CurrentClient = C;
                return;
            }
        }

        LoginScreen();
        cout << "Invlaid Accout Number/Password!";

    } while (Client.AccountNumber != AccoutNumber && Client.PinCode != PinCode);

 

}
int GetQuickWithdrawOption(short Choose) {

    switch (Choose)
    {
    case 1:
        return 20;
        break;
    case 2:
        return 50;
        break;
    case 3:
        return 100;
        break;
    case 4:
        return 200;
        break;
    case 5:
        return 400;
        break;
    case 6:
        return 600;
        break;
    case 7:
        return 800;
        break;
    case 8:
        return 1000;
        break;
    case 9:
        GoBackToMainMenue();
        break;
    }
}
void QuickWithdrawOptions(short Choose)
{
    int NumberToCheck = GetQuickWithdrawOption(Choose);

    while (NumberToCheck > CurrentClient.Balance)
    {
        cout << "\nThe Amount Exceeds Your Balance, Make Another Choice.\n";
        cout << "Press Any Key To Contunue... ";
        system("pause>0");
        QuickWithdrawScreen();
        return;
    }

    char Answor = ' ';
    cout << "\nAre You Sure You Want Perform This Transaction [Y/N] ? ";
    cin >> Answor;

    if (toupper(Answor) != 'Y')
        return;

    CurrentClient.Balance -= (double)NumberToCheck;
    LodaDataToFile(CurrentClient);
    cout << "\nDone Successfully. New Balance is : " << CurrentClient.Balance << endl << endl;
}
void QuickWithdrawScreen()
{
    system("cls");
    cout << "-------------------------------------------------\n";
    cout << "\t\tQuick Withdraw Screen\n";
    cout << "-------------------------------------------------\n";
    cout << "[1] 20\t\t[2] 50\n";
    cout << "[3] 100\t\t[4] 200\n";
    cout << "[5] 400\t\t[6] 600\n";
    cout << "[7] 800\t\t[8] 1000\n";
    cout << "[9] Exit\n";
    cout << "-------------------------------------------------\n";
    cout << "Your Balance is " << CurrentClient.Balance << endl;

    QuickWithdrawOptions(ReadPostiveNumber("Choose What To Withdraw From [1] To [8] ? "));
}
void NormalWithdraw()
{
    char Answor = ' ';
    int Amount = CheckAmount();

    while (Amount % 5 != 0)
    {
        cout << "\nEnter an Amount Multipple Of 5's ? ";
        cin >> Amount;
    }
    
    cout << "\nAre You Sure You Want Perform This Transaction [Y/N] ? ";
    cin >> Answor;

    if (toupper(Answor) == 'Y') {

        CurrentClient.Balance -= (double)Amount;
        LodaDataToFile(CurrentClient);
        cout << "\nDone Successfully. New Balance is : " << CurrentClient.Balance << endl << endl;
    }
}
void NormalWithdrawScreen()
{
    system("cls");
    cout << "-------------------------------------------------\n";
    cout << "\t\tNormal Withdraw Screen\n";
    cout << "-------------------------------------------------\n";
}
int CheckAmount()
{
    int Amount;
    cout << "\nEnter an Amount Multipple Of 5's ? ";
    cin >> Amount;

    while (Amount > CurrentClient.Balance) {

        cout << "\nThe Amount Exceeds Your Balance, Make Another Choice.\n";
        cout << "Press Any Key To Contunue... ";
        system("pause>0");
        NormalWithdrawScreen();
        cout << "\nEnter an Amount Multipple Of 5's ? ";
        cin >> Amount;
    }
    return Amount;
}
void Deposit()
{
    char Answor = ' ';
    int Amount = ReadPostiveNumber("\nEnter a Positive Deposit Ammount ? ");

    cout << "\nAre You Sure You Want Perform This Transaction [Y/N] ? ";
    cin >> Answor;

    if (toupper(Answor) == 'Y') {

        CurrentClient.Balance += (double)Amount;
        LodaDataToFile(CurrentClient);
        cout << "\nDone Successfully. New Balance is : " << CurrentClient.Balance << endl << endl;
    }

}
void DepositScreen()
{
    system("cls");
    cout << "-------------------------------------------------\n";
    cout << "\t\tDeposit Screen\n";
    cout << "-------------------------------------------------\n";
}
void CheckBalanceScreen()
{
    system("cls");
    cout << "-------------------------------------------------\n";
    cout << "\t\tChec kBalance Screen\n";
    cout << "-------------------------------------------------\n";
    cout << "\nYour Balancd is : " << CurrentClient.Balance << endl << endl;
}
void AtmMainMenue(enAtmMainMenue Option)
{
    switch (Option)
    {
    case eQuickWithdraw:
        QuickWithdrawScreen();
        GoBackToMainMenue();
        break;
    case eNormalWithdraw:
        NormalWithdrawScreen();
        NormalWithdraw();
        GoBackToMainMenue();
        break;
    case eDeposit:
        DepositScreen();
        Deposit();
        GoBackToMainMenue();
        break;
    case eCheckBalance:
        CheckBalanceScreen();
        GoBackToMainMenue();
        break;
    case eLogout:
        ATM();
        break;
    default:
        cout << "Wrong Number!";
        break;
    }
}
void AtmMainMenueScreen()
{
    system("cls");
    cout << "-------------------------------------------------\n";
    cout << "\t\t ATM Main Menue Screen\n";
    cout << "-------------------------------------------------\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Logout.\n";
    cout << "-------------------------------------------------\n";

    AtmMainMenue((enAtmMainMenue)ReadPostiveNumber("Choose What Do You Want To Do [1 To 5] ? "));
}
void GoBackToMainMenue()
{
    cout << "Press Any Key To Go Back To Main Menue...";
    system("pause>0");
    AtmMainMenueScreen();
}
void ATM()
{
    Login();
    AtmMainMenueScreen();
}

int main()
{
    ATM();

    return 0;
}

