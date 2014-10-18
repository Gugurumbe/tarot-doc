#ifndef PROTOCOLE_DEFINI
#define PROTOCOLE_DEFINI

#include <QDataStream>

//Implémente le protocole 1.0
//Il y a un easter egg, le vois-tu ????

enum {ERREUR_PROTOCOLE, REFUSE, NUMERO, DISTRIBUTION, DECISION, CONTRAT,
      APPEL, APPELER, CONTRAT_FINAL, CHIEN, ECART, JEU, REQUETE, CARTE, 
      PLI, RESULTAT/*, TRESORERIE*/};

struct Msg_erreur_protocole
{
};

struct Msg_refuse
{
};

struct Msg_numero
{
  int n;
};

struct Msg_distribution
{
  int cartes[15];
};

struct Msg_decision
{
  int niveau;
};

struct Msg_contrat
{
  int niveau;
};

struct Msg_appel
{
};

struct Msg_appeler
{
  int carte;
};

struct Msg_contrat_final
{
  int preneur;
  int niveau;
  int appel;
};

struct Msg_chien
{
  int chien[3];
};

struct Msg_ecart
{
  int ecart[3];
};

struct Msg_jeu
{
};

struct Msg_requete
{
  int carte;
};

struct Msg_carte
{
  int carte;
};

struct Msg_pli
{
  int joueur;
};

struct Msg_resultat
{
  int resultats[5];
};

union Msg
{
  struct Msg_erreur_protocole erreur_protocole;
  struct Msg_refuse refuse;
  struct Msg_numero numero;
  struct Msg_distribution distribution;
  struct Msg_decision decision;
  struct Msg_contrat contrat;
  struct Msg_appel appel;
  struct Msg_appeler appeler;
  struct Msg_contrat_final contrat_final;
  struct Msg_chien chien;
  struct Msg_ecart ecart;
  struct Msg_jeu jeu;
  struct Msg_requete requete;
  struct Msg_carte carte;
  struct Msg_pli pli;
  struct Msg_resultat resultat;
};

struct Message
{
  int type;
  bool compris;
  union Msg m;
};

bool lire(QDataStream & in, struct Message & m);
//retourne vrai si on a pu lire le message en entier.
void ecrire(struct Message const & m, QDataStream & out);

#endif
