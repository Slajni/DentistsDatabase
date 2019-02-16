#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>

using namespace std;

ifstream  inputFileVisits;
ifstream  inputFileClients;
ifstream  inputFileDentists;
ofstream  outputFileClients;
ofstream  outputFileVisits;
ofstream  outputFileDentists;


int getPositiveNumber()
{
    int res;
    do
    {
        cout << "Provide the number: ";
        cin >> res;
        if(res<0)
            cout << "Number has to be positive" << endl;

    }while(res < 0);
    return res;
}

enum type {surgeon, esthetic, general};

struct Time
{
    int hour;
    int minute;

};

class Date
{
    int year;
    int month;
    int day;

    Time time;

public:

    Date(int y, int m, int d, int h, int min) // constructor making sure that date is correct
    {
        if(y >= 2019)
            year = y;
        else
            year = 2019;
        if(m >= 1 && m <=12)
            month = m;
        else
            month = 1;
        if(d >= 1)
        {
            if(month == 2)
            {
                if(year % 4 == 0)

                    if(year % 100 == 0)

                        if(year % 400 == 0)
                            if(d <= 29)
                                day = d;
                            else
                                day = 1;
                        else
                            if(d <=28)
                                day = d;
                            else
                                day = 1;

                    else
                    {
                        if(d <= 29)
                            day = d;
                        else
                            day = 1;
                    }

                else
                {
                    if(d <=28)
                        day = d;
                    else
                        day = 1;
                }
            }
            else
                if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
                {
                    if(d <= 31)
                        day = d;
                    else
                        day = 1;
                }
                else
                {
                    if(d <= 30)
                        day = d;
                    else
                        day = 1;
                }
        }

        if(h >= 0 && h <=23)
            time.hour = h;
        else
            time.hour = 8;
        if(min >=0 && min <= 59)
            time.minute = min;
        else
            time.minute = 0;
    }


    void printDate()
    {
        printf("Date is %d-%d-%d   %d:%d \n", year, month, day, time.hour, time.minute);
    }

    string getDate()
    {
        return (to_string(year) + " " + to_string(month) + " " + to_string(day) + " " + to_string(time.hour) + " " + to_string(time.minute));
    }

    static Date * dateCreator()
    {
        int y,m,d,h,min;
        cout << "Choose year: ";
        cin >> y;
        cout << "Choose month: ";
        cin >> m;
        cout << "Choose day: ";
        cin >> d;
        cout << "Choose hour: ";
        cin >> h;
        cout << "Choose minutes: ";
        cin >> min;

        return new Date(y, m, d, h, min);

    };


};

class Person
{
    string name;
    string surname;
    int id;
    static int nextId;

public:

    Person(string n, string s)
    {
        name = n;
        surname = s;
        id = nextId;
        nextId++;
    }

    int getId()
    {
        return id;
    }

    virtual void printPerson()
    {
        printf("%s %s with id: %d", name.c_str(), surname.c_str(), id);
    }

    virtual string getPerson()
    {
        return name + " " + surname + " " + to_string(id);
    }

};

int Person::nextId = 0;

class Dentist : public Person
{
    type specialisation;

public:

    Dentist(string n, string s, type sp)
    :Person(n,s)
    {
        specialisation = sp;
    }

    virtual void printPerson() override
    {
        Person::printPerson();
        switch(specialisation)
        {
            case surgeon:
                cout << " of specialisation: " << "surgeon" << endl;
                break;
            case esthetic:
                cout << " of specialisation: " << "esthetic" << endl;
                break;
            case general:
                cout << " of specialisation: " << "general" << endl;
                break;
            default:
                break;
        }
    }

    virtual string getPerson() override
    {
        string res = Person::getPerson();
        switch(specialisation)
        {
            case surgeon:
                res = res + " " + "1";
                break;
            case esthetic:
                res = res + " " + "2";
                break;
            case general:
                res = res + " " + "3";
                break;
            default:
                break;
        }
        return res;
    }

