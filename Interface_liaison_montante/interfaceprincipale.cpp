#include "interfaceprincipale.h"
#include "ui_interfaceprincipale.h"



InterfacePrincipale::InterfacePrincipale(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InterfacePrincipale)
    , configLiaison(lePort)
{
    QTimer timer;

    ui->setupUi(this);
    ui->labelEtatPort->setText("port <font color = 'red'> fermé </font>");
    ui->statusbar->addPermanentWidget(&labelEtatPort);
    ui->statusbar->show();

    connect(&lePort,
            &QSerialPort::readyRead,
            this,
            &InterfacePrincipale::onQSerialPort_ReadyRead);
    connect(&timer, &QTimer::timeout, this,&InterfacePrincipale::onQSerialPort_ReadyRead);

    // les boutons sont désactivés
    ui->pushButtonM8->setEnabled(false);

}

InterfacePrincipale::~InterfacePrincipale()
{
    delete ui;
}

void InterfacePrincipale::onQSerialPort_ReadyRead()
{
        QByteArray recu;
        recu = lePort.readAll();
        trameRecu.append(recu);

    // Traiter les données par paquets terminés par '\n'
    while (trameRecu.contains('\n')){

        int endIndex = trameRecu.indexOf('\n'); // Trouver l'indice du premier '\n' dans la trame en cours

        QByteArray packet = trameRecu.left(endIndex + 1); // Extraire un paquet de données jusqu'à l'indice du '\n'

        trameRecu.remove(0, endIndex + 1);  // Supprimer le paquet extrait de la trame en cours

        packet = packet.trimmed(); // Nettoyer les données en supprimant les espaces avant et après

        if(packet.contains("OK"))
        {
            ui->textEditTrame->append("Le message <font color = 'red'> M8 </font> a bien été reçu par la ttgo");
        }
        else
        {
            qDebug() << "fin communication";
        }
    }
}

void InterfacePrincipale::on_actionConfigurer_triggered()
{
    if (configLiaison.exec() == QDialog::Accepted)
    {
        qDebug()<<lePort.portName();
        //ouverture du port
        if(lePort.open(QIODeviceBase::ReadWrite))
        {

            QString chaine;
            QTextStream (&chaine) << "Port " << lePort.portName()
                                 << ", " << lePort.baudRate()
                                 << ", " << lePort.dataBits()
                                 << ", " << lePort.parity()
                                 << ", " << lePort.stopBits();

            labelEtatPort.setText(chaine);

            ui->labelEtatPort->setText("port <font color = 'green'> ouvert </font>");

            // les boutons sont activés
            ui->pushButtonM8->setEnabled(true);
        }
        else
        {
            labelEtatPort.setText(lePort.errorString());
        }
    }
}

void InterfacePrincipale::on_actionEffacerTout_triggered()
{
    ui->textEditTrame->clear();
}

void InterfacePrincipale::on_pushButtonM8_clicked()
{
    if(lePort.isOpen())
    {
        // Envoyer un message
        QString message = "M8\n";
        // conversion message en tableau de bytes avec encodage UTF-8
        QByteArray data = message.toUtf8();
        // ecriture des données sur le port serie
        lePort.write(data);
        ui->textEditTrame->setText("Envoie du message : <font color = 'red'> M8 </font>");
    }
    else
    {
        qDebug() << "Erreur lors de l'ouverture";
    }
}

