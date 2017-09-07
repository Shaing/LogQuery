/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "main.hpp"
#include <fstream>
#include <vector>

using namespace std;

namespace
{
	Array<File> ret;
	std::string inputPath{"C:\\CRCtest"};
	std::string tarExt{"*.csv"};


	void startSearch(const Array<File>& r)
	{
		std::string fBuf;
		vector<string> fBufLs;

		unique_ptr<inno::ELMMAP> crcMap(new inno::CRCMAP());
		std::unordered_map<std::string, std::string> crcUm;
		std::unordered_map<std::string, int> crcStats;
		for(auto i = 0; i < r.size(); ++i)
		{
			fBufLs.clear();
			//set sn
			crcMap->setKey(r[i].getFullPathName().toStdString());
			std::fstream f(r[i].getFullPathName().toRawUTF8(), std::fstream::in);
			if(!f)
				std::cout << "Open file fail!" << std::endl;
			else
			{
				while(std::getline(f, fBuf), !f.eof())
				{
					if(fBuf.find("") != std::string::npos)
					{
						//cout << fBuf << endl;
						fBufLs.push_back(move(fBuf));
					}
				}
			}
			f.close();
			//set crc cnt
			crcMap->setVal(fBufLs[(fBufLs.size() - 1)]);
			crcMap->setMap();
		}
		crcMap->showMap();
		crcMap->getMap(crcUm);

		for(auto b = crcUm.begin(); b != crcUm.end(); ++b)
		{
			++crcStats[b->second];
		}

		for(const auto &s : crcStats)
			std::cout << s.first << "," << s.second << std::endl; 		

	}
	
}



//==============================================================================
int main (int argc, char* argv[])
{
    // ..your code goes here!
	//File tar(File::getCurrentWorkingDirectory().getFullPathName() + "\\log");

	File tar(inputPath);
	DBG(tar.getFullPathName());
	tar.findChildFiles(ret, 2, true, tarExt);

	startSearch(ret);

	system("PAUSE");
    return 0;
}


