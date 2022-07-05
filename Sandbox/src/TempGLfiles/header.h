#ifndef HEADER_H
#define HEADER_H


#include <stdio.h>
#include <stdint.h>

typedef uint32_t  u32;
typedef int32_t   i32;
typedef uint16_t  u16;
typedef int16_t   i16;
typedef uint8_t   u8;
typedef int8_t    i8;
typedef double    f64;
typedef float     f32;
typedef int32_t   bool;


#pragma warning(push, 3)
#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>
//#include <shellscalingapi.h>
#include "../res/resource.h"
#pragma warning(pop)

// GL Version 4.5
#include "glad/glad.h"

#include "main.h"

#endif // HEADER_H
