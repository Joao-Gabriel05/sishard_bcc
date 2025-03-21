//    0x0000000000000000 <+0>:     endbr64
//    0x0000000000000004 <+4>:     lea    (%rdi,%rdi,1),%rax
//    0x0000000000000008 <+8>:     ret

static long vezes2(long rdi) {
    long rax = rdi + rdi*1;
    return rax;
}

/* Implementar função solucao_ex2 */
//    0x0000000000000009 <+0>:     endbr64
//    0x000000000000000d <+4>:     push   %rbx
//    0x000000000000000e <+5>:     mov    %rdi,%rbx
//    0x0000000000000011 <+8>:     mov    %rsi,%rdi
//    0x0000000000000014 <+11>:    call   0x19 <ex2+16>
//    0x0000000000000019 <+16>:    cmp    %rbx,%rax
//    0x000000000000001c <+19>:    jle    0x21 <ex2+24>
//    0x000000000000001e <+21>:    add    %rbx,%rbx
//    0x0000000000000021 <+24>:    add    %rbx,%rax
//    0x0000000000000024 <+27>:    pop    %rbx
//    0x0000000000000025 <+28>:    ret
long solucao_ex2(long rdi, long rsi) {
    long rbx;
    long rax;

    rbx = rdi;
    rdi = rsi;

    rax = vezes2(rdi);

    long cmp;

    cmp = rax - rbx;

    if (cmp > 0) {
        rbx += rbx;
    } 
    
    rax += rbx;
       
    return rax;

}

  

long vezes_2(long rdi){
    return rdi*2;
}

long ex2(long rdi, long rsi){
    int rax = vezes_2(rsi);
    if(rax>=rdi){
        rdi+=rdi;
    }
    rax+=rdi;
    return rax;
}