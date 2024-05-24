#include <iostream>
#include <thread>
#include <chrono>
#include <csignal>
#include <cassert>
#include <functional>
#include <memory>

//volatile sighandler_t previousSignalHandler;
//extern "C" void __gcov_dump();
//void gcovDump(int signal)
//{
//    __gcov_dump();
//    std::signal(signal, previousSignalHandler);
//    std::raise(signal);
//}


class App;
App* app = nullptr;
void stopApp(int);

class Member
{
public:
    Member() {std::cout << "member ctor" << std::endl;}
    ~Member() {std::cout << "member dtor" << std::endl;}
};

class App
{
public:
    App()
    {
        std::cout << "constructor" << std::endl;
        app = this;
        std::signal(SIGTERM, stopApp);
    }
    void run()
    {
        is_running = true;
        while(is_running)
        {
            using namespace std::chrono_literals;
            std::cout << "hello" << std::endl;
            std::this_thread::sleep_for(2000ms);
        }
        std::cout << "app is killed" << std::endl;
        exit(0);
    }
    void stop()
    {
        is_running = false;
    }
    ~App()
    {
        std::cout << "destructor" << std::endl;
    }
    bool is_running;
    Member member;
};


void stopApp(int)
{
    app->stop();
}

int main()
{
    auto app = std::make_shared<App>();
//    previousSignalHandler = std::signal(SIGTERM, gcovDump);
//    assert(previousSignalHandler != nullptr);

    app->run();

    using namespace std::chrono_literals;
    std::cout << "hello" << std::endl;
    std::this_thread::sleep_for(2000ms);
    std::cout << "hello" << std::endl;
    std::this_thread::sleep_for(2000ms);
    std::cout << "hello" << std::endl;
    std::this_thread::sleep_for(2000ms);
    std::cout << "hello" << std::endl;
    std::this_thread::sleep_for(2000ms);
}