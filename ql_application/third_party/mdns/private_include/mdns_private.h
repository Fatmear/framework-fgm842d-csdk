// Copyright 2015-2017 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#ifndef MDNS_PRIVATE_H_
#define MDNS_PRIVATE_H_
#include "ql_type.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "timers.h"
#include "rtos.h"
#include "rtos_pub.h"


typedef void*  mdns_netif_t;

//#define MDNS_ENABLE_DEBUG
#ifdef MDNS_ENABLE_DEBUG
//#define _mdns_dbg_printf(...) bk_printf(__VA_ARGS__)
#define _mdns_dbg_printf  bk_printf
#endif

static inline char * strdup(const char *s)
{
    unsigned int len = strlen(s) + 1;
    void *new = malloc(len);
    if (new == NULL) {
        return NULL;
    }
    return (char *)memcpy(new, s, len);
}

static inline char * strndup(const char *s, size_t n)
{
    unsigned int len = strlen(s) + 1;
    unsigned int copy_len = (n < len)?n:len;
    void *new = malloc(copy_len*sizeof(char));
    if (new == NULL) {
        return NULL;
    }
    memset(new, 0x00, copy_len*sizeof(char));
    return (char *)memcpy(new, s, copy_len);
}

#define MIN(a,b) a>b?b:a
/** The maximum number of services */
#define MDNS_MAX_SERVICES             25

#define MDNS_ANSWER_PTR_TTL         4500
#define MDNS_ANSWER_TXT_TTL         4500
#define MDNS_ANSWER_SRV_TTL         120
#define MDNS_ANSWER_A_TTL           120
#define MDNS_ANSWER_AAAA_TTL        120

#define MDNS_FLAGS_AUTHORITATIVE    0x8400
#define MDNS_FLAGS_DISTRIBUTED      0x0200

#define MDNS_NAME_REF               0xC000

//custom type! only used by this implementation
//to help manage service discovery handling
#define MDNS_TYPE_SDPTR             0x0032

#define MDNS_CLASS_IN               0x0001
#define MDNS_CLASS_ANY              0x00FF
#define MDNS_CLASS_IN_FLUSH_CACHE   0x8001

#define MDNS_ANSWER_ALL             0x3F
#define MDNS_ANSWER_PTR             0x08
#define MDNS_ANSWER_TXT             0x04
#define MDNS_ANSWER_SRV             0x02
#define MDNS_ANSWER_A               0x01
#define MDNS_ANSWER_AAAA            0x10
#define MDNS_ANSWER_NSEC            0x20
#define MDNS_ANSWER_SDPTR           0x80
#define MDNS_ANSWER_AAAA_SIZE       16

#define MDNS_SERVICE_PORT           5353                    // UDP port that the server runs on
#define MDNS_SERVICE_STACK_DEPTH    4096                    // Stack size for the service thread
#define MDNS_TASK_PRIORITY          3


#define MDNS_SERVICE_ADD_TIMEOUT_MS      1000

#define MDNS_PACKET_QUEUE_LEN       16                      // Maximum packets that can be queued for parsing
#define MDNS_ACTION_QUEUE_LEN       16                      // Maximum actions pending to the server
#define MDNS_TXT_MAX_LEN            1024                    // Maximum string length of text data in TXT record
#define MDNS_NAME_MAX_LEN           64                      // Maximum string length of hostname, instance, service and proto
#define MDNS_NAME_BUF_LEN           (MDNS_NAME_MAX_LEN+1)   // Maximum char buffer size to hold hostname, instance, service or proto
#define MDNS_MAX_PACKET_SIZE        1460                    // Maximum size of mDNS  outgoing packet

#define MDNS_HEAD_LEN               12
#define MDNS_HEAD_ID_OFFSET         0
#define MDNS_HEAD_FLAGS_OFFSET      2
#define MDNS_HEAD_QUESTIONS_OFFSET  4
#define MDNS_HEAD_ANSWERS_OFFSET    6
#define MDNS_HEAD_SERVERS_OFFSET    8
#define MDNS_HEAD_ADDITIONAL_OFFSET 10

