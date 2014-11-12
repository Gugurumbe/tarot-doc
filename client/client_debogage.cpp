#include "client_debogage.hpp"
#include <iostream>
#include <QtConcurrentRun>
#include <string>

#define min(a,b) (a<b?a:b)

std::string nom(unsigned int i)
{
  std::string r;
  switch(i)
    {
    case 0 : r="Agathe";break;
    case 1 : r="Emmanuel";break;
    case 2 : r="Isidore";break;
    case 3 : r="Olivier";break;
    case 4 : r="Ursula";break;
    default: r="un inconnu";break;
    }
  return r ;
}

ClientDebogage::ClientDebogage(QObject * parent):
  Client(parent), m_partie(0)
{
  QObject::connect(this, SIGNAL(connecte()),
		   this, SLOT(traiter_connexion()));
  QObject::connect(this, SIGNAL(deconnecte()),
		   this, SLOT(traiter_deconnexion()));
  QObject::connect(this, SIGNAL(recu(Protocole::Message)),
		   this, SLOT(traiter_message(Protocole::Message)));
  //Comme promis, on connecte les signaux Client aux réactions de débogage.
  QtConcurrent::run(this, &ClientDebogage::demander_ordres);
}

void ClientDebogage::traiter_connexion()
{
  std::cout<<"Vous êtes connecté."<<std::endl;
  m_partie = new PartieClient(this);
  QObject::connect(m_partie, SIGNAL(doit_emettre(Protocole::Message)),
		   this, SLOT(envoyer(Protocole::Message)));
}

void ClientDebogage::traiter_deconnexion()
{
  std::cout<<"Vous êtes déconnecté."<<std::endl;
  m_partie->deleteLater();
  m_partie = 0;
  reconnecter();
}

