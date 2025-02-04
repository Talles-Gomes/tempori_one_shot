#include <stdio.h>
#include "pico/stdlib.h" // Inclui a biblioteca padrão para funcionalidades básicas como GPIO.
#include "hardware/timer.h" // Inclui a biblioteca para gerenciamento de temporizadores de hardware.

#define ledG 11
#define ledB 12
#define ledR 13
#define botA 5
int a=0;
int64_t turn_off_callback(alarm_id_t id, void *user_data) {

  switch(a){
    case 1:            
            gpio_put(ledG,false);
            gpio_put(ledB,true);
            gpio_put(ledR,true);
            a++;
            add_alarm_in_ms(3000, turn_off_callback, NULL, false);
    break;
    case 2:
            gpio_put(ledG,false);
            gpio_put(ledB,false);
            gpio_put(ledR,true);
            a++;
            add_alarm_in_ms(3000, turn_off_callback, NULL, false);
    break;
    case 3:
            gpio_put(ledG,false);
            gpio_put(ledB,false);
            gpio_put(ledR,false);
            a=0;
    break;
  }
return 0;
 }

int main() {
// Inicializa a comunicação serial
stdio_init_all();
// Inicialização dos pinos dos leds
gpio_init(ledR);
gpio_set_dir(ledR,true);

gpio_init(ledB);
gpio_set_dir(ledB,true);

gpio_init(ledG);
gpio_set_dir(ledG,true);

gpio_init(botA);
gpio_set_dir(botA,GPIO_IN);
gpio_pull_up(botA);

// Loop infinito que mantém o programa em execução.
while (true) {
  //delay pra economizar processamento e evitar slowdown na simulação
  sleep_ms(10);
  
    if (gpio_get(botA) == 0) {  // Botão pressionado (nível baixo)
            sleep_ms(50);  // Delay para debounce
      if (gpio_get(botA) == 0 && gpio_get(ledR)==0) {
          
        gpio_put(ledG,true);
        gpio_put(ledB,true);
        gpio_put(ledR,true);
        a++;
        add_alarm_in_ms(3000, turn_off_callback, NULL, false); 
      }
    }
  }return 0;
}