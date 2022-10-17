.ARM
.ALIGN
.GLOBL MultMatrix
.TYPE MultMatrix,function
.TEXT

MultMatrix:

stmdb sp!, {r4 - r12, lr}

mov r4,#0 @r4 = i=0
fori:
    cmp r4,r2 @i<len
    bge endfori


    mul r10,r4,r2 @r10 = len * i


    mov r5,#0 @r5 = j=0
    forj:
        cmp r5,r2
        bge endfoj

        mul r11,r5,r2 @r11 = len * j

        mov r7,#0 @clear tmp sum


        mov r6,#0 @r6 = k=0
        fork:
            cmp r6,r2
            bge endfork
            
            mul r12,r6,r2 @r12 = len * k
            add r8,r10,r6
            ldr r8,[r0,r8,lsl #2] @A_ik
            add r9, r12,r5
            ldr r9,[r1,r9,lsl#2] @B_kj

            mul r9,r8 @A_ik * B_kj
            add r7,r9


            add r6,#1
            b fork
        endfork:

    @now we store result into C_ij
    add r8,r10,r5
    str r7,[r3,r8,lsl #2]

    add r5,#1
    b forj
    endfoj:


add r4,#1
b fori
endfori:

ldmia sp!, {r4 - r12, lr}
bx lr
.END
