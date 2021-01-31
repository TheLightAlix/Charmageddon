#include "map.hpp"


Map::Map(){
    for (int i = 0;i < horizon;i++){
        for(int j = 0;j < nOfColumns-1;j++){
                matrix[i][j]=' ';
        }
    }
    for (int j = 0;j < nOfColumns-1;j++){
        matrix[horizon][j]='=';
    }
    for (int i = 0;i < nOfLines-horizon-1;i++){
        for (int j = 0;j < nOfColumns-1;j++){
            if(j == colTopLeftRoad-i){
                matrix[horizon+1+i][j]='/';
            }
            else if(j == colTopRightRoad+i){
                matrix[horizon+1+i][j]='\\';
            }
            else{
                matrix[horizon+1+i][j]=' ';
            }
        }
    }
    for(int i = 0;i < nOfLines;i++){
        matrix[i][nOfColumns-1]='\n';
    }
}

void Map::print() { //stampa riga per riga tutti i caratteri della matrice
    for (int i = 0; i < nOfLines; i++) {
        for (int j = 0; j < nOfColumns; j++) {
            cout << matrix[i][j];
        }
    }
}

void Map::set(char character, int line, int column) { //si può immettere nella matrice un carattere nella posizione desiderata
    matrix[line][column]=character;
}
//usiamo nOFColumns-2 perchè nofcolumns -1 è dove ho \n, -2 è il primo spazio indirizzabile.
void Map::defGrass(int grassType, int xCoord) { //definisce e mette sulla mappa i vari tipi di erba.
    switch(grassType){
        case 0:
            set('*',horizon+1,xCoord);
            set('*',horizon+1,nOfColumns-2-xCoord);
            break;
        case 1:
            set('@',horizon+1,xCoord);
            set('|',horizon+2,xCoord);
            set('@',horizon+1,nOfColumns-2-xCoord);
            set('|',horizon+2,nOfColumns-2-xCoord);
            break;
        case 2:
            set('\\',horizon+1,xCoord-1);
            set('|',horizon+1,xCoord);
            set('/',horizon+1,xCoord+1);
            set('\\',horizon+1,nOfColumns-2-xCoord-1);
            set('|',horizon+1,nOfColumns-2-xCoord);
            set('/',horizon+1,nOfColumns-2-xCoord+1);
            break;
        default:
            set('#',horizon+1,xCoord);
            set('#',horizon+1,nOfColumns-2-xCoord);
    }
}

void Map::createLineGrass(){
    srand(time(0)); //inizializziamo il random
    int grassType,xCoord=0, space;
    int numOfGrass=rand()%7;//0-6
    if(numOfGrass > 0){
        int spaceForGrass=(colTopLeftRoad-2)/numOfGrass;//è 20 perchè alcune grass occupano anche x+1.
        //divido la linea di inizio dell'erba per
        // il numero di erba che deve crescere, in modo da avere idea del max spazio tra erba.
        for (int counter = 0; counter < numOfGrass;counter++){
            grassType=rand()%4;
            if(grassType == 2){
                space= rand()%(spaceForGrass-2)+2;//mi serve almeno 2 spazi dalla grass vecchia
            } else{space = rand()%spaceForGrass+1;}
            xCoord+=space;
            defGrass(grassType,xCoord);
            xCoord+=spaceForGrass-space;//per riempire bene gli spazi
        }
    }
}

void Map::runGrass() {
    //cancello l'ultima riga
    for (int j = 0; j < colBottomLeftRoad; j++) {
        set(' ', nOfLines-1, j);
        set(' ', nOfLines-1, colBottomRightRoad+1+j);
    }
    //ora dobbiamo far traslare in prospettiva tutta l'erba, partendo dall'alto
    int leftBorder = colBottomLeftRoad;
    int rightBorder = colBottomRightRoad;
    char charToCopy;
    for(int i = nOfLines-1;i > horizon; i--){
        for(int j = 0; j < leftBorder;j++){
            charToCopy = matrix[i][j];
            if((charToCopy != ' ')&&(j == 0)){
                set(' ',i,j);
            } else if((charToCopy != ' ')&&(j > 0)){
                set(charToCopy,i+1,j-1);
                set(' ',i,j);
            }
        }
        for(int j = rightBorder+1; j < nOfColumns-1; j++) {
            charToCopy = matrix[i][j];
            if ((charToCopy != ' ') && (j == nOfColumns-2)){
                set(' ',i,j);
            } else if((charToCopy != ' ')&&(j < nOfColumns-2)){
                set(charToCopy,i+1,j+1);
                set(' ',i,j);
            }
        }
        rightBorder--;
        leftBorder++;
    }
    createLineGrass();
}
