#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QImage>
#include <QDebug>
#include <exception>
#include "attentevalidationthread.h"


MainWindow::MainWindow(QWidget *parent, GestionContact * gc, GestionLienIntertache * glit)
    : QMainWindow(parent)
{
    setListeContact(gc);
    setListeLienInterTache(glit);



    connect(this, SIGNAL(toAffichagePrincipal()), this, SLOT(affichagePrincipal()));
    emit(toAffichagePrincipal());
}

MainWindow::~MainWindow()
{
}

GestionContact* MainWindow::getListeContact()
{
    return this->listeContact;
}

GestionLienIntertache* MainWindow::getListeLienInterTache()
{
    return this->listeLienInterTache;
}

void MainWindow::setListeContact(GestionContact* gc)
{
    this->listeContact = gc;
}

void MainWindow::setListeLienInterTache(GestionLienIntertache * glit)
{
    this->listeLienInterTache = glit;
}


void MainWindow::affichagePrincipal()
{
    QWidget * centralWidget = new QWidget();;

    QPushButton * boutCreeContact = new QPushButton("Nouveau contact", this);
    connect(boutCreeContact, SIGNAL(clicked()), this, SLOT(affichageCreeContact()));

    QListWidget * widgetListContact = new QListWidget();
    for(int i=0;i<this->getListeContact()->taille();i++){
        widgetListContact->addItem(QString::fromStdString(getListeContact()->getContact(i).getNom() + " " + getListeContact()->getContact(i).getPrenom()));
    }
    connect(widgetListContact, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(affichageContact(QListWidgetItem*)));

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
    //convertir le tel en std::list<unsigned>
    std::list<unsigned> tel = std::list<unsigned>();
    for(int i=0;i<t.size();i++){
        for(int j=0;j<10;j++){
            if(t.at(i)=='0'+j){
                tel.push_back(j);
                j=10;
            }
        }
    }

    // créer un contact avec les infos saisies
    Contact c(n.toStdString(), pr.toStdString(),e.toStdString(), m.toStdString(), tel, ph.toStdString());
    // ajouter le contact dans la liste
    this->getListeContact()->ajouteContact(c);
    // revenir sur l'affichage principale
    emit(toAffichagePrincipal());
}

void MainWindow::affichageContact(QListWidgetItem* item)
{
    QWidget * centralWidget = new QWidget();

    QImage * photo;
    photo = new QImage(QString::fromStdString(getListeContact()->getContact(item->listWidget()->row(item)).getPhoto()));

    if(photo->isNull()){
        photo = new QImage("../images/photoDeProfil.jpeg");
    }

    *photo = photo->scaled(100, 100, Qt::KeepAspectRatio);
    QLabel * photoLabel = new QLabel();
    photoLabel->setPixmap(QPixmap::fromImage(*photo));

    QLabel * nomLabel = new QLabel(QString::fromStdString(getListeContact()->getContact(item->listWidget()->row(item)).getNom()
                                                          + " "
                                                          + getListeContact()->getContact(item->listWidget()->row(item)).getPrenom()));

    QLabel * entrepriseLabel = new QLabel(QString::fromStdString("Entreprise : " + getListeContact()->getContact(item->listWidget()->row(item)).getEntreprise()));
    QLabel * mailLabel = new QLabel(QString::fromStdString("Mail : " + getListeContact()->getContact(item->listWidget()->row(item)).getMail()));

    QString telStr = "";
    std::list<unsigned> tmpTel = getListeContact()->getContact(item->listWidget()->row(item)).getTelephone();
    for (std::list<unsigned>::iterator it = tmpTel.begin(); it != tmpTel.end(); ++it){
        telStr += QString::number(*it);
    }
    QLabel * telLabel = new QLabel("Tél : " + telStr);

    QPushButton * boutModifier = new QPushButton("Modifier",this);
    //connect(boutModifier, SIGNAL(clicked()), this, SLOT(/*....*/));
    QVBoxLayout * Layout = new QVBoxLayout(centralWidget);
    Layout->addWidget(photoLabel);
    Layout->addWidget(nomLabel);
    Layout->addWidget(telLabel);
    Layout->addWidget(entrepriseLabel);
    Layout->addWidget(mailLabel);
    Layout->addWidget(boutModifier);

    setCentralWidget(centralWidget);
}
