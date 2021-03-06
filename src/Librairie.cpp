//! implémentation de classe Librairie
//! \author Samuel Lavallée et Anthelme Clisson
//! \date 29 fevrier 2020

#include "Librairie.h"

using namespace std;

//! constructeur par copie de la classe Librairie
//! \param librairie: la libraire à copier
Librairie::Librairie(const Librairie& librairie)
{
	
	for (int i = 0; i < librairie.medias_.size(); i++)
		medias_.push_back(move(librairie.medias_[i]->clone()));
	
	
}

//! opérateur d'affectation de librairie
//! \param librairie: la librairie à copier
//! \return librairie affectée
Librairie& Librairie::operator=(const Librairie& librairie)
{
	if (&librairie != this) {
		for (int i = 0; i < librairie.medias_.size(); i++) {
			medias_.push_back(move(librairie.medias_[i]->clone()));
		}
	}


	return *this;
}

//! Destructeur de la classe Librairie
Librairie::~Librairie()
{
	medias_.clear();
}

//! Méthode qui recherche un film dans une librairie
//! \param nomFilm: nom du film à rechercher
//! \return un pointeur de film
Film* Librairie::chercherFilm(const std::string& nomFilm)
{
	Media* ptr = chercherMedia(nomFilm, Media::TypeMedia(0));

	if (ptr) {
		return(dynamic_cast<Film*>(ptr));
	}
	else {
		return nullptr;
	}

}

//! Méthode qui recherche une série dans une librairie
//! \param nomSerie: nom de la série recherchée
//! \return pointeur de série
Serie* Librairie::chercherSerie(const std::string& nomSerie) 
{
	Media* ptr = chercherMedia(nomSerie, Media::TypeMedia(1));

	if (ptr) {
		return(dynamic_cast<Serie*>(ptr));
	}
	else {
		return nullptr;
	}
}

//! Méthode qui ajoute la saison d'un série à une librairie
//! \param nomSerie: nom de la série a ajouter
//! \param saison: numéro de la saison a ajouter
void Librairie::ajouterSaison(const std::string& nomSerie, std::unique_ptr<Saison> saison)
{
	if (saison) {
		size_t index = trouverIndexMedia(nomSerie);
		Media::TypeMedia typeSerie = Media::TypeMedia(1);
		if (index != -1 && medias_[index]->getTypeMedia() == typeSerie) {
			auto serie = dynamic_cast<Serie*>(medias_[index].get());
			*serie += move(saison);
		}
	}



}

//! Méthode qui retire la saison d'une série dans la libraire
//! \param nomSerie: nom de la série
//! \param numSaison: numéro de la saison
void Librairie::retirerSaison(const std::string& nomSerie, unsigned int numSaison)
{
	size_t index = trouverIndexMedia(nomSerie);
	Media::TypeMedia typeSerie = Media::TypeMedia(1);
	if (index != -1 && medias_[index]->getTypeMedia() == typeSerie) {
		auto serie = dynamic_cast<Serie*>(medias_[index].get());
		*serie -= numSaison;
	}

}


//! Méthode qui ajoute l'épisode de la saison de la série dans la librairie
//! \param nomSerie: nom de la série
//! \param numSaison: numéro de la saison
//! \param episode: pointeur de l'épisode
void Librairie::ajouterEpisode(const std::string& nomSerie, unsigned int numSaison,
	std::unique_ptr<Episode> episode)
{
	if (episode) {
		size_t index = trouverIndexMedia(nomSerie);
		Media::TypeMedia typeSerie = Media::TypeMedia(1);
		if (index != -1 && medias_[index]->getTypeMedia() == typeSerie) {
			auto serie = dynamic_cast<Serie*>(medias_[index].get());
			serie->ajouterEpisode(numSaison, move(episode));
		}
	}

}

//! Méthode qui retire l'épisode de la saison de la série dans la librairie
//! \param nomSerie: nom de la série
//! \param numSaison: numéro de la saison
//! \param numEpisode: numéro de l'épisode
void Librairie::retirerEpisode(const std::string& nomSerie, unsigned int numSaison,
	unsigned int numEpisode)
{
	size_t index = trouverIndexMedia(nomSerie);
	Media::TypeMedia typeSerie = Media::TypeMedia(1);
	if (index !=-1 && medias_[index]->getTypeMedia() == typeSerie) {
		auto serie = dynamic_cast<Serie*>(medias_[index].get());
		serie->retirerEpisode(numSaison, numEpisode);
	}

}

