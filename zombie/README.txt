Parent is blocked by sleep to reach waitforpid.
During this time child is a zombie.

when child is alive
krzysiek  3746  0.0  0.0   5884  1588 pts/1    S+   12:34   0:00              \_ ./a.out
krzysiek  3747  0.0  0.0   5884   192 pts/1    S+   12:34   0:00                  \_ ./a.out

when child is ended but parent is still sleeping
krzysiek  3746  0.0  0.0   5884  1588 pts/1    S+   12:34   0:00              \_ ./a.out
krzysiek  3747  0.0  0.0      0     0 pts/1    Z+   12:34   0:00                  \_ [a.out] <defunct>

output:
$ ./a.out
hello 3746
parent: my pid: 3746
parent: go sleep for 20sec
child: my pid: 3747
child: my parent pid: 3746
child: go sleep for 10sec
child: woke up, parent is still blocked by sleep, I'll exit in a moment and become a ZOMBIE
bye 3747
parent: woke up
exited, status=0
bye 3746