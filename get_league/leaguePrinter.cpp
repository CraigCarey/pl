// TODO:  Timestamp output file
//        Check output file age before updating
//        Format table properly
//        getopt other leagues

#include <iostream>

#include "getRequest.h"
#include "league.h"

int main(int argc, char* argv[])
{
	const std::string HostUrl = "www.footballwebpages.co.uk";
	const std::string RequestLeague = "/league.json?comp=1";
	const std::string FilenameOut = "lg.json";

	try
	{
		// Execute get request
		std::ostringstream response;
		if (getRequest(HostUrl, RequestLeague, response))
		{
			std::cerr << "Failed to retrieve league data" << std::endl;
			return 1;
		}

		// Open file for writing json response
		std::ofstream outfile(FilenameOut);
		if(!outfile.is_open())
		{
			std::cerr << "Couldn't open '" << FilenameOut << "'" << std::endl;
			return 1;
		}

		// Write response to file
		outfile << response.str() << std::endl;
		outfile.close();

		// Parse League data from json file
		League lg;
		lg.load(FilenameOut);

		// Table header
		std::cout << "\nPosition\tTeam\n----------------------------------\n";

		// Print league data
		for (Team t : lg.teams)
		{
			std::cout << t.position << "\t\t" << t.name << std::endl;
		}

		std::cout << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << "\n";
		return 1;
	}

	return 0;
}