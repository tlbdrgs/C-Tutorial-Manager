#pragma once
#include "services.h"

class UI {
private:
    Services services;
public:
    UI();
    ~UI();
    void print_menu_administrator();
    void print_menu_user();
    void start();
    void see_tutorials_by_presenter();
};
