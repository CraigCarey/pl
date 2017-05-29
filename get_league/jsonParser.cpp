// TODO: Make league, team proper classes
//use C++11 for loop instead of BOOST_FOREACH
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <vector>
#include <exception>
#include <iostream>

namespace pt = boost::property_tree;

struct team
{
	int position;
	std::string name;
	int played;
	int won;
	int drawn;
	int lost;
	int goalsFor;
	int goalsAgainst;
	int goalDifference;
	int points;
};

struct league
{
	std::string competition;
	std::string description;
	std::vector<team> teams;
	void load(const std::string &filename);
	void save(const std::string &filename);
};

void league::load(const std::string &filename)
{
	// Create empty property tree object
	pt::ptree tree;

	// Parse the JSON into the property tree
	pt::read_json(filename, tree);

	// Use the throwing version of get to find the competition name & description
	// If the path cannot be resolved, an exception is thrown
	competition = tree.get<std::string>("leagueTable.competition");
	description = tree.get<std::string>("leagueTable.description");

	// Use get_child to find the node containing the teams, and iterate over
	// its children. If the path cannot be resolved, get_child throws
	// TODO: C++11 for-range loop would also work
	BOOST_FOREACH(pt::ptree::value_type &v, tree.get_child("leagueTable.team"))
	{
		std::string name;
		pt::ptree subTree;
		std::tie(name, subTree) = v;

		team tm;
		tm.position = subTree.get<int>("position");
		tm.name = subTree.get<std::string>("name");
		tm.played = subTree.get<int>("played");
		tm.won = subTree.get<int>("won");
		tm.drawn = subTree.get<int>("drawn");
		tm.lost = subTree.get<int>("lost");
		tm.goalsFor = subTree.get<int>("for");
		tm.goalsAgainst = subTree.get<int>("against");
		tm.goalDifference = subTree.get<int>("goalDifference");
		tm.points = subTree.get<int>("points");

		teams.push_back(tm);
	}
}

int main()
{
	try
	{
		league lg;
		lg.load("pl.json");

		for (team t : lg.teams)
		{
			std::cout << t.name << std::endl;
		}
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << "\n";
	}

	return 0;
}