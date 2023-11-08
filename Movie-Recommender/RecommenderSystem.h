//
// Created on 2/20/2022.
//

#ifndef SCHOOL_SOLUTION_RECOMMENDERSYSTEM_H
#define SCHOOL_SOLUTION_RECOMMENDERSYSTEM_H
#include "RSUser.h"
#include <map>
#include "Movie.h"


class RecommenderSystem
{

private:
    std::map<sp_movie , std::vector<double> > data_base ; // hold the movies
    // and thier features vectors
    std::map< std::pair<const std::string , int> ,
            sp_movie > name_year_database; // map that hold the name and year
            // of movie , and return the sp_movie of i



    friend std::vector<double> fev_vector(rank_map norm_rate ,
                                          RecommenderSystem& rs);


    friend double calculate_fev_rate(sp_movie movie , RecommenderSystem& rs
                                     , std::vector<double>& fev_vector );
public:

	//explicit RecommenderSystem()

    RecommenderSystem()
    {
    }
    /**
     * adds a new movie to the system
     * @param name name of movie
     * @param year year it was made
     * @param features features for movie
     * @return shared pointer for movie in system
     */
	sp_movie add_movie(const std::string& name,int year,
                       const std::vector<double>& features);


    /**
     * a function that calculates the movie with highest score
     * based on movie features
     * @param ranks user ranking to use for algorithm
     * @return shared pointer to movie in system
     */
	sp_movie recommend_by_content(const RSUser& user );

    /**
     * a function that calculates the movie with highest predicted score
     * based on ranking of other movies
     * @param ranks user ranking to use for algorithm
     * @param k
     * @return shared pointer to movie in system
     */
	sp_movie recommend_by_cf(const RSUser& user, int k);


    /**
     * Predict a user rating for a movie given argument using item cf
     * procedure with k most similar movies.
     * @param user_rankings: ranking to use
     * @param movie: movie to predict
     * @param k:
     * @return score based on algorithm as described in pdf
     */
	double predict_movie_score(const RSUser& user, const sp_movie &movie,
												  int k);

	/**
	 * gets a shared pointer to movie in system
	 * @param name name of movie
	 * @param year year movie was made
	 * @return shared pointer to movie in system
	 */
	sp_movie get_movie(const std::string &name, int year) const;

    /**
     * print all movies in the database of the recommand system
     * @param os
     * @param r_s
     * @return
     */
	friend std::ostream& operator<<(std::ostream& os ,
            const RecommenderSystem& r_s);


};


#endif //SCHOOL_SOLUTION_RECOMMENDERSYSTEM_H
