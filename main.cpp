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

int main() {
    cout << col::GREEN << "Fetchfetch" << col::END;
    vector<string> paths = findFetches();
    cout << paths[5] << endl;
    return 0;
}
