#ifndef ATTENTEVALIDATIONTHREAD_H
#define ATTENTEVALIDATIONTHREAD_H
#include <QThread>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>

class AttenteValidationThread : public QThread
{
    Q_OBJECT
private:
    bool cont;
    unsigned ID;
    QLineEdit * nom;
    QLineEdit *prenom;
    QLineEdit * entreprise;
    QLineEdit * mail;
    QLineEdit * tel;
    QLineEdit * photo;
    QTextEdit * interactions;
public:
    AttenteValidationThread(unsigned, QLineEdit *, QLineEdit *, QLineEdit *, QLineEdit *, QLineEdit *, QLineEdit *, QTextEdit *);
    AttenteValidationThread(QLineEdit *, QLineEdit *, QLineEdit *, QLineEdit *, QLineEdit *, QLineEdit *);
    ~AttenteValidationThread();
    void run() override;
    bool validNom(QString);
    bool validMail(QString);
    bool validTel(QString);
    bool validPhoto(QString);
signals:
    void toCreeContact(QString, QString, QString, QString, QString, QString);
    void toModifierContact(unsigned, QString, QString, QString, QString, QString, QString, QString);
    void toSupprimeContact(unsigned);
    void toAffichagePrincipal();
public slots:
    void validCreation();
    void validModification();
    void suppression();
    void annulation();
};

#endif // ATTENTEVALIDATIONTHREAD_H
