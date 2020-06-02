#ifndef RPILIB_TYPE_STDIN
#define RPILIB_TYPE_STDIN

/*
 *  コンパイラ依存のデータ型の定義
 */


typedef signed char			int8_t;		/* 符号付き8ビット整数 */
typedef unsigned char		uint8_t;	/* 符号無し8ビット整数 */

typedef signed short		int16_t;	/* 符号付き16ビット整数 */
typedef unsigned short		uint16_t;	/* 符号無し16ビット整数 */

typedef signed int			int32_t;	/* 符号付き32ビット整数 */
typedef unsigned int		uint32_t;	/* 符号無し32ビット整数 */

typedef signed long long	int64_t;	/* 符号付き64ビット整数 */
typedef unsigned long long	uint64_t;	/* 符号無し64ビット整数 */

typedef int8_t				int_least8_t;	/* 8ビット以上の符号付き整数 */
typedef uint8_t				uint_least8_t;	/* 8ビット以上の符号無し整数 */

typedef long				intptr_t;	/* ポインタを格納できる符号付き整数 */
typedef unsigned long		uintptr_t;	/* ポインタを格納できる符号無し整数 */


#endif
