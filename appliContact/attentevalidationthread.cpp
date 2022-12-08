#include "attentevalidationthread.h"
#include <QDebug>
#include <QRegularExpression>
#include "sdate.h"

/// @brief constructeur pour modification d'un contact
/// @param unsigned i, QLineEdit * n, QLineEdit * pr, QLineEdit * e, QLineEdit * m, QLineEdit * t, QLineEdit * ph, QTextEdit * in
AttenteValidationThread::AttenteValidationThread(unsigned i, QLineEdit * n, QLineEdit * pr, QLineEdit * e, QLineEdit * m, QLineEdit * t, QLineEdit * ph, QTextEdit * in)
{
    this->cont = true;
    this->ID = i;
    this->nom = n;
    this->prenom = pr;
    this->entreprise = e;
    this->mail = m;
    this->tel = t;
    this->photo = ph;
    this->interactions = in;
}

/// @brief constructeur pour creation d'un contact
/// @param QLineEdit * n, QLineEdit * pr, QLineEdit * e, QLineEdit * m, QLineEdit * t, QLineEdit * ph
AttenteValidationThread::AttenteValidationThread(QLineEdit * n, QLineEdit * pr, QLineEdit * e, QLineEdit * m, QLineEdit * t, QLineEdit * ph)
{
    this->cont = true;
    this->nom = n;
    this->prenom = pr;
    this->entreprise = e;
    this->mail = m;
    this->tel = t;
    this->photo = ph;
}

