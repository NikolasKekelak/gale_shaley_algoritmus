#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <iomanip>
#include <deque>
#include <conio.h>
#define INPUT unordered_map<char,definitely_human_being>

using namespace std;

unordered_map<char, string> naming=
    {
        {'a', "Adela"},
        {'b', "Beth"},
        {'c', "Cyrila"},
        {'d', "Daniela"},
        {'e', "Eva"},
        {'f', "Faye"},
        {'g', "Gabriela"},

        {'h', "Hugo"},
        {'i', "Ivan"},
        {'j', "Joseph"},
        {'k', "Kamil"},
        {'l', "Lucas"},
        {'m', "Michael"},
        {'n', "Nicolas"}

    };

class definitely_human_being {
    public:
        char name;
        bool is_taken;
        char current_partner;
        deque<char> priorities;


    bool more_wants(char option) {
        return ( find(priorities.begin(), priorities.end(), option) <
            find(priorities.begin(), priorities.end(), current_partner) );
    }

};

unordered_map< char,definitely_human_being > men, women;
deque<char> men_p, women_p;

definitely_human_being new_human(char name , deque<char> priorities)  {
    definitely_human_being _new_human;
    _new_human.name = name;
    _new_human.is_taken = false;
    _new_human.priorities = priorities;
    return _new_human;
}

void find_pairing(INPUT FIRST, INPUT SECOND, int numb_of_pairs) {
    int count=0;
    while (count<numb_of_pairs) {

        for (auto &it : FIRST) {

            if (it.second.is_taken) {;continue;} // ak je vyberajuci zabraty, pokracuj

            if ( !SECOND[ it.second.priorities[0] ].is_taken   ) { //ak vyberajuci si vybere niekoho kto nie je zadany, spoja sa
                count++;

                it.second.current_partner = it.second.priorities[0]; // navzajom si priradia current partner
                SECOND[ it.second.priorities[0] ].current_partner = it.second.name;

                SECOND[ it.second.priorities[0] ].is_taken = true;
                it.second.is_taken = true;

            }

            else if ( SECOND[ it.second.priorities[0] ].more_wants( it.second.name ) ) {
                FIRST[SECOND[ it.second.priorities[0] ].current_partner].is_taken = false;

                it.second.is_taken=true;
                it.second.current_partner =  it.second.priorities[0] ;
                SECOND[ it.second.priorities[0] ].current_partner = it.second.name;
            }

            it.second.priorities.pop_front();
        }

    }
    cout<<"\n";
    for (auto it : FIRST) {
        cout<<naming[it.second.name]<<" - "<< naming[it.second.current_partner] <<"\n";
    }
}

deque<char> shuffle_vector(deque<char> input) {
    for (int i = 0 ; i < input.size(); i++) {
        swap(input[i], input[rand() % input.size()]);
    }
    return input;
}

int main() {

    srand(time(NULL));

    int numb_pairs;
    cout<<"Zadaj pocet parov: ";
    cin >> numb_pairs;

    if (numb_pairs > 7)
        numb_pairs = 7;
    if (numb_pairs < 3)
        numb_pairs = 3;

    for (int c='a'; c<('a'+numb_pairs); c++) {
        women_p.push_back( c );
        men_p.push_back( c+7 );
    }
    for (int c='a'; c<('a'+numb_pairs); c++) {
        women[c] = new_human(c, shuffle_vector(men_p));

        men[c+7] = new_human(c+7, shuffle_vector(women_p));
    }

    //vypis
    for (int c='a'; c<('a'+numb_pairs); c++) {
        cout<<setw(10)<< naming[women[c].name]<<" : ";
        for (auto it : women[c].priorities) {
            cout<<setw(3) << it<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    for (int c='a'; c<('a'+numb_pairs); c++) {
        cout<<setw(10)<< naming[men[c+7].name]<<" : ";
        for (auto it : men[c+7].priorities) {
            cout<<setw(3) << it<<" ";
        }
        cout<<endl;
    }
    cout<<"\nChces vidiet vysledok? (klikni hocico)";
    getch();
    cout<<"\nKed prve vyberaju zeny:";
    find_pairing(women, men,numb_pairs);
    cout<<"\nKed prvy vyberaju muzi:";
    find_pairing(men, women,numb_pairs);
    cout<<"\nPre zrusenie okna dvojklikni hocijake tlacitko";
    getch();
    getch();
    return 0;
}