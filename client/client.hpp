#ifndef CLIENT_DEFINI
#define CLIENT_DEFINI

#include <QObject>
#include <QHostAddress>
#include <QTcpSocket>
#include "protocole.hpp"

class Client: public QObject
{
  Q_OBJECT;
public:
  Client(QObject * parent = 0);
public slots:
  void reconnecter();
  void connecter(QHostAddress, unsigned int);
  void deconnecter();
  void envoyer(Message);
  void envoyer(QByteArray);
signals:
  void connecte();
  void deconnecte();
  void recu(Message);
private slots:
  void recevoir();
private:
  QTcpSocket sock;
  QHostAddress hote;
  unsigned int port;
};

#endif
