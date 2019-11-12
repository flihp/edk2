/*
 */
#ifndef _EDK2_TO_TSS2_MAP_H_
#define _EDK2_TO_TSS2_MAP_H_

#include "IndustryStandard/Tpm20.h"

/*
 * types missing from Tpm20.h (missing types from newer TPM2 specs)
 * these typically fall into three categories:
 * - mapping names from TPM_ to TPM2_ types
 * - mapping constants from no namespace to TPM2_ namespace to prevent
 *   conflicts with symbols from other crypto libraries e.g.
 *   SHA1_DIGEST_SIZE -> TPM2_SHA1_DIGEST_SIZE
 * - mapping from conventions:
 *   - tpm2-tss headers often define a simple type, map it to more specific
 *     types, then reference the "base type" in parts of code:
 *     e.g. tpm2-tss defines TPMS_SIGNATURE_RSA and then has type defs from
 *     this type to TPMS_SIGNATURE_RSASSA & TPMS_SIGNATURE_RSAPSS where the
 *     EDK2 header defines the to structures independently (and identically).
 * - missing types: EDK2 headers are old and haven't been updated for newer
 *   TPM2 specs e.g. missing TPMS_SIGNATURE_ECC, using non-standard (?)
 *   TPMS_SIGNATURE_ECCDSA type.
 * - types defined as structures with bitfields. C spec is ambiguous as to
 *   bitfield order and so tpm2-tss defines these as the primitive types with
 *   bit field selectors as macros, EDK2 uses structure with bitfield.
 */

/* Hash algorithm sizes */
#define TPM2_SHA_DIGEST_SIZE     SHA_DIGEST_SIZE
#define TPM2_SHA1_DIGEST_SIZE    SHA1_DIGEST_SIZE
#define TPM2_SHA256_DIGEST_SIZE  SHA256_DIGEST_SIZE
#define TPM2_SHA384_DIGEST_SIZE  SHA384_DIGEST_SIZE
#define TPM2_SHA512_DIGEST_SIZE  SHA512_DIGEST_SIZE
#define TPM2_SM3_256_DIGEST_SIZE SM3_256_DIGEST_SIZE

#define TPM2_MAX_RSA_KEY_BYTES MAX_RSA_KEY_BYTES
#define TPM2_ALG_ERROR TPM_ALG_ERROR
#define TPM2_ALG_RSA TPM_ALG_RSA
#define TPM2_ALG_SHA TPM_ALG_SHA
#define TPM2_ALG_SHA1 TPM_ALG_SHA1
#define TPM2_ALG_HMAC TPM_ALG_HMAC
#define TPM2_ALG_AES TPM_ALG_AES
#define TPM2_ALG_MGF1 TPM_ALG_MGF1
#define TPM2_ALG_KEYEDHASH TPM_ALG_KEYEDHASH
#define TPM2_ALG_XOR TPM_ALG_XOR
#define TPM2_ALG_SHA256 TPM_ALG_SHA256
#define TPM2_ALG_SHA384 TPM_ALG_SHA384
#define TPM2_ALG_SHA512 TPM_ALG_SHA512
#define TPM2_ALG_NULL TPM_ALG_NULL
#define TPM2_ALG_SM3 TPM_ALG_SM3
#define TPM2_ALG_SM4 TPM_ALG_SM4
#define TPM2_ALG_RSASSA TPM_ALG_RSASSA
#define TPM2_ALG_RSAES TPM_ALG_RSAES
#define TPM2_ALG_RSAPSS TPM_ALG_RSAPSS
#define TPM2_ALG_OAEP TPM_ALG_OAEP
#define TPM2_ALG_ECDSA TPM_ALG_ECDSA
#define TPM2_ALG_ECDH TPM_ALG_ECDH
#define TPM2_ALG_ECDAA TPM_ALG_ECDAA
#define TPM2_ALG_SM2 TPM_ALG_SM2
#define TPM2_ALG_ECSCHNORR TPM_ALG_ECSCHNORR
#define TPM2_ALG_ECMQV TPM_ALG_ECMQV
#define TPM2_ALG_KDF1 TPM_ALG_KDF1
#define TPM2_ALG_KDF2 TPM_ALG_KDF2
#define TPM2_ALG_KDF1 TPM_ALG_KDF1
#define TPM2_ALG_ECC TPM_ALG_ECC
#define TPM2_ALG_SYMCIPHER TPM_ALG_SYMCIPHER
#define TPM2_ALG_CAMELLIA TPM_ALG_CAMELLIA
#define TPM2_ALG_CMAC TPM_ALG_CMAC
#define TPM2_ALG_CTR TPM_ALG_CTR
#define TPM2_ALG_SHA3 TPM_ALG_SHA3
#define TPM2_ALG_SHA3 TPM_ALG_SHA3
#define TPM2_ALG_SHA3 TPM_ALG_SHA3
#define TPM2_ALG_OFB TPM_ALG_OFB
#define TPM2_ALG_CBC TPM_ALG_CBC
#define TPM2_ALG_CFB TPM_ALG_CFB
#define TPM2_ALG_ECB TPM_ALG_ECB
#define TPM2_ALG_FIRST TPM_ALG_FIRST
#define TPM2_ALG_LAST TPM_ALG_LAST

