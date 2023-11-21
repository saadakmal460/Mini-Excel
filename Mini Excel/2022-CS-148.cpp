#include <iostream>
#include<conio.h>
#include <string>
#include <windows.h>
#include<fstream>
#include<iomanip>
#include<vector>
#include<sstream>
using namespace std;

//2022-CS-148
template <typename T>
class Excel
{
	class Cell
	{

	public:
		T data;
		Cell* up;
		Cell* down;
		Cell* left;
		Cell* right;



		Cell(T val)
		{
			data = val;
			up = nullptr;
			down = nullptr;
			left = nullptr;
			right = nullptr;
		}

	};


public:
	class Iterator
	{
	public:
		Cell* iter;

		Iterator(Cell* curr)
		{
			iter = curr;
		}

		Iterator& operator++() //Pre increment to move right
		{
			iter = iter->right;
			return *this;
		}

		Iterator& operator--() //Pre decrement to move left
		{
			iter = iter->left;
			return *this;
		}

		Iterator& operator++(int) //Post increment to move down
		{
			iter = iter->down;
			return *this;
		}

		Iterator& operator--(int) //Post decrement to move up
		{
			iter = iter->up;
			return *this;
		}

		T& operator*() //Returns data in cell
		{
			return iter->data;
		}

		bool operator==(const Iterator& other) const
		{
			return iter == other.iter;
		}

		bool operator!=(const Iterator& other) const
		{
			return iter != other.iter;
		}


	};


public:

	Cell* current;
	Cell* firstCell;
	vector<T> data;
	bool isColumn;

	Excel()
	{

		current = new Cell("1"); //intializing 1 element
		firstCell = current;



		for (int i = 0; i < 4; i++) //intializing 1st row
		{
			Cell* newCell = new Cell("1");
			current->right = newCell;
			newCell->left = current;
			newCell->up = nullptr;
			current = newCell;
		}



		for (int i = 0; i < 4; i++) //initializing column 5
		{
			Cell* col5 = new Cell("col5");
			current->down = col5;
			col5->up = current;
			col5->right = nullptr;
			current = col5;
		}

		current = firstCell;
		current = current->right->right->right;

		for (int i = 0; i < 4; i++) //initializing column 4
		{
			Cell* col4 = new Cell("col4");
			current->down = col4;
			col4->up = current;
			current = col4;
		}

		current = firstCell;

		for (int i = 0; i < 4; i++) //initializing column 1
		{
			Cell* col1 = new Cell("1");
			current->down = col1;
			col1->up = current;
			col1->left = nullptr;
			current = col1;
		}

		current = firstCell;
		current = current->right;

		for (int i = 0; i < 4; i++) //initializing column 2
		{
			Cell* col2 = new Cell("col2");
			current->down = col2;
			col2->up = current;
			current = col2;
		}

		current = firstCell;
		current = current->right->right;

		for (int i = 0; i < 4; i++) //initializing column 3
		{
			Cell* col3 = new Cell("col3");
			current->down = col3;
			col3->up = current;
			current = col3;
		}

		current = firstCell;

		Cell* conec1 = current;	//conection 1 pointer
		Cell* conec2 = current->right; //connection 2 pointer

		for (int i = 1; i <= 16; i++) //making left and right connections between 1 to 5 columns
		{
			conec1 = conec1->down;
			conec2 = conec2->down;

			conec1->right = conec2;
			conec2->left = conec1;

			if (i % 4 == 0)
			{
				while (conec1->up && conec2->up)
				{
					conec1 = conec1->up;
					conec2 = conec2->up;

				}
				conec1 = conec1->right;
				conec2 = conec2->right;

			}


		}

	}

	//Function 2

	void InsertRowAbove()
	{
		Cell* temp = current; //storing current in temporary pointer
		Cell* row = new Cell("nRow"); //Creating 1st Element of new Row
		Cell* tempRow = row; //Creating a temporary element of row

		while (temp->left)
		{
			temp = temp->left; //moving temporary to the left most
		}

		if (temp->up == nullptr) //Checking if the current is in first row
		{
			//Establishing up and down connections
			row->down = temp;
			temp->up = row;
			row->up = nullptr;

			while (temp->right) //Looping till the row end
			{
				Cell* rowElement = new Cell("nRow"); //Creating element
				tempRow->right = rowElement; //Establishing right connection of previous element
				rowElement->left = tempRow; //Establishing left connection of new Elemnt
				temp = temp->right; //Moving temporary to right
				rowElement->down = temp; //Establishing down connection of new Element
				temp->up = rowElement; //Establishing up connection of the temporary element
				rowElement->up = nullptr;//Nullptr because it will be the first trow
				tempRow = tempRow->right; //Moving temporary row to next element
			}

		}

		//If not the first row
		else
		{
			//Establishing connections
			row->down = temp;
			row->up = temp->up;
			temp->up->down = row;
			temp->up = row;

			while (temp->right) //Looping till the row end
			{
				Cell* rowElement = new Cell("nRow");//Creating element
				tempRow->right = rowElement;//Establishing right connection of previous element
				rowElement->left = tempRow; //Establishing left connection of new Elemnt
				temp = temp->right;//Moving temporary to right
				rowElement->down = temp;//Establishing down connection of new Element
				rowElement->up = temp->up;//Establishing up connection of new Element
				temp->up->down = rowElement;//Changing the down link of element above current
				temp->up = rowElement;//Establishing up connection of the temporary element
				tempRow = tempRow->right; //Moving temporary row to next element

			}
		}
	}

