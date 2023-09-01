#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_

#include "stdbool.h"
#include "stdint.h"

#ifndef _Bool
#define _Bool unsigned char
#endif

#define CPU_TYPE CPU_TYPE_32
#define cpu_BIT_ORDER MSB_FIRST
#define cpu_BYTE_ORDER HIGH_BYTE_FIRST

#ifndef FASLE
#define FALSE (boolean)false
#endif

#ifndef TRUE
#define TRUE (boolean)true
#endif

typedef _Bool 				boolean;
typedef signed char 		sint8;
typedef unsigned char 		uint8;
typedef char 				char_t;
typedef short 				sint16;
typedef unsigned short 		uint16;
typedef int 				sint32;
typedef unsigned 			uint32;
typedef long long 			sint64;
typedef unsigned long long 	uint64;


typedef volatile signed char 		vint8_t;
typedef volatile unsigned char 		vuint8_t;

typedef volatile short 				vint16_t;
typedef volatile unsigned short 	vuint16_t;

typedef volatile int 				vint32_t;
typedef volatile unsigned 			vuint32_t;

typedef volatile long 				vint64_t;
typedef volatile long long 			vuint64_t;

#endif /* PLATFORM_TYPES_H_ */
