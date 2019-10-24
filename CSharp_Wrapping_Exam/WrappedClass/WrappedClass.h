#pragma once
#include "NativeClass.h"
using namespace System;

namespace WrappedClass {
	public ref class CWrappedClass
	{
		// TODO: 여기에 이 클래스에 대한 메서드를 추가합니다.
	public:
		CWrappedClass();
		~CWrappedClass();
		void CallNativeFunction();
		int CallGetAge();
		double CallGetWeight();
		double CallGetSum();
	private:
		CNativeClass* m_pNativeClass;
	};
}