	//Function 3
	void InsertRowBelow()
	{
		Cell* temp = current; //storing current in temporary pointer
		Cell* row = new Cell("nRow"); //Creating 1st Element of new Row
		Cell* tempRow = row; //Creating a temporary element of row

		while (temp->left)
		{
			temp = temp->left; //moving temporary to the left most
		}

		if (temp->down == nullptr) //Checking if the current is in last row
		{
			//Establishing up and down connections
			row->up = temp;
			temp->down = row;
			row->down = nullptr;

			while (temp->right) //Looping till the row end
			{
				Cell* rowElement = new Cell("nRow"); //Creating element
				tempRow->right = rowElement; //Establishing right connection of previous element
				rowElement->left = tempRow; //Establishing left connection of new Elemnt
				temp = temp->right; //Moving temporary to right
				rowElement->up = temp; //Establishing up connection of new Element
				temp->down = rowElement; //Establishing down connection of the temporary element
				rowElement->down = nullptr;//Nullptr because it will be the last trow
				tempRow = tempRow->right; //Moving temporary row to next element
			}
		}

		else //Not the last row
		{
			//Establishing connections
			row->up = temp;
			row->down = temp->down;
			temp->down->up = row;
			temp->down = row;

			while (temp->right) //Looping till the row end
			{
				Cell* rowElement = new Cell("nRow");//Creating element
				tempRow->right = rowElement;//Establishing right connection of previous element
				rowElement->left = tempRow; //Establishing left connection of new Elemnt
				temp = temp->right;//Moving temporary to right
				rowElement->up = temp;//Establishing up connection of new Element
				rowElement->down = temp->down;//Establishing down connection of new Element
				temp->down->up = rowElement;//Changing the up link of element above current
				temp->down = rowElement;//Establishing down connection of the temporary element
				tempRow = tempRow->right; //Moving temporary row to next element

			}

		}


	}

	//Function 4
	void InsertColumnToRight()
	{
		Cell* temp = current; //storing current in temporary pointer
		Cell* col = new Cell("nCol"); //Creating 1st Element of new Col
		Cell* tempCol = col; //Creating a temporary element of col

		while (temp->up)
		{
			temp = temp->up;
		}

		if (temp->right == nullptr)
		{
			col->left = temp;
			temp->right = col;
			col->right = nullptr;

			while (temp->down) //Looping till the row end
			{
				Cell* colElement = new Cell("nCol"); //Creating element
				tempCol->down = colElement; //Establishing down connection of previous element
				colElement->up = tempCol; //Establishing up connection of new Elemnt
				temp = temp->down; //Moving temporary to down
				colElement->left = temp; //Establishing left connection of new Element
				temp->right = colElement; //Establishing right connection of the temporary element
				colElement->right = nullptr;//Nullptr because it will be the last col
				tempCol = tempCol->down; //Moving temporary col to next element
			}
		}

		else
		{
			//Establishing connections
			col->left = temp;
			col->right = temp->right;
			temp->right->left = col;
			temp->right = col;

			while (temp->down) //Looping till the col end
			{
				Cell* colElement = new Cell("ncol");//Creating element
				tempCol->down = colElement;//Establishing down connection of previous element
				colElement->up = tempCol; //Establishing up connection of new Elemnt
				temp = temp->down;//Moving temporary to down

				colElement->left = temp;//Establishing left connection of new Element
				colElement->right = temp->right;//Establishing right connection of new Element
				temp->right->left = colElement;//Changing the left link of element right to current
				temp->right = colElement;//Establishing right connection of the temporary element
				tempCol = tempCol->down; //Moving temporary col to next element

			}

		}

	}

