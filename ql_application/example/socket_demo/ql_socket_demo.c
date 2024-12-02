
#include "lwip_netif_address.h"
#include "sockets.h"
#include "ql_osi.h"
#include "net.h"
#include "string.h"

#define ql_debug os_printf

#define sta_ip_test 0
#define ap_name "quectel"
#define ap_pwd  "12345678"

ql_task_t	socket_server_test_thread_handle = NULL;
extern void ql_demo_sta_app_init(char *oob_ssid,char *connect_key);
extern void ql_demo_softap_app_init(char *ap_ssid, char *ap_key);
/***************socket server test******************/

void ql_socket_server_demo_thread(void *param)
{
	struct wlan_ip_config local_ip;
	int ret = 0;
	int sock_fd = -1;
	int sock_nbio = 0;
	u8 recv_buf[1024] = {0};

	// char    local_addr[256] = {0};
    struct sockaddr_in server_addr;
	ql_rtos_task_sleep_ms(2000);
#if sta_ip_test
    ql_demo_sta_app_init("zxcvbnm", "12345678");
   do
   {
      ql_rtos_task_sleep_ms(1000);
      ql_debug("connectting");
   } while (0 == sta_ip_is_start());
   ql_rtos_task_sleep_ms(2000);
    net_get_if_addr(&local_ip, net_get_sta_handle());
#else
	ql_demo_softap_app_init(ap_name,ap_pwd);//让模块打开热点
   	ql_rtos_task_sleep_ms(2000);
	net_get_if_addr(&local_ip, net_get_uap_handle());
#endif
	ret = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//创建Socket
	if (ret < 0)
	{
		ql_debug("*** socket create fail ***\r\n");
		goto exit;
	}
	ql_debug("*** socket create ret: %d ***\r\n",ret);
	sock_fd = ret;
	/* 设置Socket为阻塞/非阻塞模式 */
	ioctl(sock_fd, FIONBIO, &sock_nbio);
	int on = 1;
	/* 绑定本地网口 */
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(1234); 
	server_addr.sin_addr.s_addr=local_ip.ipv4.address;
	ql_debug("--------->ip: %s\n",inet_ntoa(server_addr.sin_addr.s_addr));
	/* 复用本地地址和端口 */
	setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	on = 1;
	setsockopt(sock_fd,SOL_SOCKET,SO_REUSEPORT,&on,sizeof(on));
	/* 绑定 */
	ret = bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (ret < 0)
	{
		ql_debug("*** bind fail ***\r\n");
		goto exit;
	}

	if(listen(sock_fd, 5) == -1)//监听
	{
		ql_debug("*** listen fail ***\r\n");
		goto exit;
	}
	ql_debug("*** listen succ ***\r\n");
	struct sockaddr_in clientaddr;
	int len = sizeof(clientaddr);
	/* 客户端来连接 */
	int client_fd = accept(sock_fd,(struct sockaddr *)&clientaddr,(socklen_t *)&len);
	if(client_fd == -1)
	{
		ql_debug("*** accept fail ***\r\n");
		goto exit;
	}
	ql_debug("*** connect succ ***\r\n");
	while(1)
	{
		/* 接收数据 */
		int num = recv(client_fd,recv_buf,sizeof(recv_buf),0);
		if(num == -1)
		{
			ql_debug("*** accept fail ***\r\n");
			goto exit;
		}
		recv_buf[num]= '\0';
		ql_debug("recv data: [%d]%s\r\n", ret, recv_buf);
	}
exit:
	if (sock_fd >= 0)
	{
		struct linger linger = {0};

		linger.l_onoff = 1;
		linger.l_linger = 10;
		/* 延迟关闭连接 */
		setsockopt(sock_fd, SOL_SOCKET, SO_LINGER, &linger, sizeof(linger));
		/* 保持连接 */
		setsockopt(sock_fd, IPPROTO_TCP, TCP_KEEPALIVE, &linger.l_linger, sizeof(linger.l_linger));
		close(sock_fd);
	}
	ql_rtos_task_delete(socket_server_test_thread_handle);
}


void ql_socket_server_demo_thread_creat(void)
{
    int ret;
	ret = ql_rtos_task_create(&socket_server_test_thread_handle,
	                	(unsigned short)2048,
					   THD_EXTENDED_APP_PRIORITY,
					   "socket server test",
					   ql_socket_server_demo_thread,  
					   0);
	if (ret != kNoErr) {
	os_printf("Error: Failed to create socket server test thread: %d\r\n",ret);
	goto init_err;
	} 
	return;   
	init_err:
	if( socket_server_test_thread_handle != NULL ) {
		ql_rtos_task_delete(socket_server_test_thread_handle);
	}
}

