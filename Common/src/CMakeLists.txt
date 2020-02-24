include_directories(${CG_TP_SOURCE_DIR}/Common/include)

file(GLOB HEADERS ${CG_TP_SOURCE_DIR}/Common/include)

add_library(Common test.cpp ${HEADERS})

target_include_directories(Common PUBLIC ${CG_TP_SOURCE_DIR}/Common/include)
