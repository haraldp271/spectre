# Distributed under the MIT License.
# See LICENSE.txt for details.

# Since benchmarking is only interesting in Release mode the executable isn't
# added in any other build. Charm++'s main function is overridden with the main
# from the Benchmark library. The executable is not added to the `all` make
# target since it is only interesting in specific circumstances.
if(${benchmark_FOUND} AND "${CMAKE_BUILD_TYPE}" STREQUAL "Release")
  set(executable Benchmark)

  add_executable(
    ${executable}
    EXCLUDE_FROM_ALL
    Benchmark.cpp
    )

  # Add specific libraries needed for the benchmark you are interested in.
  target_link_libraries(
    ${executable}
    benchmark
    CoordinateMaps
    NumericalAlgorithms
    ${SPECTRE_LIBRARIES}
    )

  set_target_properties(
    ${executable}
    PROPERTIES LINK_FLAGS "-nomain-module -nomain"
    )
endif()
