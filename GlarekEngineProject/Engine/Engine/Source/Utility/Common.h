#pragma once
#include "../Math/Vector2.h"

#include <cstdint> // <stdint.h>
#include <cassert>
#include <memory>

#define DLLEXP __declspec(dllexport)
#define V2f Vector2<float>
#define GLUA(...) //...any number of arguments 
//GLUA(Type = Static, DisplayName = DoTheThing)

//ret name args,read backwards , split args by comma, left type and right name
//


// --------------------------------------------------------------------- //
// type defines
// --------------------------------------------------------------------- //

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;

// --------------------------------------------------------------------- //
// magical numbers
// --------------------------------------------------------------------- //
constexpr u32 kPixelsPerMeter = 60;
constexpr f64 kPhyTimestep = 1.0 / 60.0;

// --------------------------------------------------------------------- //
// struct defines
// --------------------------------------------------------------------- //
struct Rect
{
	i32 x;
	i32 y;
	i32 w;
	i32 h;
};

struct Color
{
	u8 red; u8 green; u8 blue; u8 alpha;
};


