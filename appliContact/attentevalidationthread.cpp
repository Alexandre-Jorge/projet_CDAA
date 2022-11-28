#include "attentevalidationthread.h"
#include <QDebug>
#include <QRegularExpression>

AttenteValidationThread::AttenteValidationThread(QLineEdit* n, QLineEdit* pr, QLineEdit* e, QLineEdit* m, QLineEdit* t, QLineEdit* ph)
{
    this->cont = true;
    this->nom = n;
    this->prenom = pr;
    this->entreprise = e;
    this->mail = m;
    this->tel = t;
    this->photo = ph;
}

AttenteValidationThread::~AttenteValidationThread()
{
}

void AttenteValidationThread::run()
{
    while(cont){}
}

void AttenteValidationThread::validation()
{
    if( validNom(this->nom->text()) &&
        validNom(this->prenom->text()) &&
        validMail(this->mail->text()) &&
        validTel(this->tel->text()) &&
        validPhoto(this->photo->text())){

        emit(toCreeContact(this->nom->text(),
                           this->prenom->text(),
                           this->entreprise->text(),
                           this->mail->text(),
                           this->tel->text(),
                           this->photo->text()));
        this->cont=false;
    }
    else{
        qDebug() << "erreur de saisie, réessayez";
    }
}

bool AttenteValidationThread::validNom(QString s)
{
    if(!s.contains(QRegularExpression("^[a-zA-z]*[-]?[a-zA-Z]*$"))){
        qDebug() << "les noms ne doivent pas être vide et doivent être de la forme : \"prenom\" ou \"prenom-compose";
        return false;
    }
    return true;
}

bool AttenteValidationThread::validMail(QString s)
{
    if(!s.contains(QRegularExpression("^[a-zA-Z]+[a-zA-Z0-9_.-]*[@][a-zA-Z0-9_.-]*[.][a-z]+$"))){
        qDebug() << "le mail doit être de la forme : exemple@domaine.ex";
        return false;
    }
    return true;
}

bool AttenteValidationThread::validTel(QString s)
{
    if(!s.contains(QRegularExpression("^0[1-9]{9}$"))){
        qDebug() << "le tel doit être une suite de 10 chiffres commençant par 0";
        return false;
    }
    return true;
}

bool AttenteValidationThread::validPhoto(QString s)
{
    if(!s.contains(QRegularExpression("^[a-zA-Z0-9\\/\\\\._-]+\\.(jpe?g|png)$"))){
        qDebug() << "l'URL/URI ne doit pas contenir d'espace ou de caractère spéciaux autre que (\"_\", \"-\", \".\", \"/\", \"\\\") et doit pointer vers un fichier de type jpeg, jpg, ou png";
        return false;
    }
    return true;
}

