cmake_minimum_required(VERSION 3.16)
project(c_testing VERSION 1.0.0 LANGUAGES C)

include(FetchContent)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -----------------------------
# Fetch cJSON
# -----------------------------
FetchContent_Declare(
  cjson
  GIT_REPOSITORY https://github.com/DaveGamble/cJSON.git
  GIT_TAG v1.7.18
)
FetchContent_MakeAvailable(cjson)

# -----------------------------
# Set build type
# -----------------------------
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# -----------------------------
# Find required packages
# -----------------------------
find_package(Threads REQUIRED)

# -----------------------------
# Source files
# -----------------------------
set(SOURCES
    src/main.c
    src/person.c
    src/reader.c
    ${cjson_SOURCE_DIR}/cJSON.c  # Compile cJSON directly into your executable
)

# -----------------------------
# Create executable
# -----------------------------
add_executable(${PROJECT_NAME} ${SOURCES})

# -----------------------------
# Include directories
# -----------------------------
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include  # Your headers
    ${cjson_SOURCE_DIR}                   # cJSON headers
)

# -----------------------------
# Link libraries
# -----------------------------
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

