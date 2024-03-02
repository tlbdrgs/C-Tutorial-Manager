#include<iostream>
#include<string.h>
#include"ui.h"
#include"services.h"
#include"Dynamic_vector.h"
#include"tutorial.h"
#include"time.h"
#include"tests.h"

using namespace std;

int main()
{
    Tests tests;
    tests.run_all_tests();
    std::cout << "all tests passed\n";
    UI ui;
    ui.start();
    return 0;
}
