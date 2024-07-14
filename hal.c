// Copyright (c) 2024 Cesanta Software Limited
// All rights reserved

#include "hal.h"

void mg_random(void *buf, size_t len) { // Use SDK RNG
  for (size_t n = 0; n < len; n += sizeof(uint32_t)) {
    uint32_t r = rng_read();
    memcpy((char *)buf + n, &r, n + sizeof(r) > len ? len - n : sizeof(r));
  }
}

void hal_init(void) {
  rng_init();       // Initialise random number generator
  stdio_init_all(); // TODO() use common hal.c
  leds_init();
  ethernet_init(); // Initialise Ethernet pins
}

void hal_genmac(unsigned char *mac) { ethernet_genmac(mac); }

// Hardware specific SPI support
void hal_spi_begin(void *spi) {
  gpio_put(SPI_CS, 0);
}
void hal_spi_end(void *spi) {
  gpio_put(SPI_CS, 1);
}
uint8_t hal_spi_txn(void *spi, uint8_t byte) {
  uint8_t result = 0;
  spi_write_read_blocking(spi0, &byte, &result, 1);
  return result;
}


