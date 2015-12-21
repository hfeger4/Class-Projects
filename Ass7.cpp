/*

CodeBlocks
Assignment 7

This is an example in reference counting and a linked list

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

class Node
{
    int      data;
    Node*    next;
public:
    int counter;
    Node(int d = 0,Node* n = 0,int c = 1) : data(d), next(n),counter(c) { }
friend class List;
};

class List
{
    Node*    top;
public:
    List();
    ~List();
    void  push(int item);
    int   pop();
    int   get_top() const;
    void  print() const;
    void  sorting();
    bool  remove(int item);
    Node* find(int item);
};

List::List() : top(0)
{
}

List::~List()
{
    Node* temp = top;
    while (temp != 0)
    {
        top = top -> next;
        delete temp;
        temp = top;
    }
}

void List::push(int item)
{
    Node* temp = new Node(item, top);
    if (!temp)
    {
        cerr << "Unable to allocate memory for a Node.  Exiting ...\n";
        exit(-1);
    }
    else
    {
        top = temp;
    }
}

int List::pop()
{
    Node* temp = top;
    top = top->next;
    int value = temp->data;
    delete temp;
    return value;
}

int List::get_top() const
{
    return top -> data;
}


void List::print() const
{
    Node* temp = top;
    while (temp != 0)
    {
        cout << setfill('0') << setw(4) << temp -> data;
        cout << "       "<< temp->counter << endl;
        temp = temp -> next;
    }
    cout << endl;
}


void List::sorting()
{
	Node * temp = top;
	int tempdata;
	int tempCounter;
	int theCount = 0;
	while (temp)
	{
		temp = temp->next;
		theCount++;
	}
	temp = top;

	for (int j=0; j<theCount; j++)
	{
		while ((temp->next)!=0)
		{
			if (temp->data > temp->next->data)
			{
				tempdata = temp->data;
				temp->data = temp->next->data;
				temp->next->data = tempdata;

				tempCounter = temp->counter;
				temp->counter = temp->next->counter;
				temp->next->counter = tempCounter;
				temp = temp->next;
			}
			else
				temp = temp->next;
		}
		temp = top;
	}
}

Node* List::find(int item)
{
    Node* temp = top;
    while (temp != 0)
    {
        if (temp->data == item) return temp;
        temp = temp -> next;
    }
    return 0;
}

bool List::remove(int item)
{
    if (!find(item))
    {
        cerr << item << " is not in the List\n";
        return false;
    }
    Node* temp1 = top;
    Node* temp2;
    if (top->data == item)
    {
        top = top -> next;
        delete temp1;
        return true;
    }
    while (temp1->next->data != item)
    {
        temp1 = temp1 -> next;
    }
    temp2 = temp1 -> next;
    temp1->next = temp2 -> next;
    delete temp2;
    return true;
}

int main (void)
{
    List L;
    string everything;
    int count = 0;

    ifstream fin;
    fin.open("inputFile.txt");
    if(!fin){
        cerr << "File not found\n";
        exit(1);
        }

    while (getline(fin,everything))
    {
        count ++; //Keep a line count

        istringstream iss(everything); //Split data into two strings
        string transaction;
        string inventory;
        iss >> transaction;
        iss >> inventory;

        string s = inventory;   //Convert inventory to int
        int xinventory = 0;
        stringstream convert(s);
        convert >> xinventory;

       // cout << transaction;
       // cout << " " << inventory << endl;

        if (transaction == "add")
        {
            //cout << "Added here" << endl;
            if (L.find(xinventory))
            {
                L.find(xinventory)->counter++;
               // cout << "The amount in inventory is: " << L.find(xinventory)->counter << endl;
            }
            else
            {
            L.push(xinventory);
            }
        }
        else if (transaction == "subtract")
        {
            //cout << "Subtracted here" << endl;
            L.find(xinventory)->counter--;
          //  cout << "The amount in inventory is: " << L.find(xinventory)->counter << endl;

            if ((L.find(xinventory)->counter) == 0)
            {
                L.remove(xinventory);
            }
        }
        else if (transaction == "print")
        {
            cout << "Item " << " Quantity"<< endl;
            L.sorting();
            L.print();
        }
        else if (transaction == "")
        {
        }
        else
        {
            cout << "Bad transaction: " << transaction << " in line #"<< count << endl;
            cout << endl;
        }
    }
    fin.close();
}
