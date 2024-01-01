#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>
#include "treemm.h"

class Movie;

class MovieDatabase
{
  public:
    MovieDatabase();
    ~MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

  private:
    std::string toLower(std::string s) const ;
    TreeMultimap<std::string, Movie*> m_id_to_movie;
    TreeMultimap<std::string, Movie*> m_director_to_movies;
    TreeMultimap<std::string, Movie*> m_actor_to_movies;
    TreeMultimap<std::string, Movie*> m_genre_to_movies;
    std::vector<Movie*> m_movies;
};

#endif // MOVIEDATABASE_INCLUDED

