#include "GestionnaireSaisons.h"

// To do
GestionnaireSaisons::~GestionnaireSaisons()
{
	saisons_.clear();
}

// To do
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

// To do
GestionnaireSaisons& GestionnaireSaisons::operator-=(const unsigned int numSaison)
{
	int index = trouverIndexSaison(numSaison);
	if (index > -1) {
		saisons_.erase(saisons_.begin() + index);
	}
	return *this;
}

// To do
void GestionnaireSaisons::ajouterEpisode(const unsigned int numSaison,
                                         std::unique_ptr<Episode> episode)
{
	int index = trouverIndexSaison(numSaison);
	if (index > -1) {
		*saisons_[index] += move(episode);
	}
}

// To do
void GestionnaireSaisons::retirerEpisode(const unsigned int numSaison,
                                         const unsigned int numEpisode)
{
	int index = trouverIndexSaison(numSaison);
	if (index > -1) {
		*saisons_[index] -= numEpisode;
	}
}

/// To do
size_t GestionnaireSaisons::trouverIndexSaison(const unsigned int numSaison) const
{
    for(int i=0; i<saisons_.size();i++)
		if (saisons_[i]->getNumSaison() == numSaison) {
			return i;
		}
	return SAISON_INEXSISTANTE;
}

// To do
Saison* GestionnaireSaisons::getSaison(const unsigned int numSaison) const
{
	int index = trouverIndexSaison(numSaison);
	
	if (index>-1) {
		return saisons_[index].get();
		
	}
	return nullptr;

}

// To do
size_t GestionnaireSaisons::getNbSaisons() const
{
	return saisons_.size();
}
