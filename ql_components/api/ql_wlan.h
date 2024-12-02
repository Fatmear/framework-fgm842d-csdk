#ifndef __QL_WLAN_H_
#define __QL_WLAN_H_


#include "lwip/nd6.h"
#include <lwip/sockets.h>


#if LWIP_IPV4 && LWIP_IPV6
#define LWIP_IPV4_V6_ON 
#else
#define LWIP_IPV4_ONLY
#endif


typedef struct
{
	int8_t rssi;
}ql_wifi_link_info_t;

/**
 *  @brief  wlan network interface enumeration definition.
 */
typedef enum
{
    QL_SOFT_AP ,  /**< Act as an access point, and other station can connect, 4 stations Max*/
    QL_STATION ,   /**< Act as a station which can connect to an access point*/
    QL_P2P,
} ql_wifi_mode_e;


/**
 *  @brief  Wi-Fi security type enumeration definition.
 */
typedef enum 
{
    QL_SECURITY_TYPE_NONE,        /**< Open system. */
    QL_SECURITY_TYPE_WEP,         /**< Wired Equivalent Privacy. WEP security. */
    QL_SECURITY_TYPE_WPA_TKIP,    /**< WPA /w TKIP */
    QL_SECURITY_TYPE_WPA_AES,     /**< WPA /w AES */
    QL_SECURITY_TYPE_WPA_MIXED,  /**< WPA /w AES or TKIP */
    QL_SECURITY_TYPE_WPA2_TKIP,   /**< WPA2 /w TKIP */
    QL_SECURITY_TYPE_WPA2_AES,    /**< WPA2 /w AES */
    QL_SECURITY_TYPE_WPA2_MIXED,  /**< WPA2 /w AES or TKIP */
    QL_SECURITY_TYPE_WPA3_SAE,	  /**< WPA3 SAE */
    QL_SECURITY_TYPE_WPA3_WPA2_MIXED, /** WPA3 SAE or WPA2 AES */
	QL_SECURITY_TYPE_EAP,         /**< EAP */
	QL_SECURITY_TYPE_OWE,         /**< OWE */
    QL_SECURITY_TYPE_AUTO,        /**< It is used when calling @ref bkWlanStartAdv, _BK_ read*/
}ql_wlan_sec_type_e;


typedef struct {
    uint8_t  sync;
    char     sta_ssid[33];
    char     sta_pwd[64];
    uint8_t  sta_bssid[6];
    uint8_t  channel;
    uint8_t  auto_conn;
} ql_wifi_nv_info_t;

/**
 *  @brief  Input network paras, used in bk_wlan_start function.
 */
typedef struct 
{
    char wifi_mode;               /**< DHCP mode: @ref ql_wifi_mode_e.*/
    char wifi_ssid[33];           /**< SSID of the wlan needs to be connected.*/
    char wifi_key[108];            /**< Security key of the wlan needs to be connected, ignored in an open system.*/
    char local_ip_addr[16];       /**< Static IP configuration, Local IP address. */
    char net_mask[16];            /**< Static IP configuration, Netmask. */
    char gateway_ip_addr[16];     /**< Static IP configuration, Router IP address. */
    char dns_server_ip_addr[16];   /**< Static IP configuration, DNS server IP address. */
    char dhcp_mode;                /**< DHCP mode, @ref DHCP_Disable, @ref DHCP_Client and @ref DHCP_Server. */
    char wifi_bssid[6];
    char reserved[26];
    int  wifi_retry_interval;     /**< Retry interval if an error is occured when connecting an access point,
                                     time unit is millisecond. */
	bool hidden_ssid;			   /**< hidden ssid, only for softap */
									 	
} ql_network_init_s;


typedef struct
{
    char    ssid[32];    /**< SSID of the wlan that needs to be connected. Example: "SSID String". */
    char    bssid[6];    /**< BSSID of the wlan needs to be connected. Example: {0xC8 0x93 0x46 0x11 0x22 0x33}. */
    uint8_t channel;     /**< Wlan's RF frequency, channel 0-13. 1-13 means a fixed channel
                            that can speed up a connection procedure, 0 is not a fixed input
                            means all channels are possible*/
    uint8_t security;
} ql_apinfo_adv_s;


