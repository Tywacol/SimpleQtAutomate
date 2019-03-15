#include "autocell.h"
#include <QWidget>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QString>
#include <QTableWidgetItem>


AutoCell::AutoCell(QWidget *parent) : QWidget(parent) {
    num = new QSpinBox(this);
    num->setRange(0,255);
    num->setValue(0);

    numl = new QLabel("Numéro", this);
    numc = new QVBoxLayout;
    numc->addWidget(numl);
    numc->addWidget(num);

    numeroc = new QHBoxLayout;
    numeroc->addLayout(numc);

    zeroOneValidator = new QIntValidator(this);
    zeroOneValidator->setRange(0,1);

    for(unsigned int i = 0; i < 8; i++) {
        numeroBit[i] = new QLineEdit(this);
        numeroBit[i]->setFixedWidth(20);
        numeroBit[i]->setMaxLength(1);
        numeroBit[i]->setText("0");
        numeroBit[i]->setValidator(zeroOneValidator);

        numeroBitl[i] =  new QLabel(this);
        bitc[i] = new QVBoxLayout;
        bitc[i]->addWidget(numeroBit[i]);
        bitc[i]->addWidget(numeroBit[i]);
        numeroc->addLayout(bitc[i]);

        connect(numeroBit[i], SIGNAL(textChanged(QString)),this,
                SLOT(synchronizeNumBitToNum(QString)));
    }

    numeroBit[0]->setText("111");
    numeroBit[1]->setText("110");
    numeroBit[2]->setText("101");
    numeroBit[3]->setText("100");
    numeroBit[4]->setText("011");
    numeroBit[5]->setText("010");
    numeroBit[6]->setText("001");
    numeroBit[7]->setText("000");

    //setLayout(numeroc);

    connect(num, SIGNAL(valueChanged(int)), this,
            SLOT(synchronizeNumToNumBit(int)));

    connect(num, SIGNAL(valueChanged(int)), this,
            SLOT(faireSimulation()));



    unsigned int taille = 25;
    depart = new QTableWidget(1,dimension,this);
    depart->setFixedSize(dimension*taille, taille);
    depart->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    depart->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    depart->horizontalHeader()->setVisible(false);
    depart->verticalHeader()->setVisible(false);
    depart->setFixedHeight(taille);

    couche = new QVBoxLayout;
    couche->addLayout(numeroc);
    couche->addWidget(depart);



    for(unsigned int i=0; i<dimension; i++) {
        depart->setColumnWidth(i,taille);
        depart->setItem(0,i,new QTableWidgetItem(""));
        depart->item(0,i)->setBackgroundColor("white");
        depart->item(0,i)->setTextColor("black");
    }

    connect(depart, SIGNAL(doubleClicked(const QModelIndex&)),
            this, SLOT(cellActivation(const QModelIndex&)));

    QPushButton *simulation= new QPushButton("Simulation", this);
    couche->addWidget(simulation);
    connect(simulation, SIGNAL(clicked(bool)),
             this, SLOT(faireSimulation()));

    //depart = new QTableWidget(1,dimension,this);

    etats = new QTableWidget(dimension, dimension, this);
    etats->setFixedSize(dimension*taille, dimension*taille);
    etats->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    etats->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    etats->horizontalHeader()->setVisible(false);
    etats->verticalHeader()->setVisible(false);
    etats->setEditTriggers(QAbstractItemView::NoEditTriggers);


    for (unsigned int i = 0; i<dimension; i++) {
        etats->setColumnWidth(i,taille);
        etats->setRowHeight(i,taille);
        for (unsigned int j=0; j<dimension; j++) {
            etats->setItem(j,i, new QTableWidgetItem(""));
            etats->item(j,i)->setBackgroundColor("white");
            etats->item(j,i)->setTextColor("black");
        }
    }

    couche->addWidget(etats);
    setLayout(couche);

}

void AutoCell::cellActivation(const QModelIndex& index) {
    if (depart->item(0,index.column())->text()=="") {
        // elle est désactivée => il faut l'activer
        depart->item(0,index.column())->setText("_");
        depart->item(0,index.column())->setBackgroundColor("black");
        depart->item(0,index.column())->setTextColor("black");
    } else {
        // elle est activée => il faut la désactiver
        depart->item(0,index.column())->setText("");
        depart->item(0,index.column())->setBackgroundColor("white");
        depart->item(0,index.column())->setTextColor("white");
    }
}

void AutoCell::synchronizeNumToNumBit(int i) {

    std::string numbit = NumToNumBit(i);
    for (unsigned int i = 0; i < 8; ++i) {
        numeroBit[i]->setText(QString(numbit[i]));
    }

}
void AutoCell::synchronizeNumBitToNum(const QString& s) {

    if (s=="") return;
    std::string str;
    for(unsigned int i=0; i<8; i++) {
        str+=numeroBit[i]->text().toStdString();
    }
    int i=NumBitToNum(str);
    num->setValue(i);

}

void AutoCell::faireSimulation(){
    Etat e(dimension);
    for (unsigned int i = 0; i<dimension; i++) {
        if (depart->item(0,i)->text() !="")  { e.setCellule(i,true); }
    }
    const Automate& A = AutomateManager::getAutomateManager().getAutomate(num->value());
    Simulateur S(A,e);
    for (unsigned int i = 0; i<dimension; i++) {
        S.next();
        const Etat& d=S.dernier();
        for (unsigned int j = 0; j<dimension; j++) {
            if (d.getCellule(j)) {
                etats->item(i,j)->setBackgroundColor("black");
                etats->item(i,j)->setTextColor("black");
            } else {
                etats->item(i,j)->setBackgroundColor("white");
                etats->item(i,j)->setTextColor("white");
            }
        }
    }
}

