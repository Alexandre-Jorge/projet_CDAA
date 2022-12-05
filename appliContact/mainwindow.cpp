#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <QImage>
#include <QDebug>
#include <exception>
#include "attentevalidationthread.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDate>


MainWindow::MainWindow(QWidget *parent, GestionContact * gc)
    : QMainWindow(parent)
{
    this->setMinimumWidth(400);
    setListeContact(gc);
    connexionBDD();

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


void MainWindow::setListeContact(GestionContact* gc)
{
    this->listeContact = gc;
}

QSqlDatabase MainWindow::getDb()
{
    return this->db;
}

void MainWindow::setDb(QSqlDatabase db)
{
    this->db = db;
}


void MainWindow::affichagePrincipal()
{
    QWidget * centralWidget = new QWidget();;

    QPushButton * boutCreeContact = new QPushButton("Nouveau contact", this);
    connect(boutCreeContact, SIGNAL(clicked()), this, SLOT(affichageCreeContact()));

    QListWidget * widgetListContact = new QListWidget();
    for(int i=0;i<this->getListeContact()->taille();i++){
        widgetListContact->addItem(QString::fromStdString(getListeContact()->getContact(i)->getNom() + " " + getListeContact()->getContact(i)->getPrenom()));
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
    QPushButton * boutRetour = new QPushButton("Retour", this);

    QFormLayout * Layout = new QFormLayout(centralWidget);

    Layout->addRow(boutRetour);
    Layout->addRow(nomLabel, nomLineEdit);
    Layout->addRow(prenomLabel, prenomLineEdit);
    Layout->addRow(entrepriseLabel, entrepriseLineEdit);
    Layout->addRow(mailLabel, mailLineEdit);
    Layout->addRow(telLabel, telLineEdit);
    Layout->addRow(photoLabel, photoLineEdit);
    Layout->addRow(boutValider);


    setCentralWidget(centralWidget);

    AttenteValidationThread * avt = new AttenteValidationThread(nomLineEdit,
                                                                prenomLineEdit,
                                                                entrepriseLineEdit,
                                                                mailLineEdit,
                                                                telLineEdit,
                                                                photoLineEdit);

    connect(avt, SIGNAL(finished()), avt, SLOT(deleteLater()));
    connect(avt, SIGNAL(toCreeContact(QString, QString, QString, QString, QString, QString)), this, SLOT(creeContact(QString, QString, QString, QString, QString, QString)));
    connect(avt, SIGNAL(toAffichagePrincipal()), this, SLOT(affichagePrincipal()));
    connect(boutValider, SIGNAL(clicked()), avt, SLOT(validCreation()));
    connect(boutRetour, SIGNAL(clicked()), avt, SLOT(annulation()));
    avt->start();
}

void MainWindow::creeContact(QString n, QString pr, QString e, QString m, QString t, QString ph)
{
    //convertir le tel en std::list<unsigned>
    std::list<unsigned> tel = std::list<unsigned>();
    for(int i=0;i<t.size();i++){
        tel.push_back((unsigned)(t.at(i).digitValue()));
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
    if(!QString::fromStdString(getListeContact()->getContact(item->listWidget()->row(item))->getPhoto()).isEmpty()){
        photo = new QImage(QString::fromStdString(getListeContact()->getContact(item->listWidget()->row(item))->getPhoto()));
        if(photo->isNull()){
            photo = new QImage("../images/photoDeProfil.jpeg");
        }
    }
    else{
        photo = new QImage("../images/photoDeProfil.jpeg");
    }




    *photo = photo->scaled(100, 100, Qt::KeepAspectRatio);
    QLabel * photoAffichage = new QLabel();
    photoAffichage->setPixmap(QPixmap::fromImage(*photo));
    photoAffichage->setMinimumHeight(100);

    QLabel * nomLabel = new QLabel("Nom");
    QLineEdit * nomLineEdit = new QLineEdit(QString::fromStdString(getListeContact()->getContact(item->listWidget()->row(item))->getNom()));
    QLabel * prenomLabel = new QLabel("Prénom");
    QLineEdit * prenomLineEdit = new QLineEdit(QString::fromStdString(getListeContact()->getContact(item->listWidget()->row(item))->getPrenom()));
    QLabel * entrepriseLabel = new QLabel("Entreprise");
    QLineEdit * entrepriseLineEdit = new QLineEdit(QString::fromStdString(getListeContact()->getContact(item->listWidget()->row(item))->getEntreprise()));
    QLabel * mailLabel = new QLabel("Mail");
    QLineEdit * mailLineEdit = new QLineEdit(QString::fromStdString(getListeContact()->getContact(item->listWidget()->row(item))->getMail()));

    QString telStr = "";
    std::list<unsigned> tmpTel = getListeContact()->getContact(item->listWidget()->row(item))->getTelephone();
    for (std::list<unsigned>::iterator it = tmpTel.begin(); it != tmpTel.end(); ++it){
        telStr += QString::number(*it);
    }

    QLabel * telLabel = new QLabel("Téléphone");
    QLineEdit * telLineEdit = new QLineEdit(telStr);
    QLabel * photoLabel = new QLabel("URL/URI Photo");
    QLineEdit * photoLineEdit = new QLineEdit(QString::fromStdString(getListeContact()->getContact(item->listWidget()->row(item))->getPhoto()));
    QPushButton * boutModifier = new QPushButton("Valider modification",this);
    QPushButton * boutSupprimer = new QPushButton("Supprimer", this);
    QPushButton * boutRetour = new QPushButton("Retour", this);

    QLabel * interactionLabel = new QLabel("Interactions");
    QTextEdit * interactionTextEdit = new QTextEdit();
    /*std::list<Interaction> tmpLi = getListeContact()->getContact(item->listWidget()->row(item))->getLi();
    for (std::list<Interaction>::iterator it = tmpLi.begin(); it != tmpLi.end(); ++it){
        interactionTextEdit->append(QString::fromStdString(it->getContenu()));
    }*/

    for(int i=0; i<getListeContact()->getContact(item->listWidget()->row(item))->getGlit().taille();i++){
        interactionTextEdit->append(QString::fromStdString(getListeContact()->getContact(item->listWidget()->row(item))->getGlit().getLien(i).getI()->getContenu()));
    }

    QLabel * tacheLabel = new QLabel("Liste de tâche");
    QString listeTacheStr = "";
    for(int i=0; i<getListeContact()->getContact(item->listWidget()->row(item))->getGlit().taille();i++){
        if(getListeContact()->getContact(item->listWidget()->row(item))->getGlit().getLien(i).getT()!=nullptr){
            listeTacheStr.append(QString::fromStdString(getListeContact()->getContact(item->listWidget()->row(item))->getGlit().getLien(i).getT()->getDesc()) + " "
                                                        + QString::number(getListeContact()->getContact(item->listWidget()->row(item))->getGlit().getLien(i).getT()->getDate().jour) + "/"
                                                        + QString::number(getListeContact()->getContact(item->listWidget()->row(item))->getGlit().getLien(i).getT()->getDate().mois) + "/"
                                                        + QString::number(getListeContact()->getContact(item->listWidget()->row(item))->getGlit().getLien(i).getT()->getDate().annee) + "\n");
        }
    }
    QLabel * listeTacheLabel = new QLabel(listeTacheStr);
    QFormLayout * Layout = new QFormLayout(centralWidget);

    Layout->addRow(boutRetour);
    Layout->addRow(photoAffichage);
    Layout->addRow(nomLabel, nomLineEdit);
    Layout->addRow(prenomLabel, prenomLineEdit);
    Layout->addRow(entrepriseLabel, entrepriseLineEdit);
    Layout->addRow(mailLabel, mailLineEdit);
    Layout->addRow(telLabel, telLineEdit);
    Layout->addRow(photoLabel, photoLineEdit);
    Layout->addRow(interactionLabel, interactionTextEdit);
    Layout->addRow(tacheLabel, listeTacheLabel);
    Layout->addRow(boutModifier);
    Layout->addRow(boutSupprimer);


    setCentralWidget(centralWidget);

    AttenteValidationThread * avt = new AttenteValidationThread(item->listWidget()->row(item),
                                                                nomLineEdit,
                                                                prenomLineEdit,
                                                                entrepriseLineEdit,
                                                                mailLineEdit,
                                                                telLineEdit,
                                                                photoLineEdit,
                                                                interactionTextEdit);

    connect(avt, SIGNAL(finished()), avt, SLOT(deleteLater()));
    connect(avt, SIGNAL(toModifierContact(unsigned, QString, QString, QString, QString, QString, QString, QString)), this, SLOT(modifierContact(unsigned, QString, QString, QString, QString, QString, QString, QString)));
    connect(avt, SIGNAL(toAffichagePrincipal()), this, SLOT(affichagePrincipal()));
    connect(avt, SIGNAL(toSupprimeContact(unsigned)), this, SLOT(supprimerContact(unsigned)));
    connect(boutModifier, SIGNAL(clicked()), avt, SLOT(validModification()));
    connect(boutSupprimer, SIGNAL(clicked()), avt, SLOT(suppression()));
    connect(boutRetour, SIGNAL(clicked()), avt, SLOT(annulation()));

    avt->start();
}

void MainWindow::modifierContact(unsigned i, QString n, QString pr, QString e, QString m, QString t, QString ph, QString in)
{
    //convertir le tel en std::list<unsigned>
    std::list<unsigned> tel = std::list<unsigned>();
    for(int i=0;i<t.size();i++){
        tel.push_back((unsigned)(t.at(i).digitValue()));
    }

    QStringList interactions = in.split("\n");
    /*std::list<Interaction> tmpLi = std::list<Interaction>();
    for(int i=0;i<interactions.size();i++){
        tmpLi.push_back(Interaction(interactions[i].toStdString()));
    }*/

    GestionLienIntertache tmpGlit = GestionLienIntertache();
    for(int i=0;i<interactions.size();i++){
        //tmpLi.push_back(Interaction(interactions[i].toStdString()));
        tmpGlit.creeLien(new Interaction(interactions[i].toStdString()));
    }

    // modifier les infos du contact
    this->getListeContact()->getContact(i)->setNom(n.toStdString());
    this->getListeContact()->getContact(i)->setPrenom(pr.toStdString());
    this->getListeContact()->getContact(i)->setEntreprise(e.toStdString());
    this->getListeContact()->getContact(i)->setMail(m.toStdString());
    this->getListeContact()->getContact(i)->setTelephone(tel);
    this->getListeContact()->getContact(i)->setPhoto(ph.toStdString());
    this->getListeContact()->getContact(i)->setGlit(tmpGlit);


    emit(toAffichagePrincipal());
}

void MainWindow::supprimerContact(unsigned i)
{
    this->getListeContact()->retireContact(i);
    emit(toAffichagePrincipal());
}

void MainWindow::connexionBDD()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../DB_appliContact.sqlite");
    QSqlQuery query;

    if(!db.open())
    {
        qDebug() << "Pas de connexion BDD !";
    }
    else
    {
        qDebug() << "Connexion BDD ok";
        query.prepare("SELECT * FROM contact");

        if(!query.exec())
        {
            qDebug() << "Impossible d'exécuter la requête !";
        }
        else
        {
            qDebug() << "Requête exécutée";
            while(query.next())
            {
                Contact c = Contact();
                c.setNom(query.value(1).toString().toStdString());
                c.setPrenom(query.value(2).toString().toStdString());
                c.setEntreprise(query.value(3).toString().toStdString());
                c.setMail(query.value(4).toString().toStdString());
                std::list<unsigned> tel = std::list<unsigned>();
                for(int i=0;i<query.value(5).toString().size();i++){
                    tel.push_back((unsigned)(query.value(5).toString().at(i).digitValue()));
                }
                c.setTelephone(tel);
                c.setPhoto(query.value(6).toString().toStdString());
                c.setDateCreation({(unsigned)query.value(7).toDate().day(),(unsigned)query.value(7).toDate().month(),(unsigned)query.value(7).toDate().year()});
                c.setDateModification({(unsigned)query.value(8).toDate().day(),(unsigned)query.value(8).toDate().month(),(unsigned)query.value(8).toDate().year()});
                this->listeContact->ajouteContact(c);
            }
        }
       query.prepare("select contact.id_contact, interaction.contenu, Interaction.dateinteract, Tache.desctache, Tache.datetache\
                       from contact, LienInterTache, Interaction ,tache\
                       where contact.id_lienintertache = LienInterTache.id_lienintertache\
                       and LienInterTache.id_interaction = Interaction.id_interaction\
                       and LienInterTache.id_tache = Tache.id_tache");
        if(!query.exec())
        {
            qDebug() << "Impossible d'exécuter la requête !";
        }
        else
        {
            qDebug() << "Requête exécutée";
            while(query.next())
            {
                /*qDebug() << "ID_Contact" <<  query.value(0).toInt();
                qDebug() << "contenu" <<  query.value(1).toString();
                qDebug() << "dateInteract" <<  query.value(2).toString();
                qDebug() << "descTache" <<  query.value(3).toString();
                qDebug() << "dateTache" <<  query.value(4).toString();*/
                /*LienInterTache tmpLit = LienInterTache();
                Interaction tmpI(query.value(1).toString().toStdString(), {(unsigned)query.value(2).toDate().day(),(unsigned)query.value(2).toDate().month(),(unsigned)query.value(2).toDate().year()});
                Tache tmpT(query.value(3).toString().toStdString(), {(unsigned)query.value(4).toDate().day(),(unsigned)query.value(4).toDate().month(),(unsigned)query.value(4).toDate().year()});
                tmpLit.setI(&tmpI);
                tmpLit.setT(&tmpT);
                std::cout << "tmpLit" << tmpLit ;*/
                this->getListeContact()->getContact(query.value(0).toInt())->getGlit().ajouteLien(LienInterTache(
                                                                                                      new Interaction(query.value(1).toString().toStdString(), {(unsigned)query.value(2).toDate().day(),(unsigned)query.value(2).toDate().month(),(unsigned)query.value(2).toDate().year()}),
                                                                                                      new Tache(query.value(3).toString().toStdString(), {(unsigned)query.value(4).toDate().day(),(unsigned)query.value(4).toDate().month(),(unsigned)query.value(4).toDate().year()})));
                std::cout << "LitContact" << this->getListeContact()->getContact(query.value(0).toInt())->getGlit().getLien(0) ;
            }
        }
    }
}
