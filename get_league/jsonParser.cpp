#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <set>
#include <exception>
#include <iostream>
namespace pt = boost::property_tree;

struct team
{
	int position;
	char outcome;
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
	std::set<std::string> teams;
	void load(const std::string &filename);
	void save(const std::string &filename);
};

void league::load(const std::string &filename)
{
	// Create empty property tree object
	pt::ptree tree;

	// Parse the JSON into the property tree
	pt::read_json(filename, tree);

	// Use the throwing version of get to find the competition description
	// If the path cannot be resolved, an exception is thrown
	competition = tree.get<std::string>("leagueTable.competition");
	description = tree.get<std::string>("leagueTable.description");

	// Use get_child to find the node containing the modules, and iterate over
	// its children. If the path cannot be resolved, get_child throws.
	// A C++11 for-range loop would also work.
	BOOST_FOREACH(pt::ptree::value_type &v, tree.get_child("leagueTable.team"))
	{
		std::cout << v.second.data() << std::endl;
		// The data function is used to access the data stored in a node.
		teams.insert(v.second.data());
	}
}

int main()
{
	try
	{
		league lg;
		lg.load("pl1.json");
		std::cout << "Success\n";
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << "\n";
	}

	return 0;
}