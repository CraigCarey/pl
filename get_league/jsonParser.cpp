#include "league.h"

int main(int argc, char * argv[])
{
	try
	{
		League lg;
		lg.load("pl.json");

		for (Team t : lg.teams)
		{
			std::cout << t.name << std::endl;
		}
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << "\n";
		return 1;
	}

	return 0;
}