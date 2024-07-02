#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include<iomanip>

using namespace std;

const string ClientsFileName = "ClintData.txt";

struct sClientData
{
    string AccountNumber = "";
    string PinCode = "";
    string Name = "";
    string Phone = "";
    double AccountBalance = 0.0;
};

string Taps(short Number)
{
    string T = "";
    while (Number--)
    {
        T += "\t";
    }
    return T;
}

string ReadString(string messag)
{
    string S;
    cout << messag;
    getline(cin >> ws, S);
    return S;
}

int ReadPositeveNumber(string messag)
{
    int Number;
    cout << messag;
    cin >> Number;
    while (Number < 0)
    {
        cout << "\n\nRoung Please entur PositeveNumber:\n";
        cin >> Number;
    }
    return Number;
}

double ReadPositeveNumberDouble(string messag)
{
    double Number;
    cout << messag;
    cin >> Number;
    while (Number < 0)
    {
        cout << "\n\nRoung Please entur PositeveNumber:\n";
        cin >> Number;
    }
    return Number;
}

bool CheckAccountNumberIsFound(vector<sClientData>& vClients, string Account)
{
    for (sClientData& ClientData : vClients)
    {
        if (ClientData.AccountNumber == Account)
        {
            return true;
        }
    }
    return false;
}
sClientData ReadClientData(vector<sClientData>& vClients)
{
    sClientData ClientData;

    ClientData.AccountNumber = ReadString("Enter Account Number ? ");
    while (CheckAccountNumberIsFound(vClients, ClientData.AccountNumber))
    {
        cout << "\nClient With [" << ClientData.AccountNumber << "] alrede exists, Enter another Account Number?";
        ClientData.AccountNumber = ReadString("Enter Account Number ? ");
    }
    ClientData.PinCode = ReadString("Enter Pin Code ? ");
    ClientData.Name = ReadString("Enter Name ? ");
    ClientData.Phone = ReadString("Enter Phone ? ");
    ClientData.AccountBalance = ReadPositeveNumberDouble("Enter AccountBalance ? ");

    return ClientData;
}

string ClientDataRecordToOneLine(sClientData ClientData, string Seperator = "#//#")
{

    string StClientRecord = "";
    StClientRecord += ClientData.AccountNumber + Seperator;
    StClientRecord += ClientData.PinCode + Seperator;
    StClientRecord += ClientData.Name + Seperator;
    StClientRecord += ClientData.Phone + Seperator;
    StClientRecord += (to_string(ClientData.AccountBalance));

    return StClientRecord;

}

void AddDataLineToFile(string FileName, string stDataline)
{
    fstream MyFile;

    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << stDataline << endl;
        MyFile.close();
    }

}

void AddNewClient(vector<sClientData>& vClients)
{

    sClientData Client = ReadClientData(vClients);


    AddDataLineToFile(ClientsFileName, ClientDataRecordToOneLine(Client));
}

void AddClients(vector<sClientData>& vClients)
{
    char AddMore = 'y';
    while (AddMore == 'y' || AddMore == 'Y') {

        

        cout << "Adding New Client:\n\n";
        AddNewClient(vClients);
        cout << "\n\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin >> AddMore;
    }
}

vector<string> SplitString(string S, string dump = "#//#")
{
    string Word;
    int pos;
    vector<string>vString;
    while ((pos = S.find(dump)) != std::string::npos)
    {
        Word = S.substr(0, pos);
        if (Word != "")
        {
            vString.push_back(Word);
        }
        S.erase(0, pos + dump.length());
    }
    if (S != "")
        vString.push_back(S);

    return vString;
}

sClientData ConvertLineDataToRecord(string S1, string dump = "#//#")
{
    vector<string>DataRecord = SplitString(S1, dump);

    sClientData ClientData;

    ClientData.AccountNumber = DataRecord[0];
    ClientData.PinCode = DataRecord[1];
    ClientData.Name = DataRecord[2];
    ClientData.Phone = DataRecord[3];
    ClientData.AccountBalance = stod(DataRecord[4]);

    return ClientData;
}

void PrintLineRecord(sClientData ClientData)
{
    cout << "| " << left << setw(15) << ClientData.AccountNumber;
    cout << "| " << left << setw(10) << ClientData.PinCode;
    cout << "| " << left << setw(40) << ClientData.Name;
    cout << "| " << left << setw(12) << ClientData.Phone;
    cout << "| " << left << setw(12) << ClientData.AccountBalance;
}

