/**
   @file client/journal.hpp
   @brief Widget personnalisé.
 */

#ifndef JOURNAL_DEFINI

/**
   @brief Empêche les inclusions récursives.
 */
#define JOURNAL_DEFINI

#include <QTextBrowser>

/**
   @brief Classe permettant d'afficher les événements du jeu.
 */
class Journal : public QTextBrowser
{
  Q_OBJECT;
public:
  /**
     @brief Constructeur par défaut.
     
     @param parent Le widget parent.
   */
  Journal(QWidget * parent = 0);
public slots :
  /**
     @brief Indique au joueur qu'il est connecté.
   */
  void afficher_connexion();
  /**
     @brief Indique au joueur qu'il est déconnecté.
   */
  void afficher_deconnexion();
  /**
     @brief Indique au joueur qu'il a reçu son numéro.
     @param n Mon numéro.
   */
  void afficher_numero(unsigned int n);

private:
  QString header;
  QString footer;
};

#endif
