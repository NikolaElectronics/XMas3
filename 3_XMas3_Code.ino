#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

const byte ledPin0 = 0;
const byte ledPin1 = 1;
const byte ledPin2 = 3;
int fadeValue;
byte saveADCSRA;
volatile byte counterWD = 0;

void setup ()
{
  resetWatchDog ();  // Initialize and configure the watchdog timer
  
  // Initialize and blink an LED for visual indication
  pinMode ( ledPin0, OUTPUT );
  digitalWrite(ledPin0, HIGH);
  delay(200);
  digitalWrite(ledPin0, LOW);
  delay(200);
  digitalWrite(ledPin0, HIGH);
  delay(200);
  digitalWrite(ledPin0, LOW);
  delay(200);
  
  led0Low();  // Start fading LED 0
}

void loop ()
{
  if ( counterWD == 2)
  {
    // Toggle LEDs and fade them in and out
    for(int i = 0; i < 23; i++)
    {
    led0High();
    led1High();
    led2High();
    led0Low();
    led1Low();
    led2Low();
    }
    analogWrite(ledPin0, LOW);
    delay(2000);
    analogWrite(ledPin1, LOW);
    delay(2000);    
    analogWrite(ledPin2, LOW);
    delay(2000);
    counterWD = 0;  // Reset the watchdog timer counter
  }
  
  sleepNow ();  // Enter low-power sleep mode
}

void sleepNow ()
{
  set_sleep_mode ( SLEEP_MODE_PWR_DOWN );  // Configure power-down sleep mode
  saveADCSRA = ADCSRA;  // Save ADC settings
  ADCSRA = 0;  // Disable ADC
  power_all_disable ();  // Disable power to peripherals
  noInterrupts ();  // Disable interrupts
  resetWatchDog ();  // Initialize watchdog timer
  sleep_enable ();  // Enable sleep mode
  interrupts ();  // Enable interrupts
  sleep_cpu ();  // Enter sleep mode
  sleep_disable ();  // Disable sleep mode
  power_all_enable ();  // Enable power to peripherals
}

void resetWatchDog ()
{
  MCUSR = 0;
  WDTCR = bit ( WDCE ) | bit ( WDE ) | bit ( WDIF );
  WDTCR = bit ( WDIE ) | bit ( WDP2 ) | bit ( WDP1 );

  wdt_reset ();
}

ISR ( WDT_vect )
{
  wdt_disable ();
  counterWD++;  // Increment the watchdog timer counter
}

void led0High()
{
  for (fadeValue = 0 ; fadeValue <= 255; fadeValue += 15)
  {
    analogWrite(ledPin0, fadeValue);  // Increase LED brightness
    delay(5);
  }
}

void led0Low()
{
  for (fadeValue = 255 ; fadeValue >= 0; fadeValue -= 15)
  {
    analogWrite(ledPin0, fadeValue);  // Decrease LED brightness
    delay(5);
  }
}


void led1High()
{
  for (fadeValue = 0 ; fadeValue <= 255; fadeValue += 15)
  {
    analogWrite(ledPin1, fadeValue);  // Increase LED brightness
    delay(5);
  }
}

void led1Low()
{
  for (fadeValue = 255 ; fadeValue >= 0; fadeValue -= 15)
  {
    analogWrite(ledPin1, fadeValue);  // Decrease LED brightness
    delay(5);
  }
}


void led2High()
{
  for (fadeValue = 0 ; fadeValue <= 255; fadeValue += 15)
  {
    analogWrite(ledPin2, fadeValue);  // Increase LED brightness
    delay(5);
  }
}

void led2Low()
{
  for (fadeValue = 255 ; fadeValue >= 0; fadeValue -= 15)
  {
    analogWrite(ledPin2, fadeValue);  // Decrease LED brightness
    delay(5);
  }
}
// Similar functions for LED 1 and LED 2 are defined below.
