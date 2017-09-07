/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include <fstream>
#include <string>

namespace
{
	Array<File> ret;
}

//==============================================================================
int main (int argc, char* argv[])
{
    // ..your code goes here!
	//File tar(File::getCurrentWorkingDirectory().getFullPathName() + "\\target");

	File tar("C:\\CRCtest");
	DBG(tar.getFullPathName());
	tar.findChildFiles(ret, 2, true, "*.csv");

	std::string fBuf;
	for(auto i = 0; i < ret.size(); ++i)
	{
		//bool doesRemove = true;
		std::fstream f(ret[i].getFullPathName().toRawUTF8(), std::fstream::in);
		if(!f)
			std::cout << "Open file fail!" << std::endl;
		else
		{
			//while(std::getline(f, fBuf), !f.eof())
			{
				//if(fBuf.find("") != std::string::npos)
				{
					std::cout << ret[i].getFullPathName() << std::endl;
					//doesRemove = false;
					//break;
				}
			}
			//if(doesRemove)
			//{
			//	ret.remove(i);
			//}
		}
		f.close();
	}

	//for(auto &r : ret)
	//	r.deleteFile();

	system("PAUSE");
    return 0;
}
