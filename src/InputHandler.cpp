// Handle the user input for the application
// User can enter a few flags when calling the program from the CLI
// Otherwise the handler prompts the user to enter necessary info

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include "InputHandler.h"
#include "CMakeConfig.h"

using namespace std;

const char* IN_ARG = "-i";
const char* OUT_ARG = "-o";
const char* HELP1_ARG = "-h";
const char* HELP2_ARG = "--help";
const char* VER1_ARG = "-v";
const char* VER2_ARG = "--version";

const char* UNKNOWN_OPT = "ERROR unknown option: ";
const char* HELP_MESSAGE = 
    "Usage: chia-log-analysis [option] ...\r\n" \
    "\r\n" \
    "OPTIONS\r\n" \
    "  -h, --help        Display this help message and exit\r\n" \
    "  -i <directory>    The directory to read Chia plotter logs from\r\n" \
    "  -o <filename>     The location to save the output data to\r\n" \
    "  -v, --version     List version information and exit\r\n" \
    "\r\n" \
    "If the input directory or output filename is not given the user will be \r\n" \
    "prompted to provide one.\r\n" \
    "\r\n" \
    "If the given output file is not empty the data will be appended without the \r\n" \
    "header row to support multiple runs of the program.";
const char* VERSION_MESSAGE = "Chia Log Analysis version ";
const char* WEBSITE_MESSAGE = "https://github.com/Pengor/chia-log-analysis";

// Prompt the user for the input directory until a valid one is provided
// in_dir will be set when this returns
void InputHandler::promptForInDir(void) {
    cout << "Enter directory to read logs from:" << endl;
    cin >> this->in_dir;

    while (!filesystem::is_directory(in_dir)) {
        cout << "DIRECTORY INVALID" << endl;
        cout << "Enter directory to read logs from:" << endl;
        cin >> this->in_dir;
    }
}

// Prompt the user for the output filename until a valid one is provided
// out_file will be set when this returns
void InputHandler::promptForOutFile(void) {
    cout << "Enter filename to save output to:" << endl;
    cin >> this->out_filename;

    while (!outFileValid()) {
        cout << "FILE INVALID" << endl;
        cout << "Enter filename to save output to:" << endl;
        cin >> this->out_filename;
    }
}

// Check that out_filename is valid
bool InputHandler::outFileValid(void) {
    ofstream out_file;
    out_file.open(this->out_filename);

    if (out_file.is_open()) {
        out_file.close();
        return true;
    } else {
        return false;
    }
}

// Send a message with program usage instructions
void InputHandler::helpMessage(void) {
    cout << HELP_MESSAGE << endl;
}

// Print the version information for the user
void InputHandler::versionMessage(void) {
    cout << VERSION_MESSAGE << CLA_MAJ_VER << "." << CLA_MIN_VER << endl;
    cout << WEBSITE_MESSAGE << endl;
}

// Constructor for InputHandler class
InputHandler::InputHandler(int argc, char* argv[]) {
    for (size_t i = 1; i < argc; i++) {
        args.push_back(argv[i]);
    }
    NumArgsLeft = argc - 1;
    in_dir_set = false;
    out_file_set = false;
}

// Returns empty strings if program should not proceed, otherwise
// returns a pair with the first element being the input directory path 
// and the second the output file path
pair<string, string> InputHandler::parseArgs(void) {
    for (size_t i = 0; i < NumArgsLeft; i++) {
        string s = args[i];
        if (s.compare(IN_ARG) == 0) {
            in_dir = args[++i]; // Use next argument as filepath
            in_dir_set = true;
        } else if (s.compare(OUT_ARG) == 0) {
            out_filename = args[++i]; // Use next argument as filepath
            out_file_set = true;
        } else if (s.compare(HELP1_ARG) == 0 || s.compare(HELP2_ARG) == 0) {
            helpMessage();
            return pair("","");
        } else if (s.compare(VER1_ARG) == 0 || s.compare(VER2_ARG) == 0) {
            versionMessage();
            return pair("","");
        } else {
            cout << UNKNOWN_OPT << s << endl;
            return pair("","");
        }
    }

    if (!in_dir_set) {
        promptForInDir();
    }
    
    if (!out_file_set) {
        promptForOutFile();
    }
    return pair(in_dir, out_filename);
}
