cmake_minimum_required(VERSION 3.10)
project(server)

# Configure compiler options ...
set(CMAKE_CXX_STANDARD 17)


# headers search paths ...
set(CPPRESTSDK_INCLUDE_DIR "/usr/include")
set(MONGOCXX_INCLUDE_DIR "/usr/local/include/mongocxx/v_noabi")  
set(BSONCXX_INCLUDE_DIR "/usr/local/include/bsoncxx/v_noabi")  

# Configure required libraries ...
if (UNIX) # Darwing or Linux
  find_package(Boost REQUIRED COMPONENTS system thread log program_options chrono)
  find_package(Threads REQUIRED)

  if (APPLE)
    # Prefer a homebrew version of OpenSSL over the one in /usr/lib
    file(GLOB OPENSSL_ROOT_DIR /usr/local/Cellar/openssl/*)
    # Prefer the latest (make the latest one first)
    list(REVERSE OPENSSL_ROOT_DIR)

    find_package(OpenSSL 1.0.2 REQUIRED)
    set(OPENSSL_VERSION "1.0.2f")
  else ()
    find_package(OpenSSL 1.0.1 REQUIRED)
    set(OPENSSL_VERSION "1.0.1")
  endif ()
endif ()

if (WIN32) # Windows systems including Win64.
  set(Boost_INCLUDE_DIR "../boost_1_67_0/")
  set(CPPRESTSDK_INCLUDE_DIR "../cpprestsdk/")
  #find_package(Threads REQUIRED)

  # message(FATAL_ERROR "-- Windows is not supported for now.")
endif ()


message(MONGOCXX_INCLUDE_DIR " ${MONGOCXX_INCLUDE_DIR}")
message(BSONCXX_INCLUDE_DIR " ${BSONCXX_INCLUDE_DIR}")
set(HEADER_SEARCH_PATHS ${CPPRESTSDK_INCLUDE_DIR} ${Boost_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR} ${BSONCXX_INCLUDE_DIR} ${MONGOCXX_INCLUDE_DIR})

# Configure compiler options ...
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  message("-- configuring clang options")
  set(CMAKE_CXX_FLAGS "-v -arch x86_64 -std=c++17 -stdlib=libc++ -DBOOST_LOG_DYN_LINK -Wno-deprecated-declarations")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  message("-- configuring gcc options")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17 -DBOOST_LOG_DYN_LINK")
endif ()

add_executable(server ./source/main.cpp
  ./source/router.cpp
  ./source/service.cpp
  ./source/util.cpp
  )

# library search paths ...
if (APPLE)
  set(OPENSSL_LIBS "/usr/local/Cellar/openssl/${OPENSSL_VERSION}/lib/libssl.1.0.0.dylib;/usr/local/Cellar/openssl/${OPENSSL_VERSION}/lib/libcrypto.1.0.0.dylib")
  set(CPPRESTSDK_LIBRARY "/usr/local/Cellar/cpprestsdk/2.10.2/lib/libcpprest.2.10.dylib;/usr/local/Cellar/cpprestsdk/2.10.2/lib/libcpprest.dylib")
  set(BSONCXX_LIBRARY "/usr/local/lib/libbsoncxx.dylib")
  set(MONGOCXX_LIBRARY "/usr/local/lib/libmongocxx.dylib")

  set(LIBRARIES_SEARCH_PATHS ${OPENSSL_LIBS} ${Boost_LIBRARIES} ${CPPRESTSDK_LIBRARY} ${BSONCXX_LIBRARY} ${MONGOCXX_LIBRARY})
else ()
  set(OPENSSL_LIBS "${OPENSSL_LIBRARIES}")
  set(CPPRESTSDK_LIBRARY "../cpprestsdk/Release/libcpprest.so")

  set(LIBRARIES_SEARCH_PATHS ${CPPRESTSDK_LIBRARY} ${OPENSSL_LIBS} ${Boost_LIBRARIES})
endif ()

message(BOOST_LIBS " ${Boost_LIBRARIES}")
message(OPENSSL_LIBS " ${OPENSSL_LIBRARIES}")
message(CPPRESTSDK_LIBRARY " ${CPPRESTSDK_LIBRARY}")
message(LIBRARIES_SEARCH_PATHS " ${LIBRARIES_SEARCH_PATHS}")
message(HEADER_SEARCH_PATHS " ${HEADER_SEARCH_PATHS}")
include_directories(${HEADER_SEARCH_PATHS})

if (APPLE)
  target_link_libraries(${PROJECT_NAME} "-framework CoreFoundation")
  target_link_libraries(${PROJECT_NAME} "-framework Security")
  target_link_libraries(${PROJECT_NAME} ${LIBRARIES_SEARCH_PATHS})
  set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-W1, -F/Library/Frameworks")
else ()
  if (UNIX)
    target_link_libraries(${PROJECT_NAME} ${LIBRARIES_SEARCH_PATHS})
  endif ()
endif ()