    type getSpec()
    {
        return specialisation;
    }

};

class Client : public Person
{
    int balance;

public:

    Client(string n, string s, int b)
    :Person(n,s)
    {
        if(balance >= 0)
            balance = b;
        else
        {
            cout << "Balance can't be negative so it is set to 10000" << endl;
            balance = 10000;
        }
    }

    void updateBalance()
    {
        int b;
        cout << "What is the new balance?: " << endl;
        cin >> b;
        if(b > 0)
            balance = b;
        else
        {
            cout << "Balance can't be negative so it is set to 10000" << endl;
            balance = 10000;
        }


    }

    void pay(int amount)
    {
        balance -= amount;
    }

    int getBalance()
    {
        return balance;
    }

    virtual void printPerson() override
    {
        Person::printPerson();
        cout << " with balance: " << balance << endl;
    }

    virtual string getPerson() override
    {
        string res = Person::getPerson();
        res = res + " " + to_string(balance);
        return res;
    }

};

class Service // TODO: CHECK IF OK
{
    Date * date;
    type typeOfService;

    virtual int calculateCost(){};

protected:
    int cost = 0;

public:

    Service(type t, Date * d)
    {
        typeOfService = t;
        date = d;
    }

public:

    void printCost()
    {
        cout << cost << endl;
    }

};

class TeethWhitening : public Service
{

public:
    virtual int calculateCost() override
    {
        return 1000;
    }

    TeethWhitening(type t, Date * d)
    :Service(t, d)
    {
        cost = calculateCost();
    }
};

class ToothRemoval : public Service
{
private:

    int numberOfTeeth = 1;

public:

    virtual int calculateCost() override
    {
        return numberOfTeeth * 300;
    }


    ToothRemoval(type t, Date * d, int nr)
    :Service(t, d)
    {
        if(nr >= 2 && nr <=24)
            numberOfTeeth = nr;
        cost = calculateCost();
    }



};

class ToothHealing : public Service
{

private:

    int numberOfTeeth = 1;

public:

    virtual int calculateCost() override
    {
        return 100 * numberOfTeeth;
    }


    ToothHealing(type t, Date * d, int nr)
    :Service(t, d)
    {
            if(nr >= 2 && nr <=24)
                numberOfTeeth = nr;
            cost = calculateCost();
    }
};
class Visit
{
    Dentist * dentist;
    Client * client;
    Date * date;
    int id;
    static int nextId;

public:

    Visit(Dentist * dentist, Client * client, Date * date)
    {
        this->dentist = dentist;
        this->client = client;
        this->date = date;
        id = nextId;
        nextId++;
    }
    void printVisitInfo()
    {
        cout << "------------------------------" << endl;
        cout << "Visit number #" << id << endl << endl << "Dentist: ";
        dentist->printPerson();
        cout << endl << "Client: ";
        client->printPerson();
        cout << endl << "Date: ";
        date->printDate();
        cout << "------------------------------" << endl;
    }

    string getVisit()
    {
        return to_string(client->getId()) + " " + to_string(dentist->getId()) + " " + date->getDate();
    }

    int getVisitId()
    {
        return id;
    }

    int getVisistsDentId()
    {
        return dentist->getId();
    }

    int getVisitsClientId()
    {
        return client->getId();
    }
    ~Visit()
    {
        delete date;
    }
};

int Visit::nextId = 0;

class Database
{
private:

    vector <Visit*> visits;
    vector <Client*> clients;
    vector <Dentist*> dentists;


public:

    void printVisitsList() const
    {
        cout << "Printing Visits\n";
        for(auto visit: visits)
            visit->printVisitInfo();
        cout << endl;
    }

    void printClientsList() const
    {
        cout << "Printing Clients\n";
        for(auto client: clients)
            client->printPerson();
        cout << endl;
    }

    void printDentistsList() const
    {
        cout << "Printing dentists\n";
        for(auto dentist: dentists)
            dentist->printPerson();
        cout << endl;
    }

