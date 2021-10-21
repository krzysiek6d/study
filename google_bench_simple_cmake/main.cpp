#include <benchmark/benchmark.h>

#include <algorithm>
#include <limits>
#include <random>
#include <vector>


auto make_data(int size) {
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<int> dis{std::numeric_limits<int>::min()};

    std::vector<int> result{};
    std::generate_n(std::back_inserter(result), size, [&](){return dis(gen);});
    return result;
}

auto const test_data = make_data(10000);

template<typename Iterator>
void bubble_sort(Iterator first, Iterator last) {
    while (last != first) {
        auto new_last = first;
        --last;
        for (auto it = first; it != last; ) {
            auto next = it + 1;
            if (*it > *next) {
                std::iter_swap(it, next);
                new_last = next;
            }
            it = std::move(next);
        }
        last = std::move(new_last);
    }
}

template<typename RandomIterator>
void heapsort(RandomIterator first, RandomIterator last) {
    std::make_heap(first, last);
    std::sort_heap(first, last);
}

static void heapsort_test(benchmark::State& state) {
    auto test_data = make_data(state.range(0));
    for (auto _ : state) {
        auto data = test_data;
        heapsort(data.begin(), data.end());
        benchmark::DoNotOptimize(data);
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(heapsort_test)->RangeMultiplier(2)->Range(1<<10, 1<<15)->Complexity();

static void bubble_sort_test(benchmark::State& state) {
    auto test_data = make_data(state.range(0));
    for (auto _ : state) {
        auto data = test_data;
        bubble_sort(data.begin(), data.end());
        benchmark::DoNotOptimize(data);
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(bubble_sort_test)->RangeMultiplier(2)->Range(1<<10, 1<<15)->Complexity();

static void std_sort_test(benchmark::State& state) {
    auto test_data = make_data(state.range(0));
    for (auto _ : state) {
        auto data = test_data;
        std::sort(data.begin(), data.end());
        benchmark::DoNotOptimize(data);
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(std_sort_test)->RangeMultiplier(2)->Range(1<<10, 1<<15)->Complexity();

BENCHMARK_MAIN();
