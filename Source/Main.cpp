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
#include <chrono>


using namespace std;

namespace
{
	Array<File> ret;
	std::string inputPath{"C:\\CRCtest"};
	std::string tarExt{"*.csv"};


	void startQuery(const Array<File>& r)
	{
		std::string fBuf;
		vector<string> fBufLs;

		unique_ptr<inno::ELMMAP> crcMap(new inno::CRCMAP());
		std::unordered_map<std::string, std::string> crcUm;
		//std::unordered_map<std::string, int> crcStats;
		std::map<int, int> crcStats;
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
		//crcMap->showMap();
		crcMap->getMap(crcUm);

		for(auto b = crcUm.begin(); b != crcUm.end(); ++b)
		{
			++crcStats[atoi(b->second.c_str())];
		}

		int totSnCnt = 0;
		for(const auto &s : crcStats)
		{
			std::cout << s.first << "," << s.second << std::endl;
			totSnCnt += s.second;
		}
		std::cout << "Tot Sn Cnt: " << totSnCnt << std::endl;

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

	coutLog("Start Query...");
	auto t0 = chrono::high_resolution_clock::now();
	startQuery(ret);
	auto t1 = chrono::high_resolution_clock::now();
	std::cout << "Tot query time: " << static_cast<double>(chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() / 1000) << " sec" << std::endl;
	system("PAUSE");
    return 0;
}


