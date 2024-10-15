#include "GUI.h"
#include <string>
#include <cstdio>
#include "QLabel"

void LocatariGui::initGUI() {
    //main window
    lyMain = new QHBoxLayout;
    this->setLayout(lyMain);

    // Partea stanga--------------------------------------------------------------------------------------------------------
    QWidget* stanga = new QWidget;
    QVBoxLayout* lyStanga = new QVBoxLayout;
    stanga->setLayout(lyStanga);

    // Formular pentru adaugare/modificare/stergere
    QHBoxLayout* lyAlaturat = new QHBoxLayout;
    QWidget* form = new QWidget;
    QFormLayout* lyForm = new QFormLayout;
    form->setLayout(lyForm);
    editApartament = new QLineEdit;
    editNume = new QLineEdit;
    editSuprafata = new QLineEdit;
    editTip = new QLineEdit;

    //--------ADAUGARE-------------------
    auto *label1=new QLabel("Adaugare: ");
    lyForm->addRow(label1); //trebuie sa adaugam totul la format
    lyForm->addRow(lbApartament, editApartament);
    lyForm->addRow(lbNume, editNume);
    lyForm->addRow(lbSuprafata, editSuprafata);

    comboTip->addItem(QString::number(1));
    comboTip->addItem(QString::number(2));
    comboTip->addItem(QString::number(3));
    lyForm->addRow(lbTip, comboTip);

    butonAdauga = new QPushButton("Adauga locatar!");
    lyForm->addWidget(butonAdauga);

    //-------STERGERE(DUPA NR APARTAMENT)---------------------
    auto *label2=new QLabel("Stergere dupa nr apartamentului: ");
    lyForm->addRow(label2);
    auto *label3=new QLabel("Nr apartamentului: ");
    stergereObiect= new QLineEdit;
    lyForm->addRow(label3,stergereObiect);
    butonSterge = new QPushButton("Sterge locatar!");
    lyForm->addWidget(butonSterge);

   //-------MODIFICARE NUME------------------------------------
    auto *label4= new QLabel("Modifica numele unui locatar: ");
    lyForm->addRow(label4);
    auto *labelNumeVechi=new QLabel("Numele vechi al locatarului: ");
    numeVechi = new QLineEdit;
    lyForm->addRow(labelNumeVechi,numeVechi);

    auto *labelApartament=new QLabel("Numarul apartamentului ");
    nrApartamentModif= new QLineEdit;
    lyForm->addRow(labelApartament,nrApartamentModif);

    NumeNou= new QLineEdit;
    auto *labelNumeNou= new QLabel("Numele nou al locatarului: ");
    lyForm->addRow(labelNumeNou,NumeNou);
    butonModifica = new QPushButton("Modifica locatar!");
    lyForm->addWidget(butonModifica);

    lyStanga->addWidget(form);

    //------FILTRARE----------------------------------------------
    QFormLayout *lyFiltrari=new QFormLayout;
    filtrari->setLayout(lyFiltrari);

    QLabel* tip = new QLabel("Dati tipul: ");
    filtrareDupaTip = new QLineEdit;
    butonFiltrareTip = new QPushButton("Filtare dupa tip!");

    lyFiltrari->addRow(tip, filtrareDupaTip);
    lyFiltrari->addWidget(butonFiltrareTip);

    QLabel* suprafata = new QLabel("Introduceti o suprafata minima: ");
    filtrareDupaSuprafataMin = new QLineEdit;
    butonFiltrareSuprafata= new QPushButton("Filtare dupa suprafata!");

    lyFiltrari->addRow(suprafata, filtrareDupaSuprafataMin);
    lyFiltrari->addWidget(butonFiltrareSuprafata);

    lyStanga->addWidget(filtrari);

    //------SORTARE-----------------------------------------------
    QVBoxLayout* sortari=new QVBoxLayout;
    grupareSortari->setLayout(sortari);
    sortari->addWidget(sortareDupaNume);
    sortari->addWidget(sortareDupaSuprafata);
    sortari->addWidget(sortareDupaTipSuprafata);
    butonSort1 = new QPushButton("Sorteaza Apartamentele");
    sortari->addWidget(butonSort1);
    lyForm->addWidget(grupareSortari);


    //------UNDO---------------------------------------------------
    undo=new QPushButton("Undo");
    lyAlaturat->addWidget(undo);

    //------ADD FILLING---------------------------------------------
    defaultadd=new QPushButton("Adauga default");
    lyAlaturat->addWidget(defaultadd);

    //NU STERGE CE E MAI JOS PLS

    lyStanga->addLayout(lyAlaturat);



    //-- Partea dreapta-----------------------------------------------------------------------------------------------------------------
    dreapta = new QWidget;
    lyDreapta = new QVBoxLayout;
    dreapta->setLayout(lyDreapta);

//    tabelLocatari = new QTableWidget{5, 4};
//    QStringList tblHeader;
//    tblHeader << "Apartament" << "Nume proprietar" << "Suprafata" << "Nr Camere";
//    tabelLocatari->setHorizontalHeaderLabels(tblHeader);
//    tabelLocatari->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    lista = new QListWidget;
//    vector<Locatar> toti = ctr.getAllServi();
//    for (auto& c : toti) {
//        lista->addItem(QString::fromStdString("Ap: " + std::to_string(c.get_ap()) + " Nume: " + c.get_nume() + " Sup: ") + QString::number(c.get_sup()) + QString::fromStdString(" Tip: " + std::to_string(c.get_tip())));
//    }
//    lyDreapta->addWidget(lista);
    tabelView = new QTableView();
    model = new MyTableModel(ctr.getAllServi());
    tabelView->setModel(model);
    lyDreapta->addWidget(tabelView);
    //-----------Lab11---------------------------------

//    tabel_lista_lab11=new QTableWidget(5, 4);
//    QStringList tbllab11;
//    tbllab11 << "Apartament" << "Nume proprietar" << "Suprafata" << "Nr Camere";
//    tabel_lista_lab11->setHorizontalHeaderLabels(tbllab11);
//    tabel_lista_lab11->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    lyDreapta->addWidget(tabel_lista_lab11);

    //----------COS-------------------------------------------------


    openCosWindowButton = new QPushButton("Deschide Cosul de Notificari - Lab 11");
    lyDreapta->addWidget(openCosWindowButton);

    coscos=new QWidget;
    exterior_cos=new QHBoxLayout;
    coscos->setLayout(exterior_cos);
    stergere= new QPushButton("Golire cos");
    exterior_cos->addWidget(stergere);
    random=new QPushButton("Adauga random");
    exterior_cos->addWidget(random);
    lyDreapta->addWidget(coscos);

    id=new QLineEdit;
    adaugare=new QPushButton("Adaugare nr apartament");
    adaugareid=new QWidget;
    ada= new QFormLayout;
    adaugareid->setLayout(ada);
    ada->addRow(id,adaugare);
    lyDreapta->addWidget(adaugareid);

    cos1=new QPushButton("Cos CRUD");
    lyDreapta->addWidget(cos1);

    cos2=new QPushButton("Cos READ Only");
    lyDreapta->addWidget(cos2);
    //-----------MAP---------------------------------------------
    map<int, int> typeCounts = ctr.make_map();

    for (const auto& pair : typeCounts) {
        int type = pair.first;
        QPushButton* button = new QPushButton(QString("Type %1").arg(type));
        lyDreapta->addWidget(button);
        butoane.push_back(button);

        QObject::connect(button, &QPushButton::clicked, [this, type]() {
            map<int, int> typeCounts = ctr.make_map();
            int count = typeCounts[type];
            QString message = QString("There are %1 objects of type %2.").arg(count).arg(type);
            QMessageBox::information(this, "Type Count", message);
        });
    }

    //------END-----------------------------------------------------
    butonAfisareIntegrala= new QPushButton("Afisare Lista");
    lyDreapta->addWidget(butonAfisareIntegrala);
    lyMain->addWidget(stanga);
    lyMain->addWidget(dreapta);
}


