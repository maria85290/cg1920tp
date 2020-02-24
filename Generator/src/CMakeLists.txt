include_directories(${CG_TP_SOURCE_DIR}/Generator/include)
include_directories(${CG_TP_SOURCE_DIR}/Common/include)

link_directories(${CG_TP_SOURCE_DIR}/Common/src)

add_executable(Generator main.cpp)

target_link_libraries(Generator Common)
