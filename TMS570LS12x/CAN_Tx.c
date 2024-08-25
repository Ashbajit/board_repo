

/* USER CODE BEGIN (0) */
#include "can.h"
/* USER CODE END */

/* Include Files */
#include "system.h"
#include "sys_common.h"

/* USER CODE BEGIN (1) */
#define D_SIZE 9

uint8_t tx_data[D_SIZE] = {'T','X',1,2,3,4,5,6,'\0'};
uint32_t checkPackets(uint8_t *src_packet,uint8_t *dst_packet,uint32_t psize);
/* USER CODE END */


/* USER CODE BEGIN (2) */
void delay(volatile uint32_t count)
{
    while(count--);
}

/* USER CODE END */

void main(void)
{
/* USER CODE BEGIN (3) */
    /* initialize can 1 */
    canInit();

    /* transmit on can1 */
    canTransmit(canREG1, canMESSAGE_BOX1, tx_data);
    /* ... run forever */
    while(1){
        canTransmit(canREG1, canMESSAGE_BOX1, tx_data);
        delay(10000000); // 10,000,000 for 1 second
    }
/* USER CODE END */
}


/* USER CODE BEGIN (4) */
uint32_t checkPackets(uint8_t *src_packet,uint8_t *dst_packet,uint32_t psize)
{
uint32_t err=0;
uint32_t cnt=psize;

    while(cnt--)
    {
     if((*src_packet++) != (*dst_packet++))
     /* data error */
     {
        err++;
     }
    }

    return (err);
}
/* can interrupt notification (Not used but must be provided) */
void canMessageNotification(canBASE_t *node, uint32_t messageBox)
{
    return;
}

/* can error notification (Not used but must be provided) */
void canErrorNotification(canBASE_t *node, uint32_t notification)
{
    return;
}
/* ESM Group notification (Not used but must be provided) */
void esmGroup1Notification(unsigned channel)
{
    return;
}
/* ESM Group2 notification (Not used but must be provided) */
void esmGroup2Notification(unsigned channel)
{
    return;
}
/* USER CODE END */
