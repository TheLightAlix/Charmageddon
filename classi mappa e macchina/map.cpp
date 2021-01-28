#include "map.hpp"


Map::Map(){
    for (int i=0;i<horizon;i++){
        for(int j=0;j<nOfColumns-1;j++){
                matrix[i][j]=' ';
        }
    }
    for (int j=0;j<nOfColumns-1;j++){
        matrix[horizon][j]='=';
    }
    for (int i=0;i<nOfLines-horizon-1;i++){
        for (int j=0;j<nOfColumns-1;j++){
            if(j==colTopLeftRoad-i){
                matrix[horizon+1+i][j]='/';
            }
            else if(j==colTopRightRoad+i){
                matrix[horizon+1+i][j]='\\';
            }
            else{
                matrix[horizon+1+i][j]=' ';
            }
        }
    }
    for(int i=0;i<nOfLines;i++){
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
