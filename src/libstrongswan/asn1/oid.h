/* Object identifiers (OIDs) used by strongSwan
 * Copyright (C) 2003-2008 Andreas Steffen, Hochschule fuer Technik Rapperswil
 * 
 * This file has been automatically generated by the script oid.pl
 * Do not edit manually!
 */

#include <utils/utils.h>

#ifndef OID_H_
#define OID_H_

typedef struct {
    u_char octet;
    u_int  next;
    u_int  down;
    u_int  level;
    const u_char *name;
} oid_t;

extern const oid_t oid_names[];

#define OID_UNKNOWN							-1
#define OID_NAME_DISTINGUISHER				6
#define OID_PILOT_USERID					16
#define OID_PILOT_DOMAIN_COMPONENT			17
#define OID_COMMON_NAME						20
#define OID_SURNAME							21
#define OID_SERIAL_NUMBER					22
#define OID_COUNTRY							23
#define OID_LOCALITY						24
#define OID_STATE_OR_PROVINCE				25
#define OID_ORGANIZATION					26
#define OID_ORGANIZATION_UNIT				27
#define OID_TITLE							28
#define OID_DESCRIPTION						29
#define OID_USER_CERTIFICATE				30
#define OID_NAME							31
#define OID_GIVEN_NAME						32
#define OID_INITIALS						33
#define OID_UNIQUE_IDENTIFIER				34
#define OID_DN_QUALIFIER					35
#define OID_DMD_NAME						36
#define OID_PSEUDONYM						37
#define OID_ROLE							38
#define OID_SUBJECT_KEY_ID					41
#define OID_KEY_USAGE						42
#define OID_SUBJECT_ALT_NAME				44
#define OID_BASIC_CONSTRAINTS				46
#define OID_CRL_NUMBER						47
#define OID_CRL_REASON_CODE					48
#define OID_DELTA_CRL_INDICATOR				51
#define OID_ISSUING_DIST_POINT				52
#define OID_NAME_CONSTRAINTS				54
#define OID_CRL_DISTRIBUTION_POINTS			55
#define OID_CERTIFICATE_POLICIES			56
#define OID_ANY_POLICY						57
#define OID_POLICY_MAPPINGS					58
#define OID_AUTHORITY_KEY_ID				59
#define OID_POLICY_CONSTRAINTS				60
#define OID_EXTENDED_KEY_USAGE				61
#define OID_FRESHEST_CRL					63
#define OID_INHIBIT_ANY_POLICY				64
#define OID_TARGET_INFORMATION				65
#define OID_NO_REV_AVAIL					66
#define OID_CAMELLIA128_CBC					77
#define OID_CAMELLIA192_CBC					78
#define OID_CAMELLIA256_CBC					79
#define OID_RSA_ENCRYPTION					92
#define OID_MD2_WITH_RSA					93
#define OID_MD5_WITH_RSA					94
#define OID_SHA1_WITH_RSA					95
#define OID_RSAES_OAEP						96
#define OID_SHA256_WITH_RSA					99
#define OID_SHA384_WITH_RSA					100
#define OID_SHA512_WITH_RSA					101
#define OID_SHA224_WITH_RSA					102
#define OID_PBE_MD5_DES_CBC					104
#define OID_PBE_SHA1_DES_CBC				105
#define OID_PBKDF2							106
#define OID_PBES2							107
#define OID_PKCS7_DATA						109
#define OID_PKCS7_SIGNED_DATA				110
#define OID_PKCS7_ENVELOPED_DATA			111
#define OID_PKCS7_SIGNED_ENVELOPED_DATA		112
#define OID_PKCS7_DIGESTED_DATA				113
#define OID_PKCS7_ENCRYPTED_DATA			114
#define OID_EMAIL_ADDRESS					116
#define OID_UNSTRUCTURED_NAME				117
#define OID_PKCS9_CONTENT_TYPE				118
#define OID_PKCS9_MESSAGE_DIGEST			119
#define OID_PKCS9_SIGNING_TIME				120
#define OID_CHALLENGE_PASSWORD				122
#define OID_UNSTRUCTURED_ADDRESS			123
#define OID_EXTENSION_REQUEST				124
#define OID_X509_CERTIFICATE				127
#define OID_PBE_SHA1_RC4_128				131
#define OID_PBE_SHA1_RC4_40					132
#define OID_PBE_SHA1_3DES_CBC				133
#define OID_PBE_SHA1_3DES_2KEY_CBC			134
#define OID_PBE_SHA1_RC2_CBC_128			135
#define OID_PBE_SHA1_RC2_CBC_40				136
#define OID_P12_KEY_BAG						139
#define OID_P12_PKCS8_KEY_BAG				140
#define OID_P12_CERT_BAG					141
#define OID_P12_CRL_BAG						142
#define OID_MD2								146
#define OID_MD5								147
#define OID_3DES_EDE_CBC					149
#define OID_EC_PUBLICKEY					153
#define OID_C2PNB163V1						156
#define OID_C2PNB163V2						157
#define OID_C2PNB163V3						158
#define OID_C2PNB176W1						159
#define OID_C2PNB191V1						160
#define OID_C2PNB191V2						161
#define OID_C2PNB191V3						162
#define OID_C2PNB191V4						163
#define OID_C2PNB191V5						164
#define OID_C2PNB208W1						165
#define OID_C2PNB239V1						166
#define OID_C2PNB239V2						167
#define OID_C2PNB239V3						168
#define OID_C2PNB239V4						169
#define OID_C2PNB239V5						170
#define OID_C2PNB272W1						171
#define OID_C2PNB304W1						172
#define OID_C2PNB359V1						173
#define OID_C2PNB368W1						174
#define OID_C2PNB431R1						175
#define OID_PRIME192V1						177
#define OID_PRIME192V2						178
#define OID_PRIME192V3						179
#define OID_PRIME239V1						180
#define OID_PRIME239V2						181
#define OID_PRIME239V3						182
#define OID_PRIME256V1						183
#define OID_ECDSA_WITH_SHA1					185
#define OID_ECDSA_WITH_SHA224				187
#define OID_ECDSA_WITH_SHA256				188
#define OID_ECDSA_WITH_SHA384				189
#define OID_ECDSA_WITH_SHA512				190
#define OID_MS_SMARTCARD_LOGON				204
#define OID_USER_PRINCIPAL_NAME				205
#define OID_STRONGSWAN						211
#define OID_BLISS_PUBLICKEY					216
#define OID_BLISS_I							218
#define OID_BLISS_II						219
#define OID_BLISS_III						220
#define OID_BLISS_IV						221
#define OID_BLISS_B_I						222
#define OID_BLISS_B_II						223
#define OID_BLISS_B_III						224
#define OID_BLISS_B_IV						225
#define OID_BLISS_WITH_SHA2_512				227
#define OID_BLISS_WITH_SHA2_384				228
#define OID_BLISS_WITH_SHA2_256				229
#define OID_BLISS_WITH_SHA3_512				230
#define OID_BLISS_WITH_SHA3_384				231
#define OID_BLISS_WITH_SHA3_256				232
#define OID_TCGID							239
#define OID_BLOWFISH_CBC					243
#define OID_AUTHORITY_INFO_ACCESS			287
#define OID_IP_ADDR_BLOCKS					289
#define OID_POLICY_QUALIFIER_CPS			291
#define OID_POLICY_QUALIFIER_UNOTICE		292
#define OID_SERVER_AUTH						294
#define OID_CLIENT_AUTH						295
#define OID_OCSP_SIGNING					302
#define OID_XMPP_ADDR						308
#define OID_AUTHENTICATION_INFO				312
#define OID_ACCESS_IDENTITY					313
#define OID_CHARGING_IDENTITY				314
#define OID_GROUP							315
#define OID_OCSP							318
#define OID_BASIC							319
#define OID_NONCE							320
#define OID_CRL								321
#define OID_RESPONSE						322
#define OID_NO_CHECK						323
#define OID_ARCHIVE_CUTOFF					324
#define OID_SERVICE_LOCATOR					325
#define OID_CA_ISSUERS						326
#define OID_IKE_INTERMEDIATE				331
#define OID_DES_CBC							335
#define OID_SHA1							336
#define OID_SHA1_WITH_RSA_OIW				337
#define OID_ECGDSA_PUBKEY					356
#define OID_ECGDSA_SIG_WITH_RIPEMD160		359
#define OID_ECGDSA_SIG_WITH_SHA1			360
#define OID_ECGDSA_SIG_WITH_SHA224			361
#define OID_ECGDSA_SIG_WITH_SHA256			362
#define OID_ECGDSA_SIG_WITH_SHA384			363
#define OID_ECGDSA_SIG_WITH_SHA512			364
#define OID_SECT163K1						387
#define OID_SECT163R1						388
#define OID_SECT239K1						389
#define OID_SECT113R1						390
#define OID_SECT113R2						391
#define OID_SECT112R1						392
#define OID_SECT112R2						393
#define OID_SECT160R1						394
#define OID_SECT160K1						395
#define OID_SECT256K1						396
#define OID_SECT163R2						397
#define OID_SECT283K1						398
#define OID_SECT283R1						399
#define OID_SECT131R1						400
#define OID_SECT131R2						401
#define OID_SECT193R1						402
#define OID_SECT193R2						403
#define OID_SECT233K1						404
#define OID_SECT233R1						405
#define OID_SECT128R1						406
#define OID_SECT128R2						407
#define OID_SECT160R2						408
#define OID_SECT192K1						409
#define OID_SECT224K1						410
#define OID_SECT224R1						411
#define OID_SECT384R1						412
#define OID_SECT521R1						413
#define OID_SECT409K1						414
#define OID_SECT409R1						415
#define OID_SECT571K1						416
#define OID_SECT571R1						417
#define OID_AES128_CBC						426
#define OID_AES128_GCM						427
#define OID_AES128_CCM						428
#define OID_AES192_CBC						429
#define OID_AES192_GCM						430
#define OID_AES192_CCM						431
#define OID_AES256_CBC						432
#define OID_AES256_GCM						433
#define OID_AES256_CCM						434
#define OID_SHA256							436
#define OID_SHA384							437
#define OID_SHA512							438
#define OID_SHA224							439
#define OID_SHA3_224						442
#define OID_SHA3_256						443
#define OID_SHA3_384						444
#define OID_SHA3_512						445
#define OID_NS_REVOCATION_URL				453
#define OID_NS_CA_REVOCATION_URL			454
#define OID_NS_CA_POLICY_URL				455
#define OID_NS_COMMENT						456
#define OID_EMPLOYEE_NUMBER					459
#define OID_PKI_MESSAGE_TYPE				465
#define OID_PKI_STATUS						466
#define OID_PKI_FAIL_INFO					467
#define OID_PKI_SENDER_NONCE				468
#define OID_PKI_RECIPIENT_NONCE				469
#define OID_PKI_TRANS_ID					470
#define OID_TPM_MANUFACTURER				476
#define OID_TPM_MODEL						477
#define OID_TPM_VERSION						478
#define OID_TPM_ID_LABEL					479

#define OID_MAX								480

#endif /* OID_H_ */