	//Function 5
	void InsertColumnToLeft()
	{
		Cell* temp = current; //storing current in temporary pointer
		Cell* col = new Cell("nCol"); //Creating 1st Element of new Col
		Cell* tempCol = col; //Creating a temporary element of col

		while (temp->up)
		{
			temp = temp->up;
		}

		if (temp->left == nullptr)
		{
			col->right = temp;
			temp->left = col;
			col->left = nullptr;

			while (temp->down) //Looping till the row end
			{
				Cell* colElement = new Cell("nCol"); //Creating element
				tempCol->down = colElement; //Establishing down connection of previous element
				colElement->up = tempCol; //Establishing up connection of new Elemnt
				temp = temp->down; //Moving temporary to down
				colElement->right = temp; //Establishing right connection of new Element
				temp->left = colElement; //Establishing left connection of the temporary element
				colElement->left = nullptr;//Nullptr because it will be the last col
				tempCol = tempCol->down; //Moving temporary col to next element
			}
		}

		else
		{
			//Establishing connections
			col->right = temp;
			col->left = temp->left;
			temp->left->right = col;
			temp->left = col;

			while (temp->down) //Looping till the col end
			{
				Cell* colElement = new Cell("ncol");//Creating element
				tempCol->down = colElement;//Establishing down connection of previous element
				colElement->up = tempCol; //Establishing up connection of new Elemnt
				temp = temp->down;//Moving temporary to down

				colElement->right = temp;//Establishing right connection of new Element
				colElement->left = temp->left;//Establishing left connection of new Element
				temp->left->right = colElement;//Changing the right link of element left to current
				temp->left = colElement;//Establishing left connection of the temporary element
				tempCol = tempCol->down; //Moving temporary col to next element

			}

		}
	}

	//Function 6
	void InsertCellByRightShift()
	{
		Cell* temp = current;
		while (current->right)
		{
			current = current->right;
		}


		InsertColumnToRight();

		while (current != temp) //Shiting data
		{
			current->right->data = current->data;
			current = current->left;
		}

		current->data = " ";
	}

	//Function 7
	void InsertRowByDownShift()
	{
		Cell* temp = current;
		while (current->down)
		{
			current = current->down;
		}

		InsertRowBelow();//Shiting data

		while (current != temp)
		{
			current->down->data = current->data;
			current = current->up;
		}

		current->data = " ";


	}

	//Function 8
	void DeleteCellByLeftShift()
	{
		Cell* temp = current;

		while (current->right)
		{
			current->data = current->right->data;
			current = current->right;
		}

		current = current->left;
		current->right->data = " ";

		if (temp->right != nullptr)
		{
			current = temp;
		}


	}

	//Function 9
	void DeleteCellByUpShift()
	{
		Cell* temp = current;
		while (current->down)
		{
			current->data = current->down->data;
			current = current->down;
		}
		current = current->up;

		current->down->data = " ";

	}

	//Function 10
	void DeleteColumn()
	{
		Cell* col = current; // Pointer to Point current
		Cell* temp = nullptr; //Temporary pointer

		while (col->up) //Moving to the top most
		{
			col = col->up;
		}

		temp = col;

		if (col->left == nullptr && col->right == nullptr) //Checking if it is the only coulmn
		{
			return;
		}

		else if (col->left == nullptr) //If the left most column
		{
			current = current->right; //Moving current to right
			while (col)
			{
				temp->right->left = nullptr; //Changing left connection of right pointer to current
				col = col->down; //Moving down the column
				temp = col;
			}

		}
		else if (current->right == nullptr)
		{
			current = current->left; //Moving current to right
			while (col)
			{
				temp->left->right = nullptr; //Changing left connection of right pointer to current
				col = col->down; //Moving down the column
				temp = col;
			}

		}

		else //Other columns
		{
			current = current->left;  //Moving current to left
			while (col)
			{
				temp->left->right = temp->right; //Establishing connections of left pointers to temp
				temp->right->left = temp->left; //Establishing connections of right pointers to temp
				col = col->down;//Moving down the col;
				temp = col;

			}
		}

	}


	//Function 11
	void DeleteRow()
	{
		Cell* row = current; // Pointer to Point current
		Cell* temp = nullptr; //Temporary pointer

		while (row->left) //Moving to the left most
		{
			row = row->left;
		}

		temp = row;

		if (row->up == nullptr && row->down == nullptr) //Checking if it is the only row
		{
			return;
		}

		else if (row->up == nullptr) //If the up most row
		{
			current = current->down; //Moving current to right
			while (row)
			{
				temp->down->up = nullptr; //Changing the up connection of temp->down pointer
				row = row->right; //Moving down the row
				temp = row;
			}

		}
		else if (row->down == nullptr)
		{
			current = current->up;
			while (row)
			{
				temp->up->down = nullptr; //Changing the up connection of temp->down pointer
				row = row->right; //Moving down the row
				temp = row;
			}
		}

		else //Other rows
		{
			current = current->up;  //Moving current to down
			while (row)
			{
				temp->up->down = temp->down; //Establishing connections of left pointers to temp
				temp->down->up = temp->up; //Establishing connections of right pointers to temp
				row = row->right;//Moving down the row;
				temp = row;

			}
		}
	}

