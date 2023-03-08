//
// Created by luxshare-ict on 2023/3/6.
//
#include "string.h"
#include "control.h"
#include "stdio.h"

void CmdCheck(char *cmd){
    if(strcmp(cmd,"HELP")==0){Help();return;}
    else if(strcmp(cmd,"START_TEST")==0){Start();return;}
    else if(strcmp(cmd,"GET_RESULT")==0){GET_RESULT();return;}
    else if(strcmp(cmd,"RF_START_TEST")==0){RF_TEST();return;}
    else if(strcmp(cmd,"END_TEST")==0){Reset();return;}
    else if(strcmp(cmd,"PC_READY")==0){PC_state();return;}
    else{ printf("Command Error\r\n");return;}
}