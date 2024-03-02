#include "services.h"
#include "time.h"
#include"exceptions.h"
#include<iostream>
#include<fstream>
#include<sstream>

bool Services::add_tutorial(Tutorial tutorial)
{
    for (int index = 0; index < repository.get_size(); index++)
        if (repository.get_item(index).get_title() == tutorial.get_title())
            throw RepositoryException("Tutorial already exists!");
    repository.add_item(tutorial);
    return true;
}

std::ostream& operator<<(std::ostream& os, const Time& time)
{
    os << time.get_minutes() << "," << time.get_seconds();
    return os;
}

bool Services::remove_tutorial(int index)
{
    if (index < 0 || index >= repository.get_size())
        throw RepositoryException("No such tutorial");
    repository.remove_item(index);
    return true;
}

bool Services::update_tutorial(int index, Tutorial tutorial)
{
    if (index < 0 || index >= repository.get_size())
        throw RepositoryException("Invalid index");
    repository.update_item(index, tutorial);
    return true;
}

int Services::find_index(string title)
{
    for (int i = 0;i < repository.get_size();i++)
        if (repository.get_item(i).get_title() == title)
            return i;
    return -1;
}


int Services::find_index_watchlist(string title)
{
    for (int i = 0;i < watchlist.get_size();i++)
        if (watchlist.get_item(i).get_title() == title)
            return i;
    return -1;
}

void Services::write_to_file_csv(const std::string& filename) const
{
    std::ofstream outfile(filename, std::ofstream::trunc);

    if (!outfile.is_open()) {
        std::cerr << "Error: failed to open file " << filename << " for writing\n";
        return;
    }

    for (int i = 0; i < this->repository.get_size(); i++) {
        outfile << this->repository.get_item(i).get_title() << ",";
        outfile << this->repository.get_item(i).get_presenter() << ",";
        outfile << this->repository.get_item(i).get_duration() << ",";
        outfile << this->repository.get_item(i).get_likes() << ",";
        outfile << this->repository.get_item(i).get_link() << std::endl;
    }

    outfile.close();
}

void Services::write_to_file_user_csv(const std::string& filename) const
{
    std::ofstream outfile(filename, std::ofstream::trunc);

    if (!outfile.is_open()) {
        throw FileException("Can't open the file");
    }

    for (int i = 0; i < this->watchlist.get_size(); i++) {
        outfile << this->watchlist.get_item(i).get_title() << ",";
        outfile << this->watchlist.get_item(i).get_presenter() << ",";
        outfile << this->watchlist.get_item(i).get_duration() << ",";
        outfile << this->watchlist.get_item(i).get_likes() << ",";
        outfile << this->watchlist.get_item(i).get_link() << std::endl;
    }

    outfile.close();
}

Services::Services()
{
   
}


Tutorial* Services::get_all_tutorials()
{
	Tutorial* tutorials = new Tutorial[repository.get_size()];
	for (int i = 0; i < repository.get_size();i++)
		tutorials[i] = repository.get_item(i);
	return tutorials;
}

Tutorial* Services::get_all_tutorials_watchlist()
{
    Tutorial* tutorials = new Tutorial[watchlist.get_size()];
    for (int i = 0; i < watchlist.get_size();i++)
        tutorials[i] = watchlist.get_item(i);

    return tutorials;
}

int Services::get_size() const
{
    return repository.get_size();
}

int Services::get_size_watchlist() const
{
    return watchlist.get_size();
}


