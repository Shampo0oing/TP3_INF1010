//! implémentation de classe Episode
//! \author Samuel Lavallée et Anthelme Clisson
//! \date 29 fevrier 2020

#include "Episode.h"

using namespace std;

//! constructeur par defaut de classe Episode
Episode::Episode(): numEpisode_(01), nom_("Episode:01"), duree_("00:00 : 00")
{
}

//! opérateur par paramètres de classe Episode
//! \param numEpisode: numero de l'episode
//! \param nom: Nom de l'episode 
//! \param duree: Duree de l'episode
Episode::Episode(unsigned int numEpisode, const std::string& nom, const std::string& duree): numEpisode_(numEpisode), nom_(nom), duree_(duree)
{
}

//! opérateur qui compare 2 episodes 
//! \param numEpisode Numero de l'episode à comparer avec l'appelant
//! \ return bool true si mêmes episodes sinon false

bool Episode::operator==(unsigned int numEpisode) {
	return(numEpisode_ == numEpisode ? true : false);
}

//! opérateur qui affiche un episode 
//! \param os Stream dans lequel afficher
//! \param episode, episode à afficher
//! \return stream os pour appel en cascade
std::ostream& operator<<(std::ostream& os, const Episode& episode)
{
	if (episode.numEpisode_ < 10) {
		os << "Episode" << " " << "0" << episode.numEpisode_ << ":" << " " << episode.nom_ << " " << "| " << "Durée:" << " " << episode.duree_;
	}
	else {
		os << "Episode" << " "  << episode.numEpisode_ << ":" << " " << episode.nom_ << " " << "| " << "Durée:" << " " << episode.duree_;
	}
	return os;
	
}

//! opérateur qui lit un episode
//! \param istream duquel lire
//! \param episode: Episode à lire 
//! \return istream pour appel en cascade
std::istream& operator>>(std::istream& is, Episode& episode)
{
	is >> episode.numEpisode_ >> quoted(episode.nom_) >> quoted(episode.duree_);

	return is;
}

//! methode qui retourne le numero de l'episode 
//! \return numEpisode_: numero de l'episode
unsigned int Episode::getNumEpisode() const
{
	return numEpisode_;
}

