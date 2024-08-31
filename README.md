# libigl 🤝 [stan math](https://mc-stan.org/users/interfaces/math)

## Build

stan math will be downloaded upon cmake-ing and will pull in its own boost and
sundial subdependencies and we'll also download tbb.

You can build with the usual

    mkdir build
    cd build
    cmake ../
    make

## Run


From within the `build` directory just issue:

    ./example

A glfw app should launch displaying a knight with white lines indicating the
computed gradients.

![](decimated-knight.png)

## Known Issues

> Thanks to [cmake/stan.cmake](cmake/stan.cmake) we no longer need to include 
`#include <stan/math.hpp>` before and Eigen or libigl includes.

 - In debug mode, stan is crashing on exit with a memory violation. This is not
   happening in http://github.com/alecjacobson/stan-crash perhaps because that
   project is using dependencies (presumably TBB) that come with stan rather
   than downloading them separately (as this project is).

