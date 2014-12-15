#include <QApplication>
#include <iostream>
#include <QtNetwork>

#define NOM_CLASSE "Testeur"

#include "deboguer.hpp"

#include "testeur_client.hpp"

Testeur::Testeur(PartieClient * partie):QObject(partie) 
{
  ENTER("Testeur(PartieClient * partie)");
  ADD_ARG("partie", partie);
  connect(this, SIGNAL(faire_assimiler(const Protocole::Message)),
	  partie, SLOT(assimiler(const Protocole::Message)));
  connect(this, SIGNAL(formuler_prise(Enchere::Prise)),
	  partie, SLOT(formuler_prise(Enchere::Prise)));
  connect(this, SIGNAL(appeler(const Carte &)),
	  partie, SLOT(appeler(const Carte &)));
  connect(this, SIGNAL(ecarter(std::vector<Carte> const &)),
	  partie, SLOT(ecarter(std::vector<Carte> const &)));
  connect(this, SIGNAL(jouer(const Carte &)),
	  partie, SLOT(jouer(const Carte &)));

#define C(s) connect(partie, SIGNAL(s), this, SLOT(s));
  
  C(doit_emettre(Protocole::Message));
  C(numero_change(unsigned int));
  C(jeu_change(std::vector<Carte>, std::vector<Carte>));
  C(tapis_change(const Tapis &));
  C(doit_priser(Option<Enchere>));
  C(enchere_acceptee(Enchere));
  C(enchere_refusee(Enchere));
  C(contrat_intermediaire(unsigned int, Enchere));
  C(doit_appeler(std::vector<Carte>));
  C(appel_accepte(Carte));
  C(appel_refuse(Carte));
  C(contrat_final(Enchere));
  C(chien_devoile(Carte, Carte, Carte));
  C(doit_ecarter(std::vector<Carte>, std::vector<Carte>));
  C(ecart_accepte(std::vector<Carte>));
  C(ecart_refuse(std::vector<Carte>));
  C(atout_au_chien(std::vector<Carte>));
  C(doit_jouer());
  C(requete_acceptee(Carte));
  C(requete_refusee(Carte));
  C(carte_jouee(unsigned int, Carte));
  C(score(std::vector<int>));
  C(carte_gagnee(Carte, unsigned int, unsigned int));
  C(pli(unsigned int));
  C(maitre(unsigned int));
}
void Testeur::doit_emettre(Protocole::Message m)
{std::cout<<"Je dois émettre le message "<<m<<std::endl;}
void Testeur::numero_change(unsigned int num)
{std::cout<<"Je prends le numéro "<<num<<std::endl;}
void Testeur::jeu_change(std::vector<Carte> gagnees, 
			 std::vector<Carte> perdues)
{std::cout<<"J'ai gagné "<<gagnees<<" et j'ai perdu "<<perdues
	  <<std::endl;}
void Testeur::tapis_change(const Tapis & tapis)
{std::cout<<"Le tapis change : "<<tapis<<std::endl;}
void Testeur::doit_priser(Option<Enchere> max)
{std::cout<<"Je dois priser face à "<<max<<std::endl;}
void Testeur::enchere_acceptee(Enchere e)
{std::cout<<"Mon enchère "<<e<<" a été acceptée."<<std::endl;}
void Testeur::enchere_refusee(Enchere e)
{std::cout<<"Mon enchère "<<e<<" a été refusée."<<std::endl;}
void Testeur::contrat_intermediaire(unsigned int joueur,
				    Enchere e)
{std::cout<<joueur<<" a fait le contrat "<<e<<std::endl;}
void Testeur::doit_appeler(std::vector<Carte> acceptees)
{std::cout<<"Vous devez appeler une carte parmi "<<acceptees
	  <<std::endl;}