void LocatariGui::actualizareLocatari(vector<Locatar> locatari) {
//    tabelLocatari->clearContents();
//    tabelLocatari->setRowCount(locatari.size());
//
//    int index = 0;
//    for (auto& l : locatari) {
//        c1 = new QTableWidgetItem(QString::number(l.get_ap()));
//        c2 = new QTableWidgetItem(QString::fromStdString(l.get_nume()));
//        c3 = new QTableWidgetItem(QString::number(l.get_sup()));
//        c4 = new QTableWidgetItem(QString::number(l.get_tip()));
//        tabelLocatari->setItem(index, 0, c1);
//        tabelLocatari->setItem(index, 1, c2);
//        tabelLocatari->setItem(index, 2, c3);
//        tabelLocatari->setItem(index, 3, c4);
//        index++;
//    }
//
//    lista->clear();
//    for (auto& c : locatari) {
//        lista->addItem(QString::fromStdString("Ap: " + std::to_string(c.get_ap()) + " Nume: " + c.get_nume() + " Sup: " + std::to_string(c.get_sup()) + " Tip: " + std::to_string(c.get_tip())));
//    }
    model->seteazaLocatari(locatari);

}


void LocatariGui::connectSignalSlots() {
    QObject::connect(butonAdauga, &QPushButton::clicked, this, &LocatariGui::adaugaGUI);
    QObject::connect(butonSterge, &QPushButton::clicked, this, &::LocatariGui::stergereGUI);
    QObject::connect(butonModifica, &QPushButton::clicked, this, &LocatariGui::modificaGUI);
    QObject::connect(undo,&QPushButton::clicked,this,&LocatariGui::undoGUI);
    QObject::connect(defaultadd, &QPushButton::clicked,this,&LocatariGui::AdaugaDefault);
    QObject::connect(openCosWindowButton, &QPushButton::clicked, this, &LocatariGui::openCosWindow);

    QObject::connect(butonFiltrareTip, &QPushButton::clicked, [&]() {
        int tip = filtrareDupaTip->text().toInt();
        filtrareDupaTip->clear();
        actualizareLocatari(ctr.filtrareTip(tip));
    });

    QObject::connect(butonFiltrareSuprafata, &QPushButton::clicked, [&]() {
        double supi = filtrareDupaSuprafataMin->text().toDouble();
        filtrareDupaSuprafataMin->cleroiar();
        actualizareLocatari(ctr.filtrareSuprafata(supi));
    });


    QObject::connect(butonSort1, &QPushButton::clicked, [&]() {
        if (sortareDupaNume->isChecked()) {
            actualizareLocatari(ctr.sortByName());
        }
        else {
            if (sortareDupaSuprafata->isChecked()) {
                actualizareLocatari(ctr.sortBySuprafata());
            }
            else {
                if (sortareDupaTipSuprafata->isChecked()) {
                    actualizareLocatari(ctr.sortByTip());
                }
            }
        }
    });



    QObject::connect(tabelLocatari, &QTableWidget::clicked, [&]() {
        QList l = tabelLocatari->selectedItems();
        QString ap, nume, sup;
        int tip=0;
        int i = 0;
        for (auto& a : l) {
            if (i == 0) { ap = a->text(); }
            if (i == 1) { nume = a->text(); }
            if (i == 2) { sup = a->text(); }
            if (i == 3) { tip = a->text().toInt(); }
            i++;
        }
        editApartament->setText(ap);
        editNume->setText(nume);
        editSuprafata->setText(sup);
        comboTip->setCurrentIndex(tip-1);
    });

    QObject::connect(butonAfisareIntegrala,&QPushButton::clicked,[&]() {
        actualizareLocatari(ctr.getAllServi());
        actualizareTabel(ctr.getAllServi());
    });

    QObject::connect(cos1,&QPushButton::clicked,[this]() {
        auto fer = new CosCRUDGUI{ ctr,servi_notif };
        fer->show();
    });

    QObject::connect(cos2, &QPushButton::clicked, [this]() {
        auto fer = new CosReadOnlyGUI{ servi_notif };
        fer->show();
    });

    QObject::connect(random, &QPushButton::clicked,[this](){
        servi_notif.generate_random((ctr.getAllServi()));
    });

    QObject::connect(stergere,&QPushButton::clicked,[this](){
        servi_notif.golire_servi();
    });

    QObject::connect(adaugare,&QPushButton::clicked,[this](){
        int ap=id->text().toInt();
        id->clear();
        try{
            Locatar l=ctr.findObjectbyNrServi(ap);
            servi_notif.add_notif(l);
        }
        catch (RepoException& re) {
            QMessageBox::warning(this, "Warning", "Imposibil de adaugat");
        }
    });
}

