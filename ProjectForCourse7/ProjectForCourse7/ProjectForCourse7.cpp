#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

void Bank();
void Start();
void GoBackToManageUsersMenue();
void GoBackToMainMenue();
void GoBackToTransactionsOptions();
void ManageUsersMenue();
void MessageForPermission();
const string ClientsFile = "Clients.txt";
const string UsersFile = "Users.txt";
struct sClients
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};
enum enMenue 
{ 
    eShowClientList = 1, eAddNewClient = 2, eDeleteClients = 3, 
    eUpdateClientsInfo = 4, eFindClient = 5, eTransctions = 6, ManageUsers = 7,Logout=8 
};
enum enTransctions { eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eMainMenue };
enum enManageUsersOptions {eListUsers=1,eAddUser=2,eDeleteUser=3,eUpdateUser=4,eFindUser=5,MainMenue=6};
enum enPermissions 
{ 
    pShowClientList = 1, pAddNewClient = 2, pDeleteClients = 4,
    pUpdateClientsInfo = 8, pFindClient = 16, pTransctions = 32, pManageUsers = 64
};
bool CheckAccessPermissions(enPermissions);

sClients ReadClientInfo()
{
    sClients Client;

    cout << "Enter Account Number : ";
    getline(cin >> ws, Client.AccountNumber);
    cout << "Enter Pin Code : ";
    getline(cin, Client.PinCode);
    cout << "Enter Name : ";
    getline(cin, Client.Name);
    cout << "Enter Phone : ";
    getline(cin, Client.Phone);
    cout << "Enter Account Balance : ";
    cin >> Client.AccountBalance;

    return Client;
}
string ConvertRecordToLine(sClients Client, string Delim = "#//#")
{
    string Line;

    Line = Client.AccountNumber + Delim
        + Client.PinCode + Delim
        + Client.Name + Delim
        + Client.Phone + Delim
        + to_string(Client.AccountBalance);

    return Line;
}
vector <string> Split(string S1, string Delim = "#//#")
{
    vector <string> vClient;
    short pos = 0;
    string Word;

    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        Word = S1.substr(0, pos);
        if (Word != " ")
        {
            vClient.push_back(Word);
        }
        S1.erase(0, pos + Delim.length());
    }
    if (S1 != " ")
    {
        vClient.push_back(S1);
    }

    return vClient;
}
sClients ConvertLineToRecord(vector <string> vClinetLine)
{
    sClients Client;

    Client.AccountNumber = vClinetLine[0];
    Client.PinCode = vClinetLine[1];
    Client.Name = vClinetLine[2];
    Client.Phone = vClinetLine[3];
    Client.AccountBalance = stod(vClinetLine[4]);

    return Client;

}
vector <sClients> LodaClientsDataFromFile(string FileName)
{
    sClients Client;
    vector <sClients> vClient;

    fstream Myfile;
    Myfile.open(FileName, ios::in);


    if (Myfile.is_open()) {

        string Line;

        while (getline(Myfile, Line)) {

            Client = ConvertLineToRecord(Split(Line));

            vClient.push_back(Client);
        }
        Myfile.close();
    }
    return vClient;
}
bool ChackAccountNumber(string& AccountNumber)
{
    vector <sClients> vClient = LodaClientsDataFromFile(ClientsFile);


    cout << "Enter Account Number : ";
    cin >> AccountNumber;

    for (sClients& Client : vClient) {

        if (Client.AccountNumber == AccountNumber)
        {
            return true;
        }
    }
    return false;
}
void ShowClientInfo(sClients Client)
{
    cout << "\nThe Follwing Are The Client Detalis :\n\n ";
    cout << "------------------------------------------\n";
    cout << "Account Number : " << Client.AccountNumber << "\n";
    cout << "Pin Code : " << Client.PinCode << "\n";
    cout << "Name : " << Client.Name << "\n";
    cout << "Phone : " << Client.Phone << "\n";
    cout << "Account Balance : " << Client.AccountBalance << endl;
    cout << "------------------------------------------\n";
}
bool FindClientByAccountNumber()
{
    if (!CheckAccessPermissions(enPermissions::pFindClient)) {
        MessageForPermission();
        return 0;
    }

    vector <sClients> vClient = LodaClientsDataFromFile(ClientsFile);

    string AccountNumber;
    cout << "Enter Account Number : ";
    cin >> AccountNumber;

    for (sClients& Client : vClient) {

        if (Client.AccountNumber == AccountNumber)
        {
            ShowClientInfo(Client);
            return true;
        }

    }
    cout << "Client With Account Number " << AccountNumber << " is Not Found!." << endl;
    return false;
}
sClients ReadForNewClientInfo(string AccountNumber)
{
    sClients Client;

    Client.AccountNumber = AccountNumber;
    cout << "Enter Pin Code : ";
    getline(cin >> ws, Client.PinCode);
    cout << "Enter Name : ";
    getline(cin, Client.Name);
    cout << "Enter Phone : ";
    getline(cin, Client.Phone);
    cout << "Enter Account Balance : ";
    cin >> Client.AccountBalance;

    return Client;
}
sClients ReadForUpdateClientInfo(string AccountNumber, sClients& Client)
{
    Client.AccountNumber = AccountNumber;
    cout << "Enter Pin Code : ";
    getline(cin >> ws, Client.PinCode);
    cout << "Enter Name : ";
    getline(cin, Client.Name);
    cout << "Enter Phone : ";
    getline(cin, Client.Phone);
    cout << "Enter Account Balance : ";
    cin >> Client.AccountBalance;

    return Client;
}
void AddClient(string AccountNumber)
{
    string Line;
    fstream Myfile;
    Myfile.open(ClientsFile, ios::out | ios::app);

    if (Myfile.is_open()) {

        sClients Client = ReadForNewClientInfo(AccountNumber);
        Line = ConvertRecordToLine(Client);

        Myfile << Line << endl;

        Myfile.close();
    }
}
void AddNowClient()
{
    if (!CheckAccessPermissions(enPermissions::pAddNewClient)) {
        MessageForPermission();
        return;
    }

    char Answer = 'Y';
    string AccountNumber;

    while (toupper(Answer) == 'Y') {

        while (ChackAccountNumber(AccountNumber)) {

            cout << "Client With [ " << AccountNumber << " ] already exists, ";
        }

        AddClient(AccountNumber);
        cout << "Client Added Successfuly, Do you Want To Add More Y/N ? ";
        cin >> Answer;
    }
}
bool MarkForDelete(string AccountNumber, vector <sClients> vClient, sClients& Client)
{
    if (Client.AccountNumber == AccountNumber) {

        Client.MarkForDelete = true;
        return true;
    }
    return false;
}
void TransferClientToFileByOutMode(vector <sClients> vClient, sClients Client)
{
    fstream Myfile;
    Myfile.open(ClientsFile, ios::out);

    if (Myfile.is_open()) {

        for (sClients& C : vClient) {

            if (C.MarkForDelete == false) {

                Myfile << ConvertRecordToLine(C) << endl;
            }
        }
        Myfile.close();
    }
}
string ReadAccountNumber()
{
    string AccountNumber;
    cout << "Enter Account Number : ";
    cin >> AccountNumber;

    return AccountNumber;
}
bool DeleteClient()
{
    if (!CheckAccessPermissions(enPermissions::pDeleteClients)) {
        MessageForPermission();
        return 0;
    }

    char Answer = 'n';
    string AccountNumber = ReadAccountNumber();
    vector <sClients> vClient = LodaClientsDataFromFile(ClientsFile);

    for (sClients& C : vClient)
    {
        if (C.AccountNumber == AccountNumber) {

            ShowClientInfo(C);
            MarkForDelete(AccountNumber, vClient, C);

            cout << "\nAre You Sure You Want Delete This Client Y/N ? ";
            cin >> Answer;
            cout << "\n";

            if (toupper(Answer) == 'Y') {

                TransferClientToFileByOutMode(vClient, C);
                cout << "\nClient Deleted Successfully." << endl;
                return true;
            }
        }
    }
    cout << "Client With Account Number " << AccountNumber << " is Not Found!." << endl;
    return false;
}
bool UpdateClientInfo()
{
    if (!CheckAccessPermissions(enPermissions::pUpdateClientsInfo)) {
        MessageForPermission();
        return 0;
    }

    char Answer = 'n';
    string AccountNumber = ReadAccountNumber();
    sClients Client;
    vector<sClients>vClient = LodaClientsDataFromFile(ClientsFile);

    for (sClients& C : vClient) {

        if (C.AccountNumber == AccountNumber) {

            ShowClientInfo(C);
            cout << "\nAre You Sure You Want Delete This Client Y/N ? ";
            cin >> Answer;
            cout << "\n";

            if (toupper(Answer) == 'Y') {

                C = ReadForUpdateClientInfo(AccountNumber, C);
                TransferClientToFileByOutMode(vClient, C);
                cout << "\nClient Updated Successfully.\n";
                return true;
            }
        }
    }
    cout << "Client With Account Number " << AccountNumber << " is Not Found!." << endl;
    return false;
}
void DepositScren()
{
    system("cls");
    cout << "-------------------------------------------\n";
    cout << "\t\tDeposit Scren";
    cout << "\n-------------------------------------------\n\n";
}
void WithdrawScren()
{
    system("cls");
    cout << "-------------------------------------------\n";
    cout << "\t\tWithdraw Scren";
    cout << "\n-------------------------------------------\n\n";
}
void TotalBalancesScren()
{
    system("cls");
    cout << "-------------------------------------------\n";
    cout << "\t   Total Balances Scren";
    cout << "\n-------------------------------------------\n\n";
}
bool DepositProcess(string AccountNumber, sClients& Client)
{
    char Answer = ' ';
    int NumForDeposit;

    cout << "\nPlease Enter Deposit Amount ? ";
    cin >> NumForDeposit;

    cout << "\nAre You Sure You Want Perform This Transction Y/N ? ";
    cin >> Answer;

    if (Client.AccountNumber == AccountNumber) {

        if (toupper(Answer) == 'Y') {

            Client.AccountBalance += NumForDeposit;
            return true;
        }
    }
    return false;
}
bool Deposit()
{
    string AccountNumber = ReadAccountNumber();
    vector<sClients>vClient = LodaClientsDataFromFile(ClientsFile);

    for (sClients& C : vClient) {

        if (C.AccountNumber == AccountNumber) {

            ShowClientInfo(C);
            DepositProcess(AccountNumber, C);
            TransferClientToFileByOutMode(vClient, C);
            cout << "\n\nDone Successfully New Balance is " << C.AccountBalance << endl;
            return true;

        }
    }
    cout << "Client With Account Number " << AccountNumber << " is Not Found!." << endl;
    return false;
}
bool WithdrawProcess(string AccountNumber, sClients& Client)
{
    char Answer = ' ';
    int NumForWithdraw;

    do
    {
        cout << "\nPlease Enter Withdraw Amount ? ";
        cin >> NumForWithdraw;

        if (NumForWithdraw > Client.AccountBalance) {

            cout << "Amout Exceeds The Balance, you can withdraw up to : " << Client.AccountBalance << endl;
        }

    } while (NumForWithdraw > Client.AccountBalance);

    cout << "\nAre You Sure You Want Perform This Transction Y/N ? ";
    cin >> Answer;

    if (Client.AccountNumber == AccountNumber) {

        if (toupper(Answer) == 'Y') {

            Client.AccountBalance -= NumForWithdraw;
            return true;
        }
    }

    return false;
}
bool Withdraw()
{
    string AccountNumber = ReadAccountNumber();
    vector<sClients>vClient = LodaClientsDataFromFile(ClientsFile);

    for (sClients& C : vClient) {

        if (C.AccountNumber == AccountNumber) {

            ShowClientInfo(C);
            WithdrawProcess(AccountNumber, C);
            TransferClientToFileByOutMode(vClient, C);
            cout << "\n\nDone Successfully New Balance is " << C.AccountBalance << endl;
            return true;

        }
    }
    cout << "Client With Account Number " << AccountNumber << " is Not Found!." << endl;
    return false;
}
double TotalBalancesProcess(vector<sClients>vClient)
{
    double Total = 0;

    for (sClients& C : vClient) {

        Total += C.AccountBalance;
    }

    return Total;
}
void BalancesFrame(sClients Client)
{
    cout << '|' << left << setw(15) << Client.AccountNumber;
    cout << '|' << left << setw(40) << Client.Name;
    cout << '|' << left << setw(12) << Client.AccountBalance;

    cout << endl;
}
void ShowBalancesList()
{
    vector<sClients> vClient = LodaClientsDataFromFile(ClientsFile);

    for (sClients Client : vClient)
    {
        BalancesFrame(Client);
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}
void TotalBalances()
{
    system("cls");
    vector <sClients> vClient = LodaClientsDataFromFile(ClientsFile);
    cout << "\n\t\t\t\tBalancs List (" << vClient.size() << ") Client(s).\n";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << '|' << left << setw(15) << " AccountNumber"
        << '|' << left << setw(40) << " Name"
        << '|' << left << setw(12) << " AccountBalance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    ShowBalancesList();

    cout << "\n\t\t\tTotal Balances = " << TotalBalancesProcess(vClient) << endl << endl;

}
bool TransactionsOptios()
{
    short NumForTransactions;

    do
    {

        cout << "Choose What Do You Want To Do [1,4] ? ";
        cin >> NumForTransactions;

        switch (NumForTransactions)
        {
        case enTransctions::eDeposit:
            DepositScren();
            Deposit();
            GoBackToTransactionsOptions();
            break;
        case enTransctions::eWithdraw:
            WithdrawScren();
            Withdraw();
            GoBackToTransactionsOptions();
            break;
        case enTransctions::eTotalBalances:
            TotalBalances();
            GoBackToTransactionsOptions();
            break;
        case enTransctions::eMainMenue:
            Start();
        default:
            cout << "Number Worng!, ";
            break;
        }

    } while (NumForTransactions < 1 || NumForTransactions > 4);

    return true;
}
void TransactionsScren()
{
    system("cls");
    cout << "-------------------------------------------\n";
    cout << "\t    Transctions Scren";
    cout << "\n-------------------------------------------\n";
    cout << "\t [1] Deposit.\n";
    cout << "\t [2] Withdraw.\n";
    cout << "\t [3] Total Balances.\n";
    cout << "\t [4] Main Menue.\n";
    cout << "-------------------------------------------" << endl;
}
void Transactions()
{
    if (!CheckAccessPermissions(enPermissions::pTransctions)) {
        MessageForPermission();
        return;
    }

    TransactionsScren();
    TransactionsOptios();
}
void GoBackToTransactionsOptions()
{
    cout << "\nPress any key to go back to Transctions Menue...";
    system("pause>0");
    Transactions();

}
void ListFrame()
{
    vector <sClients> vClient = LodaClientsDataFromFile(ClientsFile);

    cout << "\n\t\t\t\tClients List (" << vClient.size() << ") Client(s).\n";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << '|' << left << setw(15) << " AccountNumber"
        << '|' << left << setw(10) << " PinCode"
        << '|' << left << setw(40) << " Name"
        << '|' << left << setw(12) << " Phone"
        << '|' << left << setw(12) << " AccountBalance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}
void ClientsFrame(sClients Client)
{
    cout << '|' << left << setw(15) << Client.AccountNumber;
    cout << '|' << left << setw(10) << Client.PinCode;
    cout << '|' << left << setw(40) << Client.Name;
    cout << '|' << left << setw(12) << Client.Phone;
    cout << '|' << left << setw(12) << Client.AccountBalance;

    cout << endl;
}
void ShowClientsList()
{
    if (!CheckAccessPermissions(enPermissions::pShowClientList)) {
        MessageForPermission();
        return;
    }
    
    system("cls");
    vector<sClients> vClient = LodaClientsDataFromFile(ClientsFile);
    ListFrame();

    for (sClients Client : vClient)
    {
        ClientsFrame(Client);
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}
void DeleteScren()
{
    system("cls");
    cout << "-------------------------------------------\n";
    cout << "\t\tDelete Scren";
    cout << "\n-------------------------------------------\n\n";
}
void AddNowClientScren()
{
    system("cls");
    cout << "-------------------------------------------\n";
    cout << "\t  Add Now Client Scren";
    cout << "\n-------------------------------------------\n\n";
}
void FindClientScren()
{
    system("cls");
    cout << "-------------------------------------------\n";
    cout << "\t     Find Client Scren";
    cout << "\n-------------------------------------------\n\n";
}
void UpdateClientInfoScren()
{
    system("cls");
    cout << "-------------------------------------------\n";
    cout << "\tUpdate Client Info Scren";
    cout << "\n-------------------------------------------\n\n";
}

struct sUsers
{
    string Username;
    string Password;
    short Permissions;
    bool MarkUserForDelete = false;
};
sUsers CurrentUser;

sUsers ConvertUserLineToRecord(vector<string>vUser)
{
    sUsers Users;

    Users.Username = vUser[0];
    Users.Password = vUser[1];
    Users.Permissions = stoi(vUser[2]);

    return Users;

}
string ConvertRecordToLine(sUsers Users,string delim = "#//#")
{
    string Line = Users.Username + delim + 
        Users.Password + delim + 
        to_string(Users.Permissions);

    return Line;
}
vector<sUsers> LodaUsersDataFromFile(string FileName)
{
    sUsers Users;
    vector<sUsers>vUsers;

    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open()) {
        
        string Line;

        while (getline(MyFile,Line))
        {
            Users = ConvertUserLineToRecord(Split(Line));
            vUsers.push_back(Users);
        }
        MyFile.close();
    }

    return vUsers;
}
string ReadUserNameOrPassword(string Messege)
{
    string UserNameOrPassword;
    cout << Messege;
    cin >> UserNameOrPassword;

    return UserNameOrPassword;

}
bool CheckUsername(string Username)
{
    vector <sUsers> vUsers = LodaUsersDataFromFile(UsersFile);

    for (sUsers& Users : vUsers) {

        if (Users.Username == Username) {

            return true;
        }
    }
    return false;

}
bool CheckPassword(string Password)
{
    vector <sUsers> vUsers = LodaUsersDataFromFile(UsersFile);

    for (sUsers& Users : vUsers) {

        if (Users.Password == Password) {

            return true;
        }
    }
    return false;

}
short ReadPermissionsToSet()
{
    char Answor = 'n';
    short Permissions = 0;

    cout << "\nShow Client List [Y/N] ? ";
    cin >> Answor;
    if (toupper(Answor) == 'Y') {
        Permissions += enPermissions::pShowClientList;
    }
    cout << "\nAdd New Client [Y/N] ? ";
    cin >> Answor;
    if (toupper(Answor) == 'Y') {
        Permissions += enPermissions::pAddNewClient;
    }
    cout << "\nDelete Client [Y/N] ? ";
    cin >> Answor;
    if (toupper(Answor) == 'Y') {
        Permissions += enPermissions::pDeleteClients;
    }
    cout << "\nUpdate Clients Info [Y/N] ? ";
    cin >> Answor;
    if (toupper(Answor) == 'Y') {
        Permissions += enPermissions::pUpdateClientsInfo;
    }
    cout << "\nFind Client [Y/N] ? ";
    cin >> Answor;
    if (toupper(Answor) == 'Y') {
        Permissions += enPermissions::pFindClient;
    }
    cout << "\nTransctions [Y/N] ? ";
    cin >> Answor;
    if (toupper(Answor) == 'Y') {
        Permissions += enPermissions::pTransctions;
    }
    cout << "\nManageUsers [Y/N] ? ";
    cin >> Answor;
    if (toupper(Answor) == 'Y') {
        Permissions += enPermissions::pManageUsers;
    }

    return Permissions;
}
void MessageForPermission()
{
    system("cls");
    cout << "-------------------------------------\n";
    cout << "Access Denied,\nYou Don't Have";
    cout << "Permissin To Do Thie, \nPlease Conact Your Admin.";
    cout << "\n-------------------------------------\n\n";
}
bool CheckAccessPermissions(enPermissions Permissions)
{
    if (CurrentUser.Permissions == -1) {
        return true;
    }
    return ((CurrentUser.Permissions & Permissions) == Permissions) ? true : false;
}
string ReadUsername()
{
    string Username;
    cout << "Please Enter Username : ";
    cin >> Username;

    return Username;
}
void ShowOneUserInfo(sUsers User)
{
    cout << "\n\nThe Following Are The User Details:\n";
    cout << "----------------------------------\n";
    cout << "Usernamw   : " << User.Username << endl;
    cout << "Password   : " << User.Password << endl;
    cout << "Permissions : " << User.Permissions << endl;
    cout << "----------------------------------\n";
}
sUsers ReadNewUserInfo()
{
    char Answer = ' ';
    sUsers Users;

    cout << "\nPlease Enter Usernaem : ";
    getline(cin >> ws, Users.Username);

    while (CheckUsername(Users.Username)) {

        cout << "Username With [ " << Users.Username << " ] already exists, ";
        cout << "Please Enter Another Usernaem : ";
        getline(cin >> ws, Users.Username);
    }

    cout << "Please Enter Password : ";
    getline(cin, Users.Password);

    cout << "\nDo You Want To Give Full Access [Y/N] ? ";
    cin >> Answer;

    if (toupper(Answer) == 'N') {

        Users.Permissions = ReadPermissionsToSet();
    }
    else {
        Users.Permissions = -1;
    }
    
    
    return Users;
}
void AddNewUserToFile()
{
    string Line;
    fstream MyFile;
    MyFile.open(UsersFile, ios::out | ios::app);

    if (MyFile.is_open()) {

        Line = ConvertRecordToLine(ReadNewUserInfo());

        MyFile << Line << endl;

        MyFile.close();
    }

}
void AddNewUser()
{
    char Answer = ' ';
   
    do
    {
        AddNewUserToFile();
        cout << "\nUser Added Successfully, Do You Want To Add More Users [Y/N] ? ";
        cin >> Answer;

    } while (toupper(Answer) == 'Y');
}
bool MarkUserForDelete(sUsers &U,string Username)
{
    if (U.Username == Username) {

        U.MarkUserForDelete = true;
        return true;
    }
    return false;
}
bool DeletingUser(vector<sUsers>vUsers)
{
    string Line;
    fstream MyFile;
    MyFile.open(UsersFile, ios::out);

    if (MyFile.is_open()) {

        for (sUsers &U : vUsers) {

            if (U.MarkUserForDelete == false) {

                Line = ConvertRecordToLine(U);

                MyFile << Line << endl;
            }
        }
        MyFile.close();
    }
    return true;
}
bool DeleteUser()
{
    string Username = ReadUsername();
    char Answer = 'n';
    vector<sUsers>vUsers = LodaUsersDataFromFile(UsersFile);

    if (Username == "Admin") {

        cout << "\nYou Cann't Delete The Admin!" << endl;
        return false;
    }

    for (sUsers &U : vUsers) {
        
        if (U.Username == Username) {

           ShowOneUserInfo(U);
           cout << "\n\nAre You Sure You Want Delete This User [" << Username << "]  [Y/N] ? ";
           cin >> Answer;
           if (toupper(Answer) == 'Y') {

               MarkUserForDelete(U, Username);
               DeletingUser(vUsers);
               cout << "\n\nDeleted Successfully.\n";
               return true;
           }
        }
    }
    cout << "Username With [ " << Username << " ] is Not Found!\n";
    return false;
}
sUsers ReadUserInfoForUpdateUser(sUsers &User,string Username)
{
    char Answer = ' ';

    User.Username = Username;
    cout << "\nPlease Enter Password : ";
    cin >> User.Password;

    cout << "\nDo You Want To Give Full Access [Y/N] ? ";
    cin >> Answer;

    if (toupper(Answer) == 'N') {

        User.Permissions = ReadPermissionsToSet();
    }
    else {
        User.Permissions = -1;
    }

    return User;
}
bool UpdateUser()
{
    char Answor = 'n';
    string Username = ReadUsername();
    vector<sUsers>vUsers = LodaUsersDataFromFile(UsersFile);

    for (sUsers& U : vUsers) {


        if (U.Username == Username) {

            ShowOneUserInfo(U);
            cout << "\n\nAre You Sure You Want Updare This User [" << Username << "]  [Y/N] ? ";
            cin >> Answor;

            if (toupper(Answor) == 'Y') {

                ReadUserInfoForUpdateUser(U, Username);
                DeletingUser(vUsers);
                cout << "\nUser Updated Successfully.\n";
                return true;
            }
        }
    }
    cout << "Username With [ " << Username << " ] is Not Found\n";
    return false;
}
bool FindUser()
{
    vector<sUsers>vUsers = LodaUsersDataFromFile(UsersFile);
    string User = ReadUsername();

    for (sUsers& U : vUsers) {

        if (U.Username == User) {

            ShowOneUserInfo(U);
            return true;
        }
    }
    cout << "\nUsername With [ " << User << " ] is Not Found!\n";
    return false;
}
void ShowUserInfo(vector<sUsers>vUsers)
{
    for (sUsers Users : vUsers) {

        cout << '|' << left << setw(15) << Users.Username;
        cout << '|' << left << setw(10) << Users.Password;
        cout << '|' << left << setw(40) << Users.Permissions;

        cout << endl;
    }
}
void ShowListUsers()
{
    system("cls");
    vector<sUsers>vUsers = LodaUsersDataFromFile(UsersFile);

        cout << "\n\t\t\t\tUsers List (" << vUsers.size() << ") User(s).\n";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << '|' << left << setw(15) << " User Name"
         << '|' << left << setw(10) << " Password"
         << '|' << left << setw(40) << " Permissions";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    ShowUserInfo(vUsers);

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}
void AddUserScren()
{
    system("cls");
    cout << "-------------------------------------------\n";
    cout << "\t\tAdd User Scren";
    cout << "\n-------------------------------------------\n";
    cout << "Adding New User:\n\n";
}
void DeleteUserScren()
{
    system("cls");
    cout << "-------------------------------------------\n";
    cout << "\t\tDelete User Scren";
    cout << "\n-------------------------------------------\n";
    cout << "Deleting User:\n\n";
}
void UpdateUserScren()
{
    system("cls");
    cout << "-------------------------------------------\n";
    cout << "\t\tUpdate User Scren";
    cout << "\n-------------------------------------------\n";
    cout << "Updating User:\n\n";
}
void FindUserScren()
{
    system("cls");
    cout << "-------------------------------------------\n";
    cout << "\t\tFind User Scren";
    cout << "\n-------------------------------------------\n";
    cout << "Finding User:\n\n";
}
void GoBackToManageUsersMenue()
{
    cout << "\n\nPress any key to go to Manage Users Menue .....";
    system("pause>0");
    ManageUsersMenue();
}
void Menue()
{
    system("cls");
    cout << "--------------------------------------------------------\n";
    cout << "\t\t  Main Menue Scren\n";
    cout << "--------------------------------------------------------\n";
    cout << "\t [1] Show Client List.\n";
    cout << "\t [2] Add New Client.\n";
    cout << "\t [3] Delete Client.\n";
    cout << "\t [4] Update Client Info.\n";
    cout << "\t [5] Find Client.\n";
    cout << "\t [6] Transactions.\n";
    cout << "\t [7] Manage Users.\n";
    cout << "\t [8] Logout.\n";
    cout << "--------------------------------------------------------" << endl;
}
void Start()
{
    Menue();
    short NumberForMenue;

    do
    {
        cout << "Choose What Do You Want To Do [1,8] ? ";
        cin >> NumberForMenue;
    
        switch (NumberForMenue)
        {
            case enMenue::eShowClientList:
                    ShowClientsList();
                    GoBackToMainMenue();
                    break;
            case enMenue::eAddNewClient:
                    AddNowClientScren();
                    AddNowClient();
                    GoBackToMainMenue();
                    break;
            case enMenue::eDeleteClients:
                    DeleteScren();
                    DeleteClient();
                    GoBackToMainMenue();
                    break;
            case enMenue::eUpdateClientsInfo:
                    UpdateClientInfoScren();
                    UpdateClientInfo();
                    GoBackToMainMenue();
                    break;
            case enMenue::eFindClient:
                    FindClientScren();
                    FindClientByAccountNumber();
                    GoBackToMainMenue();
                    break;
            case enMenue::eTransctions:
                    Transactions();
                    GoBackToMainMenue();
                    break;
            case enMenue::ManageUsers:
                    ManageUsersMenue(); 
                    GoBackToMainMenue();
                    break;
            case enMenue::Logout:
                Bank();
            default:
                cout << "Number Worng!, ";
                break;
        }
    
    } while (NumberForMenue > 7 || NumberForMenue < 1);
}
void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go to Manage Users Menue .....";
    system("pause>0");
    Start();
}
bool ManageUsersOptions()
{
    short NumberForOptions;
    cout << "Cho0se What Do You Want To Do [ 1 To 6 ] ? ";
    cin >> NumberForOptions;

    switch (NumberForOptions)
    {
    case enManageUsersOptions::eListUsers:
        ShowListUsers();
        GoBackToManageUsersMenue();
        break;
    case enManageUsersOptions::eAddUser:
        AddUserScren();
        AddNewUser();
        GoBackToManageUsersMenue();
        break;
    case enManageUsersOptions::eDeleteUser:
        DeleteUserScren();
        DeleteUser();
        GoBackToManageUsersMenue();
        break;
    case enManageUsersOptions::eUpdateUser:
        UpdateUserScren();
        UpdateUser();
        GoBackToManageUsersMenue();
        break;
    case enManageUsersOptions::eFindUser:
        FindUserScren();
        FindUser();
        GoBackToManageUsersMenue();
        break;
    case enManageUsersOptions::MainMenue:
        Start();
    }
    return true;
}
void ManageUsersMenue()
{
    if (!CheckAccessPermissions(enPermissions::pManageUsers)) {
        MessageForPermission();
        return;
    }

    system("cls");
    cout << "--------------------------------------------------------\n";
    cout << "\t\t  Manage Users Menue Scren\n";
    cout << "--------------------------------------------------------\n";
    cout << "\t [1] List Users.\n";
    cout << "\t [2] Add New User.\n";
    cout << "\t [3] Delete User.\n";
    cout << "\t [4] Update User.\n";
    cout << "\t [5] Find User.\n";
    cout << "\t [6] Main Menue.\n";
    cout << "--------------------------------------------------------" << endl;

    ManageUsersOptions();
}
void LohinScren()
{
    system("cls");
    cout << "-------------------------------------------\n";
    cout << "\t\tLogin Scren";
    cout << "\n-------------------------------------------\n\n";
}
bool Login()
{
    LohinScren();

    string Username;
    string Password;
    sUsers User;
    vector <sUsers> vUsers = LodaUsersDataFromFile(UsersFile);

    do
    {
        Username = ReadUserNameOrPassword("Please Enter Username : ");
        Password = ReadUserNameOrPassword("Please Enter Password : ");

        for (sUsers& U : vUsers) {

            if (U.Password == Password && U.Username == Username) {

                CurrentUser = U;
                return true;
            }
        }

        system("cls");
        LohinScren();
        cout << "Invlaide Username/Password" << endl;

    } while (User.Password != Password && User.Username != Username);
}
void Bank()
{
    Login();
    Start();
}

int main()
{
    Bank();

    return 0;
}
