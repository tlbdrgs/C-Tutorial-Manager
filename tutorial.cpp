#include "tutorial.h"
using namespace std;

Tutorial::Tutorial()
{
	title = "";
	presenter = "";
	duration = Time();
	likes = 0;
	link = "";	
}

string Tutorial::get_title()
{
	return title;
}

string Tutorial::get_presenter()
{
	return presenter;
}

string Tutorial::get_link()
{
	return link;
}

int Tutorial::get_likes()
{
	return likes;
}

Time Tutorial::get_duration()
{
	return duration;
}

Tutorial::Tutorial(const std::string& title, const std::string& presenter, const Time& duration, const int likes, const std::string& link)
	: title(title), presenter(presenter), duration(duration), likes(likes), link(link)
{
}

Tutorial::~Tutorial()
{

}

Tutorial::Tutorial(const Tutorial& other)
{
	this->title = other.title;
	this->presenter = other.presenter;
	this->duration = other.duration;
	this->likes = other.likes;
	this->link = other.link;
}

string Tutorial::toString()
{
	return "NAME: " + this->title
		+ " PRESENTER: " + this->presenter +
		" DURATION: " + to_string(this->duration.get_minutes()) + " minutes and " + to_string(this->duration.get_seconds())
		+ " seconds LIKES: " + to_string(this->likes)
		+ " LINK: " + this->link + '\n';
}

void Tutorial::increment_likes()
{
	this->likes++;
}

