#include "Map.hpp"
Map::Map() {
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi); // mi prendo le informazioni sulla finestra
    screenWidth = csbi.srWindow.Right;
    screenHeight = csbi.srWindow.Bottom;
    starsAStarts = 1;
    xMiddle = 0.5;
    roadWidth = 0.85; //strada occupa l'85% della finestra
    startLeftRoad = (xMiddle-roadWidth/2)*screenWidth;
    startRightRoad = (xMiddle+roadWidth/2)*screenWidth;
    startGrass();
}
void Map::setCursor(short x,short y) {
    COORD position; //mi definisce una posizione sullo schermo
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),position);
}
void Map::setAndPrintChar(char c,short x, short y) {
    setCursor(x,y);
    cout<<c;
}
void Map::setAndPrintStr(string str, short x, short y, colours col=WHITE) {
    switch(col) {
        case BLUE:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
            break;
        case RED:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            break;
        case GREEN:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            break;
        case OCHRE:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
            break;
        case VIOLET:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_BLUE);
            break;
        case CYAN:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_GREEN);
            break;
        default: ;

    }
    setCursor(x,y);
    cout<<str;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),csbi.wAttributes);//ritorna alla normalità
}

void Map::setAndPrintStrCol(string str[],int length, short x, short y, colours col=WHITE) {
    switch(col) {
        case BLUE:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
            break;
        case RED:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            break;
        case GREEN:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            break;
        case OCHRE:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
            break;
        case VIOLET:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_BLUE);
            break;
        case CYAN:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_GREEN);
            break;
        default: ;

    }
    //stampa per prima l'ultima riga (dello sprite), poi la penultima etc etc
    for(int i = 0; i < length;i++){
        setCursor(x,y-i);
        cout<<str[i];
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),csbi.wAttributes);//ritorna alla normalità
}

void Map::printMap() {
    for(int y = screenHeight;y >(int)(screenHeight/2.3);y--){ //il 2.3 serve per dare più di metà schermo alla strada
        for (int x = 0;x <= screenWidth;x++){
            if(x == (startLeftRoad+screenHeight-y)){ //serve per stampare la strada in prospettiva
                setAndPrintChar('/',x,y);
            }
            else if(x == (startRightRoad-screenHeight+y)){
                setAndPrintChar('\\',x,y);
            }
        }
    }
    //printStars();
    //printGrass();
}

