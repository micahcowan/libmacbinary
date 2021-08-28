// MacBinary header
#define MB_HEADER_LENGTH        128u
#define MB_F_DATA_FORK_LENGTH   83u
#define MB_F_RES_FORK_LENGTH    87u


// Resource Fork header
#define RF_F_RES_DATA_OFF       0u
#define RF_F_RES_MAP_OFF        4u
#define RF_F_RES_DATA_LENGTH    8u
#define RF_F_RES_MAP_LENGTH     12u

// Resource Map header
#define RFM_F_NUM_TYPES         0u
#define RFM_F_TYPE_LIST         2u

// Resource Map entries
#define RFME_F_TYPE_NAME        0u
#define RFME_F_NUM_RES          4u
#define RFME_F_REF_LIST_OFF     6u
#define RFME_SIZE               8u
