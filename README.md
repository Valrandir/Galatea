Galatea
====

Valrandir's Game Library



Linux Build

On 64bits ubuntu install the 32bits libs:

1. libstdc++.i386
2. libgcc.i386
3. glibc.i386
4. glibc-devel.i386

Building Debug32 on 64Bits Ubuntu may gives this error:

/usr/include/feature.h: 324:26: fatal error: bits/predefs.h: No such file or directory

Fix: sudo apt-get install libc6-dev-i386
