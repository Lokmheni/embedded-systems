
//{{BLOCK(paysage)

//======================================================================
//
//	paysage, 256x192@8, 
//	+ palette 256 entries, not compressed
//	+ 763 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x24 
//	Total size: 512 + 48832 + 1536 = 50880
//
//	Time-stamp: 2022-12-06, 19:12:32
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_PAYSAGE_H
#define GRIT_PAYSAGE_H

#define paysageTilesLen 48832
extern const unsigned int paysageTiles[12208];

#define paysageMapLen 1536
extern const unsigned short paysageMap[768];

#define paysagePalLen 512
extern const unsigned short paysagePal[256];

#endif // GRIT_PAYSAGE_H

//}}BLOCK(paysage)
