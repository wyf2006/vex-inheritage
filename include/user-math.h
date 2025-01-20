#ifndef _USER_MATH_H_
#define _USER_MATH_H_

#include "robot-config.h"

class MyTimer
{
private:
    int time;

public:
    MyTimer();
    void reset();
    void click();
    int getTime() const;
};


template <class T>
T MaxElement(T a[],int size) 
{
	T tmpMax = a[0];
	for( int i = 1;i < size;++i)
	{
		if (tmpMax < a[i])
		{
			tmpMax = a[i];
		}
	}
	return tmpMax;
}

template <class T>
T MinElement(T a[],int size) 
{
	T tmpMin = a[0];
	for( int i = 1;i < size;++i)
	{
		if (tmpMin > a[i])
		{
			tmpMin = a[i];
		}
	}
	return tmpMin;
}

template <class T>
T SumElement(T a[],int size) 
{
	T tmp = a[0];
	for( int i = 1;i < size;++i)
	{
		tmp += a[i];
	}
	return tmp;
}

#endif