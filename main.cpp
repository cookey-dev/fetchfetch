#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <filesystem>
#include <boost/algorithm/string.hpp>

using namespace std;

namespace fs = std::filesystem;
namespace col {
    string END = "\033[0m\n";
    string ENDCOLOR = "\033[0m";
    string GREEN = "\033[92m";
    string CYAN = "\033[96m";
    string RED = "\033[91m";
};

vector<string> findFetches() {
    string path = getenv("PATH");
    vector<string> paths_str;
    boost::split(paths_str, path, boost::is_any_of(":"));
    vector<string> paths;
    for (const string &path_str : paths_str) {
        if (!fs::exists(path_str)) continue;
        for (const fs::path &path : fs::directory_iterator(path_str)) {
            string fname = path.filename();
            if (boost::ends_with(fname, "fetch")) paths.push_back(fname);
        }
    }
    return paths;
}

void outputFetches(vector<string> fetches) {
    if (fetches.size() <= 0) {
        cout << col::RED << "No fetches found :(" << col::END;
        return;
    } else {
        cout << col::GREEN << "Found " << to_string(fetches.size()) << " fetches!" << col::END;
    }
    for (const string &fetch : fetches) {
        cout << col::CYAN << "• " << fetch << col::END;
    }
}

int main() {
    cout << col::GREEN << "Fetchfetch\nScanning $PATH" << col::END;
    vector<string> fetches = findFetches();
    outputFetches(fetches);
    return 0;
}
