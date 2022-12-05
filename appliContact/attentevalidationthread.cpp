#include "attentevalidationthread.h"
#include <QDebug>
#include <QRegularExpression>
#include "sdate.h"

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


AttenteValidationThread::~AttenteValidationThread()
{
}

void AttenteValidationThread::run()
{
    while(cont){}
}

void AttenteValidationThread::annulation()
{
    emit(toAffichagePrincipal());
    this->cont=false;
}

void AttenteValidationThread::suppression()
{
    emit(toSupprimeContact(this->ID));
    this->cont=false;
}
void AttenteValidationThread::validCreation()
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

void AttenteValidationThread::validModification()
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

bool AttenteValidationThread::validNom(QString s)
{
    if(s.isEmpty() || !s.contains(QRegularExpression("^[a-zA-z]*[-]?[a-zA-Z]*$"))){
        qDebug() << "les noms ne doivent pas être vide et doivent être de la forme : \"prenom\" ou \"prenom-compose";
        return false;
    }
    return true;
}

bool AttenteValidationThread::validMail(QString s)
{
    if(s.isEmpty()){
        return true;
    }
    else if(!s.contains(QRegularExpression("^[a-zA-Z]+[a-zA-Z0-9_.-]*[@][a-zA-Z0-9_.-]*[.][a-z]+$"))){
        qDebug() << "le mail doit être de la forme : exemple@domaine.ex";
        return false;
    }
    return true;
}

bool AttenteValidationThread::validTel(QString s)
{
    if(s.isEmpty()){
        return true;
    }
    else if(!s.contains(QRegularExpression("^0[1-9]{9}$"))){
        qDebug() << "le tel doit être une suite de 10 chiffres commençant par 0";
        return false;
    }
    return true;
}

bool AttenteValidationThread::validPhoto(QString s)
{
    if(s.isEmpty()){
        return true;
    }
    else if(!s.contains(QRegularExpression("^[a-zA-Z0-9\\/\\\\._-]+\\.(jpe?g|png)$"))){
        qDebug() << "l'URL/URI ne doit pas contenir d'espace ou de caractère spéciaux autre que (\"_\", \"-\", \".\", \"/\", \"\\\") et doit pointer vers un fichier de type jpeg, jpg, ou png";
        return false;
    }
    return true;
}

bool AttenteValidationThread::validInteraction(QString s)
{
    QStringList qsl = s.split("\n");
    for(int i=0 ; i<qsl.size() ; i++){
        if(qsl[i].contains(QRegularExpression("^@todo"))){
            if(qsl[i].contains(QRegularExpression("@date"))){
                if(qsl[i].contains(QRegularExpression("@date [0-9]{2}\\/[0-9]{2}\\/[0-9]{4}$"))){

                    time_t t = time(0);//nb sec depuis 1970
                    tm * ltm = localtime(&t);//conversion
                    sdate ajd = {(unsigned int)ltm->tm_mday,(unsigned int)1+ltm->tm_mon,(unsigned int)1900+ltm->tm_year};
                    int debDate = qsl[i].lastIndexOf(QRegularExpression("@date")) + 6;
                    sdate d = {(unsigned)(qsl[i].at(debDate).digitValue()*10+qsl[i].at(debDate+1).digitValue()),
                               (unsigned)(qsl[i].at(debDate+3).digitValue()*10+qsl[i].at(debDate+4).digitValue()),
                               (unsigned)(qsl[i].at(debDate+6).digitValue()*1000+qsl[i].at(debDate+7).digitValue()*100+qsl[i].at(debDate+8).digitValue()*10+qsl[i].at(debDate+9).digitValue())};
                    if(d < ajd){
                        qDebug() << "la date doit être postérieur à la date d'aujourd'hui";
                        return false;
                    }
                }
                else{
                    qDebug() << "il faut entrer une date après un @date (jj/mm/aaaa)";
                    return false;
                }
            }
        }
    }

    return true;
}

