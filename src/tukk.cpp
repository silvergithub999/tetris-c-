#include <cstdlib>
#include <iostream>
#include "tukk.h"

using namespace std;

Tukk::Tukk() {
    // Suvaline tüki kuju.
    this->millineTukk = rand() % 7;

    // Suvaline värv.
    this->varv = QColor(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);

    int keskX = 5;
    int keskY = -1;

    switch(millineTukk) {
        case 0 :
            /**
             * X O X X
             */
            this->tukiOsad.push_back(Koordinaat(keskX, keskY));
            this->tukiOsad.push_back(Koordinaat(keskX - 1, keskY));
            this->tukiOsad.push_back(Koordinaat(keskX + 1, keskY));
            this->tukiOsad.push_back(Koordinaat(keskX + 2, keskY));
            break;
        case 1 :
            /**
             * X O X
             * X
             */
            this->tukiOsad.push_back(Koordinaat(keskX, keskY));
            this->tukiOsad.push_back(Koordinaat(keskX + 1, keskY));
            this->tukiOsad.push_back(Koordinaat(keskX - 1, keskY));
            this->tukiOsad.push_back(Koordinaat(keskX - 1, keskY + 1));
            break;
        case 2 :
            /**
             * X O X
             *     X
             */
            this->tukiOsad.push_back(Koordinaat(keskX, keskY));
            this->tukiOsad.push_back(Koordinaat(keskX + 1, keskY));
            this->tukiOsad.push_back(Koordinaat(keskX - 1, keskY));
            this->tukiOsad.push_back(Koordinaat(keskX + 1, keskY + 1));
            break;
        case 3 :
            /**
             * O X
             * X X
             */
            this->tukiOsad.push_back(Koordinaat(keskX, keskY));
            this->tukiOsad.push_back(Koordinaat(keskX + 1, keskY));
            this->tukiOsad.push_back(Koordinaat(keskX, keskY + 1));
            this->tukiOsad.push_back(Koordinaat(keskX + 1, keskY + 1));
            break;
        case 4 :
            /**
             *   O X
             * X X
             */
            this->tukiOsad.push_back(Koordinaat(keskX, keskY));
            this->tukiOsad.push_back(Koordinaat(keskX + 1, keskY));
            this->tukiOsad.push_back(Koordinaat(keskX, keskY + 1));
            this->tukiOsad.push_back(Koordinaat(keskX - 1, keskY + 1));
            break;
        case 5 :
            /**
             * X O
             *   X X
             */
            this->tukiOsad.push_back(Koordinaat(keskX, keskY));
            this->tukiOsad.push_back(Koordinaat(keskX - 1, keskY));
            this->tukiOsad.push_back(Koordinaat(keskX, keskY + 1));
            this->tukiOsad.push_back(Koordinaat(keskX + 1, keskY + 1));
            break;
        default :
            /**
             * X O X
             *   X
             */
            this->tukiOsad.push_back(Koordinaat(keskX, keskY));
            this->tukiOsad.push_back(Koordinaat(keskX + 1, keskY));
            this->tukiOsad.push_back(Koordinaat(keskX - 1, keskY));
            this->tukiOsad.push_back(Koordinaat(keskX, keskY + 1));
            break;
    }
}


bool Tukk::onVaba(int x, int y, std::vector<Tukk> kinni){
    if (x < 0 || y < -1 || y > 19 || x > 9){
        return false;
    }

    for (unsigned i = 0; i < kinni.size(); i++){
        Tukk t = kinni.at(i);
        for(unsigned j = 0; j < t.tukiOsad.size(); j++){
            int tx = t.tukiOsad.at(j).x;
            int ty = t.tukiOsad.at(j).y;
            if(tx == x && ty == y){
                return false;
            }
        }
    }
    return true;
}

void Tukk::liiguVasakule(std::vector<Tukk> kinni){
    for(unsigned i = 0; i < tukiOsad.size(); i++){
        int x = tukiOsad.at(i).x - 1;
        int y = tukiOsad.at(i).y;
        if(!onVaba(x, y, kinni)){
            return;
        }
    }

    for(unsigned i = 0; i < tukiOsad.size(); i++){
        tukiOsad.at(i).x -= 1;
    }
}


void Tukk::liiguParemale(std::vector<Tukk> kinni){
    for(unsigned i = 0; i < tukiOsad.size(); i++){
        int x = tukiOsad.at(i).x + 1;
        int y = tukiOsad.at(i).y;
        if(!onVaba(x, y, kinni)){
            return;
        }
    }

    for(unsigned i = 0; i < tukiOsad.size(); i++){
        tukiOsad.at(i).x += 1;
    }
}


bool Tukk::liiguAlla(std::vector<Tukk> kinni) {
    for(unsigned i = 0; i < tukiOsad.size(); i++){
        int x = tukiOsad.at(i).x;
        int y = tukiOsad.at(i).y + 1;
        if(!onVaba(x, y, kinni)){
            return false;
        }
    }

    for(unsigned i = 0; i < tukiOsad.size(); i++){
        tukiOsad.at(i).y += 1;
    }
    return true;
}

void Tukk::keeraParipaeva(std::vector<Tukk> kinni){
    /**
     * Pööramiseks teen (x, y) -> (-y, x).
     * See järel liigutan vanasse keskpunkti tagasi.
     * kus a = vanaX - uusX, b = vanaY - uusY
     */
    if(this->millineTukk == 3){
        //Ruutu pole vaja keerata.
        return;
    }

    Koordinaat kesk = this->tukiOsad.at(0);
    int a = kesk.x + kesk.y;
    int b = kesk.y - kesk.x;
    Koordinaat k0(-tukiOsad.at(0).y + a, tukiOsad.at(0).x + b);
    Koordinaat k1(-tukiOsad.at(1).y + a, tukiOsad.at(1).x + b);
    Koordinaat k2(-tukiOsad.at(2).y + a, tukiOsad.at(2).x + b);
    Koordinaat k3(-tukiOsad.at(3).y + a, tukiOsad.at(3).x + b);
    if(onVaba(k0.x, k0.y, kinni) && onVaba(k1.x, k1.y, kinni) && onVaba(k2.x, k2.y, kinni) && onVaba(k3.x, k3.y, kinni)){
        this->tukiOsad.at(0) = k0;
        this->tukiOsad.at(1) = k1;
        this->tukiOsad.at(2) = k2;
        this->tukiOsad.at(3) = k3;
    }
}

void Tukk::eemaldaReaTukiosad(int rida) {
    for(int n = tukiOsad.size() - 1; n >= 0; n--){
        if(tukiOsad.at(n).y == rida){
            tukiOsad.erase(tukiOsad.begin() + n);
        }
    }
}

