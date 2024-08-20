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


namespace dummy_data {
    std::vector<std::string> input_product_names {
        "iphne 13 pro maks",
        "nkie ar jrdan 1",
        "samsng 55\" qled 4k smrt tv",
        "dysin v11 absloote",
        "instnt pot dou plus 6 qt",
        "playstaton 5 digitl editon",
        "fitbt versa 3 smrt wach",
        "keurigk-cup coffe makr",
        "bose quetcomfort 45 hdphnes",
        "nutribullt pro - 13-pce hi-sped blndr",
        "roomba i3+ evo self-emtying robt vacum",
        "ninja foodie 10-in1 xl pro ar fyer & othr",
        "lgo star wars milenim falcn",
        "amazn eko dot (4th gen) smrt spkr",
        "vizio 5.1 srrond sound bar systm",
        "logitek mx mster 3s wirelss mose",
        "kitchenaid artsan seres 5 qt mixr",
        "goPro HRO11 blck",
        "appel watchh series 7 gps + cellulr",
        "sonos on sl wi-fi speakr",
        "microsft srface pro 8 laptp",
        "lg 65\" c1 seris aled 4k uhd smrt tv",
        "breville the barsta expres espreso machin",
        "garmen forerunr 945 gps runnin watch",
        "whrlpol 4.8 cu ft frnt load washr",
        "canon eos r6 mirorles camra",
        "beats by dr studio3 wirelss over-ear hdphnes",
        "theragun prim deep tisue masage gun",
        "philps norelco multigrom al-in-1 trimr",
        "nespreso vertuo next coffe & espreso makr",
        "ring video dorbel pro 2",
        "brita longlas water filtr pitchr",
        "vitamx e310 explrer seris blndr",
        "traeger pro 575 wod pelet gril",
        "oculs quest 2 advnced al-in-one virtul realty hedset",
        "sunbeemosmo 3 revrse osmsis water filtr systm",
        "meijei 10 trmpoline with enclosre",
        "crutchfild ht-g700 3.1ch dolby atms soundbr",
        "yeti tndr 45 hard coolr",
        "rtic ultralite 52 qt coolr",
        "hidrte spak 3.0 32oz instlated water botl",
        "lumin ultra-comfortble coper-infusd matres",
        "anova culnary sous vide precisin cookr",
        "aerogardn harvest elite indor gardn",
        "waterpk aquaris water flossr",
        "eufy robovac 11s (slim) robt vacum",
        "scrpl 1/4\" hex elctric scredriver",
        "smok novo 4 pod systm vape kt",
        "anker powercore 10000 portble charger"
    };


