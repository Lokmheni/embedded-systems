
@{{BLOCK(player)

@=======================================================================
@
@	player, 32x32@8, 
@	Transparent color : 00,FF,00
@	+ palette 256 entries, not compressed
@	+ 16 tiles not compressed
@	Total size: 512 + 1024 = 1536
@
@	Time-stamp: 2022-12-06, 19:12:32
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global playerTiles		@ 1024 unsigned chars
playerTiles:
	.word 0x2D2D2D2D,0x2D2D2D2D,0x2D2D2D2D,0x2D2D2D2D,0x2D2D2D2D,0x2D2D2D2D,0x2D2D2D2D,0x4C2B2B2D
	.word 0x4C652D1E,0x8B99993D,0x87A94545,0x80837C51,0x15BC2B2D,0xA3646492,0x301E2D2D,0xFC3F497E
	.word 0x45452D09,0x562B4F2D,0x2D454545,0x8C312BA0,0x964F4F4F,0x1947B37A,0x624545A0,0xD179B1AD
	.word 0x74228623,0xCDEDECDA,0xD5D57687,0xEA5B1A7F,0x282BA8D1,0xE283935E,0xCCF0E1C8,0xF8AA85E8
	.word 0x25CAD82D,0x28562B16,0x5C5C4A4B,0xA0986CBA,0x8959187D,0xBB918210,0x79C971B4,0x4FF04057
	.word 0x30600B0B,0x1E2BA02F,0xE5FD6AEA,0x2D094F5E,0xAF4BA604,0x2876465E,0xC5D735D4,0x2D54253B
	.word 0x2D2D2D28,0x2D2D2D2D,0x2D2D2D2D,0x2D2D2D2D,0x2D2D2D45,0x2D2D2D2D,0x2D2D2D2D,0x2D2D2D2D
	.word 0x2D2D2D2D,0x2D2D2D2D,0x2D2D2D2D,0x2D2D2D2D,0x2D2D2D2D,0x2D2D2D2D,0x2D2D2D56,0x2D2D2D2D

	.word 0x33962D2D,0xB2A18DEA,0x482B2D2D,0xED43144E,0x45282D2D,0x44C2BF7C,0x2B652D16,0x17AEBEF5
	.word 0x2D2D2D2D,0xE858962D,0x2D2D2D2D,0x769A864F,0x2D2D2D2D,0x4F2BA73D,0x2D2D2D2D,0x4C2B2B23
	.word 0xD0BEC3E4,0x5D632736,0xB2B2C2ED,0xC4857CAC,0x925BA3C2,0x2B2B1EF1,0x749CBFF9,0x4F4FF276
	.word 0x9F1B6955,0xC1B0E097,0xA79A659A,0x0E0C050A,0x682B2B1F,0xB52BEFEB,0x553D3D3D,0x942D1D00
	.word 0x0F4E379E,0xABE6348B,0x62EEE542,0x6732306D,0x77CFD652,0x6A3FC36F,0x4139FA53,0x81C873AA
	.word 0xBC42B097,0xAECB30B7,0x50864F26,0x933B5E3D,0x8B8B2B95,0x2B4C65E9,0xE9862B0C,0x2D4FDEF6
	.word 0x282D2D2B,0x2D2D2D28,0x2D2D2B2E,0x2D2D2D2D,0x2D96AB27,0x452D2D2D,0x16966E3A,0x452D2D2D
	.word 0x2D2B6BDC,0x2D2D2D2D,0x2D2D2B3B,0x2D2D2D2D,0x2D2D2D2B,0x2D2D2D2D,0x2D2D2D2D,0x2D2D2D2D

	.word 0x232D2D2D,0x2B2B2B2D,0x2D232B2D,0x2B2B2B2B,0x2B3D3D2B,0x2B2B2B2B,0x2B2B232D,0x2B2B2B2B
	.word 0x2D2D23A9,0x2B2B2B2B,0x9AA78B4C,0x768B869A,0x761F2D2D,0x9AFA86F7,0x76A72B2D,0x88503D2B
	.word 0x552D2B2B,0x1D2338EB,0x992D2B2B,0x2BA70654,0x23284C2B,0x8B704C1F,0x784F4C4C,0x9A4C4C76
	.word 0x763C7628,0x3D2D2D4C,0x2B707886,0x2B2D2D28,0x2D9A9AE3,0x2D2D2D2D,0x868B4F88,0x2D2D2D28
	.word 0x4F2BB9FE,0x4CDE669B,0x4C2BB9C4,0x86016653,0x2B2B2B2B,0x789DF74C,0x2B2B2BD8,0x50F2032B
	.word 0x2B2B0DA4,0x2B2B2B2B,0x4C8BE976,0x2B2B2B2B,0x9AB0994C,0x2B284F8B,0x0876282D,0x2B4F768B
	.word 0x2D2D2D2D,0x2D2D2D2D,0x2D2D2D2B,0x2D2D2D2D,0x2D2D2D1F,0x2D2D2D2D,0x2D2D2DC1,0x2D2D2D2D
	.word 0x2D2B42A7,0x2D2D2D2D,0x2D990688,0x2D2D2D2D,0x8676863D,0x2D282D28,0x3D2B3D2D,0x2D2D2823

	.word 0x58CA4C65,0x962B4C28,0x2D454528,0x2E23C676,0x28454545,0x04454C28,0x2D2D2D4C,0x84CE254C
	.word 0x962D282D,0xFB2C217B,0x2B282D45,0x2AB6367B,0x282D2D45,0x98BC2D2B,0x282D2D45,0x4C2B282D
	.word 0x5FB72B2B,0x452D4F2B,0x2ADF32B8,0x452D96C7,0x8A3EA28E,0x2828CA90,0xDB723E8A,0xA92D3B8F
	.word 0xC092A5FF,0x2D2D2BBB,0x451E7FD0,0x2D2D2D28,0x2D2D2B2B,0x2D2D2D28,0x2DA04F2D,0x2D2D2D2D
	.word 0x2D2B2D45,0x2B2D3D23,0x2D2D2D2D,0x3D3D3D2D,0x2D2D2D2D,0x2B2D2D2D,0x2D2D2D2D,0x2B2D2D2D
	.word 0x2D2D2D2D,0x2B2D2D2D,0x2D2D2D2D,0x2B2D2D2D,0x2D2D2D2D,0x2D2D2D2D,0x2D2D2D2D,0x2D2D2D2D
	.word 0x742B4C4C,0x452D4C23,0x29AE1398,0x2D4F20BA,0xBD122CF3,0x4F961107,0xBDDD1CD9,0x2816905A
	.word 0xD324C3F5,0x45337ED3,0x2975C54D,0x5661E102,0x2EF4D22D,0x283DE77F,0x2B2B4C2D,0x2D2D2B2B

	.section .rodata
	.align	2
	.global playerPal		@ 512 unsigned chars
playerPal:
	.hword 0x0842,0x6736,0x2E16,0x73BB,0x4AB8,0x2529,0x56B4,0x3238
	.hword 0x6B79,0x7BFD,0x35AD,0x42BD,0x4611,0x77DC,0x20E7,0x56B9
	.hword 0x2993,0x5B3B,0x367C,0x637D,0x46BC,0x4235,0x77DE,0x4278
	.hword 0x1D31,0x14AC,0x56FC,0x5EF5,0x42BA,0x39CE,0x77DF,0x6739
	.hword 0x77FF,0x3614,0x737A,0x739C,0x46FE,0x73BD,0x4E72,0x4675
	.hword 0x7FDE,0x3637,0x3E78,0x7FFF,0x29F6,0x7BDE,0x633B,0x5B19
	.hword 0x52DA,0x56D6,0x429A,0x5B1B,0x52D6,0x212C,0x4676,0x190C
	.hword 0x18C6,0x637A,0x298E,0x6B7C,0x6B39,0x77BD,0x3ABF,0x3A7A

	.hword 0x35D2,0x6338,0x6318,0x4ADE,0x4EDC,0x7BDF,0x6B7A,0x2530
	.hword 0x633C,0x429C,0x4A98,0x3E14,0x7FFE,0x6B7D,0x35F5,0x7BDD
	.hword 0x7BBD,0x4A76,0x7B9A,0x7BBB,0x5294,0x5EF7,0x7FDF,0x2D92
	.hword 0x6B7B,0x14F0,0x3EDD,0x46BB,0x4EB8,0x10C8,0x739D,0x56D8
	.hword 0x571F,0x52B8,0x631C,0x256D,0x531F,0x7FDD,0x6B56,0x4678
	.hword 0x6B3A,0x5F17,0x3A57,0x6319,0x56F9,0x77BE,0x4233,0x4E95
	.hword 0x737B,0x4A9B,0x3A9F,0x52DC,0x673A,0x3635,0x77BC,0x6B9C
	.hword 0x6738,0x31B4,0x6F7E,0x675B,0x4256,0x14CE,0x3E9A,0x675C

	.hword 0x4A97,0x4698,0x2971,0x4677,0x3A79,0x3DF1,0x6F7A,0x5AD8
	.hword 0x779C,0x2153,0x42DE,0x739B,0x294D,0x3659,0x2617,0x4EDB
	.hword 0x46B9,0x31B0,0x4ABB,0x5F3B,0x0C64,0x3DEF,0x7BFF,0x6316
	.hword 0x6F9D,0x6F7B,0x6B59,0x6F57,0x4ED8,0x6F9A,0x18E9,0x5AD4
	.hword 0x7BFE,0x3E7B,0x327D,0x4ADC,0x6758,0x3E59,0x3E35,0x6B5A
	.hword 0x5AF9,0x7BBE,0x4A75,0x631A,0x469A,0x3195,0x4ABA,0x5F1B
	.hword 0x6317,0x108D,0x4EFE,0x4E79,0x3A36,0x294A,0x3E77,0x5F1A
	.hword 0x4EFA,0x675A,0x52D9,0x73BE,0x6F7C,0x3EDF,0x4AB9,0x4699

	.hword 0x635D,0x62F7,0x4EFD,0x4ADB,0x4A73,0x4A77,0x7BBC,0x679D
	.hword 0x4ADD,0x35F6,0x6F9C,0x52FC,0x779D,0x4279,0x4697,0x56F8
	.hword 0x4EB9,0x3A35,0x6B5B,0x3EDE,0x39F2,0x779B,0x6759,0x254E
	.hword 0x73BC,0x6B9D,0x5AFA,0x42BE,0x254C,0x46FF,0x6F78,0x429B
	.hword 0x6717,0x3615,0x4257,0x6F5A,0x531E,0x56D9,0x4275,0x6B5C
	.hword 0x5AD6,0x6737,0x3E79,0x0C63,0x56FD,0x4EDD,0x4679,0x4E73
	.hword 0x673B,0x5B3C,0x7BDC,0x4696,0x5F19,0x635C,0x6B57,0x6B58
	.hword 0x4E97,0x4299,0x739A,0x369C,0x4ABC,0x52DB,0x0C84,0x3E9B

@}}BLOCK(player)