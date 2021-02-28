#include "Map.hpp"

Map::Map() {
    srand(time(0)); // serve per randomizzare la partita per l'erba
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi); //ci salviamo le informazio della console
    screenWidth = csbi.srWindow.Right; //larghezza max della console
    screenHeight = csbi.srWindow.Bottom; //alltezza massima della console
    xMiddle = 0.5;
    roadWidth = 0.85; //strada occupa l'85% della finestra
    startLeftRoad = (xMiddle-roadWidth/2)*screenWidth;
    startRightRoad = (xMiddle+roadWidth/2)*screenWidth;
    startStars(); //serve per inizializzare le variabili legate alle stelle
    startGrass();//serve per inizializzare le variabili legate all'erba
}
void Map::setCursor(short x,short y) {
    COORD position;
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),position); //setto il cursore alla posizione position
}
void Map::setAndPrintChar(char c,short x, short y) {
    setCursor(x,y);
    cout<<c;
}
void Map::chooseColor(colours col) {
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
}

void Map::setAndPrintStr(string str, short x, short y, colours col) {
    chooseColor(col);
    setCursor(x,y);
    cout<<str;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),csbi.wAttributes);//ritorna alla normalità
}

void Map::setAndPrintStrCol(string str[],int length, short x, short y, colours col) {
    chooseColor(col);
    //stampa per prima l'ultima riga (dello sprite passato in input), poi la penultima etc etc
    for(int i = 0; i < length;i++){
        setCursor(x,y-i);
        cout<<str[i];
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),csbi.wAttributes);//ritorna alla normalità
}

