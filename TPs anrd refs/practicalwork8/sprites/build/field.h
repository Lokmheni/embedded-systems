
//{{BLOCK(field)

//======================================================================
//
//	field, 256x192@8, 
//	+ palette 253 entries, not compressed
//	+ 769 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x24 
//	Total size: 506 + 49216 + 1536 = 51258
//
//	Time-stamp: 2022-11-13, 21:57:23
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.1
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_FIELD_H
#define GRIT_FIELD_H

#define fieldTilesLen 49216
extern const unsigned int fieldTiles[12304];

#define fieldMapLen 1536
extern const unsigned short fieldMap[768];

#define fieldPalLen 506
extern const unsigned short fieldPal[254];

#endif // GRIT_FIELD_H

//}}BLOCK(field)
