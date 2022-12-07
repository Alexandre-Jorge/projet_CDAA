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
    QSqlQuery query;

    if(!db.open())
    {
        qDebug() << "Pas de connexion BDD !";
    }
    else
    {
        qDebug() << "Connexion BDD ok";
        query.prepare("DELETE FROM contact");
        qDebug() << "suppression TABLE contact : " << query.exec();
        query.prepare("DELETE FROM interaction");
        qDebug() << "suppression TABLE interaction : " << query.exec();
        query.prepare("DELETE FROM tache");
        qDebug() << "suppression TABLE tache : " << query.exec();
        query.prepare("DELETE FROM LienInterTache");
        qDebug() << "suppression TABLE lienintertache : " << query.exec();

        //boucle sur gestioncontact pour inserer dans TOUTES les tables
        QSqlQuery queryContact;
        QSqlQuery queryInteraction;
        QSqlQuery queryTache;
        QSqlQuery queryLienInterTache;

        queryContact.prepare("INSERT INTO contact VALUES (:i, :n, :pr, :e, :m, :t, :ph, :dc, :dm)");

        queryInteraction.prepare("INSERT INTO interaction VALUES (:i, :c, :d)");

        queryTache.prepare("INSERT INTO tache VALUES (:i, :c, :d)");

        queryLienInterTache.prepare("INSERT INTO LienInterTache VALUES (:i, :idc, :idi, :idt)");

        int nbInteraction = 0;
        int nbTache = 0;
        for(int i=0; i<this->listeContact->taille();i++){
            queryContact.bindValue(":i", i+1);
            queryContact.bindValue(":n", QString::fromStdString(this->listeContact->getContact(i)->getNom()));
            queryContact.bindValue(":pr", QString::fromStdString(this->listeContact->getContact(i)->getPrenom()));
            queryContact.bindValue(":e", QString::fromStdString(this->listeContact->getContact(i)->getEntreprise()));
            queryContact.bindValue(":m", QString::fromStdString(this->listeContact->getContact(i)->getMail()));
            std::list<unsigned> tmpTel = this->listeContact->getContact(i)->getTelephone();
            QString telStr;
            for (std::list<unsigned>::iterator it = tmpTel.begin(); it != tmpTel.end(); ++it){
                telStr += QString::number(*it);
            }
            queryContact.bindValue(":t", telStr);
            queryContact.bindValue(":ph", QString::fromStdString(this->listeContact->getContact(i)->getPhoto()));
            QString dateStr;
            dateStr.append(QString::number(this->listeContact->getContact(i)->getDateCreation().annee) + "-");
            if(this->listeContact->getContact(i)->getDateCreation().mois < 10) dateStr.append("0");
            dateStr.append(QString::number(this->listeContact->getContact(i)->getDateCreation().mois) + "-");
            if(this->listeContact->getContact(i)->getDateCreation().jour < 10) dateStr.append("0");
            dateStr.append(QString::number(this->listeContact->getContact(i)->getDateCreation().jour));
            queryContact.bindValue(":dc", QString(dateStr));
            dateStr = "";
            dateStr.append(QString::number(this->listeContact->getContact(i)->getDateModification().annee) + "-");
            if(this->listeContact->getContact(i)->getDateModification().mois < 10) dateStr.append("0");
            dateStr.append(QString::number(this->listeContact->getContact(i)->getDateModification().mois) + "-");
            if(this->listeContact->getContact(i)->getDateModification().jour < 10) dateStr.append("0");
            dateStr.append(QString::number(this->listeContact->getContact(i)->getDateModification().jour));
            queryContact.bindValue(":dm", QString(dateStr));
            qDebug() << "insert into contact : " << queryContact.exec();
            for(int j=0; j<this->listeContact->getContact(i)->getGlit().taille(); j++){
                nbInteraction++;
                queryInteraction.bindValue(":i", nbInteraction);
                queryInteraction.bindValue(":c", QString::fromStdString(this->listeContact->getContact(i)->getGlit().getLien(j).getI()->getContenu()));
                dateStr = "";
                dateStr.append(QString::number(this->listeContact->getContact(i)->getGlit().getLien(j).getI()->getDateInteract().annee) + "-");
                if(this->listeContact->getContact(i)->getGlit().getLien(j).getI()->getDateInteract().mois < 10) dateStr.append("0");
                dateStr.append(QString::number(this->listeContact->getContact(i)->getGlit().getLien(j).getI()->getDateInteract().mois) + "-");
                if(this->listeContact->getContact(i)->getGlit().getLien(j).getI()->getDateInteract().jour < 10) dateStr.append("0");
                dateStr.append(QString::number(this->listeContact->getContact(i)->getGlit().getLien(j).getI()->getDateInteract().jour));
                queryInteraction.bindValue(":d", QString(dateStr));
                qDebug() << "insert into interaction : " << queryInteraction.exec();
                if(this->listeContact->getContact(i)->getGlit().getLien(j).getT()!=nullptr){
                    nbTache++;
                    queryTache.bindValue(":i", nbTache);
                    queryTache.bindValue(":c", QString::fromStdString(this->listeContact->getContact(i)->getGlit().getLien(j).getT()->getDesc()));
                    dateStr = "";
                    dateStr.append(QString::number(this->listeContact->getContact(i)->getGlit().getLien(j).getT()->getDate().annee) + "-");
                    if(this->listeContact->getContact(i)->getGlit().getLien(j).getT()->getDate().mois < 10) dateStr.append("0");
                    dateStr.append(QString::number(this->listeContact->getContact(i)->getGlit().getLien(j).getT()->getDate().mois) + "-");
                    if(this->listeContact->getContact(i)->getGlit().getLien(j).getT()->getDate().jour < 10) dateStr.append("0");
                    dateStr.append(QString::number(this->listeContact->getContact(i)->getGlit().getLien(j).getT()->getDate().jour));
                    queryTache.bindValue(":d", QString(dateStr));
                    queryLienInterTache.bindValue(":idt", nbTache);
                    qDebug() << "insert into tache : " << queryTache.exec();
                }
                else{
                    queryLienInterTache.bindValue(":idt", QString());
                }
                queryLienInterTache.bindValue(":i", nbInteraction);
                queryLienInterTache.bindValue(":idc", i+1);
                queryLienInterTache.bindValue(":idi", nbInteraction);
                qDebug() << "insert into LienInterTache : " << queryLienInterTache.exec();
            }
        }
        db.close();
    }
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
            listeTacheStr.append(QString::fromStdString(getListeContact()->getContact(item->listWidget()->row(item))->getGlit().getLien(i).getT()->getDesc()) + " ");
            if(getListeContact()->getContact(item->listWidget()->row(item))->getGlit().getLien(i).getT()->getDate().jour < 10)listeTacheStr.append("0");
            listeTacheStr.append(QString::number(getListeContact()->getContact(item->listWidget()->row(item))->getGlit().getLien(i).getT()->getDate().jour) + "/");
            if(getListeContact()->getContact(item->listWidget()->row(item))->getGlit().getLien(i).getT()->getDate().mois < 10)listeTacheStr.append("0");
            listeTacheStr.append(QString::number(getListeContact()->getContact(item->listWidget()->row(item))->getGlit().getLien(i).getT()->getDate().mois) + "/");
            listeTacheStr.append(QString::number(getListeContact()->getContact(item->listWidget()->row(item))->getGlit().getLien(i).getT()->getDate().annee) + "\n");
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

    GestionLienIntertache tmpGlit;
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
                Contact c;
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
       query.prepare("SELECT contact.id_contact, Interaction.contenu, interaction.dateinteract, LienInterTache.id_tache\
                      FROM contact, LienInterTache, Interaction\
                      WHERE contact.id_contact = LienInterTache.id_contact\
                      AND LienInterTache.id_interaction = Interaction.id_interaction");
        if(!query.exec())
        {
            qDebug() << "Impossible d'exécuter la requête !";
        }
        else
        {
            qDebug() << "Requête exécutée";
            GestionLienIntertache * tmpGlit = new GestionLienIntertache();
            int ind = 1;
            while(query.next())
            {
                /*qDebug() << "ID_Contact" <<  query.value(0).toInt();
                qDebug() << "contenu" <<  query.value(1).toString();
                qDebug() << "dateInteract" <<  query.value(2).toString();
                qDebug() << "id_tache" <<  query.value(3).toInt();*/
                if(query.value(0).toInt()!=ind){
                    ind = query.value(0).toInt();
                    delete tmpGlit;
                    tmpGlit = new GestionLienIntertache();
                }
                LienInterTache tmpLit;
                tmpLit.setI(new Interaction(query.value(1).toString().toStdString(), {(unsigned)query.value(2).toDate().day(),(unsigned)query.value(2).toDate().month(),(unsigned)query.value(2).toDate().year()}));
                if(query.value(3).isNull()){
                    tmpLit.setT(nullptr);
                }
                else{
                    QSqlQuery query2;
                    query2.prepare("SELECT desctache, datetache FROM tache WHERE id_tache = :i");
                    query2.bindValue(":i", query.value(3).toInt());
                    if(!query2.exec())
                    {
                        qDebug() << "Impossible d'exécuter la requête !";
                    }
                    else{
                        qDebug() << "Requête exécutée";
                        query2.first();
                        tmpLit.setT(new Tache(query2.value(0).toString().toStdString(), {(unsigned)query2.value(1).toDate().day(),(unsigned)query2.value(1).toDate().month(),(unsigned)query2.value(1).toDate().year()}));
                    }
                }

                tmpGlit->ajouteLien(tmpLit);
                //std::cout << "tmpLit : " << tmpLit << std::endl;
                this->listeContact->getContact(ind-1)->setGlit(*tmpGlit);
                //std::cout << "LitContact : " << *this->getListeContact()->getContact(ind-1) << std::endl;
            }
            delete tmpGlit;
        }
    }
    db.close();
}
