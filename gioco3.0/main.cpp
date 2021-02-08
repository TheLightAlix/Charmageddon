#include "Map.cpp"
#include "Player.cpp"

int main() {

    system("pause>nul");
    Map console= Map();
    console.printMap();
    system("pause>nul");
    Player car=Player(&console,2, OCHRE);
    car.printCar(&console);
    bool game= true;
    while(game){
        car.moveCar(&console);
    }
    string carr[4];
    carr[3] = "  _____";
    carr[2] = " /_..._\\";
    carr[1] = "(*[###]*)";
    carr[0] = " []   []";
    string c = carr[0];
    cout<<c.length();
    return 0;
}