// Secure Coding in C++
// Challenge 02_05
// Secure a data parsing function, by Eduardo Corpeño

#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>
#include <cctype>

std::map<std::string, std::string> parseSettings(const std::string& input){
    std::map<std::string, std::string> result;
    std::istringstream ss(input);
    std::string pair;

    while (std::getline(ss, pair, ',')){
        size_t eq = pair.find('=');

        // Check for missing '='
        if(eq == std::string::npos){
            std::cerr << "Error: Missing '=' in pair: " << pair << std::endl;
            continue;
        }

        std::string key = pair.substr(0, eq);
        std::string value = pair.substr(eq + 1);

        // Check for empty key
        if(key.empty()){
            std::cerr << "Error: Empty key in pair: " << pair << std::endl;
            continue;
        }

        // Check for empty value
        if(value.empty()){
            std::cerr << "Error: Empty value in pair: " << pair << std::endl;
            continue;
        }

        // Check for spaces in key
        if(key.find(' ') != std::string::npos){
            std::cerr << "Error: Key contains spaces: " << key << std::endl;
            continue;
        }

        // Check for duplicate keys
        if(result.find(key) != result.end()){
            std::cerr << "Error: Duplicate key: " << key << std::endl;
            continue;
        }

        // Check if value is numeric
        bool isNumeric = !value.empty() && std::all_of(value.begin(), value.end(), ::isdigit);
        if(!isNumeric){
            std::cerr << "Error: Non-numeric value: " << value << std::endl;
            continue;
        }

        result[key] = value;
    }
    return result;
}

int main(){
    std::string rawInput;
    std::cout << "Enter settings (key=value,key=value,...): ";
    std::getline(std::cin, rawInput);

    auto settings = parseSettings(rawInput);

    std::cout << "Parsed settings:\n";
    for (const auto& [k, v] : settings)
        std::cout << k << ": " << v << "\n";

    std::cout << std::endl;
    return 0;
}
