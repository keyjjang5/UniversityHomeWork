#pragma once

class Printer
{
	std::string model;
	std::string manufacturer;
	int printedCount;
	int availableCount;

public:
	Printer(std::string model, std::string manufacturer, int availableCount);
	bool print(int pages);
	void dataShow();
};

Printer::Printer(std::string model, std::string manufacturer, int availableCount) : model(model), manufacturer(manufacturer), availableCount(availableCount)
{

}

bool Printer::print(int pages)
{
	printedCount = pages;
	if (availableCount > printedCount)
	{
		availableCount -= pages;
		return true;
	}
	else
		return false;

}

void Printer::dataShow()
{
	std::cout << model << ", " << manufacturer << ", 남은 종이 " << availableCount << "장 ";
}

class InkJetPrinter :public Printer
{
	int availableInk;
public:
	InkJetPrinter(std::string model, std::string manufacturer, int availableCount, int availableInk);
	bool printInkJet(int pages);
	void InkJetDataShow();
};

InkJetPrinter::InkJetPrinter(std::string model, std::string manufacturer, int availableCount, int availableInk)
	:Printer(model, manufacturer, availableCount), availableInk(availableInk)
{

}

bool InkJetPrinter::printInkJet(int pages)
{
	if (print(pages))
	{
		availableInk -= pages;
		return true;
	}
	else
		return false;
}

void InkJetPrinter::InkJetDataShow()
{
	dataShow();
	std::cout << "남은 잉크 " << availableInk << std::endl;
}

class LaserPrinter :public Printer
{
	int availableToner;
public:
	LaserPrinter(std::string model, std::string manufacturer, int availableCount, int availableToner);
	bool printLaser(int pages);
	void laserDataShow();
};

LaserPrinter::LaserPrinter(std::string model, std::string manufacturer, int availableCount, int availableToner)
	:Printer(model, manufacturer, availableCount), availableToner(availableToner)
{

}

bool LaserPrinter::printLaser(int pages)
{
	if (print(pages))
	{
		availableToner -= pages;
		return true;
	}
	else
		return false;
}

void LaserPrinter::laserDataShow()
{
	dataShow();
	std::cout << "남은 토너 " << availableToner << std::endl;
}