void ClientDebogage::demander_ordres()
{
  while(true)
    {
      //Réaction face à un nouveau message : on en envoie un.
      Protocole::Message m;
      std::cout<<"Entrez le numéro de type."<<std::endl;
      std::cin>>m.type; // Le type de message.
      char * paquet_perso; //Le paquet perso à compléter
      int taille; //la taille
      int octet; //Sert à demander 1 octet
      QByteArray ba_perso; //Sert à envoyer le paquet perso sous une forme
      //que Qt comprend.
      std::string chaine; //Oui ou non
      switch(m.type)
	{
	case Protocole::ERREUR_PROTOCOLE:
	  std::cout<<"Envoi du message \"erreur_protocole\"..."<<std::endl;
	  envoyer(m);
	  break;
	case Protocole::REFUSE:
	  std::cout<<"Envoi du message \"refuse\"..."<<std::endl;
	  envoyer(m);
	  break;
	case Protocole::NUMERO:
	  std::cout<<"Choisissez le numéro : ";
	  std::cin>>m.m.numero.n;
	  std::cout<<"Envoi du message \"numero\"("<<m.m.numero.n<<")..."<<
	    std::endl;
	  envoyer(m);
	  break;
	case Protocole::DISTRIBUTION:
	  std::cout<<"Choisissez les 15 cartes : "<<std::endl;
	  for(int i = 0 ; i < 15 ; i ++)
	    {
	      std::cin>>m.m.distribution.cartes[i];
	    }
	  std::cout<<"Envoi du message \"distribution\"..."<<std::endl;
	  envoyer(m);
	  break;
	case Protocole::PRISE:
	  std::cout<<"Alors, vous prenez ? (nombre) "<<std::endl;
	  std::cin>>m.m.prise.niveau;
	  std::cout<<"Envoi du message \"prise\"..."<<std::endl;
	  envoyer(m);
	  break;
	case Protocole::CONTRAT:
	  std::cout<<"Quel contrat allez-vous déclarer ? (nombre) "<<std::endl;
	  std::cin>>m.m.contrat.niveau;
	  std::cout<<"Envoi du message \"contrat\"..."<<std::endl;
	  envoyer(m);
	  break;
	case Protocole::APPEL:
	  std::cout<<"Envoi du message \"appel\"..."<<std::endl;
	  envoyer(m);
	  break;
	case Protocole::APPELER:
	  std::cout<<"Quelle carte allez-vous appeler ?"<<std::endl;
	  std::cin>>m.m.appeler.carte;
	  std::cout<<"Envoi du message \"appeler\"..."<<std::endl;
	  envoyer(m);
	  break;
	case Protocole::CONTRAT_FINAL:
	  std::cout<<"Quel contrat final décide le serveur ?"<<std::endl;
	  std::cout<<"Preneur : ";
	  std::cin>>m.m.contrat_final.preneur;
	  std::cout<<"Niveau : ";
	  std::cin>>m.m.contrat_final.niveau;
	  std::cout<<"Carte appelée : ";
	  std::cin>>m.m.contrat_final.appel;
	  std::cout<<"Envoi du message \"contrat_final\"..."<<std::endl;
	  envoyer(m);
	  break;
	case Protocole::CHIEN:
	  std::cout<<"Quel chien montrez-vous au preneur ?"<<std::endl;
	  for(int i = 0 ; i < 3 ; i ++)
	    {
	      std::cin>>m.m.chien.chien[i];
	    }
	  std::cout<<"Envoi du message \"chien\"..."<<std::endl;
	  envoyer(m);
	  break;
	case Protocole::ECART:
	  std::cout<<"Quel écart souhaitez-vous faire ?"<<std::endl;
	  for(int i = 0 ; i < 3 ; i ++)
	    {
	      std::cin>>m.m.ecart.ecart[i];
	    }
	  std::cout<<"Envoi du message \"ecart\"..."<<std::endl;
	  envoyer(m);
	  break;      
	case Protocole::ATOUT:
	  std::cout<<"Combien d'atouts souhaitez-vous mettre au chien ?"<<std::endl;
	  std::cin>>m.m.atout.nombre;
	  if(m.m.atout.nombre > 3) m.m.atout.nombre = 3;
	  std::cout<<"Entrez les numéros de carte des "<<m.m.atout.nombre<<" atouts : ";
	  for(int i = 0 ; i < m.m.atout.nombre ; i++)
	    {
	      std::cin>>m.m.atout.cartes[i];
	    }
	  std::cout<<"Envoi du message \"atout\"..."<<std::endl;
	  envoyer(m);
	  break;
	case Protocole::CHELEM:
	  std::cout<<"Voulez-vous demander un chelem ? o/*"<<std::endl;
	  std::cin>>chaine;
	  m.m.chelem.demande = (QString(chaine.c_str()).trimmed() == "o");
	  std::cout<<"Envoi du message \"chelem\"..."<<std::endl;
	  envoyer(m);
	  break;
	case Protocole::JEU:
	  std::cout<<"Voulez-vous attribuer un chelem à quelqu'un ? "
		   <<"Si oui, entrez son numéro (0-4), sinon entrez 5 ou"
		   <<" plus."<<std::endl;
	  std::cin>>m.m.jeu.chelem;
	  std::cout<<"Envoi du message \"jeu\"..."<<std::endl;
	  envoyer(m);
	  break;
	case Protocole::MONTRER_POIGNEE:
	  std::cout<<"Entrez la taille de la poignée (8, 10 ou 13)..."<<std::endl;
	  std::cin>>m.m.montrer_poignee.taille;
	  std::cout<<"Entrez les "<<min(m.m.montrer_poignee.taille, 13)
		   <<" cartes : ";
	  for(int i = 0 ; i < m.m.montrer_poignee.taille && i < 13 ; i++)
	    {
	      std::cin>>m.m.montrer_poignee.atouts[i];
	    }
	  std::cout<<"Envoi du message \"montrer_poignee\"..."<<std::endl;
	  envoyer(m);
	  break;
	case Protocole::POIGNEE:
	  std::cout<<"Entrez la taille de la poignée (8, 10 ou 13)..."<<std::endl;
	  std::cin>>m.m.poignee.taille;
	  std::cout<<"Entrez les "<<min(m.m.poignee.taille, 13)<<" cartes : ";
	  for(int i = 0 ; i < m.m.poignee.taille && i < 13 ; i++)
	    {
	      std::cin>>m.m.poignee.atouts[i];
	    }
	  std::cout<<"Envoi du message \"poignee\"..."<<std::endl;
	  envoyer(m);
	  break;
	case Protocole::REQUETE:
	  std::cout<<"Quelle carte voulez-vous jouer ?"<<std::endl;
	  std::cin>>m.m.requete.carte;
	  std::cout<<"Envoi du message \"requete\"..."<<std::endl;
	  envoyer(m);
	  break;
	case Protocole::CARTE:
	  std::cout<<"Quelle carte voulez-vous faire jouer ?"<<std::endl;
	  std::cin>>m.m.carte.carte;
	  std::cout<<"Envoi du message \"carte\"..."<<std::endl;
	  envoyer(m);
	  break;
	case Protocole::PLI:
	  std::cout<<"À qui revient le pli ?"<<std::endl;
	  std::cin>>m.m.pli.joueur;
	  std::cout<<"Envoi du message \"pli\"..."<<std::endl;
	  envoyer(m);
	  break;
	case Protocole::RESULTAT:
	  std::cout<<"Rentrez les résultats des 5 joueurs : ";
	  for(int i = 0 ; i < 5 ; i ++)
	    {
	      std::cin>>m.m.resultat.resultats[i];
	    }
	  std::cout<<"Envoi du message \"resultat\"..."<<std::endl;
	  envoyer(m);
	  break;
	default:
	  std::cout<<"Vous voulez jouer ? OK : entrez la taille du paquet."
		   <<std::endl;
	  std::cin>>taille;
	  paquet_perso = new char[taille];
	  std::cout<<"Entrez les octets en base 10 (positifs) : ";
	  for(int i = 0 ; i < taille ; i++)
	    {
	      std::cin>>octet;
	      paquet_perso[i] = (char) octet;
	    }
	  ba_perso.append(paquet_perso, taille);
	  std::cout<<"Envoi du paquet perso..."<<std::endl;
	  envoyer(ba_perso);
	  delete[] paquet_perso;
	}
    }
}

