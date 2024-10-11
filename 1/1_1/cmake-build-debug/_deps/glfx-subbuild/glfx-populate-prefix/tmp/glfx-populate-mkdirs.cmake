# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/maksimveselov/Projects/ood/1/1_1/cmake-build-debug/_deps/glfx-src"
  "/Users/maksimveselov/Projects/ood/1/1_1/cmake-build-debug/_deps/glfx-build"
  "/Users/maksimveselov/Projects/ood/1/1_1/cmake-build-debug/_deps/glfx-subbuild/glfx-populate-prefix"
  "/Users/maksimveselov/Projects/ood/1/1_1/cmake-build-debug/_deps/glfx-subbuild/glfx-populate-prefix/tmp"
  "/Users/maksimveselov/Projects/ood/1/1_1/cmake-build-debug/_deps/glfx-subbuild/glfx-populate-prefix/src/glfx-populate-stamp"
  "/Users/maksimveselov/Projects/ood/1/1_1/cmake-build-debug/_deps/glfx-subbuild/glfx-populate-prefix/src"
  "/Users/maksimveselov/Projects/ood/1/1_1/cmake-build-debug/_deps/glfx-subbuild/glfx-populate-prefix/src/glfx-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/maksimveselov/Projects/ood/1/1_1/cmake-build-debug/_deps/glfx-subbuild/glfx-populate-prefix/src/glfx-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/maksimveselov/Projects/ood/1/1_1/cmake-build-debug/_deps/glfx-subbuild/glfx-populate-prefix/src/glfx-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
