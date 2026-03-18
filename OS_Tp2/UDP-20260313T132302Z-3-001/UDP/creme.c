#include "creme.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 9998
#define LBUF 512

/* PID du processus serveur en tâche de fond */
static pid_t serveur_pid = -1;

/* Fonction utilitaire interne pour envoyer au serveur local */
static int envoyer_datagramme(const char *buf, int len) {
    int sid;
    struct sockaddr_in Sock;

    if ((sid = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        perror("socket");
        return -1;
    }

    memset(&Sock, 0, sizeof(Sock));
    Sock.sin_family = AF_INET;
    Sock.sin_port = htons(PORT);
    Sock.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (sendto(sid, buf, len, 0, (struct sockaddr *)&Sock, sizeof(Sock)) < 0) {
        perror("sendto");
        close(sid);
        return -1;
    }

    close(sid);
    return 0;
}

int beuip_start(const char *pseudo) {
    if (serveur_pid != -1) {
        printf("Le serveur est déjà en cours d'exécution (PID %d).\n", serveur_pid);
        return -1;
    }

    serveur_pid = fork();
    if (serveur_pid < 0) {
        perror("fork");
        return -1;
    }

    if (serveur_pid == 0) {
        /* Processus fils : exécute le serveur */
        execl("./servbeuip", "servbeuip", pseudo, NULL);
        perror("execl");
        exit(1); /* Si execl échoue */
    }

    /* Processus père */
#ifdef TRACE
    printf("[TRACE] Serveur démarré avec le PID %d\n", serveur_pid);
#endif
    return 0;
}

int beuip_stop(void) {
    if (serveur_pid == -1) {
        printf("Aucun serveur en cours d'exécution.\n");
        return -1;
    }

    /* Envoi du signal SIGTERM pour que le serveur exécute son gestionnaire et s'arrête */
    if (kill(serveur_pid, SIGTERM) == 0) {
#ifdef TRACE
        printf("[TRACE] Signal SIGTERM envoyé au PID %d\n", serveur_pid);
#endif
        serveur_pid = -1;
        return 0;
    } else {
        perror("kill");
        return -1;
    }
}

int mess_liste(void) {
    char buf[LBUF] = "3BEUIP";
    return envoyer_datagramme(buf, strlen(buf));
}

int mess_send_one(const char *pseudo, const char *message) {
    char buf[LBUF];
    buf[0] = '4';
    strcpy(&buf[1], "BEUIP");
    
    int len_pseudo = strlen(pseudo);
    strcpy(&buf[6], pseudo);
    strcpy(&buf[6 + len_pseudo + 1], message);
    
    int len = 6 + len_pseudo + 1 + strlen(message);
    return envoyer_datagramme(buf, len);
}

int mess_send_all(const char *message) {
    char buf[LBUF];
    snprintf(buf, LBUF, "5BEUIP%s", message);
    return envoyer_datagramme(buf, strlen(buf));
}