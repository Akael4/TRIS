#include <iostream>
#include <string>   
#include <fstream>    

using namespace std;

void casella(int a, int& riga, int& colonna){
 
    if(a<1 || a>9){
        cout<<"scelta non valida"<<endl;
        cout<<"Scegli un numero da 1 a 9"<<endl;
        return;
    }
    else{
    riga = (a - 1)/3 ;    //(3 - 1) / 3 = 2 / 3 = 0 (divisione intera)
    colonna = (a - 1)%3 ; // (3 - 1) % 3 = 2 % 3 = 2 (perchè 2 è 0 volte tre, quindi risultato rimane 2) 
    }

}

void clearGrigglia(){
#ifdef _WIN32
    system("cls");  // per Windows
#else
    system("clear"); // per Linux/macOS
#endif
}

void grigliaAggiornata(char griglia[3][3]){
    for(int r=0; r<3; r++){
        for(int c=0; c<3; c++){                   //aggiorna nuova griglia
        cout << " | " << griglia[r][c] << " | ";
    }
    cout << endl;
    }
}

bool winCheck(const int win[8][3][2], char griglia[3][3]){
    int conteggioX = 0;
    int conteggioO = 0;

    ifstream infile("statistica.txt");
    if (infile.is_open()){
        string skip;
        infile >> skip >> skip >> skip >> conteggioX; //la struttura dentro file statistica.txt è: Win di X/O: <conteggioX/O>
                                                      //per prendere solo il valore del conteggio bisogna skippare "Win" "di" "X/O"
        infile >> skip >> skip >> skip >> conteggioO;
        infile.close();
    }

    for (int i = 0; i < 8; i++) {
        int r1 = win[i][0][0], c1 = win[i][0][1];
        int r2 = win[i][1][0], c2 = win[i][1][1];
        int r3 = win[i][2][0], c3 = win[i][2][1];

    if (griglia[r1][c1] != ' ' &&
        griglia[r1][c1] == griglia[r2][c2] &&
        griglia[r2][c2] == griglia[r3][c3]) {
        char elemento = griglia[r3][c3];
        cout<<"Ha vinto: "<<elemento<<endl;  // prende l'ultimo elemento (X or O) che ha vinto
        
        if(elemento == 'X'){
            conteggioX++;
        }else if (elemento == 'O')conteggioO++;
        
        ofstream file("statistica.txt");

        if(file.is_open()){
            file<<"Win di X: "<<conteggioX<<endl;
            file<<"Win di O: "<<conteggioO<<endl;
            file.close();
            cout << "Salvato in statistica.txt" << endl;
        }
        return true;
        } 

     }

 return false;
}

void punteggio(){
    ifstream infile("statistica.txt");
    string testo;
    string testoX;
    string testoO;
    int puntiX;
    int puntiO;
    if (infile.is_open()){
        while(infile>>testo>>testo>>testoX>>puntiX && infile>>testo>>testo>>testoO>>puntiO){
            for(int i=0; i<19; i++)cout<<"*";
            cout<<endl;
            cout<<"|"<<"Le vincite di "<<testoX<<puntiX<<"|"<<endl;
            cout<<"|"<<"Le vincite di "<<testoO<<puntiO<<"|"<<endl;
            for(int i=0; i<19; i++)cout<<"*";
            cout<<endl;
    }
}else cout<<"errore di apertura del file"<<endl;

infile.close();

}

int main() {
gioco:
    char griglia[3][3]; // nome[r][c] --- r = righe; c = colonne    3x3
    int numeri = 1;
    int riga, colonna;
    char X = 'X';
    char O = 'O';
    const int win[8][3][2] = {
    {{0,0}, {0,1}, {0,2}}, // prima riga
    {{1,0}, {1,1}, {1,2}}, // seconda riga
    {{2,0}, {2,1}, {2,2}}, // terza riga
    {{0,0}, {1,0}, {2,0}}, // prima colonna
    {{0,1}, {1,1}, {2,1}}, // seconda colonna
    {{0,2}, {1,2}, {2,2}}, // terza colonna
    {{0,0}, {1,1}, {2,2}}, // diagonale 
    {{0,2}, {1,1}, {2,0}}  // diagonale 
};
    cout<<"*** LA GRIGLIA DEL GIOCO ***"<<endl;
    cout<<endl;

    for(int r=0; r<3; r++){
        for(int c = 0; c < 3; c++){
            griglia[r][c] = '0' + numeri; // '0' vuol dire che legge 0 perchè è char.
            numeri++;
            cout << " | " << griglia[r][c] << " | ";
        }
        cout << endl;
    }
    cout<<endl;
 

    for(int i = 0; i < 5; i++){
        returno_X:
            int scelta; 
            cout<<"Scegli la casella : ";
            cin>>scelta;
            cout<<endl;

            casella(scelta, riga, colonna);
            if(i == 4){
                if (griglia[riga][colonna] == X || griglia[riga][colonna] == O) {
                    goto pareggio_r;   //siccome il ciclo for non è ancora finito ma tutte le caselle sono occupate, chiama il pareggio
                }
            }
            if (griglia[riga][colonna] == X || griglia[riga][colonna] == O) {
                cout << "Casella gia occupata. Riprova." << endl;
                goto returno_X;
            }
        griglia[riga][colonna] = X;
        clearGrigglia();
        cout<<"*** LA GRIGLIA DEL GIOCO ***"<<endl;
        cout<<"Turno: "<<i + 1<<endl;
        grigliaAggiornata(griglia);
        if(winCheck(win, griglia))goto riprova_r;
        cout<<endl;
        
        if(casella){
            returno_O:
                int scelta1; 
                cout<<"Scegli la casella : ";
                cin>>scelta1;
                cout<<endl;
                
                casella(scelta1, riga, colonna);
                if(i == 4){
                    if (griglia[riga][colonna] == X || griglia[riga][colonna] == O) {
                        goto pareggio_r;   //siccome il ciclo for non è ancora finito ma tutte le caselle sono occupate, chiama il pareggio
                    }
                }
                if (griglia[riga][colonna] == X || griglia[riga][colonna] == O) {
                cout << "Casella gia occupata. Riprova." << endl;
                goto returno_O;
                }
            griglia[riga][colonna] = O;
            clearGrigglia();
            cout<<"*** LA GRIGLIA DEL GIOCO ***"<<endl;
            cout<<"Turno: "<<i + 1<<endl;
            grigliaAggiornata(griglia);
            if(winCheck(win, griglia))goto riprova_r;
            cout<<endl;
           
        }
    }
    pareggio_r:
        if (winCheck(win, griglia) == false){
            cout<<"Pareggio"<<endl;
        }
riprova_r:
    punteggio();
    char riprova;
    cout<<"Vuoi riprovare gioco? (s = si  n = no)"<<endl;
    cin>>riprova;
    if (riprova == 's')goto gioco;
    else if (riprova == 'n')return 0;
    system("pause");
    
    return 0;
}