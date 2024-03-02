#include "ui.h"
#include"exceptions.h"
#include<iostream>
#include<Windows.h>
using namespace std;

UI::UI()
{
}

UI::~UI()
{
}

void UI::print_menu_administrator()
{
	cout << "C++ MASTER\n";
	cout << "MENU:\n";
	cout << "\t1.Add a tutorial\n";
	cout << "\t2.Delete a tutorial\n";
	cout << "\t3.Update a tutorial\n";
	cout << "\t4.Show all the tutorials\n";
    cout << "\t5.Save in a CSV file\n";
	cout << "\t0.Exit\n";
}


void UI::print_menu_user()
{
    cout << "WELCOME USER\n";
    cout << "MENU:\n";
    cout << "1.See tutorials from a specific presenter\n";
    cout << "2.See the watch list\n";
    cout << "3.Delete the watch list\n";
    cout << "4.Save in a CSV file\n";
    cout << "0.Exit\n";
}

void UI::see_tutorials_by_presenter()
{
    string presenter;
    cout << "Enter the presenter's name (or leave empty to see all tutorials): ";
    cin.ignore();
    getline(cin, presenter);

    int tutorial_count = services.get_size();
    Tutorial* tutorials = services.get_all_tutorials();

    for (int i = 0; i < tutorial_count; i++)
    {
        if (presenter.empty() || tutorials[i].get_presenter() == presenter)
        {
            cout << tutorials[i].toString();
            cout << "Opening tutorial in browser...\n";
            ShellExecuteA(NULL, "open", tutorials[i].get_link().c_str(), NULL, NULL, SW_SHOWNORMAL);
            string like;
            cout << "Do you like the video and want to add it to your watch list? (y/n) type break to stop\nOPTION:";
            getline(cin, like);
            if (like == "break")
                break;
            if (like == "y")
            {
                Tutorial* tutorial_copy = new Tutorial(tutorials[i]);
                services.add_tutorial_watchlist(*tutorial_copy);
                services.increase_likes(i);
                
                delete tutorial_copy;
            }
        }
        if (i == tutorial_count - 1)
            i = 0;
    }

    delete[] tutorials;
}

void openUserCsvInNotepad()
{
    system("notepad.exe user.csv");
}