void Map::setCarPos(int x) {
    carPosition = x;
}
int Map::getScreenWidth() {
    return screenWidth;
}
int Map::getScreenHeight() {
    return screenHeight;
}
int Map::getSLR() {
    return startLeftRoad;
}
int Map::getSRR(){
    return startRightRoad;
}
int Map::getELR() {
    return endLeftRoad;
}
int Map::getERR() {
    return endRightRoad;
}
//stars
void Map::printStars() {
    string starA = "*";
    string starB = "   *";
    int spaces = 5;
    // creo starA: "*     *     *     *     *.."
    for(int i = 1;i <= screenWidth;i++){
        if(spaces > 0){
            starA += " ";
            spaces--;
        }else{
            starA += "*";
            spaces=5;
        }
    }
    spaces = 5;
    //creo starB: "   *     *     *     *     *..."
    for(int i = 3;i <= screenWidth;i++){
        if(spaces > 0){
            starB += " ";
            spaces--;
        }else{
            starB += "*";
            spaces=5;
        }
    }
    string stars[(int)(screenHeight/2.8-6)];
    //il triangolo di pericolo arriva ad altezza screenHeight/2.8-6
    //quindi le stelle possono andare da 0 a screenHeight/2.8-7
    if(starsAStarts == 1){
        for(int i = screenHeight/2.8-7;i >= 0;i--){
            if (i%2 == 0){
                stars[i] = starA;
            }else{
                stars[i] = starB;
            }
        }
    }else{
        for(int i = screenHeight/2.8-7;i >= 0;i--){
            if (i%2 == 0){
                stars[i] = starB;
            }else{
                stars[i] = starA;
            }
        }
    }
    starsAStarts = starsAStarts*(-1);//serve per avere l'alternanza le righe di stelle
    setAndPrintStrCol(stars,screenHeight/2.8-6,0,screenHeight/2.8-7,OCHRE);
}
//grass
void Map::startGrass() {
    length = screenHeight-screenHeight/2.3;
    endLeftRoad = startLeftRoad + length;
    endRightRoad = startRightRoad - length;
    create = endLeftRoad-1;
    head = new bilista;
    head->next = nullptr;
    head->prev = head;
    for(int i = 0;i < length;i++){
        insert();
    }
    tail = head->prev;
    tail->next = head;//con queste due info ho creato la mia lista circolare
    srand(time(0));
    random=rand()%5+1; //va da 1 a 5 e mi rappresenta randomicità tra le partite
    createLine(0);//qui ho un create line, tanto è nel costruttore, metto come punteggio 0.
}
void Map::insert() {
    ptrBilista newHead = new bilista;
    string str = " ";
    for(int i = 1;i < create;i++){
        str += " ";
    }
    create--;//creo stringhe di spazi, ma della dimensione giusta della riga che vanno a rappresentare
    newHead->line = str;//per ora li inizializzo tutti così, mi evito delle beghe a esecuzione
    newHead->next = head;
    newHead->prev = head->prev;
    head->prev = newHead;
    head = newHead;
}
void Map::createLine(int score) {
    string line = " ";//default
    int density = score%8+1; //questo numero per stesso punteggio è sempre uguale
    int spaces = endLeftRoad/(density+random); //questo numero per stesso punteggio e stessa partita è uguale
    //nello stesso punto della stessa partita creo sempre la stessa linea
    int copy = spaces;
    string add;
    for(int i = 1;i < endLeftRoad;i++) //parte da 1 perchè stringa ha già un elemento
    {
        if(copy == 0){
            int type = i%5;
            switch(type){
                case 0:
                    add = "#";
                    break;
                case 1:
                    add = "*";
                    break;
                case 2:
                    add = "@";
                    break;
                default:
                    add = " ";
            }
            copy = spaces;
        }else {
            add = " ";
            copy--;
        }
        line += add;
    }
    tail->line =  line; //metto in tail che mi rappresenta la prima riga in alto di erba
}
void Map::printGrass() {
    //parto dalla prima riga, la stampo a sx, la ribalto e la stampo a dx, poi passo alla linea dopo
    ptrBilista tmp = tail;
    int xDx = endRightRoad +1;//dove stampare l'erba a destra
    int firstY=(int)(screenHeight/2.3)+1; //perchè strada in alto arriva fin qui
    string str;
    do {
        str = tmp->line;
        setAndPrintStr(str,0,firstY,GREEN);
        reverse(str.begin(),str.end()); //a destra stampo la stringa ribaltata
        setAndPrintStr(str,xDx,firstY,GREEN);
        tmp = tmp->prev;
        firstY++;
        xDx++;//funziona perchè ho costruito la lista con un certo numero di elementi
    } while (tmp != tail);
}
void Map::runGrass(int score) {
   //while (true) Gamestate == PLAYING {
        //this_thread::chrono  alla stessa vel dei bonus
        //qui parto dall'ultima riga, che prende la penultima riga, troncando la parte più a sx
        //per dare impressione di movimento in prospettiva
        string str;
        ptrBilista tmp = head;
        do {
            str = tmp->next->line;//penultima riga
            str.erase(str.begin());//tolgo il primo carattere della stringa
            tmp->line = str;//ora ha lunghezza compatibile con ultima riga
            tmp = tmp->next;
        } while (tmp != tail);//così per tutte le righe fino alla seconda
        createLine(
                score);//la prima la creo nuova, sennò non avrebbe senso il concept e andrebbe poi a predere l'ultima riga
        //visto che ho lista circolare.
        printGrass();
        printStars();
    //}
}


