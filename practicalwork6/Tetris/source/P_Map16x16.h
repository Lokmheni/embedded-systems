
#include <nds.h>

#include "P_Graphics.h"

static u16* mapMemory;
static int  MapCols;
static int  MapRows;

void P_Map16x16_configureBG2();
void P_Map16x16_configureBG2_Sub();
void P_Map16x16_configureBG0();
void P_Map16x16_configureBG3();
void SetMap16x16To(int index16, bool full);