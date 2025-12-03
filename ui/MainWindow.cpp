//
// Created by Caesar on 2025/12/3.
//

// You may need to build the project (run Qt uic code generator) to get
// "ui_MainWindow.h" resolved

#include "MainWindow.h"

#include <iostream>

#include <QTimer>
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    init();
    connectSlot();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::init() {
    m_timer = new QTimer(this);
    // m_timer->start(100);
}

void MainWindow::connectSlot() {
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::print);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::changeColor);
}

void MainWindow::print() const { changeColor(); }

void MainWindow::changeColor() const {
    static int r = 0;
    static int g = 0;
    static int b = 0;

    r = std::rand() % 255;
    g = std::rand() % 255;
    b = std::rand() % 255;

    const auto color = QColor(r, g, b);
    ui->pushButton->setStyleSheet(
            QString("background-color: %1;").arg(color.name()));

    const auto v = std::rand() % 100;
    ui->lcdNumber->display(v);
    ui->verticalSlider->setValue(v);
}