void PrintAllClientsData(vector<sClientData> vClientData)
{
    system("cls");
    cout << Taps(5) << "Client Lint (" << vClientData.size() << ") Client(s).\n";
    cout << "\n____________________________________________________________________________________________________\n\n";

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";


    cout << "\n____________________________________________________________________________________________________\n\n";
    for (sClientData ClientData : vClientData)
    {
        PrintLineRecord(ClientData);
        cout << endl;
    }
    cout << "\n____________________________________________________________________________________________________\n\n";



}

vector<sClientData> LoadClientesFromFile(string FileName)
{
    fstream MyFile;

    vector< sClientData> Clint;

    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;

        while (getline(MyFile, Line))
        {
            Clint.push_back(ConvertLineDataToRecord(Line));
        }
        MyFile.close();
    }
    return Clint;
}

void PrintRecord(sClientData ClientData)
{
    cout << "\nAccount Number: " << ClientData.AccountNumber << endl;
    cout << "Pin Code      : " << ClientData.PinCode << endl;
    cout << "Name          : " << ClientData.Name << endl;
    cout << "Phone         : " << ClientData.Phone << endl;
    cout << "Account Balance: " << ClientData.AccountBalance << endl;;


}

bool CheckClientIsFound(vector<sClientData>& vClients, string Account, sClientData& Client)
{
    for (sClientData& ClientData : vClients)
    {
        if (ClientData.AccountNumber == Account)
        {
            Client = ClientData;
            return true;
        }
    }
    return false;
}

short CheckClientIsFound(vector<sClientData> vClients, string Account)
{
    short indx = -1;
    sClientData ClientData;
    for (short i = 0; i < vClients.size(); i++)
    {
        ClientData = vClients[i];
        if (ClientData.AccountNumber == Account)
            return i;
    }
    return -1;
}

void AddDataLineToFile(string FileName, vector<string> stDataline)
{
    fstream MyFile;

    MyFile.open(FileName, ios::out);

    if (MyFile.is_open())
    {
        for (string line : stDataline)
        {
            MyFile << line << endl;
        }
        MyFile.close();
    }

}



void DeleteClient(vector<sClientData>& vClients, sClientData DeleteClientData)
{

    vector<string> vString;
    for (sClientData ClientData : vClients)
    {
        if (DeleteClientData.AccountNumber == ClientData.AccountNumber)
        {
            continue;
        }
        vString.push_back(ClientDataRecordToOneLine(ClientData));
    }
    AddDataLineToFile(ClientsFileName, vString);

    vClients = LoadClientesFromFile(ClientsFileName);


}

