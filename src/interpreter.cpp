#include <interpreter.hpp>

#include <iostream>
#include <algorithm>
#include <fstream>

bool interpreter::isVerbose()const
{
	return verbose && !silent;
}
bool interpreter::isSilent()const
{
	return silent;
}

interpreter::interpreter(const std::vector<std::string> &v)
{
	params = v;
	verbose = false;
	silent = false;
	fileToOpen = "";
	memSize = 300;
	pointer = 0;

	if(parseOpts() == false)
	{
		if(!isSilent())std::cout<<"bxx: Some options were invalid, and have been ignored"<<std::endl;
	}

	if(isVerbose())
	{
	std::cout<<"bxx: BrainfuckExtended interpreter! "<<std::endl;
	std::cout<<"###"<<std::endl;
	std::cout<<"bxx started with options: \n";
	for(const auto i : params)std::cout<<i<<std::endl;
	std::cout<<"###"<<std::endl;
	}

}
bool interpreter::parseOpts()
{
	bool returner = true;
	std::reverse(params.begin(), params.end());

	for(const auto i: params)
	{
		std::string optsym = i.substr(0,2);

		if(optsym == "-v"){
			if(isVerbose()){
				std::cout<<"bxx: Verbose output requested. ";
				if(silent)std::cout<<"Silent is already chosen. Disabling verbose.";
				std::cout<<std::endl;
			}
			verbose = true;
		}else if(optsym == "-s"){
			if(isVerbose()){
				std::cout<<"bxx: Silent output requested. ";
				if(verbose)std::cout<<"Verbose option is disabled. Will be silent from now on.";
				std::cout<<std::endl;
			}
			silent = true;
		}else if(optsym == "-v2"){

		}else if(optsym == "-b"){
			memSize = std::stoi(i.substr(2));
			if(isVerbose()){
				std::cout<<"Set memory to "<<memSize<<" blocks"<<std::endl;
			}
		}else if(optsym == "-p"){
			pointer = std::stoi(i.substr(2));
			if(isVerbose()){
				std::cout<<"Set memory pointer to block number "<<pointer<<" "<<std::endl;
			}
		}else if(optsym == "-f"){
			fileToOpen = i.substr(2);
			if(isVerbose())std::cout<<"bxx: Will read file: "<<fileToOpen<<std::endl;

		}else{
			returner = false;
			if(isVerbose())std::cout<<"bxx: Unrecogized option. Skipping :"<<i<<std::endl;
		}

	}

	return returner;
}
bool interpreter::parse(void)
{
	std::ifstream fs;

	fs.open(fileToOpen.c_str(), std::fstream::in);

	if(!fs.good())
	{
		if(!isSilent())std::cout<<"bxx: Fatal - cannot open file."<<std::endl;
		return false;
	}
	fckMemory = new int [memSize];
	for(int i=0; i<memSize; i++)fckMemory[i] = 0;

	if(isVerbose())std::cout<<"bxx: allocated "<<memSize<<" memory blocks."<<std::endl;
	

	std::string str;
	fs.seekg(0, std::ios::end);   
	str.reserve(fs.tellg());
	fs.seekg(0, std::ios::beg);

	str.assign( ( std::istreambuf_iterator<char>(fs) ), std::istreambuf_iterator<char>() );

	if(isVerbose())std::cout<<"bxx: executing: "<<fileToOpen<<std::endl<<"###########\n";

	char c;
	int nesting = 0;

	for(auto iterator = str.begin(), end = str.end(); iterator != end; ++iterator)
	{

			//std::cout<<c;

		c = *iterator;
		switch(c)
		{
			case '<':
			{
				pointer--;
				break;
			}
			case '>':
			{
				pointer++;
				break;
			}
			case '+':
			{
				fckMemory[pointer]++;
				break;
			}
			case '-':
			{
				fckMemory[pointer]--;
				break;
			}
			case '.':
			{
				putchar(fckMemory[pointer]);
				break;
			}
			case ',':
			{
				fckMemory[pointer] = getchar();
				break;
			}
			case '[':
			{
				if(fckMemory[pointer] > 0)nesting++; //warunek spełniony
				else //skip the loop
				{
					int ins = 0;
					do{
						c = *iterator;
						if(c == '[')ins++;
						if(c == ']')ins--;

						if(c == ']' && ins == 0)
						{
							break;
						}
					}while(++iterator != str.end());
				}
				break;
			}
			case ']':
			{
				int ins = 0;
				do{
					//std::cout<<"#"<<c<<"#"<<"p."<<fckMemory[pointer]<<".p"<<pointer<<"_";
					c = *iterator;
					if(c == ']')ins++;
					else if(c == '[')ins--;
					//else if(c == '>')pointer--;
					//else if(c == '<')pointer++;

					if(c == '[' && ins == 0)
					{
						--iterator;
						break;
					}

				}while(--iterator != str.begin());
			}
			default:
			{}

		}		
	

		if(pointer < 0 || pointer >= memSize)
		{
			if(!isSilent())std::cout<<"\nbxx: Fatal - Pointer out of bounds."<<std::endl;
			return false;
		}


	}

	if(isVerbose())std::cout<<"\n###########\nExecution has been successful"<<std::endl;

	fs.close();
	delete [] fckMemory;

	return true;
}
