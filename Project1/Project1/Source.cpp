#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

void CallProcedure(string pName) { //sends user string to python function
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

void PrintHistogram() {  //prints the new file into a histogram on screen
	ifstream file;
	string product;
	string number;
	int max = 0;
	int i;
	string histogramChar;

	file.open("frequency.dat");
	if (!file.is_open()) {  //error catch for missing/unreadable file
		cout << "Could not open file." << endl;
	}

	while (!file.fail()) {  //iterates while file is open
		file >> product;
		file >> number;
		max = std::stoi(number);
		histogramChar = "";
		for (i = 1; i <= max; ++i) {
			histogramChar.push_back('$');  //adds char for every sale (1/1 ratio)
		}
		if (file.fail()) {  //break loop if file complete
			break;
		}
		else {   //prints file as histogram
			cout << product << endl << histogramChar<< endl << endl;
		}	
	}

	file.close();  //closes file after use
}

int GetItemFrequency(string proc, string param) { //sends user's searched item to python function
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	printf("Amount Sold Today: %d\n", _PyLong_AsInt(presult));  //print command for user option 2
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;

	return _PyLong_AsInt(presult);
}

void Menu() {  //displays menu options to user
	cout << "   Corner Grocer" << endl;
	cout << "   Enter Selection" << endl;
	cout << "1) All Items Purchased" << endl;
	cout << "2) Search for Item" << endl;
	cout << "3) Print File/Display Histogram" << endl;
	cout << "4) Exit Program" << endl;
}

void UserSelection(string input) {  //validates user input
	string grocery;
	
	while (input != "4") {
		if (input == "1") {
			cout << endl << "The following items were sold today:" << endl;
			CallProcedure("FrequencyList");  //CallProceudre calls Python function "FrequencyList"
			break;
		}
		if (input == "2") {
			cout << "\nEnter item to search:" << endl;
			cout << "Misspellings will result in zero." << endl;
			cin >> grocery;
			GetItemFrequency("FrequencyItem", grocery);  //GetItemFrequency calls Python function "FrequencyItem" and passes user's grocery item
			break;
		}
		if (input == "3") {
			CallProcedure("PrintReceipt");  //CallProcedure calls Python function "PrintReceipt" which consolidates data & creates new  file
			cout << endl << "Here's a visual:" << endl;
			PrintHistogram();  //PrintHistogram iterates over newly created file and displays data in an-on screen histogram
			break;
		}
		if (input == "4") {  //breaks the loop so user can exit
			break;
		}
		else  {  //prints an error for all invalid input and allows user to re-attempt
			cout << endl << "Invalid Input." << endl;
			break;
		}
	}	
	cout << endl;
}

void main() {
	string userInput;

	Menu();
	cin >> userInput;

	while (userInput != "4") {     //continues until user wants to quit
		UserSelection(userInput);  //sends user input to be validated
		Menu();
		cin >> userInput;
	}
	if (userInput == "4") {        //farewell message when user exits
		cout << endl << "Goodbye." << endl;
	}	
}