void DeleteClients(vector<sClientData>& vClients, string Account, sClientData& Client)
{

    system("cls");
    if (CheckClientIsFound(vClients, Account, Client))
    {
        cout << "\nThe following are the client details:\n\n";
        PrintRecord(Client);
        cout << "\n Are you sure tou whant delete this client? y/n ? ";
        char Choise;
        cin >> Choise;
        if (tolower(Choise) == 'y')
        {
            DeleteClient(vClients, Client);
            cout << "\n\nClient Deleted Successfuly.\n";
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << Account << ")Not Found!\n";
    }

}

void AddDataLineToFile(string FileName, vector<sClientData>stDataline)
{
    fstream MyFile;

    MyFile.open(FileName, ios::out);

    if (MyFile.is_open())
    {
        for (sClientData line : stDataline)
        {
            MyFile << ClientDataRecordToOneLine(line) << endl;
        }
        MyFile.close();
    }

}

sClientData ReadNewClientData(sClientData ClientData)
{
    sClientData Client;
    cout << "Please Enter Clint Data:\n\n";
    Client.AccountNumber = ClientData.AccountNumber;
    Client.PinCode = ReadString("Enter Pin Code ? ");
    Client.Name = ReadString("Enter Name ? ");
    Client.Phone = ReadString("Enter Phone ? ");
    Client.AccountBalance = ReadPositeveNumberDouble("Enter AccountBalance ? ");

    return Client;
}

void UpdateClient(vector<sClientData>& vClients, sClientData UbateClientData)
{

    vector<string> vString;
    for (sClientData& ClientData : vClients)
    {
        if (UbateClientData.AccountNumber == ClientData.AccountNumber)
        {
            ClientData = ReadNewClientData(ClientData);
            break;
        }
    }
    AddDataLineToFile(ClientsFileName, vClients);

}

void UpdateClientByAccountNumber(vector<sClientData>& vClients, string Account, sClientData& Client)
{

    system("cls");
    if (CheckClientIsFound(vClients, Account, Client))
    {
        cout << "\nThe following are the client details:\n\n";
        PrintRecord(Client);
        cout << "\n Are you sure tou whant Update this client? y/n ? ";
        char Choise;
        cin >> Choise;
        if (tolower(Choise) == 'y')
        {
            UpdateClient(vClients, Client);
            cout << "\n\nClient Update Successfuly.\n";
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << Account << ")Not Found!\n";
    }

}

void FindClientByAccountNumber(vector<sClientData> vClients, string Account)
{
    system("cls");
    short indxClient = CheckClientIsFound(vClients, Account);

    if (indxClient == -1)
    {
        cout << "\nClient with Account Number (" << Account << ")Not Found!\n";
    }
    else
    {
        cout << "\nThe following are the client details:\n\n";
        PrintRecord(vClients[indxClient]);

    }

}

void ShowMenueScreen()
{
    system("cls");

    cout << "===========================================\n";
    cout << Taps(2) << "Main Menue Screen\n";
    cout << "===========================================\n\n";
    cout << Taps(1) << "[1] Show Clinet List.\n";
    cout << Taps(1) << "[2] Add New Client.\n";
    cout << Taps(1) << "[3] Delete Client.\n";
    cout << Taps(1) << "[4] Update Client Info.\n";
    cout << Taps(1) << "[5] Find Client.\n";
    cout << Taps(1) << "[6] Exit.\n";
    cout << "===========================================\n";
    cout << "Choose what do you want to do? [1 to 6]?";
}

void ShowAddNewScreen()
{
    cout << "------------------------------------------\n";
    cout << Taps(1) << "Add New Clients Screen\n";
    cout << "------------------------------------------\n";

}
void ShowDeleteScreen()
{
    cout << "------------------------------------------\n";
    cout << Taps(1) << "Delete Clients Screen\n";
    cout << "------------------------------------------\n\n";

}
void ShowUpdateScreen()
{
    cout << "------------------------------------------\n";
    cout << Taps(1) << "Update Clients Info Screen\n";
    cout << "------------------------------------------\n\n";

}
void ShowFindScreen()
{
    cout << "---------------------------------------\n";
    cout << Taps(1) << "Find Clients Screen\n";
    cout << "---------------------------------------\n\n";

}
void ShowProgramEnds()
{
    cout << "---------------------------------------\n";
    cout << Taps(1) << "  Program Ends :-)\n";
    cout << "---------------------------------------\n\n";

}
enum enMainMenueOptions
{
    enShowClinetList = 1, enAddNewClient = 2, enDeleteClient = 3,
    enUpdateClientInfo = 4, enFindClient = 5, Exit = 6

};
void StartBank()
{   
    sClientData Client;
    vector< sClientData> ClientData = LoadClientesFromFile(ClientsFileName);
    short NumberChoice=0;
        

    while (true)
    {
        
        ShowMenueScreen();
       cin >> NumberChoice;
        switch ((enMainMenueOptions)NumberChoice)
        {
        case enMainMenueOptions::enShowClinetList:
            PrintAllClientsData(ClientData);
            break;

        case enMainMenueOptions::enAddNewClient:
            system("cls");
            ShowAddNewScreen();
            AddClients(ClientData);
            ClientData = LoadClientesFromFile(ClientsFileName);
            break;

        case enMainMenueOptions::enDeleteClient:
            system("cls");
            ShowDeleteScreen();
            DeleteClients(ClientData, ReadString("Please enter AccountNumber? "), Client);
            break;

        case enMainMenueOptions::enUpdateClientInfo:
            system("cls");
            ShowUpdateScreen();
            UpdateClientByAccountNumber(ClientData, ReadString("Please enter AccountNumber? "), Client);
            break;

        case enMainMenueOptions::enFindClient:
            system("cls");
            ShowFindScreen();
            FindClientByAccountNumber(ClientData, ReadString("Please enter AccountNumber? "));
            break;

        case enMainMenueOptions::Exit:
            system("cls");
            ShowProgramEnds();
            system("pause");
            return;
            break;
        default:
            cout << "Rong Choose what do you want to do? [1 to 6]?";
            break;
        }
        system("pause");


    }

}
int main()
{
    StartBank();
    return 0;
}
