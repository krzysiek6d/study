#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>


std::vector<std::string> tokenize(const std::string& cmdline)
{
    std::vector<std::string> args;
    std::istringstream iss(cmdline);
    std::string arg;
    while (iss >> arg)
    {
        args.push_back(arg);
    }
    return args;
}


void read_args_outside_main()
{
    std::ifstream is("/proc/self/cmdline");
    std::string cmdline{};
    std::getline(is, cmdline);
    std::replace(cmdline.begin(), cmdline.end(), '\000', ' ');
    std::cout << "args read from /proc/self/cmdline" << std::endl;
    std::cout << cmdline << std::endl;
    std::cout << "tokenized" << std::endl;
    auto argv = tokenize(cmdline);
    for (int i = 0; i < argv.size(); i++)
    {
        std::cout << "arg " << i << ": " << argv[i] << std::endl;
    }
}


int main(int argc, char** argv)
{
    std::cout << "args passed to main func: " << std::endl;
    for (int i = 0; i < argc; i++)
    {
        std::cout << "arg " << i << ": " << argv[i] << std::endl;
    }
    read_args_outside_main();
}
