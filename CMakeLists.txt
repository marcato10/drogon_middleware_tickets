cmake_minimum_required(VERSION 3.21)
project(middleware)

set(CMAKE_CXX_STANDARD 20)
find_package(Drogon REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/model)
include_directories(/usr/include/jsoncpp)
#Model
add_library(person STATIC ${CMAKE_CURRENT_SOURCE_DIR}/model/person.hpp ${CMAKE_CURRENT_SOURCE_DIR}/model/person.cpp)
add_library(ticket STATIC ${CMAKE_CURRENT_SOURCE_DIR}/model/ticket.hpp ${CMAKE_CURRENT_SOURCE_DIR}/model/ticket.cpp)

#Proxy Client
add_library(proxy_client STATIC ${CMAKE_CURRENT_SOURCE_DIR}/model/proxy_client.hpp ${CMAKE_CURRENT_SOURCE_DIR}/model/proxy_client.cpp)
target_link_libraries(proxy_client Drogon::Drogon)

add_library(person_controller STATIC ${CMAKE_CURRENT_SOURCE_DIR}/controller/PersonController.hpp ${CMAKE_CURRENT_SOURCE_DIR}/controller/PersonController.cpp)
add_library(ticket_controller STATIC ${CMAKE_CURRENT_SOURCE_DIR}/controller/TicketController.hpp ${CMAKE_CURRENT_SOURCE_DIR}/controller/TicketController.cpp)



#Repository
add_library(person_repository STATIC ${CMAKE_CURRENT_SOURCE_DIR}/repository/PersonRepository.hpp ${CMAKE_CURRENT_SOURCE_DIR}/repository/PersonRepository.cpp)
target_link_libraries(person_repository PUBLIC proxy_client person)

add_library(ticket_repository STATIC ${CMAKE_CURRENT_SOURCE_DIR}/repository/TicketRepository.hpp ${CMAKE_CURRENT_SOURCE_DIR}/repository/TicketRepository.cpp)
target_link_libraries(ticket_repository PUBLIC proxy_client ticket)
#Controller
target_link_libraries(person_controller PUBLIC person_repository)
target_include_directories(person_controller PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/repository)

target_link_libraries(ticket_controller PUBLIC ticket_repository)
target_include_directories(ticket_controller PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/repository)

add_executable(middleware main.cpp)
target_include_directories(middleware PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/controller)
target_link_libraries(middleware Drogon::Drogon person_controller ticket_controller)