void LocatariGui::adaugaGUI() {
    try {
        int ap = editApartament->text().toInt();
        string nume = editNume->text().toStdString();
        double sup = editSuprafata->text().toDouble();
        int tip = comboTip->currentText().toInt();

        editApartament->clear();
        editNume->clear();
        editSuprafata->clear();
        comboTip->clearEditText();
        editTip->clear();
        bool maie = false;
        vector<Locatar>inainte = ctr.getAllServi();
        for (auto& a : inainte) {
            if (a.get_tip() == tip) {
                maie = true;
            }
        }

        ctr.addServi(ap, nume, sup, tip);
        actualizareLocatari(ctr.getAllServi());
        //actualizareTabel(ctr.getAllServi());
        QMessageBox::information(this, "Info", QString::fromStdString("Locatar adaugat cu succes!"));

        vector<int>tipuri;
        bool maaa = false;
        for (auto& a : inainte) {
            if (a.get_tip() == tip) {
                maaa = true;
            }
        }
        if (maaa == false) {
            tipuri.push_back(tip);
            auto s = std::to_string(tip);
            string ss = s;
            QString d = QString::fromStdString(ss);
            QPushButton* but = new QPushButton(d); butoane.push_back(but);
            QObject::connect(but, &QPushButton::clicked, [=]() {
                int tipp = but->text().toInt();
                vector<Locatar>inainte = ctr.getAllServi(); int cate = 0;
                for (auto& c : inainte) { if (c.get_tip() == tipp) { cate++; } }
                string am = "Avem " + std::to_string(cate) + " apartamente de tipul " + std::to_string(tipp);
                QMessageBox::information(this, "Info", QString::fromStdString(am));
            });
            lyDreapta->addWidget(but);
        }

    }
    catch (RepoException& re) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));

    }
    catch (ValidateException& ve) {
        string erori = "";
        for (auto& mesaje : ve.getErrorMessages()) {
            erori = erori + mesaje + '\n';
        }
        QMessageBox::warning(this, "Warning", QString::fromStdString(erori));
    }
}