void ClientDebogage::traiter_message(Protocole::Message m)
{
  //Attention : on affiche tous les champs de message, pour être exhaustif.
  //Ils n'ont peut-être rien de pertinent : si le serveur vous dit que vous
  //avez fait une erreur de protocole, les cartes du chien n'ont pas à vous
  //inquiéter.
  std::cout<<"Vous avez un message : "<<std::endl;
  std::cout<<"Type : "<<m.type<<std::endl;
  std::cout<<(m.compris?"Le message est compris.":
	      "Le message n'a pas été compris.")<<std::endl;
  std::cout<<Protocole::ERREUR_PROTOCOLE<<" : Erreur protocole"<<std::endl;
  std::cout<<Protocole::REFUSE<<" : Refuse"<<std::endl;
  std::cout<<Protocole::NUMERO<<" : Numéro : "<<m.m.numero.n<<std::endl;
  std::cout<<Protocole::DISTRIBUTION<<" : Distribution : ";
  for(int i = 0 ; i < 15 ; i ++) std::cout<<m.m.distribution.cartes[i]<<", ";
  std::cout<<std::endl;
  std::cout<<Protocole::PRISE<<" : Prise : "<<m.m.prise.niveau<<std::endl;
  std::cout<<Protocole::CONTRAT<<" : Contrat : "<<m.m.contrat.niveau<<std::endl;
  std::cout<<Protocole::APPEL<<" : Appel"<<std::endl;
  std::cout<<Protocole::APPELER<<" : Appeler : "<<m.m.appeler.carte<<std::endl;
  std::cout<<Protocole::CONTRAT_FINAL<<" : Contrat final : "
	   <<m.m.contrat_final.preneur<<", "
	   <<m.m.contrat_final.niveau<<", "
	   <<m.m.contrat_final.appel<<std::endl;
  std::cout<<Protocole::CHIEN<<" : Chien : ";
  for(int i = 0 ; i < 3 ; i ++) std::cout<<m.m.chien.chien[i]<<", ";
  std::cout<<std::endl;
  std::cout<<Protocole::ECART<<" : Écart : ";
  for(int i = 0 ; i < 3 ; i ++) std::cout<<m.m.ecart.ecart[i]<<", ";
  std::cout<<std::endl;
  std::cout<<Protocole::ATOUT<<" : Atout : taille "<<m.m.atout.nombre<<", ";
  for(int i = 0 ; i < 3 ; i++)
    std::cout<<m.m.atout.cartes[i]<<", ";
  std::cout<<std::endl;
  std::cout<<Protocole::CHELEM<<" : Chelem : "
	   <<(m.m.chelem.demande != 0 ?"demandé":"non demandé")
	   <<std::endl;
  std::cout<<Protocole::JEU<<" : Jeu : "
	   <<(m.m.jeu.chelem >= 5 ? "sans chelem (":"avec chelem (")
	   <<m.m.jeu.chelem<<")"<<std::endl;
  std::cout<<Protocole::MONTRER_POIGNEE<<" : Montrer poignée : taille "
	   <<(m.m.montrer_poignee.taille)<< " : ";
  for(int i = 0 ; i < 13 && i < m.m.montrer_poignee.taille ; i++)
    std::cout<<m.m.montrer_poignee.atouts[i]<<", ";
  std::cout<<std::endl;
  std::cout<<Protocole::POIGNEE<<" : Poignée : taille "<<(m.m.poignee.taille)<< " : ";
  for(int i = 0 ; i < 13 && i < m.m.poignee.taille ; i++) 
    std::cout<<m.m.poignee.atouts[i]<<", ";
  std::cout<<std::endl;
  std::cout<<Protocole::REQUETE<<" : Requête : " << m.m.requete.carte<<std::endl;
  std::cout<<Protocole::CARTE<<" : Carte : "<<m.m.carte.carte<<std::endl;
  std::cout<<Protocole::PLI<<" : Pli : "<<m.m.pli.joueur<<std::endl;
  std::cout<<Protocole::RESULTAT<<" : Résultat : ";
  for(int i = 0 ; i < 5 ; i ++) std::cout<<m.m.resultat.resultats[i]<<", ";
  std::cout<<std::endl;

  m_partie->assimiler(m);
  afficher_etat();
}

