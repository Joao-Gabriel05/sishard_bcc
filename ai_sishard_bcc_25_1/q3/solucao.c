// Seu código da funcao1_solucao

long funcao1_solucao(long rdi,long rsi){
    int ecx = 0;
    while(rdi>=rsi){
    rdi = rdi/rsi;
        ecx++;
    }
    return ecx;
}