//! Méthode qui charge les series à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un serie à un
//! auteur.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerMediasDepuisFichier(const std::string& nomFichier,
	GestionnaireAuteurs& gestionnaireAuteurs)
{
	fstream fichier(nomFichier);
	if (!fichier.is_open()) {
		cout << "Fichier introuvable.";
		return false;
	}
	string ligne;
	while (getline(fichier, ligne)) {
		lireLigneMedia(ligne, gestionnaireAuteurs);
	}
	return true;
}

//! Méthode qui charge les restrictions des series à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerRestrictionsDepuisFichiers(const std::string& nomFichier)
{
	std::ifstream fichier(nomFichier);
	if (fichier)
	{
		for (int i = 0; i < medias_.size(); i++)
			medias_[i]->supprimerPaysRestreints();

		std::string ligne;
		while (getline(fichier, ligne))
			if (!lireLigneRestrictions(ligne))
				return false;

		return true;
	}
	std::cerr << "Le fichier " << nomFichier
		<< " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
	return false;
}

//! Méthode qui retourn le nombre de Médias
//! \return la taille du vecteur medias_
size_t Librairie::getNbMedias() const
{
	return(medias_.size());
}

//! opérateur qui affiche chaque média de la librairie
//! \param os: stream dans lequel afficher 
//! \param librairie: librairie dont on veut afficher les médias
//! \return stream pour appel en casacde
std::ostream& operator<<(std::ostream& os, const Librairie& librairie)
{
	for (int i = 0; i < librairie.medias_.size(); i++)
		if (librairie.medias_[i]->getTypeMedia() == Media::TypeMedia(0)) {
			os << *librairie.medias_[i];
		}
	for (int i = 0; i < librairie.medias_.size(); i++)
		if (librairie.medias_[i]->getTypeMedia() == Media::TypeMedia(1))
			os << *librairie.medias_[i];
	return os;
}

//! Méthode qui trouve l'index du média recherché
//! \param nomMedia: nom du média
//! \return l'index du média recherché
size_t Librairie::trouverIndexMedia(const std::string& nomMedia) const
{
	for (int i = 0; i < medias_.size(); i++)
		if (medias_[i]->getNom() == nomMedia) {
			return i;
		}
	return MEDIA_INEXSISTANT;

}

//! Opérateur qui ajoute un media à la librairie
//! \param media: pointeur du media à ajouter
//! \return la librairie
Librairie& Librairie::operator+=(std::unique_ptr<Media> media)
{
	if (media) {
		medias_.push_back(move(media));
	}
	return *this;
}

//! Opérateur qui retire un média de la librairie
//! \param nomMedia: nom du média
//! \return la librairie
Librairie& Librairie::operator-=(const std::string& nomMedia)
{
	size_t index = trouverIndexMedia(nomMedia);
	if (index != -1) {
		medias_.erase(medias_.begin() + index);
		//medias_[index]->getAuteur()->setNbMedias(medias_[index]->getAuteur()->getNbMedias() - 1);
	}
	return *this;
}

//! Méthode qui recherche un média dans la librairie
//! \param nomMedia: nom du média
//! \param typeMedia: typeMedia
//! \return le media recherché
Media* Librairie::chercherMedia(const std::string& nomMedia, Media::TypeMedia typeMedia) 
{
	
	size_t index = trouverIndexMedia(nomMedia);
	if (index != -1 && medias_[index]->getTypeMedia() == typeMedia) {
		return(medias_[index].get());
	}
	return nullptr;
}

//! Méthode qui lit la ligne de restriction
//! \param ligne: ligne à lire
//! \return vrai si le media existe
bool Librairie::lireLigneRestrictions(const std::string& ligne)
{
	istringstream stream(ligne);
	int typeMedia;
	int paysValeurEnum;
	string nom;
	stream >> typeMedia >> quoted(nom);
	Media* media = chercherMedia(nom, to_enum<Media::TypeMedia>(typeMedia));
	if (media) {
		while (stream >> paysValeurEnum) {
			media->ajouterPaysRestreint(to_enum<Pays>(paysValeurEnum));
		}
		return true;
	}
	return false;
}

//! Méthode qui lit la ligne
bool Librairie::lireLigneMedia(const std::string& ligne, GestionnaireAuteurs& gestionnaireAuteurs)
{
	lireLigneMediaFunction fonctionLireligne[] = { &Librairie::lireLigneFilm,
												  &Librairie::lireLigneSerie,
												  &Librairie::lireLigneSaison,
												  &Librairie::lireLigneEpisode };
	std::istringstream stream(ligne);
	int typeMediaValeurEnum;

	if (stream >> typeMediaValeurEnum)
		return invoke(fonctionLireligne[typeMediaValeurEnum], *this, stream, gestionnaireAuteurs);

	return false;
}