	//Function 12
	void ClearColumn()
	{
		Cell* temp = current;
		while (temp->up)
		{
			temp = temp->up;
		}
		while (temp)
		{
			temp->data = " "; //Clearing just column data Data
			temp = temp->down;
		}

	}

	//Function 13
	void ClearRow()
	{
		Cell* temp = current;
		while (temp->left)
		{
			temp = temp->left;
		}
		while (temp)
		{
			temp->data = " ";//Clearing just row data Data
			temp = temp->right;
		}

	}

	//Function 14
	void GetRangeSum(Cell* start, Cell* end , Cell* destination)
	{
		int sum = 0;
		
		bool flag = FindEnd(end, start); //Finding the direction either to move right or down
		if (flag) //When true move right
		{
			while (start != end->right)
			{
				if (StringIsDigit(start->data))
				{
					sum = sum + stoi(start->data);
					
				}
				start = start->right;
			}
		}

		else //Move down
		{
			while (start != end->down)
			{
				if (StringIsDigit(start -> data))
				{
					sum = sum + stoi(start->data);
					
				}
				start = start->down;
			}
		}
		current = destination;
		destination->data = to_string(sum);

	}

	//Function 15
	void GetRangeAverage(Cell* start, Cell* end , Cell* destination)
	{
		double sum = 0;
		int count = 0;

		bool flag = FindEnd(end, start); //Finding the direction either to move right or down
		if (flag)//When true move right
		{
			while (start != end->right)
			{
				if (StringIsDigit(start->data))
				{
					sum = sum + stoi(start->data);
					count++; //Counting the elements
				}
				start = start->right;
			}
		}
		else
		{
			while (start != end->down)
			{
				if (StringIsDigit(start->data))
				{
					sum = sum + stoi(start->data);
					count++;
				}
				start = start->down;
			}
		}
		sum = sum / count;
		current = destination;
		destination->data = to_string(sum);
	}


	//Function 17
	void PrintSheet()
	{
		for (Iterator it = Start(); it != End(); ++it)
		{
			setColor(32, 0);
			cout << "________________";
			resetColor();
		}
		cout << endl;
		for (Iterator it = Start(); it != End(); it++)
		{
			setColor(32, 0);
			cout << "|";
			resetColor();
			for (Iterator t = it; t != End(); ++t)
			{
				if (t == current)
				{
					setColor(32, 15);
					cout << " " << setw(13) << *t << " ";
					resetColor();

					setColor(32, 0);
					cout << "|";
					resetColor();

				}
				else
				{
					cout << " " << setw(13) << *t << " ";
					setColor(32, 0);
					cout << "|";
					resetColor();

				}
			}
			cout << endl;
			for (Iterator it = Start(); it != End(); ++it)
			{
				setColor(32, 0);
				cout << "________________";

				resetColor();
			}

			cout << endl;
		}
	}


	//Function 18
	void Count(Cell* start, Cell* end , Cell* destination)
	{
		
		int count = 0;
		
		bool flag = FindEnd(end, start); //Finding the direction either to move right or down
		if (flag)//When true move right
		{
			while (start != end->right)
			{
				start = start->right;
				count++; //Counting the elements
			}
		}
		else
		{
			while (start != end->down)
			{
				start = start->down;
				count++;
			}
		}


		current = destination;
		destination->data = to_string(count);

	}


	void Max(Cell* start, Cell* end, Cell* destination)
	{
		int max = 0;

		bool flag = FindEnd(end, start); //Finding the direction either to move right or down
		if (flag)//When true move right
		{
			while (start != end)
			{
				if (StringIsDigit(start->data) && StringIsDigit(start->right->data))
				{
					if (stoi(start->data) > stoi(start->right->data) && start->right != nullptr)
					{
						max = stoi(start->data);
					}
				}
				start = start->right;
				
			}
			
		}
		else
		{
			while (start != end)
			{
				if (StringIsDigit(start->data) && StringIsDigit(start->down->data))
				{
					if (stoi(start->data) > stoi(start->down->data) && start->down != nullptr && StringIsDigit(start->data))
					{
						max = stoi(start->data);
					}
				}

				start = start->down;
				
			}
			
		}

		if (StringIsDigit(end->data))
		{
			if (start == end && stoi(end->data) > max)
			{
				max = stoi(end->data);
			}
		}


		current = destination;
		destination->data = to_string(max);


	}

