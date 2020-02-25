#include "Saison.h"
#include <iostream>

using namespace std;
//
Saison::Saison() : numSaison_(1), nbEpisodesmax_(0)
{
}

Saison::Saison(unsigned int numSaison, unsigned int nbEpisodemax): numSaison_(numSaison), nbEpisodesmax_(nbEpisodemax)
{
}


Saison::Saison(const Saison& saison)
{
	numSaison_ = saison.numSaison_; nbEpisodesmax_= saison.nbEpisodesmax_;
	vector<unique_ptr<Episode>> vect;
	for (int i = 0; i < saison.episodes_.size(); i++)
		vect.push_back(make_unique<Episode>(*episodes_[i]));


}

Saison::~Saison()
{
	episodes_.clear();
}

// To do
Saison& Saison::operator+=(std::unique_ptr<Episode> episode)
{
	
	if (episode) {
		int index = trouverIndexEpisode(episode->getNumEpisode());
		if (index > -1) {
			episodes_.erase(episodes_.begin() + index);
		}

		episodes_.push_back(move(episode));
		
		
		
	};

	sort(episodes_.begin(), episodes_.end(), Episode::SortByNumEpisode());
	return *this;
}

// To do
Saison& Saison::operator-=(unsigned int numEpisode)
{
	int index = trouverIndexEpisode(numEpisode);

	if (index >= 0) {
		episodes_.erase(episodes_.begin() + index);

	}
	return *this;
}

// To do
bool Saison::operator==(unsigned int numSaison)
{
	if (numSaison_ == numSaison) {
		return true;
	}
	return false;
}

bool operator==(unsigned int numSaison, Saison saison) {
	return(saison == numSaison);
}

// To do
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

// To do
std::istream& operator>>(std::istream& is, Saison& saison)
{
	is >> saison.numSaison_ >> saison.nbEpisodesmax_;
	return  is;
}

// To do
unsigned int Saison::getNumSaison() const
{
	return numSaison_;
}

// To do
size_t Saison::getNbEpisodes() const
{
	return(episodes_.size());
}

// To do
size_t Saison::trouverIndexEpisode(unsigned int numEpisode)
{
	for (int i = 0; i < episodes_.size(); i++) {
		if (episodes_[i]->getNumEpisode() == numEpisode) {
			return i;
		}
	}
	return -1;
}