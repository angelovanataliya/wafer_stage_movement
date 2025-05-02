cmake_minimum_required(VERSION 3.16)

project(wafer_stage_movement)

add_executable(wafer_stage
    main.cpp
    FileManager.cpp
    WaferStage.cpp
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(wafer_stage Threads::Threads)

