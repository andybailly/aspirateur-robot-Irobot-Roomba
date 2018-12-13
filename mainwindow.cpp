#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mCommunication(nullptr)

{
    ui->setupUi(this);
    mRobot= new Robot();
    mDialogConfigurationCommunication= new DialogConfigurationCommunication();

}


MainWindow::~MainWindow()
{
    delete ui;
    delete mRobot;
    delete mDialogConfigurationCommunication;
    if((mCommunication)!=nullptr)
    {
        delete mCommunication;
    }
}

void MainWindow::configurerCommunication()
{

    mDialogConfigurationCommunication->remplir();
    if((mDialogConfigurationCommunication->exec()==QDialog::Accepted))
    {
        delete mCommunication;
        mCommunication=nullptr;
    }
    if(mDialogConfigurationCommunication->port()=="")
    {

    }else if(mDialogConfigurationCommunication->port()=="simulateur")
    {
        mCommunication= new Simulateur;
    }else
    {
        QSerialPort *config= new QSerialPort;
        config->setPortName(mDialogConfigurationCommunication->port());
        config->setBaudRate(QSerialPort::Baud19200);
        config->setDataBits(QSerialPort::Data8);
        config->setParity(QSerialPort::NoParity);
        config->setStopBits(QSerialPort::OneStop);
        config->setFlowControl(QSerialPort::NoFlowControl);
        mCommunication=config;
    }
    mRobot->setCommunication(mCommunication);
}

void MainWindow::on_horizontalSlider_RoueDroite_valueChanged(int value)
{
    mRobot->setPWmRoueDroite(value);
}

void MainWindow::on_pushButton_ArretComplet_clicked()
{
    mRobot->faireArret();
}

void MainWindow::on_pushButton_NettoyageModeClean_clicked()
{
    mRobot->faireNettoyageModeClean();
}

void MainWindow::on_horizontalSlider_RoueGauche_valueChanged(int value)
{
    mRobot->setPWmRoueDroite(value);
}


void MainWindow::on_horizontalSlider_BrossePrincipale_valueChanged(int value)
{
    mRobot->setPwmBrossePrincipale(value);
}

void MainWindow::on_horizontalSlider_BrosseLaterale_valueChanged(int value)
{
    mRobot->setPwmBrosseLaterale(value);
}

void MainWindow::on_horizontalSlider_Aspiration_valueChanged(int value)
{
    mRobot->setPwmAspiration(value);
}


void MainWindow::on_pushButton_Spot_clicked(bool checked)
{
    mRobot->setLedSpot(checked);
}


void MainWindow::on_pushButton_DirtDetect_clicked(bool checked)
{
    mRobot->setLedDirtDetect(checked);
}


void MainWindow::on_horizontalSlider_Intensite_valueChanged(int value)
{
    mRobot->setLedCleanIntensite(value);
}

void MainWindow::on_horizontalSlider_Couleur_valueChanged(int value)
{
    mRobot->setLedCleanCouleur(value);
}

void MainWindow::on_actionConfigurer_triggered()
{
    configurerCommunication();
}

void MainWindow::on_actionConnecter_triggered()
{
    mRobot->connecter();
}

void MainWindow::on_actionDeconnecter_triggered()
{
    mRobot->deconnecter();
}

void MainWindow::on_actionSelectionnerValeurs_triggered()
{

}

void MainWindow::on_actionDemarrerAcquisition_triggered()
{

}

void MainWindow::on_actionArreterAcquisition_triggered()
{

}

void MainWindow::on_actionExporter_triggered()
{

}

void MainWindow::on_actionQuitter_triggered()
{

}
