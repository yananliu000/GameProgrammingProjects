#ifndef UTILITY_H
#define UTILITY_H

#define GLOBAL_SCALE     1.0f
#define NUM_INTERVALS    20
#define INTERVAL         GLOBAL_SCALE
#define START_HOR_OFFSET (-10.0f*GLOBAL_SCALE)
#define END_HOR_OFFSET   (START_HOR_OFFSET + (NUM_INTERVALS*INTERVAL))
#define START_VER_OFFSET (-10.0f*GLOBAL_SCALE)
#define END_VER_OFFSET   (START_VER_OFFSET + (NUM_INTERVALS*INTERVAL))

//color
typedef struct color_ {
    unsigned char r, g, b, a;
} color;

//rect
typedef struct rect_ {
    float left, top, right, bot;
} rect;

//line
typedef struct line_
{
    float p1x, p1y, p2x, p2y;
} line;

static constexpr color sYellow = { 255,255,0, 255 };
static constexpr color sRed = { 255,0,0, 255 };

static void Clamp(size_t* value, size_t min, size_t max)
{
    if (*value < min)
    {
        *value = min;
    }
    else if (*value > max)
    {
        *value = max;
    }
}

static void Clamp(float* value, float min, float max)
{
    if (*value < min)
    {
        *value = min;
    }
    else if (*value > max)
    {
        *value = max;
    }
}

static size_t Square(size_t A)
{
    return A * A;
}

#endif