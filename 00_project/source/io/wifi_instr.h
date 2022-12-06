/**
 * @file wifi_instr.h
 * @author Simon Thür
 * @brief Defines for instructions to be sent over wifi
 * @version 0.1
 * @date 2022-12-06
 *
 * @copyright Copyright (c) 2022
 *
 */


#ifndef __WIFI_INSTR_H
#define __WIFI_INSTR_H

#include <nds.h>

// WIFI_SYNC_INSTR_SCORE DAT1 VALUES
#define START_GAME    ( ( u8 ) ( 1 << 0 ) )
#define IS_PLAY       ( ( u8 ) ( 1 << 1 ) )  // PLAY PAUSE (TOGGLE INPUT)
#define SET_STAGE     ( ( u8 ) ( 1 << 2 ) )
#define RESET_GAME    ( ( u8 ) ( 1 << 3 ) )  // IMPLIES SET STAGE, RESET SCORES
#define END_ROUND     ( ( u8 ) ( 1 << 4 ) )
#define WINNER_REMOTE ( ( u8 ) ( 1 << 5 ) )  // IIF END_ROUND
#define END_GAME      ( ( u8 ) ( 1 << 6 ) )  // EXIT AND DISCONNECT WIFI
#define REQ_ACK       ( ( u8 ) ( 1 << 7 ) )


#endif  // __WIFI_INSTR_H
