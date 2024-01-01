#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED

#include <string>
#include <vector>
#include <set>
#include <unordered_map>

class UserDatabase;
class MovieDatabase;
class Movie;

struct MovieAndRank
{
    MovieAndRank(const std::string& id, int score)
     : movie_id(id), compatibility_score(score)
    {}
   

    std::string movie_id;
    int compatibility_score;
};

class Recommender
{
  public:
    Recommender(const UserDatabase& user_database,
                const MovieDatabase& movie_database);
    std::vector<MovieAndRank> recommend_movies(const std::string& user_email,
                                               int movie_count) const;

  private:
    
    const UserDatabase* m_user_database;
    const MovieDatabase* m_movie_database;
    
    struct MovieRating
    {
        MovieRating(const float movie_rating, const std::string movie_name, const std::string movie_id, int movie_compatability_score)  {
            rating = movie_rating;
            name = movie_name;
            m_id = movie_id;
            compatability_score = movie_compatability_score;
        }
        float rating;
        std::string name;
        std::string m_id;
        int compatability_score;
    };
    
    static bool compare(const MovieRating m1, const MovieRating m2);
};

#endif // RECOMMENDER_INCLUDED