void UI::start()
{
    //services.initial_10_tutorials();
    services.read_from_file();
    string option;
    while (true)
    {
        cout << "Enter the mode (Administrator or User): ";
        cin >> option;
        if (option == "Administrator")
        {
            cout << "WELCOME C++ MASTER\n";
            int command;
            do
            {
                this->print_menu_administrator();
                cout << "Enter a command: ";
                cin >> command;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(100, '\n');
                    command = -1;
                }
                switch (command)
                {
                case 1:
                    // add tutorial
                    try {
                        string name="", presenter="", link="";
                        int minutes, seconds, likes;
                        cout << "Enter the name of the tutorial: ";
                        cin.clear();
                        cin.ignore(100, '\n');
                        
                        getline(cin, name);
                        cout << "Enter the presenter of the tutorial: ";
                        getline(cin, presenter);
                        cout << "Enter the duration of the tutorial (minutes): ";
                        cin >> minutes;
                        cin.clear();
                        cin.ignore(100, '\n');
                        cout << "Enter the duration of the tutorial (seconds): ";
                        cin >> seconds;
                        cin.clear();
                        cin.ignore(100, '\n');
                        cout << "Enter the number of likes of the tutorial: ";
                        cin >> likes;
                        cin.clear();
                        cin.ignore(100, '\n');
                        cout << "Enter the link of the tutorial: ";
                        getline(cin, link);
                        services.add_tutorial(Tutorial(name, presenter, Time(minutes, seconds), likes, link));
                        services.write_to_file();
                        cout << "Tutorial added successfully!\n";
                    }
                    catch (RepositoryException& error) {
                        cout << "Error: " << error.what() << '\n';
                    }
                    break;
                case 2:
                    try
                    {
                        string name;
                        cout << "Enter the name of the video you want to delete: ";
                        cin.clear();
                        cin.ignore(100, '\n');
                        getline(cin, name);
                        int index = services.find_index(name);
                        services.remove_tutorial(index);
                        services.write_to_file();
                        cout << "Success!\n";
                    }
                    catch (RepositoryException& error)
                    {
                        cout << "Error: " << error.what() << '\n';
                    }
                    break;
                case 3:
                    try
                    {
                        string name;
                        cout << "Enter the name of the tutorial you want to modify: ";
                        cin.clear();
                        cin.ignore(100, '\n');
                        getline(cin, name);
                        int index = services.find_index(name);
                        string new_name, new_presenter, new_link;
                        int new_minutes, new_seconds, new_likes;
                        cout << "Enter the new name: ";
                        std::getline(cin, new_name);
                        cout << "Enter the new presenter: ";
                        std::getline(cin, new_presenter);
                        cout << "Enter the minutes: ";
                        cin >> new_minutes;
                        cin.get();
                        cout << "Enter the seconds: ";
                        cin >> new_seconds;
                        cin.get();
                        cout << "Enter the number of likes: ";
                        cin >> new_likes;
                        cin.get();
                        cout << "Enter the new link: ";
                        getline(cin, new_link);
                        services.update_tutorial(index, Tutorial(new_name, new_presenter, Time(new_minutes, new_seconds), new_likes, new_link));
                        services.write_to_file();
                        cout << "Success!\n";
                    }
                    catch (RepositoryException&)
                    {
                        cout << "Error: No such tutorial found!" << '\n';
                    }
                    break;
                case 4:
                {
                    Tutorial* tutorials = services.get_all_tutorials();
                    int tutorial_count = services.get_size();
                    for (int i = 0; i < tutorial_count; i++) {
                        cout << tutorials[i].toString() << endl;
                    }
                    delete[] tutorials;
                    break;
                }
                case 5:
                {
                    string filename;
                    cin >> filename;
                    services.write_to_file_csv(filename);
                }
                case 0:
                    break;
                default:
                    cout << "Invalid command\n";
                    break;
                }
            } while (command != 0);
        }else
            if (option.compare("User") == 0)
        {
                int command;
            do
                {
                    this->print_menu_user();
                    cout << "Enter a command: ";
                    cin >> command;
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(100, '\n');
                        command = -1;
                    }
                    switch (command)
                    {
                    case 1:
                    {
                        see_tutorials_by_presenter();
                        services.write_to_file_user();
                        break;
                    }
                    case 2:
                    {
                        //Tutorial* tutorials = services.get_all_tutorials_watchlist();
                        //int tutorial_count = services.get_size_watchlist();
                        //for (int i = 0; i < tutorial_count; i++)
                        //{
                        //    cout << tutorials[i].toString() << endl;
                        //}
                        //delete[] tutorials;
                        //services.write_to_file_user();
                        openUserCsvInNotepad();
                        break;
                    }
                    case 3:
                    {
                        try
                            {
                                string title;
                                cin.clear();
                                cin.ignore(100, '\n');
                                cout << "Enter the name of the tutorial you want to remove: ";
                                getline(cin, title);
                                int index = services.find_index_watchlist(title);
                                services.remove_tutorial_watchlist(index);
                                services.write_to_file_user();
                                cout << "Success!\n";
                            }
                        catch (RepositoryException&)
                        {
                            cout << "Error: No such tutorial found!" << '\n';
                        }
                        break;
                    }
                    case 4:
                    {
                    
                        string filename;
                        cin >> filename;
                        services.write_to_file_csv(filename);
                    }
                    case 0:
                        break;
                    default:
                    {
                        cout << "Invalid command!\n";
                        break;
                    }
                    }
                } while (command != 0);
        }
            else if (option == "0")
            {
                break;
            }
            else
                cout << "Invalid option!\n";
    }
}