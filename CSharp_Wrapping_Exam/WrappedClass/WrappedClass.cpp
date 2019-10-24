#include "stdafx.h"

#include "WrappedClass.h"

namespace WrappedClass
{
	CWrappedClass::CWrappedClass()
	{
		m_pNativeClass = new CNativeClass;
	}
	CWrappedClass::~CWrappedClass()
	{
		delete m_pNativeClass;
	}
	void CWrappedClass::CallNativeFunction()
	{
		m_pNativeClass->PrintInfo();
	}
	int CWrappedClass::CallGetAge()
	{
		return m_pNativeClass->GetAge();
	}
	double CWrappedClass::CallGetWeight()
	{
		return m_pNativeClass->GetWeight();
	}
	double CWrappedClass::CallGetSum()
	{
		return m_pNativeClass->GetSum();
	}
}