typedef struct ql_network_InitTypeDef_adv_st
{
    ql_apinfo_adv_s ap_info;         /**< @ref apinfo_adv_t. */
    char  key[64];                /**< Security key or PMK of the wlan. */
    int   key_len;                /**< The length of the key. */
    char  local_ip_addr[16];      /**< Static IP configuration, Local IP address. */
    char  net_mask[16];           /**< Static IP configuration, Netmask. */
    char  gateway_ip_addr[16];    /**< Static IP configuration, Router IP address. */
    char  dns_server_ip_addr[16];  /**< Static IP configuration, DNS server IP address. */
    char  dhcp_mode;               /**< DHCP mode, @ref DHCP_Disable, @ref DHCP_Client and @ref DHCP_Server. */
    char  reserved[32];
    int   wifi_retry_interval;    /**< Retry interval if an error is occured when connecting an access point,
                                  time unit is millisecond. */
} ql_network_InitTypeDef_adv_s;

typedef struct ql_network_init_ap_st
{
    char wifi_ssid[32];
    char wifi_key[64];
    uint8_t channel;
    uint8_t security;
	uint8_t ssid_hidden;
	uint8_t max_con;
    char local_ip_addr[16];
    char net_mask[16];
    char gateway_ip_addr[16];
    char dns_server_ip_addr[16];
    char dhcp_mode;
    char reserved[32];
    int  wifi_retry_interval;
} ql_network_init_ap_s;

typedef struct 
{
		char ssid[33];	
		char ApPower;	
		uint8_t bssid[6];
		char channel;	
		uint8_t security;
} ql_apliststruct;

typedef  struct  ql_ScanResult_adv
{
	char ApNum; 	  /**< The number of access points found in scanning.*/
    ql_apliststruct *ql_aplist_s;
} ql_scan_result_s;

typedef struct
{
	uint8_t dhcp;       /**< DHCP mode: @ref DHCP_Disable, @ref DHCP_Client, @ref DHCP_Server.*/
	char    ip[16];     /**< Local IP address on the target wlan interface: @ref wlanInterfaceTypedef.*/
    char    gate[16];   /**< Router IP address on the target wlan interface: @ref wlanInterfaceTypedef.*/
    char    mask[16];   /**< Netmask on the target wlan interface: @ref wlanInterfaceTypedef.*/
    char    dns[16];    /**< DNS server IP address.*/
    char    mac[16];    /**< MAC address, example: "C89346112233".*/
    char    broadcastip[16];
	char 	standby_dns[16];/**< standby DNS server IP address.*/
} ql_ip_status_s;

typedef struct 
{
	int conn_state;       /**< The link to wlan is established or not, 0: disconnected, 1: connected. */
    int wifi_strength;      /**< Signal strength of the current connected AP */
    uint8_t  ssid[33];      /**< SSID of the current connected wlan */
    uint8_t  bssid[6];      /**< BSSID of the current connected wlan */
    uint16_t  aid;          /**< BSSID of the current connected wlan */
    int      channel;       /**< Channel of the current connected wlan */
    uint8_t security;
} ql_link_status_s;


#ifdef LWIP_IPV4_ONLY
struct _ip4_addr {
  uint32 addr;
};
typedef struct _ip4_addr ql_ip_addr_t;
#endif

#ifdef  LWIP_IPV4_V6_ON
struct _ip4_addr {
  uint32 addr;
};
typedef struct _ip4_addr ql_ip4_addr_t;

struct _ip6_addr {
  uint32 addr[4];
#if LWIP_IPV6_SCOPES
  uint8_t zone;
#endif /* LWIP_IPV6_SCOPES */
};

/** IPv6 address */
typedef struct _ip6_addr ql_ip6_addr_t;
typedef struct _ip_addr {
  union {
    ql_ip6_addr_t ip6;
    ql_ip4_addr_t ip4;
  } u_addr;
  /** @ref lwip_ip_addr_type */
  uint8_t type;
} ql_ip_addr_t;
#endif

