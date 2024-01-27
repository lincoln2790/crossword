#ifndef WORD_MAP_HPP
#define WORD_MAP_HPP

#include <iterator>
#include <cereal/archives/json.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <utility>
#include <string>
//#define RESOURCE_STR "./resources/"
#include "../include/const.hpp"
//#define NUM_CLUES 1000
//constexpr const char* NYT_CLUES_STR = RESOURCE_STR "nytcrossword.csv";

class word_map_t {
	public:

 	std::map<char,std::vector<std::pair<std::string, std::string>>> word_map;

    template<class Archive>
    void serialize(Archive & archive) {
        archive(word_map);
    }
};
namespace cereal {
    //template<class Archive, class T, class U>
    //inline void save(Archive& ar, std::pair<T, U> const& pair) {
        //ar(pair.first, pair.second);
    //}

    template<class Archive, class T>
    inline void save(Archive& ar, std::vector<T> const& vector) {
        ar(vector.size());
        for (auto const& element : vector)
            ar(element);
    }

    //template<class Archive, class T, class U>
    //inline void load(Archive& ar, std::pair<T, U>& pair) {
        //ar(pair.first, pair.second);
    //}

    template<class Archive, class T>
    inline void load(Archive& ar, std::vector<T>& vector) {
        size_t size;
        ar(size);
        vector.resize(size);
        for (auto& element : vector)
            ar(element);
    }
    template<class Archive>
    inline void save(Archive& ar, const std::pair<std::string, std::string>& pair) {
        ar(cereal::make_nvp("first", pair.first), cereal::make_nvp("second", pair.second));
    }

    template<class Archive>
    inline void load(Archive& ar, std::pair<std::string, std::string>& pair) {
        ar(cereal::make_nvp("first", pair.first), cereal::make_nvp("second", pair.second));
    }
}


#endif
