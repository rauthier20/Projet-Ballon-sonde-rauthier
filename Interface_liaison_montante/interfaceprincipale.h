#ifndef INTERFACEPRINCIPALE_H
#define INTERFACEPRINCIPALE_H

#include <QMainWindow>
#include <QSerialPort>
#include <QLabel>
#include <QByteArray>
#include <QTextStream>
#include <QFileDialog>
#include <QTimer>

#include "dialogconfigurerliaison.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class InterfacePrincipale;
}
QT_END_NAMESPACE

class InterfacePrincipale : public QMainWindow
{
    Q_OBJECT

public:
    InterfacePrincipale(QWidget *parent = nullptr);
    ~InterfacePrincipale();


private slots:
    void on_actionConfigurer_triggered();

    void onQSerialPort_ReadyRead();

    void on_actionEffacerTout_triggered();

    void on_pushButtonM8_clicked();

    void on_pushButtonPing_clicked();

private:
    Ui::InterfacePrincipale *ui;
    QSerialPort lePort;
    DialogConfigurerLiaison configLiaison;

    QLabel labelEtatPort;
    QByteArray trameRecu;

};
#endif // INTERFACEPRINCIPALE_H
