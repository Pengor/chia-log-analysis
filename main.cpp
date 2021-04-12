// Chia Log Analysis by Drew M. Johnson
// Authored 4/11/2021
// Last updated 4/11/2021

// This program prompts the user for two file locations:
//      1) The location to read Chia plotter logs from
//      2) The location to write a csv formatted output file to
// It then performs regular expression matching to find all the important info

#include <string>
#include <iostream>
#include <regex>
#include <fstream>
#include <filesystem>

using namespace std;

const regex REGEX_IGNORE = regex("^\tBucket"); // Start of lines to ignore

const regex REGEX_PLOT_SIZE   = regex("^Plot size is: (\\d+)");
const regex REGEX_BUFFER_SIZE = regex("^Buffer size is: (\\d+)MiB");
const regex REGEX_BUCKETS     = regex("^Using (\\d+) buckets");
const regex REGEX_THREADS     = regex("^Using (\\d+) threads of stripe size (\\d+)");
const regex REGEX_START_DATE  = regex("^Starting phase 1/4: Forward Propagation into tmp files\\.\\.\\. (.+)");
const regex REGEX_PHASE_1     = regex("^Time for phase 1 = (\\d+\\.\\d+) seconds");
const regex REGEX_PHASE_2     = regex("^Time for phase 2 = (\\d+\\.\\d+) seconds");
const regex REGEX_PHASE_3     = regex("^Time for phase 3 = (\\d+\\.\\d+) seconds");
const regex REGEX_PHASE_4     = regex("^Time for phase 4 = (\\d+\\.\\d+) seconds");
const regex REGEX_TOTAL_TIME  = regex("^Total time = (\\d+\\.\\d+) seconds");
const regex REGEX_FILENAME    = regex("^Renamed final file from \".+\" to (\".+\")");

int main() {
    string directory, out_filename, current_line;
    ofstream out_file;
    ifstream in_file;

    cout << "Enter directory to read logs from:" << endl;
    cin >> directory;
    
    cout << "Enter filename to save output to:" << endl;
    cin >> out_filename;

    out_file.open(out_filename);

    if (out_file.is_open()) {
        if (filesystem::file_size(out_filename) == 0) {
            out_file << 
                "Plot size," << 
                "Buffer size," << 
                "Buckets," << 
                "Threads," << 
                "Stripe size," << 
                "Start date," << 
                "Phase 1 duration," << 
                "Phase 2 duration," << 
                "Phase 3 duration," << 
                "Phase 4 duration," << 
                "Total time," << 
                "Plot filename," << 
                endl;
        }

        for(auto& current: filesystem::directory_iterator(directory)) {
            in_file.open(current.path());
            if (in_file.is_open()) {
                smatch match;
                bool found_flags[10] = {false};
                while (getline(in_file, current_line)) {

                    // Perform regular expression searches for all the key info 
                    // we need, skipping searches that have already hit once to 
                    // improve performance
                    if (regex_search(current_line, match, REGEX_IGNORE)) {
                        // Most lines in the plotter log files start with
                        // "\tBucket" and we don't care about them so just skip
                        // these lines
                        continue;
                    } else if (!found_flags[0] && regex_search(current_line, match, REGEX_PLOT_SIZE)) {
                        out_file << match.str(1) << ",";
                        found_flags[0] = true;
                    } else if (!found_flags[1] && regex_search(current_line, match, REGEX_BUFFER_SIZE)) {
                        out_file << match.str(1) << ",";
                        found_flags[1] = true;
                    } else if (!found_flags[2] && regex_search(current_line, match, REGEX_BUCKETS)) {
                        out_file << match.str(1) << ",";
                        found_flags[2] = true;
                    } else if (!found_flags[3] && regex_search(current_line, match, REGEX_THREADS)) {
                        out_file << match.str(1) << "," << match.str(2) << ",";
                        found_flags[3] = true;
                    } else if (!found_flags[4] && regex_search(current_line, match, REGEX_START_DATE)) {
                        out_file << match.str(1) << ",";
                        found_flags[4] = true;
                    } else if (!found_flags[5] && regex_search(current_line, match, REGEX_PHASE_1)) {
                        out_file << match.str(1) << ",";
                        found_flags[5] = true;
                    } else if (!found_flags[6] && regex_search(current_line, match, REGEX_PHASE_2)) {
                        out_file << match.str(1) << ",";
                        found_flags[6] = true;
                    } else if (!found_flags[7] && regex_search(current_line, match, REGEX_PHASE_3)) {
                        out_file << match.str(1) << ",";
                        found_flags[7] = true;
                    } else if (!found_flags[8] && regex_search(current_line, match, REGEX_PHASE_4)) {
                        out_file << match.str(1) << ",";
                        found_flags[8] = true;
                    } else if (!found_flags[9] && regex_search(current_line, match, REGEX_TOTAL_TIME)) {
                        out_file << match.str(1) << ",";
                        found_flags[9] = true;
                    } else if (regex_search(current_line, match, REGEX_FILENAME)) {
                        out_file << match.str(1) << ",";
                        break; // Last piece of data we're interested in, skip the rest of the lines
                    }
                }
                out_file << endl;
            }
            in_file.close();
            cout << "Parsed: " << current.path() << endl;
        }
    }
    out_file.close();
}
