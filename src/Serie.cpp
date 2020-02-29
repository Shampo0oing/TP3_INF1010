//! implémentation de classe Serie
//! \author Samuel Lavallée et Anthelme Clisson
//! \date 29 fevrier 2020

#include "Serie.h"



//! \ constructeur par paramètre de la classe Auteur. 
//! \ param auteur: pointeur vers auteur de la serie.
Serie::Serie(Auteur* auteur): Media(auteur, Media::TypeMedia(1))
{
}

//! constructeur par parametres de la classe Serie
//! \param nom (nom de la serie), anneeDeSortie, genre (genre de la serie), pays, estRestreintParAge (oui/non), auteur( auteur de la serie)
Serie::Serie(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
             bool estRestreintParAge, Auteur* auteur): Media(nom, anneeDeSortie, genre, pays, estRestreintParAge, auteur, Media::TypeMedia(1))
{
}

//! constructeur par copie de classe Serie
//! \param serie: serie a copier
Serie::Serie(const Serie& serie): Media(serie.nom_, serie.anneeDeSortie_, serie.genre_, serie.pays_, serie.estRestreintParAge_, serie.auteur_, Media::TypeMedia(1))
{
	std::vector<std::unique_ptr<Saison>> vect;
	for (int i = 0; i < serie.saisons_.size(); i++) {
		vect.push_back(std::make_unique<Saison>(*serie.saisons_[i]));
	}


}



//! constructeur par parametres de la classe Film
//! \param nom (nom du film), anneeDeSortie, genre (genre du film), pays, estRestreintParAge (oui/non), auteur( auteur du film), duree (duree du film)
std::ostream& Serie::afficher(std::ostream& os) const
{

	

	Media::afficher(os);
	for (int i = 0; i < saisons_.size(); i++) {
		os << *saisons_[i];
	}


	return os;
}

//! méthode qui retourne une copie allouée dynamiquement de l'objet courant
//! \return un unique_ptr vers une copie de la serie
std::unique_ptr<Media> Serie::clone() const
{
	std::unique_ptr<Media> clone = std::make_unique<Media>(*this);

	return clone;
}

