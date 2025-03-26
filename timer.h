#ifndef _TIMER_H_
#define _TIMER_H_

#include "main.h"

// „P„u„‚„u„‰„y„ƒ„|„u„~„y„u „„„y„„€„r „„„u„{„ƒ„„„…„‚ „t„|„‘ „„„p„z„}„u„‚„p
typedef enum
{
    TIMER_LABEL = 0,  // "Time: "
    TIMER_DIGITS,      // „X„y„ƒ„|„€„r„€„u „€„„„€„q„‚„p„w„u„~„y„u „r„‚„u„}„u„~„y
    TIMER_MAX
} TIMERTYPE;

// „P„…„„„y „{ „„„u„{„ƒ„„„…„‚„p„} „„„p„z„}„u„‚„p
static const char* TIMER_TEXTURES[TIMER_MAX] =
{
    "data\\TEXTURE\\Time.png",  // „S„u„{„ƒ„„ "Time: "
    "data\\TEXTURE\\Numbers.png"  // „X„y„ƒ„|„p „r„‚„u„}„u„~„y
};

// „R„„„‚„…„{„„„…„‚„p „„„p„z„}„u„‚„p
typedef struct
{
    D3DXVECTOR3 pos;  // „P„€„x„y„ˆ„y„‘ „~„p „„{„‚„p„~„u
    float fWidth;      // „Y„y„‚„y„~„p „„„u„{„ƒ„„„…„‚„
    float fHeight;     // „B„„ƒ„€„„„p „„„u„{„ƒ„„„…„‚„
} TIMER;

// „P„‚„€„„„€„„„y„„ „†„…„~„{„ˆ„y„z
void InitTimer(void);
void UninitTimer(void);
void UpdateTimer(void);
void DrawTimer(void);

#endif
