#ifndef ATTENTEVALIDATIONTHREAD_H
#define ATTENTEVALIDATIONTHREAD_H
#include <QThread>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>

// cette classe est utilisé lors de la creation ou la modification d'un contact
// elle prends en paramètre les champs de texte de la creation/modification
// elle attends l'appui sur le bouton valider
// puis elle verifi la conformité des données saisient
// et enfin elle passe les données a la fonction de creation/modification
// nous avons utilisé un thread pour palier au probleme que nous ne pouvons pas
// passer de paramètre au signal clicked() d'un bouton
// ainsi nous n'avons pas besoin de mettre les QLineEdit en attributs global

class AttenteValidationThread : public QThread
{
    Q_OBJECT
private:
    bool cont;//booleen disant si ou non le thread doit continuer de tourner
    unsigned ID;//position du contact la liste (ne sert que pour la modification d'un contact)
    QLineEdit * nom;
    QLineEdit *prenom;
    QLineEdit * entreprise;
    QLineEdit * mail;
    QLineEdit * tel;
    QLineEdit * photo;
    QTextEdit * interactions;
public:
    AttenteValidationThread(unsigned, QLineEdit *, QLineEdit *, QLineEdit *, QLineEdit *, QLineEdit *, QLineEdit *, QTextEdit *);//constructeur pour modification
    AttenteValidationThread(QLineEdit *, QLineEdit *, QLineEdit *, QLineEdit *, QLineEdit *, QLineEdit *);//constructeur pour creation
    ~AttenteValidationThread();
    void run() override;//corps du thread
    //fonctions de verification de la conformite des données
    bool validNom(QString);
    bool validMail(QString);
    bool validTel(QString);
    bool validPhoto(QString);
    bool validInteraction(QString);
signals:
    void toCreeContact(QString, QString, QString, QString, QString, QString);//passe les données a la fonction de creation de contact
    void toModifierContact(unsigned, QString, QString, QString, QString, QString, QString, QString);//passe les données a la fonction de modification de contact
    void toSupprimeContact(unsigned);//en cas de click sur le bouton supprimer passe l'ID du contact a supprimer
    void toAffichagePrincipal();//indique de revenir a l'affichage principal (en cas d'annulation de la creation/modification)
public slots:
    //actions a effectuer en cas de click sur le bouton correspondant (details dans le .cpp)
    void validCreation();
    void validModification();
    void suppression();
    void annulation();
};

#endif // ATTENTEVALIDATIONTHREAD_H
