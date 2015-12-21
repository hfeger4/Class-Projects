/*

CodeBlocks
Assignment 6

Constructing the World Population:
This assignment creates a partial model of the population system,
emulating the aging and dying of a population.

*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <ctime>
#include <sstream>
using namespace std;


unsigned DaysPerMonth[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
string NAMES[] =
    {"Negar","Ron","Wayne","Justin","Stephen","Michael","David","Zian","Christopher","Rodney",
    "Zhaozhen","Tatiana","Sam","Yan","Paul","Romualdo","Dalia","Wee Chong Alex","Richard",
    "Brandon","Pramodh","Thomas","Bahman","Asim","Yijie","Maya","Bhavya","Erik","Huy","Tiffany",
    "Xiaolin","Fangyuan","William","Adam","Di","Joe"};

class Date{
private:
    unsigned int day;
    unsigned int month;
    unsigned int year;
    void errmsg(const char* msg);
public:
    Date();
    Date(unsigned int,unsigned int,unsigned int);
    void set(const char* mmddyy);
    int getAge(Date);
    void increment(void);
    void display(void) const;
    Date getRandomBDay();
    Date operator=(Date);
    Date operator+(int);
    void letTimePass();
};

Date::Date()
:day(0),month(0),year(0)
{
}

Date::Date(unsigned int x ,unsigned int y,unsigned int z)
{
    char mm_dd_yy[9];
    string mmddyy;
    stringstream ss;

    if(x < 10)ss << mmddyy << 0;
    ss << mmddyy << x;
    ss << mmddyy << '/';
    if(y < 10)ss << mmddyy << 0;
    ss << mmddyy << y;
    ss << mmddyy << '/';
    if(z < 10)ss << mmddyy << 0;
    ss << mmddyy << z;

    mmddyy = ss.str();

    //cout << mmddyy << endl;

    for(int i = 0; i < 9; i++)
    {
        mm_dd_yy[i] = mmddyy[i];
    }

    set(mm_dd_yy);

}

void Date::set(const char* mm_dd_yy)
{
	char* temp;
	char copy[9];

	if (strlen(mm_dd_yy) != 8) errmsg(mm_dd_yy);

	strcpy(copy,mm_dd_yy);

	temp = strtok(copy,"/");
	if (temp != NULL) month = atoi(temp);
	else errmsg(copy);

	temp = strtok(NULL,"/");
	if (temp != NULL) day = atoi(temp);
	else errmsg(copy);

	temp = strtok(NULL,"/");
	if (temp != NULL) year = atoi(temp);
	else errmsg(copy);

	if (year < 15) year += 2000;
	else if (year > 14) year += 1900;
	else ;
}


void Date::increment (void)
{
	day++;

	if (day > DaysPerMonth[month - 1])
	{
		month ++;
		day = 1;
	}

	if (month > 12)
	{
		year ++;
		month = 1;
	}

	return;
}

void Date::display(void) const
{
	cout << month << '/' << day << '/'
		<< (year%100< 10?"0":"") << year%100 ;//<< endl;
	if (day % DaysPerMonth[month-1] == 0) ;//cout << endl;

	return;
}

void Date::errmsg(const char* msg)
{
	cerr << "Invalid date format: " << msg << endl;
	exit(EXIT_FAILURE);
}

void Date::letTimePass()
{
    int randomNumber = rand() % 364 + 1;
    //cout << " RANDOM " << randomNumber << endl;
    Date temp;
    temp.day = day;
    temp.month = month;
    temp.year = year;
    //cout << " ----- " << temp.day << temp.month << temp.year << endl;
    temp = temp.operator+(randomNumber);
    //cout << " ----- " << temp.day << temp.month << temp.year << endl;
    day = temp.day;
    month = temp.month;
    year = temp.year;
}

Date Date::operator=(Date x)
{
    day = x.day;
    month = x.month;
    year = x.year;

}

Date Date::operator+(int randomDay)
{
    Date temp;

    temp.day = day + randomDay;
    //cout << "temp day    " << temp.day << endl;
    //cout << "day   " << day << endl;
    temp.month = month;
    //cout << "m   " << temp.month << endl;
    temp.year = year;
    //cout << "y   " << temp.year << endl;
    while (temp.day > DaysPerMonth[temp.month - 1])
	{
	    //cout << temp.day << " is greater than " << DaysPerMonth[temp.month-1] << endl;
        temp.day -= DaysPerMonth[temp.month - 1];
        temp.month ++;
        if (temp.month > 12)
        {
		temp.year ++;
		temp.month = 1;
        }
	}
    return temp;
}

Date Date::getRandomBDay()
{
    Date newBDay;
    Date tempBDay(1,1,15);
    //char startDate[9] ={'0','1','/','0','1','/','1','5'};
    //cout << "tempBday" << tempBDay.day << endl;
    int randomNumber;
    randomNumber  = rand() % 36525;
    //cout << "RANDOM  " << randomNumber << endl;
    newBDay = tempBDay + randomNumber;
    return newBDay;
}

int Date::getAge(Date x)
{
    int age = 0;

	//cout << "x.year " << x.year << endl;
	//cout << "year " << year << endl;
    age = x.year - year;
    //cout << "x.month " << x.month << endl;
    //cout << "month " << month << endl;
    if (x.month < month)
    {
        age-=1;
    }
    else if (x.month = month)
    {
        if (x.day < day)
        {
            age-=1;
        }
    }
    return age;
}
Date TODAY(11,20,14);

class Human{
public:
    string name;
    Date birthday;
    Date deathDay;
    bool alive;
    Human(const string&n, const Date&b);
    int age(Date);
};

Human::Human(const string&n, const Date& bday)
:name(n),birthday(bday),alive(true)
{
}


int Human::age(Date x)
{
    int bday;
    bday = birthday.getAge(x);
    return bday;
}

class Population{
private:
    Human** people;
    unsigned original_size;
public:
    Population(int);
    void display() const;
    ~Population();
    void examinePopulation();
    float rollTheDice(unsigned short);
    int getNumberLiving();
    };

Population::Population(int size)
:people(new Human*[size]),original_size(size)
{
    for(int i=0; i< size; i++)
    {
        people[i] = new Human(NAMES[i], people[i]->birthday.getRandomBDay());
    }
}
void Population::display() const
{

cout << "-------------------------------------------------" << endl;
    for(int i = 0; i < 36; i++)
    if (people[i]->alive == false)
    {
    people[i]->deathDay.display();
    cout << " " << people[i]->name << " died at the age of ";
    cout << people[i]->age(TODAY);
        cout << endl;
    }
    cout << "-------------------------------------------------" << endl;
    cout << "Today is ";
    TODAY.display();
    cout << endl;
    for(int i = 0; i < 36; i++)
    if (people[i]->alive == true)
    {
        cout << people[i]->name << " was born on ";
        people[i]->birthday.display();
        cout << " is " << people[i]->age(TODAY) << endl;
        //cout << " is alive? " << people[i]->alive << endl;
    }
}


Population::~Population()
{
    delete people;
}

float Population::rollTheDice(unsigned short age)
{
    return static_cast<float>(age)*(rand()%100)/10000.;
}

void Population::examinePopulation()
{
    for(int i=0;i<36;i++)
    {
        if (rollTheDice(people[i]->age(TODAY)) > .5)
        {
            people[i]->alive = (false);
            //cout << " HELLO alive? " << people[i]->alive << endl;
            people[i]->deathDay = TODAY;
        }
    }
}

int Population::getNumberLiving()
{
    int living = 36;
    for (int i=0;i<36;i++)
    {
        if (people[i]->alive == (false))
        {
            living--;
        }
    }
    //cout << "LIVING "<<living << endl;
    return living;
}

int main()
{
    const int OriginalPopulationSize = 36;

    //TODAY.letTimePass();
    //TODAY.display();

    srand(time(NULL));

    Population World(OriginalPopulationSize);
    World.display();

    // let time pass until half of the world's Population dies
    do
    {
        TODAY.letTimePass();
        World.examinePopulation();
        //cout << World.getNumberLiving() << endl;
    }
    while (World.getNumberLiving() > OriginalPopulationSize/2);

    World.display();

}
