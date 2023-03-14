//
// Created on 2/20/2022.
//

// don't change those includes


#include "RSUser.h"
#include "RecommenderSystem.h"
#include <algorithm>

// implement your cpp code here

std::string RSUser::get_name() const
{
    return _user_name;
}


RSUser::RSUser(const std::string& name , rank_map& user_rank_map ,
       rec_sp& recommander_system)
{
    _user_name = name;
    _user_rank_map = user_rank_map;
    _recommender_system = recommander_system;

}

void RSUser::add_movie_to_rs(const std::string &name, int year,
                     const std::vector<double> &features,
                     double rate)
{
    auto movie= _recommender_system->add_movie(name , year , features);
    _user_rank_map[movie] = rate;
}

sp_movie RSUser::get_recommendation_by_content() const
{
    sp_movie recommanded_movie =
            _recommender_system->recommend_by_content(*this);

    return recommanded_movie;
}

sp_movie RSUser::get_recommendation_by_cf(int k) const
{
   sp_movie recommanded_movie =
           _recommender_system->recommend_by_cf(*this , k);

   return recommanded_movie;
}

double RSUser::get_prediction_score_for_movie(const std::string& name,
                                              int year, int k) const
{
    sp_movie searched_movie = _recommender_system->get_movie(name, year);
    double p_score = _recommender_system->predict_movie_score(*this ,
                                                  searched_movie, k);
    return p_score;
}

std::ostream& operator<<(std::ostream& os , const RSUser& user)
{
    os << "name: " << user.get_name() << "\n";
    os << *(user._recommender_system) << std::endl;
    return os;
}