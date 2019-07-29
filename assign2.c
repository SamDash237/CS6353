// Assignment 2
// CS 6353
// Sam Dash

#include <stdio.h>
#include <stdlib.h>
#include <openssl/ssl.h>

int compare(unsigned char *pf, unsigned char *ip, int len);
int random_message(unsigned char *m);
int get_MD5_digest(unsigned char *m, unsigned char *d);

int main(){

    unsigned char target_message[20];
    unsigned char target_digest[16];
    unsigned char match_digest_prefix[16];
    unsigned int match_length;
    unsigned int ip;
    int x;
    int digest_counter = 0;
    
    fprintf(stdout, "Enter Number of Bytes to match\n");
    scanf("%d", &match_length);

    fprintf(stdout, "Enter the byte values to match for %d bytes\n", match_length);
    
    for (x = 0; x < match_length; x++)
    {
        scanf("%u", &ip);
        match_digest_prefix[x] = (unsigned char)ip;
    }

    fprintf(stdout, "TargetDigestPrefix in hexadecimal for %d bytes\n", match_length);
    
    for (x = 0; x < match_length; x++)
    {
        fprintf(stdout, "%02x", match_digest_prefix[x]);
    }
    
    printf("\n");

    do
    {
        random_message(target_message);
        get_MD5_digest(target_message, target_digest);
        digest_counter++;
    }while (compare(match_digest_prefix, target_digest, match_length) != 0);


    fprintf(stdout, "\n\nMatch in %d runs\n", digest_counter);
    
    fprintf(stdout, "Message in hexadecimal format\n");
    for (x = 0; x < 20; x++)
    {
        fprintf(stdout, "%02x", target_message[x]);
    }
    printf("\n");

    fprintf(stdout, "MD5 Digest in hexadecimal format\n");
    for (x = 0; x < 16; x++)
    {
        fprintf(stdout, "%02x", target_digest[x]);
    }
    printf("\n");

    return 0;
}

int compare(unsigned char *pf, unsigned char *ip, int len)
{
    int x;
    
    for (x = 0; x < len; x++)
    {
        if (pf[x] - ip[x] != 0)
            return pf[x] - ip[x];
    }

    return 0;
}

int random_message(unsigned char *m)
{
   int x;

   for (x = 0; x < 20; x++)
       m[x] = rand() % 256;

   return 0;
}

int get_MD5_digest(unsigned char *m, unsigned char *d)
{
    EVP_MD_CTX context;
    int md5HashLen;

    OpenSSL_add_all_digests();

    EVP_MD_CTX_init(&context);
    EVP_DigestInit_ex(&context, EVP_md5(), NULL);
    EVP_DigestUpdate(&context, m, 20);
    EVP_DigestFinal_ex(&context, d, &md5HashLen);
    EVP_MD_CTX_cleanup(&context);

    return 0;
}