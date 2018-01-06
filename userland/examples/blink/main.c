#include <led.h>
#include <timer.h>
#include <console.h>

char hello[] = "Hello World!\r\n";

static void nop(
  int a __attribute__((unused)),
  int b __attribute__((unused)),
  int c __attribute__((unused)),
  void* d __attribute__((unused))) {}

int main(void) {
  // Ask the kernel how many LEDs are on this board.
  int num_leds = led_count();

  // Blink the LEDs in a binary count pattern and scale
  // to the number of LEDs on the board.
  for (int count = 0; ; count++) {
    for (int i = 0; i < num_leds; i++) {
      if (count & (1 << i)) {
        led_on(i);
      } else {
        led_off(i);
      }
    }
    putnstr_async(hello, sizeof(hello), nop, NULL);
    printf("hello from printf\n");
    // This delay uses an underlying timer in the kernel.
    delay_ms(250);
  }
}
