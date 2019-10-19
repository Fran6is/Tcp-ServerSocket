#include "TcpConsoleChat.h"
//#include <thread>

int main(void)
{
	
	//Run this before running the client socket program. You will need two or more running windows of the client socket program
	TcpConsoleChat test{ "0.0.0.0", 5000 };
	int status = test.init();
	if (status == 0)
	{
		test.run();

	}
	else
	{
		std::cerr << status << std::endl;
	}

	

	std::system("pause");
	return 0;
}