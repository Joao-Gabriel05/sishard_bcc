// 0x000 <+0>:  endbr64 
// 0x004 <+4>:  mov    $0x0,%ecx
// 0x009 <+9>:  mov    $0x0,%r8d
// 0x00f <+15>: jmp    0x15 <ex3+21>
// 0x011 <+17>: add    $0x1,%rcx
// 0x015 <+21>: cmp    %rdi,%rcx
// 0x018 <+24>: jge    0x2c <ex3+44>
// 0x01a <+26>: mov    %rcx,%rax
// 0x01d <+29>: cqto   
// 0x01f <+31>: idiv   %rsi
// 0x022 <+34>: test   %rdx,%rdx
// 0x025 <+37>: jne    0x11 <ex3+17>
// 0x027 <+39>: add    %rcx,%r8
// 0x02a <+42>: jmp    0x11 <ex3+17>
// 0x02c <+44>: mov    %r8,%rax
// 0x02f <+47>: ret

int loopando_goto(long rdi, long rsi,long rdx){
    int ecx = 0;
    int r8 = 0;
    goto lin_21;
    lin_17:
        rcx+=1;
    lin_21:
        if(ecx>=rdi){
            goto lin_44;
        }
        rsi = rsi/rcx;
        if(rdx<=0){
            goto lin_17;
        }
        r8+=rcx;
        goto lin_17;

    lin_44:
        return r8;

}


int loopando_c(long rdi, long rsi,long rdx){
    int rcx = 0;
    int r8 = 0;
    while(rcx<rdi){
        rsi = rsi/rcx;
        if(rdx>0){
            r8+=rcx;
        }
        rcx+=1
    }
    return r8;
}