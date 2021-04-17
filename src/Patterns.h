// Regular expression search pattern definitions

#ifndef PATTERNS_H
#define PATTERNS_H

#include <regex>

using namespace std;

namespace patterns {
    const regex IGNORE = regex("^\tBucket"); // Start of lines to ignore

    const regex PLOT_SIZE   = regex("^Plot size is: (\\d+)");
    const regex BUFFER_SIZE = regex("^Buffer size is: (\\d+)MiB");
    const regex BUCKETS     = regex("^Using (\\d+) buckets");
    const regex THREADS     = regex("^Using (\\d+) threads of stripe size (\\d+)");
    const regex START_DATE  = regex("^Starting phase 1/4: Forward Propagation into tmp files\\.\\.\\. (.+)");
    const regex PHASE_1     = regex("^Time for phase 1 = (\\d+\\.\\d+) seconds");
    const regex PHASE_2     = regex("^Time for phase 2 = (\\d+\\.\\d+) seconds");
    const regex PHASE_3     = regex("^Time for phase 3 = (\\d+\\.\\d+) seconds");
    const regex PHASE_4     = regex("^Time for phase 4 = (\\d+\\.\\d+) seconds");
    const regex TOTAL_TIME  = regex("^Total time = (\\d+\\.\\d+) seconds");
    const regex FILENAME    = regex("^Renamed final file from \".+\" to (\".+\")");

    const int NUM_SEARCHES = 11; // Number of patterns minus the ignore pattern
}

#endif /* PATTERNS_H */