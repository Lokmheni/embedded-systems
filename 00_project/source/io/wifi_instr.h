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


// WIFI_SYNC_INSTR_SCORE DAT1 VALUES
#define START_GAME    ((u8)(1 << 0)) /*!< NOT USED, PREFER IS_PLAY */
#define IS_PLAY       ((u8)(1 << 1)) /*!< PLAY PAUSE (TOGGLE INPUT) */
#define SET_STAGE     ((u8)(1 << 2)) /*!< RESET PLAYER POSITIONS AND HEALTH */
#define RESET_GAME    ((u8)(1 << 3)) /*!< IMPLIES SET STAGE, RESET SCORES */
#define END_ROUND     ((u8)(1 << 4)) /*!< END ROUND, IMPLIES (~IS_PLAY) */
#define WINNER_REMOTE ((u8)(1 << 5)) /*!< IIF END_ROUND||END_GAME */
#define END_GAME      ((u8)(1 << 6)) /*!< EXIT AND DISCONNECT WIFI */
#define REQ_ACK       ((u8)(1 << 7)) /*!< REQUEST ACKNOWLEDGE FOR MSG */


#endif // __WIFI_INSTR_H
