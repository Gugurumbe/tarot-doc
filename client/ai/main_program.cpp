#include <QCoreApplication>
#include "./config.hpp"
#include "ia.hpp"

int main(int argc, char * argv[])
{
  QCoreApplication app(argc, argv);
  IA * ia = new IA;
  ia->connecter(AUTO_ADDR, AUTO_PORT);
  QObject::connect(ia, SIGNAL(destroyed()),
		   &app, SLOT(quit()));
  return app.exec();
}