std::string nom_d_atout(Carte::Valeur i)
{
  std::string r = "\x1B[33m";
  switch((int)i)
    {
    case 1 : r+="Petit";break;
    case 2 : r+="Deux d'Atout";break;
    case 3 : r+="Trois d'Atout";break;
    case 4 : r+="Quatre d'Atout";break;
    case 5 : r+="Cinq d'Atout";break;
    case 6 : r+="Six d'Atout";break;
    case 7 : r+="Sept d'Atout";break;
    case 8 : r+="Huit d'Atout";break;
    case 9 : r+="Neuf d'Atout";break;
    case 10 : r+="Dix d'Atout";break;
    case 11 : r+="Onze d'Atout";break;
    case 12 : r+="Douze d'Atout";break;
    case 13 : r+="Treize d'Atout";break;
    case 14 : r+="Quatorze d'Atout";break;
    case 15 : r+="Quinze d'Atout";break;
    case 16 : r+="Seize d'Atout";break;
    case 17 : r+="Dix-sept d'Atout";break;
    case 18 : r+="Dix-huit d'Atout";break;
    case 19 : r+="Dix-neuf d'Atout";break;
    case 20 : r+="Vingt d'Atout";break;
    case 21 : r+="Vingt-et-un d'Atout";break;
    default : r+="Un atout inconnu";
    }
  r += "\x1B[0m";
  return r;
}

