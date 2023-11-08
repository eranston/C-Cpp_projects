//
// Created by 1eran on 04/06/2022.
//
#include "RecommenderSystemLoader.h"
#include <sstream>
#include <fstream>
#define MAX_RATE 10
#define MIN_RATE 1


/**
 *
 * read file and return istringstream with all the input from the file
 * @param file_path path to file
 * @return istringstream with all the file content in it
 */
std::istringstream read_file(const std::string file_path)
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


rec_sys_ptr RecommenderSystemLoader::create_rs_from_movies_file
        (const std::string &movies_file_path) noexcept (false)
{
    std::string line , word;
    double featue_rate;
    RecommenderSystem recomand_system;
    std::istringstream all_file = read_file(movies_file_path);
    while(std::getline(all_file , line))
    {
        std::istringstream iss(line);
        iss >> word;
        int pos = word.find("-");
        std::string movie_name = word.substr(0, pos);
        int year = std::stoi(word.substr(pos + 1,
                                         word.size() + 1 ));
        std::vector<double> features;
        while (iss >> featue_rate)
        {
            if(featue_rate < MIN_RATE || featue_rate > MAX_RATE)
            {
                throw std::runtime_error("movie rating not in range");
            }
            features.push_back(featue_rate);
        }
        recomand_system.add_movie(movie_name, year, features);
    }
    return std::make_unique<RecommenderSystem>(recomand_system);;
}

