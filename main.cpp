#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <iomanip>
#include <deque>
#include <conio.h>
#define INPUT unordered_map<char,definitely_human_being>
#define iterated it.second
#define wanted SECOND[ iterated.top() ]


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

    char top() {
        return priorities[0];
    }
    bool more_wants(char option) { //ak osoba dana v parametry je viac chcena tak vrat true inak false
        return ( find(priorities.begin(), priorities.end(), option) <
            find(priorities.begin(), priorities.end(), current_partner) );
    }

};

//potrebne data-structures
unordered_map< char,definitely_human_being > men, women;
deque<char> men_p, women_p;

//na vytvorenie noveho jedinca
definitely_human_being new_human(char name , deque<char> priorities)  {
    definitely_human_being _new_human;
    _new_human.name = name;
    _new_human.is_taken = false;
    _new_human.priorities = priorities;
    return _new_human;
}


//Tato funkcia nam najde najlepsie parovanie a vypise ho
void find_pairing(INPUT FIRST, INPUT SECOND, int numb_of_pairs) {
    int count=0;

    //cyklus opakujuci sa dokym nedosiahneme potrebneho poctu parov
    while (count<numb_of_pairs) {

        for (auto &it : FIRST) {

            if (iterated.is_taken)continue; // ak je vyberajuci zabraty, pokracuj

            if ( !SECOND[ iterated.top() ].is_taken   ) { //ak vyberajuci si vybere niekoho kto nie je zadany, spoja sa

                count++;
                iterated.current_partner = iterated.top(); // navzajom si priradia current partner
                wanted.current_partner = iterated.name;
                wanted.is_taken = true;
                iterated.is_taken = true;

            }
            //ak je momentalna osoba viac chcena, stara sa nastavi na nezadanu
            else if ( wanted.more_wants( iterated.name ) ) {

                FIRST[wanted.current_partner].is_taken = false;
                iterated.is_taken=true;
                iterated.current_partner =  iterated.top() ;
                wanted.current_partner = iterated.name;
            }
            //zbavi sa prveho poradi, pretoze uz je zabraty alebo nepotrebny
            iterated.priorities.pop_front();
        }

    }
    //vypis vysledku
    cout<<"\n";
    for (auto it : FIRST) {
        cout<<naming[iterated.name]<<" - "<< naming[iterated.current_partner] <<"\n";
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
    cout<<"\n";
    if (numb_pairs > 7)
        numb_pairs = 7;
    if (numb_pairs < 3)
        numb_pairs = 3;

    //vytvorenie vectorov na
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