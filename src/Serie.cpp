#include "Serie.h"



// To do              Pointeur vers l'auteur du serie
Serie::Serie(Auteur* auteur): Media(auteur, Media::TypeMedia(1))
{
}

// To do
Serie::Serie(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
             bool estRestreintParAge, Auteur* auteur): Media(nom, anneeDeSortie, genre, pays, estRestreintParAge, auteur, Media::TypeMedia(1))
{
}

// To do
Serie::Serie(const Serie& serie): Media(serie.nom_, serie.anneeDeSortie_, serie.genre_, serie.pays_, serie.estRestreintParAge_, serie.auteur_, Media::TypeMedia(1))
{
	std::vector<std::unique_ptr<Saison>> vect;
	for (int i = 0; i < serie.saisons_.size(); i++) {
		vect.push_back(std::make_unique<Saison>(*serie.saisons_[i]));
	}


}



// To do
std::ostream& Serie::afficher(std::ostream& os) const
{

	

	Media::afficher(os);
	for (int i = 0; i < saisons_.size(); i++) {
		os << *saisons_[i];
	}


	return os;
}

// To do
std::unique_ptr<Media> Serie::clone() const
{
	std::unique_ptr<Media> clone = std::make_unique<Media>(*this);

	return clone;
}

