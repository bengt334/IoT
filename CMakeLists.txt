# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
set(CODECHECKER_ANALYZE_OPTS
  "--config;${CMAKE_SOURCE_DIR}/config/codechecker.yml;"
  "--skip;${CMAKE_SOURCE_DIR}/config/skip.codechecker"
  CACHE STRING "CodeChecker options")
set(CODECHECKER_ANALYZE_OPTS
  "--enable-all"
  CACHE STRING "CodeChecker options")
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(temp_meas)
add_subdirectory(src)



