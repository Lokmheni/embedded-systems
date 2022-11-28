.ARM
.ALIGN
.GLOBL sum6
.TYPE sum6,function
.TEXT

sum6:

    add r0,r1
    add r0,r2
    add r0,r3
    
    ldmia sp,{r1,r2}

    add r0,r1
    add r0,r2
    

bx lr






.ALIGN
.GLOBL sumMatrix6
.TYPE sumMatrix6,function
.TEXT

sumMatrix6:
stmdb sp!, {r4 - r11, lr}


    mov r7,#0 @i=0
    mov r8,#0 @ret=0
beginforloop:
        cmp r7,#6
        bge endforloop
        ldmia r0!,{r1-r6}
        push {r0}
        mov r0,r6
        push {r4,r5}
        bl sum6
        add r8, r0
        pop {r0,r1}
        pop {r0}

        add r7,#1
        b beginforloop
endforloop:
    mov r0,r8

ldmia sp!, {r4 - r11, lr}
bx lr
.END
