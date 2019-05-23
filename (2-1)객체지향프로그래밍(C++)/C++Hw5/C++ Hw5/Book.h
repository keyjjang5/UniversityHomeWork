#pragma once
using namespace std;

class Book {
	string title;
	int price;
public:
	Book(const string title, int price);
	~Book();
	void set(const string title, int price);
	void show();
};

Book::Book(const string title, int price) : price(price)
{
	this->title = title;

}

Book::~Book()
{
	
}


void Book::set(const string title, int price)
{
	this->title = title;
	this->price = price;
}

void Book::show()
{
	cout << title << "  " << price << endl;
}