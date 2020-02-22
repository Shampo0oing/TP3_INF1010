#include "Episode.h"

using namespace std;

Episode::Episode(): numEpisode_(01), nom_("Episode:01"), duree_("00:00 : 00")
{
}


Episode::Episode(unsigned int numEpisode, const std::string& nom, const std::string& duree): numEpisode_(numEpisode), nom_(nom), duree_(duree)
{
}


bool Episode::operator==(unsigned int numEpisode) {
	return(numEpisode_ == numEpisode ? true : false);
}

// To do
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

// To do
std::istream& operator>>(std::istream& is, Episode& episode)
{
	is >> episode.numEpisode_ >> quoted(episode.nom_) >> quoted(episode.duree_);

	return is;
}

// To do
unsigned int Episode::getNumEpisode() const
{
	return numEpisode_;
}

