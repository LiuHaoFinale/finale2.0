# clog用法

支持`5`种日志级别

```c
enum clog_level {
    CLOG_DEBUG,
    CLOG_INFO,
    CLOG_WARN,
    CLOG_ERROR
};
```

接口定义

```c
void clog_debug(const char *sfile, int sline, int id, const char *fmt, ...);
void clog_info(const char *sfile, int sline, int id, const char *fmt, ...);
void clog_warn(const char *sfile, int sline, int id, const char *fmt, ...);
void clog_error(const char *sfile, int sline, int id, const char *fmt, ...);
```