void Testeur::appel_accepte(Carte c)
{std::cout<<"Vous avez réussi à appeler "<<c<<std::endl;}
void Testeur::appel_refuse(Carte c)
{std::cout<<"Vous n'avez pas réussi à appeler "<<c<<std::endl;}
void Testeur::contrat_final(Enchere e)
{std::cout<<"Le contrat final est "<<e<<std::endl;}
void Testeur::chien_devoile(Carte c1, Carte c2, Carte c3)
{std::cout<<"Chien : "<<c1<<", "<<c2<<", "<<c3<<std::endl;}
void Testeur::doit_ecarter(std::vector<Carte> possibles,
			   std::vector<Carte> atouts)
{std::cout<<"Je dois écarter parmi "<<possibles<<" voire "<<atouts
	  <<std::endl;}
void Testeur::ecart_accepte(std::vector<Carte> ecart)
{std::cout<<"Mon écart "<<ecart<<" a été accepté."<<std::endl;}
void Testeur::ecart_refuse(std::vector<Carte> ecart)
{std::cout<<"Mon écart "<<ecart<<" a été refusé."<<std::endl;}
void Testeur::atout_au_chien(std::vector<Carte> atouts)
{std::cout<<"Atouts au chien : "<<atouts<<std::endl;}
void Testeur::doit_jouer()
{std::cout<<"Je dois jouer."<<std::endl;}
void Testeur::requete_acceptee(Carte posee)
{std::cout<<"Ma carte "<<posee<<" a été acceptée."<<std::endl;}
void Testeur::requete_refusee(Carte posee)
{std::cout<<"Ma carte "<<posee<<" a été refusée."<<std::endl;}
void Testeur::carte_jouee(unsigned int joueur, Carte carte)
{std::cout<<joueur<<" a joué "<<carte<<std::endl;}
void Testeur::score(std::vector<int> scores)
{std::cout<<"Scores : "<<scores<<std::endl;}
void Testeur::carte_gagnee(Carte c, unsigned int poseur,
			   unsigned int gagnant)
{std::cout<<gagnant<<" gagne la carte de "<<poseur<<" : "<<c
	  <<std::endl;}
void Testeur::pli(unsigned int tour)
{std::cout<<"Levée terminée. C'est à "<<tour<<"."<<std::endl;}
void Testeur::maitre(unsigned int joueur)
{std::cout<<"Le joueur maître est "<<joueur<<std::endl;}

#define EMIT std::cout<<std::endl; emit

