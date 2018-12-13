#ifndef DIALOGCONFIGURATIONCOMMUNICATION_H
#define DIALOGCONFIGURATIONCOMMUNICATION_H

#include <QDialog>

namespace Ui {
class DialogConfigurationCommunication;
}

class DialogConfigurationCommunication : public QDialog
{
    Q_OBJECT

public:
    void remplir();
    explicit DialogConfigurationCommunication(QWidget *parent = 0);
    ~DialogConfigurationCommunication();

    QString port() const;
    void setPort(const QString port);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogConfigurationCommunication *ui;
    QString mPort;

};

#endif // DIALOGCONFIGURATIONCOMMUNICATION_H
