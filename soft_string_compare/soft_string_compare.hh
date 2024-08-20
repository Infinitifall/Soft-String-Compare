#ifndef SOFT_STRING_COMPARE_HH
#define SOFT_STRING_COMPARE_HH

#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <set>
#include <map>
#include <regex>

// #include <boost/regex.hpp>
// namespace regex_lib = boost;
namespace regex_lib = std;


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

    typedef std::map<
                std::string,            // the word
                std::size_t>            // the frequency of the word
        WordFrequencies;

    typedef std::map<
                std::tuple<            // the strings being compared
                    std::string,        // the first string
                    std::string>,       // the second string
                double>                 // the rating
        RatingCache;


    /**
     * Pretty-print SubstringMatrix
     *
     * Time complexity = O(m * n)
     * Space complexity = O(m * n)
     * m = s1.length()
     * n = s2.length()
     */
    void print_substringmatrix(
        const std::string& s1, const std::string& s2,
        const SubstringMatrix& sm,
        std::ostream& printer = std::cout
    );


    /**
     * Pretty-print ComparisonMatrix
     *
     * Time complexity = O(m * n)
     * Space complexity = O(m * n)
     * m = s1.length()
     * n = s2.length()
     */
    void print_substringmatrix(
        const std::string& s1, const std::string& s2,
        const ComparisonMatrix& cm,
        std::ostream& printer = std::cout
    );


    /**
     * Pretty print SubstringTuple vector
     *
     * Time complexity = O(s * log(s))
     * Space complexity = O(s)
     * s = substrings.size()
     */
    void print_substringtuples(
        const std::string& s1, const std::string& s2,
        const std::vector<SubstringTuple>& substrings,
        std::ostream& printer = std::cout
    );


    /**
     * Return ComparisonMatrix of two strings
     * Size is m * n
     *
     * Time complexity = O(m * n)
     * Space complexity = O(m * n)
     * m = s1.length()
     * n = s2.length()
     */
    ComparisonMatrix calculate_comparisonmatrix(
        const std::string& s1, const std::string& s2
    );


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
    SubstringMatrix calculate_substringmatrix(
        const std::string& s1, const std::string& s2,
        const ComparisonMatrix& cm
    );


    /**
     * Return list of all common substrings of s1 and s2 as substring-tuples
     *
     * Time complexity = O(m * n)
     * Space complexity = O(m * n)
     * m = s1.length()
     * n = s2.length()
     */
    std::vector<SubstringTuple> calculate_substringtuples(
        const std::string& s1, const std::string& s2,
        const SubstringMatrix& sm,
        const std::size_t minimum_length = 2
    );


    const regex_lib::regex r_default ("[\\w\\d]+");  // faster performance
    /**
     * Return words in a string
     * Word is defined by a regular expression
     *
     * Time complexity = O(n)
     * Space complexity = O(n)
     * n = s.length()
     */
    std::vector<std::string> words_in_string(
        const std::string& s,
        const regex_lib::regex& r = r_default
    );


    const std::set<char> word_breaks_default = std::set<char> {
        ' ', '-', '.', ',',
        '/', '\\', ':',
        '(', ')', '[', ']'
    };  // faster performance
    /**
     * Return words in a string
     * Word is defined by word break characters
     * Uses manual method of string traversal
     *
     * Time complexity = O(n)
     * Space complexity = O(n)
     * n = s.length()
     */
    std::vector<std::string> words_in_string_manual(
        const std::string& s,
        const std::set<char>& word_breaks = word_breaks_default
    );


    /**
     * Calculate frequency words in document
     */
    WordFrequencies calculate_word_frequencies(const std::vector<std::string>& document);


    /**
     * A way to rate the similarity of two strings
     *
     * Time complexity = O(s)
     * Space complexity = O(s)
     * s = substrings.size()
     */
    double rate_strings_1(
        const std::string& s1, const std::string& s2,
        const std::vector<SubstringTuple>& substrings,
        const double weight_power = 2.5
    );


    /**
     * A way to rate the similarity of two strings
     *
     * Time complexity = O(m * n)
     * Space complexity = O(m * n)
     * m = s1.length()
     * n = s2.length()
     */
    double rate_strings_2(
        const std::string& s1, const std::string& s2,
        const WordFrequencies& word_frequencies,
        RatingCache& rating_cache, bool enable_rating_cache=false
    );
}

#endif
