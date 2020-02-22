#include "Film.h"

Film::Film(Auteur* auteur): Media(auteur, Media::TypeMedia(0) )
{
}


Film::Film(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
           bool estRestreintParAge, Auteur* auteur, const std::string& duree): Media(nom, anneeDeSortie, genre, pays, estRestreintParAge, auteur, Media::TypeMedia(0)), duree_(duree)
{
}

// To do
std::ostream& Film::afficher(std::ostream& os) const
{
	Media::afficher(os);
	os << "\tDurée: " << duree_ << std::endl;

	return os;
}

// To do
std::istream& Film::lire(std::istream& is)
{
	Media::lire(is);
	is >> quoted(duree_);
	return is;
}

// To do
std::unique_ptr<Media> Film::clone() const
{
	std::unique_ptr<Film> clone = std::make_unique<Film>(*this);
	return clone;

}
