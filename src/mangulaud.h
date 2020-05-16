#ifndef TETRIS_GAMEBOARD_H
#define TETRIS_GAMEBOARD_H

#include "tukk.h"

/**
 * Mängulaua klass.
 */
class Mangulaud {
public:
    /**
     * Mängulaua konstruktor.
     */
    Mangulaud();

    /**
     * Tükid, mis on mängulaual juba paigas.
     */
    std::vector<Tukk> tukid;

    /**
     * Tükk, mida mängulaual praegu liigutatakse.
     */
    Tukk praegune;


    /**
     * Lisab skoori juurde.
     * @param lisada - skoor, mis kogu skoorile lisada.
     */
    void lisaSkoor(int lisada);


     /**
      * Kui eelmine tükk ei saa enam edasi liikuda, siis tekitab uue tüki.
      * @return true kui saab edasi liikuda, false kui ei saa.
      */
    bool uusTukk();


    /**
     * Kontrollib, kas kuskil on rida täis. Kui on, siis eemaldab selle rea ja toob
     * üleval olevad read alla.
     */
    void ridaTais();


    /**
     * Tagastab skoori.
     * @return skoor.
     */
    int tagastaSkoor();

private:
    /**
     * Mängu skoor.
     */
    int skoor;

    /**
     * Toob antud reast üleval kõik tükid ühe võrra alla.
     * @param rida - rida millest ülevalt alla tuua.
     */
    void tooReadAlla(int rida);
};

#endif
