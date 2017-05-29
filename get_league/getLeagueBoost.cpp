#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int getRequest(std::string hostStr, std::string requestStr, std::string &responseStr)
{
	try
	{
		// core I/O functionality for asynchronous I/O objects, including tcp::socket
		boost::asio::io_service ioService;

		// Get a list of endpoints corresponding to the server name
		tcp::resolver resolver(ioService);
		tcp::resolver::query query(hostStr, "http");
		tcp::resolver::iterator endpointIterator = resolver.resolve(query);

		// Try each endpoint until we successfully establish a connection
		tcp::socket socket(ioService);
		boost::asio::connect(socket, endpointIterator);

		// Form the request. We specify the "Connection: close" header so that the
		// server will close the socket after transmitting the response. This will
		// allow us to treat all data up until the EOF as the content
		boost::asio::streambuf request;
		std::ostream request_stream(&request);
		request_stream << "GET " << requestStr << " HTTP/1.1\r\n";
		request_stream << "Host: " << hostStr << "\r\n";
		request_stream << "Accept: */*\r\n";
		request_stream << "Connection: close\r\n\r\n";

		// Send the request
		boost::asio::write(socket, request);

		// Read the response status line. The response streambuf will automatically
		// grow to accommodate the entire line. The growth may be limited by passing
		// a maximum size to the streambuf constructor
		boost::asio::streambuf response;
		boost::asio::read_until(socket, response, "\r\n");

		// Check that response is OK
		std::istream responseStream(&response);
		std::string httpVersion;
		responseStream >> httpVersion;
		unsigned int statusCode;
		responseStream >> statusCode;
		std::string statusMessage;
		std::getline(responseStream, statusMessage);

		if (!responseStream || httpVersion.substr(0, 5) != "HTTP/")
		{
			std::cerr << "Invalid response\n";
			return 1;
		}

		if (statusCode != 200)
		{
			std::cerr << "Response returned with status code " << statusCode << "\n";
			return 1;
		}

		// Read the response headers, which are terminated by a blank line
		boost::asio::read_until(socket, response, "\r\n\r\n");

		// Consume the response headers
		std::string header;
		while (std::getline(responseStream, header) && header != "\r")
		{
			// std::cout << header << "\n";
		}
		
		std::ostringstream responseStrStream;

		// Write whatever content we already have to stringStream
		if (response.size() > 0)
		{
			responseStrStream << &response;
		}

		// Read until EOF, writing data to stringStream as we go
		boost::system::error_code error;

		while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error))
		{
			responseStrStream << &response;
		}

		if (error != boost::asio::error::eof)
		{
			throw boost::system::system_error(error);
		}

		responseStr = responseStrStream.str();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
		return 1;
	}

	return 0;
}

int main(int argc, char* argv[])
{

	const std::string HostUrl = "www.footballwebpages.co.uk";
	const std::string RequestLeague = "/league.json?comp=1";

	std::string plString;

	if (getRequest(HostUrl, RequestLeague, plString))
	{
		std::cerr << "Failed to retrieve league data" << std::endl;
		return 1;
	}

	std::cout << plString;

	return 0;
}