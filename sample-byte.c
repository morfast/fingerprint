#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SAMPLE_TABLE_SIZE    256

void hashlittle2( 
  const void *key,       /* the key to hash */
  size_t      length,    /* length of the key */
  uint32_t   *pc,        /* IN: primary initval, OUT: primary hash */
  uint32_t   *pb);        /* IN: secondary initval, OUT: secondary hash */

uint64_t JenkinsHash(unsigned char *data, uint32_t size)
{
    uint32_t c, b;
    uint64_t result;

    hashlittle2((const void *)data, size, &c, &b);

    result = 0;
    result |= c;
    result = result << 32;
    result |= b;

    return result;
}

static unsigned char sample_table[SAMPLE_TABLE_SIZE];

/* initialize the byte table */
int init_sample_byte()
{
    bzero(sample_table, SAMPLE_TABLE_SIZE);
    /* According to the paper, the following bits are set to 1:
       0, 32, 48, 101, 105, 115, 116, 255. 
       Other bits are zero. */
    sample_table[0] = 1;
    sample_table[32] = 1;
    sample_table[48] = 1;
    sample_table[101] = 1;
    sample_table[105] = 1;
    sample_table[115] = 1;
    sample_table[116] = 1;
    sample_table[225] = 1;

    return 0;
}

/* sample byte fingerprint algorithm
pdata:  input data  (INPUT)
size:   size of data  (INPUT)
offset: offset of the block for fingerprint (OUTPUT)
fp: fingerprint  (OUTPUT) */
int sample_byte(unsigned char *pdata, 
			    uint32_t size, 
			    uint32_t wsize, 
			    uint32_t *offset,
			    uint32_t *skip,
				uint64_t *fingerprint)
{
    uint32_t i;
    uint32_t p;

    p = wsize;

    for(i = 0; i < (size-wsize); i++) {
//        printf("%d\n", pdata[i]);
        if (sample_table[pdata[i]] == 1) {
            printf("counting fingerprint\n");
            *offset = i;
            *fingerprint = JenkinsHash(pdata + i, wsize);
            *skip = p/2;
            return 0;
        }
    }
    return 1;

}

int main(void)
{
    unsigned char data[1000];

    uint32_t offset;
    uint32_t skip;
    uint64_t fp;
    int i;

    for (i = 0; i < 1000; i++) {
        data[i] = i % 256;
    }

    init_sample_byte();
    sample_byte(data, 1000, 32, &offset, &skip, &fp);

    return 0;
}
