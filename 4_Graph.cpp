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
#include <queue>
#include <limits>

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

bool person_is_seller(const string &str)
{
	return str.find("n") != string::npos;
}

bool search(const std::map<string, std::list<string>> &graph, const string &name)
{
	std::queue<string> search_que;
	std::for_each(graph.at(name).cbegin(), graph.at(name).cend(), [&search_que](auto val) {search_que.push(val); });

	std::vector<string> searched;

	while (!search_que.empty())
	{
		auto person = search_que.front();
		search_que.pop();

		if (std::find(searched.cbegin(), searched.cend(), person) != searched.cend())
			continue;

		if (person_is_seller(person))
		{
			cout << person << " is finded!\n";
			return true;
		}
		else
		{
			std::for_each(graph.at(person).cbegin(), graph.at(person).cend(), [&search_que](auto val) {search_que.push(val); });
			searched.push_back(person);
		}
	}

	return false;
}

string find_lowest_cost_node(const std::map<string, size_t> &costs, const vector<string> &processed)
{
	auto lowest_coast = std::numeric_limits<size_t>::max();

	string lowest_coast_node;

	for (auto &node : costs)
	{
		if (node.second < lowest_coast && std::find(processed.begin(), processed.end(), node.first) == processed.end())
		{
			lowest_coast = node.second;
			lowest_coast_node = node.first;
		}
	}

	return lowest_coast_node;
}

void weighted_search(const std::map<string, map<string, size_t>> &weighted_graph,
	std::map<string, size_t> &costs, std::map<string, string> &parents, vector<string> &processed)
{
	auto node = find_lowest_cost_node(costs, processed);

	while (!node.empty())
	{
		auto cost = costs[node];
		auto neighbors = weighted_graph.at(node);

		for (auto neightbor : neighbors)
		{
			auto new_cost = cost + neightbor.second;

			if (costs[neightbor.first] > new_cost)
			{
				costs[neightbor.first] = new_cost;
				parents[neightbor.first] = node;
			}
		}
		processed.push_back(node);
		node = find_lowest_cost_node(costs, processed);
	}
}

int main()
{
	std::map<string, std::list<string>> graph;

	graph["you"] = {"alice", "bob", "claire"};
	graph["bob"] = { "anuj", "peggy" };
	graph["alice"] = { "peggy" };
	graph["claire"] = { "tom", "jonny" };
	graph["peggy"] = { };
	graph["tom"] = { };
	graph["jonny"] = { };

	cout << search(graph, "you") << endl;

	std::map<string, map<string, size_t>> weighted_graph;

	auto &m = weighted_graph["start"];
	m.insert(std::make_pair<string, size_t>("a", 6));
	m.insert(std::make_pair<string, size_t>("b", 2));

	weighted_graph["a"].insert(std::make_pair<string, size_t>("fin", 1));

	weighted_graph["b"].insert(std::make_pair<string, size_t>("a", 3));
	weighted_graph["b"].insert(std::make_pair<string, size_t>("fin", 5));

	weighted_graph["fin"];

	decltype(weighted_graph)::mapped_type costs;
	costs["a"] = 6;
	costs["b"] = 2;
	costs["fin"] = std::numeric_limits<size_t>::max();

	std::map<string, string> parents;
	parents["a"] = "start";
	parents["b"] = "start";
	parents["fin"];

	vector<string> processed;

	weighted_search(weighted_graph, costs, parents, processed);

	cout << "press any key to exit\n";
	_getch();

	return 0;
}