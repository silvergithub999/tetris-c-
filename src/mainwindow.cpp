#include "mainwindow.h"

#include <QAction>
#include <QApplication>
#include <QEvent>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QWhatsThis>
#include <iostream>
#include "drawingwidget.h"
#include <string>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //TODO: MUUTA ÕIGEKS SUURUSEKS
    this->setFixedSize(360, 799);

	initWidgets();
    initMenus();
}

MainWindow::~MainWindow() {
    // Intentionally empty
}

/**
  Initializes all menus of this widget.
*/
void MainWindow::initMenus() {
    // Mängu menüü
    m_mangMenu = new QMenu(this);
    m_mangMenu->setTitle(QString("Mäng"));
    menuBar()->addMenu(m_mangMenu);

    //Skoorid.
    m_naitaSkoorid = new QAction(this);
    m_naitaSkoorid->setText(QString("Skoorid"));
    m_mangMenu->addAction(m_naitaSkoorid);
    connect(m_naitaSkoorid, SIGNAL(triggered()), this, SLOT(naitaSkoorid()));

    //Uus mäng.
    m_uusMang = new QAction(this);
    m_uusMang->setText(QString("Uus mäng"));
    m_mangMenu->addAction(m_uusMang);
    connect(m_uusMang, SIGNAL(triggered()), this, SLOT(uusMang()));

}

/**
  Translates all texts of this widget.
*/
void MainWindow::initWidgets() {
    setWindowTitle(QString("Tetris"));

    m_drawingWidget = new DrawingWidget(this);
    setCentralWidget(m_drawingWidget);

    m_mangijaSkoor = new QLabel(this);
    statusBar()->addWidget(m_mangijaSkoor);
}

void MainWindow::uuendaSkoor(){
    char stringSkooriInfo[128];
    snprintf(stringSkooriInfo, sizeof(stringSkooriInfo), "Skoor: %d", m_drawingWidget->mangulaud.tagastaSkoor());
    m_mangijaSkoor->setText(stringSkooriInfo);
}

void MainWindow::uusMang(){
    std::cout << "Alustan uut mängu!" << std::endl;
    m_drawingWidget->mangulaud = Mangulaud();
    m_drawingWidget->timer->start(1000);
}

void MainWindow::naitaSkoorid(){
    std::cout << "Näitan skoore!" << std::endl;
    std::vector<int> skoorid = m_drawingWidget->loeSkoor();

    QMessageBox sonumiAken;
    sonumiAken.setWindowTitle("Skoorid");
    sonumiAken.setFixedSize(600, 600);

    sonumiAken.setText("Top 3 skoori: \n" + QString::number(skoorid.at(0)) + "\n" + QString::number(skoorid.at(1)) + "\n" + QString::number(skoorid.at(2)));
    sonumiAken.setStandardButtons(QMessageBox::Close);
    if(sonumiAken.exec() == QMessageBox::Close){
        sonumiAken.close();
    }
}

