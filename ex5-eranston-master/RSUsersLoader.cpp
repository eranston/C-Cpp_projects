//
// Created by 1eran on 04/06/2022.
//
#include "RSUsersLoader.h"
#include "RecommenderSystem.h"
#include <fstream>
#include <sstream>

#define MAX_RATE 10
#define MIN_RATE 1

std::istringstream read_file_user(const std::string file_path)
{
    std::ifstream myfile;
    myfile.open(file_path);
    if(!myfile.is_open())
    {
        throw std::runtime_error("file cannot be open");
    }
    myfile.seekg (0, std::ifstream::end);
    int length = myfile.tellg();
    myfile.seekg (0, std::ifstream::beg);
    char *buffer = new char [length];
    myfile.read(buffer , length);
    std::istringstream all_file(buffer);
    myfile.close();
    delete[] buffer;
    return all_file;
}

std::vector<std::pair<std::string , int>> first_row(std::istringstream& iss)
{
    std::string s;
    std::vector<std::pair<std::string , int>> movies ;
    while(iss >> s)
    {
        int pos = s.find("-");
        std::string movie_name = s.substr(0 , pos);
        int year = std::stoi(s.substr(pos+1 , s.size() +1));
        movies.push_back(std::make_pair(movie_name , year));
    }
    return movies;
}


RSUser make_user(std::istringstream& iss , rec_sp rs ,
                 std::vector<std::pair<std::string , int>>& movies)
{

    std::string name;
    std::string input;
    iss >> name;
    sp_movie movie_ptr;
    rank_map user_rank_map(0, sp_movie_hash, sp_movie_equal);
    int index = 0;
    while(iss >> input)
    {
        if (input != "NA")
        {
            auto movie_name = movies[index].first;
            auto movie_year = movies[index].second;
            sp_movie movie_ptr = rs->get_movie(movie_name ,
                                               movie_year);
            double double_input = std::stod(input);
            if (double_input < MIN_RATE || double_input > MAX_RATE)
            {
                throw std::runtime_error("out of number range");
            }
            auto pair = std::make_pair(movie_ptr , double_input);
            user_rank_map.insert(pair);
        }
        index++;
    }
    return RSUser(name ,user_rank_map , rs );
}





std::vector<RSUser> RSUsersLoader::create_users_from_file
(const std::string& users_file_path, rec_sp rs) noexcept(false)
{

    std::string line, word;
    std::vector<RSUser> all_users;

    bool first = true;

    std::vector<std::pair<std::string , int>> movies;
    std::istringstream all_file = read_file_user(users_file_path);

    while (std::getline(all_file , line))
    {
        std::istringstream iss(line);
        if(first)
        {
            movies = first_row(iss);
            first = false;
        }
        else
        {
            RSUser user = make_user(iss , rs , movies );
            all_users.push_back(user);
        }
    }


    return all_users;
}

