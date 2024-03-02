#pragma once

#include<string>
#include<iostream>
#include"time.h"
using namespace std;

class Tutorial
{
	private:
		std::string title;
		std::string presenter;
		Time duration;
		int likes;
		std::string link;
	public:
		Tutorial();
		Tutorial(const std::string& title, const std::string& presenter, const Time & duration, const int likes, const std::string& link);
		Tutorial(const Tutorial&);
		std::string get_title();
		std::string get_presenter();
		std::string get_link();
		Time get_duration();
		int get_likes();
		void increment_likes();
		~Tutorial();
		std::string toString();
		friend std::ostream& operator<<(std::ostream& out, const Tutorial& tutorial);
		friend std::istream& operator>>(std::istream& in, Tutorial& tutorial);
};
