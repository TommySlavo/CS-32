#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <sstream>
#include <cstring>
#include <cctype>
#include <iostream>
#include <fstream>
using namespace std;

MovieDatabase::MovieDatabase()
{
    // Replace this line with correct code.
}

MovieDatabase::~MovieDatabase() {
    for (int i = 0; i < m_movies.size(); i++) {
        delete m_movies[i];
    }
}

bool MovieDatabase::load(const string& filename)
{
    
    ifstream inputfile(filename);
    if(inputfile) {
        std::string id, name, year, line, rating; // holding values to be inputted
        std::vector<std::string> theDirectors, theActors, theGenres; // holding vectors
        float new_rating = -1.0;
        int read = 1; // keeps track of line
        
        while (getline(inputfile, line)) {
            if (read == 1) {
                id = line;
                read++;
                continue;
            }
            if (read == 2) {
                name = line;
                read++;
                continue;
            }
            if (read == 3) {
                year = line;
                read++;
                continue;
            }
            if (read == 4) {
                int i = 0;
                std::string director;
                while (i < line.size()) { // makes sure directors are separated 
                    char c = line[i];
                    if (c == ',') {
                        theDirectors.push_back(director);
                        director = "";
                    }
                    else {
                        director += c;
                    }
                    i++;
                }
                theDirectors.push_back(director);
                read++;
                continue;
            }
            if (read == 5) {
                int i = 0;
                std::string actor;
                while (i < line.size()) {
                    char c = line[i];
                    if (c == ',') {
                        theActors.push_back(actor);
                        actor = "";
                    }
                    else {
                        actor = actor + c;
                    }
                    i++;
                }
                theActors.push_back(actor);
                read++;
                continue;
            }
            if (read == 6) {
                int i = 0;
                std::string genre;
                while (i < line.size()) {
                    char c = line[i];
                    if (c == ',') {
                        theGenres.push_back(genre);
                        genre = "";
                    }
                    else {
                        genre = genre + c;
                    }
                    i++;
                }
                theGenres.push_back(genre);
                read++;
                continue;
            }
            if (read == 7) {
                rating = line;
                read++;
                new_rating = stof(rating);
                continue;
            }
            if (line.empty() == true) {
                read = 1;
                Movie* m = new Movie(id, name, year, theDirectors, theActors, theGenres, new_rating); // creates new movie
                m_movies.push_back(m); // pushes back movie to be deleted quikly
                m_id_to_movie.insert(toLower(id), m); // inputs are inputted to not be case sensitive
                for (int i =0; i < theDirectors.size(); i++) {
                    m_director_to_movies.insert(toLower(theDirectors[i]), m);
                }
                for (int i = 0; i < theActors.size(); i++) {
                    m_actor_to_movies.insert(toLower(theActors[i]), m);
                }
                for (int i = 0; i < theGenres.size(); i++) {
                    m_genre_to_movies.insert(toLower(theGenres[i]), m);
                }
                theDirectors.clear(); // resetting values
                theActors.clear();
                theGenres.clear();
                new_rating = -1.0;
                rating = "";
                id = "";
                name = "";
                year = "";
            }
        }
        if (name != "") { // in the case that the last line is not empty
            Movie* m = new Movie(id, name, year, theDirectors, theActors, theGenres, new_rating);
            m_movies.push_back(m);
            m_id_to_movie.insert(toLower(id), m);
            for (int i = 0; i < theDirectors.size(); i++) {
                m_director_to_movies.insert(toLower(theDirectors[i]), m);
            }
            for (int i = 0; i < theActors.size(); i++) {
                m_actor_to_movies.insert(toLower(theActors[i]), m);
            }
            for (int i = 0; i < theGenres.size(); i++) {
                m_genre_to_movies.insert(toLower(theGenres[i]), m);
            }

            theDirectors.clear();
            theActors.clear();
            theGenres.clear();
            rating = -1.0;
            id = "";
            name = "";
            year = "";
        }
        
        return true;
    }
    return false;  // Replace this line with correct code.
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    std::string lowerId = toLower(id);
    TreeMultimap<std::string, Movie*>::Iterator it = m_id_to_movie.find(lowerId);
    if (it.is_valid()) {
        return(it.get_value());
    }
    
    return(nullptr);
}

std::vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    std::string lowerDirector = toLower(director);
    std::vector<Movie*> movies_to_directors;
    TreeMultimap<std::string, Movie*>::Iterator it = m_director_to_movies.find(lowerDirector);
    if (it.is_valid()) {
        while (it.is_valid()) { // loops through to get all the movies
            movies_to_directors.push_back(it.get_value());
            it.advance();
        }
    }
    return(movies_to_directors);
}

std::vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    std::string lowerActor = toLower(actor);
    std::vector<Movie*> movies_to_actors;
    TreeMultimap<std::string, Movie*>::Iterator it = m_actor_to_movies.find(lowerActor);
    
    if (it.is_valid()) {
        while (it.is_valid()) {
            movies_to_actors.push_back(it.get_value());
            it.advance();
        }
    }
    
    return(movies_to_actors);
}

std::vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    std::string lowerGenre = toLower(genre);
    std::vector<Movie*> movies_to_genres;
    TreeMultimap<std::string, Movie*>::Iterator it = m_genre_to_movies.find(lowerGenre);
    
    if (it.is_valid()) {
        while (it.is_valid()) {
            movies_to_genres.push_back(it.get_value());
            it.advance();
        }
    }
    
    return(movies_to_genres);
}

std::string MovieDatabase::toLower(std::string s) const { // converts strings to lowercase
    std::string lower = "";
    for (int i = 0; i < s.size(); i++) {
        char c = s[i];
        lower += tolower(c);
    }
    return(lower);
}



