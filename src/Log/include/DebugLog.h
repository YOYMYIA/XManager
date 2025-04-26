#ifndef __DEBUGLOG_H__
#define __DEBUGLOG_H__
#include <stdint.h>
#include <string.h> //strrchr()函数所需头文件
#include <time.h>
#include <sys/time.h>

#define filename(x) strrchr(x,'/')?strrchr(x,'/')+1:x

/*
 * @brief   UTF-8显示
 * @note    颜色显示打印信息到终端
*/

/************************** 用户自定义宏 *********************************/
/**
 * @brief   调试输出总开关
 * @note    处于禁用状态时关闭所有输出
*/
#define DBG_ENABLE          1
/**
 * @brief   是否启用颜色输出
 * @note    如果显示的终端不支持ANSI转义序列，可以将此项设置为0以关闭颜色输出
*/
#define COLOR_ENABLE        1

/**
 * @brief   指定 输出打印等级
 * @note    1. 只会打印当前等级及其以上的等级的信息
 * @note    2. 假设 指定的打印等级 = DBG_LOG_WARNING,
 *          则只会打印 DBG_LOG_WARNING 和 DBG_LOG_ERROR两个等级的信息
*/
#define DBG_LOG_LEVEL  DBG_LOG_DEBUG

/**
 * @brief   输出的等级从高到低的排序: [错误] > [警告] > [普通] > [调试]
*/
#define DBG_LOG_ERROR       1
#define DBG_LOG_WARNING     2
#define DBG_LOG_INFO        3
#define DBG_LOG_DEBUG       4

#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_MAGENTA  "\x1b[35m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_RESET    "\x1b[0m"


#if COLOR_ENABLE
#define PRINT_ANSI_COLOR(...) printf(__VA_ARGS__)
#else
#define PRINT_ANSI_COLOR(...)
#endif


#if DBG_ENABLE
#define DBG_LOG(color, ...) do{                                 \
    struct tm dbg_log_tm;                                       \
    unsigned dbg_log_ms = 0;                                    \
    struct timeval dbg_log_tv;                                  \
    gettimeofday(&dbg_log_tv, NULL);                            \
    time_t t = dbg_log_tv.tv_sec;                               \
    localtime_r(&t, &dbg_log_tm);                               \
    dbg_log_ms = dbg_log_tv.tv_usec / 1000;                     \
    PRINT_ANSI_COLOR(color);                                    \
    printf("[%02d:%02d.%03d]",                                  \
        dbg_log_tm.tm_min, dbg_log_tm.tm_sec, dbg_log_ms);      \
    printf("[%s]", filename(__FILE__));                         \
    printf("[%s]", __func__);                                   \
    printf("[%d]: ", __LINE__);                                 \
    printf(__VA_ARGS__);                                        \
    PRINT_ANSI_COLOR(ANSI_COLOR_RESET);                         \
    printf("\n");                                               \
} while(0)

#if DBG_LOG_LEVEL >= DBG_LOG_DEBUG
#define DBG_LOGD(...) DBG_LOG(ANSI_COLOR_BLUE, __VA_ARGS__);
#else
#define DBG_LOGD(...)
#endif

// [普通]等级控制
#if DBG_LOG_LEVEL >= DBG_LOG_INFO
#define DBG_LOGI(...) DBG_LOG(ANSI_COLOR_GREEN, __VA_ARGS__);
#else
#define DBG_LOGI(...)
#endif

// [警告]等级控制
#if DBG_LOG_LEVEL >= DBG_LOG_WARNING
#define DBG_LOGW(...) DBG_LOG(ANSI_COLOR_YELLOW, __VA_ARGS__);
#else
#define DBG_LOGW(...)
#endif

// [错误]等级控制
#if DBG_LOG_LEVEL >= DBG_LOG_ERROR
#define DBG_LOGE(...) DBG_LOG(ANSI_COLOR_RED, __VA_ARGS__);
#else
#define DBG_LOGE(...)
#endif

#else
#define DBG_LOGD(...)
#define DBG_LOGI(...)
#define DBG_LOGW(...)
#define DBG_LOGE(...)
#endif

/**
 * @brief   自定义打印
 * @note    不受级别控制，用于打印系统开机提示等关键信息
 * @note    第一个参数传入颜色，第二个参数传入需要打印的信息
 * @note    最好传入两个宏以避免警告
*/

#define ADVANCED_LOG(color, ...)\
    PRINT_ANSI_COLOR(color);\
    printf(__VA_ARGS__);\
    PRINT_ANSI_COLOR(ANSI_COLOR_RESET);\
    printf("\n");

/**
 * @brief   以16进制打印数据
 * @param   [in] data   打印的数据数据
 * @param   [in] len    数据长度
 * @note    输出格式 = %02X
*/
void print_hex_table(uint8_t *data, uint16_t len);


#endif








