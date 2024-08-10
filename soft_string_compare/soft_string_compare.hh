#ifndef SOFT_STRING_COMPARE_HH
#define SOFT_STRING_COMPARE_HH

#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <map>
#include <regex>


namespace ss_compare {

    typedef std::vector<                // index of character/byte of string 1
                std::vector<            // index of character/byte of string 2
                    bool>>              // if the characters/bytes match
        ComparisonMatrix;

    typedef std::vector<                // index of character/byte of string 1
                std::vector<            // index of character/byte of string 2
                    std::size_t>>       // length of substring so far
        SubstringMatrix;

    typedef std::tuple<
                std::size_t,            // index of starting character/byte of substring in string 1
                std::size_t,            // index of starting character/byte of substring in string 2
                std::size_t>            // length of substring
        SubstringTuple;

    typedef std::vector<                // index of character/byte of string 1
                std::vector<            // index of character/byte of string 2
                    std::tuple<
                        std::size_t,    // length of soft-substring so far
                        std::size_t,    // gap to last character match
                        bool>>>         // path to closest character match (horizontal/vertical)
        SoftSubstringMatrix;

    typedef std::tuple<
                std::size_t,
                std::size_t,
                bool>
        SoftSubstringTuple;


    /**
     * Pretty-print SubstringMatrix
     *
     * Time complexity = O(m * n)
     * Space complexity = O(m * n)
     * m = s1.length()
     * n = s2.length()
     */
    void print_substringmatrix(std::string s1, std::string s2, SubstringMatrix sm, std::ostream& printer = std::cout);


    /**
     * Pretty-print ComparisonMatrix
     *
     * Time complexity = O(m * n)
     * Space complexity = O(m * n)
     * m = s1.length()
     * n = s2.length()
     */
    void print_substringmatrix(std::string s1, std::string s2, ComparisonMatrix cm, std::ostream& printer = std::cout);


    /**
     * Pretty print SubstringTuple vector
     *
     * Time complexity = O(s * log(s))
     * Space complexity = O(s)
     * s = substrings.size()
     */
    void print_substringtuples(std::string s1, std::string s2, std::vector<SubstringTuple> substrings, std::ostream& printer = std::cout);


    /**
     * Return ComparisonMatrix of two strings
     * Size is m * n
     *
     * Time complexity = O(m * n)
     * Space complexity = O(m * n)
     * m = s1.length()
     * n = s2.length()
     */
    ComparisonMatrix calculate_comparisonmatrix(std::string s1, std::string s2);


    /**
     * Return SubstringMatrix of two strings
     * Size is (2 + m) * (2 + n)
     * Border is filled with zeros
     *
     * Time complexity = O(m * n)
     * Space complexity = O(m * n)
     * m = s1.length()
     * n = s2.length()
     */
    SubstringMatrix calculate_substringmatrix(std::string s1, std::string s2, ComparisonMatrix cm);


    /**
     * Return list of all common substrings of s1 and s2 as substring-tuples
     *
     * Time complexity = O(m * n)
     * Space complexity = O(m * n)
     * m = s1.length()
     * n = s2.length()
     */
    std::vector<SubstringTuple> calculate_substringtuples(std::string s1, std::string s2, SubstringMatrix sm, std::size_t minimum_length = 2);


    /**
     * Return words in a string
     * Word is defined by a regular expression
     *
     * Time complexity = O(n)
     * Space complexity = O(n)
     * n = s.length()
     */
    std::vector<std::string> words_in_string(std::string s, std::regex r = std::regex("[\\w\\d]+", std::regex_constants::ECMAScript));


    /**
     * Calculate frequency words in document
     */
    std::map<std::string, std::size_t> calculate_word_frequencies(std::vector<std::string> document);


    /**
     * A way to rate the similarity of two strings
     *
     * Time complexity = O(s)
     * Space complexity = O(s)
     * s = substrings.size()
     */
    double rate_strings_1(std::string s1, std::string s2, std::vector<SubstringTuple> substrings, double weight_power = 2.5);


    /**
     * A way to rate the similarity of two strings
     *
     * Time complexity = O(m * n)
     * Space complexity = O(m * n)
     * m = s1.length()
     * n = s2.length()
     */
    double rate_strings_2(std::string s1, std::string s2, std::map<std::string, std::size_t> word_frequencies);
}

#endif