	void Min(Cell* start, Cell* end, Cell* destination)
	{
		int min = 0;

		bool flag = FindEnd(end, start); //Finding the direction either to move right or down
		if (flag)//When true move right
		{
			while (start != end)
			{
				if (StringIsDigit(start->data) && StringIsDigit(start->right->data))
				{
					if (stoi(start->data) < stoi(start->right->data) && start->right != nullptr)
					{
						min = stoi(start->data);
					}
					
				}
				start = start->right;
			}

		}
		else
		{
			while (start != end)
			{
				if (StringIsDigit(start->data) && StringIsDigit(start->down->data))
				{
					if (stoi(start->data) < stoi(start->down->data) && start->down != nullptr)
					{
						min = stoi(start->data);
					}
				}

				start = start->down;

			}

		}

		if (StringIsDigit(end->data))
		{
			if (start == end && (stoi(end->data) < min))
			{
				min = stoi(end->data);
			}
		}

		current = destination;
		destination->data = to_string(min);

	}

	//Function 19
	void Copy(Cell* start, Cell* end)
	{
		data.clear();
		bool flag = FindEnd(end, start); //Finding the direction either to move right or down
		isColumn = flag;

		if (flag)//When true move right
		{
			while (start != end->right)
			{
				data.push_back(start->data);
				start = start->right;

			}

		}
		else
		{
			while (start != end->down)
			{
				data.push_back(start->data);
				start = start->down;

			}

		}
	}


	//Function 20
	void Cut(Cell* start, Cell* end)
	{

		data.clear();
		bool flag = FindEnd(end, start); //Finding the direction either to move right or down
		isColumn = flag;

		if (flag)//When true move right
		{
			while (start != end->right)
			{
				data.push_back(start->data);
				start->data = "-";
				start = start->right;

			}

		}
		else
		{
			while (start != end->down)
			{
				data.push_back(start->data);
				start->data = "-";
				start = start->down;

			}

		}
		
		

	}

	//Function 21
	void Paste()
	{
		
		if (isColumn) // Finding if column or not , if it is true then row was copied
		{
			for (int i = 0; i < data.size(); i++)
			{
				current->data = data[i]; //copying data

				if (current->right == nullptr && i!=data.size()-1) //Checking if the columns are ended and still their are elements in vector
				{
					Cell* newCell = new Cell("0"); //NewCell
					newCell->left = current; //Left Connection
					current->right = newCell; //right Connection
				}
				else if (current->right == nullptr && i == data.size() - 1) //If the last column and also the last row so do not create an extra cell
				{
					current = current;
				}
				else
				{
					current = current->right;
				}
			}
		}

		else //Checking if column was copied
		{
			for (int i = 0; i < data.size(); i++)
			{
				current->data = data[i];
				if (current->down == nullptr)  //Checking if the columns are ended and still their are elements in vector
				{
					Cell* newCell = new Cell("0");
					newCell->up = current;
					current->down = newCell;
				}
				else if (current->down == nullptr && i == data.size() - 1)//If the last column and also the last row so do not create an extra cell
				{
					current = current;
				}
				else
				{
					current = current->down;
				}
			}
		}
	}



	//Function 23
	void SaveSheet()
	{
		fstream file;
		file.open("sheet.txt", ios::out);

		for (Iterator it = Start(); it != End(); it++)
		{
			bool firstElement = true; //Flag to avoid a comma at very end of row

			for (Iterator t = it; t != End(); ++t)
			{
				if (!firstElement)
				{
					file << ","; 
				}
				else
				{
					firstElement = false;
				}

				file << *t;
			}
			file << endl;
		}

		file.close();
	}

	void LoadSheet()
	{
		string line;
		fstream file;
		file.open("sheet.txt", ios::in);
		
		Cell* temp = nullptr;
		Cell* tempRow = nullptr;

		while (getline(file, line))
		{
			vector<string> values;
			splitString(line, values, ',');

			while (!values.empty())
			{
				Cell* rowElement = new Cell(values.front()); //Creating first element of the row
				values.erase(values.begin());//erasing first value

				if (temp == nullptr && tempRow == nullptr) //Checking if it is first element
				{
					//Setting connections
					temp = rowElement;
					tempRow = temp;
					current = temp;
					firstCell = temp;
				}

				else if (temp == nullptr && tempRow != nullptr)
				{
					temp = rowElement;
					tempRow->down = rowElement;
					rowElement->up = tempRow;
					tempRow = tempRow->down;
				}


				else
				{
					temp->right = rowElement;
					rowElement->left = temp;
					temp = temp->right;
				}
			}
			temp = nullptr;
		}

		Cell* conec1 = firstCell;
		Cell* conec2 = firstCell->down;

		Cell* tempConec1 = conec1;
		Cell* tempConec2 = conec2;

		while (conec2 != nullptr)
		{
			tempConec1 = conec1;
			tempConec2 = conec2;
			while (tempConec2 != nullptr)
			{
				tempConec1->down = tempConec2;
				tempConec2->up = tempConec1;
				tempConec1 = tempConec1->right;
				tempConec2 = tempConec2->right;
			}
			conec1 = conec2;
			conec2 = conec2->down;
		}

		file.close();
	}

