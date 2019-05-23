#pragma once

class Accumulator
{
	int value;
public:
	Accumulator(int value); // �Ű� ���� value�� ��� value�� �ʱ�ȭ�Ѵ�. 
	Accumulator& add(int n); // value�� n�� ���� ���� �����Ѵ�. 
	int get(); // ������ �� value�� �����Ѵ�. 
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