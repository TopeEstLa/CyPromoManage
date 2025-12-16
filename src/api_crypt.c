#include <api_crypt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generate_master_key(char *password, unsigned char *key) {
    unsigned char init_key[16] = {
        0x01, 0x45, 0x57, 0x89, 0xAB, 0xCD, 0xEF, 0x10,
        0x32, 0x54, 0x75, 0x98, 0xBA, 0xDC, 0xFE
    };

    for(int i=0; i<16; i++) key[i] = init_key[i];
    key[15] = 0x00;

    int pwd_len = strlen(password);
    for (int i = 0; i < pwd_len; i++) {
        char c = password[i];
        int idx = i % 16;

        key[idx] ^= c;

        key[(idx + 1) % 16] += c;

        key[(idx - 1 + 16) % 16] *= c;
    }
}

int API_cipher(char *pIn, char *pOut) {
    FILE *fIn = fopen(pIn, "rb");
    FILE *fOut = fopen(pOut, "wb");
    if (!fIn || !fOut) return 0;

    char password[256];
    printf("Entrez le mot de passe pour chiffrer (min 16 cars recommande): ");
    scanf("%255s", password);

    unsigned char master_key[16];
    generate_master_key(password, master_key);

    unsigned char file_key[16];
    srand(time(NULL));
    for(int i=0; i<16; i++) file_key[i] = (unsigned char)(rand() % 256);

    unsigned char encrypted_key[16];
    for(int i=0; i<16; i++) {
        encrypted_key[i] = file_key[i] ^ master_key[i];
    }

    fwrite(encrypted_key, 1, 16, fOut);

    int c;
    int index = 0;
    while ((c = fgetc(fIn)) != EOF) {
        unsigned char ch = (unsigned char)c;
        unsigned char ciphered = ch ^ file_key[index % 16];
        fputc(ciphered, fOut);
        index++;
    }

    fclose(fIn);
    fclose(fOut);
    printf("Fichier chiffre avec succes.\n");
    return 1;
}
int API_decipher(char *pIn, char *pOut) {
    FILE *fIn = fopen(pIn, "rb");
    FILE *fOut = fopen(pOut, "wb");
    if (!fIn || !fOut) return 0;

    char password[256];
    printf("Entrez le mot de passe pour dechiffrer : ");
    scanf("%255s", password);

    unsigned char master_key[16];
    generate_master_key(password, master_key);

    unsigned char encrypted_key[16];
    if (fread(encrypted_key, 1, 16, fIn) != 16) {
        printf("Erreur: Fichier trop court ou corrompu.\n");
        fclose(fIn); fclose(fOut);
        return 0;
    }

    unsigned char file_key[16];
    for(int i=0; i<16; i++) {
        file_key[i] = encrypted_key[i] ^ master_key[i];
    }

    int c;
    int index = 0;
    while ((c = fgetc(fIn)) != EOF) {
        unsigned char ch = (unsigned char)c;
        unsigned char plain = ch ^ file_key[index % 16];
        fputc(plain, fOut);
        index++;
    }

    fclose(fIn);
    fclose(fOut);
    printf("Fichier dechiffre avec succes.\n");
    return 1;
}