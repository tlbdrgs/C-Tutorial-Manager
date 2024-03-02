#pragma once
#include "Dynamic_vector.h"

class Services
{
	private:
		Dynamic_vector<Tutorial> repository;
		Dynamic_vector<Tutorial> watchlist;
	public:
		Services();
		bool add_tutorial(Tutorial tutorial);
		bool add_tutorial_watchlist(Tutorial tutorial);
		bool remove_tutorial_watchlist(int index);
		bool remove_tutorial(int index);
		bool update_tutorial(int index, Tutorial tutorial);
		Tutorial* get_all_tutorials_watchlist();
		int get_size_watchlist() const;
		void initial_10_tutorials();
		int get_size() const;
		int find_index(string name);
		int find_index_watchlist(string title);
		void write_to_file() const;
		void write_to_file_user() const;
		int get_index(const std::string& title) const;
		Tutorial* get_all_tutorials();
		void increase_likes(int index);
		void read_from_file();
		void write_to_file_csv(const std::string& filename) const;
		void write_to_file_user_csv(const std::string& filename) const;
};
