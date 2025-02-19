# usecases/CMakeLists.txt
add_executable(SimpleClient simple_client.cpp)

# 假设build目录与项目根目录同级
include_directories(${CMAKE_SOURCE_DIR}/build/include)
target_link_libraries(SimpleClient
        ${CMAKE_SOURCE_DIR}/build/libleveldb.a
        pthread
)