#include  <msp430x14x.h>

#define   Num_of_Results   8

static unsigned int A0results[Num_of_Results];  // These need to be global in
static unsigned int A1results[Num_of_Results];  // this example. Otherwise, the
static unsigned int A2results[Num_of_Results];  // compiler removes them because
static unsigned int A3results[Num_of_Results];  // they are not used

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  P6SEL = 0x0F;                             // Enable A/D channel inputs
  ADC12CTL0 = ADC12ON+MSC+SHT0_8;           // Turn on ADC12, extend sampling time
                                            // to avoid overflow of results
  ADC12CTL1 = SHP+CONSEQ_3;                 // Use sampling timer, repeated sequence
  ADC12MCTL0 = INCH_0;                      // ref+=AVcc, channel = A0
  ADC12MCTL1 = INCH_1;                      // ref+=AVcc, channel = A1
  ADC12MCTL2 = INCH_2;                      // ref+=AVcc, channel = A2
  ADC12MCTL3 = INCH_3+EOS;                  // ref+=AVcc, channel = A3, end seq.
  ADC12IE = 0x08;                           // Enable ADC12IFG.3
  ADC12CTL0 |= ENC;                         // Enable conversions
  ADC12CTL0 |= ADC12SC;                     // Start conversion
  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0, Enable interrupts
}

#pragma vector=ADC_VECTOR
__interrupt void ADC12ISR (void)
{
  static unsigned int index = 0;

  ADC12CTL0 &= ~ADC12SC;
  
  A0results[index] = ADC12MEM0;             // Move A0 results, IFG is cleared
  A1results[index] = ADC12MEM1;             // Move A1 results, IFG is cleared
  A2results[index] = ADC12MEM2;             // Move A2 results, IFG is cleared
  A3results[index] = ADC12MEM3;             // Move A3 results, IFG is cleared
  max7219_display(A1results[index]);
  index = (index+1)%Num_of_Results;         // Increment results index, modulo; Set Breakpoint here
  ADC12CTL0 |= ADC12SC;
}
