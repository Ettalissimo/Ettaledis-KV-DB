cmake_minimum_required(VERSION 3.10)
project(ETTALEDIS CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Headers live here — used by all targets
include_directories(include)

# --- Shared logic used by BOTH server and client (if any) ---
# If client doesn't use Store/validator/processor, remove this and
# link only into the server target below.
set(COMMON_SOURCES
    src/store.cpp
    src/request_validator.cpp
    src/request_processor.cpp
)

# --- Server binary ---
add_executable(server
    src/server.cpp
    ${COMMON_SOURCES}
)

# --- Client binary ---
add_executable(client
    src/client.cpp
)