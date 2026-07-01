file(GLOB_RECURSE src "${PROJECT_SOURCE_DIR}/include/tenshiUtil/*.cpp")

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include/tenshiUtil")
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${src})