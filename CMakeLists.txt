cmake_minimum_required (VERSION 2.6)
project( dhcp_lever )

if ( NOT UNIX )
    message ( FATAL_ERROR "It os is not unix" )
endif ()

set( APP_NAME dhcp_lever )

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_VERBOSE_MAKEFILE ON )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-result" )
#set( CMAKE_BUILD_TYPE RELEASE )
#set( CMAKE_BUILD_TYPE DEBUG )

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE RELEASE)
endif()

aux_source_directory( ${CMAKE_CURRENT_SOURCE_DIR}/src SRC )

set( LIBS )

find_package(CURL REQUIRED)
if(CURL_FOUND)
	include_directories(${CURL_INCLUDE_DIR})
	set(LIBS ${LIBS} ${CURL_LIBRARIES} )
else(CURL_FOUND)
	message(fatal_error "Could not find the CURL library and development files.")
endif(CURL_FOUND)


add_executable( ${APP_NAME} ${SRC} )

target_link_libraries( ${APP_NAME}
	${LIBS} )

