#ifndef __control_H
#define __control_H
#include "main.h"
//=============================
#define TMUX1208_A0   PBout(8)
#define TMUX1208_A1   PBout(9)
#define TMUX1208_A2   PBout(10)
#define TMUX1208_EN1  PBout(11)
#define LED   PCout(4)//DIR
#define MLED  PAout(11)//DIR
//=====================================
void Start(void);
void Reset(void);
//================================================================
void GET_RESULT(void);
void RF_TEST(void);
void PC_state(void);
void Help(void);
void Fixture_Information(void);

#endif
