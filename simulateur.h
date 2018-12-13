#ifndef SIMULATEUR_H
#define SIMULATEUR_H

#include <QIODevice>

class Simulateur : public QIODevice
{
public:
   Simulateur();
protected:
    qint64 readData(char *data, qint64 maxSize);
    qint64 writeData(const char *data, qint64 maxSize);
public:
    bool open(OpenMode mode);
    bool isSequential();
    qint64 bytesAvailable() const;

    void dataToRead(const char *data, qint64 size);
    void dataToRead(QByteArray &data);

    quint64 dataWriten(char *data, qint64 maxSize);
    QByteArray dataWriten();

private:
    QByteArray rxData;
    QByteArray txData;
    void simulateRobot();
    int idxFrame;

};
#endif // SIMULATEUR_H
