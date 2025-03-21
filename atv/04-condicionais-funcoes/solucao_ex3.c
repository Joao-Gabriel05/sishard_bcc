/* Implementar função solucao_ex3 */
//    0x0000000000000000 <+0>:     endbr64
//    0x0000000000000004 <+4>:     cmp    %rsi,%rdi
//    0x0000000000000007 <+7>:     setl   %al
//    0x000000000000000a <+10>:    movzbl %al,%eax
//    0x000000000000000d <+13>:    mov    %eax,(%rdx)
//    0x000000000000000f <+15>:    sete   %al
//    0x0000000000000012 <+18>:    movzbl %al,%eax
//    0x0000000000000015 <+21>:    mov    %eax,(%rcx)
//    0x0000000000000017 <+23>:    setg   %al
//    0x000000000000001a <+26>:    movzbl %al,%eax
//    0x000000000000001d <+29>:    mov    %eax,(%r8)
//    0x0000000000000020 <+32>:    ret
int solucao_ex3(long rdi, long rsi, int *rdx, int *rcx, int *r8) {
    long cmp;
    int eax;
    cmp = rdi - rsi;
    short al = 0;
    if (cmp < 0) {
        al = 1;
    }

    eax = al;
    *rdx = eax;

    al = 0;
    if (cmp == 0) {
        al = 1;
    } 

    eax = al;
    *rcx = eax;

    al = 0;
    if (cmp > 0) {
        al = 1;
    } 

    eax = al;
    *r8 = eax;

    return eax;
}


// 0x0000000000000000 <+0>:     endbr64 
// 0x0000000000000004 <+4>:     cmp    %rsi,%rdi
// 0x0000000000000007 <+7>:     setl   %al
// 0x000000000000000a <+10>:    movzbl %al,%eax
// 0x000000000000000d <+13>:    mov    %eax,(%rdx)
// 0x000000000000000f <+15>:    sete   %al
// 0x0000000000000012 <+18>:    movzbl %al,%eax
// 0x0000000000000015 <+21>:    mov    %eax,(%rcx)
// 0x0000000000000017 <+23>:    setg   %al
// 0x000000000000001a <+26>:    movzbl %al,%eax
// 0x000000000000001d <+29>:    mov    %eax,(%r8)
// 0x0000000000000020 <+32>:    ret   


int solucao_ex3(long rdi,long rsi,long rdx,long rcx,long r8){
    short al = (rdi<rsi);
    

}