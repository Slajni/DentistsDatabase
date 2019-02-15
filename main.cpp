#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

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

};

int Person::nextId = 0;

class Dentist : public Person
{
    type specialisation;

    Dentist(string n, string s, type sp)
    :Person(n,s)
    {
        specialisation = sp;
    }


};

class Client : public Person
{
    int balance;

    Client(string n, string s, int b)
    :Person(n,s)
    {
        balance = b;
    }
};

class Service
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
    virtual int calculateCost() override
    {
        return 1000;
    }

public:

    TeethWhitening(type t, Date * d)
    :Service(t, d)
    {
        cost = calculateCost();
    }
};

class ToothRemoval : public Service
{
    int numberOfTeeth = 1;

    ToothRemoval(type t, Date * d, int nr)
    :Service(t, d)
    {
        if(nr >= 2 && nr <=24)
            numberOfTeeth = nr;
    }

};

class ToothHealing : public Service
{
    int numberOfTeeth = 1;

    ToothHealing(type t, Date * d, int nr)
    :Service(t, d)
    {
            if(nr >= 2 && nr <=24)
            numberOfTeeth = nr;
    }
};
class Visit
{
    Dentist * dentist;
    Client * client;
    Date * date;

public:

    Visit(Dentist * dentist, Client * client, Date * date)
    {
        this->dentist = dentist;
        this->client = client;
        this->date = date;
    }
};

class Database
{
private:

    vector <Visit*> visits;
    vector <Client*> clients;
    vector <Dentist*> dentists;

public:

    void addVisit();
    void addClient();
    void addDentist();

    void readFromFiles();
    void saveToFiles();

public:

};

int main()
{
    // Tests
    Date d1(2020,5,4,16,30);
    Date d2(-100,0,4,18,0);
    Date d3(2400,2,29,14,0);
    Date d4(2300,2,29,14,0);

    d1.printDate();
    d2.printDate();
    d3.printDate();
    d4.printDate();

    Service s1(surgeon, &d1);
    TeethWhitening s2(general, &d2);

    s1.printCost();
    s2.printCost();

    return 0;
}