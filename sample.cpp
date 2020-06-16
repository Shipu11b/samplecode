/*
 COURSE ID:             CSC 331
 FULL NAME:             Shipu Mohammed Aashiq
 SECTION:               0900
 FILE NAME:             csc331-0900_aashiq_prog4.cpp
 ASSIGNMENT NUMBER:     4
 DUE DATE:              12/2/2019
 PROGRAM PURPOSE:       work order using heap
 */

#include <iostream>
#include <string>
#include<algorithm>

using namespace std;





struct transcation
{
	string order, custname;
	int ordernum, priornum;
	static int numorder;
	
	

	transcation(string name, string year, char warranty) 
	{
		this->custname = name;
		numorder++;
		ordernum = numorder;
		priornum = calcpriornum(warranty, year);
		getorder();

		

	}
	int calcpriornum(char wty, string y)
	{
		if (wty == 'y')
			return 1;

		const int currentyear = 2019;
		int year = stoi(y);
		if (currentyear - year < 6)
			return 2;
		return 3;
	}

	void getorder()

	{
		order += to_string(priornum) + "-" + to_string(ordernum) + custname;
	}
};
int transcation::numorder = 0;

struct heaptype
{
public:
	void push(transcation*);
	void pop();
	int getcount();
private:
	int count = 0;
	int EOL = 0;
	transcation* heap[10];
	int pi;
	int c1i;
	int c2i;
	

};



void heaptype::push(transcation* tran)
{
	if (count == 10) 
	{
		cout << "Error: Queue is full" << endl;
		return;
	}

	heap[EOL] = tran;
	int c1 = EOL;
	EOL++;
	count++;

	while (c1)
	{
		pi = (c1 - 1) / 2;
		if (heap[pi]->priornum > tran->priornum)
		{
			transcation* t = heap[pi];
			heap[pi] = tran;
			heap[pi] = t;

		}
		else
			return;
		c1 = pi;
	}
}


void heaptype::pop()
{
	if (count == 0)
		cout << "Heap is empty" << endl;
	else if (count == 1)
	{
		cout << heap[0]->custname << endl;
		count = 0; EOL = 0;
		heap[0] = 0;
	}
	else if (count == 2) 
	{
		cout << heap[0]->custname << endl;
		count--; EOL--;
		heap[0] = heap[1]; heap[1] = 0;
	}
	else 
	{
		cout << heap[0]->custname << endl;
		count--; EOL--;
		heap[0] = heap[EOL]; heap[EOL] = 0;

		int ni = 0;

		 c2i = (2 * ni) + 1, c1i = (2 * ni) + 2;

		do
		{
			if (heap[c1i] != NULL)
			{
				if ((heap[ni]->priornum > heap[c2i]->priornum) ||
					(heap[ni]->priornum > heap[c1i]->priornum))
				{
					if (heap[c2i]->priornum < heap[c1i]->priornum)
					{
						transcation* t = heap[ni];
						heap[ni] = heap[c2i];
						heap[c2i] = t;
						ni = c2i;
					}
					else if (heap[c2i]->priornum == heap[c1i]->priornum)
					{
						if (heap[c2i]->ordernum < heap[c1i]->ordernum)
						{
							transcation* t = heap[ni];
							heap[ni] = heap[c2i];
							heap[c2i] = t;
							ni = c2i;
						}
						else
						{
							transcation* t = heap[ni];
							heap[ni] = heap[c1i];
							heap[c1i] = t;
							ni = c1i;
						}


					}
					else
					{
						transcation* t = heap[ni];
						heap[ni] = heap[c1i];
						heap[c1i] = t;
						ni = c1i;
					}

					c2i = (2 * ni) + 1; c1i = (2 * ni) + 2;

				}

			}
			else 
			{

				if (heap[ni]->priornum > heap[c2i]->priornum)
				{
					transcation* t = heap[ni];
					heap[ni] = heap[c2i];
					heap[c2i] = t;
					ni = c2i;
				}
				c2i = (2 * ni) + 1; c1i = (2 * ni) + 2;
			}
		} while (c1i < EOL);

	}
}
int heaptype::getcount()
{
	return count;
}

bool displayinput(string, char&, string&, string&);
bool checkyear(string& y)
{
	if (y.length() != 6)
		return false;
	else if (*(y.begin()) != '-' || *(y.end() - 1) != '-')
		return false;
	else 
	{
		string yearnum(y.begin() + 1, y.end() - 1);

		for (int i = 0; i < yearnum.length(); i++)
		{
			char num = yearnum[i];
			if (num < 48 || num > 57)
			{
				return false;
			}
		}
		y = yearnum;
	}
	return true;
}

bool checkwarty(char  e)
{
	return e == 'y' || e == 'n';
}

void errormsg()
{
	cout << "Invalid input" << endl;
}

int main()
{


	string orders;

	heaptype warty;
	do
	{
		cout << " input: "; getline(cin, orders);
		if (orders != "end-of-file")
		{
			if (orders == "service")
			{
				cout << "serviced: ";
				warty.pop();
			}
			else
			{
				string year, name;
				char warranty;
				if (displayinput(orders, warranty, year, name))
				{
					transcation* w = new transcation(name, year, warranty);
					warty.push(w);
				}
			}
		}
		else
		{
			cout << "there is " << warty.getcount() << "remaining repair orders in the queue " << endl;
		}
	} while (orders != "end-of-file");



}
bool displayinput(string w, char& warranty, string& year, string& name)
{

	warranty = *(w.end() - 1); //Last charater is warrantys

	if (!checkwarty(warranty)) 
	{ //Check warranty
		errormsg();
		return false;
	}

	year = string(w.end() - 7, w.end() - 1); //get year from input
	if (!checkyear(year))
	{
		errormsg();
		return false;
	}

	name = string(w.begin(), w.end() - 7); //The rest of the charaters is the name
	return true;
}









