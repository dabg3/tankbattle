# Tank Battle

WARNING: Code is a mess right now, I'm getting the hang of gamedev/graphics and SDL2 itself.


## Build

Configure 
```shell
cmake -B build -DCMAKE_BUILD_TYPE=Debug 
```

Compile
```shell
cd build
make 
```

Run all test suites
```shell
make test
```


## Project layout 

* `assets`      - static game components
* `engine`      - engine headers and sources
* `tankbattle`  - game implementation
* `tests`       - test suites
* `unity`       - test framework


## LSP Integration

Language servers require the source file list and their compilation command lines.
Those are obtained by reading a `compile_commands.json` file generated by the build system.

```shell
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -B build
ln -s build/compile_commands.json .
```


## TODO
* REFACTORING
* position x,y as integers
* group objects
* improve accelleration and slow down
* handle arena borders
* fire bullets
* shot animation
