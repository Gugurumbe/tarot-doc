/**
   @file client/client_graphique.hpp
   @brief Classe d'interface graphique pour le client de tarot virtuel.
 */

#ifndef CLIENT_GRAPHIQUE_DEFINI

/**
   @brief Empêche les inclusions récursives.
 */
#define CLIENT_GRAPHIQUE_DEFINI

#include "ui_client.h"

#include "client_jeu.hpp"

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

public slots:

  /**
     @brief Envoie un message "prise".
     
     Voir l'interface graphique client.ui.
   */
  void on_bouton_enchere_clicked();
  
private:
  Ui::ClientGraphique ui;
  ClientJeu jeu;
};

#endif
