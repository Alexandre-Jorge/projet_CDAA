#include "mainwindow.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QDebug>
#include "attentevalidationthread.h"


MainWindow::MainWindow(QWidget *parent, GestionContact * gc, GestionLienIntertache * glit)
    : QMainWindow(parent)
{
    listeContact = gc;
    listeLienInterTache = glit;
    affichagePrincipal();
}

MainWindow::~MainWindow()
{
}

void MainWindow::affichagePrincipal()
{
    QWidget * centralWidget = new QWidget();;
    QPushButton * boutCreeContact = new QPushButton("Nouveau contact", this);
    connect(boutCreeContact, SIGNAL(clicked()), this, SLOT(affichageCreeContact()));

    QListWidget * widgetListContact = new QListWidget();

    QVBoxLayout * Layout = new QVBoxLayout(centralWidget);
    Layout->addWidget(boutCreeContact);
    Layout->addWidget(widgetListContact);

    setCentralWidget(centralWidget);

}

void MainWindow::affichageCreeContact()
{
    QWidget * centralWidget = new QWidget();
    QLabel * nomLabel = new QLabel("Nom");
    QLineEdit * nomLineEdit = new QLineEdit();
    QLabel * prenomLabel = new QLabel("Prénom");
    QLineEdit * prenomLineEdit = new QLineEdit();
    QLabel * entrepriseLabel = new QLabel("Entreprise");
    QLineEdit * entrepriseLineEdit = new QLineEdit();
    QLabel * mailLabel = new QLabel("Mail");
    QLineEdit * mailLineEdit = new QLineEdit();
    QLabel * telLabel = new QLabel("Téléphone");
    QLineEdit * telLineEdit = new QLineEdit();
    QLabel * photoLabel = new QLabel("URL/URI Photo");
    QLineEdit * photoLineEdit = new QLineEdit();
    QPushButton * boutValider = new QPushButton("Valider", this);
    QFormLayout * Layout = new QFormLayout(centralWidget);
    Layout->addWidget(nomLabel);
    Layout->addWidget(nomLineEdit);
    Layout->addWidget(prenomLabel);
    Layout->addWidget(prenomLineEdit);
    Layout->addWidget(entrepriseLabel);
    Layout->addWidget(entrepriseLineEdit);
    Layout->addWidget(mailLabel);
    Layout->addWidget(mailLineEdit);
    Layout->addWidget(telLabel);
    Layout->addWidget(telLineEdit);
    Layout->addWidget(photoLabel);
    Layout->addWidget(photoLineEdit);
    Layout->addWidget(boutValider);
    setCentralWidget(centralWidget);

    AttenteValidationThread * avt = new AttenteValidationThread(nomLineEdit,
                                                                prenomLineEdit,
                                                                entrepriseLineEdit,
                                                                mailLineEdit,
                                                                telLineEdit,
                                                                photoLineEdit);
    connect(avt, SIGNAL(finished()), avt, SLOT(deleteLater()));
    connect(avt, SIGNAL(toCreeContact(QString, QString, QString, QString, QString, QString)), this, SLOT(creeContact(QString, QString, QString, QString, QString, QString)));
    connect(boutValider, SIGNAL(clicked()), avt, SLOT(validation()));
    avt->start();
}

void MainWindow::creeContact(QString n, QString pr, QString e, QString m, QString t, QString ph)
{
    ////TODO/////
    // créer un contact avec les infos saisies
    // ajouter le contact a la liste
    // revenir sur l'affichage principale
    // afficher le contact dans la liste sur l'affichage principal
    qDebug() << n;
    qDebug() << pr;
    qDebug() << e;
    qDebug() << m;
    qDebug() << t;
    qDebug() << ph;
}
