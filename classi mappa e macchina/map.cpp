#include "map.hpp"

map::map() { //crea la strada del gioco.
    for(int j=0;j<20;j++){
        for(int i=0;i<120;i++){
            if (i==119){
                matrix[i][j]='\n';
            }
            else if(j==9){
                matrix[i][j]='=';
            }
            else{//27 9     93 9
                if ((i<60)&&(i==36-j)&&(j>9)){
                    matrix[i][j]='/';
                }
                else if((i>60)&&(i==84+j)&&(j>9)){
                    matrix[i][j]='\\';
                }
                else{
                    matrix[i][j]=' ';
                }
            }
        }
    }
}

void map::print() { //stampa riga per riga tutti i caratteri della matrice
        for (int j = 0; j < 20; j++) {
            for (int i = 0; i < 120; i++) {
                cout << matrix[i][j];
            }
        }
}

void map::set(char carattere, int coordx, int coordy) { //si può immettere nella matrice un carattere nella posizione desiderata
    matrix[coordx][coordy]=carattere;
}