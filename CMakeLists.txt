project(ZLToolKit)
cmake_minimum_required(VERSION 3.1.3)

include(CheckStructHasMember)
include(CheckSymbolExists)

list(APPEND CMAKE_REQUIRED_DEFINITIONS -D_GNU_SOURCE)
check_struct_has_member("struct mmsghdr" msg_hdr sys/socket.h HAVE_MMSG_HDR)
check_symbol_exists(sendmmsg sys/socket.h HAVE_SENDMMSG_API)
check_symbol_exists(recvmmsg sys/socket.h HAVE_RECVMMSG_API)

if (HAVE_MMSG_HDR)
    add_definitions(-DHAVE_MMSG_HDR)
endif ()
if (HAVE_SENDMMSG_API)
    add_definitions(-DHAVE_SENDMMSG_API)
endif ()
if (HAVE_RECVMMSG_API)
    add_definitions(-DHAVE_RECVMMSG_API)
endif ()

# check the socket buffer size set by the upper cmake project, if it is set, use the setting of the upper cmake project, otherwise set it to 256K
# if the socket buffer size is set to 0, it means that the socket buffer size is not set, and the kernel default value is used(just for linux)
if (DEFINED SOCKET_DEFAULT_BUF_SIZE)
    if (SOCKET_DEFAULT_BUF_SIZE EQUAL 0)
        message(STATUS "Socket default buffer size is not set, use the kernel default value")
    else ()
        message(STATUS "Socket default buffer size is set to ${SOCKET_DEFAULT_BUF_SIZE}")
    endif ()
    add_definitions(-DSOCKET_DEFAULT_BUF_SIZE=${SOCKET_DEFAULT_BUF_SIZE})
endif ()
#加载自定义模块
#Load custom modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
#设置库文件路径
#Set the library file path
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
#设置可执行程序路径
#Set the executable program path
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#设置子目录
#Set subdirectories
set(SUB_DIR_LIST "Network" "Poller" "Thread" "Util" "Log" "Wheels")

if (WIN32)
    list(APPEND SUB_DIR_LIST "win32")
    #防止Windows.h包含Winsock.h
    #Prevent Windows.h from including Winsock.h
    add_definitions(-DWIN32_LEAN_AND_MEAN)
    if (MSVC)
        add_compile_options("/utf-8")
    endif ()
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
else ()
    add_compile_options("-Wno-comment")
endif ()

#安装目录
#Installation directory
if (WIN32)
    set(INSTALL_PATH_LIB $ENV{HOME}/${PROJECT_NAME}/lib)
    set(INSTALL_PATH_INCLUDE $ENV{HOME}/${PROJECT_NAME}/include)
else ()
    set(INSTALL_PATH_LIB lib)
    set(INSTALL_PATH_INCLUDE include)
endif ()

foreach (SUB_DIR ${SUB_DIR_LIST})
    #遍历源文件
    #Traverse source file
    aux_source_directory(src/${SUB_DIR} SRC_LIST)
    #安装头文件至系统目录
    #Install header file to system directory
    install(DIRECTORY src/${SUB_DIR} DESTINATION ${INSTALL_PATH_INCLUDE} FILES_MATCHING PATTERN "*.h")
endforeach ()

#非苹果平台移除.mm类型的文件
#Remove .mm type files from non-apple platforms
if (NOT APPLE)
    list(REMOVE_ITEM SRC_LIST "src/Network/Socket_ios.mm")
endif ()

if (WIN32)
    set(LINK_LIB_LIST WS2_32 Iphlpapi shlwapi)
else ()
    set(LINK_LIB_LIST)
endif ()


set(ENABLE_OPENSSL ON CACHE BOOL "enable openssl")
set(ENABLE_MYSQL ON CACHE BOOL "enable mysql")
set(ASAN_USE_DELETE OFF CACHE BOOL "use delele[] or free when asan enabled")

#查找openssl是否安装
#Find out if openssl is installed
find_package(OpenSSL QUIET)
if (OPENSSL_FOUND AND ENABLE_OPENSSL)
    message(STATUS "找到openssl库:\"${OPENSSL_INCLUDE_DIR}\",ENABLE_OPENSSL宏已打开")
    include_directories(${OPENSSL_INCLUDE_DIR})
    add_definitions(-DENABLE_OPENSSL)
    list(APPEND LINK_LIB_LIST ${OPENSSL_LIBRARIES})
endif ()

#查找mysql是否安装
#Find out if mysql is installed
find_package(MYSQL QUIET)
if (MYSQL_FOUND AND ENABLE_MYSQL)
    message(STATUS "找到mysqlclient库:\"${MYSQL_INCLUDE_DIR}\",ENABLE_MYSQL宏已打开")
    include_directories(${MYSQL_INCLUDE_DIR})
    include_directories(${MYSQL_INCLUDE_DIR}/mysql)
    add_definitions(-DENABLE_MYSQL)
    list(APPEND LINK_LIB_LIST ${MYSQL_LIBRARIES})
endif ()

#是否使用delete[]替代free，用于解决开启asan后在MacOS上的卡死问题
#use delele[] or free when asan enabled
if (ASAN_USE_DELETE)
    add_definitions(-DASAN_USE_DELETE)
endif ()

#打印库文件
#Print library files
message(STATUS "将链接依赖库:${LINK_LIB_LIST}")
#使能c++11
#Enable c++11
set(CMAKE_CXX_STANDARD 11)

if (NOT WIN32)
    add_compile_options(-Wno-deprecated-declarations)
    add_compile_options(-Wno-predefined-identifier-outside-function)
endif ()

#编译动态库
#Compile dynamic library
if (NOT IOS AND NOT ANDROID AND NOT WIN32)
    add_library(${PROJECT_NAME}_shared SHARED ${SRC_LIST})
    target_include_directories(${PROJECT_NAME}_shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
    target_link_libraries(${PROJECT_NAME}_shared ${LINK_LIB_LIST})
    set_target_properties(${PROJECT_NAME}_shared PROPERTIES OUTPUT_NAME "${PROJECT_NAME}")
    install(TARGETS ${PROJECT_NAME}_shared ARCHIVE DESTINATION ${INSTALL_PATH_LIB} LIBRARY DESTINATION ${INSTALL_PATH_LIB})
endif ()

#编译静态库
#Compile static library
add_library(${PROJECT_NAME}_static STATIC ${SRC_LIST})
#引用头文件路径
#Reference header file path
target_include_directories(${PROJECT_NAME}_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set_target_properties(${PROJECT_NAME}_static PROPERTIES OUTPUT_NAME "${PROJECT_NAME}")
#安装静态库至系统目录
#Install static library to system directory
install(TARGETS ${PROJECT_NAME}_static ARCHIVE DESTINATION ${INSTALL_PATH_LIB})


#测试程序
#Test program
if (NOT IOS)
    add_subdirectory(app)
endif ()