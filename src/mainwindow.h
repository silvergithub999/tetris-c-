#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

class DrawingWidget;
class QMenu;

class MainWindow: public QMainWindow {
    Q_OBJECT
    public:
        MainWindow(QWidget *parent = 0);
        ~MainWindow();

        /**
         * Uuendab skoori Label'it.
         */
        void uuendaSkoor();

    protected:
        void initMenus();
        void initWidgets();

        DrawingWidget *m_drawingWidget;

        QMenu *m_mangMenu;
            QAction *m_naitaSkoorid;
            QAction *m_uusMang;

        QLabel *m_mangijaSkoor;

    private slots:
            /**
             * Alustab uue mängu.
             */
            void uusMang();

            /**
             * Avab akna, kus näitab siiani olnud 3 parimat skoori.
             */
            void naitaSkoorid();
};

#endif
