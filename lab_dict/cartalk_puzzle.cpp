/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ans;
    vector< string > vectorWords;
	ifstream words(word_list_fname);
	string word;
	if(words.is_open()) 
	{
    /* Reads a line from words into word until the file ends. */
   		while(getline(words, word)) 
        {
			if(word.length() == 5)
				vectorWords.push_back(word);
		}
	}
	for(auto & eachWord : vectorWords)
	{
		std:: string fst = eachWord.substr(1);
		std:: string scnd;
		scnd.append(eachWord.begin(),eachWord.begin()+1);
		scnd.append(fst.begin()+1,fst.end());
		if(d.homophones(eachWord, fst)&&d.homophones(eachWord, scnd)&&d.homophones(fst, scnd))
		{	
			std::tuple<std::string, std::string, std::string> answer;
			std::get<0>(answer) = eachWord; 
			std::get<1>(answer) = fst;
			std::get<2>(answer) = scnd;
			ans.push_back(answer);
		}			 
	}
    return ans;
}
