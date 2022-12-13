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

/// @brief constructeur
/// @param QWidget *parent, GestionContact * gc
MainWindow::MainWindow(QWidget *parent, GestionContact * gc)
    : QMainWindow(parent)
{
    this->setMinimumWidth(400);
    setListeContact(gc);
    connexionBDD();

    connect(this, SIGNAL(toAffichagePrincipal()), this, SLOT(affichagePrincipal()));
    emit(toAffichagePrincipal());
}
/// @brief destructeur, il est utilisé egalement pour mettre a jour la bdd lors de la fermeture de l'application
MainWindow::~MainWindow()
{
    QSqlQuery query;

    if(!db.open())//ouverture de la bdd
    {
        qDebug() << "Pas de connexion BDD !";
    }
    else
    {
        //suppression de toute la bdd
        qDebug() << "Connexion BDD ok";
        query.prepare("DELETE FROM contact");
        qDebug() << "suppression TABLE contact : " << query.exec();
        query.prepare("DELETE FROM interaction");
        qDebug() << "suppression TABLE interaction : " << query.exec();
        query.prepare("DELETE FROM tache");
        qDebug() << "suppression TABLE tache : " << query.exec();
        query.prepare("DELETE FROM LienInterTache");
        qDebug() << "suppression TABLE lienintertache : " << query.exec();

        QSqlQuery queryContact;
        QSqlQuery queryInteraction;
        QSqlQuery queryTache;
        QSqlQuery queryLienInterTache;

        //preparation de toutes les requetes pour les insertions dans le bdd
        queryContact.prepare("INSERT INTO contact VALUES (:i, :n, :pr, :e, :m, :t, :ph, :dc, :dm)");

        queryInteraction.prepare("INSERT INTO interaction VALUES (:i, :c, :d)");

        queryTache.prepare("INSERT INTO tache VALUES (:i, :c, :d)");

        queryLienInterTache.prepare("INSERT INTO LienInterTache VALUES (:i, :idc, :idi, :idt)");

        int nbInteraction = 0;
        int nbTache = 0;
        for(unsigned i=0; i < static_cast<unsigned>(this->listeContact->taille());i++){//on parcour la liste de contact
            queryContact.bindValue(":i", i+1);//bind de l'id du contact courant
            queryContact.bindValue(":n", QString::fromStdString(this->listeContact->getContact(i)->getNom()));// bind du nom du contact courant
            queryContact.bindValue(":pr", QString::fromStdString(this->listeContact->getContact(i)->getPrenom()));// bind du prenom du contact courant
            queryContact.bindValue(":e", QString::fromStdString(this->listeContact->getContact(i)->getEntreprise()));// bind de l'entreprise du contact courant
            queryContact.bindValue(":m", QString::fromStdString(this->listeContact->getContact(i)->getMail()));// bind du mail du contact courant
            //conversion du numero de tel en string pour la bdd
            std::list<unsigned> tmpTel = this->listeContact->getContact(i)->getTelephone();
            QString telStr;
            for (std::list<unsigned>::iterator it = tmpTel.begin(); it != tmpTel.end(); ++it){
                telStr += QString::number(*it);
            }

            queryContact.bindValue(":t", telStr);//bind du tel du contact courant
            queryContact.bindValue(":ph", QString::fromStdString(this->listeContact->getContact(i)->getPhoto()));//bind de la photo du contact courant
            //conversion de la date de creation pour la bdd
            QString dateStr;
            dateStr.append(QString::number(this->listeContact->getContact(i)->getDateCreation().annee) + "-");
            if(this->listeContact->getContact(i)->getDateCreation().mois < 10) dateStr.append("0");
            dateStr.append(QString::number(this->listeContact->getContact(i)->getDateCreation().mois) + "-");
            if(this->listeContact->getContact(i)->getDateCreation().jour < 10) dateStr.append("0");
            dateStr.append(QString::number(this->listeContact->getContact(i)->getDateCreation().jour));

            queryContact.bindValue(":dc", QString(dateStr));//bind de la date de creation du contact courant
            //conversion de la date de modification pour la bdd
            dateStr = "";
            dateStr.append(QString::number(this->listeContact->getContact(i)->getDateModification().annee) + "-");
            if(this->listeContact->getContact(i)->getDateModification().mois < 10) dateStr.append("0");
            dateStr.append(QString::number(this->listeContact->getContact(i)->getDateModification().mois) + "-");
            if(this->listeContact->getContact(i)->getDateModification().jour < 10) dateStr.append("0");
            dateStr.append(QString::number(this->listeContact->getContact(i)->getDateModification().jour));

            queryContact.bindValue(":dm", QString(dateStr));//bind de la date de modification du contact courant
            qDebug() << "insert into contact : " << queryContact.exec();//insertion du contact courant dans la bdd

            for(int j=0; j<this->listeContact->getContact(i)->getGlit().taille(); j++){//on parcour la liste de d'interaction/tache du contact courant
                nbInteraction++;
                queryInteraction.bindValue(":i", nbInteraction);//bind de l'id de l'interaction courante
                queryInteraction.bindValue(":c", QString::fromStdString(this->listeContact->getContact(i)->getGlit().getLien(j).getI()->getContenu()));//bind du contenu de l'interaction courante
                //conversion de la date de l'interaction courante pour la bdd
                dateStr = "";
                dateStr.append(QString::number(this->listeContact->getContact(i)->getGlit().getLien(j).getI()->getDateInteract().annee) + "-");
                if(this->listeContact->getContact(i)->getGlit().getLien(j).getI()->getDateInteract().mois < 10) dateStr.append("0");
                dateStr.append(QString::number(this->listeContact->getContact(i)->getGlit().getLien(j).getI()->getDateInteract().mois) + "-");
                if(this->listeContact->getContact(i)->getGlit().getLien(j).getI()->getDateInteract().jour < 10) dateStr.append("0");
                dateStr.append(QString::number(this->listeContact->getContact(i)->getGlit().getLien(j).getI()->getDateInteract().jour));

                queryInteraction.bindValue(":d", QString(dateStr));//bind de la date de l'interaction courante
                qDebug() << "insert into interaction : " << queryInteraction.exec();//insertion de l'interaction courante dans la bdd
                if(this->listeContact->getContact(i)->getGlit().getLien(j).getT()!=nullptr){
                    //si l'interaction est lié a une tache :
                    nbTache++;
                    queryTache.bindValue(":i", nbTache);//bind de l'id de la tache
                    queryTache.bindValue(":c", QString::fromStdString(this->listeContact->getContact(i)->getGlit().getLien(j).getT()->getDesc()));//bind de la description de la tache
                    //conversion de la date de la tache pour la bdd
                    dateStr = "";
                    dateStr.append(QString::number(this->listeContact->getContact(i)->getGlit().getLien(j).getT()->getDate().annee) + "-");
                    if(this->listeContact->getContact(i)->getGlit().getLien(j).getT()->getDate().mois < 10) dateStr.append("0");
                    dateStr.append(QString::number(this->listeContact->getContact(i)->getGlit().getLien(j).getT()->getDate().mois) + "-");
                    if(this->listeContact->getContact(i)->getGlit().getLien(j).getT()->getDate().jour < 10) dateStr.append("0");
                    dateStr.append(QString::number(this->listeContact->getContact(i)->getGlit().getLien(j).getT()->getDate().jour));

                    queryTache.bindValue(":d", QString(dateStr));//bind de la date de la tache courante
                    queryLienInterTache.bindValue(":idt", nbTache);//bind de l'id de la tache dans la table lienInterTache
                    qDebug() << "insert into tache : " << queryTache.exec();//insertion de la tache dans la bdd
                }
                else{
                    //si l'interaction n'est pas lié a une tache :
                    queryLienInterTache.bindValue(":idt", QString());//bind de la valeur NULL pour l'id de la tache dans la table LienInterTache
                }
                queryLienInterTache.bindValue(":i", nbInteraction);//bind de l'id du lien interaction/tache courant
                queryLienInterTache.bindValue(":idc", i+1);//bind de l'id du contact auquel est lié le lien interaction/tache courant
                queryLienInterTache.bindValue(":idi", nbInteraction);//bind de l'id de l'interaction du lien interaction/tache courant
                qDebug() << "insert into LienInterTache : " << queryLienInterTache.exec();//insertion du lien interaction/tache courant
            }
        }
        db.close();//fermeture de la base
    }
}
/// @brief renvoie la liste de contact
/// @return GestionContact*
GestionContact* MainWindow::getListeContact()
{
    return this->listeContact;
}

