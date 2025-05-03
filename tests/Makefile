vpath %.c 
vpath %.cc 
vpath %.cpp 
vpath %.h 
vpath %.hh 
vpath %.hpp 

.PHONY: clean rebuild do

 #-I/usr/include/GL
SRCS := $(wildcard ./*.c) $(wildcard ./*.cc) $(wildcard ./*.cpp)  # 所有源文件
OBJS := $(patsubst ./%.c, ./bin/%.o, $(SRCS))
OBJS := $(patsubst ./%.cc, ./bin/%.o, $(OBJS))
OBJS := $(patsubst ./%.cpp, ./bin/%.o, $(OBJS))

CC := g++
COM_OP := -Wall -g
THREAD := -lpthread
MYSQL := -lmysqlclient
LOG4CPP := -llog4cpp
WORKFLOW := -lworkflow
HASHLIB := -lssl -lcrypto
LGLUT := -lglut
RMOPT := -fno-elide-constructors
OPENGL := -lGL -lGLU -lglfw
HIREDIS := -lhiredis

ALL_LINK := $(COM_OP) $(THREAD) #$(MYSQL) $(LOG4CPP) $(WORKFLOW) $(HIREDIS)

# 生成 .o 文件的规则
./bin/%.o : ./%.c
	@mkdir -p ./bin  # 确保 bin 目录存在
	$(CC) $(COM_OP) -c $< -o $@

./bin/%.o : ./%.cc
	@mkdir -p ./bin  # 确保 bin 目录存在
	$(CC)  $(COM_OP) -c $< -o $@

./bin/%.o : ./%.cpp
	@mkdir -p ./bin  # 确保 bin 目录存在
	$(CC) $(COM_OP) -c $< -o $@

# 链接生成主程序
./bin/test.exe: $(OBJS)
	$(CC) $(OBJS) -o $@ $(ALL_LINK)

# 清理编译生成的文件
do:
	./bin/test.exe

clean:
	$(RM) ./bin/*.o test.exe

rebuild: clean ./bin/test.exe

