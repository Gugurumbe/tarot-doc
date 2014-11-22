/**
   @file shared/partie_client.hpp
   @brief Particularise une Partie côté client.
 */

#ifndef PARTIE_CLIENT_DEFINIE

/**
   Empêche les inclusions récursives.
 */
#define PARTIE_CLIENT_DEFINIE

#include "partie.hpp"
#include "main.hpp"

#include <QObject>

/**
   @brief Précision d'une Partie, côté client.

   La classe PartieClient est une Partie qui possède les propriétés
   suivantes :
   1. C'est un QObject, donc elle peut émettre des signaux et définir
   des slots pour faciliter la compréhension de l'avancement d'une
   partie.
   2. Contrairement à la PartieServeur, elle contient de l'information
   particulière pour un seul joueur. Elle connaît son numéro, ses
   cartes, peut deviner son équipe en fonction des cartes qui se
   jouent.
 */
class PartieClient: public QObject, public Partie
{
  Q_OBJECT;
public:

  /**
     @brief Construit un QObject.
     
     @param parent : l'objet parent dans le système Qt.
   */
  PartieClient(QObject * parent = 0);

  /**
     @brief Indique si c'est mon tour.
     
     @return vrai ssi je dois faire une Enchere ou demander à jouer
     une Carte.
   */
  bool mon_tour() const;

  /**
     @brief Indique si le joueur concerné est ami.

     À priori, en début de partie, seul moi-même suis un ami.
     @param joueur : le numéro du joueur à tester.
     @return vrai ssi le joueur est un ami.
   */
  bool est_ami(unsigned int joueur) const;

  /**
     @brief Retourne le numéro du joueur.

     mon_numero() == tour() est équivalent à mon_tour().
     
     @return Le numéro du joueur.
     @see PartieClient::mon_tour() const
  */
  unsigned int mon_numero() const;
  
  /**
     @brief Comprend un Protocole::Message.
    
     La mise à jour du contenu de la Partie côté client s'effectue de
     la façon suivante :
     1. Appel de Partie::assimiler(unsigned int).
     2. Récupération de mon numéro en début de partie.
     3. Récupération de mes cartes en début de partie.
     4. Mise à jour de mes cartes si je prends le Chien et fais un
     écart.
     5. Mise à jour de mes cartes lorsque je joue.
     6. Mise à jour de mon équipe lorsque la Carte appelée se dévoile
     dans mon jeu, dans le Chien et au cours de la partie.

     @see Partie::assimiler(unsigned int)
   */
  void assimiler(const Protocole::Message & message);

  /**
     @brief Regarder mon jeu.

     @return Mon jeu, augmenté des Cartes de l'écart si elles sont
     disponibles. 
   */
  const Main & mon_jeu() const;
private:

  /** Retient le numéro de mon tour. */
  unsigned int m_mon_tour;
  /** Retient mes Cartes. */
  Main mes_cartes;
  /** Retient les 3 cartes que j'écarte a priori.*/
  std::vector<Carte> chien_si_devoile;
  /** Retient les numéros des joueurs de mon équipe. */
  std::vector<unsigned int> mon_equipe;
  /** Retient les cartes dont on veut se séparer. */
  std::vector<Carte> en_chemin;
public slots:

  /**
     @brief Construit un Message.

     Construit un message de type "prise".
     @param p : la prise que souhaite effectuer le client.
     @see PartieClient::doit_emettre(Message)
   */
  void formuler_prise(Enchere::Prise p);

  /**
     @brief Construit un Message.

     Construit un message de type "appeler".
     @param carte : la carte que l'on souhaite appeler.
     @see PartieClient::doit_emettre(Message)
   */
  void appeler(const Carte & carte);

  /**
     @brief Construit un Message.

     Construit un message de type "ecarter".
     @param cartes : les cartes que l'on souhaite écarter.
     @see PartieClient::doit_emettre(Message)
   */
  void ecarter(std::vector<Carte> const & cartes);

  /**
     @brief Construit un Message.

     Construit un message de type "chelem".
     @see PartieClient::demander_jeu()
     @see PartieClient::doit_emettre(Message)
   */
  void demander_chelem();

  /**
     @brief Construit un Message.
     
     Construit un message de type "chelem".
     @see PartieClient::demander_chelem()
     @see PartieClient::doit_emettre(Message)
   */
  void demander_jeu();

  /**
     @brief Construit un Message.

     Construit un message de type "montrer_poignee".
     @param requete : les cartes que l'on souhaite montrer.
     @see PartieClient::doit_emettre(Message)
   */
  void montrer_poignee(std::vector<Carte> const & requete);

  /**
     @brief Construit un Message.
     
     Construit un Message de type "requete".
     @param carte : la carte que l'on souhaite jouer.
     @see PartieClient::doit_emettre(Message)
   */
  void jouer(const Carte & carte);
  
signals:
  
  /**
     @brief Envoyer un Message

     Indique à la partie "réseau" du programme client qu'il faut
     envoyer un Message au serveur.

     Ce Message peut être constitué dans 
     PartieClient::assimiler(const Message &),
     ou par l'un des slots de PartieClient.
     @param m : le Message à envoyer au serveur.
   */
  void doit_emettre(Protocole::Message m);

  /**
     @brief Quitter l'application.

     Indique que la relation avec le serveur n'est plus valable.

     Ce signal est déclenché lorsqu'une erreur de protocole est
     signalée par le serveur.
   */
  void doit_quitter();

  /**
     @brief Le numéro a changé
     @param num Le numéro du client.
   */
  void numero_change(unsigned int num);

  /**
     @brief Votre jeu a été modifié.
   */
  void jeu_change();