#define MDNS_TYPE_OFFSET            0
#define MDNS_CLASS_OFFSET           2
#define MDNS_TTL_OFFSET             4
#define MDNS_LEN_OFFSET             8
#define MDNS_DATA_OFFSET            10

#define MDNS_SRV_PRIORITY_OFFSET    0
#define MDNS_SRV_WEIGHT_OFFSET      2
#define MDNS_SRV_PORT_OFFSET        4
#define MDNS_SRV_FQDN_OFFSET        6

#define MDNS_TIMER_PERIOD_MS        1

#define MDNS_SERVICE_LOCK()     xSemaphoreTake(_mdns_service_semaphore, portMAX_DELAY)
#define MDNS_SERVICE_UNLOCK()   xSemaphoreGive(_mdns_service_semaphore)

#if BYTE_ORDER == BIG_ENDIAN
#define mdns_netif_htonl(x) ((uint32_t)(x))
#else
#define mdns_netif_htonl(x) ((((x) & (uint32_t)0x000000ffUL) << 24) | \
                      (((x) & (uint32_t)0x0000ff00UL) <<  8) | \
                      (((x) & (uint32_t)0x00ff0000UL) >>  8) | \
                      (((x) & (uint32_t)0xff000000UL) >> 24))
#endif

#define mdns_netif_ip4_makeu32(a,b,c,d) (((uint32_t)((a) & 0xff) << 24) | \
                               ((uint32_t)((b) & 0xff) << 16) | \
                               ((uint32_t)((c) & 0xff) << 8)  | \
                                (uint32_t)((d) & 0xff))

// Access address in 16-bit block
#define MDNS_IP6_ADDR_BLOCK1(ip6addr) ((uint16_t)((mdns_netif_htonl((ip6addr)->addr[0]) >> 16) & 0xffff))
#define MDNS_IP6_ADDR_BLOCK2(ip6addr) ((uint16_t)((mdns_netif_htonl((ip6addr)->addr[0])) & 0xffff))
#define MDNS_IP6_ADDR_BLOCK3(ip6addr) ((uint16_t)((mdns_netif_htonl((ip6addr)->addr[1]) >> 16) & 0xffff))
#define MDNS_IP6_ADDR_BLOCK4(ip6addr) ((uint16_t)((mdns_netif_htonl((ip6addr)->addr[1])) & 0xffff))
#define MDNS_IP6_ADDR_BLOCK5(ip6addr) ((uint16_t)((mdns_netif_htonl((ip6addr)->addr[2]) >> 16) & 0xffff))
#define MDNS_IP6_ADDR_BLOCK6(ip6addr) ((uint16_t)((mdns_netif_htonl((ip6addr)->addr[2])) & 0xffff))
#define MDNS_IP6_ADDR_BLOCK7(ip6addr) ((uint16_t)((mdns_netif_htonl((ip6addr)->addr[3]) >> 16) & 0xffff))
#define MDNS_IP6_ADDR_BLOCK8(ip6addr) ((uint16_t)((mdns_netif_htonl((ip6addr)->addr[3])) & 0xffff))

#define IPSTR "%d.%d.%d.%d"
#define mdns_ip4_addr_get_byte(ipaddr, idx) (((const uint8_t*)(&(ipaddr)->addr))[idx])
#define mdns_ip4_addr1(ipaddr) mdns_ip4_addr_get_byte(ipaddr, 0)
#define mdns_ip4_addr2(ipaddr) mdns_ip4_addr_get_byte(ipaddr, 1)
#define mdns_ip4_addr3(ipaddr) mdns_ip4_addr_get_byte(ipaddr, 2)
#define mdns_ip4_addr4(ipaddr) mdns_ip4_addr_get_byte(ipaddr, 3)


