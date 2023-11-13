/*
* spell_checker.hpp
* Written by : Lana Cossettini (c3436542)
* Modified : 29/10/2023
*
* The class represents a simple spell checker that provides suggestions for incorrectly spelled words.
* This file is used in conjunction with Assignment 3 for SENG1120.
*/

#include "spell_checker.h"

SpellChecker::SpellChecker() 
{

}

SpellChecker::~SpellChecker() 
{

}

// adds new word to the dictionary
void SpellChecker::add_word(const std::string& word) {
    Word newWord(word);
    dictionary.insert(newWord);
}

// removes word from the dictionary
void SpellChecker::remove_word(const std::string& word) {
    dictionary.remove(word);
}

// checks spelling of given word
void SpellChecker::spell_check(const std::string& word) const {
    if (spelled_correctly(word)) {
        std::cout << word << " is spelled correctly." << std::endl;
    } else {
        std::vector<std::string> suggestions = similar_words(word);
        std::cout << word << " is not spelled correctly. ";
        if (!suggestions.empty()) {
            std::cout << "Here is a list of suggestions:" << std::endl;
            for (const auto& suggestion : suggestions) {
                std::cout << suggestion << std::endl; //prints suggested words
            }
        } else {
            std::cout << "There are no suggestions." << std::endl;
        }
    }
}

// checks if word is spelled correctly by finding it in the dictionary
bool SpellChecker::spelled_correctly(const std::string& word) const {
    Word searchWord(word);
    return dictionary.contains(searchWord.get_key());
}

std::vector<std::string> SpellChecker::similar_words(const std::string& word) const {
    std::vector<std::string> words;
    std::string clone = word; // Make a copy

    // Check swaps
    for (int i = 1; i < (int)clone.length(); i++) {
        std::swap(clone[i - 1], clone[i]);
        if (spelled_correctly(clone)) {
            words.push_back(clone); 
        }
        std::swap(clone[i - 1], clone[i]); // Put the word back as before
    }

    // Check one-letter replacements
    for (int i = 0; i < (int)clone.length(); i++) {
        char orig = clone[i];
        // Use ASCII codes for letters
        for (int j = 97; j < 123; j++) {
            clone[i] = j;
            if (spelled_correctly(clone)) {
                words.push_back(clone); 
            }
        }
        // Put the word back as before
        clone[i] = orig;
    }

    return words;
}

// print content of the dictionary
std::ostream& SpellChecker::print(std::ostream& os) const {
    return dictionary.print(os);
}

// print the spell checker
std::ostream& operator<<(std::ostream& os, const SpellChecker& sc) {
    return sc.print(os);
}