    std::vector<std::string> correct_product_names {
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


    std::vector<std::string> all_product_names {
        "Keurig K-Cup Coffee Maker",
        "Beats by Dr. Dre Studio3 Wireless Over-Ear Headphones",
        "Garmin Forerunner 945 GPS Running Watch",
        "Merax 10' Trampoline with Enclosure",
        "GoPro HERO11 Black",
        "Ring Video Doorbell Pro 2",
        "SMOK Novo 4 Pod System Vape Kit",
        "Leesa Original Mattress",
        "NutriBullet Pro - 13-Piece High-Speed Blender",
        "LG 65\" C1 Series OLED 4K UHD Smart TV",
        "Oculus Quest 2 Advanced All-in-One Virtual Reality Headset",
        "Amazon Echo Dot (4th Gen) Smart Speaker",
        "Nike Air Jordan 1",
        "Waterpik Aquarius Water Flosser",
        "iRobot Roomba i3+ EVO Self-Emptying Robot Vacuum",
        "Breville The Barista Express Espresso Machine",
        "Whirlpool 4.8 cu. ft. Front Load Washer",
        "eufy RoboVac 11S (Slim) Robot Vacuum",
        "Dyson V11 Absolute",
        "Instant Pot Duo Plus 6 Qt",
        "PlayStation 5 Digital Edition",
        "YETI Tundra 45 Hard Cooler",
        "Canon EOS R6 Mirrorless Camera",
        "Logitech MX Master 3S Wireless Mouse",
        "Sunbeam Osmo 3 Reverse Osmosis Water Filter System",
        "Nespresso Vertuo Next Coffee & Espresso Maker",
        "VIZIO 5.1 Surround Sound Bar System",
        "KitchenAid Artisan Series 5 Qt. Mixer",
        "Traeger Pro 575 Wood Pellet Grill",
        "Microsoft Surface Pro 8 Laptop",
        "SKIL 1/4\" Hex Electric Screwdriver",
        "Klipsch HT-G700 3.1ch Dolby Atmos Soundbar",
        "Brita Longlast Water Filter Pitcher",
        "Vitamix E310 Explorian Series Blender",
        "Anova Culinary Sous Vide Precision Cooker",
        "Sonos One SL Wi-Fi Speaker",
        "LEGO Star Wars Millennium Falcon",
        "AeroGarden Harvest Elite Indoor Garden",
        "Philips Norelco Multigroom All-in-One Trimmer",
        "Ninja Foodi 10-in-1 XL Pro Air Fryer & Other",
        "Apple Watch Series 7 GPS + Cellular",
        "Theragun Prime Deep Tissue Massage Gun",
        "RTIC UltraLight 52 Qt Cooler",
        "Bose QuietComfort 45 Headphones",
        "Samsung 55\" QLED 4K Smart TV",
        "Anker PowerCore 10000 Portable Charger",
        "Fitbit Versa 3 Smartwatch",
        "iPhone 13 Pro Max",
        "HidrateSpark 3.0 32oz Insulated Water Bottle"
    };
}


std::string lowercase_string(std::string s) {
    for (std::size_t i = 0; i < s.length(); i++) {
        s[i] = std::tolower(s[i]);
    }
    return s;
}


std::vector<std::string> lowercase_document(std::vector<std::string> document) {
    for (std::size_t i = 0; i < document.size(); i++) {
        document[i] = lowercase_string(document[i]);
    }
    return document;
}


std::vector<std::string> read_document(std::string file_name) {
    std::ifstream my_file(file_name);
    if (!my_file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    std::string temp;
    std::vector<std::string> file_lines;
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
        throw std::runtime_error("Failed to open file");
    }

    for (const auto& my_string : document) {
        my_file << my_string << std::endl;
    }

    my_file.close();
}


std::vector<std::tuple<std::size_t, double>> get_all_ratings_1(const std::string& s1, const std::vector<std::string>& all_list, const ss_compare::WordFrequencies& word_frequencies, ss_compare::WordsCache words_cache) {
    std::vector<std::tuple<std::size_t, double>> ratings_list;

    // rate against each string
    for (std::size_t j = 0; j < all_list.size(); j++) {
        auto s2 = all_list[j];
        auto rating = ss_compare::rate_strings_2(s1, s2, word_frequencies, words_cache);
        std::tuple<std::size_t, double> temp_tuple {j, rating};
        ratings_list.push_back(temp_tuple);
    }

    // sort ratings
    std::sort(ratings_list.begin(), ratings_list.end(), [](const std::tuple<std::size_t, double>& a, const std::tuple<std::size_t, double>& b) { return (std::get<1>(a) < std::get<1>(b)); });

    return ratings_list;
}


void real_run(const std::string& all_list_file, const std::string& input_list_file, const std::string& output_list_file, const std::string& dict_list_file) {
    std::vector<std::string> output_list;

    // lists to use
    auto all_list_raw = read_document(all_list_file);
    auto all_list = lowercase_document(all_list_raw);
    auto input_list = lowercase_document(read_document(input_list_file));
    auto dict_list = lowercase_document(read_document(dict_list_file));

    // get word frequencies
    auto word_frequencies = ss_compare::calculate_word_frequencies(dict_list);

    // initialize words cache
    auto words_cache = ss_compare::WordsCache ();

    for (std::size_t i = 0; i < input_list.size(); i++) {
        auto s1 = input_list[i];

        // get all ratings
        auto ratings_list = get_all_ratings_1(s1, all_list, word_frequencies, words_cache);

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

    // create all lists
    auto all_list_raw = dummy_data::all_product_names;
    auto all_list = lowercase_document(all_list_raw);

    // get word frequencies
    auto word_frequencies = ss_compare::calculate_word_frequencies(all_list);

    // initialize words cache
    auto words_cache = ss_compare::WordsCache ();

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
        auto ratings_list = get_all_ratings_1(s1, all_list, word_frequencies, words_cache);

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
    auto all_list_raw = dummy_data::all_product_names;
    auto all_list = lowercase_document(all_list_raw);
    auto input_list = lowercase_document(dummy_data::input_product_names);
    auto correct_list = dummy_data::correct_product_names;

    // get word frequencies
    auto word_frequencies = ss_compare::calculate_word_frequencies(all_list);

    // initialize words cache
    auto words_cache = ss_compare::WordsCache ();

    // keep track of matches
    int correct_matches = 0, unknown_matches = 0, no_matches = 0;
    for (std::size_t i = 0; i < input_list.size(); i++) {
        auto s1 = input_list[i];
        auto s1_correct = correct_list[i];

        // get all ratings
        auto ratings_list = get_all_ratings_1(s1, all_list, word_frequencies, words_cache);

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
        std::cerr << "Usage: <program-name> <all_list_file> <input_list_file> <output_list_file> <dict_list_file>\n";
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
