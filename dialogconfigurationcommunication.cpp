#include "dialogconfigurationcommunication.h"
#include "ui_dialogconfigurationcommunication.h"
#include <QSerialPortInfo>

void DialogConfigurationCommunication::remplir()
{

    ui->listWidget->clear();
    const QList <QSerialPortInfo> serialPortInfos = QSerialPortInfo::availablePorts();
    QList<QString> listePorts;
    QString portName;


    QListWidget listWidget;


    ui->listWidget->clear();
    for(int i=0;i<serialPortInfos.count();i++)  listePorts.append(serialPortInfos[i].portName());
    for(int i=0;i<listePorts.count();i++)
    {
        ui->listWidget->addItem(listePorts[i]);
        QString portComm = QString(serialPortInfos[i].portName()+" ("+serialPortInfos[i].manufacturer()+" "+serialPortInfos[i].description()+")");
        ui->listWidget->item(i)->setText(portComm);
        ui->listWidget->item(i)->setData(Qt::UserRole,QVariant(QString(serialPortInfos[i].portName())));
        if((ui->listWidget->item(i)->text()) ==  mPort) ui->listWidget->item(i)->setSelected(true);
    }
    ui->listWidget->addItem("simulateur");
    ui->listWidget->item(ui->listWidget->count()-1)->setData(Qt::UserRole,QVariant(QString("simulateur")));
    if(mPort == "simulateur") ui->listWidget->item(ui->listWidget->count()-1)->setSelected(true);


}


DialogConfigurationCommunication::DialogConfigurationCommunication(QWidget *parent) :
    QDialog(parent),
    mPort(""),
    ui(new Ui::DialogConfigurationCommunication)


{
    ui->setupUi(this);
}

DialogConfigurationCommunication::~DialogConfigurationCommunication()
{
    delete ui;
}

QString DialogConfigurationCommunication::port() const
{
    return mPort;
}

void DialogConfigurationCommunication::setPort(QString port)
{
    mPort = port;
}

void DialogConfigurationCommunication::on_buttonBox_accepted()
{
    QList<QListWidgetItem *> elementSelectionnes = ui->listWidget->selectedItems();

    if(elementSelectionnes.count()==0)
    {
        mPort="";
    }else
    {
        mPort=elementSelectionnes.first()->text();

    }

}
