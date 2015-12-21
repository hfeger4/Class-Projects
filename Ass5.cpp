/*

CodeBlocks
Assignment 5

This is a mutual fund analysis using classes.

*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <sstream>
using namespace std;

class MutualFund{
private:
    string ticker;
    string analysisDate;
    float closeArray[300];
    int dateArray[300];
public:
    void readHistoryFile(const char* filename);
    void assignTicker(string s);
    int getDateFromString(const string &s);
    float getCloseFromString(const string &s);
    float getMin();
    float getMax();
    void report();
    float fiftyDayAverage();
    float twoHundredDayAverage();
    void recommendation(float x);

};

void MutualFund::assignTicker(string s)
{
    ticker = s;
    cout << "Fund: "<< ticker << endl;
}

void MutualFund::readHistoryFile(const char* filename)
{
    int size = 300;
    string buffer[size];
    string firstline;

    ifstream fin(filename);
    if (!fin)
    {
        cerr << "Unable to open team file " << filename << endl;
        exit(1);
    }

    getline(fin,firstline);
    //cout <<firstline << endl;

    for(int i=0; i < size;i++)
    {
        getline(fin,buffer[i]);
        //cout << buffer[i] << endl;
        int l = getDateFromString(buffer[i]);
        dateArray[i] = l;
        float j = getCloseFromString(buffer[i]);
        closeArray[i] = j;
    }

    fin.close();
}

int MutualFund::getDateFromString(const string &s)
{
    string temp;
    temp =  s.substr(2,2);
    temp += s.substr(5,2);
    temp += s.substr(8,2);
    //cout << "This is the date " << temp << endl;

    return atoi(temp.c_str());

}

float MutualFund::getCloseFromString(const string &s)
{
    string temp;
    size_t pos,pos4,pos5;
    pos = s.find(' ');
    pos = s.find(',',pos+1);
 //   cout << pos << endl;
    pos = s.find(',',pos+1);
  //  cout << pos << endl;
    pos = s.find(',',pos+1);
 //   cout << pos << endl;
    pos4 = s.find(',',pos+1);
  //  cout << pos4 << endl;
    pos5 = s.find(',',pos4+1);
 //   cout << pos5 << endl;
    temp = s.substr((pos4+1),(pos5-pos4-1));

    //cout << "This is the close " << temp << endl;
    //cout << endl;
    return atof(temp.c_str());

}

float MutualFund::getMin()
{
    float smallest = closeArray[0];
    for (int i = 0; i < 254; i++) {
    if (closeArray[i] < smallest) {
        smallest = closeArray[i];
        }
    }
    return smallest;
}

float MutualFund::getMax()
{
    float largest = closeArray[0];
    for (int i = 0; i < 254; i++) {
    if (closeArray[i] > largest) {
        largest = closeArray[i];
        }
    }
    return largest;
}

float MutualFund::fiftyDayAverage()
{
    float average = 0;
    for(int i=0;i<50;i++)
    {
        //cout << "closeArray " << closeArray[i] << endl;
        average += (closeArray[i]);
    }
    average = average/50;
    return average;
}

float MutualFund::twoHundredDayAverage()
{
    float average = 0;
    for(int i=0;i<200;i++)
    {
        //cout << "closeArray " << closeArray[i] << endl;
        average += (closeArray[i]);
    }
    average = average/200;
    return average;
}

void MutualFund::recommendation(float x)
{
    cout << "Recommendation: ";

    if (x < (-3.0))
    {
        cout << "Buy" << endl;
    }
    else if (x > (3.0))
    {
        cout << "Sell" << endl;
    }
    else
    {
        cout << "Hold" << endl;
    }
}

void MutualFund::report()
{
    cout << "Analysis Date: ";
    int a = dateArray[0];
    stringstream ss;
    ss << a;
    string str = ss.str();
    //cout << str << endl;
    cout << str.substr(2,2) << "/";
    cout << str.substr(4,2) << "/";
    cout << str.substr(0,2) << endl;
    cout << "Latest Close: $" << fixed << setprecision(2) << closeArray[0] << endl;
    cout << "Minimum for the last year = $";
    cout << fixed << setprecision(2) << getMin() << endl;
    cout << "Maximum for the last year = $";
    cout << fixed << setprecision(2) << getMax() << endl;
    cout << "50 day moving average = $";
    cout << fixed << setprecision(2) << fiftyDayAverage() << endl;

    cout << "200 day moving average = $";
    cout << fixed << setprecision(2) << twoHundredDayAverage() << endl;

    float movingAvg = (((closeArray[0]-twoHundredDayAverage())/(closeArray[0]))*100);

    cout << "% gain over 200 Day Moving Avg: ";
    cout << fixed << setprecision(1) << movingAvg << "%" <<endl;
    recommendation(movingAvg);
    cout << endl;
}

int main()
{
    MutualFund vbmfx;
    vbmfx.assignTicker("VBMFX");
    vbmfx.readHistoryFile("vbmfx.csv");
    vbmfx.report();

    MutualFund vtsmx;
    vtsmx.assignTicker("VTSMX");
    vtsmx.readHistoryFile("vtsmx.csv");
    vtsmx.report();
}