void Services::initial_10_tutorials()
{
    Services::add_tutorial(Tutorial("C++ Tutorial for Beginners - Learn C++ in 1 Hour", "Programming with Mosh", Time(30, 10), 12000, "https://www.youtube.com/watch?v=ZzaPdXTrSb8"));
    Services::add_tutorial(Tutorial("Introducere în programare - tutorial C++ - cursul 1", "Videotutorial.ro", Time(50, 1), 7600, "https://www.youtube.com/watch?v=JjY9U9lu37I"));
    Services::add_tutorial(Tutorial("C++ Tutorial for Beginners - Full Course", "freeCodeCamp.org", Time(180, 0), 250000, "https://www.youtube.com/watch?v=vLnPwxZdW4Y"));
    Services::add_tutorial(Tutorial("C++ Programming Course - Beginner to Advanced", "freeCodeCamp.org", Time(60, 15), 100000, "https://www.youtube.com/watch?v=8jLOx1hD3_o"));
    Services::add_tutorial(Tutorial("C++ in 100 Seconds", "Fireship", Time(1, 1), 50000, "https://www.youtube.com/watch?v=MNeX4EGtR5Y"));
    Services::add_tutorial(Tutorial("C++ Full Course for free", "Bro Code", Time(360, 0), 34000, "https://www.youtube.com/watch?v=-TkoO8Z07hI"));
    Services::add_tutorial(Tutorial("C++ FULL COURSE For Beginners (Learn C++ in 10 hours)", "CodeBeauty", Time(627, 100), 84000, "https://www.youtube.com/watch?v=GQp1zzTwrIg"));
    Services::add_tutorial(Tutorial("How to REALLY learn C++", "The Cherno", Time(8, 12), 24000, "https://www.youtube.com/watch?v=_zQqN5OYCCM"));
    Services::add_tutorial(Tutorial("Learn C++ With Me #1 - How to Compile and Run C++ Code", "Tech With Tim", Time(18, 25), 5100, "https://www.youtube.com/watch?v=lPd13fsU-CQ"));
    Services::add_tutorial(Tutorial("C++ Tutorial From Basic to Advance", "Extern Code", Time(553, 4), 79000, "https://www.youtube.com/watch?v=mUQZ1qmKlLY"));
}

void Services::read_from_file()
{
    std::ifstream infile("tutorials.txt");

    std::string line;
    while (std::getline(infile, line))
    {
        std::stringstream ss(line);
        std::string title, presenter, duration_str, likes_str, link;

        std::getline(ss, title, ',');
        std::getline(ss, presenter, ',');
        std::getline(ss, duration_str, ',');
        std::getline(ss, likes_str, ',');
        std::getline(ss, link);

        int minutes = 0, seconds = 0;
        std::stringstream duration_ss(duration_str);
        duration_ss >> minutes;
        duration_ss.ignore(1, ':');
        duration_ss >> seconds;

        int likes = 0;
        std::stringstream likes_ss(likes_str);
        likes_ss >> likes;

        Tutorial tutorial(title, presenter, Time(minutes, seconds), likes, link);
        this->repository.add_item(tutorial);
    }

    infile.close();
}


void Services::write_to_file() const
{
    std::ofstream outfile;
    outfile.open("administrator.txt");

    if (!outfile.is_open()) {
        throw FileException("Can't open the file");
    }

    for (int i=0; i<this->repository.get_size();i++)
    {
        outfile << this->repository.get_item(i).get_title() << ",";
        outfile << this->repository.get_item(i).get_presenter() << ",";
        outfile << this->repository.get_item(i).get_duration() << ",";
        outfile << this->repository.get_item(i).get_likes() << ",";
        outfile << this->repository.get_item(i).get_link() << std::endl;
    }
    outfile.close();
}

void Services::write_to_file_user() const
{
    std::ofstream outfile;
    outfile.open("user.csv");

    if (!outfile.is_open()) {
        throw FileException("Can't open the file");
    }

    for (int i = 0; i < this->watchlist.get_size();i++)
    {
        outfile << this->watchlist.get_item(i).get_title() << ",";
        outfile << this->watchlist.get_item(i).get_presenter() << ",";
        outfile << this->watchlist.get_item(i).get_duration() << ",";
        outfile << this->watchlist.get_item(i).get_likes() << ",";
        outfile << this->watchlist.get_item(i).get_link() << std::endl;
    }

    outfile.close();
}



bool Services::add_tutorial_watchlist(Tutorial tutorial)
{
    for (int index = 0; index < watchlist.get_size(); index++)
        if (watchlist.get_item(index).get_title() == tutorial.get_title())
            throw RepositoryException("Tutorial already exists!");
    watchlist.add_item(tutorial);
    return true;
}
bool Services::remove_tutorial_watchlist(int index)
{
    if (index < 0 || index >= watchlist.get_size())
        throw RepositoryException("No such tutorial");
    watchlist.remove_item(index);
    return true;
}

void Services::increase_likes(int index)
{
    Tutorial new_tutorial = repository.get_item(index);
    new_tutorial.increment_likes();
    repository.update_item(index, new_tutorial);
    watchlist.update_item(index, new_tutorial);
}



