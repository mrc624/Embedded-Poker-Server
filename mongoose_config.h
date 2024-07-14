#pragma once

// See https://mongoose.ws/documentation/#build-options
#define MG_ARCH MG_ARCH_RP2040

#define MG_ENABLE_TCPIP 1
#define MG_ENABLE_DRIVER_W5500 1
#define MG_ENABLE_CUSTOM_RANDOM 1
#define MG_ENABLE_PACKED_FS 1

// For static IP configuration, define MG_TCPIP_{IP,MASK,GW}
// By default, those are set to zero, meaning that DHCP is used
//
// #define MG_TCPIP_IP MG_IPV4(192, 168, 1, 10)
// #define MG_TCPIP_GW MG_IPV4(192, 168, 1, 1)
// #define MG_TCPIP_MASK MG_IPV4(255, 255, 255, 0)

// Set custom MAC address. By default, it is randomly generated
// Using a build-time constant:
// #define MG_SET_MAC_ADDRESS(mac) do { uint8_t buf_[6] = {2,3,4,5,6,7};
// memmove(mac, buf_, sizeof(buf_)); } while (0)
//
// Using custom function:
extern void hal_genmac(unsigned char *mac);
#define MG_SET_MAC_ADDRESS(mac) hal_genmac(mac)

// Hardware specific SPI support
#include <stdint.h>
extern void hal_spi_begin(void *);
extern void hal_spi_end(void *);
extern uint8_t hal_spi_txn(void *, uint8_t);
#define MG_TCPIP_DRIVER_INIT(mgr)                                              \
  do {                                                                         \
    static struct mg_tcpip_spi spi_ = {NULL, hal_spi_begin, hal_spi_end,       \
                                       hal_spi_txn};                           \
    static struct mg_tcpip_if mif_;                                            \
    mif_.ip = MG_TCPIP_IP;                                                     \
    mif_.mask = MG_TCPIP_MASK;                                                 \
    mif_.gw = MG_TCPIP_GW;                                                     \
    mif_.driver = &mg_tcpip_driver_w5500;                                      \
    mif_.driver_data = &spi_;                                                  \
    MG_SET_MAC_ADDRESS(mif_.mac);                                              \
    mg_tcpip_init(mgr, &mif_);                                                 \
    MG_INFO(("Driver: W5500, MAC: %M", mg_print_mac, mif_.mac));               \
  } while (0)
