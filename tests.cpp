#include "tests.h"
#include"exceptions.h"
#include<iostream>

void Tests::test_add_tutorial() {
    Tutorial tutorial("Title", "Presenter", Time(60, 0), 0, "Link");
    assert(services.add_tutorial(tutorial));
    assert(services.get_size() == 11);

    try {
        services.add_tutorial(tutorial);
    }
    catch (RepositoryException& )
    {

    }
}


void Tests::test_remove_tutorial() {
    try {
        services.remove_tutorial(-1);
    }
    catch (RepositoryException& e) {
        assert(strcmp(e.what(), "No such tutorial") == 0);
    }

    assert(services.remove_tutorial(0));
    assert(services.get_size() == 10);
}


void Tests::test_update_tutorial()
{
    Tutorial new_tutorial("New Title", "New Presenter", Time(90, 0), 0, "New Link");
    assert(services.update_tutorial(0, new_tutorial));
    assert(services.get_all_tutorials()[0].get_title() == "New Title");
    assert(services.get_all_tutorials()[0].get_presenter() == "New Presenter");
    assert(services.get_all_tutorials()[0].get_duration().get_minutes() == 90);
    assert(services.get_all_tutorials()[0].get_duration().get_seconds() == 0);
    assert(services.get_all_tutorials()[0].get_link() == "New Link");

    try {
        Tutorial invalid_tutorial("Invalid Title", "Invalid Presenter", Time(60, 0), 0, "Invalid Link");
        services.update_tutorial(-1, invalid_tutorial);
        }
    catch (RepositoryException&) {
        assert(true);
    }
}

void Tests::test_index()
{
    assert(services.find_index("C++ Tutorial for Beginners - Full Course") == 1);
    assert(services.find_index("invalid name") == -1);
}

void Tests::test_index_watchlist()
{
    watchlist.add_tutorial_watchlist(services.get_all_tutorials()[0]);
    assert(watchlist.find_index_watchlist("New Title") == 0);
    assert(watchlist.find_index_watchlist("invalid name") == -1);
}


void Tests::test_add_tutorial_to_watchlist() {
    assert(services.add_tutorial_watchlist(services.get_all_tutorials()[0]));
    assert(services.get_size_watchlist() == 1);

    try {
        services.add_tutorial_watchlist(services.get_all_tutorials()[0]);
    }
    catch (RepositoryException& e) {
        assert(string(e.what()) == "Tutorial already exists!");
    }
}


void Tests::test_remove_tutorial_from_watchlist()
{
    assert(watchlist.add_tutorial_watchlist(services.get_all_tutorials()[0]));
    assert(watchlist.remove_tutorial_watchlist(0));
    assert(watchlist.get_size_watchlist() == 0); // Check that the size has decreased by 1
    try
    {
        watchlist.remove_tutorial_watchlist(-1);
    }
    catch (RepositoryException& e)
    {
        assert(string(e.what()) == "No such tutorial");
    }
}

void Tests::test_increase_likes() {
    services.increase_likes(0);
    assert(services.get_all_tutorials()[1].get_likes() == 250000); // Check that likes have been increased by 1
}

void Tests::test_initial_10_tutorials()
{
    services.initial_10_tutorials();
    assert(services.get_all_tutorials()[0].get_title() == "C++ Tutorial for Beginners - Learn C++ in 1 Hour");
    assert(services.get_all_tutorials()[0].get_presenter() == "Programming with Mosh");
    assert(services.get_all_tutorials()[0].get_duration().get_minutes() == 30);
    assert(services.get_all_tutorials()[0].get_duration().get_seconds() == 10);
    assert(services.get_all_tutorials()[0].get_likes() == 12000);
    assert(services.get_all_tutorials()[0].get_link() == "https://www.youtube.com/watch?v=ZzaPdXTrSb8");
}


void Tests::run_all_tests()
{
    test_initial_10_tutorials();
    test_add_tutorial();
    test_remove_tutorial();
    test_update_tutorial();
    test_add_tutorial_to_watchlist();
    test_remove_tutorial_from_watchlist();
    test_increase_likes();
    test_index();
    test_index_watchlist();
    test_get_all_tutorials_watchlist();
    test_toString();
}

void Tests::test_get_all_tutorials_watchlist() {
    Services services;

    Tutorial t1("Title 1", "Presenter 1", Time(30, 0), 100, "Link 1");
    Tutorial t2("Title 2", "Presenter 2", Time(45, 0), 200, "Link 2");
    Tutorial t3("Title 3", "Presenter 3", Time(60, 0), 300, "Link 3");

    services.add_tutorial_watchlist(t1);
    services.add_tutorial_watchlist(t2);
    services.add_tutorial_watchlist(t3);
    Tutorial* watchlist_tutorials = services.get_all_tutorials_watchlist();
    assert(watchlist_tutorials[0].get_title() == "Title 1");
    assert(watchlist_tutorials[1].get_title() == "Title 2");
    assert(watchlist_tutorials[2].get_title() == "Title 3");
    delete[] watchlist_tutorials;
}

void Tests::test_toString()
{

    Tutorial t1("Title 1", "Presenter 1", Time(30, 0), 100, "Link 1");

    string expectedString = "NAME: Title 1 PRESENTER: Presenter 1 DURATION: 30 minutes and 0 seconds LIKES: 100 LINK: Link 1\n";
    assert(t1.toString() == expectedString);
}
