/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */
#include "sci.h"
#include "sys_common.h"
#include "system.h"

/* USER CODE BEGIN (1) */

#define  TSIZE1 9
uint8  TEXT1[TSIZE1]= {'T','H','I','S',' ','I','S',' ',' '};
#define  TSIZE2 19
uint8  TEXT2[TSIZE2]= {'S','A','M','P','L','E',' ','P','R','O','J','E','C','T',' ','B','Y',' ',' '};
#define  TSIZE3 9
uint8  TEXT3[TSIZE3]= {'A','B','H','I','J','I','T','\n','\r'};

void sciDisplayText(sciBASE_t *sci, uint8 *text, uint32 length);
void wait(uint32 time);


#define UART scilinREG

/* USER CODE BEGIN (2) */
/* USER CODE END */


void main(void)
{
/* USER CODE BEGIN (3) */

    sciInit();      /* initialize sci/sci-lin    */
                    /* even parity , 2 stop bits */

    while(1)        /* continous desplay        */
    {
      sciDisplayText(UART,&TEXT1[0],TSIZE1);   /* send text code 1 */
      sciDisplayText(UART,&TEXT2[0],TSIZE2);   /* send text code 2 */
      sciDisplayText(UART,&TEXT3[0],TSIZE3);   /* send text code 3 */
      wait(200);
    };

/* USER CODE END */
}

/* USER CODE BEGIN (4) */
void sciDisplayText(sciBASE_t *sci, uint8 *text,uint32 length)
{
    while(length--)
    {
        while ((UART->FLR & 0x4) == 4); /* wait until busy */
        sciSendByte(UART,*text++);      /* send out text   */
    };
}


void wait(uint32 time)
{
    time--;
}
/* USER CODE END */

