#pragma once

class Accumulator
{
	int value;
public:
	Accumulator(int value); // 매개 변수 value로 멤버 value를 초기화한다. 
	Accumulator& add(int n); // value에 n을 더해 값을 누적한다. 
	int get(); // 누적된 값 value를 리턴한다. 
};

Accumulator::Accumulator(int value) :value(value)
{

}

Accumulator& Accumulator::add(int n)
{
	value += n;

	return *this;
}

int Accumulator::get()
{
	return value;
}