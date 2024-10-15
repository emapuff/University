
#pragma once
#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include <QList>
#include <QListWidget>
#include <QComboBox>
#include <qtableview.h>
#include "servy_notif.h"
#include "observer.h"
#include "ServiceLocatari.h"
#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QMessageBox>
#include <QWidget>
#include "cosuri.h"
#include "model.h"
#ifndef TEST2_GUI_H
#define TEST2_GUI_H

using std::vector;
using std::string;


class CosWindow;
class CosCRUDGUI;

class LocatariGui: public QWidget{
    friend class CosWindow;
private:
    Service& ctr;
    ServiNotif& servi_notif;
    QLabel* lbApartament= new QLabel{"Apartamentul: "};
    QLabel* lbNume= new QLabel{"Nume proprietar: "};
    QLabel* lbSuprafata=new QLabel{"Suprafata apartamentului: "};
    QLabel*lbTip=new QLabel{"Nr camere(Tip): "};

    QComboBox* comboTip=new QComboBox;

    QLineEdit* editApartament, *editNume, *editSuprafata,*editTip,*stergereObiect,*numeVechi,*NumeNou,*nrApartamentModif;

    QPushButton* butonAdauga;
    QPushButton* butonSterge;
    QPushButton* butonModifica;
    QPushButton* butonAfisareIntegrala;

    QLineEdit* filtrareDupaTip;
    QLineEdit* filtrareDupaSuprafataMin;
    QPushButton* butonFiltrareTip, * butonFiltrareSuprafata;

    QGroupBox* filtrari=new QGroupBox(tr("Filtrare dupa: "));
    QGroupBox* cos=new QGroupBox(tr("Lista Notificari: "));
    QGroupBox* grupareSortari= new QGroupBox(tr("Sortare dupa: "));
    QRadioButton* sortareDupaNume = new QRadioButton(QString::fromStdString("nume"));
    QRadioButton* sortareDupaSuprafata = new QRadioButton(QString::fromStdString("suprafata"));
    QRadioButton* sortareDupaTipSuprafata = new QRadioButton(QString::fromStdString("tip + suprafata"));
    QPushButton* butonSort1{}, * butonSort2{};
    QPushButton* cos1, *cos2;
    QPushButton* actualizare{};
    QPushButton* adaugare,*stergere,*random;
    QHBoxLayout* exterior_cos;
    QLineEdit *id;
    QWidget* coscos, *adaugareid;
    QFormLayout* ada;
    QPushButton* undo, *openCosWindowButton{};
    QPushButton* defaultadd;


    QTableWidget* tabelFiltrari;
    QTableWidget* tabelLocatari{};
    QTableWidget* tabelNotificari;

    QTableWidgetItem* c1{}, * c2{}, * c3{}, * c4{};

    QListWidget* lista{};
    QListWidget* lista_filtrari{};
    QTableWidget* tabel_lista_lab11{};

    std::vector<QPushButton*> butoane;

    QTableView * tabelView;
    MyTableModel* model;
    QHBoxLayout* lyMain{};

    QWidget* dreapta{};
    QVBoxLayout* lyDreapta{};

    QPushButton *butonReload{};

    CosWindow* cosWindow;

    void connectSignalSlots();
    void actualizareLocatari(vector<Locatar>locatari);
    void actualizareTabel(vector<Locatar>locatari);
    void initGUI();
    //void listafiltrare(vector<Locatar> locatari);

public:
    explicit LocatariGui(Service &_crt, ServiNotif&_servi_notif): ctr{_crt}, servi_notif{_servi_notif}{
        initGUI();
        connectSignalSlots();
        actualizareLocatari(ctr.getAllServi());
    }

    void adaugaGUI();
    void stergereGUI();
    void modificaGUI();
    void undoGUI();
    void AdaugaDefault();
    void openCosWindow();

};

class CosWindow : public QWidget {
public:
    CosWindow(LocatariGui &gui, QWidget *parent = nullptr)
            : QWidget(parent), locatariGui(gui), tabelNotificari(new QTableWidget(5, 4)),
              deleteAll(new QPushButton("Sterge tot!")), addById(new QPushButton("Adauga dupa apartament!")),
              addRandom(new QPushButton("Adauga random!")), exportButton(new QPushButton("Export in fisier html!")),
              closeButton(new QPushButton("Inchide")), ad(new QLineEdit()), ra(new QLineEdit()), ex(new QLineEdit()) {
        setupUI();
        connectSignalSlots();
    }

    void clearNotifications();

    void addNotificationById();

    void addRandomNotifications();

    void exportNotifications();

private:
    LocatariGui &locatariGui;
    QTableWidget *tabelNotificari;
    QPushButton *deleteAll, *addById, *addRandom, *exportButton;
    QLineEdit *apartmentIdInput, *randomInput, *exportInput;
    QLineEdit *ad{}, *ra{}, *ex{};
    QPushButton *closeButton,*deleteall{}, *addbyid{}, *addrandom{}, *exportt{}, *deschidecos1{}, *deschidecos2{};

    void setupUI();

    void connectSignalSlots();

    void actualizareNotificari(const vector<Locatar>& locatari);


};

#endif //TEST2_GUI_H
