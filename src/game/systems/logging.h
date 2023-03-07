#ifndef LOGGING_SYSTEM_H
#define LOGGING_SYSTEM_H

void logging_graphics_process(float delta);
void logging_physics_process(float delta);

#ifdef _WIN32
    #define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
    #define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#ifdef DEBUG
    #define LOG_ERROR(...) { \
        _logging_error("%s:%d:%s(): ",__FILENAME__, __LINE__, __func__);\
        _logging_error(__VA_ARGS__);\
    } 
    #define LOG(...) { \
        _logging_log("%s:%d:%s(): ",__FILENAME__, __LINE__, __func__);\
        _logging_log(__VA_ARGS__);\
    } 
#else
    #define LOG_ERROR(...) { logging_log(__VA_ARGS__); }
    #define LOG(...) { logging_log(__VA_ARGS__); } 
#endif

void _logging_log(const char* string, ...);
void _logging_error(const char* string, ...);

#endif