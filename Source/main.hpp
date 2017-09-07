#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

using std::cout;
using std::endl;

template<typename T>
void coutLog(T l){ std::cout << l << std::endl;}

namespace inno{
class ELMMAP
{
public:
	virtual void setKey(const std::string& k) = 0;
	virtual void setVal(const std::string& v) = 0;
	virtual void setMap() = 0;
	virtual void getMap(std::unordered_map<std::string, std::string>& m) = 0;
	virtual void showMap() = 0;
};

class CRCMAP : public ELMMAP
{
public:
	void setKey(const std::string& k) override
	{
		key = k.substr(k.find_last_of("\\") + 1);
		key = key.substr(0, 20);
	}

	void setVal(const std::string& v) override
	{
		std::string::size_type f = v.find("CRCCnt");
		if(f != std::string::npos)
		{
			value = v.substr((f + 8));
			value = value.substr(0, value.find(","));
			value = value.substr(value.find_last_of(" ") + 1);
			//coutLog(value);
		}
		else
			value.clear();
	}

	void setMap() override{ snAndCrcCnt.insert({key, value}); }
	void getMap(std::unordered_map<std::string, std::string>& m) override{ m = std::move(snAndCrcCnt); }
	void showMap() override
	{
		for(const auto& x : snAndCrcCnt)
			cout << x.first << "," << x.second << endl;
	}
private:
	std::string key;
	std::string value;
	std::unordered_map<std::string, std::string> snAndCrcCnt;
};

}

