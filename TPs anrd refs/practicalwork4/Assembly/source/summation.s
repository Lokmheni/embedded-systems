.ARM
.ALIGN
.GLOBL SumArray
.TYPE SumArray,function
.TEXT

SumArray:
    stmdb sp!, {r4 - r11, lr}

    mov r2,#0 @int i=0
    mov r3,#0 @ret = 0

forloop:
    cmp r2,r1 @ i<len
    bge encforloop
    ldr r4, [r0,r2,lsl #2]@r4 = r0[r2* sizeof(4)] 
    add r3,r4 @ret+= r4
    add r2,#1 @i++

    b forloop
encforloop:

    mov r0,r3@return ret


    ldmia sp!, {r4 - r11, lr}
    bx lr

.END