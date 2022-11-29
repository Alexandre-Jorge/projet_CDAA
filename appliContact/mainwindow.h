#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include "gestioncontact.h"
#include "gestionlienintertache.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    GestionContact * listeContact;
    GestionLienIntertache * listeLienInterTache;

public:
    MainWindow(QWidget *parent = nullptr, GestionContact * gc = nullptr, GestionLienIntertache * glit = nullptr);
    ~MainWindow();
    GestionContact * getListeContact();
    GestionLienIntertache * getListeLienInterTache();
    void setListeContact(GestionContact*);
    void setListeLienInterTache(GestionLienIntertache*);

signals:
    void toAffichagePrincipal();
public slots:
    void affichagePrincipal();
    void affichageCreeContact();
<<<<<<< HEAD
    void affichageContact(QListWidgetItem*);
=======
>>>>>>> d8656cc733c777f4b3202f8d9e8dc61c81894664
    void creeContact(QString n, QString pr, QString e, QString m, QString t, QString ph);
};
#endif // MAINWINDOW_H
