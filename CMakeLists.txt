cmake_minimum_required(VERSION 3.10)

project(cppsh LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    cppsh
    main.cpp
)

set(CPPSH_VERSION "0.1.0")
set(CPPSH_TRIPLET "${CMAKE_SYSTEM_PROCESSOR}-apple-${CMAKE_SYSTEM_NAME}${CMAKE_SYSTEM_VERSION}")
string(TOLOWER "${CPPSH_TRIPLET}" CPPSH_TRIPLET)
target_compile_definitions(cppsh PRIVATE 
    "MACHTYPE=\"${CPPSH_TRIPLET}\""
    "CPPSH_VERSION=\"${CPPSH_VERSION}\""
)