	void splitString(const string& inputString, vector<string>& outputVector, char delimiter)
	{
		istringstream tokenStream(inputString);
		string token;

		while (getline(tokenStream, token, delimiter))
		{
			outputVector.push_back(token);
		}
	}

	Iterator Start()
	{
		Cell* temp = current;
		while (temp->left)
		{
			temp = temp->left;
		}
		while (temp->up)
		{
			temp = temp->up;
		}

		return Iterator(temp);
	}

	Iterator End()
	{

		return Iterator(nullptr);

	}


	//Extra Functions
	void MoveCurrentToRight()
	{
		if (current->right)
		{
			current = current->right;//Moving right
		}
	}

	void MoveCurrentToLeft()
	{
		if (current->left)
		{
			current = current->left;//Moving left
		}
	}

	void MoveCurrentToUp()
	{
		if (current->up)
		{
			current = current->up;//Moving up
		}
	}

	void MoveCurrentToDown()
	{
		if (current->down)
		{
			current = current->down;//Moving down
		}
	}

	void ChangeData()
	{
		cout << "Enter data of current: ";

		while (_kbhit()) //Clearing any echo
		{
			_getch();
		}
		cin >> current->data;
	}

	bool FindEnd(Cell* end, Cell* start) //Finding cell
	{
		while (start)
		{
			if (start == end)
			{
				return true;
			}
			start = start->right;
		}

		return false;
	}

	Cell* GetCell(int row , int col)
	{
		Cell* temp = firstCell;
	

		for (int i = 0; i < row; i++)
		{
			if (temp->down != nullptr)
			{
				temp = temp->down;
			}
			else
			{
				break;
			}
		}

		for (int i = 0; i < col; i++)
		{
			if (temp->right != nullptr)
			{
				temp = temp->right;
			}
			else
			{
				break;
			}
		}
		return temp;
	}


	T parsing(string line, int num)
	{
		int count = 1;
		string temp;
		for (int i = 0; i < line.length(); i++)
		{
			if (line[i] == ',')
			{
				count = count + 1;
			}
			else if (count == num)
			{
				temp = temp + line[i];
			}
		}
		return temp;
	}


	int TakeInputForCell(string prompt)
	{
		int cell;
		cout << prompt;
		while (_kbhit()) {
			_getch();
		}
		cin >> cell;
		return cell;
	}

	void Validations(int& row, int& col, int& row2, int& col2)
	{
		if (row == row2)
		{

			while (col2 < col)
			{
				col2 = TakeInputForCell("Error! Enter ending cell column again: ");
			}
		}

		else
		{
			while (row2 < row)
			{
				row2 = TakeInputForCell("Error! Enter ending cell row again: ");
			}

			while (col2 != col)
			{
				col2 = TakeInputForCell("Error! Enter ending cell column again: ");
			}
		}
	}


	void setColor(int foreground, int background) 
	{
		// Set color for text and background
		cout << "\033[" << foreground << ";48;5;" << background << "m";
	}

	void resetColor() 
	{
		cout << "\033[0m";
	}


	bool StringIsDigit(string s)
	{
		
		for (int i = 0; i < s.size(); i++)
		{
			if (!isdigit(s[i]))
			{
				return false;
			}
		}
		return true;
	}


	void Header() {
		setColor(31, 0);
		cout << "\t\t\t\t  __  __  _____  _   _  _____ " << endl;
		cout << "\t\t\t\t |  \\/  ||_   _|| \\ | ||_   _|" << endl;
		cout << "\t\t\t\t | \\  / |  | |  |  \\| |  | |  " << endl;
		cout << "\t\t\t\t | |\\/| |  | |  | . ` |  | |  " << endl;
		cout << "\t\t\t\t | |  | | _| |_ | |\\  | _| |_ " << endl;
		cout << "\t\t\t\t |_|  |_||_____||_| \\_||_____|" << endl << endl << endl;

		cout << "\t\t\t\t  ______ __   __  _____  ______  _      " << endl;
		cout << "\t\t\t\t |  ____|\\ \\ / / / ____||  ____|| |     " << endl;
		cout << "\t\t\t\t | |__    \\ V / | |     | |__   | |     " << endl;
		cout << "\t\t\t\t |  __|    > <  | |     |  __|  | |     " << endl;
		cout << "\t\t\t\t | |____  / . \\ | |____ | |____ | |____ " << endl;
		cout << "\t\t\t\t |______|/_/ \\_\\ \\_____||______||______|" << endl;

		resetColor();
	}

};