#define mdns_ip4_addr1_16(ipaddr) ((uint16_t)mdns_ip4_addr1(ipaddr))
#define mdns_ip4_addr2_16(ipaddr) ((uint16_t)mdns_ip4_addr2(ipaddr))
#define mdns_ip4_addr3_16(ipaddr) ((uint16_t)mdns_ip4_addr3(ipaddr))
#define mdns_ip4_addr4_16(ipaddr) ((uint16_t)mdns_ip4_addr4(ipaddr))

#define IP2STR(ipaddr) mdns_ip4_addr1_16(ipaddr), \
    mdns_ip4_addr2_16(ipaddr), \
    mdns_ip4_addr3_16(ipaddr), \
    mdns_ip4_addr4_16(ipaddr)

#if LWIP_IPV6
#define IPV6STR "%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x"

#define IPV62STR(ipaddr) MDNS_IP6_ADDR_BLOCK1(&(ipaddr)),     \
    MDNS_IP6_ADDR_BLOCK2(&(ipaddr)),     \
    MDNS_IP6_ADDR_BLOCK3(&(ipaddr)),     \
    MDNS_IP6_ADDR_BLOCK4(&(ipaddr)),     \
    MDNS_IP6_ADDR_BLOCK5(&(ipaddr)),     \
    MDNS_IP6_ADDR_BLOCK6(&(ipaddr)),     \
    MDNS_IP6_ADDR_BLOCK7(&(ipaddr)),     \
    MDNS_IP6_ADDR_BLOCK8(&(ipaddr))
#endif

#define queueToEnd(type, queue, item)       \
    if (!queue) {                           \
        queue = item;                       \
    } else {                                \
        type * _q = queue;                  \
        while (_q->next) { _q = _q->next; } \
        _q->next = item;                    \
    }

#define queueDetach(type, queue, item)              \
    if (queue) {                                    \
        if (queue == item) {                        \
            queue = queue->next;                    \
        } else {                                    \
            type * _q = queue;                      \
            while (_q->next && _q->next != item) {  \
                _q = _q->next;                      \
            }                                       \
            if (_q->next == item) {                 \
                _q->next = item->next;              \
                item->next = NULL;                  \
            }                                       \
        }                                           \
    }

#define queueFree(type, queue)  while (queue) { type * _q = queue; queue = queue->next; free(_q); }

#define PCB_STATE_IS_PROBING(s) (s->state > PCB_OFF && s->state < PCB_ANNOUNCE_1)
#define PCB_STATE_IS_ANNOUNCING(s) (s->state > PCB_PROBE_3 && s->state < PCB_RUNNING)
#define PCB_STATE_IS_RUNNING(s) (s->state == PCB_RUNNING)

#ifndef HOOK_MALLOC_FAILED
#define HOOK_MALLOC_FAILED  bk_printf("Cannot allocate memory (line: %d, free heap: %d bytes)", __LINE__, xPortGetFreeHeapSize());
#endif

/** @brief Status of DHCP client or DHCP server */
typedef enum {
    MDNS_NETIF_DHCP_INIT = 0,    /**< DHCP client/server is in initial state (not yet started) */
    MDNS_NETIF_DHCP_STARTED,     /**< DHCP client/server has been started */
    MDNS_NETIF_DHCP_STOPPED,     /**< DHCP client/server has been stopped */
    MDNS_NETIF_DHCP_STATUS_MAX
} mdns_netif_dhcp_status_t;

typedef enum {
    PCB_OFF, PCB_DUP, PCB_INIT,
    PCB_PROBE_1, PCB_PROBE_2, PCB_PROBE_3,
    PCB_ANNOUNCE_1, PCB_ANNOUNCE_2, PCB_ANNOUNCE_3,
    PCB_RUNNING
} mdns_pcb_state_t;

typedef enum {
    MDNS_ANSWER, MDNS_NS, MDNS_EXTRA
} mdns_parsed_record_type_t;

