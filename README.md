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

As far as I can tell, the

```cpp
#include <stan/math.hpp>
```

line must come before any includes to Eigen. If you first include Eigen headers
(or libigl which in turn include Eigen headers), then you could get errors like:

```
…/libigl-stan/build/_deps/stan/src/stan/stan/math/rev/fun/gp_exp_quad_cov.hpp:94:58: error: no member named 'adj' in 'stan::math::arena_matrix<Eigen::Matrix<stan::math::var_value<double>, -1, 1, 0>>'
```
