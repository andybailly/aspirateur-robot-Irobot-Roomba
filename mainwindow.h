/** @file
 *  @copyright GPLv3
 *  @date 12/10/2017
 *  @author AB
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"robot.h"
#include"dialogconfigurationcommunication.h"
#include<QIODevice>
#include<QSerialPort>
#include<simulateur.h>


namespace Ui {

class Unit_mainwindowTest;

class MainWindow;
}
/**
 * @brief Interface graphique de l'application
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_horizontalSlider_RoueDroite_valueChanged(int value);

    void on_pushButton_ArretComplet_clicked();

    void on_pushButton_NettoyageModeClean_clicked();

    void on_horizontalSlider_RoueGauche_valueChanged(int value);

    void on_horizontalSlider_BrossePrincipale_valueChanged(int value);

    void on_horizontalSlider_BrosseLaterale_valueChanged(int value);

    void on_horizontalSlider_Aspiration_valueChanged(int value);

    void on_pushButton_Spot_clicked(bool checked);

    void on_pushButton_DirtDetect_clicked(bool checked);

    void on_horizontalSlider_Intensite_valueChanged(int value);

    void on_horizontalSlider_Couleur_valueChanged(int value);

    void on_actionConfigurer_triggered();

    void on_actionConnecter_triggered();

    void on_actionDeconnecter_triggered();

    void on_actionSelectionnerValeurs_triggered();

    void on_actionDemarrerAcquisition_triggered();

    void on_actionArreterAcquisition_triggered();

    void on_actionExporter_triggered();

    void on_actionQuitter_triggered();

private:
    Ui::MainWindow *ui;
    Robot *mRobot;
    DialogConfigurationCommunication *mDialogConfigurationCommunication;
    QIODevice *mCommunication;
    void configurerCommunication();
    friend class Unit_mainwindowTest;
};

#endif // MAINWINDOW_H
