
@{{BLOCK(mario)

@=======================================================================
@
@	mario, 32x32@4, 
@	+ palette 256 entries, not compressed
@	+ 16 tiles not compressed
@	Total size: 512 + 512 = 1024
@
@	Time-stamp: 2020-12-11, 14:42:19
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global marioTiles		@ 512 unsigned chars
marioTiles:
	.word 0x99999999,0x99999999,0xC9999999,0x9C999999,0x23C99999,0xB2AC9999,0x6623C999,0x66B29C99
	.word 0x324CCC99,0xBB22E9C9,0x6666221C,0x2B66662E,0x2326666B,0xC5B26666,0xC6C52666,0xA2154B66
	.word 0x99CCC433,0x9CCF22BB,0xCA226666,0xA26666B2,0x2666B234,0x66662BCC,0x66625C65,0x66B4522A
	.word 0x99999999,0x99999999,0x9999999C,0x999999CC,0x99999CD2,0x9999CB2B,0x999CD2B6,0x99CC2B66
	.word 0x666B0C99,0x666626C9,0x6666629C,0x6666627C,0x6666662C,0x66666625,0x2B666624,0x5EB66624
	.word 0x2D2C3266,0xF92F7266,0xCCB6A266,0x9CE3FB66,0xCCC222B6,0xECFECBA2,0xBB2222CA,0x6666622E
	.word 0x6629C2D2,0x662BF298,0x662A6BCC,0x66BFF8C9,0x6B220CCC,0x2ABCEFC6,0xA52222BB,0xB2266666
	.word 0x99C4B666,0x9C926666,0xC9266666,0xC8266666,0xC2666666,0x12666666,0xA26666B2,0x12666BEC

	.word 0xD5EB6625,0x2DC6BB65,0x225C22BC,0xDCCCBBC9,0xC999CC99,0x59999999,0xD5999999,0x00599999
	.word 0x2222B662,0xCC5262B6,0x9CCCC532,0x99999CCC,0x99999999,0x99999999,0x99999995,0x99999954
	.word 0x266B2222,0x6B2E15CC,0x235CCCC9,0xCCC99999,0x99999999,0x99999999,0x59999999,0x45999999
	.word 0x3266B65D,0x5EBBECA2,0xCB22C522,0x9CBECCCD,0x99CC999C,0x99999995,0x9999995D,0x99999500
	.word 0xD1599999,0x79599999,0x2C599999,0x05599999,0x55999999,0x59999999,0x99999999,0x99999999
	.word 0x99995587,0x95555377,0x59847A7C,0x977A7CCD,0x77CCCC27,0x2CCC9A78,0xBA7713B5,0x95505559
	.word 0x78559999,0x77C55559,0xC7A7F895,0xDCC7A779,0x72CCCC77,0x87A9CCC2,0x5B3177AB,0x95550059
	.word 0x99999512,0x99999597,0x999995C2,0x99999550,0x99999955,0x99999995,0x99999999,0x99999999

	.section .rodata
	.align	2
	.global marioPal		@ 512 unsigned chars
marioPal:
	.hword 0x0000,0x4632,0x001C,0x6B5E,0x18BC,0x1D09,0x41FD,0x569D
	.hword 0x295D,0x77BD,0x0423,0x041C,0x7FFE,0x56B5,0x0C5C,0x2D8C
	.hword 0x0C85,0x5EFD,0x39DD,0x20FD,0x4A3D,0x7FFF,0x081C,0x0844
	.hword 0x5EF8,0x0002,0x631D,0x35CE,0x254B,0x739E,0x083C,0x529D
	.hword 0x107C,0x14A6,0x7BBE,0x251D,0x4A53,0x673E,0x18DC,0x0001
	.hword 0x2D7D,0x7BDE,0x4A5D,0x6F7E,0x0C65,0x0443,0x5ADE,0x147C
	.hword 0x5AD6,0x3DFD,0x253D,0x461D,0x4E5D,0x631E,0x0C3C,0x319D
	.hword 0x4E73,0x0422,0x18BD,0x1086,0x0864,0x1CDD,0x56BD,0x317D

	.hword 0x4A52,0x3DDD,0x0843,0x107D,0x149C,0x6318,0x0C5D,0x14A7
	.hword 0x39CF,0x463D,0x5EFE,0x56BE,0x147D,0x293D,0x2D5D,0x421D
	.hword 0x77DE,0x4E7D,0x4A3E,0x294B,0x318D,0x1085,0x1CDC,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(mario)