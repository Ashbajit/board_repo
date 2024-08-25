/* USER CODE BEGIN (0) */
#include "sci.h"

#include "sys_common.h"
#include "system.h"
/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
static unsigned char command;
/* USER CODE END */


/* USER CODE BEGIN (2) */
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    _enable_IRQ();

    sciInit();

    sciSend(scilinREG, 21, (unsigned char *)"Please press a key!\r\n");

    sciReceive(scilinREG, 1, (unsigned char *)&command);
    while(1);

/* Initialize the system and SCI module */
   systemInit();
   sciInit();

   /* Text to be sent */
   uint8 text[] = "Hello, SCI!\r\n";

   /* Loop to continuously send the text */
   while(1)
   {
       sciDisplayText(scilinREG, text, sizeof(text) - 1);
       wait(0xFFFFFF); // Delay between messages
   }
/* USER CODE END */

}


/* USER CODE BEGIN (4) */

void sciNotification(sciBASE_t *sci,  unsigned flags)
{

/* echo received character */
sciSend(sci, 1,(unsigned char *)&command);

/* Await further character */
sciReceive(sci, 1,(unsigned char *)&command);
}
/* ESM interrupt notification (Not used but must be provided) */
void esmGroup1Notification(int bit)
{
    return;
}

void esmGroup2Notification(int bit)
{
    return;
}

/* Function to send text via SCI */
void sciDisplayText(sciBASE_t *sci, uint8 *text, uint32 length)
{
    while(length--)
    {
        while ((sci->FLR & SCI_TX_INT) == 0); // Wait for TX ready
        sciSendByte(sci, *text++);            // Send byte
    }
}

/* Simple delay function */
void wait(uint32 time)
{
    while(time--);
}

/* USER CODE END */
