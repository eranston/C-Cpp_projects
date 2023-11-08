
#include "RecommenderSystem.h"
#include <algorithm>
#include <numeric>
#include <math.h>

sp_movie RecommenderSystem::add_movie(const std::string& name,int year,
                   const std::vector<double>& features)
{
    sp_movie movie = std::make_shared<Movie>(Movie(name,year));
    name_year_database[std::make_pair(name , year)] = movie;
    data_base[movie] = features;
    return movie;
}


rank_map normalize_rate(const RSUser& user)
{
    rank_map user_ranks = user.get_ranks();
    int counter = 0;
    double sum = 0;
    for(auto i: user_ranks)
    {
        counter ++;
        sum += i.second;
    }
    double normelize_num = sum / counter;
    for(auto i: user_ranks)
    {
        user_ranks[i.first] -= normelize_num ;
    }
    return user_ranks;
}
std::vector<double> multiply(const std::vector<double> vec , double k)
{
    std::vector<double> temp_vec = vec;
    for( size_t i = 0 ; i< vec.size() ; i++)
    {
        temp_vec[i] *= k;
    }
    return temp_vec;
}


std::vector<double> fev_vector(rank_map norm_rate , RecommenderSystem& rs)
{
   std::vector<double> final_vec;
   bool flag = true;
   for(auto it : norm_rate)
   {
       if(flag)
       {
           final_vec = multiply(rs.data_base[it.first], it.second);
           flag = false;
       }
       else
       {
           auto temp_vec= multiply(rs.data_base[it.first] ,
                                   it.second);
           for(size_t i = 0 ; i<temp_vec.size() ; i++)
           {
               final_vec[i] += temp_vec[i];
           }
       }
   }
   return final_vec;

}



double calculate_norm(const std::vector<double> vec)
{

    double sum = 0;
    for(size_t i =0 ; i< vec.size() ; i++)
    {
        sum += vec[i] * vec[i];
    }
    return sqrt(sum);
}


sp_movie RecommenderSystem::recommend_by_content(const RSUser& user )
{
    std::map<sp_movie , double> rates;
    rank_map norm_rate = normalize_rate(user);
    auto fevourite_vec = fev_vector(norm_rate ,*this);
    for(auto movie : data_base)
    {
        auto pointer = user.get_ranks().find(movie.first);
        if(pointer == user.get_ranks().end())
        {
            double inner_rate= std::inner_product(movie.second.begin(),
              movie.second.end() , fevourite_vec.begin() , 0);
            rates[movie.first] = inner_rate /
                (calculate_norm(data_base[movie.first])
                    * calculate_norm(fevourite_vec));
        }
    }
    sp_movie best_match_movie = rates.begin()->first;
    double max_match_rate = rates.begin()->second;
    for(auto i : rates)
    {
        if(max_match_rate < i.second)
        {
            best_match_movie = i.first;
            max_match_rate = i.second;
        }
    }
    return best_match_movie;
}

sp_movie RecommenderSystem::recommend_by_cf(const RSUser& user, int k)
{
    sp_movie suggested_movie = nullptr;
    auto user_ranks = user.get_ranks();
    double max = 0;
    bool first = true;
    for(auto it : data_base)
    {
        if(user_ranks.find(it.first) == user_ranks.end() )
        {
            if(first)
            {
                max = predict_movie_score(user ,it.first , k);;
                suggested_movie = it.first;
                first = false;
            }
            double suggested_rate = predict_movie_score(user ,
                                                        it.first , k);

            if(max < suggested_rate)
            {
                max = suggested_rate;
                suggested_movie = it.first;
            }
        }
    }
    return suggested_movie;
}

double multiply_vectors(const std::vector<double>& vec1 ,
                        const std::vector<double>& vec2)
{
    double sum = 0 ;
    for (size_t i =0; i<vec1.size() ; i++)
    {
        sum += vec1[i] * vec2[i];
    }
    return sum;
}

std::pair<sp_movie , double> find_max_in_map(std::map<sp_movie , double>& map)
{

    std::pair<sp_movie , double> max;
    for(auto it : map)
    {
        if(max.second < it.second)
        {
            max = it;
        }
    }
    return max;

}

double RecommenderSystem::predict_movie_score(const RSUser &user,
                                              const sp_movie &movie, int k)
{
   auto target_movie_feature = (data_base.find(movie))->second;
   std::map< sp_movie ,double> movie_simalrity;
   for(auto it : user.get_ranks())
   {
       auto temp_feature = data_base[it.first];
       double vec_mult_res = multiply_vectors(temp_feature ,
                                              target_movie_feature);
       double norm_mult_res = calculate_norm(temp_feature)
               * calculate_norm(target_movie_feature);
       double result = vec_mult_res/norm_mult_res;
       movie_simalrity[it.first]=result;
   }
   double upper_sum = 0;
   double lower_sum = 0;
   for(int i = 0 ; i<k ; i++)
   {
       sp_movie current_movie = find_max_in_map(movie_simalrity).first;
       double movie_rate = user.get_ranks()[current_movie];
       upper_sum += movie_simalrity[current_movie]* movie_rate;
       lower_sum += movie_simalrity[current_movie];
       movie_simalrity.erase(current_movie);
   }
    return upper_sum/lower_sum;
}

sp_movie RecommenderSystem::get_movie(const std::string &name, int year) const
{
    auto pair = std::make_pair(name , year);
    auto movie_iter= name_year_database.find(pair);
    return movie_iter->second;
}

std::ostream& operator<<(std::ostream& os , const RecommenderSystem& r_s)
{
    std::vector<Movie> temp_vec;
    for(auto it : r_s.data_base)
    {
        os<<it.first;
    }
    return os;
}

