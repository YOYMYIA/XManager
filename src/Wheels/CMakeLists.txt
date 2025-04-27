function(process_tools)
    file(GLOB tool_dirs LIST_DIRECTORIES true "${CMAKE_CURRENT_SOURCE_DIR}/*")
    foreach(tool_dir ${tool_dirs})
        if(IS_DIRECTORY ${tool_dir})
            get_filename_component(tool_name ${tool_dir} NAME)
            
            file(GLOB_RECURSE TOOL_SOURCES
                "${tool_dir}/source/*.c"
                "${tool_dir}/source/*.cpp"
                "${tool_dir}/*.c"
                "${tool_dir}/*.cpp"

            )
            
            file(GLOB_RECURSE TOOL_HEADERS
                "${tool_dir}/include/*.h"
                "${tool_dir}/include/*.hpp"
                "${tool_dir}/*.h"
                "${tool_dir}/*.hpp"
            )
            
            if(TOOL_SOURCES OR TOOL_HEADERS)
                # 区分普通库和INTERFACE库
                if(TOOL_SOURCES)
                    # 普通库
                    add_library(${tool_name} ${TOOL_SOURCES} ${TOOL_HEADERS})
                    target_include_directories(${tool_name} PUBLIC
                        ${tool_dir}/include
                        ${tool_dir}
                    )
                    else()
                    # 纯头文件库
                    add_library(${tool_name} INTERFACE)  #  关键修复：使用INTERFACE类型
                    target_include_directories(${tool_name} INTERFACE
                        ${tool_dir}/include
                        ${tool_dir}
                    )
                    target_sources(${tool_name} INTERFACE ${TOOL_HEADERS})
                endif()
                
                # 链接到主程序
                target_link_libraries(${PROJECT_NAME} PRIVATE ${tool_name})
            endif()
        endif()
    endforeach()
endfunction()

process_tools()