typedef enum {
    ACTION_SYSTEM_EVENT,
    ACTION_HOSTNAME_SET,
    ACTION_INSTANCE_SET,
    ACTION_SERVICE_ADD,
    ACTION_SERVICE_DEL,
    ACTION_SERVICE_INSTANCE_SET,
    ACTION_SERVICE_PORT_SET,
    ACTION_SERVICE_TXT_REPLACE,
    ACTION_SERVICE_TXT_SET,
    ACTION_SERVICE_TXT_DEL,
    ACTION_SERVICES_CLEAR,
    ACTION_SEARCH_ADD,
    ACTION_SEARCH_SEND,
    ACTION_SEARCH_END,
    ACTION_TX_HANDLE,
    ACTION_RX_HANDLE,
    ACTION_TASK_STOP,
    ACTION_MAX
} mdns_action_type_t;


typedef struct {
    uint16 id;
    union {
        struct {
            uint16 qr :1;
            uint16 opCode :4;
            uint16 aa :1;
            uint16 tc :1;
            uint16 rd :1;
            uint16 ra :1;
            uint16 z :1;
            uint16 ad :1;
            uint16 cd :1;
            uint16 rCode :4;//response/error code
        };
        uint16 value;
    } flags;
    uint16 questions; //QDCOUNT
    uint16 answers;   //ANCOUNT
    uint16 servers;   //NSCOUNT
    uint16 additional;//ARCOUNT
} mdns_header_t;

typedef struct {
    char host[MDNS_NAME_BUF_LEN];
    char service[MDNS_NAME_BUF_LEN];
    char proto[MDNS_NAME_BUF_LEN];
    char domain[MDNS_NAME_BUF_LEN];
    uint8 parts;
    uint8 sub;
    bool    invalid;
} mdns_name_t;

typedef struct mdns_parsed_question_s {
    struct mdns_parsed_question_s * next;
    uint16 type;
    bool unicast;
    char * host;
    char * service;
    char * proto;
    char * domain;
} mdns_parsed_question_t;

typedef struct mdns_parsed_record_s {
    struct mdns_parsed_record_s * next;
    mdns_parsed_record_type_t record_type;
    uint16 type;
    uint16 clas;
    uint8 flush;
    uint32 ttl;
    char * host;
    char * service;
    char * proto;
    char * domain;
    uint16 data_len;
    uint8 *data;
} mdns_parsed_record_t;

typedef struct {
    mdns_if_t tcpip_if;
    mdns_ip_protocol_t ip_protocol;
    //struct udp_pcb *pcb;
    ip_addr_t src;
    uint16 src_port;
    uint8 multicast;
    uint8 authoritative;
    uint8 probe;
    uint8 discovery;
    uint8 distributed;
    mdns_parsed_question_t * questions;
    mdns_parsed_record_t * records;
} mdns_parsed_packet_t;

typedef struct {
    mdns_if_t tcpip_if;
    mdns_ip_protocol_t ip_protocol;
    struct pbuf *pb;
    ip_addr_t src;
    ip_addr_t dest;
    uint16 src_port;
    uint8  multicast;
} mdns_rx_packet_t;

typedef struct mdns_txt_linked_item_s {
    const char * key;                       /*!< item key name */
    const char * value;                     /*!< item value string */
    struct mdns_txt_linked_item_s * next;   /*!< next result, or NULL for the last result in the list */
} mdns_txt_linked_item_t;

typedef struct {
    const char * instance;
    const char * service;
    const char * proto;
    uint16  priority;
    uint16  weight;
    uint16  port;
    mdns_txt_linked_item_t * txt;
} mdns_service_t;

typedef struct mdns_srv_item_s {
    struct mdns_srv_item_s * next;
    mdns_service_t * service;
} mdns_srv_item_t;

typedef struct mdns_out_question_s {
    struct mdns_out_question_s * next;
    uint16  type;
    bool unicast;
    const char * host;
    const char * service;
    const char * proto;
    const char * domain;
} mdns_out_question_t;

