/* Implementar função solucao_ex4 */
//    0x0000000000000000 <+0>:     endbr64
//    0x0000000000000004 <+4>:     cmp    $0x11,%di
//    0x0000000000000008 <+8>:     jle    0x17 <ex4+23>
//    0x000000000000000a <+10>:    sub    $0x41,%esi
//    0x000000000000000d <+13>:    cmp    $0x1,%sil
//    0x0000000000000011 <+17>:    ja     0x1f <ex4+31>
//    0x0000000000000013 <+19>:    lea    -0x11(%rdi),%eax
//    0x0000000000000016 <+22>:    ret
//    0x0000000000000017 <+23>:    mov    $0x12,%eax
//    0x000000000000001c <+28>:    sub    %edi,%eax
//    0x000000000000001e <+30>:    ret
//    0x000000000000001f <+31>:    mov    $0xffffffff,%eax
//    0x0000000000000024 <+36>:    ret
int solucao_ex4(short di, int esi) {
    int eax;
    int cmp = di - 0x11;
    if (cmp > 0) {
        esi -= 0x41;
        cmp = esi - 1;
        if (cmp <= 0) {
            eax = di - 0x11;
            return eax;
        }
        eax = 0xffffffff;
        return eax;
    }
    eax = 0x12;
    eax -= di;
    return eax;
}