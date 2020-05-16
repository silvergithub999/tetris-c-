#include "mangulaud.h"
#include <iostream>

Mangulaud::Mangulaud() {
    this->skoor = 0;
    praegune = Tukk();
}


bool Mangulaud::uusTukk() {
    this->tukid.push_back(praegune);
    ridaTais();
    Tukk uus;
    //Kontrollin kas uus tükk, mis tekitati saab kuhugi liikuda või kuhugi tekkida.
    for(unsigned i = 0; i < uus.tukiOsad.size(); i++){
        if(!uus.onVaba(uus.tukiOsad.at(i).x, uus.tukiOsad.at(i).y, tukid)){
            return false;
        }
    }
    praegune = uus;
    return true;
}


void Mangulaud::ridaTais() {
    //Reas olevate tükkide loendamiseks array ja täidan selle 0'dega.
    int a[20];
    for(int i = 0; i < 20; i++){
        a[i] = 0;
    }

    //Loendan.
    for (unsigned i = 0; i < tukid.size(); i++){
        Tukk t = tukid.at(i);
        for(int j = 0; j < t.tukiOsad.size(); j++){
            a[t.tukiOsad.at(j).y] += 1;
        }
    }

    //Vaatan, kas kuskil rida täis ja eemaldan need tüki osad.
    for(int i = 0; i < 20; i++){
        if(a[i] == 10){
            //Eemaldan rea.
            for (unsigned h = 0; h < tukid.size(); h++){
                Tukk *t = &tukid.at(h);
                t->eemaldaReaTukiosad(i);
            }
        }
    }

    //Toon kõik üleval olevad read alla 1 võrra.
    for(int i = 0; i < 20; i++){
        if(a[i] == 10){
            lisaSkoor(500);
            tooReadAlla(i);
        }
    }

    //Vaatan, kas mõni tükk on 0 tüki osaga ja eemaldan selle.
    for (int i = tukid.size() - 1; i >= 0; i--){
        Tukk t = tukid.at(i);
        if(t.tukiOsad.size() == 0){
            tukid.erase(tukid.begin() + i);
        }
    }
}

void Mangulaud::tooReadAlla(int rida) {
    for (unsigned h = 0; h < tukid.size(); h++){
        Tukk *t = &tukid.at(h);
        for(int n = 0; n < t->tukiOsad.size(); n++){
            if(t->tukiOsad.at(n).y < rida){
                t->tukiOsad.at(n).y += 1;
            }
        }
    }
}

void Mangulaud::lisaSkoor(int lisada){
    this->skoor += lisada;
}

int Mangulaud::tagastaSkoor(){
    return this->skoor;
}
