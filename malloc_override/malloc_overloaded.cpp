#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <execinfo.h>
#include <mutex>

std::recursive_mutex malloc_mutex;
FILE * log_file;

static inline void *lookup_symbol(const char *sym)
{
    void *func = dlsym(RTLD_NEXT, sym);
    if (!func) {
        void *handle = dlopen("libc.so", RTLD_LAZY);
        if (!handle) {
            fprintf(stderr, "Lookup error for %s: %s", sym, dlerror());
            abort();
        }
        func = dlsym(handle, sym);
        if (!func) {
            fprintf(stderr, "Cannot lookup %s", sym);
            abort();
        }
        dlclose(handle);
    }
    return func;
}

void print_trace(int allocated_size)
{
    if (!log_file)
    {
        log_file = fopen("/tmp/malloc_log.txt", "w");
    }
    void *array[100];
    int size;
    char **strings;

    size = backtrace (array, 100);
    strings = backtrace_symbols (array, size);
    fprintf(log_file, "malloc size is: %d\n", allocated_size);
    fprintf(log_file, "Obtained %d stack frames.\n", size);

    for (int i = 0; i < size; i++)
        fprintf(log_file, "[%d] %s\n", i, strings[i]);
    fflush(log_file);

    free (strings);
}

void* malloc( size_t size)
{
    std::lock_guard<std::recursive_mutex> malloc_blocker{malloc_mutex};
    static bool isPrinting = false;
    static void* (*func)(size_t);
    if (!func) {
        func = (decltype(func))(lookup_symbol(__func__));
    }
    if (!isPrinting) {
        isPrinting = true;
        print_trace(size);
        isPrinting = false;
    }
    return func(size);
}