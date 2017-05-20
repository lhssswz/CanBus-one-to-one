#include  "stdio.h"
#include  "string.h"
#include  "intrins.h"
#include  "reg51.h"

//����SJA1000�Ļ�ַ
#define SJA_BaseAdr  0XFE00       //P2.0
// ���ƼĴ���
#define         REG_CONTROL       SJA_BaseAdr+0x00       //�ڲ����ƼĴ���
#define         REG_COMMAND       SJA_BaseAdr+0x01       //����Ĵ���
#define         REG_STATUS        SJA_BaseAdr+0x02       //״̬�Ĵ���
#define         REG_INTERRUPT     SJA_BaseAdr+0x03       //�жϼĴ���
#define         REG_INTENABLE     SJA_BaseAdr+0x04       //�ж�ʹ�ܼĴ���
#define         REG_BTR0          SJA_BaseAdr+0x06       //���߶�ʱ�Ĵ���0
#define         REG_BTR1          SJA_BaseAdr+0x07       //���߶�ʱ�Ĵ���1
#define         REG_OCR           SJA_BaseAdr+0x08       //������ƼĴ���
#define         REG_TEST          SJA_BaseAdr+0x09       //���ԼĴ���

#define         REG_RESVER1       SJA_BaseAdr+0x0A       //����1
#define         REG_ARBITRATE     SJA_BaseAdr+0x0B       //�ٲö�ʧ��׽
#define         REG_ERRCATCH      SJA_BaseAdr+0x0C       //������벶׽
#define         REG_ERRLIMIT      SJA_BaseAdr+0x0D       //���󱨾��޶�

#define         REG_RXERR         SJA_BaseAdr+0x0E         //���մ��������
#define         REG_TXERR         SJA_BaseAdr+0x0F         //���ʹ��������

#define         REG_ACR1          SJA_BaseAdr+0x10       //���մ���Ĵ���
#define         REG_ACR2          SJA_BaseAdr+0x11       //���մ���Ĵ���
#define         REG_ACR3          SJA_BaseAdr+0x12       //���մ���Ĵ���
#define         REG_ACR4          SJA_BaseAdr+0x13       //���մ���Ĵ���
#define         REG_AMR1          SJA_BaseAdr+0x14       //�������μĴ���
#define         REG_AMR2          SJA_BaseAdr+0x15       //�������μĴ���
#define         REG_AMR3          SJA_BaseAdr+0x16       //�������μĴ���
#define         REG_AMR4          SJA_BaseAdr+0x17       //�������μĴ���

// ���ͻ������Ĵ���
#define         REG_TXBuffer1     SJA_BaseAdr+0x10         //���ͻ�����1
#define         REG_TXBuffer2     SJA_BaseAdr+0x11         //���ͻ�����2
#define         REG_TXBuffer3     SJA_BaseAdr+0x12         //���ͻ�����3
#define         REG_TXBuffer4     SJA_BaseAdr+0x13         //���ͻ�����4
#define         REG_TXBuffer5     SJA_BaseAdr+0x14         //���ͻ�����5
#define         REG_TXBuffer6     SJA_BaseAdr+0x15         //���ͻ�����6
#define         REG_TXBuffer7     SJA_BaseAdr+0x16         //���ͻ�����7
#define         REG_TXBuffer8     SJA_BaseAdr+0x17         //���ͻ�����8
#define         REG_TXBuffer9     SJA_BaseAdr+0x18         //���ͻ�����9
#define         REG_TXBuffer10    SJA_BaseAdr+0x19         //���ͻ�����10
#define         REG_TXBuffer11    SJA_BaseAdr+0x1A         //���ͻ�����11
#define         REG_TXBuffer12    SJA_BaseAdr+0x1B         //���ͻ�����12
#define         REG_TXBuffer13    SJA_BaseAdr+0x1C         //���ͻ�����13