void Map::printMap() {
    for(int y = screenHeight;y >= screenHeight/2.3;y--){ //il 2.3 serve per dare più di metà schermo alla strada
        for (int x = 0;x <= screenWidth;x++){
            if(x == (startLeftRoad + screenHeight - y)){
                setAndPrintChar('/',x,y); //disegno la parte sx della strada
            }
            else if(x == (startRightRoad - screenHeight + y)){
                setAndPrintChar('\\',x,y); //disegno la parte destra della strada
            }
        }
    }
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
void Map::startStars() {
    lastStarsMove = chrono::steady_clock::now(); //inizializzo un timer di movimento.
    millisecToMoveStars = 5000; //simulano il movimento ogni 5 secondi
    starsAStarts = 1;
    starsA = "*";
    starsB = "  *";
    int spaces = 3;
    // creo starA: "*   *   *   *   *.." in questo formato
    for(int i = 1;i <= screenWidth;i++){
        if(spaces > 0){
            starsA += " ";
            spaces--;
        }else{
            starsA += "*";
            spaces=3;
        }
    }
    spaces = 3;
    //creo starB: "  *   *   *   *   *..." in questo formato
    for(int i = 3;i <= screenWidth;i++){
        if(spaces > 0){
            starsB += " ";
            spaces--;
        }else{
            starsB += "*";
            spaces=3;
        }
    }
}

void Map::printStars() {
    string stars[(int)(screenHeight/2.8 - 6)];
    if(starsAStarts == 1){
        for(int i = (int)(screenHeight/2.8) - 7;i >= 0;i--){ //riempio l'array, alternando i due tipi di stringhe
            if (i%2 == 0){
                stars[i] = starsA;
            }else{
                stars[i] = starsB;
            }
        }
    }else{
        for(int i =(int)(screenHeight/2.8) - 7;i >= 0;i--){//riempio l'array, alternando i due tipi di stringhe
            if (i%2 == 0){
                stars[i] = starsB;
            }else{
                stars[i] = starsA;
            }
        }
    }
    starsAStarts = starsAStarts * (-1); //prossima volta viene alternata in modo diverso
    setAndPrintStrCol(stars,screenHeight/2.8-6,0,screenHeight/2.8-7,OCHRE);
}
//grass

void Map::startGrass() {
    lastGrassMove =  std::chrono::steady_clock::now(); //inizializzo timer che mi serve per il movimento
    milliSecToMoveGrass = 500; //erba si muove ogni 0.5 secondi
    length = screenHeight-screenHeight/2.3; //quante righe di erba devo avere
    endLeftRoad = startLeftRoad + length;
    endRightRoad = startRightRoad - length;
    create = endLeftRoad-1; //serve per creare le linne fatte di spazi.
    head = new bilista; //è una bilista circolare
    head->next = head;//qui modifica
    head->prev = head;
    for(int i = 0;i < length;i++){
        insert(); //head insert.
    }
    tail = head->prev;
    tail->next = head;
    random=rand()%5+1;
    createLine(0);//qui ho un create line, tanto è costruttore, metto come punteggio 0.
}
void Map::insert() {
    ptrBilista newHead = new bilista;
    string str = " ";
    for(int i = 1;i < create;i++){
        str += " ";
    }
    create--;//creo stringhe di spazi, ma della dimensione giusta.
    newHead->line = str;//per ora li inizializzo tutti con spazi vuoti.
    newHead->next = head;
    newHead->prev = head->prev;
    head->prev->next = newHead; //la tail punta alla testa
    head->prev = newHead;
    head = newHead;
}
void Map::createLine(int score) {
    string line = " ";
    int density = score%10+1; //con punteggi uguali spawno sempre la stessa linea.
    int spaces = endLeftRoad/(density+random);
    int copy = spaces; //serve per mettere il numero giusto di spazi senza perdere il valore di spaces.
    string add;
    for(int i = 1;i < endLeftRoad;i++)
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
    tail->line =  line; //la nuova linea è in fondo alla lista.
}
void Map::printGrass() {
    ptrBilista tmp = tail; //scorro la linea e stampo dall'alto in basso le linee.
    int xDx = endRightRoad + 1;
    int firstY=screenHeight/2.3 + 1;
    string str;
    do {
        str = tmp->line;
        setAndPrintStr(str,0,firstY,GREEN);
        reverseString(&str,0,str.length()-1); // serve per creare l'effetto di erba speculae a sx e dx
        setAndPrintStr(str,xDx,firstY,GREEN);
        tmp = tmp->prev;
        firstY++;
        xDx++;
    } while (tmp != tail); //se torno a tail ho scorso tutta la lista.
}
void Map::reverseString(string *string,int left,int right) {
    if(left >= right){ //caso base in cui ho un solo carattere o una stringa non valida-> inizio dopo la fine
        return;
    }
    else{
        char tmp = (*string)[left];
        (*string)[left] = (*string)[right];
        (*string)[right] = tmp; //scambio i caratteri left e right
        reverseString(string, ++left, --right); //inverto la stringa che va da left+1 a right-1
    }
}

void Map::runGrass(int score) {
    string str;
    ptrBilista tmp = head;
    //prendo una riga a livello superiore e la mette nella riga sotto, diminuendo la lunghezza di uno.
    do {
        str = tmp->next->line;
        str.erase(str.begin()); //elimina il primo carattere perchè per la prospettiva uscirebbe dallo schermo
        tmp->line = str;
        tmp = tmp->next;
    }while(tmp != tail);//per ora rimango così, poi vediamo.
    createLine(score); //crea una nuova riga.
    printGrass(); //stampa tutta l'erba
}

void Map::runDecorations(int score) {
    move = chrono::steady_clock::now();
    //se sono passati milliSecToMoveGrass dall'ultimo movimento, allora muovi grass
    if(timer(lastGrassMove,move, milliSecToMoveGrass)){
        runGrass(score);
        lastGrassMove = chrono::steady_clock::now();//serve a resettare il timer.
    }
    //se sono passati milliSecToMoveStars dall'ultimo movimento, allora muovi stars
    if(timer(lastStarsMove,move,millisecToMoveStars)){
        printStars();
        lastStarsMove = chrono::steady_clock::now();//serve a resettare il timer.
    }
}

bool Map::timer(chrono::steady_clock::time_point timeStart,chrono::steady_clock::time_point timeCheck, float numToMillisec) {
    float elapsedTime = chrono::duration_cast<chrono::milliseconds>(timeCheck - timeStart).count(); //differenza in millisecondi tra timecheck e timestart
    if(elapsedTime >= numToMillisec)
        return true;
    else
        return false;
}