    Dentist * hasDentistOfId(int id)
    {

        for(auto dentist: dentists)
        {
            if(dentist->getId() == id)
                return dentist;
        }
        return nullptr;
    }

    Client * hasClientOfId(int id)
    {

        for(auto client: clients)
        {
            if(client->getId() == id)
                return client;
        }
        return nullptr;
    }

    int numberOfVisits()
    {
        return visits.size();
    }
    int numberOfClients()
    {
        return clients.size();
    }
    int numberOfDentists()
    {
        return dentists.size();
    }

    void addVisit()
    {
        if(clients.size()>0 && dentists.size() > 0)
        {
            cout << "------------------------------\n";
            cout << "Printing all clients" << endl;
            for(auto client: clients)
                client->printPerson();
            cout << "---------------\n";
            cout << "Printing all dentists" << endl;
            for(auto dentist: dentists)
                dentist->printPerson();

            cout << endl;
            int choice = -1;

            Dentist * dent = nullptr;
            Client * cli = nullptr;

            do
            {
                cout << "Choose client by id: ";
                cin >> choice;
                cli = hasClientOfId(choice);
                if (cli != nullptr)
                {
                    choice = -1;
                    break;
                }

                cout << "There is no client with such id, provide correct id" << endl;
            } while (cli == nullptr);
            do
            {
                cout << "Choose dentist by id: ";
                cin >> choice;
                dent = hasDentistOfId(choice);
                if (dent != nullptr)
                {
                    choice = -1;
                    break;
                }

                cout << "There is no dentist with such id, provide correct id" << endl;
            } while (dent == nullptr);


            switch(dent->getSpec())
            {
                case surgeon:
                {
                    cout << "Getting the number of teeth\n";
                    int nr = getPositiveNumber();
                    Date * date = Date::dateCreator();
                    ToothRemoval * serv = new ToothRemoval(surgeon, date, nr);

                    if(serv->calculateCost() > cli->getBalance())
                    {
                        cout << "Client has not sufficient amount of money" << endl;
                    }
                    else
                    {
                        visits.push_back(new Visit(dent, cli, date));
                        cli->pay(serv->calculateCost());
                        cout << "Visit has been created\n";
                    }
                    delete serv;
                    break;
                }
                case general:
                {
                    cout << "Getting the number of teeth\n";
                    int nr = getPositiveNumber();
                    Date * date = Date::dateCreator();
                    ToothHealing * serv = new ToothHealing(general, date, nr);

                    if(serv->calculateCost() > cli->getBalance())
                    {
                        cout << "Client has not sufficient amount of money" << endl;
                    }
                    else
                    {
                        visits.push_back(new Visit(dent, cli, date));
                        cli->pay(serv->calculateCost());
                        cout << "Visit has been created\n";
                    }
                    delete serv;
                    break;
                }
                case esthetic:
                {
                    Date * date = Date::dateCreator();
                    TeethWhitening * serv = new TeethWhitening(general, date);

                    if(serv->calculateCost() > cli->getBalance())
                    {
                        cout << "Client has not sufficient amount of money" << endl;
                    }
                    else
                    {
                        visits.push_back(new Visit(dent, cli, date));
                        cli->pay(serv->calculateCost());
                        cout << "Visit has been created\n";
                    }
                    delete serv;
                    break;
                }
                default:
                    break;
            }



        }
        else
        {
            cout << "There is not enough clients and/or dentists to book a visit\n";
        }
        cout << "------------------------------\n";
    }
    void addClient()
    {
        cout << "Welcome to client creator, please provide sufficient info\n Name: ";
        string name;
        cin >> name;
        cout << "Surname: ";
        string surname;
        cin >> surname;
        cout << "Account balance: ";
        int balance = getPositiveNumber();
        clients.push_back(new Client(name, surname, balance));
        cout << "Client was created" << endl;
    }
    void addDentist()
    {
        cout << "Welcome to dentist creator, please provide sufficient info\n Name: ";
        string name;
        cin >> name;
        cout << "Surname: ";
        string surname;
        cin >> surname;
        int choice = 0;
        cout << "Provide 1 if the dentists specialisation is surgeon, 2 if esthetic, 3 if general: ";
        do
        {
            cin >> choice;
            if(choice > 3 || choice <1)
                cout << "This is not a valid option choose again: ";
        }while(choice > 3 || choice <1);

        switch(choice)
        {
            case 1:
                dentists.push_back(new Dentist(name, surname, surgeon));
                break;
            case 2:
                dentists.push_back(new Dentist(name, surname, esthetic));
                break;
            case 3:
                dentists.push_back(new Dentist(name, surname, general));
                break;
            default:
                break;
        }
        cout << "Dentist was created" << endl;
    }