void LocatariGui::stergereGUI() {
    try {
        int ap = stergereObiect->text().toInt();
        bool ceva=ctr.deleteServi(ap);
        if(ceva){
            actualizareLocatari(ctr.getAllServi());
           // actualizareTabel(ctr.getAllServi());
            QMessageBox::information(this, "Info", QString::fromStdString("Locatar sters cu succes!"));
        }
        else
            QMessageBox::warning(this, "Warning", QString::fromStdString("Stergerea nu a putut fi efectuata"));
    }
    catch (RepoException& re) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));

    }
    catch (ValidateException& ve) {
        string erori = "";
        for (auto& mesaje : ve.getErrorMessages()) {
            erori = erori + mesaje + '\n';
        }
        QMessageBox::warning(this, "Warning", QString::fromStdString(erori));
    }
    catch (std::exception e){
        QMessageBox::warning(this, "Warning", QString::fromStdString("Nu exista Locatarul cautat!"));
    }

}

void LocatariGui::modificaGUI() {
    try {
        string numeleVechi= numeVechi->text().toStdString();
        string numeleNou=NumeNou->text().toStdString(); //Un nume nou s-a scris in Vesniciee
        int ApartamentModificabil=nrApartamentModif->text().toInt();
        ctr.modifyServi(numeleVechi,ApartamentModificabil,numeleNou);
        actualizareLocatari(ctr.getAllServi());
        actualizareTabel(ctr.getAllServi());
        QMessageBox::information(this, "Info", QString::fromStdString("Locatar modificat cu succes!"));

    }
    catch (RepoException& re) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));

    }
    catch (ValidateException& ve) {
        string erori = "";
        for (auto& mesaje : ve.getErrorMessages()) {
            erori = erori + mesaje + '\n';
        }
        QMessageBox::warning(this, "Warning", QString::fromStdString(erori));
    }
}

void LocatariGui::undoGUI() {
    try{
        ctr.fa_undo();
        actualizareLocatari(ctr.getAllServi());
        actualizareTabel(ctr.getAllServi());
        QMessageBox::information(this,"Info",QString::fromStdString("Undo efectuat cu succes!"));
    } catch (RepoException &re){
        QMessageBox::warning(this,"Atentie",QString::fromStdString("Nu se poate face undo!"));
    }
}

void LocatariGui::AdaugaDefault() {
    ctr.addServi(12,"Oti", 469.5, 2);
    ctr.addServi(17,"Ema", 600.5, 2);
    ctr.addServi(13,"Ema", 1600.5, 3);
    ctr.addServi(1,"Alexandra", 134.5, 1);
    ctr.addServi(7,"Andrei", 60.5, 1);
    actualizareLocatari(ctr.getAllServi());
    //actualizareTabel(ctr.getAllServi());
}


void LocatariGui::openCosWindow() {

    if(!cosWindow){
        cosWindow= new CosWindow(*this);
        cosWindow->setAttribute(Qt::WA_DeleteOnClose);
    }
    cosWindow->show();
}

