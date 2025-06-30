cmake_minimum_required(VERSION 3.10)
project(time-until)

find_package(cpprestsdk REQUIRED)

add_executable(time-until src/main.cpp src/handler.cpp src/datetimeparser.cpp)

set(Casablanca_LIBRARIES "-lboost_system -lcrypto -lssl -lcpprest")
set(LINKING_LIBRARIES ${Casablanca_LIBRARIES})

target_link_libraries(time-until PRIVATE cpprestsdk::cpprest ${LINKING_LIBRARIES})
