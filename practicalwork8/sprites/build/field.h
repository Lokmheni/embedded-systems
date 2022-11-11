
//{{BLOCK(field)

//======================================================================
//
//	field, 256x192@8, 
//	+ palette 256 entries, not compressed
//	+ 769 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x24 
//	Total size: 512 + 49216 + 1536 = 51264
//
//	Time-stamp: 2020-08-19, 13:05:52
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_FIELD_H
#define GRIT_FIELD_H

#define fieldTilesLen 49216
extern const unsigned int fieldTiles[12304];

#define fieldMapLen 1536
extern const unsigned short fieldMap[768];

#define fieldPalLen 512
extern const unsigned short fieldPal[256];

#endif // GRIT_FIELD_H

//}}BLOCK(field)