void LocatariGui::actualizareTabel(vector<Locatar> locatari) {
    tabel_lista_lab11->clearContents();
    tabel_lista_lab11->setRowCount(locatari.size());
    int index = 0;
    for (auto& l : locatari) {
        tabel_lista_lab11->setItem(index, 0, new QTableWidgetItem(QString::number(l.get_ap())));
        tabel_lista_lab11->setItem(index, 1, new QTableWidgetItem(QString::fromStdString(l.get_nume())));
        tabel_lista_lab11->setItem(index, 2, new QTableWidgetItem(QString::number(l.get_sup())));
        tabel_lista_lab11->setItem(index, 3, new QTableWidgetItem(QString::number(l.get_tip())));
        index++;
    }
}

void CosWindow::clearNotifications() {
    try {
        locatariGui.servi_notif.golire_servi();
        actualizareNotificari(locatariGui.servi_notif.get_everything_servi());
    } catch (RepoException& re) {
        QMessageBox::warning(this, "Warning", "Nu avem ce sterge!");
    }
}

void CosWindow::addNotificationById() {
    int ap = apartmentIdInput->text().toInt();
    apartmentIdInput->clear();
    try {
        Locatar loc = locatariGui.ctr.findObjectbyNrServi(ap);
        locatariGui.servi_notif.add_notif(loc);
        actualizareNotificari(locatariGui.servi_notif.get_everything_servi());
    } catch (RepoException& re) {
        QMessageBox::warning(this, "Warning", "Imposibil de adaugat");
    }
}

void CosWindow::addRandomNotifications() {
    /*
     * adauga notificari random
     */
    locatariGui.servi_notif.generate_random((locatariGui.ctr.getAllServi()));
    actualizareNotificari(locatariGui.servi_notif.get_everything_servi());
}

void CosWindow::setupUI() {
    /*
     * intefata ui
     */
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout); // Set the layout for the CosWindow widget

    tabelNotificari = new QTableWidget(5, 4);
    QStringList tblHeader;
    tblHeader << "Apartament" << "Nume proprietar" << "Suprafata" << "Nr Camere";
    tabelNotificari->setHorizontalHeaderLabels(tblHeader);
    tabelNotificari->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    layout->addWidget(tabelNotificari);

    QWidget* form2 = new QWidget;
    QFormLayout* lyForm2 = new QFormLayout;
    form2->setLayout(lyForm2);
    deleteAll = new QPushButton("Sterge tot!");
    ad = new QLineEdit();
    addById = new QPushButton("Adauga dupa apartament!");
    ra = new QLineEdit();
    addRandom = new QPushButton("Adauga random!");
    ex = new QLineEdit();
    exportButton = new QPushButton("Export in fisier html!");

    lyForm2->addWidget(deleteAll);
    lyForm2->addRow(ad, addById);
    lyForm2->addRow(ra, addRandom);
    lyForm2->addRow(ex, exportButton);

    layout->addWidget(form2);

    closeButton = new QPushButton("Inchide");
    layout->addWidget(closeButton);

}



void CosWindow::connectSignalSlots() {
    /*
     * conecteaza butoanele din cos cu functiile
     */
    QObject::connect(closeButton, &QPushButton::clicked, this, &CosWindow::close);
    QObject::connect(deleteAll, &QPushButton::clicked, this, &CosWindow::clearNotifications);
    QObject::connect(addById, &QPushButton::clicked, [&]() {
        int ap = ad->text().toInt();ad->clear();
        try {
            Locatar loc=locatariGui.ctr.findObjectbyNrServi(ap);
            locatariGui.servi_notif.add_notif(loc);
            actualizareNotificari(locatariGui.servi_notif.get_everything_servi());
        }
        catch (RepoException& re) {
            QMessageBox::warning(this, "Warning", QString::fromStdString("Imposibil de adaugat"));
        }
    });
    QObject::connect(addRandom, &QPushButton::clicked, this, &CosWindow::addRandomNotifications);
    QObject::connect(exportButton, &QPushButton::clicked, [&]() {
        string nume = ex->text().toStdString(); ex->clear();
        if (nume != "") {
            locatariGui.servi_notif.export_servi(nume);
            QMessageBox::information(this, "Info", QString::fromStdString("Export realizat cu succes!"));
        }
        else {
            QMessageBox::warning(this, "Warning", QString::fromStdString("Nume vid, nu se poate face exportul!"));
        }
    });
}


void CosWindow::actualizareNotificari(const vector<Locatar>& locatari) {
    /*
     * Afiseaza tabelul de notificari
     */
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
