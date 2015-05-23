#ifndef DEFINES_H
#define DEFINES_H

#define MAIN_INI_SECTION                    "main"

#define FILE_TEMPLATE                       "aa_simulator_results_"
#define STRIPE_SIZE_KB                      128
#define STRIPE_SIZE_BYTES                   131072
#define SP_COUNT                            2
#define DEFAULT_REQUESTS_COUNT              1


//Read traces
#define RANDOM_READ_TRACE                   "random"
#define SEQUENTIAL_READ_TRACE               "sequential"
#define USER_DEFINED_READ_TRACE             "user-defined"
#define RANDOM_LOCALITY_TYPE                "RANDOM_LOCALITY_TYPE"
#define RANDOM_LOCALITY_NONE                "none"
#define RANDOM_LOCALITY_SPACIAL             "spacial"
#define RANDOM_LOCALITY_TIME                "time"

#define SPACIAL_LOCALITY_LEFT_ADDRESS       "SPACIAL_LOCALITY_LEFT_ADDRESS"
#define SPACIAL_LOCALITY_RIGHT_ADDRESS      "SPACIAL_LOCALITY_RIGHT_ADDRESS"
#define SPACIAL_LOCALITY_PROBABILITY        "SPACIAL_LOCALITY_PROBABILITY"

#define TIME_LOCALITY_MEMORIZED_QUEUE_LENGTH      "TIME_LOCALITY_MEMORIZED_QUEUE_LENGTH"
#define TIME_LOCALITY_PROBABILITY           "TIME_LOCALITY_PROBABILITY"


//////////String constants

//// Modeling options
#define MODELING_STEPS_NUMBER               "MODELING_STEPS_NUMBER"
#define RAID_FILE                           "RAID_FILE"
#define RAID_SIZE                           "RAID_SIZE"

// Latencies
#define LB_SELECTING_LATENCY                "LB_SELECTING_LATENCY"
#define APP_LB_REQUEST_SEND_LATENCY         "APP_LB_REQUEST_SEND_LATENCY"
#define APP_SP_DATA_SEND_LATENCY            "APP_SP_DATA_SEND_LATENCY"
#define CACHE_CHECKUP_LATENCY               "CACHE_CHECKUP_LATENCY"
#define CACHE_DATA_RETRIVAL_LATENCY         "CACHE_DATA_RETRIVAL_LATENCY"
#define RAID_SP_REQUEST_SEND_LATENCY        "RAID_SP_REQUEST_SEND_LATENCY"
#define RAID_SP_DATA_SEND_LATENCY           "RAID_SP_DATA_SEND_LATENCY"
#define INTERCONNECT_CHECKUP_LATENCY        "INTERCONNECT_CHECKUP_LATENCY"
#define INTERCONNECT_DATA_LOAD_LATENCY      "INTERCONNECT_DATA_LOAD_LATENCY"
#define RAND_RAID_SP_DATA_SEND_LATENCY      "RAND_RAID_SP_DATA_SEND_LATENCY"
#define QUEUE_WAITING_IC_LATENCY            "QUEUE_WAITING_IC_LATENCY"
#define QUEUE_WAITING_RAID_LATENCY          "QUEUE_WAITING_RAID_LATENCY"

// Storage element names
#define APPLICATION                         "APPLICATION"
#define LOAD_BALANCER                       "LOAD_BALANCER"
#define RAID                                "RAID"
#define STORAGE_PROCESSOR                   "STORAGE_PROCESSOR"
#define RR_NODE_WORKLOAD                    "RR_NODE_WORKLOAD"

// Read pattern
#define READ_REQUESTS_COUNT                 "READ_REQUESTS_COUNT"
#define READ_BLOCK_SIZE                     "READ_BLOCK_SIZE"
#define READ_TRACE_TYPE                     "READ_TRACE_TYPE"
#define READ_TRACE_FILE                     "READ_TRACE_FILE"


//Cache parameters
#define CACHE_SIZE                          "CACHE_SIZE"
#define READ_AHEAD_BLOCK                    "READ_AHEAD_BLOCK"
#define CACHE_POLICY                        "CACHE_POLICY"
#define CACHE_RATIO                         "CACHE_RATIO"


// Cache policy
#define CACHE_POLICY_COHERENT                            "coherent"
#define CACHE_POLICY_NON_COHERENT                        "independent"
#define CACHE_POLICY_NON_COHERENT_WITH_CROSS_SP_LOOKUP   "independent_with_cross_sp_lookup"

//ReadAhead
#define READ_AHEAD_SEQUENCE_LENGTH  "READ_AHEAD_SEQUENCE_LENGTH"
#define READ_AHEAD_DISTANCE		    "READ_AHEAD_DISTANCE"
#define READ_AHEAD_TYPE             "READ_AHEAD_TYPE"
#define READ_AHEAD_SIMPLE           "simple"
#define READ_AHEAD_SMART            "smart"
#define READ_AHEAD_NONE             "none"

// CommandLine options
#define CL_VERBOSE_OPTION		    "--verbose"
#define CL_QUIET_OPTION             "--quiet"

// Load balancing algorithms
#define LOAD_BALANCING_ALGORITHM    "LOAD_BALANCING_ALGORITHM"
#define ROUND_ROBIN_ALGORITHM       "round_robin"
#define MIN_QUEUE_DEPTH_ALGORITHM   "min_queue_depth"

// Events
#define APPLY_STEP                  "APPLY_STEP"
#define PARAMETER_NAME              "PARAMETER_NAME"
#define NEW_VALUE                   "NEW_VALUE"
#define VALUE_DELTA                 "VALUE_DELTA"
#define STEPS_NUMBER_TO_APPLY       "STEPS_NUMBER_TO_APPLY"

// Max Throughput

#define MAX_THROUGHPUT_IC           "MAX_THROUGHPUT_IC"
#define MAX_THROUGHPUT_RAID         "MAX_THROUGHPUT_RAID"

// RedirectControl

#define IC_REDIRECT_CONTROL_LONGEVITY   "IC_REDIRECT_CONTROL_LONGEVITY"
#define IC_REDIRECT_CONTROL_ENABLED     "IC_REDIRECT_CONTROL_ENABLED"
#define IC_REDIRECT_CONTROL_MAX_QUEUE_LENGTH "IC_REDIRECT_CONTROL_MAX_QUEUE_LENGTH"
#define DEFAULT_MAX_QUEUE_LENGTH	0

#endif // DEFINES_H
