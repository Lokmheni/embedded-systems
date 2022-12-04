.ARM
.ALIGN
.GLOBL Sum
.TYPE Sum,function
.TEXT

Sum:

stmdb sp!, {r4 - r11, lr}
add r0, r0, r1

ldmia sp!, {r4 - r11, lr}
bx lr
.END
