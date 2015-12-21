/*

CodeBlocks
Assignment 8

This is an example of polymorphism using a quadrilateral base class
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

class Quadrilateral{
protected:
    int side1;
    int side2;
    string quadType;
public:
    Quadrilateral(){}
    ~Quadrilateral(){}
    virtual string getQuadType()=0;
    virtual int getside1()=0;
    virtual int getside2()=0;
    virtual int area()=0;
    virtual int perimeter()=0;
};

class Rectangle: public Quadrilateral{
public:
    Rectangle(string,int, int);
    ~Rectangle(){}
    string getQuadType(){return quadType;}
    int getside1() {return side1;}
    int getside2() {return side2;}
    int area(){return side1*side2;}
    int perimeter(){return (2*side1 + 2*side2);}
};

class Square: public Rectangle{
public:
    Square(string, int);
    ~Square(){}
    string getQuadType(){return quadType;}
};

class Parallelogram:public Quadrilateral{
protected:
    int height;
public:
    Parallelogram(string,int,int,int);
    ~Parallelogram();
    string getQuadType(){return quadType;}
    int getside1() {return side1;}
    int getside2() {return side2;}
    int area(){return side1 * height;}
    int perimeter(){return (2*side1 + 2*side2);}
};


class Rhombus: public Parallelogram{
public:
    Rhombus(string, int, int);
    ~Rhombus(){}
    string getQuadType(){return quadType;}
};

Rectangle::Rectangle(string c, int s1, int s2)
{
    quadType = c;
    side1 = s1;
    side2 = s2;
}

Square::Square(string c, int s1)
:Rectangle(c,s1,s1){}

Parallelogram::Parallelogram(string c, int s1, int s2, int h)
{
    quadType = c;
    side1 = s1;
    side2 = s2;
    height = h;
}

Rhombus::Rhombus(string c,int s1,int h)
:Parallelogram(c,s1,s1,h){}

ostream& operator<<(ostream& out, Quadrilateral*);
Quadrilateral* createQuadrilateralFromString(string);

int main()
{
    const string filename = "ass8data.txt";   // use your filename here
    ifstream fin(filename.c_str());
    if (!fin)
    {
        cerr << "Unable to open " << filename << endl;
        exit(1);
    }
    string buffer;
    Quadrilateral* ptrQuad;
    while (getline(fin,buffer))
    {
        //cout << buffer << endl;

        // Process only valid input
        if (buffer.size() > 1)
        {
            ptrQuad = createQuadrilateralFromString(buffer);
            cout << ptrQuad << endl;
            delete ptrQuad;
        }
    }
    fin.close();
}

ostream& operator<<(ostream&out, Quadrilateral *pquad)
{
    if (pquad->getQuadType() == "rectangle")
    {
        out << "Rectangle: sides " << pquad->getside1() << " and " << pquad->getside2() << " area=" << pquad->area();
        out << " perimeter=" << pquad->perimeter();
        return out;
    }
    else if(pquad->getQuadType() == "square")
    {
        out << "Square: side "<< pquad->getside1() << " area="<< pquad->area();
        out << " perimeter=" << pquad->perimeter();
        return out;
    }
    else if(pquad->getQuadType() == "parallelogram")
    {
        out << "Parallelogram: sides " << pquad->getside1() << " and " << pquad->getside2() << " area=" << pquad->area();
        out << " perimeter=" << pquad->perimeter();
        return out;
    }
    else if(pquad->getQuadType() == "rhombus")
    {
        out << "Rhombus: side "<< pquad->getside1() << " area="<< pquad->area();
        out << " perimeter=" << pquad->perimeter();
        return out;
    }
    else
        return out;
}

Quadrilateral* createQuadrilateralFromString(string buffer)
{
    string tempType, tempside1,tempside2,tempheight;
    int tempside1x,tempside2x,tempheightx;

    istringstream iss(buffer);
    iss >> tempType;

    if (tempType == "rectangle")
    {
        iss >> tempside1;
        iss >> tempside2;

        istringstream buffer(tempside1);
        buffer >> tempside1x;

        istringstream buffer2(tempside2);
        buffer2 >> tempside2x;

        return new Rectangle(tempType,tempside1x,tempside2x);

    }
    else if (tempType == "square")
    {
         iss >> tempside1;
         istringstream buffer(tempside1);
         buffer >> tempside1x;

         return new Square(tempType,tempside1x);
    }
    else if (tempType == "parallelogram")
    {
        iss >> tempside1;
        iss >> tempside2;
        iss >> tempheight;

        istringstream buffer(tempside1);
        buffer >> tempside1x;

        istringstream buffer2(tempside2);
        buffer2 >> tempside2x;

        istringstream buffer3(tempheight);
        buffer3 >> tempheightx;

        return new Parallelogram(tempType,tempside1x,tempside2x,tempheightx);
    }
    else if(tempType == "rhombus")
    {
         iss >> tempside1;
         istringstream buffer(tempside1);
         buffer >> tempside1x;

         iss >> tempheight;
         istringstream buffer2(tempheight);
         buffer2 >> tempheightx;

         return new Rhombus(tempType,tempside1x, tempheightx);
    }
    else

        return 0;
}