std::string nom_valeur(Carte::Valeur v)
{
  std::string r;
  switch(v)
    {
    case 0 : r+="As";break;
    case 1 : r+="Deux";break;
    case 2 : r+="Trois";break;
    case 3 : r+="Quatre";break;
    case 4 : r+="Cinq";break;
    case 5 : r+="Six";break;
    case 6 : r+="Sept";break;
    case 7 : r+="Huit";break;
    case 8 : r+="Neuf";break;
    case 9 : r+="Dix";break;
    case 10 : r+="Valet";break;
    case 11 : r+="Cavalier";break;
    case 12 : r+="Dame";break;
    case 13 : r+="Roi";break;
    default : r+="Valeur inconnue";
    }
  return r;
}

std::string nom_carte(Carte c)
{
  std::string r;
  if(c == EXCUSE)r="\x1B[33mExcuse";
  else switch(c.couleur())
	 {
	 case Carte::PIQUE :
	   r="\x1B[34m"+nom_valeur(c.valeur())+" de Pique";
	   break;
	 case Carte::TREFLE :
	   r="\x1B[32m"+nom_valeur(c.valeur())+" de Trèfle";
	   break;
	 case Carte::CARREAU :
	   r="\x1B[31m"+nom_valeur(c.valeur())+" de Carreau";
	   break;
	 case Carte::COEUR :
	   r="\x1B[35m"+nom_valeur(c.valeur())+" de Coœur";
	   break;
	 default :
	   r=nom_d_atout(c.valeur());
	 }
  r += "\x1B[0m";
  return r;
}

void presenter_jeu(const Main & m)
{
  std::cout<<"Votre jeu : ["<<std::endl;
  for(unsigned int i = 0 ; i < 78 ; i++)
    {
      if(m.possede(Carte(i)))
	{
	  std::cout<<nom_carte(Carte(i))<<" ("<<i<<");"<<std::endl;
	}
    }
  std::cout<<"]"<<std::endl;
}

void ClientDebogage::afficher_etat()
{
  std::cout<<std::endl;
  if(m_partie)
    {
      std::cout<<"Vous êtes "<<nom(m_partie->mon_numero())<<"."<<std::endl;
      presenter_jeu(m_partie->mon_jeu());
      switch(m_partie->phase())
	{
	case Partie::CONSTITUTION_TABLE :
	  std::cout<<"On en est à la constitution de la Table."
		   <<std::endl;
	  break;
	case Partie::ENCHERES :
	  std::cout<<"On en est aux enchères."<<std::endl;
	  if(m_partie->mon_tour())
	    std::cout<<"C'est à votre tour, "
		     <<nom(m_partie->mon_numero())<<std::endl;
	  else
	    std::cout<<"C'est au tour d'"
		     <<nom(m_partie->tour())<<"."<<std::endl;
	  break;
	case Partie::CONSTITUTION_ECART :
	  std::cout<<"On en est à la constitution de l'écart."
		   <<std::endl;
	  if(m_partie->mon_numero() == m_partie->attaquant())
	    {
	      std::cout<<"Vous devez composer un écart."<<std::endl;
	    }
	  break;
	case Partie::PHASE_JEU :
	  std::cout<<"On en est à la phase de jeu."<<std::endl;
	  if(m_partie->mon_tour())
	    std::cout<<"C'est à votre tour, "
		     <<nom(m_partie->mon_numero())<<std::endl;
	  else
	    std::cout<<"C'est au tour d'"
		     <<nom(m_partie->tour())<<"."<<std::endl;
	  break;
	case Partie::FIN :
	  std::cout<<"C'est fini."<<std::endl;
	  break;
	default :
	  std::cout<<"Erreur dans l'implémentation de Partie."
		   <<std::endl;
	}
    }
  else
    std::cout<<"Connexion en cours..."<<std::endl;
}
