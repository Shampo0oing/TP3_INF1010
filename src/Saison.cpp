//! implémentation de classe Saison
//! \author Samuel Lavallée et Anthelme Clisson
//! \date 29 fevrier 2020

#include "Saison.h"
#include <iostream>

using namespace std;

//! \ constructeur par défaut de classe Saison
Saison::Saison() : numSaison_(1), nbEpisodesmax_(0)
{
}

//! \ constructeur par paramètres de la classe Saison
//! \param numSaison (numero de la saison), nbEpisodemax (nombre d'episode max de la saison)
Saison::Saison(unsigned int numSaison, unsigned int nbEpisodemax): numSaison_(numSaison), nbEpisodesmax_(nbEpisodemax)
{
}

//! \ constructeur par copie de la classe Saison
//! \ param saison: saison a copier
Saison::Saison(const Saison& saison)
{
	numSaison_ = saison.numSaison_; nbEpisodesmax_= saison.nbEpisodesmax_;
	vector<unique_ptr<Episode>> vect;
	for (int i = 0; i < saison.episodes_.size(); i++)
		vect.push_back(make_unique<Episode>(*episodes_[i]));


}

//! \ destructeur de la classe Saison
Saison::~Saison()
{
	episodes_.clear();
}

//! opérateur qui ajoute un episode à la saison
//! \param episode: unique ptr vers episode à ajouter
//! \return *this soit l'objet appelant pour appel en cascade
Saison& Saison::operator+=(std::unique_ptr<Episode> episode)
{
	
	if (episode) {
		if (episodes_.size() < nbEpisodesmax_) {
			int index = trouverIndexEpisode(episode->getNumEpisode());
			if (index > -1) {
				episodes_.erase(episodes_.begin() + index);
			}

			episodes_.push_back(move(episode));
		}
		
		
		
	};

	sort(episodes_.begin(), episodes_.end(), Episode::SortByNumEpisode());
	return *this;
}

//! opérateur qui enleve un episode de la saison
//! \param numEpisode: numero de l'Episode à enlever
//! \return *this soit l'objet appelant pour appel en cascade
Saison& Saison::operator-=(unsigned int numEpisode)
{
	int index = trouverIndexEpisode(numEpisode);

	if (index >= 0) {
		episodes_.erase(episodes_.begin() + index);

	}
	return *this;
}

//! opérateur qui compare 1 saison et 1 numero
//! \param numSaison: numero de la saison à comparer
//! \return bool: true si les mêmes sinon false
bool Saison::operator==(unsigned int numSaison)
{
	if (numSaison_ == numSaison) {
		return true;
	}
	return false;
}

//! opérateur qui compare 1 numereo de saison et 1 saison (ordre inversé de l'operateur precedent)
//! \param numSaison: numero de la saison à enlever
//! \param Saison: la saison a comparer avec le numero
//! \ return saison == numsaison, appel l'operateur == de classe saison
bool operator==(unsigned int numSaison, Saison saison) {
	return(saison == numSaison);
}

//! opérateur qui affiche une saison
//! \param os: stream dans lequel afficher
//! \param saison: la saison à afficher
//! \return os: ostream pour appel en casacde
std::ostream& operator<<(std::ostream& os, const Saison& saison)
{
	os << "\t" << "Saison" << " " << "0" << saison.numSaison_ << ":" << " " << saison.episodes_.size() << "/" << saison.nbEpisodesmax_;
	if (saison.episodes_.size() == saison.nbEpisodesmax_) {
		os << "(Terminée)" << endl;
	}
	else {
		os << "(En cours)" << endl;
	}
	for (int i = 0; i < saison.episodes_.size(); i++)
		os << "\t"<<"\t"<< *saison.episodes_[i] << endl;
   return os;
}

//! opérateur qui lit une saison
//! \param is: stream duquel lire
//! \param saison: saison à lire
//! \return is: istream pour appel en cascade
std::istream& operator>>(std::istream& is, Saison& saison)
{
	is >> saison.numSaison_ >> saison.nbEpisodesmax_;
	return  is;
}

//! méthode qui retourne le numero de la saison
//! \return numSaison_: numero de la saison
unsigned int Saison::getNumSaison() const
{
	return numSaison_;
}

//! méthode qui retourne le nombre d'episodes de la saison
//! \return la size du vecteur episodes_
size_t Saison::getNbEpisodes() const
{
	return(episodes_.size());
}

//! \ methode qui trouve l'index d'un episode
//! \ param numEpisode: numero de l'episode a rechercher
//! \ return index si trouvé sinon -1
size_t Saison::trouverIndexEpisode(unsigned int numEpisode)
{
	for (int i = 0; i < episodes_.size(); i++) {
		if (episodes_[i]->getNumEpisode() == numEpisode) {
			return i;
		}
	}
	return EPISODE_INEXSISTANTE;
}