    void removeVisit(int id)
    {
        {
            int i = 0;
            for (auto visit : visits)
            {
                if (visit->getVisitId() == id)
                {
                    visits.erase(visits.begin() + i);
                    return;
                }
                i++;
            }
            cout << "There is no visit of such id" << endl;
        }
    }

    void removeClient(int id)
    {
        for(auto visit: visits) // removing all visits with that client first
            if(visit->getVisitsClientId() == id)
                removeVisit(visit->getVisitId());

        int i = 0;
        for (auto client : clients)
        {
            if (client->getId() == id)
            {
                clients.erase(clients.begin() + i);
                return;
            }
            i++;
        }
        cout << "There is no client of such id" << endl;

    }

    void removeDentist(int id)
    {
        for(auto visit: visits) // removing all visits with that dentist first
            if(visit->getVisistsDentId() == id)
                removeVisit(visit->getVisitId());

        int i = 0;
        for (auto dentist : dentists)
        {
            if (dentist->getId() == id)
            {
                dentists.erase(dentists.begin() + i);
                return;
            }
            i++;
        }
        cout << "There is no dentist of such id" << endl;

    }

    void readFromFiles()
    {
        inputFileClients.open("clients.txt");
        inputFileDentists.open("dentists.txt");
        inputFileVisits.open("visits.txt");

        if(!inputFileVisits || !inputFileDentists || !inputFileClients)
            throw std::exception();
        else
        {
            string name, surname, nameD, surnameD;
            int balance = 0, spec = 0, idDent = 0, idClient = 0, year = 0, month = 0, day = 0, hours = 0, minutes = 0;
            while(inputFileClients >> name >> surname >> balance)
            {
                clients.push_back(new Client(name, surname, balance));
            }
            while(inputFileDentists >> nameD >> surnameD >> spec)
            {
                switch(spec)
                {
                    case 1:
                        dentists.push_back(new Dentist(nameD, surnameD, surgeon));
                        break;
                    case 2:
                        dentists.push_back(new Dentist(nameD, surnameD, esthetic));
                        break;
                    case 3:
                        dentists.push_back(new Dentist(nameD, surnameD, general));
                        break;
                    default:
                        break;
                }
            }
            while (inputFileVisits >> idClient >> idDent >> year >> month >> day >> hours >> minutes)
            {
                visits.push_back(new Visit(hasDentistOfId(idDent), hasClientOfId(idClient), new Date(year, month, day, hours, minutes)));
            }

        }

    }
    void saveToFiles() // TODO: dokonczyc
    {
        inputFileVisits.close();
        inputFileClients.close();
        inputFileDentists.close();
        outputFileClients.open("clients.txt");
        outputFileDentists.open("dentists.txt");
        outputFileVisits.open("visits.txt");

        for(auto client: clients)
            outputFileClients << client->getPerson() << endl;
        for(auto dentist: dentists)
            outputFileDentists << dentist->getPerson() << endl;
        for(auto visit: visits)
            outputFileVisits << visit->getVisit() << endl;

        outputFileVisits.close();
        outputFileDentists.close();
        outputFileClients.close();

    }

public:

