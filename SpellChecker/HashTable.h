#pragma once
//Hash Table Class
#ifndef HASHTABLE_CLASS
#define HASHTABLE_CLASS
#include <vector>
#include <list>

int nextPrime(int n);

template <typename HashedObj>
class HashTbl
{
public:
	explicit HashTbl(int size = 1373) : currentSize{ 0 }
	{
		theLists.resize(1373);
	}

	bool contains(const HashedObj & x)
	{
		auto & whichList = theLists[myhash(x)];
		return find(whichList.begin(), whichList.end(), x) != end(whichList);
	}

	void makeEmpty()
	{
		for (int x = 0 x < theLists.size(); x++)
		{
			theLists[x].clear();
		}
	}

	bool insert(const HashedObj & x)
	{
		auto & whichList = theLists[myhash(x)];
		if (find(whichList.begin(), whichList.end(), x) != whichList.end())
			return false;
		whichList.push_back(x);

		if (++currentSize > (int)theLists.size())
			rehash();

		return true;
	}


	bool remove(const HashedObj & x)
	{
		auto & whichList = theLists[myhash(x)];
		auto itr = find(whichList.begin(), whichList.end(), x);

		if (itr == whichList.end())
			return false;

		whichList.erase(itr);
		--currentSize;
		return true;

	}

private:
	std::vector<std::list<HashedObj> > theLists;
	int currentSize;

	void rehash()
	{
		std::vector<std::list<HashedObj> > prevList = theLists;

		//double the size of the list then check for next prime number
		theLists.resize(nextPrime(2 * theLists.size()));

		for (auto & thisList : theLists)
			thisList.clear();

		currentSize = 0;
		for (auto & thisList : prevList)
			for (auto & x : thisList)
				insert(std::move(x));

	}
	size_t myhash(const HashedObj & x) const
	{
		static hash<HashedObj> hf;
		return hf(x) % theLists.size();
	}

};



#endif