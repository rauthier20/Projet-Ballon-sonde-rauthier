#ifndef DIALOGCONFIGURERLIAISON_H
#define DIALOGCONFIGURERLIAISON_H

#include <QDialog>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QDebug>
#include <QPushButton>

namespace Ui {
class DialogConfigurerLiaison;
}

class DialogConfigurerLiaison : public QDialog
{
    Q_OBJECT

public:
    explicit DialogConfigurerLiaison(QSerialPort &_lePort,QWidget *parent = nullptr);
    ~DialogConfigurerLiaison();

private slots:
    void on_comboBoxPort_currentIndexChanged(int index);



    void on_spinBoxBitData_valueChanged(int arg1);

    void on_checkBoxBitsStop_toggled(bool checked);

    void on_radioButtonPaire_toggled(bool checked);

    void on_radioButtonImpaire_toggled(bool checked);

    void on_radioButtonPasParite_toggled(bool checked);



    void on_comboBoxVitesse_currentTextChanged(const QString &arg1);

    void on_comboBoxFlux_currentIndexChanged(int index);

private:
    Ui::DialogConfigurerLiaison *ui;
    QSerialPort &lePort;


};

#endif // DIALOGCONFIGURERLIAISON_H
