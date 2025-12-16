#ifndef API_CRYPT_H
#define API_CRYPT_H

/**
 * ask a password and cipher the input file with it then save the result on the output file
 * @param pIn path to the input file
 * @param pOut path to the output file
 * @return 1 on success 0 on failure
 */
int API_cipher(char *pIn, char *pOut);

/**
 * ask a password and decipher the input file with it then save the result on the output file
 * @param pIn path to the input file
 * @param pOut path to the output file
 * @return 1 on success 0 on failure
 */
int API_decipher(char *pIn, char *pOut);

#endif //API_CRYPT_H