//
// Created by emato on 24.05.2024.
//

#ifndef TEST2_COSURI_H
#define TEST2_COSURI_H
#pragma once
#include "ServiceLocatari.h"
#include "servy_notif.h"
#include "observer.h"
#include <qwidget.h>
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
#include <random>
#include <chrono>
#include <qpainter.h>


class CosCRUDGUI:public QWidget,public Observer {
private:
    Service& ctr_mare;
    ServiNotif &ctr;

    QVBoxLayout* lyMain;

    QLineEdit *ad, * ra;
    QPushButton *addbyitem, * deleteall, * addrandom;

    QTableWidget* tabelNotificari;

public:
    void initCosCRUDGUI();
    void connectSignalSlots();
    void actualizareNotificari(vector<Locatar>locatari);

    CosCRUDGUI(Service& ctr_mare, ServiNotif& _ctr) : ctr_mare{ctr_mare}, ctr{ _ctr } {
        initCosCRUDGUI();
        connectSignalSlots();
        actualizareNotificari(ctr.get_everything_servi());
    }

    void update() override {
        actualizareNotificari(ctr.get_everything_servi());
    }
};


class CosReadOnlyGUI :public QWidget,public Observer {
private:
    ServiNotif& ctr;
public:
    CosReadOnlyGUI(ServiNotif& _ctr) : ctr{ _ctr } {
        ctr.addObserver(this); setFixedHeight(650); qSetFieldWidth(650);
    }

    void update() override {
        repaint();
    }

    void paintEvent(QPaintEvent* ev) override {
        QPainter p{ this };
        std::mt19937 mt{ std::random_device{}() };
        std::uniform_int_distribution<> dist(0, 600);
        std::uniform_int_distribution<int> colorDist(0, 255);
        int x, y,r,g,b;

        for (auto& n : ctr.get_everything_servi()) {
            x = dist(mt);
            y = dist(mt);
            r = dist(mt) % 256;
            g = dist(mt) % 256;
            b = dist(mt) % 256;
            p.setBrush(QColor{ r,g,b });
            p.drawEllipse(x, y, 70, 70);
        }
    }
};
#endif //TEST2_COSURI_H
