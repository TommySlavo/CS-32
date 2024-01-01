#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"

#include <unordered_set>
#include <string>

#include <algorithm>
#include <vector>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database) : m_user_database(&user_database), m_movie_database(&movie_database)
{

}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    if (movie_count <= 0) {
        return(vector<MovieAndRank>());
    }
    User* u = m_user_database->get_user_from_email(user_email); // gets all users
    if (u == nullptr) {
        return vector<MovieAndRank>();
    }
    std::vector<std::string> movies = u->get_watch_history();
    
    std::unordered_map<Movie*, int> movie_to_compatability_score; // creates unordered map to relate movie pointer to combatability score
   
    
    for (int i = 0; i < movies.size(); i++) { // loops through all watched movies
        
        Movie* m = m_movie_database->get_movie_from_id(movies[i]); // gets all movies
        std::vector<std::string> genresOfMovie = m->get_genres();
        std::vector<std::string> actorsOfMovie = m->get_actors();
        std::vector<std::string> directorsOfMovie = m->get_directors();
        
        for (int j = 0; j < genresOfMovie.size(); j++) { // loops through all genres
            std::vector<Movie*> moviesOfGenre = m_movie_database->get_movies_with_genre(genresOfMovie[j]);
            for (int k = 0; k < moviesOfGenre.size(); k++) {
                movie_to_compatability_score[moviesOfGenre.at(k)] += 1; // maps compatability score if a movie shares same genre
                
            }
        }
        for (int j = 0; j < actorsOfMovie.size(); j++) { // loops through all actors
            std::vector<Movie*> moviesOfActor = m_movie_database->get_movies_with_actor(actorsOfMovie[j]);
            for (int k = 0; k < moviesOfActor.size(); k++) {
                movie_to_compatability_score[moviesOfActor.at(k)] += 30; // maps compatability score if a movie shares same actor
            }
        }
        for (int j = 0; j < directorsOfMovie.size(); j++) { // loops through all directors
            std::vector<Movie*> moviesOfDirector = m_movie_database->get_movies_with_director(directorsOfMovie[j]);
            for (int k = 0; k < moviesOfDirector.size(); k++) {
                movie_to_compatability_score[moviesOfDirector.at(k)] += 20; // maps compatability score if a movie shares same director
            }
        }
    }
    
    
    for (int i = 0; i < movies.size(); i++) { // get rid of duplicates before having to convert to struct
        movie_to_compatability_score.erase(m_movie_database->get_movie_from_id(movies[i]));
    }
    std::unordered_map<Movie*, int>::iterator it;
    std::vector<MovieRating> movie_ratings; // need new struct to properly compare movies
    for (it = movie_to_compatability_score.begin(); it != movie_to_compatability_score.end(); it++) {
        Movie* m = it->first;
        int compatability_score = it->second;
        MovieRating r = MovieRating(m->get_rating(), m->get_title(), m->get_id(), compatability_score);
        movie_ratings.push_back(r);
    }
    
    sort(movie_ratings.begin(), movie_ratings.end(), compare); // call sort function to compare movies in new struct
    
    std::vector<MovieAndRank> movie_and_rank;
    for (int i = 0; i < movie_count; i++) {
        MovieAndRank m = MovieAndRank(movie_ratings[i].m_id, movie_ratings[i].compatability_score);
        movie_and_rank.push_back(m);
    }
    
    
    return(movie_and_rank);
}

bool Recommender::compare(const MovieRating m1, const MovieRating m2) {
    if(m1.compatability_score > m2.compatability_score) { // compare compatability first
        return(true);
    }
    else if (m1.compatability_score == m2.compatability_score) {
        if (m1.rating > m2.rating) { // then compare ratings
            return(true);
        }
        else if (m1.rating == m2.rating) {
            if (m1.name < m2.name) { // then compare names
                return(true);
            }
        }
        
    }
    
    return(false);
}



