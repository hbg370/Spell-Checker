//Hash Table Implementation, reads/hashes a dictionary file into a hash table,
//compares with words of another file, checking for spelling errors. If word from
//file is not included in hash table, it is printed.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include "HashTable.h"

using namespace std;

ifstream & getWord(ifstream & inFile, string & w);

int main()
{
	ifstream dictRead, testRead;
	vector<string> testStrings;
	string fileName, word, cmp;
	HashTbl<string> hashObj;

	dictRead.open("dict.dat");

	if (dictRead.fail())
	{
		cerr << "ERROR OPENING DICTIONARY FILE..." << endl;
		exit(0);
	}

	cout << "Hashing dictionary into table..." << endl << endl;

	while (dictRead >> word)
	{
		hashObj.insert(word);
	}

	dictRead.close();
	cout << "Hash table created successfully!" << endl << endl;

	cout << "Enter file name to be spell checked:";
	cin >> fileName;

	testRead.open(fileName);

	if (testRead.fail())
	{
		cerr << "ERROR OPENING TEST FILE..." << endl;
		exit(1);
	}

	cout << endl << "Misspelled words:" << endl << endl;

	while (testRead)
		while (getWord(testRead, cmp))
		{
			if (hashObj.contains(cmp) == false)
				cout << cmp << endl;
		}


	return 0;

}

ifstream & getWord(ifstream & inFile, string & w)
{
	char c;
	w = "";

	while (inFile.get(c) && !isalpha(c))
		;

	if (inFile.eof())
		return inFile;

	w += tolower(c);

	while (inFile.get(c) && isalpha(c) || isdigit(c))
		w += tolower(c);

	return inFile;

}
