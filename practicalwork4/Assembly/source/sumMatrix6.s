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
.END