// ���ջ������Ĵ���
#define         REG_RXBuffer1       SJA_BaseAdr+0x10       //���ջ�����1
#define         REG_RXBuffer2       SJA_BaseAdr+0x11       //���ջ�����2
#define         REG_RXBuffer3      SJA_BaseAdr+0x12        //���ջ�����3
#define         REG_RXBuffer4       SJA_BaseAdr+0x13       //���ջ�����4
#define         REG_RXBuffer5      SJA_BaseAdr+0x14        //���ջ�����5
#define         REG_RXBuffer6     SJA_BaseAdr+0x15         //���ջ�����6
#define         REG_RXBuffer7     SJA_BaseAdr+0x16         //���ջ�����7
#define         REG_RXBuffer8     SJA_BaseAdr+0x17         //���ջ�����8
#define         REG_RXBuffer9     SJA_BaseAdr+0x18         //���ջ�����9
#define         REG_RXBuffer10     SJA_BaseAdr+0x19        //���ջ�����10
#define         REG_RXBuffer11     SJA_BaseAdr+0x1A        //���ջ�����11
#define         REG_RXBuffer12     SJA_BaseAdr+0x1B        //���ջ�����12
#define         REG_RXBuffer13     SJA_BaseAdr+0x1C        //���ջ�����13

#define         REG_RXCOUNT       SJA_BaseAdr+0x1D         //RX���ļ�����
#define         REG_RBSA          SJA_BaseAdr+0x1E         //���ջ�������ʼ��ַ
#define         REG_CDR           SJA_BaseAdr+0x1F         //ʱ�ӷ�Ƶ�Ĵ���
//����˵��:   CAN������SJA1000ͨѶ������.SJA1000�ľ���Ϊ����Ϊ24MHZ*/
#define         BTR0_Rate_10k      0xEF          //20KBPS��Ԥ��ֵ
#define         BTR1_Rate_10k      0xFF          //20KBPS��Ԥ��ֵ

/*
����˵��:   CAN������SJA1000ͨѶ������.SJA1000�ľ���Ϊ����Ϊ16MHZ*/

#define         BTR0_Rate_20k      0x53          //20KBPS��Ԥ��ֵ
#define         BTR1_Rate_20k      0x2F          //20KBPS��Ԥ��ֵ
#define         BTR0_Rate_40k      0x87          //40KBPS��Ԥ��ֵ
#define         BTR1_Rate_40k      0xFF          //40KBPS��Ԥ��ֵ
#define         BTR0_Rate_50k      0x47          //50KBPS��Ԥ��ֵ
#define         BTR1_Rate_50k      0x2F          //50KBPS��Ԥ��ֵ
#define         BTR0_Rate_80k      0x83          //80KBPS��Ԥ��ֵ
#define         BTR1_Rate_80k      0xFF          //80KBPS��Ԥ��ֵ
#define         BTR0_Rate_100k     0x43          //100KBPS��Ԥ��ֵ
#define         BTR1_Rate_100k     0x2f          //100KBPS��Ԥ��ֵ
#define         BTR0_Rate_125k     0x03          //125KBPS��Ԥ��ֵ
#define         BTR1_Rate_125k     0x1c          //125KBPS��Ԥ��ֵ
#define         BTR0_Rate_200k     0x81          //200KBPS��Ԥ��ֵ
#define         BTR1_Rate_200k     0xFA          //200KBPS��Ԥ��ֵ
#define         BTR0_Rate_250k     0x01          //250KBPS��Ԥ��ֵ
#define         BTR1_Rate_250k     0x1c          //250KBPS��Ԥ��ֵ
#define         BTR0_Rate_400k     0x80          //400KBPS��Ԥ��ֵ
#define         BTR1_Rate_400k     0xfa          //400KBPS��Ԥ��ֵ
#define         BTR0_Rate_500k     0x00          //500KBPS��Ԥ��ֵ
#define         BTR1_Rate_500k     0x1c          //500KBPS��Ԥ��ֵ
#define         BTR0_Rate_666k     0x80          //666KBPS��Ԥ��ֵ
#define         BTR1_Rate_666k     0xb6          //666KBPS��Ԥ��ֵ
#define         BTR0_Rate_800k     0x00          //800KBPS��Ԥ��ֵ
#define         BTR1_Rate_800k     0x16          //800KBPS��Ԥ��ֵ
#define         BTR0_Rate_1000k    0x00          //1000KBPS��Ԥ��ֵ
#define         BTR1_Rate_1000k    0x14          //1000KBPS��Ԥ��ֵ
//BPS
#define         ByteRate_10k       10 //24MHZ**********************
#define         ByteRate_40k       40
#define         ByteRate_50k       50
#define         ByteRate_80k       80
#define         ByteRate_100k      100
#define         ByteRate_125k      125
#define         ByteRate_200k      200
#define         ByteRate_250k      250
#define         ByteRate_400k      400
#define         ByteRate_500k      500
#define         ByteRate_800k      800
#define         ByteRate_1000k     1000

