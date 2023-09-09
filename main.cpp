#include <bits/stdc++.h>

void compile(const std::string &name) {
    std::string code = name + ".cpp", output = name;
    std::string cmd = "g++ " + code + " -o " + output;
    cmd += " -O2 -std=c++14 -Wall -Wextra -pedantic";
    if (system(cmd.c_str())) {
        std::cerr << "Compile Error: " << name << std::endl;
        std::exit(0);
    }
}

void run(const std::string &name, const std::string &args) {
    std::string output = name;
    std::string cmd = "./" + output + " " + args;
    if (system(cmd.c_str())) {
        std::cerr << "Runtime Error: " << name << std::endl;
        std::exit(0);
    }
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    const std::vector<std::pair<std::string, std::vector<std::string>>> algo = {
        {"odt/main", {"0 10 10", "0 1000 1000", "0 1000000 1000000"}},
        {"fenwick/main", {"0 10 10", "0 1000 1000", "0 1000000 1000000"}}
    };

    for (auto [name, all_args] : algo) {
        compile(name);
        for (auto args : all_args) {
            auto start = std::chrono::steady_clock::now();
            run(name, args);
            std::chrono::duration<double> diff = std::chrono::steady_clock::now() - start;
            std::cout << name << "(" << args << "): " << diff.count() << "s" << std::endl;
        }
    }

    return 0;
}
