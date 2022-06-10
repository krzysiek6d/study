takes arguments outside main function, linux only

works with bash -c'....'
works with exports before executable

DUPA=foo ./program_args_outside_main -d 3 4 23432 ljkh423    34          
args passed to main func: 
arg 0: ./program_args_outside_main
arg 1: -d
arg 2: 3
arg 3: 4
arg 4: 23432
arg 5: ljkh423
arg 6: 34
args read from /proc/self/cmdline
./program_args_outside_main -d 3 4 23432 ljkh423 34 
tokenized
arg 0: ./program_args_outside_main
arg 1: -d
arg 2: 3
arg 3: 4
arg 4: 23432
arg 5: ljkh423
arg 6: 34

