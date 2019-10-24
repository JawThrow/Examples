#include "NativeClass.h"
#include <iostream>
using namespace std;
CNativeClass::CNativeClass()
{
	this->age = 28;
	this->weight = 60.0;
}

CNativeClass::~CNativeClass()
{
	this->age = 0;
	this->weight = 0;
}

void CNativeClass::PrintInfo()
{
	cout << "Age: " << this->age << endl;
	cout << "Weight: " << this->weight << endl;
}