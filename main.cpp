#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <windows.h>
#include <time.h>
#include <conio.h>
using namespace std;

char name[50],fName[50],pPkmn[50] = "1";// player name, player's filename
int cLoc;// current location

void prNot(){cout << "It was not very effective!" << endl;}
void prSup(){cout << "It is super effective!" << endl;}
void grass(int cLoc);
void location(char x, int *);
void menu();
void checkPok(int loc);
void encounter(int x);
int nameCheck(char n[]);
void battle(char pkName[]);
void save(int sLoc);
void plyrPkmn();
int capture(int hp, char pn[]);
float damage(string t1, string t2);
void line(){
    cout << "\n********************************************************************************" << endl;
}

int main(){

    cout << "Enter player name(Numbers not allowed):" << endl;
    cin >> name;
    if(nameCheck(name) == 1){cout << "\nINVALID NAME!\n\nEXITING GAME..."; exit(0);}// checks whether name has digit
    system("cls");
    cout << "Welcome " << name << "!" << endl;
    plyrPkmn();
    strcpy(fName, name);
    strcat(fName, ".txt");
    ifstream oFile(fName);
    oFile >> cLoc;
    if(cLoc < 1 || cLoc > 25){cLoc = 1;}
    grass(cLoc);
    cout << "\nCurrent Location:\n" << cLoc << endl;
    menu();
    cout << "\nYour move:" << endl;
    char mOpt;// menu option
    while(mOpt = getch()){
        location(mOpt, &cLoc);// moves player
        system("cls");
        grass(cLoc);// shows '*' on players location
        checkPok(cLoc);//check for a pokemon on that spot
        menu();
        cout << "\nCurrent Location:\n" << cLoc << endl;
    }
}

// player's pokemon list function
void plyrPkmn(){
    strcat(pPkmn, name);
    strcat(pPkmn, ".txt");
    // checking if user's file already exists
    ifstream check(pPkmn);
    string x;
    check >> x;
    if(x != "Vibrava"){
        // creating file for player's pokemons
        ofstream pkmn(pPkmn);
        pkmn << "Vibrava";
    }
}

// pokemon checking function
void checkPok(int loc){
    srand(time(0));
    // creating five random numbers
    int r1,r2,r3,r4,r5;
    r1 = (rand() % 25) + 1;
    r2 = (rand() % 25) + 1;
    r3 = (rand() % 25) + 1;
    r4 = (rand() % 25) + 1;
    r5 = (rand() % 25) + 1;

    if(loc==r1||loc==r2||loc==r3||loc==r4||loc==r5){
        // choosing random pokemon
        int r6 = (rand() % 100) + 1;
        encounter(r6);
    }
}
// encounter function
void encounter(int x){
    ifstream foe("0pokemonList.txt");
    int rar;// rarity of pokemon
    char pkmn[50];// pokemon name
    while(foe >> rar >> pkmn){
        if(x <= rar){break;}
    }
    system("cls");
    cout << "A wild " << pkmn << " appeared!" << endl;
    battle(pkmn);
}

// damage calc function
float damage(string t1, string t2){
    // t1 is the attack type and t2 is pokemon's type
    if(t2 == "None"){return 1;}
    if(t1 == "Normal"){
            if(t2 == "Steel"){return 0.5;}
            else{return 1;}
    }
    if(t1 == "Fire"){
        if(t2 == "Dragon" || t2 == "Fire" || t2 == "Water"){return 0.5;}
        else if(t2 == "Grass" || t2 == "Steel"){return 2;}
        else{return 1;}
    }
    if(t1 == "Dragon"){
        if(t2 == "Dragon"){return 2;}
        else if(t2 == "Steel"){return 0.5;}
        else{return 1;}
    }
    if(t1 == "Fight"){
        if(t2 == "Steel"){return 2;}
        else if(t2 == "Psychic"){return 0.5;}
        else{return 1;}
    }
    if(t1 == "Grass"){
        if(t2 == "Water" || t2 == "Ground"){return 2;}
        else if(t2 == "Dragon" || t2 == "Fire" || t2 == "Steel" || t2 == "Grass"){return 0.5;}
        else{return 1;}
    }
    if(t1 == "Bug"){
        if(t2 == "Grass" || t2 == "Psychic"){return 2;}
        else if(t2 == "Fire" || t2 == "Steel"){return 0.5;}
        else{return 1;}
    }
    if(t1 == "Water"){
        if(t2 == "Fire" || t2 == "Ground"){return 2;}
        else if(t2 == "Dragon" || t2 == "Water"){return 0.5;}
        else{return 1;}
    }
    if(t1 == "Ground"){
        if(t2 == "Fire" || t2 == "Steel"){return 2;}
        else if(t2 == "Grass"){return 0.5;}
        else{return 1;}
    }
    if(t1 == "Psychic"){
        if(t2 == "Fighting"){return 2;}
        else if(t2 == "Steel" || t2 == "Psychic"){return 0.5;}
        else{return 1;}
    }
    if(t1 == "Steel"){
        if(t2 == "Fire" || t2 == "Steel" || t2 == "Water"){return 0.5;}
        else{return 1;}
    }
    if(t1 == "Dark"){
        if(t2 == "Psychic"){return 2;}
        if(t2 == "Fighting"){return 0.5;}
        else{return 1;}
    }
    if(t1 == "Rock"){
        if(t2 == "Fighting" || t2 == "Ground" || t2 == "Steel"){return 0.5;}
        else if(t2 == "Fire"){return 2;}
        else{return 1;}
    }
}

