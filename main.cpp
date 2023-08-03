#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <vector>
#include <ctime>
#include <algorithm>
#include <sstream>

bool run;

    
/*
 * FEATURES TO ADD:
 *  - Consolidate the turn-system
 *  - Clean up code/split into files
 *  - Error checking for the files (AI) (words.txt)
 *  - Error checking on input (Does the word exist, does it only contain letters, etc.)
 *  - Hints/definitions of words
 *  - Allow Player 2 to guess the word right away
 *  - Have the hangman get drawn
 *  - Check lowercase/uppercase letters for player 2
 *      - (E.g. Word is: Foo and they type lowercase f --> Should be valid)
 */


int countLines(std::vector<std::string> words) {
    return words.size();
}
    
std::string getWord() {
    std::ifstream words_file;
    try {
        words_file.open("words.txt");
    }
    catch (...) {//words_file.fail()) {
        std::cout << "Error" << std::endl;
        run = false;
    }
        
    std::string line;

    std::vector<std::string> words;

    while (std::getline(words_file,line)) {
        words.push_back(line);
    }

    srand(time(NULL));

    int number_of_words = countLines(words);
    // std::cout << number_of_words << std::endl;

    std::string word = words.at(rand() % number_of_words);

    return word;
    
}

std::string runAI() {
    return (getWord());
}


void endGame() {
    std::cout << "Thank you for playing. Goodbye!" << std::endl;
    run = false;
}



std::string updateWord(std::string word, std::vector<int> characterLocations, char to_update) {
    char dummy;
    std::vector<char> word_vec (word.length(),dummy);

    for (int i = 0; i < word.length(); i++) {
        std::vector<int>::iterator found = std::find(characterLocations.begin(), characterLocations.end(), i);
        if(found != characterLocations.end()) { // if i is in the characterLocations vector
            word_vec[i] = to_update;
            characterLocations.erase(found);
        }
        else {
            word_vec[i] = word[i];
        }
    }
    

    std::string result(word_vec.begin(),word_vec.end()); // converts char vector to string

    return result;
}

bool has_only_alpha(std::string word) {
    char c;
    for (int i = 0; i < word.length(); i++) {
        c = word.at(i);

        if (! ( ( c >= 'a' && c <= 'z' ) ||
                    ( c >= 'A' && c <= 'Z') ) ) {
            return false;
        }
    }
    return true;
}

std::vector<int> findLocation(std::string sample, char findIt)
{
    std::vector<int> characterLocations;
    for(int i =0; i < sample.size(); i++)
        if(sample[i] == findIt)
            characterLocations.push_back(i);

    return characterLocations;
}

void toLower(std::string& word) {
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
}



int main() {
    std::cout << "Welcome to Hangman!" << std::endl;

    run = true;

    while (run) {

        std::string gameMode;

        std::cout << "Would you like to play against:\n 1) A friend\n 2) The computer?" << std::endl;
        std::cout << "Type 'quit' to end the game." << std::endl;

        std::cin >> gameMode;

        /* The commented code is used for creating a lower case string.

        std::locale loc;
        for (std::string::size_type i=0; i < str.length(); i++)
            std::cout << std::tolower(str[i],loc);
        */



        std::string hidden_word = "";
        std::string input;

        if (gameMode == "1") {
            bool isValidWord = false;

            std::cout << "=========PLAYER 1'S TURN=========" << std::endl;
            while (isValidWord == false) {

                std::cout << "Give me a word: ";
                std::cin >> input;
                isValidWord = has_only_alpha(input);
                if (isValidWord) {
                    for (int i = 0; i < 100; i++) { // clears the terminal
                        std::cout << "\n" << std::endl;
                    }
                    break;
                }
                std::cout << "Only letters are allowed in words." << std::endl;
            }

            for (int j = 0; j < input.length(); j++) {
                hidden_word += "_";
            }

            toLower(input);
   
            std::cout << "=========PLAYER 2'S TURN=========" << std::endl;

            bool game_over = false;

            int num_tries = input.length() + 1;

            std::cout << "The word that your friend gave was " << input.length() << " letters long." << std::endl;

            std::cout << "Updated Word: " << hidden_word << std::endl;

            while ((num_tries > 0) && (game_over == false)) {
                char letter;
                std::cout << "Number of tries left: " << num_tries << std::endl;
                std::cout << "Give me a letter you think is in the word: ";
                std::cin >> letter;
                
                
                std::stringstream stream;
                std::string str;

                stream << letter;
                stream >> str;

                toLower(str);
                            
                std::size_t found = input.find(letter);
                if (found != std::string::npos) {
                    std::cout << "That letter is in the word!" << std::endl;
                    std::vector<int> characterLocations = findLocation(input,letter);



                    hidden_word = updateWord(hidden_word, characterLocations, letter);
                    if (hidden_word == input) {
                        game_over = true;
                        break;
                    }
                    std::cout << "Updated Word: " << hidden_word << std::endl;



                }
                else {
                    std::cout << "That letter is not in the word." << std::endl;
                }

                num_tries--;
            }




            if (num_tries != 0) {
                std::cout << "Player 2 wins!" << std::endl;
            }
            else {
                std::cout << "Player 1 wins!" << std::endl;
            }
            std::cout << "The word you gave me was: " << input  << std::endl;
            run = false;
        }
        else if (gameMode == "2") {
           
            input = runAI();
            //std::cout << "word chosen by computer is: " << input << std::endl;
            for (int j = 0; j < input.length(); j++) {
                hidden_word += "_";
            }


            std::cout << "=========PLAYER 2'S TURN=========" << std::endl;

            bool game_over = false;

            int num_tries = input.length() + 1;
            while ((num_tries > 0) && (game_over == false)) {
                char letter;
                std::cout << "If you would like to guess the word, press 1." << std::endl;
                std::cout << "Number of tries left: " << num_tries << std::endl;
                std::cout << "Give me a letter you think is in the word: ";
                std::cin >> letter;
                
                if (letter == '1')
                {
                    std::string guess;
                    std::cout << "What is your guess?" << std::endl;
                    std::cin >> guess;
                    if (input == guess) {
                        std::cout << "You guessed the word right!" << std::endl;
                        num_tries = -1;
                    }

                }
                else {
                    std::size_t found = input.find(letter);
                    if (found != std::string::npos) {
                        std::cout << "That letter is in the word!" << std::endl;
                        std::vector<int> characterLocations = findLocation(input,letter);

                        for (int i = 0; i < characterLocations.size(); i++) {
                            std::cout << characterLocations[i] << std::endl;;
                        }

                        hidden_word = updateWord(hidden_word, characterLocations, letter);
                        if (hidden_word == input) {
                            game_over = true;
                            break;
                        }
                        std::cout << "Updated Word: " << hidden_word << std::endl;



                    }
                    else {
                        std::cout << "That letter is not in the word." << std::endl;
                    }

                    num_tries--;
                }
            }




            if (num_tries != 0) {
                std::cout << "You win!" << std::endl;
            }
            else {
                std::cout << "The computer wins!" << std::endl;
            }
            std::cout << "The word the computer gave was: " << input  << std::endl;
            run = false;
        }
        else if (gameMode == "quit") {
            run = false;
        }
        else {
            std::cout << "Please input only 1 or 2 or 'quit'." << std::endl;
        }

    }

    endGame();
    

    return 0;
}


