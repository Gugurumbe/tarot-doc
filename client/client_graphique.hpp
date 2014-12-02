/**
   @brief Classe d'interface graphique pour le client de tarot virtuel.
 */

#ifndef CLIENT_GRAPHIQUE_DEFINI

/**
   @brief Empêche les inclusions récursives.
 */
#define CLIENT_GRAPHIQUE_DEFINI

#include "ui_client.h"

#include <QWidget>

/**
   @brief Définition de la classe d'interface graphique principale.
 */
class ClientGraphique : public QWidget
{
  Q_OBJECT;
public:
  
  /**
     @brief Construit le Widget.
     
     @param parent Le widget parent au sens de Qt.
  */
  ClientGraphique(QWidget * parent = 0);

private:
  Ui::ClientGraphique ui;
};

#endif
