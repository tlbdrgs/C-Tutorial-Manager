#include "time.h"
#include<fstream>
#include<iostream>

Time::Time() :minutes{ 0 }, seconds{ 0 }
{

}

Time::Time(int minutes, int seconds)
{
	if (seconds > 60)
	{
		this->minutes = minutes + seconds / 60;
		this->seconds = seconds % 60;
	}
	else
	{
		this->minutes = minutes;
		this->seconds = seconds;
	}
}

int Time::get_minutes() const
{
	return minutes;
}

int Time::get_seconds() const
{
	return seconds;
}