int main() {
	Excel<string> e;
	e.Header();
	_getch();
	system("cls");
	e.PrintSheet();

	while (true)
	{
		if (GetAsyncKeyState(VK_LSHIFT) && GetAsyncKeyState('A'))  // Insert column to left 
		{
			e.InsertColumnToLeft();
			system("cls");
			e.PrintSheet();
		}

		if (GetAsyncKeyState(VK_LSHIFT) && GetAsyncKeyState('D')) //Insert column to Right 
		{
			e.InsertColumnToRight();
			system("cls");
			e.PrintSheet();
		}

		if (GetAsyncKeyState(VK_LSHIFT) && GetAsyncKeyState('W')) //adds row above
		{
			e.InsertRowAbove();
			system("cls");
			e.PrintSheet();
		}

		if (GetAsyncKeyState(VK_LSHIFT) && GetAsyncKeyState('S')) //Down arrow adds row down
		{
			e.InsertRowBelow();
			system("cls");
			e.PrintSheet();
		}

		if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState('R')) //Insert cell to right and shifts
		{
			e.InsertCellByRightShift();
			system("cls");
			e.PrintSheet();
		}

		if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState('D'))//Insert cell down and shifts
		{
			e.InsertRowByDownShift();
			system("cls");
			e.PrintSheet();
		}

		if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState('L'))//Delete cell and shifts data left
		{
			e.DeleteCellByLeftShift();
			system("cls");
			e.PrintSheet();
		}

		if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState('U'))//Delete cell and shifts data up
		{
			e.DeleteCellByUpShift();
			system("cls");
			e.PrintSheet();
		}



		if (GetAsyncKeyState(VK_DELETE)) //Delete Key deletes Columns
		{
			e.DeleteColumn();
			system("cls");
			e.PrintSheet();
		}

		if (GetAsyncKeyState(VK_END)) //End key deletes Row
		{
			e.DeleteRow();
			system("cls");
			e.PrintSheet();
		}

		if (GetAsyncKeyState(VK_LSHIFT) && GetAsyncKeyState('C')) //Clears Column data
		{
			e.ClearColumn();
			system("cls");
			e.PrintSheet();
		}

		if (GetAsyncKeyState(VK_LSHIFT) && GetAsyncKeyState('R')) //Clear Row Data
		{
			e.ClearRow();
			system("cls");
			e.PrintSheet();
		}

		
		if (GetAsyncKeyState(VK_LMENU) && GetAsyncKeyState(0xBB))//Range sum
		{
			int row = e.TakeInputForCell("Enter starting cell row: ");
			int col = e.TakeInputForCell("Enter starting cell col: ");

			int row2 = e.TakeInputForCell("Enter ending cell row: ");
			int col2 = e.TakeInputForCell("Enter ending cell col: ");

			e.Validations(row, col, row2, col2);


			int row3 = e.TakeInputForCell("Enter destination cell row: ");
			int col3 = e.TakeInputForCell("Enter destination cell col: ");

			

			e.GetRangeSum(e.GetCell(row, col), e.GetCell(row2, col2), e.GetCell(row3, col3));
			system("cls");
			e.PrintSheet();
			
		}

		if (GetAsyncKeyState(VK_LMENU) && GetAsyncKeyState('H'))//Average
		{
			int row = e.TakeInputForCell("Enter starting cell row: ");
			int col = e.TakeInputForCell("Enter starting cell col: ");

			int row2 = e.TakeInputForCell("Enter ending cell row: ");
			int col2 = e.TakeInputForCell("Enter ending cell col: ");


			e.Validations(row, col, row2, col2);


			int row3 = e.TakeInputForCell("Enter destination cell row: ");
			int col3 = e.TakeInputForCell("Enter destination cell col: ");

			
			e.GetRangeAverage(e.GetCell(row, col), e.GetCell(row2, col2), e.GetCell(row3, col3));
			system("cls");
			e.PrintSheet();

		}

		if (GetAsyncKeyState(VK_LMENU) && GetAsyncKeyState('G'))//Count
		{
			int row = e.TakeInputForCell("Enter starting cell row: ");
			int col = e.TakeInputForCell("Enter starting cell col: ");

			int row2 = e.TakeInputForCell("Enter ending cell row: ");
			int col2 = e.TakeInputForCell("Enter ending cell col: ");


			e.Validations(row, col, row2, col2);

			int row3 = e.TakeInputForCell("Enter destination cell row: ");
			int col3 = e.TakeInputForCell("Enter destination cell col: ");

			

			e.Count(e.GetCell(row, col), e.GetCell(row2, col2), e.GetCell(row3, col3));
			system("cls");
			e.PrintSheet();

		}

		if (GetAsyncKeyState(VK_LMENU) && GetAsyncKeyState('M'))//Max
		{
			int row = e.TakeInputForCell("Enter starting cell row: ");
			int col = e.TakeInputForCell("Enter starting cell col: ");

			int row2 = e.TakeInputForCell("Enter ending cell row: ");
			int col2 = e.TakeInputForCell("Enter ending cell col: ");

			e.Validations(row, col, row2, col2);

			int row3 = e.TakeInputForCell("Enter destination cell row: ");
			int col3 = e.TakeInputForCell("Enter destination cell col: ");

			

			e.Max(e.GetCell(row, col), e.GetCell(row2, col2), e.GetCell(row3, col3));
			system("cls");
			e.PrintSheet();

		}

		if (GetAsyncKeyState(VK_LMENU) && GetAsyncKeyState('N'))//Min
		{
			int row = e.TakeInputForCell("Enter starting cell row: ");
			int col = e.TakeInputForCell("Enter starting cell col: ");

			int row2 = e.TakeInputForCell("Enter ending cell row: ");
			int col2 = e.TakeInputForCell("Enter ending cell col: ");

			e.Validations(row, col, row2, col2);

			int row3 = e.TakeInputForCell("Enter destination cell row: ");
			int col3 = e.TakeInputForCell("Enter destination cell col: ");

			

			e.Min(e.GetCell(row, col), e.GetCell(row2, col2) , e.GetCell(row3,col3));
			system("cls");
			e.PrintSheet();

		}


		if (GetAsyncKeyState(VK_LMENU) && GetAsyncKeyState('J')) //Copy
		{
			int row = e.TakeInputForCell("Enter starting cell row: ");
			int col = e.TakeInputForCell("Enter starting cell col: ");

			int row2 = e.TakeInputForCell("Enter ending cell row: ");
			int col2 = e.TakeInputForCell("Enter ending cell col: ");

			e.Validations(row, col, row2, col2);
			e.Copy(e.GetCell(row, col), e.GetCell(row2, col2));
			system("cls");
			e.PrintSheet();
		}


		if (GetAsyncKeyState(VK_LMENU) && GetAsyncKeyState('X')) //Cut
		{
			int row = e.TakeInputForCell("Enter starting cell row: ");
			int col = e.TakeInputForCell("Enter starting cell col: ");
			
			int row2 = e.TakeInputForCell("Enter ending cell row: ");
			int col2 = e.TakeInputForCell("Enter ending cell col: ");

			e.Validations(row, col, row2, col2);
			e.Cut(e.GetCell(row , col), e.GetCell(row2 , col2));
			system("cls");
			e.PrintSheet();
		}


		if (GetAsyncKeyState(VK_LMENU) && GetAsyncKeyState('V')) //Cut
		{
			
			e.Paste();
			system("cls");
			e.PrintSheet();
		}


		if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState('S'))//Saves Data
		{
			e.SaveSheet();
			system("cls");
			e.PrintSheet();
		}

		if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState('K'))//Load data
		{
			e.LoadSheet();
			system("cls");
			e.PrintSheet();
		}


		if (GetAsyncKeyState(VK_RIGHT)) //Move current right
		{
			e.MoveCurrentToRight();
			system("cls");
			e.PrintSheet();
		}

		if (GetAsyncKeyState(VK_LEFT)) //Move current left
		{
			e.MoveCurrentToLeft();
			system("cls");
			e.PrintSheet();
		}

		if (GetAsyncKeyState(VK_UP)) //Move current up
		{
			e.MoveCurrentToUp();
			system("cls");
			e.PrintSheet();
		}

		if (GetAsyncKeyState(VK_DOWN)) //Move current down
		{
			e.MoveCurrentToDown();
			system("cls");
			e.PrintSheet();
		}

		if (GetAsyncKeyState(VK_LSHIFT) && GetAsyncKeyState('E')) //Take input
		{
			e.ChangeData();
			system("cls");
			e.PrintSheet();
			Sleep(100);
		}

		


		if (GetAsyncKeyState(VK_ESCAPE)) //Exits the program
		{
			break;
		}


		Sleep(100);
	}

}

