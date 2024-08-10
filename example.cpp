#include <iomanip>
#include <ios>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <cctype>
#include <cstddef>

#include "./soft_string_compare/soft_string_compare.hh"


#ifdef __EMSCRIPTEN__

#include <emscripten/emscripten.h>
#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif


EXTERN EMSCRIPTEN_KEEPALIVE
int countOccurrences(char* str, int len, char target){
	int i, count = 0;
	for(i = 0; i < len; i++){
    	if(str[i] == target){
        	count++;
    	}
	}
	return count;
}

#endif


std::vector<std::string> lowercase_document(std::vector<std::string> document) {
    for (std::size_t i = 0; i < document.size(); i++) {
        for (std::size_t j = 0; j < document[i].length(); j++) {
            document[i][j] = std::tolower(document[i][j]);
        }
    }
    return document;
}


std::vector<std::string> read_document(std::string file_name) {
    std::vector<std::string> file_lines;

    std::ifstream my_file(file_name);
    if (!my_file.is_open()) {
        std::cerr << "Error: Could not open file " << file_name << " for writing." << std::endl;
        return file_lines;
    }
    
    std::string temp;
    while (std::getline(my_file, temp)) {
        // empty lines are NOT ignored because they may be important
        file_lines.push_back(temp);
    }

    my_file.close();
    return file_lines;
}


void write_document(std::vector<std::string> document, std::string file_name) {
    std::ofstream my_file(file_name);
    if (!my_file.is_open()) {
        std::cerr << "Error: Could not open file " << file_name << " for writing." << std::endl;
        return;
    }
    
    for (const auto& my_string : document) {
        my_file << my_string << std::endl;
    }
    my_file.close();
    return;
}


std::vector<std::tuple<std::size_t, double>> get_all_ratings(std::string s1, std::vector<std::string> all_list, std::map<std::string, std::size_t> word_frequencies) {
    std::vector<std::tuple<std::size_t, double>> ratings_list;

    // rate against each string
    for (std::size_t j = 0; j < all_list.size(); j++) {
        auto s2 = all_list[j];
        auto rating = ss_compare::rate_strings_2(s1, s2, word_frequencies);
        std::tuple<std::size_t, double> temp_tuple{j, rating};
        ratings_list.push_back(temp_tuple);
    }

    // sort ratings
    std::sort(ratings_list.begin(), ratings_list.end(), [](const auto a, const auto b) { return (std::get<1>(a) < std::get<1>(b)); });

    return ratings_list;

}


void real_run(std::string all_list_file, std::string input_list_file, std::string output_list_file, std::string dict_list_file) {
    std::vector<std::string> output_list;

    // lists to use
    auto all_list_raw = read_document(all_list_file);
    auto all_list = lowercase_document(all_list_raw);
    auto input_list = lowercase_document(read_document(input_list_file));
    auto dict_list = lowercase_document(read_document(dict_list_file));

    // get word frequencies
    auto word_frequencies = ss_compare::calculate_word_frequencies(dict_list);

    
    for (std::size_t i = 0; i < input_list.size(); i++) {
        auto s1 = input_list[i];

        // get all ratings
        std::vector<std::tuple<std::size_t, double>> ratings_list = get_all_ratings(s1, all_list, word_frequencies);

        if (ratings_list.size() == 0) {
            continue;
        }

        // for (std::size_t i = 0; i < ratings_list.size(); i++) {
        //     std::cout << std::get<1>(ratings_list[i]) << " points: " << all_list[std::get<0>(ratings_list[i])] << "\n";
        // }

        auto best_rating_tuple = ratings_list.back();
        // auto best_rating = std::get<1>(best_rating_tuple);
        auto best_match_index = std::get<0>(best_rating_tuple);
        auto best_match = all_list_raw[best_match_index];

        // std::cout << best_match << "\n";
        output_list.push_back(best_match);
    }

    write_document(output_list, output_list_file);
}


