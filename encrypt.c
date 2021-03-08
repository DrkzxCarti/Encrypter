/*
Coded By MichCartii#0988
Date: 02/11/2020
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <arpa/inet.h>

static uint32_t table_key = 0xdeadbeef;

void *x(void *, int);

int main(int argc, char **args)
{
    void *data;
    int len, i;

    if (argc != 3)
    {
        printf("\e[0;97m[\e[0;91m!\e[0;97m] \e[0;96mSyntax: %s (STRING/UINT32/UINT16/UINT8) (data) \e[0;97m[\e[0;91m!\e[0;97m]\n", args[0]);
        return 0;
    }

    if (strcmp(args[1], "STRING") == 0)
    {
        data = args[2];
        len = strlen(args[2]) + 1;
    }
    else if (strcmp(args[1], "UINT32") == 0)
    {
        data = calloc(1, sizeof (uint32_t));
        *((uint32_t *)data) = htonl((uint32_t)atoi(args[2]));
        len = sizeof (uint32_t);
    }
    else if (strcmp(args[1], "UINT16") == 0)
    {
        data = calloc(1, sizeof (uint16_t));
        *((uint16_t *)data) = htons((uint16_t)atoi(args[2]));
        len = sizeof (uint16_t);
    }
    else if (strcmp(args[1], "UINT8") == 0)
    {
        data = calloc(1, sizeof (uint8_t));
        *((uint8_t *)data) = atoi(args[2]);
        len = sizeof (uint8_t);
    }
    else
    {
        printf("\e[0;97m[\e[0;91m!\e[0;97m] \e[0;96mNo Type Named '%s' Was Found! \e[0;97m[\e[0;91m!\e[0;97m]\n", args[1]);
        return -1;
    }

    printf("\e[0;97m[\e[0;91m!\e[0;97m] \e[0;96mEncrypted %d Bytes Of Precious Data. \e[0;97m[\e[0;91m!\e[0;97m]\n", len);
    data = x(data, len);
    for (i = 0; i < len; i++)
        printf("\\x%02X", ((unsigned char *)data)[i]);
    printf("\n");
}

void *x(void *_buf, int len)
{
    unsigned char *buf = (char *)_buf, *out = malloc(len);
    int i;
    uint8_t k1 = table_key & 0xff,
            k2 = (table_key >> 8) & 0xff,
            k3 = (table_key >> 16) & 0xff,
            k4 = (table_key >> 24) & 0xff;

    for (i = 0; i < len; i++)
    {
        char tmp = buf[i] ^ k1;

        tmp ^= k2;
        tmp ^= k3;
        tmp ^= k4;

        out[i] = tmp;
    }

    return out;
}
