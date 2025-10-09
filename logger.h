/**
 * @file logger.h
 * @author kioz.wang
 * @brief
 * @version 0.1
 * @date 2025-10-09
 *
 * @copyright MIT License
 *
 *  Copyright (c) 2025 kioz.wang
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdint.h>

#ifndef __LOGGER_PREFIX__
#define __LOGGER_PREFIX__ _
#endif
#define __SYMBOL_CONCAT__(a, b) a##b
#define ____LOGGER_FUNC__(prefix, name) __SYMBOL_CONCAT__(prefix, name)
#define __LOGGER_FUNC__(name) ____LOGGER_FUNC__(__LOGGER_PREFIX__, name)

#ifdef __cplusplus
extern "C" {
#endif

enum log_level {
  LOG_ERROR,
  LOG_WARNING,
  LOG_INFO,
  LOG_VERBOSE,
  LOG_DEBUG,
};
typedef uint8_t log_level_t;

typedef void (*logger_f)(const char *msg);

void __LOGGER_FUNC__(logger)(log_level_t lvl, const char *fmt, ...) __attribute__((format(printf, 2, 3)));
void __LOGGER_FUNC__(set_logger)(log_level_t lvl, logger_f f);

#define logfE(fmt, ...) __LOGGER_FUNC__(logger)(LOG_ERROR, fmt "\n", ##__VA_ARGS__)
#define logfW(fmt, ...) __LOGGER_FUNC__(logger)(LOG_WARNING, fmt "\n", ##__VA_ARGS__)
#define logfI(fmt, ...) __LOGGER_FUNC__(logger)(LOG_INFO, fmt "\n", ##__VA_ARGS__)
#define logfV(fmt, ...) __LOGGER_FUNC__(logger)(LOG_VERBOSE, fmt "\n", ##__VA_ARGS__)
#define logfD(fmt, ...) __LOGGER_FUNC__(logger)(LOG_DEBUG, fmt "\n", ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif /* __LOGGER_H__ */
