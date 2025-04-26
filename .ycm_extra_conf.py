import os
import ycm_core

# 新增函数：递归查找父目录中的 include 路径
def find_parent_includes(filepath):
    include_paths = []
    current_dir = os.path.dirname(os.path.abspath(filepath))
    
    # 向上查找最多 10 层父目录
    max_depth = 10  
    for _ in range(max_depth):
        parent_include = os.path.join(current_dir, 'include')
        if os.path.exists(parent_include):
            include_paths.append('-I' + parent_include)
        
        # 向上一级目录
        parent_dir = os.path.dirname(current_dir)
        if parent_dir == current_dir:
            break  # 到达根目录
        current_dir = parent_dir
    
    return include_paths

# 修改后的 flags 生成逻辑
def get_dynamic_flags(filename):
    # 保留原有静态 flags
    base_flags = [
        '-Wall',
        '-Wextra',
        '-Wno-long-long',
        '-Wno-variadic-macros',
        '-fexceptions',
        '-DNDEBUG',
        '-DUSE_CLANG_COMPLETER',
        '-std=c++17',
        '-x',
        'c++',
        '-isystem',
        '/usr/include',
        '-isystem',
        '/usr/include/c++/11',
        '-isystem',
        '/usr/include/x86_64-linux-gnu',
        '-isystem',
        '/usr/include/linux',
        '-isystem',
        '/usr/local/include',
    ]
    
    # 动态添加父目录 include 路径
    dynamic_includes = find_parent_includes(filename)
    
    # 合并并去重（保持顺序）
    seen = set()
    final_flags = []
    
    # 优先动态路径
    for flag in dynamic_includes + base_flags:
        if flag not in seen:
            seen.add(flag)
            final_flags.append(flag)
    
    return final_flags

# 修改 FlagsForFile 函数
def FlagsForFile(filename, **kwargs):
    # 如果存在编译数据库，优先使用
    if database:
        compilation_info = GetCompilationInfoForFile(filename)
        if compilation_info:
            final_flags = list(compilation_info.compiler_flags_)
            
            # 合并动态路径
            dynamic_flags = find_parent_includes(filename)
            final_flags = dynamic_flags + [
                flag for flag in final_flags 
                if flag not in dynamic_flags
            ]
            
            return {
                'flags': final_flags,
                'include_paths_relative_to_dir': 
                    compilation_info.compiler_working_dir_
            }
    
    # 无编译数据库时使用动态生成的 flags
    return {
        'flags': get_dynamic_flags(filename),
        'include_paths_relative_to_dir': os.path.dirname(os.path.abspath(filename))
    }

# 以下保持原有代码不变
SOURCE_EXTENSIONS = [ '.cpp', '.cxx', '.cc', '.c', '.m', '.mm' ]

def DirectoryOfThisScript():
    return os.path.dirname(os.path.abspath(__file__))

def IsHeaderFile(filename):
    extension = os.path.splitext(filename)[1]
    return extension in ['.h', '.hxx', '.hpp', '.hh']

def GetCompilationInfoForFile(filename):
    if IsHeaderFile(filename):
        basename = os.path.splitext(filename)[0]
        for extension in SOURCE_EXTENSIONS:
            replacement_file = basename + extension
            if os.path.exists(replacement_file):
                compilation_info = database.GetCompilationInfoForFile(replacement_file)
                if compilation_info.compiler_flags_:
                    return compilation_info
        return None
    return database.GetCompilationInfoForFile(filename)

compilation_database_folder = ''
if os.path.exists(compilation_database_folder):
    database = ycm_core.CompilationDatabase(compilation_database_folder)
else:
    database = None  