/// @brief destructeur
AttenteValidationThread::~AttenteValidationThread()
{
}
/// @brief corps de thread
void AttenteValidationThread::run()
{
    while(cont){}//tant qu'aucun bouton n'est cliqué le thread continue de tourner
}
/// @brief actions en cas d'annulation
void AttenteValidationThread::annulation()
{
    emit(toAffichagePrincipal());//en cas d'annulation aucune action n'est a effectuer, on revient a l'affichage principal
    this->cont=false;//on stop le thread
}
/// @brief actions en cas de suppression
void AttenteValidationThread::suppression()
{
    emit(toSupprimeContact(this->ID));//on passe l'indice du contact a supprimer au SLOT correspondant dans mainwindow
    this->cont=false;//on stop le thread
}
/// @brief actions en cas de validation de la creation du contact
void AttenteValidationThread::validCreation()
{
    if( validNom(this->nom->text()) &&
        validNom(this->prenom->text()) &&
        validMail(this->mail->text()) &&
        validTel(this->tel->text()) &&
        validPhoto(this->photo->text())){//on verifie la conformité des données

        emit(toCreeContact(this->nom->text(),
                           this->prenom->text(),
                           this->entreprise->text(),
                           this->mail->text(),
                           this->tel->text(),
                           this->photo->text()));//si les données sont conforment on les passe au SLOT de creation du contact dans mainwindow
        this->cont=false;//on stop le thread
    }
    else{
        qDebug() << "erreur de saisie, réessayez";//si les données ne sont pas conforme, on affiche une erreur
        //le thread continue de tourner
    }
}
/// @brief actions en cas de validations des modifications
void AttenteValidationThread::validModification()//meme principe que pour la creation mais on passe l'indice du contact a modifier
{
    if( validNom(this->nom->text()) &&
        validNom(this->prenom->text()) &&
        validMail(this->mail->text()) &&
        validTel(this->tel->text()) &&
        validPhoto(this->photo->text()) &&
        validInteraction(this->interactions->toPlainText())){

        emit(toModifierContact(this->ID,
                               this->nom->text(),
                               this->prenom->text(),
                               this->entreprise->text(),
                               this->mail->text(),
                               this->tel->text(),
                               this->photo->text(),
                               this->interactions->toPlainText()));
        this->cont=false;
    }
    else{
        qDebug() << "erreur de saisie, réessayez";
    }
}
/// @brief verifie la conformité d'un nom/prenom
/// @param Qstring s
/// @return bool
bool AttenteValidationThread::validNom(QString s)
{
    //on verifie que le champ n'est pas vide et que le nom est bien un nom
    // ex : "alexandre" ou "jean-pierre" sont valide
    // "alex21" "jean*pierre" ne le sont pas
    if(s.isEmpty() || !s.contains(QRegularExpression("^[a-zA-z]*[-]?[a-zA-Z]*$"))){
        qDebug() << "les noms ne doivent pas être vide et doivent être de la forme : \"prenom\" ou \"prenom-compose";
        return false;
    }
    return true;
}
/// @brief verifie la conformité du mail
/// @param Qstring s
/// @return bool
bool AttenteValidationThread::validMail(QString s)
{
    if(s.isEmpty()){//le champ peut etre vide
        return true;
    }
    // verifie la conformité du mail
    // exemple ok : exemple@exemple.fr  | exem_ple@ex.emple.com
    // exemple !ok : exemple@exemple | exemple.com | exe*mple@ex.fr
    else if(!s.contains(QRegularExpression("^[a-zA-Z]+[a-zA-Z0-9_.-]*[@][a-zA-Z0-9_.-]*[.][a-z]+$"))){
        qDebug() << "le mail doit être de la forme : exemple@domaine.ex";
        return false;
    }
    return true;
}
/// @brief verifie la conformité du numero de tel
/// @param Qstring s
/// @return bool
bool AttenteValidationThread::validTel(QString s)
{
    if(s.isEmpty()){//le numero de telephone peut etre vide
        return true;
    }
    //verifie que le numero est une suite de 10 chiffres commencant par 0
    else if(!s.contains(QRegularExpression("^0[1-9]{9}$"))){
        qDebug() << "le tel doit être une suite de 10 chiffres commençant par 0";
        return false;
    }
    return true;
}
/// @brief verifie la conformité de l'URL/URI de la photo
/// @param Qstring s
/// @return bool
bool AttenteValidationThread::validPhoto(QString s)
{
    if(s.isEmpty()){//l'URL/URI de la photo peut etre vide
        return true;
    }
    //verifie la conformite de l'URL/URI
    // le chemin doit etre valide (dans la forme on ne verifie pas que la photo existe ici)
    // le fichier doit etre un .png .jpg ou .jpeg
    else if(!s.contains(QRegularExpression("^[a-zA-Z0-9\\/\\\\._-]+\\.(jpe?g|png)$"))){
        qDebug() << "l'URL/URI ne doit pas contenir d'espace ou de caractère spéciaux autre que (\"_\", \"-\", \".\", \"/\", \"\\\") et doit pointer vers un fichier de type jpeg, jpg, ou png";
        return false;
    }
    return true;
}
/// @brief verifie la conformité des interactions/taches
/// @param Qstring s
/// @return bool
bool AttenteValidationThread::validInteraction(QString s)
{
    QStringList qsl = s.split("\n");//chaque ligne est une interaction differente, on les places dans une liste
    for(int i=0 ; i<qsl.size() ; i++){//on parcour cette liste
        if(qsl[i].contains(QRegularExpression("^@todo"))){//si la ligne commence par @todo
            if(qsl[i].contains(QRegularExpression("@date"))){// alors on regarde si la ligne contient @date
                //si oui alors on verfifie qu'une date correcte suit l'@date et que rien ne trouve après
                if(qsl[i].contains(QRegularExpression("@date [0-9]{2}\\/[0-9]{2}\\/[0-9]{4}$"))){
                    //si c'est la cas alors on récupère la date du jour
                    time_t t = time(0);//nb sec depuis 1970
                    tm * ltm = localtime(&t);//conversion
                    sdate ajd = {(unsigned int)ltm->tm_mday,(unsigned int)1+ltm->tm_mon,(unsigned int)1900+ltm->tm_year};
                    int debDate = qsl[i].lastIndexOf(QRegularExpression("@date")) + 6;//indice du premier chiffre de la date
                    //on cree la date a partir de la string
                    sdate d = {(unsigned)(qsl[i].at(debDate).digitValue()*10+qsl[i].at(debDate+1).digitValue()),
                               (unsigned)(qsl[i].at(debDate+3).digitValue()*10+qsl[i].at(debDate+4).digitValue()),
                               (unsigned)(qsl[i].at(debDate+6).digitValue()*1000+qsl[i].at(debDate+7).digitValue()*100+qsl[i].at(debDate+8).digitValue()*10+qsl[i].at(debDate+9).digitValue())};
                    if(d < ajd){//on verifie que la date est postérieur a la date du jour
                        qDebug() << "la date doit être postérieur à la date d'aujourd'hui";
                        return false;
                    }
                }
                else{//si il n'y a pas de date valide après l'@date
                    qDebug() << "il faut entrer une date après un @date (jj/mm/aaaa)";
                    return false;
                }
            }
        }
    }

    return true;
}

