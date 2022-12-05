#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
using namespace std;

bool testContact(){
//Test du fonctionnement des contacts
    bool res = true;
    Contact c1 = Contact("Doe", "John","google" ,"Doe.John@gmail.com", {0,6,1,2,3,4,5,6,7,8}, "photo.jpg");//test constructeur avec paramètres
    Contact c2 = Contact(c1);//test constructeur de copie
    res = (c1==c2);//test operateur == doit retourner true
    c2.setNom("Doe2");//test setter nom
    res = res && !(c1==c2);//test operateur == doit retourner false car nom différent
    c2.setTelephone({0,6,1,2,3,4,5,6,6,8});
    c2.setNom("Doe");
    res = res && !(c1==c2);//test operateur == doit retourner false car telephone différent
    Contact c3 = Contact();//test constructeur par defaut
    c3.setDateModification({15,12,2022});//test setter date de modification
    res = res && !(c1.getDateModification()==c3.getDateModification());//test operateur == doit retourner false car date de modification différente
    return res;
}

void testGestionContact(){
//Test du fonctionnement de GestionContact
    Contact c1 = Contact("Doe", "John","google" ,"Doe.John@gmail.com", {0,6,1,2,3,4,5,6,7,8}, "photo.jpg");
    GestionContact gc1;
    gc1.ajouteContact(c1);//test ajouteContact
    Contact c2 = Contact();
    gc1.ajouteContact(c2);
    cout << "Taille :" <<gc1.getLc().size() << endl;//affiche la taille de la liste de contact (doit être 2)
    cout << gc1 << endl;//affiche la liste de contact
    gc1.retireContact(c2);//test retireContact via un contact
    cout << "Taille :" <<gc1.getLc().size() << endl;//affiche la nouvelle taille de la liste de contact (doit etre 1)
    cout << gc1 << endl;//affiche la nouvelle liste de contact
    gc1.retireContact(0);//test retireContact via un indice
    cout << "Taille :" <<gc1.getLc().size() << endl;//affiche la nouvelle taille de la liste de contact
    cout << gc1 << endl;//affiche la nouvelle liste de contact (doit etre vide)
    gc1+=c1;//test operateur +=
    cout << "Taille :" <<gc1.getLc().size() << endl;//affiche la taille de la liste de contact (doit etre 1)
    cout << gc1 << endl;//affiche la liste de contact
    gc1-=c1;//test operateur -=
    cout << "Taille :" <<gc1.getLc().size() << endl;//affiche la taille de la liste de contact (doit etre 0)
    cout << gc1 << endl;//affiche la liste de contact (doit etre vide)
}

void testInteraction(){
    //Test du fonctionnement des interactions
    /*Contact c1 = Contact("Doe", "John","google" ,"Doe.John@gmail.com", {0,6,1,2,3,4,5,6,7,8}, "photo.jpg");
    GestionLienIntertache gli1;
    c1.setDateModification({15,12,2022});//test setter date de modification afin de tester si une modification change bien la date de modification
    cout << "c1 : " << c1 << endl;//affiche le contact c1
    Interaction i("test de contenu");
    Interaction i2("@todo test de contenu2");
    Interaction i3("@todo test de contenu3 @date 15/12/2022");
    c1.ajouteInteraction(i);//test ajouteInteraction
    gli1.creeLien(c1.getInteraction(0));//cree le lien Interaction Tache
    cout << "gli1 : " << gli1 << endl;//affiche la liste de lien
    cout << "c1 : " << c1 << endl;//affiche le contact c1
    gli1.retireLien(c1.getInteraction(0));//retire le lien de la liste de lien
    c1.retireInteraction(i);//retire l'interaction du contact
    cout << "gli1 : " << gli1 << endl;//affiche la nouvelle liste de lien
    cout << "c1 : " << c1 << endl;//affiche le contact c1
    c1.ajouteInteraction(i2);//test ajouteInteraction avec @todo
    gli1.creeLien(c1.getInteraction(0));//cree le lien Interaction Tache
    c1.ajouteInteraction(i3);//test ajouteInteraction avec @todo et @date
    gli1.creeLien(c1.getInteraction(1));//cree le lien Interaction Tache
    cout << "gli1 : " << gli1 << endl;//affiche la liste de lien
    cout << "c1 : " << c1 << endl;//affiche le contact c1
    gli1.retireLien(c1.getInteraction(0));//retire le lien de la liste de lien
    c1.retireInteraction(0);//retire l'interaction du contact via un indice
    cout << "gli1 : " << gli1 << endl;//affiche la liste de lien
    cout << "c1 : " << c1 << endl;//affiche le contact c1*/
}

void appelTest(){
    cout << "testContact : " << testContact() << endl;
    testGestionContact();
    testInteraction();
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GestionContact * listeContact = new GestionContact();
    MainWindow w(nullptr,listeContact);
    w.show();

    //-- todo -- //
    //gerer toutes les exceptions y compris dans les setteurs
    return a.exec();

}
