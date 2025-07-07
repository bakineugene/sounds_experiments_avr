#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "sounds.h"
#include "build/sounds/hi.h"
#include "build/sounds/bump.h"
#include "build/sounds/dzin.h"

#define SAMPLE_RATE 8000  // Частота дискретизации
#define PWM_TOP 255       // Частота PWM = 16МГц / (1 * 256) = 62.5 кГц

volatile uint16_t currentSample = 0;

void setupTimer1_PWM() {
    DDRB |= (1 << PB1);       // PB1 (OC1A) как выход
    TCCR1A = (1 << COM1A1) | (1 << WGM11);
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS10);  // Fast PWM, режим 14
    ICR1 = PWM_TOP;          // Верхнее значение (частота PWM = 62.5 кГц)
}

void setupTimer0_Interrupt() {
    TCCR0A = (1 << WGM01);   // CTC режим
    TCCR0B = (1 << CS01);    // Предделитель /8
    OCR0A = (F_CPU / 8 / SAMPLE_RATE) - 1;
    TIMSK0 = (1 << OCIE0A);  // Разрешить прерывание
}

Sound queue[18];
int queue_head = 0;
int queue_end = 0;
ISR(TIMER0_COMPA_vect) {
    if (queue_head != queue_end) {
        Sound current_sound = queue[queue_head];
        if (currentSample < current_sound.length) {
            uint8_t sample = pgm_read_byte(&current_sound.start[currentSample++]);
            OCR1A = sample;
        } else {
            ++queue_head;
            currentSample = 0;
        }
    } else {
        TIMSK0 &= ~(1 << OCIE0A);
    }
}


int main() {
    setupTimer1_PWM();
    setupTimer0_Interrupt();

    queue[queue_end++] = SOUND_DZIN;
    queue[queue_end++] = SOUND_BUMP;
    queue[queue_end++] = SOUND_DZIN;
    queue[queue_end++] = SOUND_DZIN;
    queue[queue_end++] = SOUND_BUMP;
    queue[queue_end++] = SOUND_HI;
    queue[queue_end++] = SOUND_BUMP;
    queue[queue_end++] = SOUND_DZIN;
    queue[queue_end++] = SOUND_DZIN;
    queue[queue_end++] = SOUND_BUMP;
    queue[queue_end++] = SOUND_DZIN;
    queue[queue_end++] = SOUND_DZIN;
    queue[queue_end++] = SOUND_HI;
    queue[queue_end++] = SOUND_BUMP;
    queue[queue_end++] = SOUND_BUMP;
    queue[queue_end++] = SOUND_DZIN;
    queue[queue_end++] = SOUND_DZIN;
    queue[queue_end++] = SOUND_BUMP;
    queue[queue_end++] = SOUND_DZIN;
    queue[queue_end++] = SOUND_DZIN;
    queue[queue_end++] = SOUND_BUMP;
    queue[queue_end++] = SOUND_BUMP;
    queue[queue_end++] = SOUND_DZIN;
    queue[queue_end++] = SOUND_HI;

    sei();
    while (1) {}
}