  /**
     @brief Action refusée.

     Indique que l'action du client a été refusée par le serveur. Ce
     peut être :
     1. une enchère,
     2. un appel,
     3. un écart,
     4. un chelem,
     5. une poignée,
     6. une carte à jouer.
   */
  void action_refusee();

  /**
     @brief C'est à vous de priser.

     Émis lorsque le tour du client arrive lors de la phase des
     enchères.
   */
  void doit_priser();
  
  /**
     @brief Votre enchère a été refusée.
   */
  void enchere_refusee();

  /**
     @brief Une enchère vient d'être annoncée.

     Émis à la réception d'un Msg_contrat.
     @param joueur : le numéro du joueur dont c'était le tour.
     @param e : l'enchère effectuée.
     @see PartieClient::doit_priser()
   */
  void contrat_intermediaire(unsigned int joueur, Enchere e);

  /**
     @brief Vous devez appeler une Carte.
     
     Émis à la réception d'un Msg_appel.
   */
  void doit_appeler();

  /**
     @brief Vous ne pouvez pas appeler cette Carte.
   */
  void appel_refuse();

  /**
     @brief Les enchères sont terminées.

     Émis à la réception d'un... Msg_contrat_final, bien sûr !
     @param e : l'enchère finale.
   */
  void contrat_final(Enchere e);

  /**
     @brief Voici les 3 cartes du Chien.
     
     Émis à la réception d'un Msg_chien, avant l'émission du signal
     PartieClient::doit_ecarter().
     @param carte1 : la première carte.
     @param carte2 : la deuxième carte.
     @param carte3 : la troisième carte.
   */
  void chien_devoile(Carte carte1, Carte carte2, Carte carte3);

  /**
     @brief Vous devez écarter 3 cartes.

     Émis juste après le signal
     PartieClient::chien_devoile()
   */
  void doit_ecarter();

  /**
     @brief Votre écart a été accepté.
   */
  void ecart_accepte();

  /**
     @brief Votre écart a été refusé.
   */
  void ecart_refuse();

  /**
     @brief On a écarté cette (ces) carte(s).

     Ce signal est émis lorsqu'un Msg_atout est reçu.
     @param atouts : 1, 2 ou 3 cartes.
   */
  void atout_au_chien(std::vector<Carte> atouts);

  /**
     @brief Vous devez dire si vous souhaitez un chelem.

     Ce signal risque de bientôt disparaître, car on pourra facilement
     demander un chelem en même temps que la Prise.  Je pensais le
     faire émettre lorsque le Chien est dévoilé, ou lorsque le contrat
     final est une garde [sans + contre] le Chien.
   */
  void doit_demander_chelem();

  /**
     @brief Un chelem a été demandé !
     
     Émis éventuellement à la réception d'un Msg_jeu.
     Le premier joueur sera celui-ci !
     @note Si c'est vous, le signal doit_jouer() sera émis juste
     après.
     
     @param joueur : le joueur ayant demandé le chelem.
   */
  void chelem_demande(unsigned int joueur);

  /**
     @brief Une poignée a été montrée !

     Lorsque ce signal est émis, c'est encore le tour de celui qui a
     déclaré la poignée.
     @param poignee : les cartes montrées.
   */
  void poignee_montree(std::vector<Carte> poignee);

  /**
     @brief C'est à vous de jouer.

     Ce signal est émis lorsque la PartieClient a déterminé que
     c'était votre tour. C'est-à-dire :
     1. En début de jeu, si mon numéro est le 0 et qu'aucun chelem n'a
     été demandé, ou si j'ai demandé un chelem.
     2. Lorsque le joueur (numéro - 1) a joué une Carte.
   */
  void doit_jouer();

  /**
     @brief Votre requête a été refusée.
     
     Une requête est la demande de jouer une carte.
   */
  void requete_refusee();

  /**
     @brief Votre requête a été acceptée.

     Une requête est la demande de jouer une carte.
   */
  void requete_acceptee();

  /**
     @brief Une Carte a été jouée;
     
     Ce signal est émis lorsqu'un Msg_carte est reçu. Le numéro du
     joueur est déterminé par la classe Partie.
     @param joueur : le numéro de celui qui vient de jouer.
     @param carte : la Carte qui a été jouée.
   */
  void carte_jouee(unsigned int joueur, Carte carte);

  /**
     @brief La partie est finie.

     Ce signal est émis lorsqu'un Msg_resultat est reçu.
     @param scores : les 5 scores des joueurs.
   */
  void score(std::vector<int> scores);

  /**
     @brief La Carte a été gagnée.
     
     Ce signal est émis lorsqu'une Carte a été gagnée par l'un des
     joueurs.

     @param c La carte en question.
     @param poseur Le numéro du joueur qui l'avait posée.
     @param gagnant Le numéro du joueur qui l'a gagnée.
   */
  void carte_gagnee(Carte c, unsigned int poseur, unsigned int gagnant);

  /**
     @brief Le pli a été gagné.

     Ce signal est émis lorsqu'un pli a été remporté.
     
     @param tour Le tour du joueur ayant gagné ce pli.
   */
  void pli(unsigned int tour);

  /**
     @brief Le joueur est maître.
     
     Ce signal est émis lorsque le maître change.

     @param joueur Le joueur maître.
   */
  void maitre(unsigned int joueur);

protected:
  virtual void changement_maitre(unsigned int ancien,
				 unsigned int nouveau);
  virtual void nouveau_maitre(unsigned int maitre);
  virtual void cartes_gagnees
  (std::vector<Carte> const & cartes,
   std::vector<unsigned int> const & poseurs,
   std::vector<unsigned int> const & gagnants);
};

#endif