cmake_minimum_required(VERSION 3.05)
project(sorry)

set(CMAKE_CXX_STANDARD 17)

if (UNIX)
  set(BOOST_INCLUDE_DIR "/usr/include/boost")
  set(OPENSSL_INCLUDE_DIR "/usr/include/openssl")
  set(CROW_INCLUDE_DIR "./")
endif ()

set(HEADER_SEARCH_PATHS ${BOOST_INCLUDE_DIR}
    ${OPENSSL_INCLUDE_DIR}
    ${CROW_INCLUDE_DIR})

include_directories(${HEADER_SEARCH_PATHS})

if (UNIX)
  set(OPENSSL_LIBS "${OPENSSL_LIBRARIES}")
  file(GLOB BOOST_ROOT_DIR /usr/include/boost/*)
  find_package(Boost 1.58 REQUIRED COMPONENTS thread system log program_options chrono)
  find_package(Threads REQUIRED)
  #find_package(OpenSSL REQUIRED)
  #find_package(Tcmalloc)
endif ()

set(LIBRARY_SEARCH_PATHS ${OPENSSL_LIBS} ${Boost_LIBRARIES})


aux_source_directory(./ SORRY_SOURCE)

add_executable(${PROJECT_NAME} ${SORRY_SOURCE})

target_link_libraries(${PROJECT_NAME} ${LIBRARY_SEARCH_PATHS} -lpthread)

