.ARM
.ALIGN
.GLOBL MultMatrix
.TYPE MultMatrix,function
.TEXT

MultMatrix:

stmdb sp!, {r4 - r15, lr}

mov r4,#0 @r4 = i=0
mov r5,#0 @r5 = j=0
mov r6,#0 @r6 = k=0

fori:
    cmp r4,r2 @i<len
    bge endfori

    mul r10,r4,r2 @r10 = len * i


    forj:
        cmp r5,r2
        bge endfoj

        mul r11,r5,r2 @r11 = len * j

        mov r7,#0 @clear tmp sum


        fork:
            cmp r6,r2
            bge endfork
            
            mul r12,r6,r2 @r12 = len * k
            add r13,r10,r6
            ldr r8,[r0,r13,lsl #2] @A_ik
            add r13, r12,r11
            ldr r9,[r1,r13,lsl#2] @B_kj

            mul r9,r8 @A_ik * B_kj
            add r7,r9


            add r6,#1
            b fork
        endfork:

    @now we store result into C_ij
    add r13,r4,r11
    str r6,[r3,r13,lsl #2]

    add r5,#1
    b forj
    endfoj:


add r4,#1
b fori
endfori:

ldmia sp!, {r4 - r15, lr}
bx lr
.END
