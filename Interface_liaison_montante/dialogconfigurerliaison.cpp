#include "dialogconfigurerliaison.h"
#include "ui_dialogconfigurerliaison.h"

DialogConfigurerLiaison::DialogConfigurerLiaison(QSerialPort &_lePort, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogConfigurerLiaison)
    , lePort(_lePort)
{
    ui->setupUi(this);
    // remplissage combobox des ports disponibles
    for(const auto &info : QSerialPortInfo::availablePorts() )
    {
        qDebug() << info.portName();
        ui->comboBoxPort->addItem(info.portName());
    }
    // remplissage combo vitesse
    int vitesse = 1200;
    for (int i; i<6; i++)
    {
        ui->comboBoxVitesse->addItem(QString::number(vitesse));
        vitesse*=2;
    }
    ui->comboBoxVitesse->addItem(QString::number(57600));
    ui->comboBoxVitesse->addItem(QString::number(115200));
    ui->comboBoxVitesse->setCurrentText(QString::number(9600));

    // combo control de flux
    ui->comboBoxFlux->addItem("pas de contrôle de flux");
    ui->comboBoxFlux->addItem("Materiel (RTS/CTS");
    ui->comboBoxFlux->addItem("logiciel (XON/XOFF)");

    // pas de controle de flux par defaut
    lePort.setFlowControl(QSerialPort::NoFlowControl);

    // pas de parité par defaut
    lePort.setParity(QSerialPort::NoParity);

    // 1 bit de stop par défaut
    lePort.setStopBits(QSerialPort::OneStop);

    // désactiver le bouton ok
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    // valeur par defaut bit de donnée
    lePort.setDataBits(QSerialPort::Data8);


}

DialogConfigurerLiaison::~DialogConfigurerLiaison()
{
    delete ui;
}

void DialogConfigurerLiaison::on_comboBoxPort_currentIndexChanged(int index)
{
    if(index != 0)// index = 0 -> c'est le choisissez un port
    {
        lePort.setPortName(ui->comboBoxPort->currentText());
        // reactiver le bouton ok
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
    else
    {
        // désactiver le bouton ok
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}





void DialogConfigurerLiaison::on_spinBoxBitData_valueChanged(int arg1)
{
    switch (arg1) {
    case 5:
        lePort.setDataBits(QSerialPort::Data5);
        break;
    case 6:
        lePort.setDataBits(QSerialPort::Data6);
        break;
    case 7:
        lePort.setDataBits(QSerialPort::Data7);
        break;
    case 8:
        lePort.setDataBits(QSerialPort::Data8);
        break;
    default:
        lePort.setDataBits(QSerialPort::Data8);
        break;

    }
}


void DialogConfigurerLiaison::on_checkBoxBitsStop_toggled(bool checked)
{
    if(checked )
    {
        lePort.setStopBits(QSerialPort::TwoStop);
    }else
    {
        lePort.setStopBits(QSerialPort::OneStop);

    }
}


void DialogConfigurerLiaison::on_radioButtonPaire_toggled(bool checked)
{
    if(checked)
    {
        lePort.setParity(QSerialPort::EvenParity);
    }
}


void DialogConfigurerLiaison::on_radioButtonImpaire_toggled(bool checked)
{
    if(checked)
    {
        lePort.setParity(QSerialPort::OddParity);
    }
}


void DialogConfigurerLiaison::on_radioButtonPasParite_toggled(bool checked)
{
    if(checked)
    {
        lePort.setParity(QSerialPort::NoParity);
    }
}





void DialogConfigurerLiaison::on_comboBoxVitesse_currentTextChanged(const QString &arg1)
{
    lePort.setBaudRate(arg1.toInt());
}


void DialogConfigurerLiaison::on_comboBoxFlux_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        lePort.setFlowControl(QSerialPort::NoFlowControl);
        break;
    case 1:
        lePort.setFlowControl(QSerialPort::HardwareControl);
        break;
    case 2:
        lePort.setFlowControl(QSerialPort::SoftwareControl);
        break;
    default:
        lePort.setFlowControl(QSerialPort::NoFlowControl);
        break;
    }
}

