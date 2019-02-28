#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include<interpreter.hpp>

using namespace std;

int main(int argc,const char* argv[])
{
	std::vector<string> params;

	while(argc--)
		{
			if(strcmp(argv[argc] ,"bxx") != 0)params.push_back(argv[argc]);
		}

	interpreter bpp(params);
	
	if(!bpp.parse())
	{
		std::cout<<"Interpreter quit because of an error."<<std::endl;
		return 1;
	}

	return 0;
}