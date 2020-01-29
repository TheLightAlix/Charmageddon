#include <iostream>

using namespace std;

//scrivere un programma che prende 3 interi e stampa 1 se uno dei
//tre è divisore degli altri due, 0 altrimenti (fare due versioni: una
//con l’if e una senza)

int main() {

int first, second, third;

cout<<"digitare tre numeri interi \n";
cin>>first>>second>>third;
cout<<"i numeri scelti sono : "<<first<<" "<<second<<" "<<third<<endl;

if(((second % first == 0)&&(third % first == 0)) ||
   ((first % second == 0)&&(third % second == 0)) ||
   ((first % third == 0)&&(second % third == 0)))
                                                    cout<<"1 \n";
    return 0;
}