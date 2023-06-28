# SuperHeroesGame
This is a project representing SuperHeroesGame. It is a custom game.

### Building and Running the project ###

**Linux**

``` shell
mkdir build && cd build
cmake ../
make -jN #where N is the number of jobs you want to use
./SuperHeroesGame #run the project
```

**Windows**\
It is important to note the you will need the path to the vcpkg installation from the previous steps
``` shell
mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]\scripts\buildsystems\vcpkg.cmake ../
cmake --build .
cd Debug # or Release depending on the build mode
SuperHeroesGame.exe #run the project
```
