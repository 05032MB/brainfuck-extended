#ifndef _INTER_H_
#define _INTER_H

#include <vector>
#include <string>

class interpreter{

		std::vector<std::string> params;
		bool verbose;
		bool silent;
		bool fastLoops;

		std::string fileToOpen;

		int *fckMemory;
		int memSize;
		int pointer;

		bool parseOpts(void);
		inline bool isVerbose(void)const;
		inline bool isSilent(void)const;
	public:
		interpreter(const std::vector<std::string> &g);
		bool parse(void);
};


#endif