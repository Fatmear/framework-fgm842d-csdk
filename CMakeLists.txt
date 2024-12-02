cmake_minimum_required(VERSION 3.18)

if(WIN32)
    message(STATUS "windows build .........")
elseif(UNIX)
    message(STATUS "Linux build ...........")
endif()

include(${CMAKE_SOURCE_DIR}/toolchain.cmake)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/ql_build/gccout)
set(target fgm842d)
set(ld_file "${CMAKE_SOURCE_DIR}/ql_build/fgm842d.ld")
set(macro_def "
    -DCFG_OS_FREERTOS=1
    -DBUILDING_LIBCURL
    -DQL_CSDK_SUPPORT
    -DQL_CSDK_MODE=1
    -DUSE_MBEDTLS_2_27_0
    -DQL_PROJECT_FGM842D
")

set(CMAKE_C_LINK_FLAGS "-g -Wl,--gc-sections -marm -mcpu=arm968e-s -mthumb-interwork -nostdlib  -Xlinker -Map=${TARGET}.map -Wl,-wrap,malloc -Wl,-wrap,_malloc_r -Wl,-wrap,free -Wl,-wrap,_free_r -Wl,-wrap,zalloc -Wl,-wrap,calloc -Wl,-wrap,realloc  -Wl,-wrap,_realloc_r -Wl,-wrap,printf -Wl,-wrap,vsnprintf -Wl,-wrap,snprintf -Wl,-wrap,sprintf -Wl,-wrap,puts -Wl,-wrap,mbedtls_ssl_handshake_server_step -Wl,-wrap,mbedtls_ssl_handshake_client_step -Wl,-wrap,mbedtls_ssl_write_client_hello -Wl,-wrap,mbedtls_ssl_read -Wl,-wrap,mbedtls_ssl_write -Wl,-wrap,mbedtls_ssl_free -Wl,-wrap,mbedtls_ssl_session_reset -Wl,-wrap,mbedtls_ssl_setup -Wl,-wrap,mbedtls_ssl_send_alert_message -Wl,-wrap,mbedtls_ssl_close_notify")
set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_LINKER> <CMAKE_C_LINK_FLAGS> -o <TARGET> <OBJECTS> <LINK_LIBRARIES> <LINK_FLAGS>")
set(ASM_OPTIONS "-g -marm -mthumb-interwork -mcpu=arm968e-s -march=armv5te -x assembler-with-cpp")
set(CMAKE_C_FLAGS "-g -mthumb -mcpu=arm968e-s -march=armv5te -mthumb-interwork -mlittle-endian -Os -std=c99 -ffunction-sections -Wall -Wno-implicit-function-declaration  -Wno-format -Wno-unknown-pragmas -fsigned-char -fdata-sections -nostdlib -fno-strict-aliasing")
set(CMAKE_CXX_FLAGS "-g -mthumb -mcpu=arm968e-s -march=armv5te -mthumb-interwork -mlittle-endian -Os -std=c99 -ffunction-sections -Wall -Wno-implicit-function-declaration  -Wno-format -Wno-unknown-pragmas -fsigned-char -fdata-sections -nostdlib -fno-strict-aliasing")

project(fgm842d VERSION 1.0)
enable_language(ASM C)
add_definitions(${macro_def})
add_link_options(-T${ld_file} -Xlinker -Map=${target}.map)


set(app_path  ${CMAKE_SOURCE_DIR}/ql_application)
set(components_path ${CMAKE_SOURCE_DIR}/ql_components)

list(APPEND include_files
    ${CMAKE_SOURCE_DIR}/ql_kernel
    ${CMAKE_SOURCE_DIR}/ql_components
    ${CMAKE_SOURCE_DIR}/ql_components/func/wpa_supplicant_2_9/src/utils
    ${CMAKE_SOURCE_DIR}/ql_components/func/wpa_supplicant_2_9/src/ap
    ${CMAKE_SOURCE_DIR}/ql_components/func/wpa_supplicant_2_9/src/common
    ${CMAKE_SOURCE_DIR}/ql_components/func/wpa_supplicant_2_9/src/drivers
    ${CMAKE_SOURCE_DIR}/ql_components/func/wpa_supplicant_2_9/src/wps
    ${CMAKE_SOURCE_DIR}/ql_components/func/wpa_supplicant_2_9/src
    ${CMAKE_SOURCE_DIR}/ql_components/func/wpa_supplicant_2_9/bk_patch
    ${CMAKE_SOURCE_DIR}/ql_components/func/wpa_supplicant_2_9/hostapd
    ${CMAKE_SOURCE_DIR}/ql_components/func/force_sleep
    ${CMAKE_SOURCE_DIR}/ql_components/func/bk_aware
    ${CMAKE_SOURCE_DIR}/ql_components/func/uart_debug
    ${CMAKE_SOURCE_DIR}/ql_components/func/easy_flash/types/struct2json/inc
    ${CMAKE_SOURCE_DIR}/ql_components/func/easy_flash/types
    ${CMAKE_SOURCE_DIR}/ql_components/func/easy_flash/inc
    ${CMAKE_SOURCE_DIR}/ql_components/func/easy_flash
    ${CMAKE_SOURCE_DIR}/ql_components/func/sensor
    ${CMAKE_SOURCE_DIR}/ql_components/func/ble_wifi_exchange
    ${CMAKE_SOURCE_DIR}/ql_components/func/power_save
    ${CMAKE_SOURCE_DIR}/ql_components/func/user_driver
    ${CMAKE_SOURCE_DIR}/ql_components/func/video_transfer
    ${CMAKE_SOURCE_DIR}/ql_components/func/spidma_intf
    ${CMAKE_SOURCE_DIR}/ql_components/func/include
    ${CMAKE_SOURCE_DIR}/ql_components/func/sim_uart
    ${CMAKE_SOURCE_DIR}/ql_components/func/rwnx_intf
    ${CMAKE_SOURCE_DIR}/ql_components/func/saradc_intf
    ${CMAKE_SOURCE_DIR}/ql_components/func/camera_intf
    ${CMAKE_SOURCE_DIR}/ql_components/func/utf8
    ${CMAKE_SOURCE_DIR}/ql_components/func/ethernet_intf
    ${CMAKE_SOURCE_DIR}/ql_components/func/misc
    ${CMAKE_SOURCE_DIR}/ql_components/func/security
    ${CMAKE_SOURCE_DIR}/ql_components/func/joint_up
    ${CMAKE_SOURCE_DIR}/ql_components/func/base64
    ${CMAKE_SOURCE_DIR}/ql_components/ip/mac
    ${CMAKE_SOURCE_DIR}/ql_components/ip/lmac/src/chan
    ${CMAKE_SOURCE_DIR}/ql_components/ip/lmac/src/tpc
    ${CMAKE_SOURCE_DIR}/ql_components/ip/lmac/src/sta
    ${CMAKE_SOURCE_DIR}/ql_components/ip/lmac/src/p2p
    ${CMAKE_SOURCE_DIR}/ql_components/ip/lmac/src/bfr
    ${CMAKE_SOURCE_DIR}/ql_components/ip/lmac/src/scan
    ${CMAKE_SOURCE_DIR}/ql_components/ip/lmac/src/rd
    ${CMAKE_SOURCE_DIR}/ql_components/ip/lmac/src/rwnx
    ${CMAKE_SOURCE_DIR}/ql_components/ip/lmac/src/tdls
    ${CMAKE_SOURCE_DIR}/ql_components/ip/lmac/src/ps
    ${CMAKE_SOURCE_DIR}/ql_components/ip/lmac/src/mm
    ${CMAKE_SOURCE_DIR}/ql_components/ip/lmac/src/vif
    ${CMAKE_SOURCE_DIR}/ql_components/ip/lmac/src/hal
    ${CMAKE_SOURCE_DIR}/ql_components/ip/lmac/src/tx/txl
    ${CMAKE_SOURCE_DIR}/ql_components/ip/lmac/src/tx
    ${CMAKE_SOURCE_DIR}/ql_components/ip/lmac/src/rx
    ${CMAKE_SOURCE_DIR}/ql_components/ip/lmac/src/rx/rxl
    ${CMAKE_SOURCE_DIR}/ql_components/ip/lmac/src/td
    ${CMAKE_SOURCE_DIR}/ql_components/ip/common
    ${CMAKE_SOURCE_DIR}/ql_components/ip/umac/src/mfp
    ${CMAKE_SOURCE_DIR}/ql_components/ip/umac/src/me
    ${CMAKE_SOURCE_DIR}/ql_components/ip/umac/src/sm
    ${CMAKE_SOURCE_DIR}/ql_components/ip/umac/src/scanu
    ${CMAKE_SOURCE_DIR}/ql_components/ip/umac/src/rxu
    ${CMAKE_SOURCE_DIR}/ql_components/ip/umac/src/txu
    ${CMAKE_SOURCE_DIR}/ql_components/ip/umac/src/mesh
    ${CMAKE_SOURCE_DIR}/ql_components/ip/umac/src/llc
    ${CMAKE_SOURCE_DIR}/ql_components/ip/umac/src/ftm
    ${CMAKE_SOURCE_DIR}/ql_components/ip/umac/src/rc
    ${CMAKE_SOURCE_DIR}/ql_components/ip/umac/src/bam
    ${CMAKE_SOURCE_DIR}/ql_components/ip/umac/src/apm
    ${CMAKE_SOURCE_DIR}/ql_components/ip/ke
    ${CMAKE_SOURCE_DIR}/ql_components/os/FreeRTOSv9.0.0
    ${CMAKE_SOURCE_DIR}/ql_components/os/include
    ${CMAKE_SOURCE_DIR}/ql_components/driver/rc_beken
    ${CMAKE_SOURCE_DIR}/ql_components/driver/calendar
    ${CMAKE_SOURCE_DIR}/ql_components/driver/dma
    ${CMAKE_SOURCE_DIR}/ql_components/driver/wdt
    ${CMAKE_SOURCE_DIR}/ql_components/driver/sys_ctrl
    ${CMAKE_SOURCE_DIR}/ql_components/driver/general_dma
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/ui
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/app/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/lan
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/lan/lanc/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/lan/lans/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/htp/htpc/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/htp/htpt/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/htp
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/dis/disc/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/dis/diss/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/uds
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/uds/udsc/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/uds/udss/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/pasp/paspc/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/pasp
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/pasp/pasps/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/bas/basc/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/bas/bass/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/bk_comm/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/cpp
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/cpp/cpps/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/cpp/cppc/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/blp/blps/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/blp
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/blp/blpc/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/tip/tipc/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/tip/tips/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/tip
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/prox/proxm/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/prox/proxr/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/wscp/wscs/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/wscp/wscc/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/wscp
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/rscp/rscps/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/rscp/rscpc/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/rscp
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/bk_sdp/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/hrp
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/hrp/hrps/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/hrp/hrpc/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/bcs/bcsc/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/bcs
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/bcs/bcss/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/find/findl/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/find/findt/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/cscp
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/cscp/cscpc/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/cscp/cscps/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/anp
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/anp/anps/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/anp/anpc/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/scpp/scpps/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/scpp
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/scpp/scppc/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/glp/glpc/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/glp
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/glp/glps/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/hogp/hogprh/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/hogp/hogpd/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/hogp
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_pub/profiles/hogp/hogpbh/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/ip/ble/hl/src/inc
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/ip/ble/hl/src/l2cap
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/ip/ble/hl/src/gap/gapc
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/ip/ble/hl/src/gap/gapm
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/ip/ble/hl/src/gap
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/ip/ble/hl/src/gatt
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/ip/ble/hl/inc
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/ip/ble/hl/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/ip/ble/iso/data_path/isoohci/src
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/ip/ble/iso/data_path/isoohci/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/ip/ble/iso/data_path
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/ip/ble/iso/data_path/isogen/src
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/ip/ble/iso/data_path/isogen/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/ip/ble/ll/src
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/ip/ble/ll/src/lli
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/ip/ble/ll/src/llc
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/ip/ble/ll/src/llm
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/ip/ble/ll/src/lld
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/ip/ble/ll/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/ip/ble/ll/import/reg
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/ip/hci/src
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/ip/hci/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/ip/ahi/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/ip/sch/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/ip/sch/import
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/ip/em/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/modules/aes/src
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/modules/aes/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/modules/dbg/src
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/modules/dbg/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/modules/ecc_p256/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/modules/common/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/modules/rwip/src
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/modules/rwip/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/modules/rwip/import/reg
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/modules/ke/src
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/modules/ke/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/ble_lib/modules/h4tl/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/arch/armv5
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/arch/armv5/compiler
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/arch/armv5/ll
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/platform/7238/nvds/api
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/platform/7238/entry
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/platform/7238/config
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/platform/7238/driver/reg
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/platform/7238/driver/rf
    ${CMAKE_SOURCE_DIR}/ql_components/driver/ble/platform/7238/driver/uart
    ${CMAKE_SOURCE_DIR}/ql_components/driver/icu
    ${CMAKE_SOURCE_DIR}/ql_components/driver/spi
    ${CMAKE_SOURCE_DIR}/ql_components/driver/fft
    ${CMAKE_SOURCE_DIR}/ql_components/driver/entry
    ${CMAKE_SOURCE_DIR}/ql_components/driver/i2c
    ${CMAKE_SOURCE_DIR}/ql_components/driver/pwm
    ${CMAKE_SOURCE_DIR}/ql_components/driver/macphy_bypass
    ${CMAKE_SOURCE_DIR}/ql_components/driver/gpio
    ${CMAKE_SOURCE_DIR}/ql_components/driver/saradc
    ${CMAKE_SOURCE_DIR}/ql_components/driver/common
    ${CMAKE_SOURCE_DIR}/ql_components/driver/common/reg
    ${CMAKE_SOURCE_DIR}/ql_components/driver/i2s
    ${CMAKE_SOURCE_DIR}/ql_components/driver/include
    ${CMAKE_SOURCE_DIR}/ql_components/driver/uart
    ${CMAKE_SOURCE_DIR}/ql_components/driver/qspi
    ${CMAKE_SOURCE_DIR}/ql_components/driver/jpeg
    ${CMAKE_SOURCE_DIR}/ql_components/driver/phy
    ${CMAKE_SOURCE_DIR}/ql_components/driver/spidma
    ${CMAKE_SOURCE_DIR}/ql_components/driver/usb/src/drivers/compl
    ${CMAKE_SOURCE_DIR}/ql_components/driver/usb/src/drivers/hid
    ${CMAKE_SOURCE_DIR}/ql_components/driver/usb/src/drivers/hub
    ${CMAKE_SOURCE_DIR}/ql_components/driver/usb/src/drivers/msd
    ${CMAKE_SOURCE_DIR}/ql_components/driver/usb/src/drivers/comm
    ${CMAKE_SOURCE_DIR}/ql_components/driver/usb/src/drivers/trans
    ${CMAKE_SOURCE_DIR}/ql_components/driver/usb/src/test/compl
    ${CMAKE_SOURCE_DIR}/ql_components/driver/usb/src/test
    ${CMAKE_SOURCE_DIR}/ql_components/driver/usb/src/test/hub
    ${CMAKE_SOURCE_DIR}/ql_components/driver/usb/src/test/cbs
    ${CMAKE_SOURCE_DIR}/ql_components/driver/usb/src/hid
    ${CMAKE_SOURCE_DIR}/ql_components/driver/usb/src/examples
    ${CMAKE_SOURCE_DIR}/ql_components/driver/usb/src/uvc
    ${CMAKE_SOURCE_DIR}/ql_components/driver/usb/src/cd
    ${CMAKE_SOURCE_DIR}/ql_components/driver/usb/src/systems/none/afs
    ${CMAKE_SOURCE_DIR}/ql_components/driver/usb/src/systems/none
    ${CMAKE_SOURCE_DIR}/ql_components/driver/usb/src/msc
    ${CMAKE_SOURCE_DIR}/ql_components/driver/usb
    ${CMAKE_SOURCE_DIR}/ql_components/driver/usb/include
    ${CMAKE_SOURCE_DIR}/ql_components/driver/usb/include/class
    ${CMAKE_SOURCE_DIR}/ql_components/driver/intc
    ${CMAKE_SOURCE_DIR}/ql_components/driver/security
    ${CMAKE_SOURCE_DIR}/ql_components/driver/flash
    ${CMAKE_SOURCE_DIR}/ql_components/driver/rw_pub
    ${CMAKE_SOURCE_DIR}/ql_components/api
    ${CMAKE_SOURCE_DIR}/ql_components/release
    ${CMAKE_SOURCE_DIR}/ql_components/common
    ${CMAKE_SOURCE_DIR}/ql_components/app/config
    ${CMAKE_SOURCE_DIR}/ql_components/app/standalone-station
    ${CMAKE_SOURCE_DIR}/ql_components/app/standalone-ap
    ${CMAKE_SOURCE_DIR}/ql_kernel/config
    ${CMAKE_SOURCE_DIR}/ql_kernel/FreeRTOSv9.0.0/FreeRTOS/Source
    ${CMAKE_SOURCE_DIR}/ql_kernel/FreeRTOSv9.0.0/FreeRTOS/Source/include
    ${CMAKE_SOURCE_DIR}/ql_kernel/FreeRTOSv9.0.0/FreeRTOS/Source/portable/Keil/ARM968es
    ${CMAKE_SOURCE_DIR}/ql_components/third_party/paho-mqtt/client/src
    ${CMAKE_SOURCE_DIR}/ql_components/third_party/paho-mqtt/packet/src
    ${CMAKE_SOURCE_DIR}/ql_components/third_party/paho-mqtt/mqtt_ui/ssl_mqtt
    ${CMAKE_SOURCE_DIR}/ql_components/third_party/paho-mqtt/mqtt_ui/tcp_mqtt
    ${CMAKE_SOURCE_DIR}/ql_components/third_party/paho-mqtt/mqtt_ui
    ${CMAKE_SOURCE_DIR}/ql_components/third_party/mbedtls/mbedtls/include
    ${CMAKE_SOURCE_DIR}/ql_components/third_party/mbedtls/mbedtls/include/mbedtls
    ${CMAKE_SOURCE_DIR}/ql_components/third_party/mbedtls/mbedtls-port/inc
    ${CMAKE_SOURCE_DIR}/ql_components/third_party/mbedtls/mbedtls_ui
    ${CMAKE_SOURCE_DIR}/ql_components/third_party/lwip_intf/lwip-2.0.2/port
    ${CMAKE_SOURCE_DIR}/ql_components/third_party/lwip_intf/lwip-2.0.2/src/include
    ${CMAKE_SOURCE_DIR}/ql_components/third_party/lwip_intf/lwip-2.0.2/src/include/lwip
    ${CMAKE_SOURCE_DIR}/ql_components/third_party/lwip_intf/lwip-2.0.2/src/include/lwip/prot
    ${CMAKE_SOURCE_DIR}/ql_components/third_party/lwip_intf/lwip-2.0.2/src/include/posix
    ${CMAKE_SOURCE_DIR}/ql_components/third_party/lwip_intf/lwip-2.0.2/src/include/netif
    ${CMAKE_SOURCE_DIR}/ql_application
    ${CMAKE_SOURCE_DIR}/ql_application/third_party/mdns/private_include
    ${CMAKE_SOURCE_DIR}/ql_application/third_party/mdns/include
    ${CMAKE_SOURCE_DIR}/ql_application/third_party/lfs
    ${CMAKE_SOURCE_DIR}/ql_application/third_party/5500
    ${CMAKE_SOURCE_DIR}/ql_application/third_party/5500/w5500
    ${CMAKE_SOURCE_DIR}/ql_application/third_party/http-parser
    ${CMAKE_SOURCE_DIR}/ql_application/third_party/curl/curl-8.1.2/include
    ${CMAKE_SOURCE_DIR}/ql_application/third_party/curl/curl-8.1.2/include/curl
    ${CMAKE_SOURCE_DIR}/ql_application/third_party/curl/curl-8.1.2/lib/vauth
    ${CMAKE_SOURCE_DIR}/ql_application/third_party/curl/curl-8.1.2/lib/vquic
    ${CMAKE_SOURCE_DIR}/ql_application/third_party/curl/curl-8.1.2/lib/vssh
    ${CMAKE_SOURCE_DIR}/ql_application/third_party/curl/curl-8.1.2/lib/vtls
    ${CMAKE_SOURCE_DIR}/ql_application/third_party/curl/curl-8.1.2/lib
)

include_directories(${include_files})

include (${app_path}/configure.cmake)

include (${components_path}/configure.cmake)

link_directories(BEFORE ${CMAKE_SOURCE_DIR}/ql_kernel/prebuilds)
add_definitions(-DMBEDTLS_CONFIG_FILE=\"tls_config.h\")

list(APPEND source_files
            ${5500_srcs}
            ${curl_srcs}
			 ${http-parser_srcs}
            ${lfs_srcs}
            ${example_srcs}
            ${mbedtls_srcs}
            ${lwip_srcs}
            ${mqtt_srcs}
            ${CMAKE_SOURCE_DIR}/ql_application/ql_app_main.c
     )

add_executable(${target}
    ${source_files}
)

target_link_libraries(${target}
                 PUBLIC
                 -Wl,--start-group
                 rwnx
                 supplicant
                 rf_test
                 wpa
                 wolfssl
                 ql_adapt
                 cal
                 src_s
                 ble
                 func
                 ble_pub
                 sensor
                 usb
                 rf_use
                 misc
                 bk_aware
                 driver
                 airkiss
                 os
                 uart_debug
                 -Wl,--end-group
)

set_target_properties(${target} PROPERTIES OUTPUT_NAME "${target}.elf")

add_custom_command(
    TARGET ${target}
    POST_BUILD
    COMMAND ${arm_gcc_objcopy} -O binary ${CMAKE_CURRENT_BINARY_DIR}/${target}.elf ${CMAKE_CURRENT_BINARY_DIR}/${target}.bin
    COMMAND cd ${CMAKE_SOURCE_DIR}/ql_tools/beken_packager/ && python bk_packager.py ${target}
)