//������
#define    TR_CMD     0X01
#define    AT_CMD     0X02
#define    RRB_CMD    0X04
#define    COS_CMD    0X08
#define    SRR_CMD    0X10
#define    GTS_CMD    0X10
//������

#define CAN_INTERFACE_OK      0
#define CAN_BUS_OK            0
#define CAN_INTERFACE_ERR     0XFF
#define CAN_ENTERSET_ERR      0XFE
#define CAN_QUITSET_ERR       0XFD
#define CAN_INITOBJECT_ERR    0XFC
#define CAN_INITBTR_ERR       0XFB
#define CAN_INITOUTCTL_ERR    0XFA
#define CAN_INTCLKDIV_ERR     0XF9
#define CAN_BUS_ERR           0XF8

// ����ͨѶЭ��ķ��������ʶ��
#define SEND_COMMAND_QUERY_STATUS   (0x81)
#define SEND_COMMAND_SET_PARAM      (0x82)
#define SEND_COMMAND_QUERY_PARAM    (0x83)
#define SEND_COMMAND_SET_ONOFF      (0x84)
#define SEND_COMMAND_SET_RESET      (0x85)

// ����ͨѶЭ���Ӧ�������ʶ��
#define ANS_COMMAND_MODULE_STATUS (0x01)
#define ANS_COMMAND_SET_PARAM     (0x02)
#define ANS_COMMAND_MODULE_PARAM  (0x03)
#define ANS_COMMAND_SET_ONOFF     (0x04)
#define ANS_COMMAND_SET_RESET     (0x05)

// ���������ַ��
#define MASTER_ADDRESS            (0x01)
#define SLAVE_A_ADDRESS           (0x02)
#define SLAVE_B_ADDRESS           (0x03)
#define MACHINE_ADDRESS           (MASTER_ADDRESS)

