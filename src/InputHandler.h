#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <string>
#include <vector>
#include <utility>

class InputHandler {
    private:
        int NumArgsLeft;
        std::vector<std::string> args;
        std::string in_dir, out_filename;
        bool in_dir_set, out_file_set;

        void promptForInDir(void);
        void promptForOutFile(void);
        bool outFileValid(void);
        void helpMessage(void);
        void versionMessage(void);

    public:
        InputHandler(int argc, char *argv[]);
        std::pair<std::string, std::string> parseArgs(void);
};

#endif /* INPUT_HANDLER_H */
