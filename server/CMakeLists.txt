cmake_minimum_required(VERSION 3.05)
project(server)

# Configure compiler options ...
set(CMAKE_CXX_STANDARD 17)

if (APPLE)
	# headers search paths ...
	set(CPPRESTSDK_INCLUDE_DIR "/usr/local/include")
	set(BOOST_INCLUDE_DIR "/usr/local/Cellar/boost/1.67.0_1")
	set(MONGOCXX_INCLUDE_DIR "/usr/local/include/mongocxx/v_noabi")
	set(BSONCXX_INCLUDE_DIR "/usr/local/include/bsoncxx/v_noabi")
	set(OPENSSL_INCLUDE_DIR "/usr/local/Cellar/openssl/1.0.2p/include")
	set(DOCTEST_INCLUDE_DIR "./doctest/doctest")
endif ()
if (UNIX)
	set(CPPRESTSDK_INCLUDE_DIR "/usr/include")
	set(BOOST_INCLUDE_DIR "/usr/include/boost")
	set(MONGOCXX_INCLUDE_DIR "/usr/local/include/mongocxx/v_noabi")
	set(BSONCXX_INCLUDE_DIR "/usr/local/include/bsoncxx/v_noabi")
	set(OPENSSL_INCLUDE_DIR "/usr/include/openssl")
	set(DOCTEST_INCLUDE_DIR "./doctest/doctest")
endif ()
if (WIN32)
	set(CPPRESTSDK_INCLUDE_DIR "/usr/include")
	set(BOOST_INCLUDE_DIR "/usr/include/boost")
	set(MONGOCXX_INCLUDE_DIR "/usr/local/include/mongocxx/v_noabi")
	set(BSONCXX_INCLUDE_DIR "/usr/local/include/bsoncxx/v_noabi")
	set(OPENSSL_INCLUDE_DIR "/usr/include/openssl")
	set(DOCTEST_INCLUDE_DIR "./doctest/doctest")
endif ()

# Configure required libraries ...
if (UNIX) # Darwing or Linux
  if (APPLE)
    # Prefer a homebrew version of OpenSSL over the one in /usr/lib
    file(GLOB OPENSSL_ROOT_DIR /usr/local/Cellar/openssl/*)
    # Prefer the latest (make the latest one first)
    #list(REVERSE OPENSSL_ROOT_DIR)

    find_package(OpenSSL 1.0.2 REQUIRED)
    set(OPENSSL_VERSION "1.0.2p")
  else ()
    find_package(OpenSSL 1.0.1 REQUIRED)
    set(OPENSSL_VERSION "1.0.1")
  endif ()

  if (APPLE)
    file(GLOB BOOST_ROOT_DIR /usr/local/Cellar/boost/*)
    find_package(Boost 1.67 REQUIRED COMPONENTS thread system log program_options chrono)
    find_package(Threads REQUIRED)
  else ()
    file(GLOB BOOST_ROOT_DIR /usr/include/boost/*)
    find_package(Boost 1.58 REQUIRED COMPONENTS thread system log program_options chrono)
    find_package(Threads REQUIRED)
  endif ()
endif ()

if (WIN32) # Windows systems including Win64.
  set(BOOST_INCLUDE_DIR "../boost_1_67_0/")
  set(CPPRESTSDK_INCLUDE_DIR "../cpprestsdk/")
  #find_package(Threads REQUIRED)

  # message(FATAL_ERROR "-- Windows is not supported for now.")
endif ()

set(CURRENT_DIR "./")
set(HEADER_SEARCH_PATHS ${CPPRESTSDK_INCLUDE_DIR}
                        ${BOOST_INCLUDE_DIR}
                        ${OPENSSL_INCLUDE_DIR}
                        ${BSONCXX_INCLUDE_DIR}
                        ${MONGOCXX_INCLUDE_DIR}
                        ${DOCTEST_INCLUDE_DIR}
                        ${CURRENT_DIR})

# Configure compiler options ...
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  message("-- configuring clang options")
  set(CMAKE_CXX_FLAGS "-v -arch x86_64 -std=c++17 -stdlib=libc++ -DBOOST_LOG_DYN_LINK -Wno-deprecated-declarations")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  message("-- configuring gcc options")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17 -DBOOST_LOG_DYN_LINK")
endif ()



aux_source_directory(./lib SERVER_SOURCE)

add_executable(server ${SERVER_SOURCE})

#add_executable(server_test ./test/source/test.cpp)

# library search paths ...
if (APPLE)
  set(OPENSSL_LIBS "/usr/local/Cellar/openssl/${OPENSSL_VERSION}/lib/libcrypto.dylib;/usr/local/Cellar/openssl/${OPENSSL_VERSION}/lib/libssl.dylib")
  set(CPPRESTSDK_LIBRARY "/usr/local/Cellar/cpprestsdk/2.10.2/lib/libcpprest.2.10.dylib;/usr/local/Cellar/cpprestsdk/2.10.2/lib/libcpprest.dylib")
  set(BSONCXX_LIBRARY "/usr/local/lib/libbsoncxx.dylib")
  set(MONGOCXX_LIBRARY "/usr/local/lib/libmongocxx.dylib")

  set(LIBRARIES_SEARCH_PATHS ${OPENSSL_LIBS} ${Boost_LIBRARIES} ${CPPRESTSDK_LIBRARY} ${BSONCXX_LIBRARY} ${MONGOCXX_LIBRARY})
else ()
  if (UNIX)
    set(OPENSSL_LIBS "${OPENSSL_LIBRARIES}")
    set(CPPRESTSDK_LIBRARY "/usr/lib/x86_64-linux-gnu/libcpprest.so")
    set(BSONCXX_LIBRARY "/usr/local/lib/libbsoncxx.so")
    set(MONGOCXX_LIBRARY "/usr/local/lib/libmongocxx.so")

    set(LIBRARIES_SEARCH_PATHS ${OPENSSL_LIBS} ${Boost_LIBRARIES} ${CPPRESTSDK_LIBRARY} ${BSONCXX_LIBRARY} ${MONGOCXX_LIBRARY})
  endif ()
endif ()

message(Boost_LIBRARIES " ${Boost_LIBRARIES}")
message(HEADER_SEARCH_PATHS " ${HEADER_SEARCH_PATHS}")
message(LIBRARIES_SEARCH_PATHS " ${LIBRARIES_SEARCH_PATHS}")
include_directories(${HEADER_SEARCH_PATHS})

if (APPLE)
  target_link_libraries(${PROJECT_NAME} "-framework CoreFoundation")
  target_link_libraries(${PROJECT_NAME} "-framework Security")
  target_link_libraries(${PROJECT_NAME} ${LIBRARIES_SEARCH_PATHS})
  set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-W1, -F/Library/Frameworks")

  target_link_libraries(server_test "-framework CoreFoundation")
  target_link_libraries(server_test "-framework Security")
  target_link_libraries(server_test ${LIBRARIES_SEARCH_PATHS})
  set_target_properties(server_test PROPERTIES LINK_FLAGS "-W1, -F/Library/Frameworks")
else ()
  if (UNIX)
    target_link_libraries(${PROJECT_NAME} ${LIBRARIES_SEARCH_PATHS})
  endif ()
endif ()


