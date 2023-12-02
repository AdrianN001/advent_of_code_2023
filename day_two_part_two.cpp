#include <iostream>
#include <fstream>
#include <string>

#include <sstream>
#include <vector>

std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

enum class Color{
    RED,
    GREEN,
    BLUE,
};
struct revealed_cubes{
    int amount;
    Color color;

};

struct Set{
    std::vector<revealed_cubes> moves;
};

struct highest_case{
    int red;
    int green;
    int blue;
    int power(){
        return red * green * blue;
    }
};


class Game{
public:
    int game_id;
    std::vector<Set> sets;

    Game(int id, std::string sets_string){
        std::vector<std::string> sets = split(sets_string, "; ");
        
        std::vector<Set> sets_parsed;

        for (auto set: sets){
            std::vector<std::string> moves = split(set, ", ");

            std::vector<revealed_cubes> moves_parsed;
            for (auto move: moves){
                std::vector<std::string> parts = split(move, " ");
                Color color;

                if (parts[1] == "blue"){
                    color = Color::BLUE;
                }else if (parts[1] == "red"){
                    color = Color::RED;
                }else{
                    color = Color::GREEN;
                }
                int amount = std::stoi(parts[0]);
                revealed_cubes cubes = {amount, color};
                moves_parsed.push_back(cubes);
            }
            
            Set new_set = {moves_parsed};
            sets_parsed.push_back(new_set);
        }
        this->sets = sets_parsed;
        this->game_id = id;
    }

    highest_case highest_possible(){

        int highest_red = 0;
        int highest_blue = 0;
        int highest_green = 0;

        for (auto set: sets){
            for (auto move: set.moves){
                
                if(move.color == Color::BLUE && move.amount > highest_blue){
                    highest_blue = move.amount;
                }
                if(move.color == Color::RED && move.amount > highest_red){
                    highest_red = move.amount;
                }
                if(move.color == Color::GREEN && move.amount > highest_green){
                    highest_green = move.amount;
                }
            }
        }
        return {highest_red, highest_green, highest_blue};
    }

};





int main(){
    std::ifstream input_file("./input/day_two.txt");
    int sum = 0;

    for( std::string line; std::getline( input_file, line ); ){
        int divider = line.find_first_of(":");
        std::vector<std::string> parts = split(line, ":");
        std::string sets = parts[1].substr(1);
        
        int space_before_number = parts[0].find_first_of(" ") + 1;

        std::string number_in_str = parts[0].substr(space_before_number);

        

        Game current_game(std::stoi(number_in_str), sets);
        int highest_power_achievable = current_game.highest_possible().power();
        sum += highest_power_achievable;
        
    }

    std::cout << "The answer is: [[ " << sum << " ]]" << std::endl;


    return 0;
}