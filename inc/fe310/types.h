/* See LICENSE file for copyright and license details. */

#ifndef LIBFE310_TYPES_H
#define LIBFE310_TYPES_H

typedef __INT8_TYPE__ s8;
typedef __INT16_TYPE__ s16;
typedef __INT32_TYPE__ s32;
typedef __INT64_TYPE__ s64;
typedef __UINT8_TYPE__ u8;
typedef __UINT16_TYPE__ u16;
typedef __UINT32_TYPE__ u32;
typedef __UINT64_TYPE__ u64;

typedef __SIZE_TYPE__ usize;
typedef __PTRDIFF_TYPE__ ssize;

#ifndef __cplusplus
typedef _Bool bool;
#define true 1
#define false 0
#endif

#endif /* LIBFE310_TYPES_H */