//ϵͳָ�룬ָ��SJA1000
unsigned char xdata	*SJA_BCANAdr;
unsigned char data		RevceData[10];
unsigned char code table[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
//sbit key=P2^5; //Button����
sbit CS=P3^5;

#define SEND_SELECTE (P2)

unsigned char sendTo = SLAVE_A_ADDRESS;

void delay_ms(unsigned char t)
{
     unsigned char i,j;
     for (i=0;i<t;i++)
     	for(j=0;j<33;j++) 
     	;
    
}
void delay10ms(void) //��ʱ����

{

      unsigned char i,j;

      for(i=20;i>0;i--)

      for(j=248;j>0;j--);

}

/****************************************************
**����ԭ�ͣ�  void display(unsigned char num) 
**��    �ܣ�  �������ʾ
**��ڲ���:   Ҫ��ʾ�ַ� 
**���ڲ���:   ��
**˵    ��:   ��SJA1000�յ���ȷ�ı���ʱ,Ȼ����ʾ����           
*****************************************************/
void display(unsigned char num)  // ��ʾ�Ӻ���
{
        P1=table[num]; //����num����ʾ������P1��
}
//***************************************************

//��ʼ��cpu

//**************************************************
void Init_Cpu(void)                                  //��Ƭ����ʼ��,�����ⲿ�ж�0
{
     PX0=1;
     EX0=1;
     IT0=0;
    // EA=1;
}

/*------------------------------------------------
                    ���ڳ�ʼ��
------------------------------------------------*/
void InitUART  (void)
{

    SCON  = 0x50;		        // SCON: ģʽ 1, 8-bit UART, ʹ�ܽ���  
    TMOD |= 0x20;               // TMOD: timer 1, mode 2, 8-bit ��װ
    TH1   = 0xFD;               // TH1:  ��װֵ 9600 ������ ���� 11.0592MHz  
    TR1   = 1;                  // TR1:  timer 1 ��                         
    EA    = 1;                  //�����ж�
 }                            

/*------------------------------------------------
                    ����һ���ֽ�
------------------------------------------------*/
void SendByte(unsigned char dat)
{
 SBUF = dat;
 while(!TI);
      TI = 0;
}
/*------------------------------------------------
                    ����һ���ַ���
------------------------------------------------*/
void SendStr(unsigned char *s)
{
 while(*s!='\0')// \0 ��ʾ�ַ���������־��
                //ͨ������Ƿ��ַ���ĩβ
  {
  SendByte(*s);
  s++;
  }
}

//***********************************************************************
/************************************************************************
*����ԭ��: bit BCAN_SET_OUTCLK( unsigned char Clock_Out)               *
*����˵��:                                                             *
*          Clock_Out:���ʱ�ӷ�Ƶ�Ĵ���(CDR)�Ĳ�������                 *
*����ֵ:                                                               *
*           0 ;���óɹ�                                                *
*           1 ;����ʧ��                                                *
*˵��:����SJA1000��ʱ�ӷ�Ƶ �����ӳ���ֻ�����ڸ�λģʽ                      
************************************************************************/
bit BCAN_SET_OUTCLK(unsigned char Clock_Out)
{
  SJA_BCANAdr=REG_CDR;           

  *SJA_BCANAdr=Clock_Out;        
  if(*SJA_BCANAdr != Clock_Out)
     return 1; 
   else 
     return 0;
} 

/************************************************************************
*����ԭ��: bit BCAN_SET_OBJECT(unsigned char  BCAN_ACR0,BCAN_ACR1,BCAN_ACR2,BCAN_ACR3     
                                              BCAN_AMR0, BCAN_AMR1, BCAN_AMR2, BCAN_AMR3     
*����˵��:                                                              *
*    BCAN_ACR(0-3):������մ���Ĵ�����ACR���Ĳ�������                  *
*    BCAN_AMR(0-3):��Ž������μĴ�����AMR���Ĳ�������                  *
*����ֵ:                                                                *
*           0 ;���óɹ�                                                 *
*           1 ;����ʧ��                                                 *
*˵��:����CAN�ڵ��ͨѶ����������յı���,����AMR��ACR��ͬ������.     *
*************************************************************************/ 
bit BCAN_SET_OBJECT(unsigned char  BCAN_ACR0,BCAN_ACR1,BCAN_ACR2,BCAN_ACR3,BCAN_AMR0,BCAN_AMR1,BCAN_AMR2,BCAN_AMR3)
{
  SJA_BCANAdr=REG_TXBuffer1;     

  *SJA_BCANAdr=BCAN_ACR0;        //д�����
   
  SJA_BCANAdr=REG_TXBuffer2;
  *SJA_BCANAdr=BCAN_ACR1;

  SJA_BCANAdr=REG_TXBuffer3;  
  *SJA_BCANAdr=BCAN_ACR2;
   
  SJA_BCANAdr=REG_TXBuffer4; 
  *SJA_BCANAdr=BCAN_ACR3;  
 
  //У��д��ֵ
  if(*SJA_BCANAdr != BCAN_ACR3)  return 1; 
  
  SJA_BCANAdr=REG_TXBuffer5;      

  *SJA_BCANAdr=BCAN_AMR0;     //д�����
  
  SJA_BCANAdr=REG_TXBuffer6;         
  *SJA_BCANAdr=BCAN_AMR1;

  SJA_BCANAdr=REG_TXBuffer7; 
  *SJA_BCANAdr=BCAN_AMR2;

  SJA_BCANAdr=REG_TXBuffer8; 
  *SJA_BCANAdr=BCAN_AMR3;
  //У��д��ֵ
  if(*SJA_BCANAdr != BCAN_AMR3) return 1; 

  return 0;
} 

/************************************************************************
;*����ԭ��:  bit BCAN_SET_BANDRATE(unsigned char CAN_ByteRate)          *
;*����ֵ:                                                               *
;*           0 ;���������óɹ�                                          *
;*           1 ;����������ʧ��                                          *
;*                                                                      * 
;*˵��:����CAN������SJA1000ͨѶ������.SJA1000�ľ������Ϊ16MHZ,         *
;*     ���������Ƶ�ʵ�ֵ�Ĳ����ʣ����Լ����� �����ӳ���ֻ������        *
;*     ��λģʽ                                                         *  
;************************************************************************/ 
bit BCAN_SET_BANDRATE(unsigned char CAN_ByteRate)         //������ѡ��
{
     unsigned char BR_Num= CAN_ByteRate,BTR0_num,BTR1_num;
       switch (BR_Num)
        {
          case ByteRate_10k:
               BTR0_num=0xef;
               BTR1_num=0xff;
               break;
          case ByteRate_40k  :
               BTR0_num=0x87;
               BTR1_num=0xff;
               break;
          case ByteRate_50k:
               //BTR0_num=0x47;
               //BTR1_num=0x2f;
               BTR0_num=0x0e;
               BTR1_num=0x1c;
               break;
          case ByteRate_80k  :
               //BTR0_num=0x83;
               //BTR1_num=0xff;
               BTR0_num=0x49;                      //ok
               BTR1_num=0x1b;
               break;
          case ByteRate_100k  :
               //BTR0_num=0x43;
               //BTR1_num=0x2f;
               BTR0_num=0x04;                       //ok
               BTR1_num=0x1c;
               break;
          case ByteRate_125k  :                      //SJA1000�ľ���Ϊ����Ϊ16MHZ,����������Ϊ125kpbs
               BTR0_num=0x03;
               BTR1_num=0x1c;
               //BTR0_num=0x44;                        //ok
               //BTR1_num=0x1f;
               break;
          case ByteRate_200k  ://24MHZ
            //   BTR0_num=0xc5;  //
             //  BTR1_num=0xa5;
               BTR0_num=0x43;                        //ok
               BTR1_num=0x1b;
               break;
          case ByteRate_250k  ://24MHZ
            //   BTR0_num=0xc5;  //
             //  BTR1_num=0xa5;
               BTR0_num=0x01;                        //ok
               BTR1_num=0x1c;
               break;
          /* case ByteRate_200k  ://24MHZ
               BTR0_num=0x81;
               BTR1_num=0xFA;
               break;*/
          case ByteRate_400k  :
               BTR0_num=0x80;
               BTR1_num=0xfa;
               break;
          case ByteRate_500k  :
               BTR0_num=0x01;
               BTR1_num=0x1c;
               break;
          case ByteRate_800k  :
               BTR0_num=0x00;
               BTR1_num=0x16;
               break;
          case ByteRate_1000k  :
               BTR0_num=0x00;
               BTR1_num=0x14;
               break;
          default :
               return 1;
               break;
        }

    SJA_BCANAdr=REG_BTR0;
    *SJA_BCANAdr=BTR0_num;
    if(*SJA_BCANAdr!=BTR0_num)
      {return 1;}
    SJA_BCANAdr=REG_BTR1;
    *SJA_BCANAdr=BTR1_num;
    if(*SJA_BCANAdr!=BTR1_num)
      {return 1;}
    return 0;
}
/************************************************************************
 *����ԭ��: bit BCAN_SET_CONTROL(unsigend char CMD)                     *
 *����˵��: ���ÿ��ƼĴ���                                              *
 ************************************************************************/
bit BCAN_SET_CONTROL(unsigned char CMD)
{  unsigned char TempData;
 
  SJA_BCANAdr=REG_CONTROL;   //SJA_BaseAdr+0x00  ���ƼĴ���
  TempData=  *SJA_BCANAdr; 
 
  *SJA_BCANAdr=CMD;
 
  if (*SJA_BCANAdr == CMD)
    return 0;
  else
    return 1;

}
/************************************************************************
 *����ԭ��:  bit   BCAN_CREATE_COMMUNATION(void)                        * 
 *����˵��:  ��                                                         *
 *����ֵ:                                                               *
 *           0 ; ��ʾSJA1000�ӿ�����                                    *
 *           1 ; ��ʾSJA1000�봦�����ӿڲ�����                          *
 *˵��:�ú������ڼ��CAN�������Ľӿ��Ƿ�����                            *
 ************************************************************************/
 bit BCAN_CREATE_COMMUNATION(void)
 {  
    SJA_BCANAdr=REG_TEST;      
    *SJA_BCANAdr=0xaa;       //д�����ֵ
    if(*SJA_BCANAdr == 0xaa)
       return 0;            //��������ȷ
    else
       return 1;
     
 }

 /************************************************************************
 *����ԭ��:      bit   BCAN_ENTER_RETMODEL(void)                        *
 *����˵��:  ��                                                         *
 *����ֵ:                                                               *
 *           0 ; ��ʾ�ɹ����븴λ����ģʽ                               *
 *           1 ; ��ʾ���ܽ��븴λ����ģʽ                               *
 *                                                                      * 
 *˵��:      CAN���������븴λ����ģʽ                                  *
 ************************************************************************/ 
 bit   BCAN_ENTER_RETMODEL(void)     //��λ��λ����
 {
    unsigned   char   TempData;
    SJA_BCANAdr  = REG_CONTROL;   

  TempData=  *SJA_BCANAdr;       
    *SJA_BCANAdr=0x01;                 //��λ��λ���� �͵��˲�ģʽ
    if((*SJA_BCANAdr&0x01) == 1)
     return   0;
    else
      return   1;   
 } 
/************************************************************************
 *����ԭ��:   BCAN_CMD_PRG(unsigned char cmd)                           *
 *����˵��:  unsigned char cmd                                          *
 *����ֵ:                                                               *
 *           0 ; ����ɹ�                                               *
 *           1 ; ����ʧ��                                               *
 *                                                                      * 
 *˵��:      ����������                                                 *
 ************************************************************************/
bit  BCAN_CMD_PRG(unsigned char cmd)
 {
   SJA_BCANAdr=REG_COMMAND;            //���ʵ�ַָ������Ĵ���
   *SJA_BCANAdr=cmd;                   //����������
 
   switch(cmd)
   {    case  TR_CMD:                    

           return    0;
           break;

  case  SRR_CMD:      

      return 0;
     break;
    
  case  AT_CMD:                  

            SJA_BCANAdr = REG_STATUS;   //���ʵ�ַָ��״̬�Ĵ���   
           if((*SJA_BCANAdr & 0x20)==0) //�ж��Ƿ����ڷ���
             return  0;
           else
             return  1;              
           break; 
     case  RRB_CMD:                   
           SJA_BCANAdr = REG_STATUS;   //���ʵ�ַָ��״̬�Ĵ���   
           if((*SJA_BCANAdr & 0x01)==1)
              return  1;
           else           
              return  0;               
           break;  
     case  COS_CMD:                  

           SJA_BCANAdr = REG_STATUS;   
           if((*SJA_BCANAdr & 0x02)==0)//�ж���������Ƿ�ɹ�
             return  0; 
           else
             return  1;             
           break; 
     default:
             return  1;
             break; 
   }
}


unsigned char BCAN_DATA_WRITE(unsigned char *SendDataBuf)
 {  unsigned char temp;
   
    SJA_BCANAdr = REG_STATUS;    
    temp=*SJA_BCANAdr;

    if ((temp&0x08)==0) return  1;    //�ϴη���δ���
    if ((temp&0x04)==0) return  2;    //���ͻ������Ƿ����� 
    if ((temp&0x10)==0x10) return 3;  //�ж��Ƿ����ڽ���   

    SJA_BCANAdr = REG_RXBuffer1;      //���ʵ�ַָ���ͻ�����1,�޸ĳ�ͷ�ļ�

    memcpy(SJA_BCANAdr,SendDataBuf,4);   
    BCAN_CMD_PRG(TR_CMD);             //������         
    return 0;
}

//CAN�������ⳤ���ֽ�
void CAN_Send_anylength(unsigned char *CAN_TX_Buf, unsigned char length1, unsigned char com)
{
	unsigned char temptt;
	loop:
    SJA_BCANAdr = REG_STATUS;    
         temptt=*SJA_BCANAdr; 
	//temptt=Read_SJA1000(REG_STATUS);
	if((temptt&0x04)==0x00)  goto loop;               //ѭ�����ȴ�                       
	//�������ͻ�����д����
	{
    SJA_BCANAdr  = REG_TXBuffer1;      //���ʵ�ַָ���ͻ�����1,�޸ĳ�ͷ�ļ�
    *SJA_BCANAdr = length1 + 1;  
    SJA_BCANAdr  = REG_TXBuffer2;      //������ַ
    *SJA_BCANAdr = sendTo;  
     SJA_BCANAdr = REG_TXBuffer3;     //Ŀ���ַ
    *SJA_BCANAdr = MACHINE_ADDRESS;
    SJA_BCANAdr  = REG_TXBuffer4;
    *SJA_BCANAdr = com;
    SJA_BCANAdr  = REG_TXBuffer5; 
    memcpy(SJA_BCANAdr,CAN_TX_Buf,length1);   
	//���ݷ�������
    BCAN_CMD_PRG(TR_CMD);            //������  
	}
}

//CAN����һ���ֽ�
void CAN_Send_onebyte(unsigned char CAN_TX_data, unsigned char com)
{
	unsigned char temptt;
	loop:
    SJA_BCANAdr = REG_STATUS;    
         temptt=*SJA_BCANAdr; 
	//temptt=Read_SJA1000(REG_STATUS);
	if((temptt&0x04)==0x00)  goto loop;               //ѭ�����ȴ�                       
	//�������ͻ�����д����
	{
    SJA_BCANAdr  = REG_TXBuffer1;      //���ʵ�ַָ���ͻ�����1,�޸ĳ�ͷ�ļ�
    *SJA_BCANAdr = 2;  
    SJA_BCANAdr  = REG_TXBuffer2;      //���ʵ�ַָ���ͻ�����1,�޸ĳ�ͷ�ļ�
    *SJA_BCANAdr = sendTo;  
    SJA_BCANAdr  = REG_TXBuffer3;     //���ʵ�ַָ���ͻ�����1,�޸ĳ�ͷ�ļ�
    *SJA_BCANAdr = MACHINE_ADDRESS;
    SJA_BCANAdr  = REG_TXBuffer4;
    *SJA_BCANAdr = com;
    SJA_BCANAdr  = REG_TXBuffer5;
    //memcpy(SJA_BCANAdr,CAN_TX_Buf,length1);  
    *SJA_BCANAdr = CAN_TX_data; 
	//���ݷ�������
    BCAN_CMD_PRG(TR_CMD);            //������  
	}
}


/****************************************************
**����ԭ�ͣ�   bit Sja_1000_Init(void)
**��    �ܣ�   ��ʼ��SJA10000
**��ڲ���:    �� 
**�� �� ֵ:     
      0�� ��ʼ���ɹ� 
      1�� ��λʧ�� 
      2:  ����sja1000ʧ�� 
      3�� ����ʧ�� 
      4�� ���������˲���ʧ��
      5�� ���ò�����ʧ��     
*****************************************************/
unsigned char Sja_1000_Init(void)
{
	bit s; 
	EA=0;                                 //�����ж�
	
	s=BCAN_ENTER_RETMODEL();
	if (s==1) return 1; 
	
	s=BCAN_CREATE_COMMUNATION();       //����ͨ��
	if (s==1) return 2;

	s=BCAN_SET_OUTCLK(0xC8);             //Pelican
	if (s==1) return 3;

	//s=BCAN_SET_OBJECT(0x01,0xe0,0x02,0xe0,0x00,0x0f,0x00,0x0f);//���μĴ���������Ϊ�޹أ��������б���
  s=BCAN_SET_OBJECT(MACHINE_ADDRESS,SLAVE_A_ADDRESS,MACHINE_ADDRESS,SLAVE_B_ADDRESS,0X00,0X00,0X00,0X00);//���μĴ���������Ϊ�޹أ��������б��� 
       //������λΪ1�����˲���0���˲��������
 	//s=BCAN_SET_OBJECT(0x55,0xe0,0xaa,0xa1,0x00,0x00,0xff,0xff);//������&������
	if (s==1) return 4;

	s=BCAN_SET_BANDRATE(ByteRate_125k);    //���ò�����125K 16MHZ
	if (s==1) return 5;
    
	SJA_BCANAdr=REG_OCR ;                  //������ƼĴ���  
	*SJA_BCANAdr=0x1a;        
	SJA_BCANAdr=REG_INTENABLE;      
	*SJA_BCANAdr=0x1D;                  //�����жϣ����պͷ����ж�
    
	SJA_BCANAdr=REG_CONTROL;            //�˳� ��λģʽ
	*SJA_BCANAdr=*SJA_BCANAdr&0xfe;
	if(*SJA_BCANAdr!=0x00)
	return 6;

	EA=1;
	return 0;   
} 

/****************************************************
**����ԭ�ͣ�  void ex0_int(void) interrupt 0 //using 1
**��    �ܣ�  �жϽ��պ���
**��ڲ���:   �� 
**���ڲ���:   RevceData[]����   
**˵    ��:   ��sja1000 �յ���ȷ�ı���ʱ,�����int�ж�           
*****************************************************/
void ex0_int(void) interrupt 0 using 1
{  
	unsigned char tt,tt1,length,com = 0;
 
	SJA_BCANAdr=REG_INTERRUPT;
	if((*SJA_BCANAdr)&0x01)                   //�����˽����ж�
	{  
		SJA_BCANAdr=REG_RXBuffer1;
		tt=*SJA_BCANAdr;
		tt1=*SJA_BCANAdr;
		length=tt1&0x0F;
		if ((tt&0x40)!=0x40)                   //����֡   = ΪԶ��֡
		{  
  			SJA_BCANAdr = REG_RXBuffer4;           //�궨��ı�������memcpy(RevceData,REG_RXBuffer4,8);
        com = *SJA_BCANAdr;
        SJA_BCANAdr = REG_RXBuffer5;
      	memcpy(RevceData,SJA_BCANAdr,length - 1);  //���ܣ���src��ָ�ڴ�������count���ֽڵ�dest��ָ�ڴ�����
  			display(RevceData[0]);
		}
		BCAN_CMD_PRG(RRB_CMD);                  //�ͷ�SJA1000���ջ�������****�Ѿ��޸�
	}
} 

/****************************************************
**����ԭ�ͣ�   void main(void)
**��    �ܣ�   �����򲿷�:
**��ڲ���:    �� 
**�� �� ֵ:     
*****************************************************/
void main(void)
{  
	unsigned char temptt,ss;
	unsigned char num=0;

	CS=0;                //Ƭѡ������
	EA=0;
	
	Init_Cpu(); 
	InitUART();     //��ʼ������ 

	//display(10);		  //��ʾ�ð��A 
	
	ss=Sja_1000_Init();  //��ʼ��SJA1000     
   
	if (ss!=0)             //��ʼ��ʧ��
	{
		SendStr("Sja_1000_Init() failure");              // ����ר�÷��͵����ڿ�״̬
    display(ss);                                     // ��ʾ������Ϣ  
	}
   	else
	{
		SendStr("Sja_1000_Init() sucess");  
    EA=1; //��ʼ���ɹ��������ж�
    display(ss);  
	}

	while(1) 
	{
    // ɨ�谴��ѡ���͵ĵ�ַ�ͷ��͵�����
		if (SEND_SELECTE != 0xF8)
		{
			delay_ms(500);
			switch (SEND_SELECTE)
			{
        case 0xFE:sendTo = SLAVE_A_ADDRESS;break;
        case 0xFD:sendTo = SLAVE_B_ADDRESS;break;
				case 0xFB:CAN_Send_onebyte(1, SEND_COMMAND_QUERY_STATUS);break;
				case 0xF7:CAN_Send_onebyte(2, SEND_COMMAND_SET_PARAM);break;
				case 0xEF:CAN_Send_onebyte(3, SEND_COMMAND_QUERY_PARAM);break;
				case 0xDF:CAN_Send_onebyte(4, SEND_COMMAND_SET_ONOFF);break;
				case 0xBF:CAN_Send_onebyte(5, SEND_COMMAND_SET_RESET);break;
        case 0x7F:break;
				default:break;
			}
		}
		
		SJA_BCANAdr = REG_STATUS;    
    temptt=*SJA_BCANAdr;         
    delay_ms(100);
  	if ((temptt&0x40)==0x40)                     //������״̬
    {  
    		Sja_1000_Init();
    		SendByte(0xee);                    //����ר�÷��͵����ڿ�״̬                     
  	}
	}   
}


