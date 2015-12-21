/*

CodeBlocks
Assignment #2

This program reads in student data and prints two outfiles
sorted differently.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;

const int SIZE = 8;
const int NumRows = 50;
const int NumCols = 17;

int findsum(int assignments[]);
int findsmallest(int assignments[]);
string lettergrade(int pct);

void printStudent(int data[][NumCols]);
void print1ElementOf2dArray(int element,ofstream &outputFile);
void print1RowOf2dArray(int row[],ofstream &outputFile);
void printPtsDescending(int data[][NumCols]);
void sortArray(int [][NumCols], int col);
void swapRow(int a[], int b[]);
void swap(int& a, int& b);
int getDataFromFile(int data[][NumCols]);
void descendSortArray(int data [][NumCols], int col);

int main ()
{
    int data[NumRows+1][NumCols];

    getDataFromFile(data);
    sortArray(data,0);
    printStudent(data);

    descendSortArray(data,15);
    printPtsDescending(data);



}

void print1RowOf2dArray(int data[],ofstream &outputFile)
{

        string grade;

        outputFile <<right << setw(8) << setfill('0')<< data[0];
        outputFile << " " << setfill(' ');
        for (int i=0;i<SIZE;i++){
        outputFile << right << setw(2) << data[i+1]<< " ";
        }

        grade = lettergrade(data[16]);


        outputFile << right << setw(3)<< data[10]<< " ";
        outputFile << right << setw(2)<< data[11]<< " ";
        outputFile << right << setw(2)<< data[12]<< " ";
        outputFile << right << setw(2)<< data[13]<< " ";
        outputFile << right << setw(3)<< data[14]<< " ";
        outputFile << right << setw(3)<< data[15]<< " ";
        outputFile << right << setw(3)<< data[16]<< " ";
        outputFile << left  << setw(2)<< grade << " ";
        outputFile << endl;

}

void print1ElementOf2dArray(int element,ofstream &outputFile)
{
    outputFile << right << setw(8) << setfill('0')<< element;
    outputFile << " " << setfill(' ');
}

void printStudent(int data[][NumCols])
{
        ofstream outputFile;
        outputFile.open("Assignment2StudentIDs.txt");

        outputFile << "Stdnt Id " << "----- Assignments ----- "<< "Tot ";
        outputFile << "Mi " << "Ex "<< "Cl "<< "Fin "<< "Pts ";
        outputFile << "Pct "<< "Gr"<< endl;
        outputFile << "-------- "<< "----------------------- "<< "--- ";
        outputFile << "-- "<< "-- "<< "-- "<< "--- "<<"--- "<< "--- ";
        outputFile << "-- "<< endl;

        string grade;

        print1ElementOf2dArray(data[0][0],outputFile);
        for (int i=0;i<SIZE;i++){
        outputFile << right << setw(2) << data[0][i+1]<< " ";
        }
         grade = lettergrade(data[0][16]);


        outputFile << right << setw(3)<< data[0][10]<< " ";
        outputFile << right << setw(2)<< data[0][11]<< " ";
        outputFile << right << setw(2)<< data[0][12]<< " ";
        outputFile << right << setw(2)<< data[0][13]<< " ";
        outputFile << right << setw(3)<< data[0][14]<< " ";
        outputFile << right << setw(3)<< data[0][15]<< " ";
        outputFile << right << setw(3)<< data[0][16]<< " ";
        outputFile << left  << setw(2)<< grade << " ";
        outputFile << endl;

        print1RowOf2dArray(data[1],outputFile);


        for(int count=2;count<NumRows;count++)
        {


        outputFile <<right << setw(8) << setfill('0')<< data[count][0];
        outputFile << " " << setfill(' ');
        for (int i=0;i<SIZE;i++){
        outputFile << right << setw(2) << data[count][i+1]<< " ";
        }

        grade = lettergrade(data[count][16]);


        outputFile << right << setw(3)<< data[count][10]<< " ";
        outputFile << right << setw(2)<< data[count][11]<< " ";
        outputFile << right << setw(2)<< data[count][12]<< " ";
        outputFile << right << setw(2)<< data[count][13]<< " ";
        outputFile << right << setw(3)<< data[count][14]<< " ";
        outputFile << right << setw(3)<< data[count][15]<< " ";
        outputFile << right << setw(3)<< data[count][16]<< " ";
        outputFile << left  << setw(2)<< grade << " ";
        outputFile << endl;

        }
        outputFile.close();
}

void printPtsDescending(int data[][NumCols])
{
        ofstream outputFile;
        outputFile.open("Assignment2PtsDescending.txt");

        outputFile << "Stdnt Id " << "----- Assignments ----- "<< "Tot ";
        outputFile << "Mi " << "Ex "<< "Cl "<< "Fin "<< "Pts ";
        outputFile << "Pct "<< "Gr"<< endl;
        outputFile << "-------- "<< "----------------------- "<< "--- ";
        outputFile << "-- "<< "-- "<< "-- "<< "--- "<<"--- "<< "--- ";
        outputFile << "-- "<< endl;

        string grade;
        for(int count=0;count<NumRows;count++)
        {


        outputFile <<right << setw(8) << setfill('0')<< data[count][0];
        outputFile << " " << setfill(' ');
        for (int i=0;i<SIZE;i++){
        outputFile << right << setw(2) << data[count][i+1]<< " ";
        }

        grade = lettergrade(data[count][16]);


        outputFile << right << setw(3)<< data[count][10]<< " ";
        outputFile << right << setw(2)<< data[count][11]<< " ";
        outputFile << right << setw(2)<< data[count][12]<< " ";
        outputFile << right << setw(2)<< data[count][13]<< " ";
        outputFile << right << setw(3)<< data[count][14]<< " ";
        outputFile << right << setw(3)<< data[count][15]<< " ";
        outputFile << right << setw(3)<< data[count][16]<< " ";
        outputFile << left  << setw(2)<< grade << " ";
        outputFile << endl;

        }
        outputFile.close();
}

int getDataFromFile(int data[][NumCols]){

    int studentid, mid, ex, cl, finals;
    int assignments[SIZE];
    string grade;
    int pct;
    int pts;

     int count = 0;
     ifstream fin;
    fin.open("StudentData.txt");
    if(!fin){
        cerr << "File not found\n";
        exit(1);
        }

    while (!fin.eof())
    {
        fin >> studentid;
        if (fin.eof() || count == NumRows) break;
        data[count][0] = studentid;

        for (int i=0; i < SIZE; i++)
            {
            fin >> assignments[i];
            }

        for(int i=0; i < SIZE; i++)
            {
            data[count][i+1] = assignments[i];
            }

        fin >> mid >> ex >> cl >> finals;

        int sum = findsum(assignments);
        int smallest= findsmallest(assignments);
        int total = sum - smallest;

        data[count][10] = total;
        data[count][11] = mid;
        data[count][12] = ex;
        data[count][13] = cl;
        data[count][14] = finals;

        float pts = total + mid + ex + cl + finals;
        pct= (((pts/400) * 100)+.5);

        data[count][15] = pts;
        data[count][16] = pct;




    count++;
    }
    fin.close();
}



void sortArray(int data [][NumCols], int col)
{
    int i, j;
    for (i = 0; i < NumRows - 1; i++) {
        for (j = i+1; j < NumRows; j++) {
            if (data[i][col] > data[j][col]) swapRow(data[i],data[j]);
        }
    }
}

void descendSortArray(int data [][NumCols], int col)
{
    int i, j;
    for (i = 0; i < NumRows - 1; i++) {
        for (j = i+1; j < NumRows; j++) {
            if (data[i][col] < data[j][col]) swapRow(data[i],data[j]);
        }
    }
}

void swapRow(int a[], int b[])
{
    for (int i = 0; i < NumCols; i++) {
        swap(a[i],b[i]);
    }
}


void swap(int& a, int& b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

int findsum (int assignments[]){
        int a,sum;
        sum = 0;
        for( a=0 ;a < 8 ;a++)
        {
        sum += assignments[a];
        }
        return sum;
}

int findsmallest(int assignments[]){
        int b, smallest;
        smallest = assignments[0];
        for (int b=1; b < 7; b++){
            if (assignments[b] < smallest)
                smallest = assignments[b];}
        return smallest;

}

string lettergrade(int pct){

    string grade;

    if (pct > 97){
        grade = "A+";
    }
    else if (pct <= 97 && pct >=93){
        grade = "A";
    }
    else if (pct >=90 && pct <93){
        grade = "A-";
    }
    else if (pct > 87 && pct < 90){
        grade = "B+";
    }
    else if (pct <= 87 && pct >=83){
        grade = "B";
    }
    else if (pct >=80 && pct <83){
        grade = "B-";
    }
    else if (pct > 77 && pct < 80){
        grade = "C+";
    }
    else if (pct <= 77 && pct >=73){
        grade = "C";
    }
    else if (pct >=70 && pct <73){
        grade = "C-";
    }
    else if (pct > 67 && pct < 70){
        grade = "D+";
    }
    else if (pct <= 67 && pct >=63){
        grade = "D";
    }
    else if (pct >=60 && pct <63){
        grade = "D-";
    }
    else {
        grade = "F";
    }

    return grade;
}