#if LWIP_IPV6
typedef struct{
char ip6_str[128];
char gw6_str[128];
char mask6_str[128];
char dns6_str[128];
}ql_ip6_addr_s;
#endif

typedef enum {
    /* for station mode */
	QL_WLAN_EVT_STA_IDLE = 0,
	QL_WLAN_EVT_STA_CONNECTING,
    QL_WLAN_EVT_STA_BEACON_LOSE,
    QL_WLAN_EVT_STA_PASSWORD_WRONG,
    QL_WLAN_EVT_STA_NO_AP_FOUND,
    QL_WLAN_EVT_STA_ASSOC_FULL,
    QL_WLAN_EVT_STA_DISCONNECTED,    /* disconnect with server */
    QL_WLAN_EVT_STA_CONNECT_FAILED, /* authentication failed */
	QL_WLAN_EVT_STA_CONNECTED,	 /* authentication success */
	QL_WLAN_EVT_STA_GOT_IP,
    /* for softap mode */
    QL_WLAN_EVT_AP_CONNECTED,          /* a client association success */
    QL_WLAN_EVT_AP_DISCONNECTED,    /* a client disconnect */
    QL_WLAN_EVT_AP_CONNECT_FAILED, /* a client association failed */
    QL_WLAN_EVT_MAX
}ql_wlan_evt_type;



typedef void (*ql_func_status_callback)(ql_wlan_evt_type *ctxt);
typedef void (*ql_func_scan_callback)(void *arg, unsigned char vif_idx);
typedef void (*ql_monitor_cb_t)(uint8_t *data, int len, ql_wifi_link_info_t *info);

extern int ql_wlan_get_mac(char * mac);

extern int ql_wlan_set_mac(char * mac);

extern int ql_wlan_start(ql_network_init_s *inNetworkInitPara);

extern int ql_wlan_start_sta_adv(ql_network_InitTypeDef_adv_s *inNetworkInitParaAdv);

extern int ql_wlan_stop(ql_wifi_mode_e mode);

extern int ql_wlan_start_scan(void);

extern int ql_wlan_scan_ap_reg_cb(ql_func_scan_callback ind_cb);

extern int ql_wlan_sta_scan_result(ql_scan_result_s *results);

extern int ql_wlan_start_assign_scan(UINT8 **ssid_ary, UINT8 ssid_num);

extern int ql_wlan_status_register_cb(ql_func_status_callback cb);

extern int ql_wlan_start_monitor(void);

extern int ql_wlan_stop_monitor(void);

extern int ql_wlan_register_monitor_cb(ql_monitor_cb_t fn);

extern int ql_wlan_ap_para_info_get(ql_network_init_ap_s *ap_info);

extern int ql_wlan_get_ip_status(ql_ip_status_s *outNetpara, ql_wifi_mode_e inInterface);

#if LWIP_IPV6
/*
return:
-1: other error
0: no invalid global ipv6 addr
1: has valid global ipv6 addr 
*/
extern int ql_wlan_get_ip6_global_addr(ql_ip6_addr_s *ip6, ql_wifi_mode_e inInterface);
#endif

extern int ql_wlan_get_link_status(ql_link_status_s *outStatus);

extern int ql_wlan_get_channel(void );

extern int ql_wlan_set_channel(int channel);

extern int ql_wlan_set_channel_sync(int channel);

extern int ql_sta_chiper_type(void);

extern int ql_wlan_ota_download(const char *uri);

extern uint32 ql_ap_ip_is_start(void);

extern uint32 ql_sta_ip_is_start(void);

extern int ql_airkiss_start(uint8_t start);

extern uint32 ql_airkiss_is_at_its_context(void);

extern int ql_wifi_stainfo_write(ql_wifi_nv_info_t *wifi_info);

extern int ql_wifi_stainfo_read(ql_wifi_nv_info_t *wifi_info);

extern int ql_wifi_stainfo_remove(void);

extern int ql_uart_baudrate_write(int *baud);

extern int ql_uart_baudrate_read(int *baud);

extern int ql_uart_baudrate_remove(void);

#endif

