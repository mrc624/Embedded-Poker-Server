// Copyright (c) 2023 Cesanta Software Limited
// All rights reserved

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "hardware/spi.h"
#include "pico/rand.h"
#include "pico/stdlib.h"

#define LED1 ((uint16_t) PICO_DEFAULT_LED_PIN)
#define LED2 LED1
#define LED3 LED1
#define UART_DEBUG NULL

void hal_init(void);
size_t hal_ram_free(void);
size_t hal_ram_used(void);
void hal_genmac(unsigned char *mac);

#define PIN(bank, num) (num)
#if 0
enum { GPIO_MODE_INPUT, GPIO_MODE_OUTPUT };
enum { GPIO_OTYPE_PUSH_PULL, GPIO_OTYPE_OPEN_DRAIN };
enum { GPIO_SPEED_LOW, GPIO_SPEED_HIGH };
enum { GPIO_PULL_NONE, GPIO_PULL_DOWN, GPIO_PULL_UP };

static inline void gpio_init(uint16_t pin, uint8_t mode, uint8_t type,
                             uint8_t speed, uint8_t pull, uint8_t af) {
// would clash with gpio_init()
}
#endif

static inline void gpio_input(uint16_t pin) {
  gpio_set_dir(pin, GPIO_IN);
}
static inline void gpio_output(uint16_t pin) {
  gpio_set_dir(pin, GPIO_OUT);
}

static inline bool gpio_read(uint16_t pin) {
  return gpio_get(pin);
}

static inline void gpio_write(uint16_t pin, bool value) {
  gpio_put(pin, value);
}

static inline void gpio_toggle(uint16_t pin) {
  gpio_xor_mask((uint32_t)(1UL << pin));
}

static inline void leds_init(void) {
  gpio_output(LED1); // Initialise LED1
  gpio_write(LED1, 1);
}

// TODO() use common hal.c 
#if 0
#undef MG_HAL_DISABLE_SYSTEM_INIT
#define MG_HAL_DISABLE_SYSTEM_INIT 1
#undef MG_HAL_DISABLE_NEWLIB
#define MG_HAL_DISABLE_NEWLIB 1
#undef MG_HAL_DISABLE_CLOCK
#define MG_HAL_DISABLE_CLOCK 1
#undef MG_HAL_DISABLE_MILLIS
#define MG_HAL_DISABLE_MILLIS 1
#undef MG_HAL_SYSTICK
#define MG_HAL_SYSTICK MG_HAL_SYSTICK_NONE
#define MG_HAL_DISABLE_UART 1

#if defined(__ZEPHYR__)
#undef MG_HAL_DISABLE_RANDOM
#define MG_HAL_DISABLE_RANDOM 1
#undef MG_HAL_DISABLE_UART
#define MG_HAL_DISABLE_UART 1
#undef MG_HAL_DISABLE_ETHERNET
#define MG_HAL_DISABLE_ETHERNET 1
#else
#undef MG_HAL_ENABLE_GENMAC
#define MG_HAL_ENABLE_GENMAC 1
#endif
#endif // 0

// clashes with uart_init
#if 0
static inline void uart_init(void *uart, unsigned long baud) {
  stdio_init_all();
  (void) uart, (void) baud;
}
#endif

static inline void rng_init(void) {}
static inline uint32_t rng_read(void) {
  get_rand_32();
}


//enum { SPI_CS = 17, SPI_CLK = 18, SPI_TX = 19, SPI_RX = 16 };  // Pins
enum { SPI_CS = 5, SPI_CLK = 2, SPI_TX = 3, SPI_RX = 4 };  // Pins

static inline void ethernet_init(void) {
  // Init SPI pins
  spi_init(spi0, 500 * 1000);
  gpio_set_function(SPI_RX, GPIO_FUNC_SPI);   // MISO
  gpio_set_function(SPI_TX, GPIO_FUNC_SPI);   // MOSI
  gpio_set_function(SPI_CLK, GPIO_FUNC_SPI);  // CLK
  gpio_init(SPI_CS);                          // CS
  gpio_set_dir(SPI_CS, GPIO_OUT);             // Set CS to output
  gpio_put(SPI_CS, 1);                        // And drive CS high (inactive)
}

// Construct MAC address from the unique board ID
#include "pico/unique_id.h"
static inline void ethernet_genmac(unsigned char *mac) {
  pico_unique_board_id_t board_id;
  pico_get_unique_board_id(&board_id);
  mac[0] = 2;
  memcpy(&mac[1], &board_id.id[3], 5);
}