// battle function
void battle(char pkName[]){
    srand(time(0));
    char pkmn[50] = "0";
    strcat(pkmn, pkName);//pkName is the name of the foe pokemon
    strcat(pkmn,".txt");
    ifstream foe(pkmn);
    string type[2],atkName[4],atkType[4];
    int atkPow[4],acc[4];
    // taking values for foe pokemon i.e. attacks, types...
    foe >> type[0] >> type[1];
    for(int i = 0;i < 4;i++){
        foe.ignore();
        getline(foe, atkName[i]);
        getline(foe, atkType[i]);
        foe >> atkPow[i] >> acc[i];
    }

    // actual battle
    int userHP = 100, foeHP = 100, flag = 0;
    ifstream user(pPkmn);// user's pokemon list
    char uPkmn[50];
    while(user >> uPkmn){
        cout << "\nGo " << uPkmn << "!" << endl;
        userHP = 100;
        char upf[50] = "0";// user's pokemons file
        strcat(upf, uPkmn);
        strcat(upf, ".txt");
        ifstream up(upf);// opening user's pokemons file
        string ut[2],uan[4],uat[4];// user's type, attacks, attack types
        int uap[4],uacc[4];// attack power, accuracy
        up >> ut[0] >> ut[1];
        for(int i = 0;i < 4;i++){
            up.ignore();
            getline(up, uan[i]);
            getline(up, uat[i]);
            up >> uap[i] >> uacc[i];
        }
        while(userHP > 0 && foeHP > 0){
            cout << "\n(r)Run\t(s)Super Potion\t(p)Pokeball" << endl;
            for(int i = 0;i < 4;i++){cout << "(" << i+1 << ")" << uan[i] << "\t";}
            cout << endl;
            char ch;
            cout << "\nYour Option: ";
            cin >> ch;
            if(ch == 'r'){flag = 1;cout <<"\nYou got away safely!" << endl;Sleep(1000);break;}
            if(ch == 's'){
                cout << "\n";
                if(userHP == 100){cout << uPkmn << "'s HP is full!" << endl;}
                else if(userHP >= 80){cout << uPkmn << " restored its HP!" << endl;userHP = 100;}
                else {cout << uPkmn << " restored its HP!" << endl;userHP+=20;}
            }
            if(ch == 'p'){
                if(capture(foeHP, pkName) == 1){flag = 2;break;}
            }
            int rn = (rand() % 100) + 1,frn = (rand() % 100) + 1, fra = (rand() % 4);// random numbers for accuracy and for foe's attack
            int x = int(ch-49);
            if(x == 0 || x == 1 || x == 2 || x == 3){
                cout << "\n" << uPkmn << " used " << uan[x] << endl;
                if(rn <= uacc[x]){
                    cout << "The attack landed!" << endl;
                    float dc = (damage(uat[x], type[0]))*(damage(uat[x], type[1]));// damage calc
                    if(dc <= 0.5){prNot();}
                    else if(dc >= 2){prSup();}
                    foeHP-=(uap[x] * dc);
                }
                else{cout << pkName << " avoided the attack!" << endl;}
            }
            if(foeHP <= 0){cout << pkName << " fainted!" << endl;Sleep(4000);}
            cout << "\nThe wild " << pkName << " used " << atkName[fra] << endl;
            if(frn <= acc[fra]){
                cout << "The foe's attack landed!" << endl;
                float dc = (damage(atkType[fra], ut[0])) * (damage(atkType[fra], ut[1]));// damage calc
                if(dc <= 0.5){prNot();}
                else if(dc >= 2){prSup();}
                userHP-=(atkPow[fra] * dc);
            }
            else{cout << uPkmn << " avoided the attack!" << endl;}
            if(userHP > 0){cout << "\n" << uPkmn << "'s HP:" << userHP << endl;}
            if(userHP <= 0){userHP = 0; cout << "\n" << uPkmn << "'s HP:" << userHP << endl; cout << uPkmn << " fainted!" << endl;Sleep(4000);}
            if(foeHP >= 0){cout << pkName << "'s HP:" << foeHP << endl;}
            line();
        }
        if(flag == 1 || flag == 2){break;}
    }
    if(userHP == 0){system("cls");cout << "\nYou rushed to the nearest Pokemon Center and got your pokemon healed. \nAlways be careful while battling wild pokemon..." << endl;Sleep(4500);}
    else if(flag == 0 || flag == 2){system("cls");cout << "\nYou went to the Pokemon Center and got all of your pokemon healed." << endl;Sleep(3500);}
    system("cls");
    grass(cLoc);
}

