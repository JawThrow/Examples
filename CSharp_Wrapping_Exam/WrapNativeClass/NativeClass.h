#pragma once

class CNativeClass
{
private:
	int age;
	double weight;
public:
	CNativeClass();
	~CNativeClass();

	void PrintInfo();
	int GetAge() { return age; }
	double GetWeight() { return weight; }
	double GetSum() { return (double)age + weight; }
};