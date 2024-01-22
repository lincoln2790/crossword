#include <cereal/archives/json.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <utility>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>

#define RESOURCE_STR "./resources/"
#define NUM_CLUES 500

// Function to read CSV file into a vector of vectors
std::vector<std::vector<std::string>> readCSV(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::vector<std::string>> data;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string token;
            std::vector<std::string> row;

            while (std::getline(iss, token, ',')) {
                row.push_back(token);
            }

            data.push_back(row);
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }

    return data;
}

// Function to write vector of vectors to CSV file
void writeCSV(const std::vector<std::vector<std::string>>& data, const std::string& filename) {
    std::ofstream file(filename);

    if (file.is_open()) {
        for (const auto& row : data) {
            std::copy(row.begin(), row.end() - 1, std::ostream_iterator<std::string>(file, ","));
            file << row.back() << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}
constexpr const char* NYT_CLUES_STR = RESOURCE_STR "nytcrossword.csv";
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

int main(){
    std::string csv_file = "./resources/nytcrossword.csv";
    auto csv = readCSV(csv_file);

	std::srand(std::time(0));
    // Shuffle the rows
    std::random_shuffle(csv.begin(), csv.end());

    // Save the shuffled data back to the CSV file
    std::string shuffled_csv_file = "./resources/nytcrossword_shuffled.csv";
    writeCSV(csv, shuffled_csv_file);// Specify the path to your CSV file
	word_map_t word_map;
	for(char c = 'a'; c <= 'z' ; c++){
		word_map.word_map[c] = {} ;
	}
    // Open the CSV file using std::ifstream
    std::ifstream csvFile;
    csvFile.open(NYT_CLUES_STR);

       // Define a vector to store each row of data
    std::vector<std::vector<std::string>> data;

    // Read the CSV file line by line
    std::string line;

	int i = 0;
    while (getline(csvFile, line) && i < NUM_CLUES) {
        // Use a stringstream to split the line into individual values
        std::stringstream ss(line);
        std::vector<std::string> row;
		//std::cout << line << std::endl;
        // Read each value separated by commas
        std::string value;
        while (getline(ss, value, ',')) {
			//for (char& c : value) {
				//c = tolower(c);
			//}
            row.push_back(value);
        }

        // Add the row to the data vector
        data.push_back(row);
		i++;
    }

    // Close the CSV file
    csvFile.close();

	// Display the read data
	for (const auto& row : data) {
		//std::cout << uu?
		std::string word = row[0];
		std::string clue_str = row[1];

		for(int i = 0; i < word.length(); i++){
			std::pair<std::string, std::string> pair(word,clue_str);
			if(word_map.word_map[word[i]].empty() || word_map.word_map[word[i]].back() != pair){
				word_map.word_map[word[i]].push_back(pair);
			}
		}
	}
	//Accessing and printing the map contents
	//for (const auto& pair : word_map.word_map) {
		 //std::cout << pair.first << ": ";
		 //if(!pair.second.empty()){
			 //for (const auto& str : pair.second) {
				 //std::cout << str.first << "|" << str.second << "\n ";
			 //}
		 //}
		 //std::cout << std::endl;
		 //std::cout << std::endl;
		 //std::cout << std::endl;
	 //}
	{
        std::ofstream os(RESOURCE_STR "word_map.json");
        cereal::JSONOutputArchive archive(os);
        archive(word_map);
    }
	//{
        //word_map_t loadedObject;
        //std::ifstream is(RESOURCE_STR "word_map.json");
        //cereal::JSONInputArchive archive(is);
        //archive(loadedObject);
		//for (auto pair = loadedObject.word_map.begin(); pair != loadedObject.word_map.end(); ++pair){
		////for(auto i : loadedObject){
		////}
			//std::cout << pair->first <<std::endl;
			 //if(!pair->second.empty()){
				 //for (const auto& str : pair->second) {
					 //std::cout << str.first << "|" << str.second << "\n ";
				 //}
			 //}
			 //std::cout << std::endl;
			 //std::cout << std::endl;
			 //std::cout << std::endl;
		 //}
    //}
	return 0;
}