// capture function
int capture(int hp, char pn[]){
    srand(time(0));
    int cr;// capture rate
    if(hp <= 15){cr = 25;}
    else if(hp <= 30){cr = 12;}
    else if(hp <= 60){cr = 6;}
    else{cr = 3;}
    int rn = (rand() % 100) + 1;
    if(rn <= cr){
        cout << "\n.";Sleep(1000);cout << " .";Sleep(1000);cout << " .";Sleep(1000);cout << " ." << endl;Sleep(1000);
        cout << "\nYou caught " << pn << "!" << endl;
        ofstream saveData(pPkmn, ios::app);
        saveData << endl << pn;
        Sleep(5000);
        return 1;
    }
    else{
        int rn2 = (rand() % 3) + 1;
        if(rn2 == 1){cout << "\n." << endl;Sleep(1000);cout  << "\nIt broke free!" << endl;}
        else if(rn2 == 2){cout << "\n.";Sleep(1000);cout << " ." << endl;Sleep(1000);cout << "\nAww! It appeared to be caught!" << endl;}
        else{cout << "\n.";Sleep(1000);cout << " .";Sleep(1000);cout << " ." << endl;Sleep(1000);cout << "\nShoot! It was so close too!" << endl;}
        return 0;
    }
}

// grass function
void grass(int cLoc){
    int counter = 1;
    for(int i = 1;i <= 5;i++){
        for(int j = 1;j <= 5;j++){
            cout << "\\|/  ";
        }
        cout << endl << " ";
        for(int j = 1;j <= 5;j++,counter++){
            if(cLoc == counter){cout << "*    ";continue;}
            (counter <= 10)?cout << counter << "    ":cout << counter << "   ";
        }
        cout << endl;
    }
}

// location function
void location(char x, int *loc){
    switch(x){
    case 'w':
        if(*loc < 6){cout << "\nINVALID MOVE!" << endl;Sleep(500);}
        else{*loc-= 5;}
        break;
    case 'a':
        if(*loc < 2){cout << "\nINVALID MOVE!" << endl;Sleep(500);}
        else{*loc-= 1;}
        break;
    case 's':
        if(*loc > 20){cout << "\nINVALID MOVE!" << endl;Sleep(500);}
        else{*loc+= 5;}
        break;
    case 'd':
        if(*loc > 24){cout << "\nINVALID MOVE!" << endl;Sleep(500);}
        else{*loc+= 1;}
        break;
    case 'S':
        int sLoc = *loc;
        save(sLoc);
        break;
    }
}

// saving function
void save(int sLoc){
    ofstream sFile(fName);
    system("cls");
    grass(sLoc);
    cout << "\nDon't turn the system!" << endl;
    cout << "Saving";Sleep(500);cout << ".";Sleep(500);cout << ".";Sleep(500);cout << "." << endl;
    sFile << sLoc;
    sFile.close();
    cout << "Success!" << endl;
    exit(0);
}

// menu function
void menu(){
    cout << "\n(w)Move Up" << endl;
    cout << "(a)Move Left" << endl;
    cout << "(s)Move Down" << endl;
    cout << "(d)Move Right" << endl;
    cout << "(S)Save" << endl;
}

// name checking function
int nameCheck(char n[]){
    int flag = 0;
    for(int i = 0;name[i] != '\0';i++){
        if(isdigit(name[i]) != 0){flag = 1;}
    }
    return flag;
}