    Database()
    {
        readFromFiles();
    }
    ~Database()
    {
        saveToFiles();
        for(auto visit: visits)
            delete visit;
        for(auto client: clients)
            delete client;
        for(auto dentist: dentists)
            delete dentist;
    }



};



void choiceMenu()
{
    cout << "//////////////////////MENU//////////////////////" << endl;
    cout << "1. Print whole database" << endl;
    cout << "2. Print all clients" << endl;
    cout << "3. Print all dentists" << endl;
    cout << "4. Print all visits" << endl;
    cout << "5. Update client balance" << endl;
    cout << "6. Add client to database" << endl;
    cout << "7. Add dentist to database" << endl;
    cout << "8. Add visit to database" << endl;
    cout << "9. Delete client from database" << endl;
    cout << "10. Delete dentist from database" << endl;
    cout << "11. Delete visit from datavase" << endl;
    cout << "12. Print menu once more" << endl;
    cout << "13. Leave the program"<< endl;
    cout << "//////////////////////MENU//////////////////////" << endl << endl;
}

void handleOptions(Database & db)
{
    choiceMenu();
    int choice = -1;
    do
    {
        cout << "Choose option from menu: ";
        cin >> choice;
        if(choice > 13 || choice < 1)
        {
            cout << "This is not a valid option" << endl;
            continue;
        }

        switch(choice)
        {
            case 1:
            {
                db.printClientsList();
                db.printDentistsList();
                db.printVisitsList();
                break;
            }
            case 2:
            {
                db.printClientsList();
                break;
            }
            case 3:
            {
                db.printDentistsList();
                break;
            }
            case 4:
            {
                db.printVisitsList();
                break;
            }
            case 5:
            {
                if(db.numberOfClients() > 0)
                {
                    db.printClientsList();
                    cout << "Choose id: ";
                    int idChoice;
                    cin >> idChoice;
                    db.hasClientOfId(idChoice)->updateBalance();
                }
                else
                {
                    cout << "There are no clients in database" << endl;
                }
                break;
            }
            case 6:
            {
                db.addClient();
                break;
            }
            case 7:
            {
                db.addDentist();
                break;
            }
            case 8:
            {
                db.addVisit();
                break;
            }
            case 9:
            {
                if(db.numberOfClients() > 0)
                {
                    db.printClientsList();
                    cout << "Choose id: ";
                    int idChoice;
                    cin >> idChoice;
                    db.removeClient(idChoice);
                }
                else
                {
                    cout << "There are no clients in database" << endl;
                }
                break;
            }
            case 10:
            {
                if(db.numberOfDentists() > 0)
                {
                    db.printDentistsList();
                    cout << "Choose id: ";
                    int idChoice;
                    cin >> idChoice;
                    db.removeDentist(idChoice);
                }
                else
                {
                    cout << "There are no dentists in database" << endl;
                }
                break;
            }
            case 11:
            {
                if(db.numberOfVisits() > 0)
                {
                    db.printVisitsList();
                    int idChoice;
                    cout << "Choose id: ";
                    cin >> idChoice;
                    db.removeVisit(idChoice);
                }
                else
                {
                    cout << "There are no visits in database" << endl;
                }
                break;
            }
            case 12:
            {
                choiceMenu();
                break;
            }
            case 13:
            {
                break;
            }
            default:
            {
                break;
            }

        }

    }while(choice != 13);
}

int main()
{


    try
    {
        Database database;

        handleOptions(database);

    }
    catch (...)
    {
        cerr << "Database files couldn't be loaded, creating blank database" << endl;
        outputFileDentists.open("dentists.txt");
        outputFileClients.open("clients.txt");
        outputFileVisits.open("visits.txt");
        outputFileClients.close();
        outputFileVisits.close();
        outputFileDentists.close();

        Database database;

        handleOptions(database);

    }



    return 0;
}