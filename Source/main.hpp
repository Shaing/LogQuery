#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

template<typename T>
void coutLog(T l){ std::cout << l << std::endl;}

namespace inno{
class ELMMAP
{
public:
	virtual std::string& getKey(const std::string& k) = 0;
	virtual std::string& getVal(const std::string& v) = 0;
	virtual void setMap() = 0;
	virtual void getMap(std::unordered_map<std::string, std::string>& m) = 0;
	virtual void showMap() = 0;
};

class CRCMAP : public ELMMAP
{
public:
	std::string& getKey(const std::string& k) override
	{
		key = k.substr(k.find_last_of("\\") + 1);
		key = key.substr(0, 20);
		return key;
	}

	std::string& getVal(const std::string& v) override
	{
		std::string::size_type f = v.find("CRCCnt");
		if(f != std::string::npos)
		{
			value = v.substr(v.find("CRCCnt"));
			value = value.substr(8);
			value = value.substr(0, value.find(","));
			//coutLog(value);
		}
		else
			value.clear();
		return value;
	}

	void setMap() override{ snAndCrcCnt.insert({key, value}); }
	void getMap(std::unordered_map<std::string, std::string>& m) override{ m = std::move(snAndCrcCnt); }
	void showMap() override
	{
		for(const auto& x : snAndCrcCnt)
			std::cout << x.first << "," << x.second << std::endl;
	}
private:
	std::string key;
	std::string value;
	std::unordered_map<std::string, std::string> snAndCrcCnt;
};

}

