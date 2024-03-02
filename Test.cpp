#include <assert.h>
#include "dynamic_vector.h"

void test_tutorial()
{
    Tutorial t{ "title", "presenter", Time{1,30}, 10, "link" };

    assert(t.get_title() == "title");
    assert(t.get_presenter() == "presenter");
    assert(t.get_link() == "link");
    assert(t.get_likes() == 10);

    t.increment_likes();
    assert(t.get_likes() == 11);

    Tutorial t2{ t };
    assert(t2.get_title() == "title");
    assert(t2.get_presenter() == "presenter");
    assert(t2.get_duration().get_minutes() == 1);
    assert(t2.get_duration().get_seconds() == 30);
    assert(t2.get_likes() == 11);
    assert(t2.get_link() == "link");

    Tutorial t3;
    assert(t3.get_title() == "");
    assert(t3.get_presenter() == "");
    assert(t3.get_duration().get_minutes() == 0);
    assert(t3.get_duration().get_seconds() == 0);
    assert(t3.get_likes() == 0);
    assert(t3.get_link() == "");
}

void TestTutorial()
{
    Tutorial t1("Introduction to C++", "John Doe", Time(1, 30), 10, "www.youtube.com");
    assert(t1.get_title() == "Introduction to C++");
    assert(t1.get_presenter() == "John Doe");
    assert(t1.get_link() == "www.youtube.com");
    assert(t1.get_likes() == 10);
    t1.increment_likes();
    assert(t1.get_likes() == 11);

    Tutorial t2(t1);
    assert(t2.get_title() == "Introduction to C++");
    assert(t2.get_presenter() == "John Doe");
    assert(t2.get_link() == "www.youtube.com");
    assert(t2.get_likes() == 11);
    t2.increment_likes();
    assert(t2.get_likes() == 12);
}

void TestDynamicVector()
{
    Dynamic_vector v(2);
    assert(v.get_size() == 0);
    assert(v.get_item(0).get_title() == "");

    Tutorial t1("Introduction to C++", "John Doe", Time(1, 30), 10, "www.youtube.com");
    Tutorial t2("Advanced C++", "Jane Doe", Time(2, 0), 15, "www.youtube.com");
    v.add_item(t1);
    v.add_item(t2);
    assert(v.get_size() == 2);
    assert(v.get_item(0).get_title() == "Introduction to C++");
    assert(v.get_item(1).get_title() == "Advanced C++");

    Tutorial t3("Introduction to C++", "John Doe", Time(1, 30), 10, "www.youtube.com");
    v.update_item(0, t3);
    assert(v.get_item(0).get_likes() == 10);
    v.get_item(0).increment_likes();
    assert(v.get_item(0).get_likes() == 11);

    v.remove_item(0);
    assert(v.get_size() == 1);
    assert(v.get_item(0).get_title() == "Advanced C++");
}

void TestAll()
{
    TestTutorial();
    TestDynamicVector();
}