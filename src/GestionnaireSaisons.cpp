//! implémentation de classe GestionnaireSaisons
//! \author Samuel Lavallée et Anthelme Clisson
//! \date 29 fevrier 2020

#include "GestionnaireSaisons.h"

//! destructeur de classe GestionnaireSaisons 
GestionnaireSaisons::~GestionnaireSaisons()
{
	saisons_.clear();
}

//! opérateur qui ajoute une saison au gestionnairedeSaisons (qui est une serie (par heritage))
//! \param saison: unique ptr vers saison à ajouter
//! \return *this soit l'objet appelant pour appel en cascade
GestionnaireSaisons& GestionnaireSaisons::operator+=(std::unique_ptr<Saison> saison)
{
	if (saison) {
			int index = trouverIndexSaison(saison->getNumSaison());
			if (index > -1) {

				saisons_.erase(saisons_.begin() + index);
			}
			saisons_.push_back(move(saison));
			sort(saisons_.begin(), saisons_.end(), Saison::SortByNumSaison());
		}
	return *this;
	
}

//! opérateur enleve une saison du gestionnaire
//! \param numSaison: numero de la saison à enlever
//! \return *this soit l'objet appelant pour appel en cascade
GestionnaireSaisons& GestionnaireSaisons::operator-=(const unsigned int numSaison)
{
	int index = trouverIndexSaison(numSaison);
	if (index > -1) {
		saisons_.erase(saisons_.begin() + index);
	}
	return *this;
}

//! opérateur ajoute un episode à la saison 
//! \param numSaison: numSaison à laquelle ajouter l'épisode
//! \param episode: unique ptr vers l'episode à ajouter
void GestionnaireSaisons::ajouterEpisode(const unsigned int numSaison,
                                         std::unique_ptr<Episode> episode)
{
	int index = trouverIndexSaison(numSaison);
	if (index > -1) {
		*saisons_[index] += move(episode);
	}
}

//! opérateur enleve un episode du gestionnaire
//! \param numSaison: numero de la saison de laquelle enlever l'episode
//! \param numEpisode: numero de l'episode à enlever
void GestionnaireSaisons::retirerEpisode(const unsigned int numSaison,
                                         const unsigned int numEpisode)
{
	int index = trouverIndexSaison(numSaison);
	if (index > -1) {
		*saisons_[index] -= numEpisode;
	}
}

//! methode qui trouve l'index d'une saison 
//! \param numSaison: numero de la saison à trouver
//! \return l'index de la saion ou -1 si la saison n'existe pas
size_t GestionnaireSaisons::trouverIndexSaison(const unsigned int numSaison) const
{
    for(int i=0; i<saisons_.size();i++)
		if (saisons_[i]->getNumSaison() == numSaison) {
			return i;
		}
	return SAISON_INEXSISTANTE;
}

//! methode qui retourne un pointeur vers une saison
//! \param numSaison: numero de la saison à retourner
//! \return pointeur vers la saison si trouvée sinon nullptr
Saison* GestionnaireSaisons::getSaison(const unsigned int numSaison) const
{
	int index = trouverIndexSaison(numSaison);
	
	if (index>-1) {
		return saisons_[index].get();
		
	}
	return nullptr;

}

//! méthode qui retourne le nombre de saisons du gestionnaire
//! \return la size du vecteur saisons
size_t GestionnaireSaisons::getNbSaisons() const
{
	return saisons_.size();
}
