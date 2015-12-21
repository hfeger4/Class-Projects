/*

CodeBlocks
Assignment 4
This program uses structs to organize NFL teams
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <cstring>
#include <cctype>
#include <algorithm>
using namespace std;

struct NFL_Team
{
    string name;
    string conference;
    string division;
    unsigned short wins;
    unsigned short losses;
    unsigned short ties;
    float pct;
};

const int size = 32;


void getTeamNames(const string& filename, NFL_Team* team);
void getScores(const string& filename, NFL_Team* team);
int isInArray(string word, NFL_Team* team);
void sort(NFL_Team* team, int b);

int main()
{
    const string teamfile = "teamNameFile.txt";
    const string scorefile = "scoresFile.txt";

    NFL_Team team[size];

    for(int i=0;i<size;i++){
        team[i].wins = 0;
        team[i].losses = 0;
        team[i].ties = 0;
    }

    getTeamNames(teamfile, team);
    getScores(scorefile, team);

    for(int i=0;i<size;i++)
    {
    team[i].pct = (team[i].wins+ .5*team[i].ties)/((team[i].wins + team[i].losses));
    }
        int b =0;

        for (int c=1; c>=0;c--)
        {
        cout << endl;
        cout << team[c].conference << endl;

        for (int i = 3; i >= 0; i--)
        {
            cout << endl;
            cout << left << setw(25) << team[i+(c*4)].division;
            cout << left << setw(6) << "W";
            cout << left << setw(6) << "L";
            cout << left << setw(6) << "T";
            cout << right << setw(6) << "Pct";
            cout << endl;

            for(int a=0;a<4;a++)
            {
            b = a+i*4+c*16;

            //sort(team,b);

            cout << left << setw(25)<< team[b].name;
            cout << left << setw(6) << team[b].wins;
            cout << left << setw(6) << team[b].losses;
            cout << left << setw(6) << team[b].ties;
            cout << right << fixed << setprecision(3)<< setw(6) << team[b].pct;
            cout << endl;
            b++;
            }
        }
        }


}

void getScores(const string& filename, NFL_Team* team)
{
    ifstream myfile("scoresFile.txt");
    if (myfile)
   {
       while(!myfile.eof()){
       string date;
       string winnerloser;
       myfile >> date;
       getline(myfile,winnerloser);
//       cout << date << endl;
//       cout << winnerloser << endl;

        int a;
        int b;

        string str = winnerloser;
        string word;
        string word2;
        string lastletters;
        string lastletters2;
        stringstream stream(str);
        getline(stream, word, ',');
        getline(stream, word2, '\n');
        lastletters.append(word, word.length()-2, word.length());
        lastletters2.append(word2,word2.length()-2,word2.length());


        a= atoi(lastletters.c_str());
        b= atoi(lastletters2.c_str());
        //cout << a << endl;
        //cout << b << endl;



        string winner;
        string loser;

        word.erase(word.length()-3,word.length());
        word.erase(word.begin());
        word2.erase(word2.length()-2,word2.length());
        word2.erase(word2.begin());
        word2.erase(word2.find_last_not_of(" \t\n\r\f\v") + 1);

        int location = 0;

        if (a > b)
        {
            //cout << word << endl;
            location = isInArray(word,team);
 //           cout << team[location].name << endl;
            team[location].wins++;

//            cout << word2 << endl;
            location = isInArray(word2,team);
//            cout << team[location].name << endl;
            team[location].losses++;


        }
        else
        {
            location = isInArray(word,team);
            team[location].ties++;
            location = isInArray(word2,team);
            team[location].ties++;

        }
       }
       myfile.close();
   }
   else cout << "File not found" << endl;
}

void getTeamNames(const string& filename, NFL_Team* team)
{
    string buffer;

   ifstream myfile("teamNameFile.txt");
   if (myfile)
   {

       int b =0;

        for (int c=0; c<2;c++)
        {

        getline(myfile, team[c].conference);

        for (int i = 0; i < 4; i++)
        {
            getline(myfile,buffer);
            getline(myfile, team[i+(c*4)].division );

            for(int a=0;a<4;a++)
            {
            b = a+i*4+c*16;
            getline(myfile, team[b].name);
            b++;
            }

        }

        getline(myfile,buffer);

        }
        myfile.close();

    }

       else cout << "File not found" << endl;
}

int isInArray(string word, NFL_Team* team)
{
    for (int i=0;i<size;i++)
    {
    if (word.compare(team[i].name) == 0)
        return i;
    }
    return 0;
}

void sort(NFL_Team* team, int b)
{
    NFL_Team temp;


        for(int a=0;a<4;a++)
        {

        for(int i = 0; i < b; i++)
        {
            for (int j = i+1 ; j < b; j++)
            {
                if (team[i].pct > team[j].pct)
                {
				temp = team[i];
				team[i] = team[j];
				team[j] = temp;
                }
            }
        }
        }

}
