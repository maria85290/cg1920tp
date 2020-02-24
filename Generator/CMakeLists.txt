include_directories(${CG_TP_SOURCE_DIR}/Common/include)

link_directories(${CG_TP_SOURCE_DIR}/Common/src)

add_executable(Generator src/main.cpp)

target_link_libraries(Generator Common)
