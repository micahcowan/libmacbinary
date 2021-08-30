// MacBinary header
#define MB_HEADER_LENGTH        128u
#define MB_F_DATA_FORK_LENGTH   83u
#define MB_F_RES_FORK_LENGTH    87u


// Resource Fork header
#define RF_F_RES_DATA_OFF       0u
#define RF_F_RES_MAP_OFF        4u
#define RF_F_RES_DATA_LENGTH    8u
#define RF_F_RES_MAP_LENGTH     12u

#define RF_APP_DATA_OFF         128u
#define RF_APP_DATA_LENGTH      128u

// Resource Map header
//      16 bytes reserved for copy of resource header
//      4  bytes reserved for handle of next resource map to search
//      2  bytes reserved for file ref num
#define RFM_F_RES_FILE_ATTRS    22u
#define RFM_F_TYPE_LIST_OFF     24u
#define RFM_F_NAME_LIST_OFF     26u

// Reource Type List (just num)
#define RFTL_F_NUM_TYPES        0u
#define RFTL_F_START_OF_ENTRIES 2u

// Resource Type List entries
#define RFTLE_F_TYPE_NAME        0u
#define RFTLE_F_NUM_RES          4u
#define RFTLE_F_REF_LIST_OFF     6u
#define RFTLE_SIZE               8u

// Resource references
#define RF_RES_F_ID             0u
#define RF_RES_F_NAME_OFF       2u
#define RF_RES_F_ATTR           4u
#define RF_RES_F_DATA_LEN_OFF   5u  // 3 bytes! for an offset!
//      4 bytes reserved for handle to resource
#define RF_RES_SIZE             12u
