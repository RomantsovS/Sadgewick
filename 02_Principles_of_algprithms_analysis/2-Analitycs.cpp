#include <iostream>
#include <list>
#include <string>
#include <forward_list>
#include <algorithm>
#include <functional>
#include <iterator>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <regex>
#include <random>
#include <conio.h>
#include <valarray>
#include <typeinfo>
#include <cctype>
#include <array>
#include <numeric>
#include <math.h>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::list;
using std::forward_list;
using std::map;
using std::set;

bool f(const string &s, const vector<string> &svec)
{
	string::size_type pos = 0;

	bool finded = true;

	while (pos != s.size() && finded)
	{
		for (auto iter = svec.begin(); iter != svec.end(); ++iter)
		{
			auto curPos = pos;

			for (auto ch : *iter)
			{
				if (ch != s[curPos++])
				{
					finded = false;
					break;
				}
			}

			if (finded)
			{
				pos = curPos;
				break;
			}
			else if (iter == svec.end() - 1)
				return false;
			else
			{
				finded = true;
			}
		}
	}

	return finded;
}

struct TreeNode
{
	TreeNode()
	{
		for (size_t i = 0; i != 10; ++i)
			ptrs[i] = nullptr;
	}

	~TreeNode()
	{
		delete val;
		
		for (size_t i = 0; i != 10; ++i)
			delete ptrs[i];
	}

	char *val = nullptr;
	TreeNode *ptrs[10];
	bool lastNode = false;

	static char firstVal;
};

char TreeNode::firstVal = 'A';

void generateTree(TreeNode *node, string::const_iterator begin, string::const_iterator end)
{
	if (!node->val)
	{
		if (!node->ptrs[*begin - TreeNode::firstVal])
		{
			node->ptrs[*begin - TreeNode::firstVal] = new TreeNode;
			node->ptrs[*begin - TreeNode::firstVal]->val = new char(*begin);
		}

		return generateTree(node->ptrs[*begin - TreeNode::firstVal], begin, end);
	}

	if (++begin == end)
	{
		node->lastNode = true;
		return;
	}

	if (node->lastNode)
	{
		throw std::invalid_argument("doesn't prefix-code");
	}

	if (!node->ptrs[*begin - TreeNode::firstVal])
	{
		node->ptrs[*begin - TreeNode::firstVal] = new TreeNode;
		node->ptrs[*begin - TreeNode::firstVal]->val = new char(*begin);
	}

	return generateTree(node->ptrs[*begin - TreeNode::firstVal], begin, end);
}

bool check(string::const_iterator begin, string::const_iterator end, TreeNode * const root)
{
	TreeNode *curNode = root;

	while(begin != end)
	{
		if (curNode->lastNode)
			curNode = root;

		if (!curNode->ptrs[*begin - TreeNode::firstVal])
			return false;
		else
		{
			curNode = curNode->ptrs[*begin - TreeNode::firstVal];
			++begin;
		}
	}

	if (curNode->lastNode)
		curNode = root;

	return curNode == root;
}

bool f2(const string &s, vector<string> &svec)
{
	TreeNode *root;

	root = new TreeNode;
	
	string::size_type pos = 0;

	string::const_iterator sIter = s.begin();

	for (auto iter = svec.begin(); iter != svec.end(); ++iter)
	{
		generateTree(root, iter->begin(), iter->end());
	}

	bool res = check(s.begin(), s.end(), root);

	delete root;

	return res;
}

int main()
{
	const size_t numLetters = 4;

	std::default_random_engine rand_eng;
	std::uniform_int_distribution<unsigned> u_ch(TreeNode::firstVal, TreeNode::firstVal + numLetters - 1);
	//std::uniform_int_distribution<unsigned> u_width(1, 2);

	size_t N = static_cast<size_t>(pow(10, 4));

	string s(N, 0);

	for (size_t i = 0; i != N; ++i)
	{
		s[i] = u_ch(rand_eng);
	}

	//cout << s << endl;

	vector<string> svec;

	cout << "Enter sub-strings: \n";

	string tmp;

	do
	{
		string tmp;

		size_t width = 2;// u_width(rand_eng);

		for(size_t i = 0; i != width; ++i)
			tmp.push_back(u_ch(rand_eng));

		if (std::find(svec.begin(), svec.end(), tmp) == svec.end())
		{
			//cout << tmp << endl;

			svec.push_back(tmp);
		}
		else
			continue;

		cout << "trying words: " << svec.size() << endl;

	} while (!f(s, svec));

	auto startTime = clock();

	cout << "f: " << f(s, svec) << endl;

	auto endTime = clock();

	cout << "Elasped time: " << endTime - startTime << endl;

	startTime = clock();

	cout << "f2: " << f2(s, svec) << endl;

	endTime = clock();

	cout << "Elasped time: " << endTime - startTime << endl;

	cout << "press any key to exit\n";
	_getch();

	return 0;
}