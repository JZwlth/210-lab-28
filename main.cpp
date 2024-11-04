#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <random>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

// New declarations
void find_oldest_goat(const list<Goat>& trip);
void find_youngest_goat(const list<Goat>& trip);
void count_goats_by_color(const list<Goat>& trip);
void sort_goats_by_name(list<Goat>& trip);
void sort_goats_by_age(list<Goat>& trip);
void display_goats_older_than(const list<Goat>& trip);
void display_unique_colors(const list<Goat>& trip);
void shuffle_goats(list<Goat>& trip);

int main() {
    srand(time(0));
    bool again;

    // Read and populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // Create and populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }

    int sel = main_menu();
    while (sel != 4) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 5:
                cout << "Finding the oldest goat.\n";
                find_oldest_goat(trip);
                break;
            case 6:
                cout << "Finding the youngest goat.\n";
                find_youngest_goat(trip);
                break;
            case 7:
                cout << "Counting goats by color.\n";
                count_goats_by_color(trip);
                break;
            case 8:
                cout << "Sorting goats by name.\n";
                sort_goats_by_name(trip);
                break;
            case 9:
                cout << "Sorting goats by age.\n";
                sort_goats_by_age(trip);
                break;
            case 10:
                cout << "Displaying goats older than a specified age.\n";
                display_goats_older_than(trip);
                break;
            case 11:
                cout << "Displaying unique colors.\n";
                display_unique_colors(trip);
                break;
            case 12:
                cout << "Shuffling goats.\n";
                shuffle_goats(trip);
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Quit\n";
    cout << "[5] Find the Oldest Goat\n";
    cout << "[6] Find the Youngest Goat\n";
    cout << "[7] Count Goats by Color\n";
    cout << "[8] Sort Goats Alphabetically by Name\n";
    cout << "[9] Sort Goats by Age\n";
    cout << "[10] Display Goats Older Than a Given Age\n";
    cout << "[11] Display Unique Colors\n";
    cout << "[12] Shuffle the List of Goats\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 12) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index - 1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt : trp)
        cout << "\t"
             << "[" << i++ << "] "
             << gt.get_name()
             << " (" << gt.get_age()
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

// Additional functions

void find_oldest_goat(const list<Goat>& trip) {
    auto oldest = max_element(trip.begin(), trip.end(), [](const Goat &a, const Goat &b) {
        return a.get_age() < b.get_age();
    });
    if (oldest != trip.end()) {
        cout << "Oldest Goat: " << oldest->get_name() << " (" << oldest->get_age() << " years old)\n";
    }
}

void find_youngest_goat(const list<Goat>& trip) {
    auto youngest = min_element(trip.begin(), trip.end(), [](const Goat &a, const Goat &b) {
        return a.get_age() < b.get_age();
    });
    if (youngest != trip.end()) {
        cout << "Youngest Goat: " << youngest->get_name() << " (" << youngest->get_age() << " years old)\n";
    }
}

void count_goats_by_color(const list<Goat>& trip) {
    map<string, int> color_count;
    for (const auto &goat : trip) {
        color_count[goat.get_color()]++;
    }
    for (const auto &[color, count] : color_count) {
        cout << color << ": " << count << " goats\n";
    }
}

void sort_goats_by_name(list<Goat>& trip) {
    trip.sort([](const Goat &a, const Goat &b) {
        return a.get_name() < b.get_name();
    });
    cout << "Goats sorted by name.\n";
}

void sort_goats_by_age(list<Goat>& trip) {
    trip.sort([](const Goat &a, const Goat &b) {
        return a.get_age() < b.get_age();
    });
    cout << "Goats sorted by age.\n";
}

void display_goats_older_than(const list<Goat>& trip) {
    int age;
    cout << "Enter the age threshold: ";
    cin >> age;
    cout << "Goats older than " << age << ":\n";
    for (const auto &goat : trip) {
        if (goat.get_age() > age) {
            cout << goat.get_name() << " (" << goat.get_age() << " years old, " << goat.get_color() << ")\n";
        }
    }
}

void display_unique_colors(const list<Goat>& trip) {
    set<string> unique_colors;
    for (const auto &goat : trip) {
        unique_colors.insert(goat.get_color());
    }
    cout << "Unique colors:\n";
    for (const auto &color : unique_colors) {
        cout << color << endl;
    }
}

void shuffle_goats(list<Goat>& trip) {
    vector<Goat> temp(trip.begin(), trip.end()); // Copy list to vector for shuffling
    random_device rd;
    mt19937 g(rd());
    shuffle(temp.begin(), temp.end(), g); // Shuffle the vector
    trip.assign(temp.begin(), temp.end()); // Assign back to list
    cout << "Goats shuffled.\n";
}
