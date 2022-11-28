#ifndef ATTENTEVALIDATIONTHREAD_H
#define ATTENTEVALIDATIONTHREAD_H
#include <QThread>
#include <QPushButton>
#include <QLineEdit>

class AttenteValidationThread : public QThread
{
    Q_OBJECT
private:
    bool cont;
    QLineEdit * nom;
    QLineEdit * prenom;
    QLineEdit * entreprise;
    QLineEdit * mail;
    QLineEdit * tel;
    QLineEdit * photo;
public:
    AttenteValidationThread(QLineEdit*, QLineEdit*, QLineEdit*, QLineEdit*, QLineEdit*, QLineEdit*);
    ~AttenteValidationThread();
    void run() override;
    bool validNom(QString);
    bool validMail(QString);
    bool validTel(QString);
    bool validPhoto(QString);
signals:
    void toCreeContact(QString, QString, QString, QString, QString, QString);
public slots:
    void validation();
};

#endif // ATTENTEVALIDATIONTHREAD_H
