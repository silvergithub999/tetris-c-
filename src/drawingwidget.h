#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include "mangulaud.h"

#include <QWidget>
#include <QMessageBox>
#include <QTimer>

class MainWindow;

class DrawingWidget: public QWidget {
    Q_OBJECT
    public:
        DrawingWidget(MainWindow *parent = 0);
        ~DrawingWidget();
        Mangulaud mangulaud;
        /**
         * Loeb failist skoorid.txt skoorid sisse ja leiab neist 3 parimat skoori.
         * @return - 3 parimat skoori.
         */
        std::vector<int> loeSkoor();
        QTimer *timer;

    public slots:
            /**
             * Liigutab praegust tükki alla.
             */
            void liiguAlla();

    protected:
        void paintEvent(QPaintEvent *event);
        void keyPressEvent(QKeyEvent *event);
        MainWindow *m_mainWindow;

        /**
         * Joonistab tüki.
         * @param t - tükk mida joonistada.
         */
        void joonistaTukk(Tukk t);

        /**
         * Avab teavituse, kus ütleb, et mäng on läbi.
         */
        void mangLabiSonum();

        /**
         * Salvestab saadud skoori skoorid.txt faili.
         */
        void salvestaSkoor();
};

#endif