#define TPM2_CC TPM_CC
#define TPM2_HANDLE TPM_HANDLE
#define TPM2_SE TPM_SE

#define TPM2_ALG_SM3_256 TPM_ALG_SM3_256

#define TPM2_CAP_ALGS TPM_CAP_ALGS
#define TPM2_CAP_HANDLES TPM_CAP_HANDLES
#define TPM2_CAP_COMMANDS TPM_CAP_COMMANDS
#define TPM2_CAP_PP_COMMANDS TPM_CAP_PP_COMMANDS
#define TPM2_CAP_AUDIT_COMMANDS TPM_CAP_AUDIT_COMMANDS
#define TPM2_CAP_PCRS TPM_CAP_PCRS
#define TPM2_CAP_TPM_PROPERTIES TPM_CAP_TPM_PROPERTIES
#define TPM2_CAP_PCR_PROPERTIES TPM_CAP_PCR_PROPERTIES
#define TPM2_CAP_ECC_CURVES TPM_CAP_ECC_CURVES
#define TPM2_CAP_VENDOR_PROPERTY TPM_CAP_VENDOR_PROPERTY

#define TPM2_ST_RSP_COMMAND TPM_ST_RSP_COMMAND
#define TPM2_ST_NULL TPM_ST_NULL
#define TPM2_ST_NO_SESSIONS TPM_ST_NO_SESSIONS
#define TPM2_ST_SESSIONS TPM_ST_SESSIONS
#define TPM2_ST_RESERVED1 TPM_ST_RESERVED1
#define TPM2_ST_RESERVED2 TPM_ST_RESERVED2
#define TPM2_ST_ATTEST_NV TPM_ST_ATTEST_NV
#define TPM2_ST_ATTEST_COMMAND_AUDIT TPM_ST_ATTEST_COMMAND_AUDIT
#define TPM2_ST_ATTEST_SESSION_AUDIT TPM_ST_ATTEST_SESSION_AUDIT
#define TPM2_ST_ATTEST_CERTIFY TPM_ST_ATTEST_CERTIFY
#define TPM2_ST_ATTEST_QUOTE TPM_ST_ATTEST_QUOTE
#define TPM2_ST_ATTEST_TIME TPM_ST_ATTEST_TIME
#define TPM2_ST_ATTEST_CREATION TPM_ST_ATTEST_CREATION
#define TPM2_ST_RESERVED3 TPM_ST_RESERVED3
#define TPM2_ST_CREATION TPM_ST_CREATION
#define TPM2_ST_VERIFIED TPM_ST_VERIFIED
#define TPM2_ST_AUTH_SECRET TPM_ST_AUTH_SECRET
#define TPM2_ST_HASHCHECK TPM_ST_HASHCHECK
#define TPM2_ST_AUTH_SIGNED TPM_ST_AUTH_SIGNED
#define TPM2_ST_FU_MANIFEST TPM_ST_FU_MANIFEST

typedef UINT32 TPM_AT;

typedef struct {
    TPM2B_DIGEST integrityHMAC;
    TPM2B_DIGEST encIdentity;
} TPMS_ID_OBJECT;

typedef struct {
    TPM_AT tag;
    UINT32 data;
} TPMS_AC_OUTPUT;

#define TPM2_MAX_AC_CAPABILITIES (TPM2_MAX_CAP_BUFFER / sizeof(TPMS_AC_OUTPUT))
typedef struct {
    UINT32 count;
    TPMS_AC_OUTPUT acCapabilities[TPM2_MAX_AC_CAPABILITIES];
} TPML_AC_CAPABILITIES;

typedef UINT8 TPM2_NT;
typedef UINT16 TPM2_ST;

/* tpm2-tss may be folowing the spec a bit *too* close, this is silly */
typedef struct {
    BYTE empty[1];
} TPMS_EMPTY;

typedef struct {
    UINT16 size;
    BYTE buffer[sizeof(TPMT_PUBLIC)];
} TPM2B_TEMPLATE;

typedef struct {
    TPM2_HANDLE handle;
    TPMT_HA policyHash;
} TPMS_TAGGED_POLICY;

typedef struct {
    TPMI_ALG_HASH hashAlg;
} TPMS_SCHEME_HASH;

typedef struct {
    TPMI_ALG_HASH hash;
    TPM2B_PUBLIC_KEY_RSA sig;
} TPMS_SIGNATURE_RSA;

typedef struct {
    TPMI_ALG_HASH hash;
    TPM2B_ECC_PARAMETER signatureR;
    TPM2B_ECC_PARAMETER signatureS;
} TPMS_SIGNATURE_ECC;

typedef struct {
    UINT32 pinCount;
    UINT32 pinLimit;
} TPMS_NV_PIN_COUNTER_PARAMETERS;

#endif