//! Méthode qui retourne le vecteur média
//! \return le vecteur
const std::vector<std::unique_ptr<Media>>& Librairie::getMedias() const
{
	return medias_;
}

//! Méthode qui lit une ligne à partir d'un string
//! \param is: stream dans lequel on lit
//! \return true si la lecture s'est bien passé
bool Librairie::lireLigneEpisode(std::istream& is, GestionnaireAuteurs&)
{

	Episode episode;
	is >>  episode;
	unique_ptr<Episode> ptrEpisode = make_unique<Episode>(episode);
	string nomSerie;
	int numeroSaison;
	is >> quoted(nomSerie) >> numeroSaison;
	ajouterEpisode(nomSerie, numeroSaison, move(ptrEpisode));

	return true;
}

//! Méthode qui lit une ligne à partir d'un string
//! \param is: stram dant lequel on lit
//! \return true si la lecture s'est bien passé
bool Librairie::lireLigneSaison(std::istream& is, GestionnaireAuteurs&)
{
	Saison saison;
	is >> saison;
	unique_ptr<Saison> ptrSaison = make_unique<Saison>(saison);
	string nomSaison;
	is >> quoted(nomSaison);
	ajouterSaison(nomSaison, move(ptrSaison));
	return true;

}

//! Méthode qui lit une ligne à partir d'un string
//! \param is: stram dant lequel on lit
//! \return true si la lecture s'est bien passé
bool Librairie::lireLigneSerie(std::istream& is, GestionnaireAuteurs& gestionnaireAuteurs)
{

	string nomAuteur;
	is >> quoted(nomAuteur);
	Auteur* auteur = gestionnaireAuteurs.chercherAuteur(nomAuteur);
	if (auteur) {
		unique_ptr<Serie> serie = make_unique<Serie>(Serie(auteur));
		is >> *serie;
		if (!chercherMedia(serie->getNom(), Media::TypeMedia(1))) {
			*this += move(serie);
			auteur->setNbMedias(auteur->getNbMedias() + 1);
			return true;
		}
	}
	return false;
}

//! Méthode qui lit une ligne à partir d'un string
//! \param is: stram dant lequel on lit
//! \return true si la lecture s'est bien passé
bool Librairie::lireLigneFilm(std::istream& is, GestionnaireAuteurs& gestionnaireAuteurs)
{

	string nomAuteur;
	is >> quoted(nomAuteur);
	Auteur* auteur = gestionnaireAuteurs.chercherAuteur(nomAuteur);
	if (auteur) {
	
		unique_ptr < Media > film = make_unique<Film>(Film(auteur));
		is >> *film;
		if (!chercherMedia(film->getNom(), Media::TypeMedia(0))) {
			*this += move(film);
			auteur->setNbMedias(auteur->getNbMedias() + 1);
			return true;
		}
	}
	return false;





}

//! Méthode qui compte le nombre de films
//! \return le nombre de films
size_t Librairie::getNbFilms() const
{
	int nbFilms = 0;
	for (int i = 0; i < medias_.size(); i++)
		if (dynamic_cast<Film*>(medias_[i].get())) {
			nbFilms++;
		}
	return nbFilms;
}

//! Méthode qui compte le nombre de séries
//! \return le nombre de séries
size_t Librairie::getNbSeries() const
{
	int nbSeries = 0;
	for (int i = 0; i < medias_.size(); i++)
		if (dynamic_cast<Serie*>(medias_[i].get())) {
			nbSeries++;
		}
	return nbSeries;
}

//! Méthode qui compte le nombre de saison d'une séries
//! \param nomSerie: nom de la série
//! \return le nombre de saisons
size_t Librairie::getNbSaisons(const std::string& nomSerie) const
{
	size_t index = trouverIndexMedia(nomSerie);
	if (index!=-1) {
		if (auto serie = dynamic_cast<Serie*>(medias_[index].get())) {
			return serie->getNbSaisons();
		}
	}
	return 0;
}

//! Méthode qui compte le nombre d'épisodes de la saison d'une série
//! \param nomSerie: nom de la série
//! \param nomSaison: nom de la saison
//! \return le nombre d'episodes
size_t Librairie::getNbEpisodes(const std::string& nomSerie, const unsigned int numSaison) const
{
	size_t index = trouverIndexMedia(nomSerie);
	if (index != -1) {
		if (auto serie = dynamic_cast<Serie*>(medias_[index].get())) {
			if(serie->getSaison(numSaison)){
				return serie->getSaison(numSaison)->getNbEpisodes();
			}
		}
			
	}
	return 0;
}
