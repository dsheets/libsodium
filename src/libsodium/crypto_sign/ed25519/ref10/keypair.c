
#include <string.h>

#include "api.h"
#include "randombytes.h"
#include "crypto_hash_sha512.h"
#include "ge.h"

int crypto_sign_seed_keypair(unsigned char *pk, unsigned char *sk,
                             const unsigned char *seed)
{
    ge_p3 A;

    crypto_hash_sha512(sk,seed,32);
    sk[0] &= 248;
    sk[31] &= 63;
    sk[31] |= 64;

    ge_scalarmult_base(&A,sk);
    ge_p3_tobytes(pk,&A);

    memmove(sk, seed, 32);
    memmove(sk + 32, pk, 32);
    return 0;
}

int crypto_sign_keypair(unsigned char *pk, unsigned char *sk)
{
    unsigned char seed[32];

    randombytes(seed,32);
    return crypto_sign_seed_keypair(pk,sk,seed);
}
