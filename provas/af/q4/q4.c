

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>


char *read_word(int fd);

typedef struct {
    int id_thread;            // identificador da thread
    int *count_cpfs;          // para as threads saberem onde guardar o resultado
    int file_desc;            // descritor do arquivo
    pthread_mutex_t *mutex_read;
    pthread_mutex_t *mutex_count;
} t_arg;

#define MAX_LINE_LENGTH 256

int isnum(char c) {
    return c >= '0' && c <= '9';
}

int validade_cpf(char *txt) {
    int qtde = 0;
    for (; txt[qtde] != '\0'; qtde++);
    if (qtde != 14) return 1;
    if (!(isnum(txt[0]) && isnum(txt[1]) && isnum(txt[2]) && txt[3]=='.' &&
          isnum(txt[4]) && isnum(txt[5]) && isnum(txt[6]) && txt[7]=='.' &&
          isnum(txt[8]) && isnum(txt[9]) && isnum(txt[10]) && txt[11]=='-' &&
          isnum(txt[12]) && isnum(txt[13])))
        return 1;
    // todos iguais?
    if (txt[0]==txt[1] && txt[0]==txt[2] && txt[0]==txt[4] && txt[0]==txt[5] &&
        txt[0]==txt[6] && txt[0]==txt[8] && txt[0]==txt[9] && txt[0]==txt[10] &&
        txt[0]==txt[12] && txt[0]==txt[13])
        return 2;
    int dig1 = ((((txt[0]-'0')*10 + (txt[1]-'0')*9 + (txt[2]-'0')*8 +
                  (txt[4]-'0')*7 + (txt[5]-'0')*6 + (txt[6]-'0')*5 +
                  (txt[8]-'0')*4 + (txt[9]-'0')*3 + (txt[10]-'0')*2)*10)%11)%10;
    int dig2 = ((((txt[0]-'0')*11 + (txt[1]-'0')*10 + (txt[2]-'0')*9 +
                  (txt[4]-'0')*8 + (txt[5]-'0')*7 + (txt[6]-'0')*6 +
                  (txt[8]-'0')*5 + (txt[9]-'0')*4 + (txt[10]-'0')*3 +
                  (txt[12]-'0')*2)*10)%11)%10;
    return (dig1==(txt[12]-'0') && dig2==(txt[13]-'0')) ? 0 : 2;
}

void *cpf_validation_thread(void *_arg) {
    t_arg *arg = _arg;

    while (1) {
        pthread_mutex_lock(arg->mutex_read);
        char *palavra = read_word(arg->file_desc);
        pthread_mutex_unlock(arg->mutex_read);


        if (palavra == NULL)
            break;

        printf("THREAD %02d VAI PROCESSAR PALAVRA [%s]\n",
               arg->id_thread, palavra);
        fflush(stdout);

        int ret = validade_cpf(palavra);
        if (ret == 0) {
            pthread_mutex_lock(arg->mutex_count);
            *arg->count_cpfs += 1;
            pthread_mutex_unlock(arg->mutex_count);
    
        }
        
        free(palavra);
    
    }
    return NULL;
}

char *read_word(int fd) {
    char buffer[1];
    char *palavra = malloc(MAX_LINE_LENGTH);
    int pos = 0, length;

    while (1) {
        length = read(fd, buffer, 1);
        if (length == 0) {
            if (pos == 0) {
                free(palavra);
                return NULL;
            } else {
                palavra[pos] = '\0';
                return palavra;
            }
        }
        if (buffer[0] == ' ') {
            palavra[pos] = '\0';
            return palavra;
        } else {
            palavra[pos++] = buffer[0];
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "USAGE:\n\t%s <n_threads> <file_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int n_threads = atoi(argv[1]);
    char *file_name = argv[2];

    int fd1 = open(file_name, O_RDONLY);
    if (fd1 == -1) {
        perror("Falha ao abrir o arquivo");
        return EXIT_FAILURE;
    }

    int count_cpfs = 0;
    pthread_t *tids = malloc(sizeof(pthread_t) * n_threads);
    t_arg **args  = malloc(sizeof(t_arg *)    * n_threads);

    pthread_mutex_t mutex_read, mutex_count;
    pthread_mutex_init(&mutex_read,  NULL);
    pthread_mutex_init(&mutex_count, NULL);

    for (int i = 0; i < n_threads; i++) {
        t_arg *arg = malloc(sizeof(t_arg));
        arg->id_thread    = i;
        arg->count_cpfs   = &count_cpfs;
        arg->file_desc    = fd1;
        arg->mutex_read   = &mutex_read;
        arg->mutex_count  = &mutex_count;
        args[i] = arg;

        pthread_create(&tids[i], NULL,
                       cpf_validation_thread, arg);
        printf("CRIOU THREAD %02d\n", i);
    }

    for (int i = 0; i < n_threads; i++) {
        pthread_join(tids[i], NULL);
        printf("THREAD %02d TERMINOU\n", i);
        free(args[i]);
    }

    printf("RESULTADO:\nFORAM ENCONTRADOS %02d CPFS VALIDOS\n",
           count_cpfs);

    close(fd1);
    free(tids);
    free(args);

    pthread_mutex_destroy(&mutex_read);
    pthread_mutex_destroy(&mutex_count);

    return 0;
}