typedef struct mdns_out_answer_s {
    struct mdns_out_answer_s * next;
    uint16  type;
    uint8   bye;
    uint8  flush;
    mdns_service_t * service;
    const char * custom_instance;
    const char * custom_service;
    const char * custom_proto;
} mdns_out_answer_t;

typedef struct mdns_tx_packet_s {
    struct mdns_tx_packet_s * next;
    uint32    send_at;
    mdns_if_t tcpip_if;
    mdns_ip_protocol_t ip_protocol;
    ip_addr_t dst;
    uint16  port;
    uint16  flags;
    uint8   distributed;
    mdns_out_question_t * questions;
    mdns_out_answer_t * answers;
    mdns_out_answer_t * servers;
    mdns_out_answer_t * additional;
    bool queued;
} mdns_tx_packet_t;

typedef struct {
    mdns_pcb_state_t state;
    struct udp_pcb * pcb;
    mdns_srv_item_t ** probe_services;
    uint8   probe_services_len;
    uint8   probe_ip;
    uint8   probe_running;
    uint16  failed_probes;
} mdns_pcb_t;

typedef enum {
    SEARCH_OFF,
    SEARCH_INIT,
    SEARCH_RUNNING,
    SEARCH_MAX
} mdns_search_once_state_t;

typedef struct mdns_search_once_s {
    struct mdns_search_once_s * next;

    mdns_search_once_state_t state;
    uint32  started_at;
    uint32  sent_at;
    uint32  timeout;
    SemaphoreHandle_t done_semaphore;
    uint16  type;
    uint8   max_results;
    uint8   num_results;
    char * instance;
    char * service;
    char * proto;
    mdns_result_t * result;
} mdns_search_once_t;

typedef struct mdns_server_s {
    struct {
        mdns_pcb_t pcbs[MDNS_IP_PROTOCOL_MAX];
    } interfaces[MDNS_IF_MAX];
    const char * hostname;
    const char * instance;
    mdns_srv_item_t * services;
    SemaphoreHandle_t lock;
    QueueHandle_t action_queue;
    mdns_tx_packet_t * tx_queue_head;
    mdns_search_once_t * search_once;
    beken_timer_t   timer_handle;
} mdns_server_t;

typedef struct {
    mdns_action_type_t type;
    union {
        char * hostname;
        char * instance;
        struct {
            int32_t event_id;
            mdns_netif_t* interface;
        } sys_event;
        struct {
            mdns_srv_item_t * service;
        } srv_add;
        struct {
            mdns_srv_item_t * service;
        } srv_del;
        struct {
            mdns_srv_item_t * service;
            char * instance;
        } srv_instance;
        struct {
            mdns_srv_item_t * service;
            uint16 port;
        } srv_port;
        struct {
            mdns_srv_item_t * service;
            mdns_txt_linked_item_t * txt;
        } srv_txt_replace;
        struct {
            mdns_srv_item_t * service;
            char * key;
            char * value;
        } srv_txt_set;
        struct {
            mdns_srv_item_t * service;
            char * key;
        } srv_txt_del;
        struct {
            mdns_search_once_t * search;
        } search_add;
        struct {
            mdns_tx_packet_t * packet;
        } tx_handle;
        struct {
            mdns_rx_packet_t * packet;
        } rx_handle;
    } data;
} mdns_action_t;

/*
 * @brief  Convert mnds if to esp-netif handle
 *
 * @param  tcpip_if     mdns supported interface as internal enum
 *
 * @return
 *     - ptr to esp-netif on success
 *     - NULL if no available netif for current interface index
 */
mdns_netif_t *_mdns_get_esp_netif(mdns_if_t tcpip_if);

struct netif *_mdns_netif_get_netif_impl(mdns_netif_t *mdns_netif);

#endif /* MDNS_PRIVATE_H_ */
