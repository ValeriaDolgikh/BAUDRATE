#include <stdio.h>
#include <stdint.h>
#include <math.h>

float calc_baud (uint8_t U2X);
void UBRR_reg (uint16_t baud);
void error(uint16_t baud, uint8_t U2X);

float clk_freq;
unsigned int baudrate;

int main()
{
    printf("entrer clock frequency [MHz]:\n");
    scanf("%f", &clk_freq);

    printf("enter baudrate:\n");
    scanf("%d", &baudrate);

    uint8_t U2X;
    printf("do you use register U2X? 1/0\n");
    scanf("%d", &U2X);

    float baud = calc_baud(U2X);

    UBRR_reg ((uint16_t)baud);
    error((uint16_t)baud, U2X);

    return 0;
}

float calc_baud (uint8_t U2X)
{
    float baud;

    if(U2X == 0)
    {
        baud = ((clk_freq * 1000000) / (16 * baudrate)) - 1;
    }
    else
    {
        baud = ((clk_freq * 1000000) / (8 * baudrate)) - 1;
    }
    printf("baud: %.2f\n", baud);
    printf("round baud: %.2f\n", roundf(baud));
    return roundf(baud);
}

void UBRR_reg (uint16_t baud)
{
    uint8_t UBRRH = (uint8_t)(baud >> 8);
    uint8_t UBRRL = (uint8_t)baud;
    printf("UBRRH: 0x%x\nUBRRL: 0x%x\n", UBRRH, UBRRL);
}

void error(uint16_t baud, uint8_t U2X)
{
    unsigned int new_baudrate;

    if(U2X == 0)
    {
        new_baudrate = (clk_freq * 1000000) / (16 * (baud+1));
    }
    else
    {
        new_baudrate = (clk_freq * 1000000) / (8 * (baud+1));       
    }

    unsigned int error = 100 - (unsigned int)round(((float)new_baudrate / (float)baudrate) * 100);
    printf("error: %d percent \n", error);

    if (error > 4)
    {
        printf("error more then 4 percent\n");
    }
    else
    {
        printf("error less then 4 percent\n");
    }
}