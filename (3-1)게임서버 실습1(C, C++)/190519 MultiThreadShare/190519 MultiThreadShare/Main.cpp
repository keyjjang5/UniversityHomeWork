#include "TCPServer.h"

int main(int argc, char *argv[])
{
	TCPServer server;

	server.Initialize();

	server.Socket();

	server.Bind();

	server.Listen();

	while (1)
	{
		server.Accept();
		
		server.Print();

		server.MCreateThread(server.ProcessClient);		
	}

	server.End();
}