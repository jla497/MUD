1. Create a new directory for building.

        mkdir networkbuild

2. Change into the new directory.

        cd networkbuild

3. Run CMake with the path to the source.

        cmake ..

4. Run make inside the build directory:

        make

This produces `mudserver` and `chatclient` tools called `bin/mudserver` and
`bin/chatclient` respectively. The library for single threaded clients and
servers is built in `lib/`.

## Running the Example Chat Client and Mud Server

First run the chat server on an unused port of the server machine.

    bin/mudserver 4000

In separate terminals, run multiple instances of the chat client using:

    bin/chatclient localhost 4000


