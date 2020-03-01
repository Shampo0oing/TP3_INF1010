//! implémentation de classe Media
//! \author Samuel Lavallée et Anthelme Clisson
//! \date 29 fevrier 2020

#include "Media.h"


	//! Fonction qui convertit le enum Media::Genre en string
	//! \param genre    Le genre à convertir
	//! \return         Le string qui représente le enum
namespace {
	const std::string& getGenreString(Media::Genre genre)
	{
		static const std::string NOMS_GENRES[] = { "Action",
												  "Aventure",
												  "Comedie",
												  "Horreur",
												  "Romance" };

		auto index = enum_value(genre);
		assert(valid_as_enum<Media::Genre>(index));
		return NOMS_GENRES[index];
	}

	//! Fonction qui convertit le enum Pays en string
	//! \param pays     Le pays à convertir
	//! \return         Le string qui représente le enum
	const std::string& getPaysString(Pays pays)
	{
		static const std::string NOMS_PAYS[] = { "Bresil",
												"Canada",
												"Chine",
												"EtatsUnis",
												"France",
												"Japon",
												"RoyaumeUni",
												"Russie",
												"Mexique" };
		auto index = enum_value(pays);
		assert(valid_as_enum<Pays>(index));
		return NOMS_PAYS[index];
	}
}



//! Constructeur par parametres de la classe Media
//! \param auteur: auteur dur media
//! \param typeMedia: type du media
Media::Media(Auteur* auteur, Media::TypeMedia typeMedia) :auteur_(auteur), typeMedia_(typeMedia), anneeDeSortie_(0), estRestreintParAge_(0), genre_(to_enum<Genre>(0)), pays_(to_enum<Pays>(0))
{

}

//! Constructeur par parametres de la classe Media
//! \param nom: nom dur media
//! \param anneeDeSortie: année de sortie du média
//! \param genre: genre du média
//! \param pays: pays d'origine du média
//! \param estResteintParAge: si oui ou non le média à une restriction d'age
//! \param auteur: auteur dur media
//! \param typeMedia: type du media
Media::Media(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
	bool estRestreintParAge, Auteur* auteur, Media::TypeMedia typeMedia) : nom_(nom), anneeDeSortie_(anneeDeSortie), genre_(genre), pays_(pays), estRestreintParAge_(estRestreintParAge)
	, auteur_(auteur), typeMedia_(typeMedia)
{
}

//! Constructeur par copie de la classe Media
//! \param serie: le média à copier
Media::Media(const Media& serie) :Media(serie.nom_, serie.anneeDeSortie_, serie.genre_, serie.pays_, serie.estRestreintParAge_, serie.auteur_, serie.typeMedia_)
{

	paysRestreints_ = serie.paysRestreints_;
}

//! Destructeur par default de la classe Media
Media::~Media()
{
	paysRestreints_.clear();
}

//! Méthode qui ajoute un pays restreints
//! \param pays: pays à ajouter
void Media::ajouterPaysRestreint(Pays pays)
{
	paysRestreints_.push_back(pays);


}

//! Méthode qui supprime les pays restreints
void Media::supprimerPaysRestreints()
{
	paysRestreints_.clear();
}

//! Méthode qui retourne si le média est restreint dans le pays
//! \param pays: le pays dont on vérifie la restriction
//! \return true si le média est restreint dans le pays, fals sinon
bool Media::estRestreintDansPays(Pays pays) const
{
	for (std::size_t i = 0; i < paysRestreints_.size(); i++)
	{
		if (paysRestreints_[i] == pays)
		{
			return true;
		}
	}
	return false;
}

//! Méthode qui retourne le vector de pays restreints par age
//! \return le vector de pays restreint par age
bool Media::estRestreintParAge() const
{
	return estRestreintParAge_;
}

//! Méthode qui affiche les informations du médias
//! \param os: stream dans lequel afficher
//! \return stream pour appel en cascade
std::ostream& Media::afficher(std::ostream& os) const
{
	os << nom_ << "\n\tDate de sortie: " << anneeDeSortie_
		<< "\n\tGenre: " << getGenreString(genre_) << "\n\tAuteur: " << auteur_->getNom()
		<< "\n\tPays: " << getPaysString(pays_)
		<< (paysRestreints_.size() == 0 ? "\n\tAucun pays restreint." : "\n\tPays restreints:");

	for (std::size_t i = 0; i < paysRestreints_.size(); i++)
	{
		os << "\n\t\t" << getPaysString(paysRestreints_[i]);
	}
	os << '\n';

	return os;
}


//! Opérateur qui utilise la fonction afficher
//! \param os: stream dans lequel afficher
//! \param media: média que l'on veut afficher
//! \return stream pour appel en cascade
std::ostream& operator<<(std::ostream& os, const Media& media)
{
	media.afficher(os);

	return os;
}

//! Méthode qui retourne le genre
//! \return le genre
Media::Genre Media::getGenre() const
{
	return genre_;
}

//! Méthode qui retourne le nom
//! \return le nom
const std::string& Media::getNom() const
{
	return nom_;
}

//! Méthode qui retourne le type de média
//! \return le type de média
Media::TypeMedia Media::getTypeMedia() const
{
	return typeMedia_;
}

//! Méthode qui lit et initialise les éléments de la classe médias
//! \param is: stream dans lequel on lit
//! \return stream pour appel en cascade
std::istream& Media::lire(std::istream& is)
{
	int genre, pays;
	is >> std::quoted(nom_) >> anneeDeSortie_ >> genre >> pays >> estRestreintParAge_;
	genre_ = to_enum<Media::Genre>(genre);
	pays_ = to_enum<Pays>(pays);

	

	return is;
};


//! Méthode qui utilise la méthode lire
//! \param is: stream dans lequel on lit
//! \return stream pour appel en cascade
std::istream& operator>>(std::istream& is, Media& media)
{
	media.lire(is);
	return is;
}

//! Méthode qui retourne une copie de l'objet courant
//! \return une copie de l'objet courant
std::unique_ptr<Media> Media::clone() const
{

	return (std::make_unique<Media>(*this));
}









