#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* sample byte fingerprint algorithm
pdata:  input data  (INPUT)
size:   size of data  (INPUT)
offset: offset of the block for fingerprint (OUTPUT)
fp: fingerprint  (OUTPUT) */
int sample_byte(char *pdata, 
			    uint32_t size, 
			    uint32_t *offset,
				uint64_t *roll)
{
    return 0;
}
