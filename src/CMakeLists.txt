add_executable(${PROJECT_NAME} main.cc)

# 特殊目录显式声明（已有独立CMakeLists的目录）
add_subdirectory(XTool)
add_subdirectory(Wheels)

# 自动发现模块函数
function(auto_discover_modules)
    file(GLOB module_dirs LIST_DIRECTORIES true "${CMAKE_CURRENT_SOURCE_DIR}/*")
    
    foreach(module_dir ${module_dirs})
        if(IS_DIRECTORY ${module_dir})
            get_filename_component(module_name ${module_dir} NAME)
            
            # 跳过已显式处理的目录
            if(module_name IN_LIST EXPLICIT_MODULES)
                continue()
            endif()

            # 收集源文件（仅限source目录）
            file(GLOB_RECURSE module_sources
                "${module_dir}/source/*.c"
                "${module_dir}/source/*.cpp"
            )
            
            # 收集头文件（仅限include目录）
            file(GLOB_RECURSE module_headers
                "${module_dir}/include/*.h"
                "${module_dir}/include/*.hpp"
            )

            # 模块存在条件判断
            if(module_sources OR module_headers)
                # 自动判断库类型
                if(module_sources)
                    # 普通库（源码+头文件）
                    add_library(${module_name} ${module_sources})
                    target_include_directories(${module_name} PUBLIC
                        $<BUILD_INTERFACE:${module_dir}/include>
                        $<BUILD_INTERFACE:${module_dir}>
                    )
                    message(STATUS "Found source module: ${module_name}")
                else()
                    # 接口库（纯头文件）
                    add_library(${module_name} INTERFACE)
                    target_include_directories(${module_name} INTERFACE
                        $<BUILD_INTERFACE:${module_dir}/include>
                        $<BUILD_INTERFACE:${module_dir}>
                    )
                    message(STATUS "Found header-only module: ${module_name}")
                endif()

                # 统一链接到主程序
                target_link_libraries(${PROJECT_NAME} PRIVATE ${module_name})
            endif()
        endif()
    endforeach()
endfunction()

# 设置已显式处理的模块列表
set(EXPLICIT_MODULES XTool Wheels)

# 执行自动发现
auto_discover_modules()