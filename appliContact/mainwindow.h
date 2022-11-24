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
signals:
public slots:
    void affichagePrincipal();
    void affichageCreeContact();
    void creeContact(std::string n, std::string pr, std::string e, std::string m, std::string t, std::string ph);
};
#endif // MAINWINDOW_H
