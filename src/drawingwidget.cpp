#include "drawingwidget.h"

#include <QInputDialog>
#include <QPainter>
#include <QLineEdit>
#include <QPaintEvent>
#include "mainwindow.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

/**
  Constructs a drawing widget.
  \param[in] parent parent widget of the drawing widget.
*/
DrawingWidget::DrawingWidget(MainWindow *parent)
    : QWidget(parent), m_mainWindow(parent)
{
    setFocusPolicy( Qt::StrongFocus );

    this->mangulaud = Mangulaud();

    // Jooksutab liiguAlla() pärast igat sekundit.
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(liiguAlla()));
    timer->start(1000);
}

DrawingWidget::~DrawingWidget() {
    // Nothing here yet
}

void DrawingWidget::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Left) {
        std::cout << "Liigun vasakule!" << std::endl;
        this->mangulaud.praegune.liiguVasakule(mangulaud.tukid);
    } else if(event->key() == Qt::Key_Right) {
        std::cout << "Liigun paremale!" << std::endl;
        this->mangulaud.praegune.liiguParemale(mangulaud.tukid);
    } else if(event->key() == Qt::Key_Up) {
        std::cout << "Pööran päripäeva!" << std::endl;
        this->mangulaud.praegune.keeraParipaeva(mangulaud.tukid);
    } else if(event->key() == Qt::Key_Down) {
        liiguAlla();
    } else {
        std::cout << "Tundmatu nupp!" << std::endl;
    }
    m_mainWindow->uuendaSkoor();
    update();
}

/**
  Overridden method to handle all received paint events.
  \param[in] event the paint event that was received.
*/
void DrawingWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(event->rect(), Qt::black);

    // Joonistan praeguse tüki.
    joonistaTukk(this->mangulaud.praegune);

    //Joonistan muud tükid.
    std::vector<Tukk> k = this->mangulaud.tukid;
    for(int i = 0; i < k.size(); i++){
        joonistaTukk(k.at(i));
    }
}

void DrawingWidget::joonistaTukk(Tukk t){
    QPainter painter(this);

    painter.setBrush(QBrush(t.varv));
    std::vector<Koordinaat> r = t.tukiOsad;
    for(int j = 0; j < r.size(); j++){
        int x = r.at(j).x;
        int y = r.at(j).y + 1;
        painter.drawRect(x * 36, y * 36, 36, 36);
    }
}

void DrawingWidget::liiguAlla() {
    std::cout << "Liigun alla!" << std::endl;
    if(!this->mangulaud.praegune.liiguAlla(mangulaud.tukid)){
        if(!mangulaud.uusTukk()){
            std::cout << "Mäng läbi!" << std::endl;
            timer->stop();
            mangLabiSonum();
        }
    } else {
        mangulaud.lisaSkoor(10);
        m_mainWindow->uuendaSkoor();
    }
    update();
}

void DrawingWidget::mangLabiSonum(){
    QMessageBox sonumiAken;
    sonumiAken.setWindowTitle("Mäng läbi");
    char stringMangLabi[256];
    snprintf(stringMangLabi, sizeof(stringMangLabi), "Mäng läbi. \nSkooriks said %d.\nKas tahad alustada uut mängu?", mangulaud.tagastaSkoor());

    sonumiAken.setText(stringMangLabi);
    sonumiAken.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    salvestaSkoor();
    if(sonumiAken.exec() == QMessageBox::Yes){
        mangulaud = Mangulaud();
        timer->start(1000);
    }
    sonumiAken.close();
}

void DrawingWidget::salvestaSkoor(){
    std::ofstream skoorid;
    skoorid.open("skoorid.txt", std::ios_base::app);
    skoorid << mangulaud.tagastaSkoor() << std::endl;
    skoorid.close();
}

std::vector<int> DrawingWidget::loeSkoor(){
    std::vector<int> top3skoori = {0, 0, 0};
    int skoor;
    std::ifstream skoorid;

    skoorid.open("skoorid.txt");
    if (!skoorid) {
        std::cout << "Ei leidnud skooride fail." << std::endl;
    }

    while (skoorid >> skoor) {
        if(skoor > top3skoori.at(0)){
            top3skoori.at(0) = skoor;
        } else if(skoor > top3skoori.at(1)){
            top3skoori.at(1) = skoor;
        } else if(skoor > top3skoori.at(2)){
            top3skoori.at(2) = skoor;
        }
    }
    skoorid.close();
    return top3skoori;
}
