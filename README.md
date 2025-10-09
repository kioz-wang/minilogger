# Minimal Logger

> MIT License Copyright (c) 2025 kioz.wang

# Description

最通用、最迷你的日志框架。可用于 `C`, `C++`。

## Test and Run

```shell
$ rm *.gch
$ gcc -D__TEST_LOGGER__ -D__LOGGER_ENV__=\"log2stderr\" *.[ch]
$ ./a.out 
message level ERROR
message level WARNING
message level INFO
$ log2stderr=DEBUG ./a.out 
message level ERROR
message level ERROR
message level WARNING
message level WARNING
message level INFO
message level INFO
message level VERBOSE
message level DEBUG
```

## Build as library

If you want, just do it.

## Build with your source codes

This is a best practice.

# API

## `log_level_t`, `logger_f`

```c
enum log_level {
  LOG_ERROR,
  LOG_WARNING,
  LOG_INFO,
  LOG_VERBOSE,
  LOG_DEBUG,
};
typedef uint8_t log_level_t;

typedef void (*logger_f)(const char *msg);
```

仅使用两个全局变量：
- 日志等级：`g_log_level`，默认为 `LOG_DEBUG`
- 输出函数：`g_logger`，默认为 `fputs(msg, stdout)`

## `__LOGGER_FUNC__(logger)`

```c
void logger(log_level_t lvl, const char *fmt, ...);
```

当 `lvl` 大于等于 `g_log_level` 时，调用 `g_logger` 输出格式化消息。

宏函数 `logfE/W/I/V/D` 是省略了 `lvl` 的写法。

## `__LOGGER_FUNC__(set_logger)`

```c
void set_logger(log_level_t lvl, logger_f f);
```

修改全局变量。`lvl` 具有防呆设计；`f` 传入 `NULL` 时，不更新 `g_logger`。

# Configuration

## `__LOGGER_PREFIX__`

为避免移植时出现符号冲突（像`logger`这种名字太常见了），可以配置该宏。

> 默认值为 `_`

## `__LOGGER_FUNC__`

宏函数，用于将 `__LOGGER_PREFIX__` 拼接在符号名前。

## `__LOGGER_FMT_MAX__`

在函数栈内存中完成消息格式化，该宏指定了占用栈内存的大小。

> 默认值为 `1024`

## `__LOGGER_ENV__`

这个宏指定了一个环境变量，`__LOGGER_FUNC__(logger)` 将读取这个环境变量，并翻译为 `log_level_t stderr_level`。

在 `__LOGGER_FUNC__(logger)` 中，当 `lvl` 大于等于 `stderr_level` 时，调用 `fputs(line, stderr)` 输出格式化消息。

### 翻译规则

单词

`"ERROR", "WARNING", "INFO", "VERBOSE", "DEBUG"` 依次对应 `log_level_t` 枚举值。不匹配的单词将按照数字翻译。

数字

- 自动推断进制
- 按数值大小一一映射到 `log_level_t` 枚举值。
- 非法数字将映射到 `LOG_DEBUG`
- 过大的数字将映射到 `LOG_DEBUG`
