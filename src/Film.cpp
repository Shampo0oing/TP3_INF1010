//! implémentation de classe Film
//! \author Samuel Lavallée et Anthelme Clisson
//! \date 29 fevrier 2020

#include "Film.h"

//! constructeur par parametres de la classe Film
//! \param auteur: Auteur du film
Film::Film(Auteur* auteur): Media(auteur, Media::TypeMedia(0) )
{
}

//! constructeur par parametres de la classe Film
//! \param nom (nom du film), anneeDeSortie, genre (genre du film), pays, estRestreintParAge (oui/non), auteur( auteur du film), duree (duree du film)

Film::Film(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
           bool estRestreintParAge, Auteur* auteur, const std::string& duree): Media(nom, anneeDeSortie, genre, pays, estRestreintParAge, auteur, Media::TypeMedia(0)), duree_(duree)
{
}

//! opérateur qui affiche un film
//! \param os: stream dans lequel afficher 
//! \return stream pour appel en casacde
std::ostream& Film::afficher(std::ostream& os) const
{
	Media::afficher(os);
	os << "\tDurée: " << duree_ << std::endl;

	return os;
}

//! opérateur qui lit un film
//! \param istream duquel lire
//! \return istream pour appel en cascade
std::istream& Film::lire(std::istream& is)
{
	Media::lire(is);
	is >> quoted(duree_);
	return is;
}

//! méthode qui retourne une copie allouée dynamiquement de l'objet courant
//! \return un unique_ptr vers une copie du film
std::unique_ptr<Media> Film::clone() const
{
	std::unique_ptr<Film> clone = std::make_unique<Film>(*this);
	return clone;

}
