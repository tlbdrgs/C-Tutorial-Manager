#pragma once

#include <cassert>
#include "services.h"

class Tests {
public:
    void run_all_tests();
    void test_add_tutorial();
    void test_remove_tutorial();
    void test_update_tutorial();
    void test_add_tutorial_to_watchlist();
    void test_remove_tutorial_from_watchlist();
    void test_increase_likes();
    void test_initial_10_tutorials();
    void test_index();
    void test_index_watchlist();
    void test_get_all_tutorials_watchlist();
    void test_toString();

private:
    Services services;
    Services watchlist;
};
