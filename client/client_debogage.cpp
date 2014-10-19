#include "client_debogage.hpp"
#include <iostream>

ClientDebogage::ClientDebogage(QObject * parent): Client(parent)
{
  QObject::connect(this, SIGNAL(connecte()),
		   this, SLOT(traiter_connexion()));
  QObject::connect(this, SIGNAL(deconnecte()),
		   this, SLOT(traiter_deconnexion()));
  QObject::connect(this, SIGNAL(recu(Message)),
		   this, SLOT(traiter_message(Message)));
  //Comme promis, on connecte les signaux Client aux réactions de débogage.
}

void ClientDebogage::traiter_connexion()
{
  std::cout<<"Vous êtes connecté."<<std::endl;
  // Merci capitaine.
  demander_ordres();
  //On demande à l'utilisateur ce qu'il veut envoyer.
}

void ClientDebogage::traiter_deconnexion()
{
  std::cout<<"Vous êtes déconnecté."<<std::endl;
  //Merci capitaine.
}

void ClientDebogage::demander_ordres()
{
  //Réaction face à un nouveau message : on en envoie un.
  Message m;
  std::cout<<"À vous maintenant : entrez le numéro de type."<<std::endl;
  std::cin>>m.type; // Le type de message.
  char * paquet_perso; //Le paquet perso à compléter
  int taille; //la taille
  int octet; //Sert à demander 1 octet
  QByteArray ba_perso; //Sert à envoyer le paquet perso sous une forme
  //que Qt comprend.
  switch(m.type)
    {
    case ERREUR_PROTOCOLE:
      std::cout<<"Envoi du message \"erreur_protocole\"..."<<std::endl;
      envoyer(m);
      break;
    case REFUSE:
      std::cout<<"Envoi du message \"refuse\"..."<<std::endl;
      envoyer(m);
      break;
    case NUMERO:
      std::cout<<"Choisissez le numéro : ";
      std::cin>>m.m.numero.n;
      std::cout<<"Envoi du message \"numero\"("<<m.m.numero.n<<")..."<<
	std::endl;
      envoyer(m);
      break;
    case DISTRIBUTION:
      std::cout<<"Choisissez les 15 cartes : "<<std::endl;
      for(int i = 0 ; i < 15 ; i ++)
	{
	  std::cin>>m.m.distribution.cartes[i];
	}
      std::cout<<"Envoi du message \"distribution\"..."<<std::endl;
      envoyer(m);
      break;
    case DECISION:
      std::cout<<"Alors, vous prenez ? (nombre) "<<std::endl;
      std::cin>>m.m.decision.niveau;
      std::cout<<"Envoi du message \"decision\"..."<<std::endl;
      envoyer(m);
      break;
    case CONTRAT:
      std::cout<<"Quel contrat allez-vous déclarer ? (nombre) "<<std::endl;
      std::cin>>m.m.contrat.niveau;
      std::cout<<"Envoi du message \"contrat\"..."<<std::endl;
      envoyer(m);
      break;
    case APPEL:
      std::cout<<"Envoi du message \"appel\"..."<<std::endl;
      envoyer(m);
      break;
    case APPELER:
      std::cout<<"Quelle carte allez-vous appeler ?"<<std::endl;
      std::cin>>m.m.appeler.carte;
      std::cout<<"Envoi du message \"appeler\"..."<<std::endl;
      envoyer(m);
      break;
    case CONTRAT_FINAL:
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
    case CHIEN:
      std::cout<<"Quel chien montrez-vous au preneur ?"<<std::endl;
      for(int i = 0 ; i < 3 ; i ++)
	{
	  std::cin>>m.m.chien.chien[i];
	}
      std::cout<<"Envoi du message \"chien\"..."<<std::endl;
      envoyer(m);
      break;
    case ECART:
      std::cout<<"Quel écart souhaitez-vous faire ?"<<std::endl;
      for(int i = 0 ; i < 3 ; i ++)
	{
	  std::cin>>m.m.ecart.ecart[i];
	}
      std::cout<<"Envoi du message \"ecart\"..."<<std::endl;
      envoyer(m);
      break;      
    case JEU:
      std::cout<<"Envoi du message \"jeu\"..."<<std::endl;
      envoyer(m);
      break;
    case REQUETE:
      std::cout<<"Quelle carte voulez-vous jouer ?"<<std::endl;
      std::cin>>m.m.requete.carte;
      std::cout<<"Envoi du message \"requete\"..."<<std::endl;
      envoyer(m);
      break;
    case CARTE:
      std::cout<<"Quelle carte voulez-vous faire jouer ?"<<std::endl;
      std::cin>>m.m.carte.carte;
      std::cout<<"Envoi du message \"carte\"..."<<std::endl;
      envoyer(m);
      break;
    case PLI:
      std::cout<<"À qui revient le pli ?"<<std::endl;
      std::cin>>m.m.pli.joueur;
      std::cout<<"Envoi du message \"pli\"..."<<std::endl;
      envoyer(m);
      break;
    case RESULTAT:
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

void ClientDebogage::traiter_message(Message m)
{
  //Attention : on affiche tous les champs de message, pour être exhaustif.
  //Ils n'ont peut-être rien de pertinent : si le serveur vous dit que vous
  //avez fait une erreur de protocole, les cartes du chien n'ont pas à vous
  //inquiéter.
  std::cout<<"Vous avez un message : "<<std::endl;
  std::cout<<"Type : "<<m.type<<std::endl;
  std::cout<<(m.compris?"Le message est compris.":
	      "Le message n'a pas été compris.")<<std::endl;
  std::cout<<"Numéro : "<<m.m.numero.n<<std::endl;
  std::cout<<"Distribution : ";
  for(int i = 0 ; i < 15 ; i ++) std::cout<<m.m.distribution.cartes[i]<<", ";
  std::cout<<std::endl;
  std::cout<<"Décision : "<<m.m.decision.niveau<<std::endl;
  std::cout<<"Contrat : "<<m.m.contrat.niveau<<std::endl;
  std::cout<<"Appeler : "<<m.m.appeler.carte<<std::endl;
  std::cout<<"Contrat final : "<<m.m.contrat_final.preneur<<", "
	   <<m.m.contrat_final.niveau<<", "
	   <<m.m.contrat_final.appel<<std::endl;
  std::cout<<"Chien : ";
  for(int i = 0 ; i < 3 ; i ++) std::cout<<m.m.chien.chien[i]<<", ";
  std::cout<<std::endl;
  std::cout<<"Écart : ";
  for(int i = 0 ; i < 3 ; i ++) std::cout<<m.m.ecart.ecart[i]<<", ";
  std::cout<<std::endl;
  std::cout<<"Requête : " << m.m.requete.carte<<std::endl;
  std::cout<<"Carte : "<<m.m.carte.carte<<std::endl;
  std::cout<<"Pli : "<<m.m.pli.joueur<<std::endl;
  std::cout<<"Résultat : ";
  for(int i = 0 ; i < 5 ; i ++) std::cout<<m.m.resultat.resultats[i]<<", ";
  std::cout<<std::endl;
  demander_ordres();
}
