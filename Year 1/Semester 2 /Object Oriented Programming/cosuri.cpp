#include "cosuri.h"

void CosCRUDGUI::initCosCRUDGUI()
{
    lyMain = new QVBoxLayout;
    setLayout(lyMain);

    QStringList antet;
    antet << "Apartamentul: " << "Nume proprietar: ";
    antet << "Suprafata apartament: " << "Tip comfort: ";

    tabelNotificari = new QTableWidget{ 5,4 };
    tabelNotificari->setHorizontalHeaderLabels(antet);

    tabelNotificari->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    lyMain->addWidget(tabelNotificari);

    ad = new QLineEdit();
    deleteall = new QPushButton("Sterge tot!");
    addbyitem = new QPushButton("Adauga!");
    ra = new QLineEdit();
    addrandom = new QPushButton("Adauga random!");


    lyMain->addWidget(deleteall);
    lyMain->addWidget(ad);
    lyMain->addWidget(addbyitem);
    lyMain->addWidget(addrandom);
}

void CosCRUDGUI::connectSignalSlots()
{
    ctr.addObserver(this);
    QObject::connect(deleteall, &QPushButton::clicked, [&]() {
        try {
            ctr.golire_servi();
            actualizareNotificari(ctr.get_everything_servi());
        }
        catch (RepoException& re) {
            QMessageBox::warning(this, "Warning", QString::fromStdString("nu se poate face golirea"));
        }
    });

    QObject::connect(addrandom, &QPushButton::clicked, [&]() {
       ctr.generate_random(ctr_mare.getAllServi());
       actualizareNotificari(ctr.get_everything_servi());
    });

    QObject::connect(addbyitem, &QPushButton::clicked, [&]() {
        int ap = ad->text().toInt(); ad->clear();
        try {
           Locatar loc=ctr_mare.findObjectbyNrServi(ap);
           ctr.add_notif(loc);
           actualizareNotificari(ctr.get_everything_servi());
        }
        catch (RepoException& re) {
            QMessageBox::warning(this, "Warning", QString::fromStdString("Nu se poate adauga dupa Id"));
        }
    });
}

void CosCRUDGUI::actualizareNotificari(vector<Locatar> locatari)
{
    tabelNotificari->clearContents();
    tabelNotificari->setRowCount(locatari.size());

    int index = 0;
    for (auto& l : locatari) {
        tabelNotificari->setItem(index, 0, new QTableWidgetItem(QString::number(l.get_ap())));
        tabelNotificari->setItem(index, 1, new QTableWidgetItem(QString::fromStdString(l.get_nume())));
        tabelNotificari->setItem(index, 2, new QTableWidgetItem(QString::number(l.get_sup())));
        tabelNotificari->setItem(index, 3, new QTableWidgetItem(QString::number(l.get_tip())));
        index++;
    }
}