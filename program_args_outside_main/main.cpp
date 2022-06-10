#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>


std::vector<std::string> read_args_outside_main()
{
    std::ifstream is("/proc/self/cmdline");
    std::vector<std::string> argv;
    for (std::string arg; std::getline(is, arg, '\000');)
        argv.push_back(arg);
    return argv;
}


int main(int argc, char** argv)
{
    std::cout << "args passed to main func: " << std::endl;
    for (int i = 0; i < argc; i++)
    {
        std::cout << "arg " << i << ": " << argv[i] << std::endl;
    }
    
    
    auto args_read_outside_main = read_args_outside_main();
    for (int i = 0; i < args_read_outside_main.size(); i++)
    {
        std::cout << "arg " << i << ": " << args_read_outside_main[i] << std::endl;
    }
}
