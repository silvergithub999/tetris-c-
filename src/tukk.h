#ifndef TETRIS_TUKK_H
#define TETRIS_TUKK_H

#include <vector>
#include <QColor>

/**
 * Hoiab koordinaati.
 */
struct Koordinaat {
    /**
     * x koordinaat.
     */
    int x;

    /**
     * y koordinaat.
     */
    int y;

    /**
     * Koordinaadi konstruktor.
     * @param x - x koordinaat.
     * @param y - y koordinaat.
     */
    Koordinaat(int x, int y){
        this->x = x;
        this->y = y;
    }
};

/**
 * Tetrise tüki klass.
 */
class Tukk {
public:
    /**
     * Tüki osade koordinaadid.
     */
    std::vector<Koordinaat> tukiOsad;

    /**
     * Arv, milline tükk on. Täpsemalt, mis arv on mis tükk näeb konstruktorist.
     */
    int millineTukk;

    /**
     * Tüki värv.
     */
    QColor varv;

    /**
     * Tüki konstruktor, genereerib suvalise kuju 7 seast.
     */
    Tukk();

    /**
     * Kontrollib kas antud koordinaat on vaba.
     * @param x - x kordinaat.
     * @param y - y kordinaat.
     * @param kinni - tükid, mis on mängulaual ees, kuhu ei tohi minna.
     * @return true kui on vaba, false kui ei ole.
     */
    bool onVaba(int x, int y, std::vector<Tukk> kinni);

    /**
     * Liigutab tükki vasakule.
     * @param kinni - tükid, mis on mängulaual ees, kuhu ei tohi minna.
     */
    void liiguVasakule(std::vector<Tukk> kinni);

    /**
     * Liigutab tükki paremale.
     * @param kinni - tükid, mis on mängulaual ees, kuhu ei tohi minna.
     */
    void liiguParemale(std::vector<Tukk> kinni);

    /**
     * Liigutab praegust tükki alla.
     * @param kinni - kõik tükid, mis on ees.
     * @return kui sai liikuda, siis true, kui ei saanud, siis false.
     */
    bool liiguAlla(std::vector<Tukk> kinni);

    /**
     * Keerab praegust tükki päripäeva, kui saab.
     * @param kinni - tükid, mis on mängulaual ees, kuhu ei tohi minna.
     */
    void keeraParipaeva(std::vector<Tukk> kinni);

    /**
     * Eemaldab ette antud real olevad tükid.
     * @param rida - rida, kust tükid eemaldada.
     */
    void eemaldaReaTukiosad(int rida);
};

#endif

