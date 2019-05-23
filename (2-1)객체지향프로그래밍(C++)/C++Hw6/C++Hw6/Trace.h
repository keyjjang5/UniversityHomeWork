#pragma once

class Trace
{
	static std::string saveTag[100];
	static std::string saveData[100];
	static int pos;
public:
	static void put(std::string tag, std::string debugData);
	static void print(std::string tag);
	static void print();

};

void Trace::put(std::string tag, std::string debugData)
{
	saveTag[pos] = tag;
	saveData[pos] = debugData;
	pos++;
}

void Trace::print()
{
	std::cout << "모든 Trace 정보를 출력합니다. ------------------" << std::endl;
	for (int i = 0; i < pos; i++)
	{
		std::cout << saveTag[i] << " : " << saveData[i] << std::endl;
	}
}

void Trace::print(std::string tag)
{
	std::cout << tag << "태그의 Trace 정보를 출력합니다. ------------------" << std::endl;
	for (int i = 0; i < pos; i++)
	{
		if (saveTag[i] == tag)
			std::cout << saveTag[i] << " : " << saveData[i] << std::endl;
	}
}

int Trace::pos = 0;
std::string Trace::saveTag[100];
std::string Trace::saveData[100];