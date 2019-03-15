#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QApplication>
#include "autocell.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    AutoCell fenetre;
    fenetre.show();
    return app.exec();
}


/*
int main(int argc, char *argv[]) {
QApplication app(argc, argv);
QWidget *fenetre = new QWidget();
//fenetre->setFixedSize(150, 110);
QLabel *numl = new QLabel("Numéro",fenetre);
QLabel *numeroBitl = new QLabel("NuméroBit",fenetre);
QLineEdit *num = new QLineEdit(fenetre);
QLineEdit *numeroBit = new QLineEdit(fenetre);
QPushButton *ok = new QPushButton("ok", fenetre);

QHBoxLayout *cnum = new QHBoxLayout();
cnum->addWidget(numl);
cnum->addWidget(num);

QHBoxLayout *cNumeroBIt= new QHBoxLayout();
cNumeroBIt->addWidget(numeroBit);
cNumeroBIt->addWidget(numeroBitl);

QVBoxLayout *couche = new QVBoxLayout();
couche->addLayout(cnum);
couche->addLayout(cNumeroBIt);
couche->addWidget(ok);
fenetre->setLayout(couche);




// positionnement
/*
numl->move(10,10);
numeroBitl->move(10,45);
num->move(70,10);
numeroBit->move(70,45);
ok->move(10,80);
*/

// tailles
/*
num->setFixedWidth(25);
numeroBit->setFixedWidth(60);
*/
//ok->setFixedWidth(100);
/*
fenetre->show();
return app.exec();
}


/*
#include <QApplication>
#include <QPushButton>
int main(int argc, char* argv[]) {
QApplication app(argc, argv);
QPushButton *button = new QPushButton("Quitter");
button->show();
QPushButton *buttonCoucou = new QPushButton("Coucou");
buttonCoucou->show();
QObject::connect(button, SIGNAL(clicked(bool)), qApp, SLOT(quit())); // qApp or &app is equivalent
return app.exec();
}
*/
