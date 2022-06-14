#include <stdio.h>
#include <chrono>
#include <thread>
#include <string>
#include <iostream>

void print_progress(int current, int total, int bar_length)
{
	setlocale(LC_ALL, "");
	double fraction = (double)current / (double)total;
	std::string arrow = std::string(fraction * bar_length, '-') + (current==total ? '-' : '>');
	std::string padding = std::string(bar_length - arrow.length() + 1, ' ');
	char ending = (current == total ? '\n' : '\r');
	printf("Progress: [%s%s] %d%% %c", arrow.c_str(), padding.c_str(), (int)(fraction*100.0), ending);
	fflush(stdout);
}

int main()
{
	using namespace std::chrono_literals;
	for (int i = 0; i <= 100; i++)
	{
		std::this_thread::sleep_for(50ms);
		print_progress(i, 100, 40);
	}
	std::cout << "completed" << std::endl;
}
