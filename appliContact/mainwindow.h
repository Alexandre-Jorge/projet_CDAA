#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QtSql/QSqlDatabase>
#include "gestioncontact.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    GestionContact * listeContact;
    QSqlDatabase db;

public:
    MainWindow(QWidget *, GestionContact *);
    ~MainWindow();
    GestionContact * getListeContact();
    QSqlDatabase getDb();
    void setListeContact(GestionContact*);
    void setDb(QSqlDatabase);
    void connexionBDD();

signals:
    void toAffichagePrincipal();
public slots:
    void affichagePrincipal();
    void affichageCreeContact();
    void affichageContact(QListWidgetItem*);
    void creeContact(QString, QString, QString, QString, QString, QString);
    void modifierContact(unsigned, QString, QString, QString, QString, QString, QString, QString);
    void supprimerContact(unsigned);
};
#endif // MAINWINDOW_H