void Testeur::run()
{
  ENTER("run()");
  //Numéro : le 2 (3^{ème})
  Protocole::Message m;
  m.type = Protocole::NUMERO;
  m.m.numero.n = 2;
  EMIT faire_assimiler(m);
  //Distribution : 
  m.type = Protocole::DISTRIBUTION;
  for(unsigned int i = 0 ; i < 15 ; i++)
    m.m.distribution.cartes[i] = (5*i) % 78;
  EMIT faire_assimiler(m);
  //Passe pour chacun des autres joueurs
  Protocole::Message erreur;
  erreur.type = Protocole::ERREUR_PROTOCOLE;
  Protocole::Message refus;
  refus.type = Protocole::REFUSE;
  Protocole::Message passe;
  passe.type = Protocole::CONTRAT;
  passe.m.contrat.niveau = 0;
  Protocole::Message prise;
  prise.type = Protocole::PRISE;
  prise.m.prise.niveau = 1;
  //Le joueur 2 essaie de faire une prise :
  EMIT faire_assimiler(prise);
  EMIT faire_assimiler(erreur);
  //Contrat des joueurs 0 et 1 : passe
  EMIT faire_assimiler(passe);
  EMIT faire_assimiler(passe);
  //Le joueur 2 fait sa prise, elle est validée.
  EMIT faire_assimiler(prise);
  passe.m.contrat.niveau = 1;
  EMIT faire_assimiler(passe);
  passe.m.contrat.niveau = 0;
  //Les joueurs 3 et 4 passent
  EMIT faire_assimiler(passe);
  EMIT faire_assimiler(passe);

  //APPELS : J'ai les cartes 
  //Pique   : 1, 6, V
  //Trèfle  : 3, 8, D
  //Carreau : 2, 7, C
  //Coeur   : 4, 9, R
  //Atouts  : 5, 10, 15
  //J'appelle la Dame de Trèfle
  m.type = Protocole::APPELER;
  m.m.appeler.carte = 40;//Dame de Trèfle
  EMIT faire_assimiler(m);
  //La Dame est refusee
  EMIT faire_assimiler(refus);
  m.m.appeler.carte = 41;//Roi de Trèfle
  EMIT faire_assimiler(m);
  //Accepté : contrat final
  m.type = Protocole::CONTRAT_FINAL;
  m.m.contrat_final.preneur = 2;//Moi
  m.m.contrat_final.niveau = 1; //Prise
  m.m.contrat_final.appel = 41;//Roi de Trèfle.
  EMIT faire_assimiler(m);
  //On dévoile le Chien : 75, 76, 77.
  m.type = Protocole::CHIEN;
  m.m.chien.chien[0]=75; //20
  m.m.chien.chien[1]=76; //21
  m.m.chien.chien[2]=77; //excuse
  EMIT faire_assimiler(m);
  //On fait l'écart 75, 76, 77.
  m.type = Protocole::ECART;
  EMIT faire_assimiler(m);
  EMIT faire_assimiler(refus);
  //On fait l'écart valet de pique, cavalier de carreau,
  //as de pique.
  m.m.ecart.ecart[0] = 10; //Valet de Pique
  m.m.ecart.ecart[1] = 25; //Cavalier de Carreau
  m.m.ecart.ecart[2] = 0 ; //As de Pique
  EMIT faire_assimiler(m);
  m.type = Protocole::JEU;
  EMIT faire_assimiler(m);
  //Mes cartes : J'ai les cartes 
  //Pique   : 6
  //Trèfle  : 3, 8, D
  //Carreau : 2, 7
  //Coeur   : 4, 9, R
  //Atouts  : 5, 10, 15, 20, 21, excuse


  std::cout<<"\n\n\n\nPremier tour : \n\n";

  //1er tour
  m.type = Protocole::REQUETE;
  m.m.requete.carte = 77; //On essaye de jouer l'excuse
  EMIT faire_assimiler(m);
  EMIT faire_assimiler(erreur);
  m.type = Protocole::CARTE;
  m.m.requete.carte = DEBUT_COEUR + 5;
  EMIT faire_assimiler(m);
  m.m.requete.carte += 1;
  EMIT faire_assimiler(m);
  //À moi de jouer.
  m.type = Protocole::REQUETE;
  m.m.requete.carte = 77; //On essaye de jouer l'excuse
  EMIT faire_assimiler(m);
  m.type = Protocole::CARTE;
  EMIT faire_assimiler(m);
  //Les 2 derniers gus :
  m.type = Protocole::CARTE;
  m.m.requete.carte = DEBUT_COEUR + 8;
  EMIT faire_assimiler(m);
  m.m.requete.carte -= 1;
  EMIT faire_assimiler(m);
  m.type = Protocole::PLI;
  m.m.pli.joueur = 3;
  EMIT faire_assimiler(m);

  std::cout<<"\n\n\n\nDeuxième tour : \n\n";

  //2ème tour :
  //Le joueur 3 joue un as de trèfle.
  //Le joueur 4 joue le 19 d'atout.
  //Le joueur 0 joue le petit.
  //Le joueur 1 joue l'as de coeur.
  //Le joueur 2 joue le 21.
  //Le pli revient au joueur 2.
  m.type = Protocole::CARTE;
  m.m.carte.carte = DEBUT_TREFLE + 0;
  EMIT faire_assimiler(m);
  m.m.carte.carte = DEBUT_ATOUT + 18;
  EMIT faire_assimiler(m);
  m.m.carte.carte = DEBUT_ATOUT + 0;
  EMIT faire_assimiler(m);
  m.m.carte.carte = DEBUT_COEUR;
  EMIT faire_assimiler(m);
  m.type = Protocole::REQUETE;
  m.m.requete.carte = VINGTETUN;
  EMIT faire_assimiler(m);
  m.type = Protocole::CARTE;
  EMIT faire_assimiler(m);
  m.type = Protocole::PLI;
  m.m.pli.joueur = 2;
  EMIT faire_assimiler(m);
}
