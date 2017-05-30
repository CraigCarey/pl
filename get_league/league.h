#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "team.h"

namespace pt = boost::property_tree;

class League
{
public:
	std::string competition;
	std::string description;
	std::vector<Team> teams;
	void load(const std::string &filename);
};

void League::load(const std::string &filename)
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
	pt::ptree children = tree.get_child("leagueTable.team");
	for (const auto& v : children)
	{
		std::string name;
		pt::ptree subTree;
		std::tie(name, subTree) = v;

		Team tm;
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