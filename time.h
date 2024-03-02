#pragma once
class Time
{
private:
	int minutes;
	int seconds;
public:
	Time();
	Time(int minutes, int seconds);
	int get_minutes() const;
	int get_seconds() const;
};