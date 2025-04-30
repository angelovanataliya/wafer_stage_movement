cmake_minimum_required(VERSION 3.16)

project(wafer_stage_movement)

add_executable(wafer_stage
    main.cpp
    FileManager.cpp
    WaferStage.cpp
)

target_link_libraries(wafer_stage pthread)
