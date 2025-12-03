//
// Created by Caesar on 2025/12/3.
//

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow final : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    void init();
    void connectSlot();

private slots:
    void print() const;
    void changeColor() const;

private:
    Ui::MainWindow *ui;
    QTimer *m_timer;
};

#endif // MAIN_WINDOW_H