void user_input_test() {

    // wasm cannot read files
    std::vector<std::string> all_list_raw{
        "iPhone 13 Pro Max",
        "Nike Air Jordan 1",
        "Samsung 55\" QLED 4K Smart TV",
        "Dyson V11 Absolute",
        "Instant Pot Duo Plus 6 Qt",
        "PlayStation 5 Digital Edition",
        "Fitbit Versa 3 Smartwatch",
        "Keurig K-Cup Coffee Maker",
        "Bose QuietComfort 45 Headphones",
        "NutriBullet Pro - 13-Piece High-Speed Blender",
        "iRobot Roomba i3+ EVO Self-Emptying Robot Vacuum",
        "Ninja Foodi 10-in-1 XL Pro Air Fryer & Other",
        "LEGO Star Wars Millennium Falcon",
        "Amazon Echo Dot (4th Gen) Smart Speaker",
        "VIZIO 5.1 Surround Sound Bar System",
        "Logitech MX Master 3S Wireless Mouse",
        "KitchenAid Artisan Series 5 Qt. Mixer",
        "GoPro HERO11 Black",
        "Apple Watch Series 7 GPS + Cellular",
        "Sonos One SL Wi-Fi Speaker",
        "Microsoft Surface Pro 8 Laptop",
        "LG 65\" C1 Series OLED 4K UHD Smart TV",
        "Breville The Barista Express Espresso Machine",
        "Garmin Forerunner 945 GPS Running Watch",
        "Whirlpool 4.8 cu. ft. Front Load Washer",
        "Canon EOS R6 Mirrorless Camera",
        "Beats by Dr. Dre Studio3 Wireless Over-Ear Headphones",
        "Theragun Prime Deep Tissue Massage Gun",
        "Philips Norelco Multigroom All-in-One Trimmer",
        "Nespresso Vertuo Next Coffee & Espresso Maker",
        "Ring Video Doorbell Pro 2",
        "Brita Longlast Water Filter Pitcher",
        "Vitamix E310 Explorian Series Blender",
        "Traeger Pro 575 Wood Pellet Grill",
        "Oculus Quest 2 Advanced All-in-One Virtual Reality Headset",
        "Sunbeam Osmo 3 Reverse Osmosis Water Filter System",
        "Merax 10' Trampoline with Enclosure",
        "Klipsch HT-G700 3.1ch Dolby Atmos Soundbar",
        "YETI Tundra 45 Hard Cooler",
        "RTIC UltraLight 52 Qt Cooler",
        "HidrateSpark 3.0 32oz Insulated Water Bottle",
        "Leesa Original Mattress",
        "Anova Culinary Sous Vide Precision Cooker",
        "AeroGarden Harvest Elite Indoor Garden",
        "Waterpik Aquarius Water Flosser",
        "eufy RoboVac 11S (Slim) Robot Vacuum",
        "SKIL 1/4\" Hex Electric Screwdriver",
        "SMOK Novo 4 Pod System Vape Kit",
        "Anker PowerCore 10000 Portable Charger"
    };
    auto all_list = lowercase_document(all_list_raw);

    // get word frequencies
    auto word_frequencies = ss_compare::calculate_word_frequencies(all_list);

    while(true) {
        // accept string from user
        std::string s1;
        std::cout << "Enter name: ";
        std::getline(std::cin, s1);

        // important for wasm to break infinite loop
        if (s1.empty()) {
            break;
        }

        // apply lower-casing on string
        for (std::size_t i = 0; i < s1.length(); i++) {
            s1[i] = std::tolower(s1[i]);
        }

        // get all ratings
        std::vector<std::tuple<std::size_t, double>> ratings_list = get_all_ratings(s1, all_list, word_frequencies);

        // print ratings
        for (std::size_t k = 0; k < ratings_list.size(); k++) {
            auto rt = ratings_list[k];
            // print format specifiers
            std::cout << std::setfill(' ') << std::setw(2) << std::setprecision(3) << std::fixed;
            std::cout << std::get<1>(rt) << " rating: " << all_list_raw[std::get<0>(rt)] << "\n";
        }

        if (ratings_list.size() == 0) {
            continue;
        }

        auto best_rating_tuple = ratings_list.back();
        // auto best_rating = std::get<1>(best_rating_tuple);
        auto best_match_index = std::get<0>(best_rating_tuple);
        auto best_match = all_list_raw[best_match_index];
        auto best_match_not_raw = all_list[best_match_index];

        std::cout << "\n";
        auto cm = ss_compare::calculate_comparisonmatrix(s1, best_match_not_raw);
        auto sm = ss_compare::calculate_substringmatrix(s1, best_match_not_raw, cm);
        auto st = ss_compare::calculate_substringtuples(s1, best_match_not_raw, sm, 1);
        ss_compare::print_substringtuples(s1, best_match, st);
        std::cout << "\n";
    }
}


void dummy_test() {

    // lists to use
    auto all_list_raw = read_document("../data_dummy/all_list.txt");
    auto all_list = lowercase_document(all_list_raw);
    auto input_list = lowercase_document(read_document("../data_dummy/input_list.txt"));
    auto correct_list = read_document("../data_dummy/correct_list.txt");

    // get word frequencies
    auto word_frequencies = ss_compare::calculate_word_frequencies(all_list);

    // keep track of matches
    int correct_matches = 0, unknown_matches = 0, no_matches = 0;
    for (std::size_t i = 0; i < input_list.size(); i++) {
        auto s1 = input_list[i];
        auto s1_correct = correct_list[i];

        // get all ratings
        std::vector<std::tuple<std::size_t, double>> ratings_list = get_all_ratings(s1, all_list, word_frequencies);

        if (ratings_list.size() == 0) {
            continue;
        }

        auto best_rating_tuple = ratings_list.back();
        // auto best_rating = std::get<1>(best_rating_tuple);
        auto best_match_index = std::get<0>(best_rating_tuple);
        auto best_match = all_list_raw[best_match_index];

        // check if correct
        if (best_match == s1_correct) {
            correct_matches += 1;
            std::cout << "✅ " << best_match << "\n";

        } else if (s1_correct == "?") {
            unknown_matches += 1;
            std::cout << "☑️  " << best_match << "\n";

        } else {
            no_matches += 1;
            std::cout << "❌ " << best_match << " (" << s1 << " = " << s1_correct << ")\n";
        }
    }

    // print statistics
    std::cout << "\n";
    std::cout << "✅ count = " << correct_matches << "\n";
    std::cout << "☑️  count = " << unknown_matches << "\n";
    std::cout << "❌ count = " << no_matches << "\n";
    std::cout << "\n";
    std::cout << std::setfill(' ') << std::setw(2) << std::setprecision(3) << std::fixed;
    std::cout << "🎯 ratio = " << (100.0 * correct_matches / (std::max(1, correct_matches + no_matches))) << " %\n";
    std::cout << "\n";
}


void real_run_wrapper(int argc, char** argv) {
    if (argc != 5) {
        std::cerr << "Usage: <program-name> <all_list_file> <input_list_file> <output_list_file> <0/1>\n";
        return;
    }

    real_run(
        std::string(argv[1]),
        std::string(argv[2]),
        std::string(argv[3]),
        std::string(argv[4])
    );
}


int main(int argc, char** argv) {

    dummy_test();  // Runs test on dummy data
    user_input_test();  // Finds match for user inputs
    // real_run_wrapper(argc, argv);

    return 0;
}