/// @brief defini une nouvelle liste de contact
/// @param GestionContact* gc
void MainWindow::setListeContact(GestionContact* gc)
{
    this->listeContact = gc;
}
/// @brief renvoie la bdd
/// @return QSqlDatabase
QSqlDatabase MainWindow::getDb()
{
    return this->db;
}
/// @brief defini une nouvelle bdd
/// @param QSqlDatabase db
void MainWindow::setDb(QSqlDatabase db)
{
    this->db = db;
}

/** @brief  applique l'affichage principal dans la fenetre,
 *          on y voit la liste de tous les contact et un bouton pour en creer des nouveau
*/
void MainWindow::affichagePrincipal()
{
    QWidget * centralWidget = new QWidget();;

    QPushButton * boutCreeContact = new QPushButton("Nouveau contact", this);//bouton pour creer un nouveau contact
    connect(boutCreeContact, SIGNAL(clicked()), this, SLOT(affichageCreeContact()));//on lie le click sur ce bouton a l'affichage de l'interface de creation de contact

    QListWidget * widgetListContact = new QListWidget();// regroupe les contact deja cree
    for(unsigned i=0; i < static_cast<unsigned>(this->getListeContact()->taille());i++){//on parcour la liste de tous les contact
        widgetListContact->addItem(QString::fromStdString(getListeContact()->getContact(i)->getNom() + " " + getListeContact()->getContact(i)->getPrenom()));//on affiche dans le widget le nom et le prenom du contact courant
    }
    connect(widgetListContact, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(affichageContact(QListWidgetItem*)));//on lie le click sur un contact a l'affichage de l'interface permettant de visualiser/modifier les infos de ce contact

    //affichage des elements dans la fenetre
    QVBoxLayout * Layout = new QVBoxLayout(centralWidget);
    Layout->addWidget(boutCreeContact);
    Layout->addWidget(widgetListContact);

    setCentralWidget(centralWidget);

}
/** @brief  applique l'affichage de l'interface de creation de contact
 *          on y retrouve tous les champs d'information d'un contact (nom, prenom, etc...)
 *          mais aussi un bouton pour revenir en arrière ou pour valider la creation
*/
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

    // on cree un thread qui prend les champs de saisie en parametre
    // il attend le click sur un bouton (retour ou valider)
    // si le bouton valider est cliqué il verifie les infos puis les envoie a la fonction de creation du contact
    // on utilise un thread car on ne peut pas passer de paramtre via le signal clicked() et cela evite d'avoir
    // plein d'attributs inutile a la class mainwindow
    AttenteValidationThread * avt = new AttenteValidationThread(nomLineEdit,
                                                                prenomLineEdit,
                                                                entrepriseLineEdit,
                                                                mailLineEdit,
                                                                telLineEdit,
                                                                photoLineEdit);

    //connexion des signaux au slots correspondants
    connect(avt, SIGNAL(finished()), avt, SLOT(deleteLater()));
    connect(avt, SIGNAL(toCreeContact(QString, QString, QString, QString, QString, QString)), this, SLOT(creeContact(QString, QString, QString, QString, QString, QString)));
    connect(avt, SIGNAL(toAffichagePrincipal()), this, SLOT(affichagePrincipal()));
    connect(boutValider, SIGNAL(clicked()), avt, SLOT(validCreation()));
    connect(boutRetour, SIGNAL(clicked()), avt, SLOT(annulation()));

    avt->start();//demarrage du thread
}
/// @brief slot de creation du contact
/// @param QString n, QString pr, QString e, QString m, QString t, QString ph
void MainWindow::creeContact(QString n, QString pr, QString e, QString m, QString t, QString ph)
{
    //convertir le tel en std::list<unsigned>
    std::list<unsigned> tel = std::list<unsigned>();
    for(int i=0;i<t.size();i++){
        tel.push_back(static_cast<unsigned>(t.at(i).digitValue()));
    }

    // créer un contact avec les infos saisies
    Contact c(n.toStdString(), pr.toStdString(),e.toStdString(), m.toStdString(), tel, ph.toStdString());
    // ajouter le contact dans la liste
    this->getListeContact()->ajouteContact(c);
    // revenir sur l'affichage principale
    emit(toAffichagePrincipal());
}
/** @brief  applique l'affichage de l'interface de visualisation/modification des infos d'un contact
 *          on y retrouve tous les champs d'information d'un contact (nom, prenom, etc...)
 *          mais aussi un bouton pour revenir en arrière, valider la creation ou supprimer le contact
*/
void MainWindow::affichageContact(QListWidgetItem* item)
{
    QWidget * centralWidget = new QWidget();

    QImage * photo;
    if(!QString::fromStdString(getListeContact()->getContact(static_cast<unsigned>(item->listWidget()->row(item)))->getPhoto()).isEmpty()){
        //si le champs donnant l'URL/URI du contact n'est pas vide :
        //alors on cree une nouvelle QIamge avec l'adresse de l'image saisie
        photo = new QImage(QString::fromStdString(getListeContact()->getContact(static_cast<unsigned>(item->listWidget()->row(item)))->getPhoto()));
        if(photo->isNull()){
            //si l'image n'a pas pu etre cree (URL/URI invalide)
            photo = new QImage("../images/photoDeProfil.jpeg");//alors on applique la photo par defaut presente dans les fichier de l'application
        }
    }
    else{
        //si le champs donnant l'URL/URI du contact est vide :
        photo = new QImage("../images/photoDeProfil.jpeg");//alors on applique la photo par defaut presente dans les fichier de l'application
    }




    *photo = photo->scaled(100, 100, Qt::KeepAspectRatio);// on redimensionne l'image pour qu'elle fasse 100x100 px en conservant les proportions
    QLabel * photoAffichage = new QLabel();
    photoAffichage->setPixmap(QPixmap::fromImage(*photo));//on affiche l'image dans un QLabel
    photoAffichage->setMinimumHeight(100);//on defini une taille minimum de la photo dans la fenetre (100px en hauteur)

    QLabel * nomLabel = new QLabel("Nom");
    QLineEdit * nomLineEdit = new QLineEdit(QString::fromStdString(getListeContact()->getContact(static_cast<unsigned>(item->listWidget()->row(item)))->getNom()));
    QLabel * prenomLabel = new QLabel("Prénom");
    QLineEdit * prenomLineEdit = new QLineEdit(QString::fromStdString(getListeContact()->getContact(static_cast<unsigned>(item->listWidget()->row(item)))->getPrenom()));
    QLabel * entrepriseLabel = new QLabel("Entreprise");
    QLineEdit * entrepriseLineEdit = new QLineEdit(QString::fromStdString(getListeContact()->getContact(static_cast<unsigned>(item->listWidget()->row(item)))->getEntreprise()));
    QLabel * mailLabel = new QLabel("Mail");
    QLineEdit * mailLineEdit = new QLineEdit(QString::fromStdString(getListeContact()->getContact(static_cast<unsigned>(item->listWidget()->row(item)))->getMail()));

    //conversion du tel en string pour l'affichage
    QString telStr = "";
    std::list<unsigned> tmpTel = getListeContact()->getContact(static_cast<unsigned>(item->listWidget()->row(item)))->getTelephone();
    for (std::list<unsigned>::iterator it = tmpTel.begin(); it != tmpTel.end(); ++it){
        telStr += QString::number(*it);
    }

    QLabel * telLabel = new QLabel("Téléphone");
    QLineEdit * telLineEdit = new QLineEdit(telStr);
    QLabel * photoLabel = new QLabel("URL/URI Photo");
    QLineEdit * photoLineEdit = new QLineEdit(QString::fromStdString(getListeContact()->getContact(static_cast<unsigned>(item->listWidget()->row(item)))->getPhoto()));
    QPushButton * boutModifier = new QPushButton("Valider modification",this);
    QPushButton * boutSupprimer = new QPushButton("Supprimer", this);
    QPushButton * boutRetour = new QPushButton("Retour", this);

    QLabel * interactionLabel = new QLabel("Interactions");
    QTextEdit * interactionTextEdit = new QTextEdit();

    //affichage des interactions du contact dans un QTextEdit
    for(int i=0; i<getListeContact()->getContact(static_cast<unsigned>(item->listWidget()->row(item)))->getGlit().taille();i++){
        interactionTextEdit->append(QString::fromStdString(getListeContact()->getContact(static_cast<unsigned>(item->listWidget()->row(item)))->getGlit().getLien(i).getI()->getContenu()));
    }

    //affichage des taches du contact dans un QLabel
    QLabel * tacheLabel = new QLabel("Liste de tâche");
    QString listeTacheStr = "";
    for(int i=0; i<getListeContact()->getContact(static_cast<unsigned>(item->listWidget()->row(item)))->getGlit().taille();i++){
        if(getListeContact()->getContact(static_cast<unsigned>(item->listWidget()->row(item)))->getGlit().getLien(i).getT()!=nullptr){
            listeTacheStr.append(QString::fromStdString(getListeContact()->getContact(static_cast<unsigned>(item->listWidget()->row(item)))->getGlit().getLien(i).getT()->getDesc()) + " ");
            if(getListeContact()->getContact(static_cast<unsigned>(item->listWidget()->row(item)))->getGlit().getLien(i).getT()->getDate().jour < 10)listeTacheStr.append("0");
            listeTacheStr.append(QString::number(getListeContact()->getContact(static_cast<unsigned>(item->listWidget()->row(item)))->getGlit().getLien(i).getT()->getDate().jour) + "/");
            if(getListeContact()->getContact(static_cast<unsigned>(item->listWidget()->row(item)))->getGlit().getLien(i).getT()->getDate().mois < 10)listeTacheStr.append("0");
            listeTacheStr.append(QString::number(getListeContact()->getContact(static_cast<unsigned>(item->listWidget()->row(item)))->getGlit().getLien(i).getT()->getDate().mois) + "/");
            listeTacheStr.append(QString::number(getListeContact()->getContact(static_cast<unsigned>(item->listWidget()->row(item)))->getGlit().getLien(i).getT()->getDate().annee) + "\n");
        }
    }
    QLabel * listeTacheLabel = new QLabel(listeTacheStr);
    QFormLayout * Layout = new QFormLayout(centralWidget);

    //affichage des elements dans la fenetre
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

    //utilisation d'un thread (voir affichageCreeContact())
    // la difference ici est qu'on passe egalement l'indice du contact dans le liste ainsi que la liste d'interaction
    AttenteValidationThread * avt = new AttenteValidationThread(static_cast<unsigned>(item->listWidget()->row(item)),
                                                                nomLineEdit,
                                                                prenomLineEdit,
                                                                entrepriseLineEdit,
                                                                mailLineEdit,
                                                                telLineEdit,
                                                                photoLineEdit,
                                                                interactionTextEdit);

    //connexion des signaux aux slots correspondants
    connect(avt, SIGNAL(finished()), avt, SLOT(deleteLater()));
    connect(avt, SIGNAL(toModifierContact(unsigned, QString, QString, QString, QString, QString, QString, QString)), this, SLOT(modifierContact(unsigned, QString, QString, QString, QString, QString, QString, QString)));
    connect(avt, SIGNAL(toAffichagePrincipal()), this, SLOT(affichagePrincipal()));
    connect(avt, SIGNAL(toSupprimeContact(unsigned)), this, SLOT(supprimerContact(unsigned)));
    connect(boutModifier, SIGNAL(clicked()), avt, SLOT(validModification()));
    connect(boutSupprimer, SIGNAL(clicked()), avt, SLOT(suppression()));
    connect(boutRetour, SIGNAL(clicked()), avt, SLOT(annulation()));

    avt->start();//demarrage du thread
}
/// @brief slot de modification des informations d'un contact
/// @param unsigned i, QString n, QString pr, QString e, QString m, QString t, QString ph, QString in
void MainWindow::modifierContact(unsigned i, QString n, QString pr, QString e, QString m, QString t, QString ph, QString in)
{
    //convertir le tel en std::list<unsigned>
    std::list<unsigned> tel = std::list<unsigned>();
    for(int i=0;i<t.size();i++){
        tel.push_back(static_cast<unsigned>(t.at(i).digitValue()));
    }

    QStringList interactions = in.split("\n");//on place chaque ligne de saisie des interaction dans une liste que l'on peut parcourir
    GestionLienIntertache tmpGlit;
    for(int i=0;i<interactions.size();i++){//on parcour la liste contenant la saise d'interaction
        tmpGlit.creeLien(new Interaction(interactions[i].toStdString()));//on cree un lien interaction/tache (la fonction cree verfiie les tags voir definition dans gestionlienintertache.cpp)
    }

    // modifier les infos du contact
    this->getListeContact()->getContact(i)->setNom(n.toStdString());
    this->getListeContact()->getContact(i)->setPrenom(pr.toStdString());
    this->getListeContact()->getContact(i)->setEntreprise(e.toStdString());
    this->getListeContact()->getContact(i)->setMail(m.toStdString());
    this->getListeContact()->getContact(i)->setTelephone(tel);
    this->getListeContact()->getContact(i)->setPhoto(ph.toStdString());
    this->getListeContact()->getContact(i)->setGlit(tmpGlit);


    emit(toAffichagePrincipal());//retour a l'affichage principal
}
/// @brief slot de suppression d'un contact
/// @param unsigned i
void MainWindow::supprimerContact(unsigned i)
{
    this->getListeContact()->retireContact(i);//suppression du contact d'indice i dans la liste de contact
    emit(toAffichagePrincipal());//retour a l'affichage principal
}
/** @brief fonction permettant d'ouvrir et de lire les donnees contenu dans la bdd
 *         elle est appele dans le constructeur de la mainwindow
*/
void MainWindow::connexionBDD()
{
    //configuration de la bdd
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../DB_appliContact.sqlite");
    QSqlQuery query;

    if(!db.open())//ouverture de la bdd
    {
        qDebug() << "Pas de connexion BDD !";
    }
    else
    {
        qDebug() << "Connexion BDD ok";
        query.prepare("SELECT * FROM contact");//selection de tous les contacts de la base

        if(!query.exec())
        {
            qDebug() << "Impossible d'exécuter la requête !";
        }
        else
        {
            qDebug() << "Requête exécutée";
            while(query.next())//parcour la liste de contact renvoye par la requete
            {
                Contact c;//creation d'un nouveau contact
                //on affecte les valeurs de la base aux attributs du contact
                c.setNom(query.value(1).toString().toStdString());
                c.setPrenom(query.value(2).toString().toStdString());
                c.setEntreprise(query.value(3).toString().toStdString());
                c.setMail(query.value(4).toString().toStdString());
                //conversion du tel en std::list<unsigned>
                std::list<unsigned> tel = std::list<unsigned>();
                for(int i=0;i<query.value(5).toString().size();i++){
                    tel.push_back(static_cast<unsigned>(query.value(5).toString().at(i).digitValue()));
                }
                c.setTelephone(tel);
                c.setPhoto(query.value(6).toString().toStdString());
                c.setDateCreation({static_cast<unsigned>(query.value(7).toDate().day()),static_cast<unsigned>(query.value(7).toDate().month()),static_cast<unsigned>(query.value(7).toDate().year())});
                c.setDateModification({static_cast<unsigned>(query.value(8).toDate().day()),static_cast<unsigned>(query.value(8).toDate().month()),static_cast<unsigned>(query.value(8).toDate().year())});
                this->listeContact->ajouteContact(c);//on ajoute le contact dans le liste de contact
            }
        }
        // selection de l'id du contact, du contenu + de la date + de l'id de la tache lie a une interaction lie au contact
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
            unsigned ind = 1;
            while(query.next())
            {
                if(query.value(0).toUInt()!=ind){
                    //si l'id du contact selectionne est different de ind cela signifie que toutes les interaction de ce contact ont ete parcouru donc on change ind pour l'id du prochain contact
                    ind = query.value(0).toUInt();
                    delete tmpGlit;
                    tmpGlit = new GestionLienIntertache();
                }
                LienInterTache tmpLit;
                //on defini une nouvelle interaction avec le contenu et la date contenu dans la bdd
                tmpLit.setI(new Interaction(query.value(1).toString().toStdString(), {static_cast<unsigned>(query.value(2).toDate().day()),static_cast<unsigned>(query.value(2).toDate().month()),static_cast<unsigned>(query.value(2).toDate().year())}));
                if(query.value(3).isNull()){
                    // si aucune tache n'est lie a l'interaction
                    tmpLit.setT(nullptr);//on affecte nullptr a la reference de la tache dans le lien interaction/tache
                }
                else{
                    // si une tache est lie a l'interaction
                    QSqlQuery query2;
                    query2.prepare("SELECT desctache, datetache FROM tache WHERE id_tache = :i");//on selectionne la description et la date de la tache en question
                    query2.bindValue(":i", query.value(3).toInt());
                    if(!query2.exec())
                    {
                        qDebug() << "Impossible d'exécuter la requête !";
                    }
                    else{
                        qDebug() << "Requête exécutée";
                        query2.first();
                        //on defini une nouvelle tache avec la description et la date contenu dans la bdd
                        tmpLit.setT(new Tache(query2.value(0).toString().toStdString(), {static_cast<unsigned>(query2.value(1).toDate().day()),static_cast<unsigned>(query2.value(1).toDate().month()),static_cast<unsigned>(query2.value(1).toDate().year())}));
                    }
                }

                tmpGlit->ajouteLien(tmpLit);//on ajoute le lien a la liste de lien interaction/tache
                this->listeContact->getContact(ind-1)->setGlit(*tmpGlit);//on defini la liste de lien cree comme celle du contact d'indice ind
            }
            delete tmpGlit;
        }
    }
    db.close();//fermeture de la bdd
}
