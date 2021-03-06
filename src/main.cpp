// Chia Log Analysis by Drew M. Johnson
// Authored 4/11/2021
// Last updated 5/20/2021
//
// This program prompts the user for two file locations if not provided:
//      1) The location to read Chia plotter logs from
//      2) The location to write a csv formatted output file to
// It then performs regular expression matching to find all the important info

#include <string>
#include <iostream>
#include <regex>
#include <fstream>
#include <filesystem>
#include "InputHandler.h"
#include "Patterns.h"
#include "TimeAndDate.h"

using namespace std;

int main(int argc, char* argv[]) {
    string directory, out_filename, current_line;
    ofstream out_file;
    ifstream in_file;

    // Handle user input
    InputHandler input_handler(argc, argv);
    pair<string, string> in_results = input_handler.parseArgs();
    if (in_results.first.compare("") == 0 && in_results.second.compare("") == 0)
        return 1; // Exit early if we didn't set input and output paths
    directory = in_results.first;
    out_filename = in_results.second;
    
    out_file.open(out_filename, fstream::out | fstream::app);

    if (out_file.is_open()) {
        if (filesystem::file_size(out_filename) == 0) {
            out_file << 
                "Log filename," << 
                "Temp dir 1," << 
                "Temp dir 2," << 
                "Plot ID," << 
                "Plot size," << 
                "Buffer size," << 
                "Buckets," << 
                "Threads," << 
                "Stripe size," << 
                "Start date," << 
                "Phase 1 duration," << 
                "Phase 1 CPU %," <<
                "Phase 2 duration," << 
                "Phase 2 CPU %," <<
                "Phase 3 duration," << 
                "Phase 3 CPU %," <<
                "Phase 4 duration," << 
                "Phase 4 CPU %," << 
                "Total time (sec)," << 
                "Total time," << 
                "Total CPU %," << 
                "Copy time," << 
                "Plot filename," << 
                "\n";
        }

        for(auto& current: filesystem::directory_iterator(directory)) {
            in_file.open(current.path());
            if (in_file.is_open()) {
                smatch match;
                bool found_flags[patterns::NUM_SEARCHES] = {false};
                cout << "Parsing file " << current.path() << endl;
                int started_plots = 0;
                int complete_plots = 0;
                while (getline(in_file, current_line)) {

                    size_t ff_i = 0; // found_flags iterator

                    // Perform regular expression searches for all the key info 
                    // we need, skipping searches that have already hit once to 
                    // improve performance
                    if (regex_search(current_line, match, patterns::IGNORE)) {
                        // Most lines in the plotter log files start with
                        // "\tBucket" and we don't care about them so just skip
                        // these lines
                        continue;
                    } else if (!found_flags[ff_i] && regex_search(current_line, match, patterns::PLOT_DIRS)) {
                        started_plots++;
                        out_file << current.path() << ","; // Log filename
                        out_file << match.str(1) << "," << match.str(2) << ",";
                        found_flags[ff_i] = true;
                    } else if (!found_flags[++ff_i] && regex_search(current_line, match, patterns::PLOT_ID)) {
                        out_file << match.str(1) << ",";
                        found_flags[ff_i] = true;
                    } else if (!found_flags[++ff_i] && regex_search(current_line, match, patterns::PLOT_SIZE)) {
                        out_file << match.str(1) << ",";
                        found_flags[ff_i] = true;
                    } else if (!found_flags[++ff_i] && regex_search(current_line, match, patterns::BUFFER_SIZE)) {
                        out_file << match.str(1) << ",";
                        found_flags[ff_i] = true;
                    } else if (!found_flags[++ff_i] && regex_search(current_line, match, patterns::BUCKETS)) {
                        out_file << match.str(1) << ",";
                        found_flags[ff_i] = true;
                    } else if (!found_flags[++ff_i] && regex_search(current_line, match, patterns::THREADS)) {
                        out_file << match.str(1) << "," << match.str(2) << ",";
                        found_flags[ff_i] = true;
                    } else if (!found_flags[++ff_i] && regex_search(current_line, match, patterns::START_DATE)) {
                        out_file << TimeAndDate::FormatDate(match.str(1)) << ",";
                        found_flags[ff_i] = true;
                    } else if (!found_flags[++ff_i] && regex_search(current_line, match, patterns::PHASE_1)) {
                        out_file << match.str(1) << "," << match.str(2) << ",";
                        found_flags[ff_i] = true;
                    } else if (!found_flags[++ff_i] && regex_search(current_line, match, patterns::PHASE_2)) {
                        out_file << match.str(1) << "," << match.str(2) << ",";
                        found_flags[ff_i] = true;
                    } else if (!found_flags[++ff_i] && regex_search(current_line, match, patterns::PHASE_3)) {
                        out_file << match.str(1) << "," << match.str(2) << ",";
                        found_flags[ff_i] = true;
                    } else if (!found_flags[++ff_i] && regex_search(current_line, match, patterns::PHASE_4)) {
                        out_file << match.str(1) << "," << match.str(2) << ",";
                        found_flags[ff_i] = true;
                    } else if (!found_flags[++ff_i] && regex_search(current_line, match, patterns::TOTAL_TIME)) {
                        out_file << match.str(1) << "," << TimeAndDate::FormatTime(match.str(1)) << "," << match.str(2) << ",";
                        found_flags[ff_i] = true;
                    } else if (!found_flags[++ff_i] && regex_search(current_line, match, patterns::COPY_TIME)) {
                        out_file << match.str(1) << ",";
                        found_flags[ff_i] = true;
                    } else if (!found_flags[++ff_i] && regex_search(current_line, match, patterns::FILENAME)) {
                        if (!found_flags[ff_i - 1])
                            out_file << ",";
                        out_file << match.str(1) << "," << "\n";
                        cout << "Plot " << ++complete_plots << " parsed" << endl;
                        for (size_t i = 0; i < patterns::NUM_SEARCHES; i++) {
                            found_flags[i] = false;
                        }
                    }
                }
                // Add line end if last plot parsed was incomplete
                if (started_plots > 0 && started_plots != complete_plots) {
                    cout << "Plot " << started_plots << " parsed (partial)" << endl;
                    out_file << "\n";
                } else if (started_plots == 0) { // File was not a plot log
                    cout << "NOTE: No relevant data found in file: " << current.path() << endl;
                }
                in_file.close();
            } else {
                cout << "ERROR: Unable to open file: " << current.path() << endl;
            }
        }
    }
    out_file.close();
}
