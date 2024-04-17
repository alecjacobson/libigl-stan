include(tbb)

set(prefix ${FETCHCONTENT_BASE_DIR}/stan)
set(stan_INSTALL ${prefix}/src/stan)
set(stan_INCLUDE_DIR ${stan_INSTALL})
include(ExternalProject)
ExternalProject_Add(
  stan
  PREFIX ${prefix}
  URL https://github.com/stan-dev/math/archive/refs/tags/v4.8.1.tar.gz
  URL_MD5 df3dfb4b5e79eebf5ed292c236251173
  UPDATE_DISCONNECTED true
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
        )

# Add your project files
file(GLOB SRC_FILES *.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})
add_dependencies(${PROJECT_NAME} stan)
add_library(stan::stan INTERFACE IMPORTED GLOBAL)
set(stan_BOOST_INCLUDE_DIR ${stan_INSTALL}/lib/boost_1.81.0)
set(stan_SUNDIALS_INCLUDE_DIR ${stan_INSTALL}/lib/sundials_6.1.1/include/)
# make temporary folder at stan_BOOST_INCLUDE_DIR and stan_SUNDIALS_INCLUDE_DIR
# so that it exists now. It will be downloaded there.
file(MAKE_DIRECTORY ${stan_BOOST_INCLUDE_DIR})
file(MAKE_DIRECTORY ${stan_SUNDIALS_INCLUDE_DIR})
target_include_directories(stan::stan INTERFACE ${stan_INCLUDE_DIR} ${stan_BOOST_INCLUDE_DIR} ${stan_SUNDIALS_INCLUDE_DIR})
# Why is this needed but not defined by default?
target_compile_definitions(stan::stan INTERFACE "_REENTRANT")
target_link_libraries(stan::stan INTERFACE "${stan_LIBRARIES}" TBB::tbb)  

