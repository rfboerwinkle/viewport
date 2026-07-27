# TL;DR
```sh
./build.sh reference
./bin/reference < maps/room.txt
```

# Getting Started
Read `base.h`. It explains most things.

# Building
`build.sh IMPLEMENTATION_NAME` will compile `main.c`, `base.c`, and
`implementations/IMPLEMENTATION_NAME.c` into `bin/IMPLEMENTATION_NAME`. Feel
free to make new implementations and modify `main.c` to suit your needs, but
probably don't touch `base.c` or `base.h`.
