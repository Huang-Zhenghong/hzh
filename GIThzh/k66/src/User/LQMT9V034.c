/*******************************************************************************
��ƽ    ̨������K66FX���ܳ�VDĸ��
����    д��CHIUSIR
��E-mail  ��chiusir@163.com
�������汾��V1.0
�������¡�2018��4��28��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
------------------------------------------------
��dev.env.��IAR7.80.4������
��Target  ��K66FX1M0VLQ18
��Crystal �� 50.000Mhz
��busclock��100.000MHz
��pllclock��200.000MHz
20180424�����µ�DMA������ʽ
******************************************************************************/
#include "include.h"
#include "motor.h"
#include "findtrack.h"
#include "Test.h"
#include "DialSwitch.h"
#include "magnet.h"
#include "steer.h"
#include "biaoding.h"
#include "common.h"
//#include "motor.h"

u8 Image_Data[120][120];      //ͼ��ԭʼ���ݴ��
u8 Image_Data_Second[120][120];
uint8_t Image_Use[LCDH][LCDW]; //ѹ����֮�����ڴ����Ļ��ʾ����
u8 yuantu[LCDH][LCDW];
u8 Pixle[LCDH][LCDW];              //��ֵ��������OLED��ʾ������
uint8_t Threshold;                  //OSTU��򷨼����ͼ����ֵ
u8  Line_Cont=0;          //�м���
u8  Field_Over_Flag=0;    //����ʶ
u8 over = 0;
extern float Error;

extern int BrokenFlag;



int guole=0;

int bbbb=0;
//int shache=0;

extern int xx,yy;
double time;
int ggg=100;
double DIS=200;
void UARTSendPicture2(uint8_t tmImage[CAMERA_H][CAMERA_W]);
void lineshow(void);
void JZTX(void);
//������

void tuxiangchuli(void)
{
  if(over)                                 //���һ��ͼ��ɼ�����ʾ���������ݵ���λ��
  {
    Get_Use_Image1(Field_Over_Flag-1);     //�ɼ�ͼ�����ݴ����
    //    if(DialSwitch_5)
     //   {
    //     ���ڷ������ݷǳ�����ע�͵�OLEDˢ�ºܿ�
    //     DeEXTI_Init(PTD,14); //���жϹر�
    //     DeEXTI_Init(PTD,15); //���жϹر�       
    //     SendPicture();     //�������ݵ���λ����ע��Э���ʽ����ͬ����λ����ԭ������Ӧ�޸�     
    //     EXTI_Init(PTD,14,rising_down);   //���ж�
    //     EXTI_Init(PTD,15,falling_up);    //���ж� 
    //    }      
    //     Threshold = GetOSTU(Image_Data);   //OSTU��� ��ȡȫ����ֵ
   // if(DialSwitch_1==1) 
   // {
    // TFTSPI_Show_Pic4(0, 0, 120, 120, Image_Use); //����TFT1.8��ʾ160*120�Ҷ�ͼ��Image_Use    0, 0, 160, 120,Image_Use            
 //   }
    Get_01_Value();                  //��ֵ��ͼ����
    //JZTX();                          //У��ͼ��
   // Pixle_Filter();                  //ȥ���    
  //  if(DialSwitch_1==1&&DialSwitch_2==1) 
    //{
      TFTSPI_Show_Pic3(0, 0, 120, 120, Image_Use); //����TFT1.8��ʾ160*120�Ҷ�ͼ��Image_Use    0, 0, 160, 120,Image_Use            
    //} 
    over= 0;       
  }
}


void ULTRASOUND(void)
{
  // DIS=200;
  GPIO_Ctrl (PTB,0,1); //trig�øߵ�ƽ
  LPTMR_delay_us(12);   //15us
  GPIO_Ctrl (PTB,0,0); //trig�õ͵�ƽ
  
  //  while(!GPIO_Get(PTB1));
  //  pit_time_start(PIT1);
  /* while(GPIO_Get(PTB1));       
  time=pit_time_get(PIT1);  //��ȡ�ߵ�ƽʱ�䣬������������ʱ��
  dis=time/58.0;            //�������dis
  DIS=(int)dis/100;
  */
}

void kaihuanbizhang(void)
{
  if((DIS<85)&&guole==0&&broken_p==1&&DIS!=0&&ABS(Error)<20)   //����&&broken_p==1
  {
    if(roundflagr!=1&&roundflagl!=1)
    {
      FTM_PWM_Duty(FTM0,FTM_CH1,220);
      FTM_PWM_Duty(FTM0,FTM_CH3,220);
      FTM_PWM_Duty(FTM3,FTM_CH0,SteerMin);
      LPTMR_delay_ms(255);
      FTM_PWM_Duty(FTM0,FTM_CH1,220);
      FTM_PWM_Duty(FTM0,FTM_CH3,220);
      FTM_PWM_Duty(FTM3,FTM_CH0,SteerMax);
      LPTMR_delay_ms(350);
      FTM_PWM_Duty(FTM0,FTM_CH1,220);
      FTM_PWM_Duty(FTM0,FTM_CH3,220);
      FTM_PWM_Duty(FTM3,FTM_CH0,SteerMidle);
      LPTMR_delay_ms(350);
      FTM_PWM_Duty(FTM0,FTM_CH1,220);
      FTM_PWM_Duty(FTM0,FTM_CH3,220);
      FTM_PWM_Duty(FTM3,FTM_CH0,SteerMax);
      LPTMR_delay_ms(340);
      FTM_PWM_Duty(FTM0,FTM_CH1,220);
      FTM_PWM_Duty(FTM0,FTM_CH3,220);
      FTM_PWM_Duty(FTM3,FTM_CH0,SteerMin);
      LPTMR_delay_ms(210);
      
    }
    DIS=200;
    guole=1;
  }
  if(guole==1)
  {
    if(ggg>0)
      ggg--;
    else
    {
      guole=2;
      ggg=100;
    }
    
  }
}

void xunjizhuti(void)
{
  if(stopstop<70)
  {
    FTM_PWM_Duty(FTM3,FTM_CH0,SteerMidle);
    
  }
  

  
  else if(!BrokenFlag)
  {
    GPIO_Ctrl(PTA,19,0);
    out=0;
    rengongshichang();
    SteerControl();
    
  }      
  else
  {  
    GPIO_Ctrl(PTA,19,1);
    kongzhi=magnetanalysis1();     
   magnetcontrol(kongzhi);
  }
}


void dianjikongzhi(void)
{
  //if(DialSwitch_3)
    MotorControlOpenLoop();//��������
  //else
    //MotorControl();//����ʽpid�㷨
}

void yuxianpanduan(void)
{
  GetBlackEndParam();      
  //magnetanalysis2();
  yuanhuanshibie(); 
  ULTRASOUND();
  
}

//����ͷͼ��ɼ��жϴ�������
void PORTD_Interrupt(void)
{     
  //���ж�PTD14
  if((PORTD_ISFR & 0x4000))//���ж� (1<<14)
  {    
    PORTD_ISFR |= 0x4000;  //����жϱ�ʶ
    // �û�����            
    //DMA�ɼ����������޸Ĳɼ��ӿ�PTD_BYTE0_IN��0--D7��   PLCK�ӵ���PTD13��   
    //DMA_PORTx2BUFF_Init (DMA_CH4, (void *)&PTD_BYTE0_IN,(void*)Image_Data[Line_Cont], PTD13, DMA_BYTE1, CAMERA_W, DMA_rising);  
    if(Field_Over_Flag==1)
    {
      DMATransDataStart(DMA_CH4,(uint32_t)(&Image_Data[Line_Cont][0]));     
    }
    else
    {
      DMATransDataStart(DMA_CH4,(uint32_t)(&Image_Data_Second[Line_Cont][0]));     
    }
    if(Line_Cont > 120)  //�ɼ�����
    { 
      Line_Cont=0; 
      return ;
    } 
    ++Line_Cont;            //�м���
    return ;
  }
  //���ж�PTD15
  if((PORTD_ISFR & 0x8000))//(1<<15)
  {
    PORTD_ISFR |= 0x8000; //����жϱ�ʶ
    // �û����� 
    Line_Cont = 0;         //�м�������
    
    if(Field_Over_Flag==1)
    {
      Field_Over_Flag = 2;     //��������ʶ
    }
    else //if(Field_Over_Flag==2)
    {
      Field_Over_Flag = 1;     //��������ʶ
    }
    bbbb++;
    over = 1;
  } 
}

/*************************************************************************
*                    �����������ܿƼ� 
*
*  �������ƣ�void SendPicture()
*  ����˵��������ͷ���ݷ���
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺
*  ��    ע��
*************************************************************************/
void SendPicture(void)
{
  int i = 0, j = 0;
  //UART_Put_Char(UART_4,0xff);//����֡ͷ��־
  for(i=0;i<CAMERA_H;i++)      //���
  {
    for(j=0;j<CAMERA_W;j++)    //����ӵ�0�е��У��û�����ѡ���Ե�������ʵ�����
    {
      //   if(Image_Data[i][j]==0xff)
      //   {
      //     Image_Data[i][j]=0xfe;//��ֹ���ͱ�־λ
      //   }
      UART_Put_Char(UART_4,Image_Data[i][j]);
    }
  }
}

void TFTSPI_Show_Pic3(uint8_t xs,uint8_t ys,uint8_t w,uint8_t h,uint8_t ppic[LCDH][LCDW]) 
{
  unsigned int i,j;	
  TFTSPI_Set_Pos(xs,ys,xs+w-1,ys+h);
  for(i=0;i<h;i+=1)  //
  { 	
    for(j=0; j<w; j+=1) //
    {
      if(ppic[i][j])
      {
        TFTSPI_Write_Word(0xffff); //��λ��ǰ��������������ϳ�һ��16λ���ݱ�ʾ����ֵ  
        //        TFTSPI_Draw_Dot(j/2, i/2+20, (ppic[i][2*j]<<8)+(ppic[i][2*j+1]));
      }
      else
      {
        TFTSPI_Write_Word(0x0000); //��λ��ǰ��������������ϳ�һ��16λ���ݱ�ʾ����ֵ 
      }
      
    }
    
  }
}

/****************��ʾͼƬ���ӵ�Ƭ����DATA����********************************/	
/*��ʼλ��x        y    ͼƬ����      �߶�   ͼƬ������*/

void TFTSPI_Show_Pic4(uint8_t xs,uint8_t ys,uint8_t w,uint8_t h,uint8_t Use_Buff[LCDH][LCDW]) 
{
  unsigned int i,j;
  uint16 color;
  TFTSPI_Set_Pos(xs,ys,xs+w-1,ys+h);
  for(i=0;i<h;i+=1)  //
  { 	
    for(j=0; j<w; j+=1) //
    {
      color=(0x001f&((Use_Buff[i][j])>>3))<<11;
      color=color|(((0x003f)&((Use_Buff[i][j])>>2))<<5);
      color=color|(0x001f&((Use_Buff[i][j])>>3));
      TFTSPI_Write_Word(color);            
    }
    
  }
}











///////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


//������������������



void GOGOGO(void)
{  
  //int saomiao = 0;
  LQMT9V034_Init();        //����ͷ��ʼ��  
  while(1)
  { 
    LED_Ctrl(LED1, RVS);                     //LEDָʾ��������״̬
    tuxiangchuli();
    
    if(DialSwitch_4)
    { 
     // gamestart_over();
     if(/*game==1*/1)
      {
        yuxianpanduan();
        xunjizhuti();     
      //  kaihuanbizhang();
        if(DialSwitch_5)
        {
          lineshow();
        }  
      }
     
      dianjikongzhi();
   /*  UART_Put_Char(UART_4,0X03);
     UART_Put_Char(UART_4,0XFC);
     
     UART_Put_Char(UART_4,GetLeftMotorPules);
     UART_Put_Char(UART_4,GetLeftMotorPules>>8);
     UART_Put_Char(UART_4,GetLeftMotorPules>>16);
     UART_Put_Char(UART_4,GetLeftMotorPules>>24);
     
     UART_Put_Char(UART_4,0XFC);
     UART_Put_Char(UART_4,0X03);*/
     
    }    
  }
}



/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////



void lineshow(void)
{
  
  int i;
 // for(i=39;i<120;i+=2)
 // {
    //if(Pixle[i][118-i] == Black_Point)
    //if(Pixle[i][41+i] == Black_Point)
 //   TFTSPI_Draw_Dot(118-i,i,u16RED);
 //   TFTSPI_Draw_Dot(41+i,i,u16RED);
 // }
  //  LPTMR_delay_ms(200);
for(i=0;i<m+1;i++)
{
  TFTSPI_Draw_Dot(midline_x[i],midline_y[i],u16RED);
}
  
  TFTSPI_Draw_Dot(79,40,u16RED);TFTSPI_Draw_Dot(40,60,u16RED);TFTSPI_Draw_Dot(40,80,u16RED);
}



void JZTX(void)
{
  int i=0,j=0;
  int A,B,C;
  for(i=0;i<CAMERA_H;i++)
  {
    for(j=0;j<CAMERA_W;j++)
    {
      C=i*160+j;
      A=jiaozheng_y[C];
      B=jiaozheng_x[C];
      if(A<0||B<0)
        Pixle[i][j]=0;
      else
        Pixle[i][j]=Image_Use[A][B];
    }
  }
}




















// MT9V034 Port Init
void LQMT9V034_Init(void)
{     
  // uint16_t data = 0;  
  TFTSPI_CLS(u16BLACK);
  //GPIO�ڳ�ʼ��
  EXTI_Init(PTD,14,rising_down);   //���ж�
  EXTI_Init(PTD,15,falling_up);    //���ж�  
  GPIO_Init(PTD,0,GPI,0);
  GPIO_Init(PTD,1,GPI,0);      
  GPIO_Init(PTD,2,GPI,0);
  GPIO_Init(PTD,3,GPI,0);
  GPIO_Init(PTD,4,GPI,0);
  GPIO_Init(PTD,5,GPI,0);
  GPIO_Init(PTD,6,GPI,0);
  GPIO_Init(PTD,7,GPI,0);
  //��λ���������
  //����ͷ�Ĵ�������
  SCCB_Init(); 
  //������ַ�ڶ����ߣ�ΪMT9V034_I2C_ADDR  
  
  MT9V034_SetFrameResolution(CAMERA_H, CAMERA_W);//��������ͷͼ��4*4��Ƶ���PCLK, 27/4 = 6.75M ,BIT4,5��������:�������Ҿ�����   
  MT9V034_SetAutoExposure(1);  
  SCCB_RegWrite(MT9V034_I2C_ADDR, 0xAC, 0x0001);
  SCCB_RegWrite(MT9V034_I2C_ADDR, 0xAD, 0x01E0);  
  SCCB_RegWrite(MT9V034_I2C_ADDR, 0x2C, 0x0004);
  
  //SCCB_RegWrite(MT9V034_I2C_ADDR, 0x7F, 0x3000);           // test pattern
  
  SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_ANALOG_CTRL, MT9V034_ANTI_ECLIPSE_ENABLE);
  SCCB_RegWrite(MT9V034_I2C_ADDR, 0x0F, 0x0000);  
  SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_HDR_ENABLE_REG, 0x0101); // 0x0F bit8:1HDR,0linear; bit1:1��ɫ,0�Ҷ�;bit0:1HDR,0linear
  //MT9V034_WriteReg16(MT9V034_HDR_ENABLE_REG, 0x0103);     // 0x0F bit8:1HDR,0linear; bit1:1��ɫ,0�Ҷ�;bit0:1HDR,0linear
  //0x07 Chip Control bit2-0:0����ɨ��,1��Ч��2����3������bit5:1�����Ӿ�ʹ��,bit7:1����ʹ�ܣ�bit8:1ͬ��ģʽ;bit9:1����������bit15:0A/1B
  SCCB_RegWrite(MT9V034_I2C_ADDR,MT9V034_CHIP_CONTROL, 0x0188);          //Context A  
  SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_ROW_NOISE_CORR_CTRL_REG, 0);   //0x70  0x0000 
  SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_AEC_AGC_ENABLE_REG, 0x0303);   //0xAF  AEC/AGC A~bit0:1AE;bit1:1AG/B~bit2:1AE;bit3:1AG
  
  SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_MIN_EXPOSURE_REG, 0x0001);     //0xAC  ��С�ֿ��ſ���   0x0001
  SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_MAX_EXPOSURE_REG, 0x01E0);     //0xAD  ���׿��ſ���   0x01E0-480
  SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_MAX_GAIN_REG, 50);             //0xAB  ���ģ������     64
  
  SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_AGC_AEC_PIXEL_COUNT_REG, 188*120);//0xB0  ����AEC/AGCֱ��ͼ������Ŀ,���44000   4096=320*240  
  SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_ADC_RES_CTRL_REG, 0x0303);     //0x1C  here is the way to regulate darkness :)    
  
  SCCB_RegWrite(MT9V034_I2C_ADDR,0x13,0x2D2E);//We also recommended using R0x13 = 0x2D2E with this setting for better column FPN.  
  SCCB_RegWrite(MT9V034_I2C_ADDR,0x20,0x03C7);//0x01C7�ԱȶȲ���ף�0x03C7�Աȶ���� Recommended by design to improve performance in HDR mode and when frame rate is low.
  SCCB_RegWrite(MT9V034_I2C_ADDR,0x24,0x0010);//Corrects pixel negative dark offset when global reset in R0x20[9] is enabled.
  SCCB_RegWrite(MT9V034_I2C_ADDR,0x2B,0x0003);//Improves column FPN.
  SCCB_RegWrite(MT9V034_I2C_ADDR,0x2F,0x0003);//Improves FPN at near-saturation.  
  
  //SCCB_RegWrite(MT9V034_I2C_ADDR, 0x08, 0x03D4);
  //SCCB_RegWrite(MT9V034_I2C_ADDR, 0x09, 0x03E7);
  //100DB //�����ع�ʱ��
  SCCB_RegWrite(MT9V034_I2C_ADDR,MT9V034_SHUTTER_WIDTH1,0x01BB);        //0x08 Coarse Shutter CAMERA_W 1
  SCCB_RegWrite(MT9V034_I2C_ADDR,MT9V034_SHUTTER_WIDTH2,0x01D9);        //0x09 Coarse Shutter CAMERA_W 2
  SCCB_RegWrite(MT9V034_I2C_ADDR,MT9V034_SHUTTER_WIDTH_CONTROL,0x0064); //0x0A Coarse Shutter CAMERA_W Control 
  SCCB_RegWrite(MT9V034_I2C_ADDR,MT9V034_V2_CTRL_REG_A, 0x001A);        //0x32   0x001A  
  SCCB_RegWrite(MT9V034_I2C_ADDR,MT9V034_TOTAL_SHUTTER_WIDTH,0x0078);   //0x0B Coarse Shutter CAMERA_W Total
  SCCB_RegWrite(MT9V034_I2C_ADDR,MT9V034_HDR_ENABLE_REG,0x0103);        //0x0F High Dynamic Range enable,bit is set (R0x0F[1]=1), the sensor uses black level correction values from one green plane, which are applied to all colors.
  SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_AGC_AEC_DESIRED_BIN_REG, 60); //0xA5  ͼ������  50  1-64
  SCCB_RegWrite(MT9V034_I2C_ADDR,MT9V034_ANALOG_GAIN,0x8010);           //0x35
  
  //80dB HDR
  //SCCB_RegWrite(MT9V034_I2C_ADDR, 0x08, 0x03CA);0x01BB
  //SCCB_RegWrite(MT9V034_I2C_ADDR, 0x09, 0x03DE);0x01D9
  //SCCB_RegWrite(MT9V034_I2C_ADDR, 0x0A, 0x0064);0x0064
  //SCCB_RegWrite(MT9V034_I2C_ADDR, 0x0B, 0x03E8);0x00E8
  //SCCB_RegWrite(MT9V034_I2C_ADDR, 0x0F, 0x0103);0x0103
  //SCCB_RegWrite(MT9V034_I2C_ADDR, 0x35, 0x8010);0x8010 
  
  SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_RESET, 0x03);          //0x0c  ��λ 
  
  
  //��ʼ��DMA�ɼ�  
  DMA_PORTx2BUFF_Init (DMA_CH4, (void *)&PTD_BYTE0_IN,(void*)Image_Data, PTD13, DMA_BYTE1, CAMERA_W, DMA_rising);  //DMA_rising
}

void MT9V034_SetFrameResolution(uint16_t height,uint16_t width)
{
  uint16_t data = 0;
  
  if((width*4)<=MAX_IMAGE_WIDTH && (height*4)<=MAX_IMAGE_HEIGHT)
  {
    width *= 4;
    height *= 4;
    data |= MT9V034_READ_MODE_ROW_BIN_4;
    data |= MT9V034_READ_MODE_COL_BIN_4;
  }
  else if((width*2)<=MAX_IMAGE_WIDTH && (height*2)<=MAX_IMAGE_HEIGHT)
  {
    width *= 2;
    height *= 2;
    data |= MT9V034_READ_MODE_ROW_BIN_2;
    data |= MT9V034_READ_MODE_COL_BIN_2;
  }
  
  //SCCB_RegWrite(MT9V034_I2C_ADDR,0x01,MT9V034_COLUMN_START_DEF);     // Column Start
  //SCCB_RegWrite(MT9V034_I2C_ADDR,0x02,MT9V034_ROW_START_DEF);        // Row Start  
  //SCCB_RegWrite(MT9V034_I2C_ADDR,0x03,MT9V034_WINDOW_HEIGHT_DEF);    // height 
  //SCCB_RegWrite(MT9V034_I2C_ADDR,0x04,MT9V034_WINDOW_WIDTH_DEF);     // width  
  //SCCB_RegWrite(MT9V034_I2C_ADDR,0x05,MT9V034_HORIZONTAL_BLANKING_MIN);   // Horizontal Blanking  809-640
  //SCCB_RegWrite(MT9V034_I2C_ADDR,0x06,MT9V034_VERTICAL_BLANKING_MIN);     // Vertical Blanking    499-480 
  
  //����ͼ�������СΪ120*188������ʧ��Ұ��ͬʱ�������ܳ���Ҫ
  //SCCB_RegWrite(MT9V034_I2C_ADDR,0x0D,0x030A);   //��������ͷͼ��4*4��Ƶ���PCLK, 27/4 = 6.75M ,BIT4,5�������� 
  //SCCB_RegWrite(MT9V034_I2C_ADDR,0x0D,0x033A);   //��������ͷͼ��4*4��Ƶ���PCLK, 27/4 = 6.75M ,BIT4,5��������:�������Ҿ����� 
  
  data |= (MT9V034_READ_MODE_ROW_FLIP|MT9V034_READ_MODE_COLUMN_FLIP);       //LQ-MT9V034 needs vertical mirror to capture correct image
  
  SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_READ_MODE, data);
  
  SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_WINDOW_WIDTH,  width);
  SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_WINDOW_HEIGHT, height);
  
  SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_COLUMN_START, (MAX_IMAGE_WIDTH-width)/2+MT9V034_COLUMN_START_MIN);
  SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_ROW_START, (MAX_IMAGE_HEIGHT-height)/2+MT9V034_ROW_START_MIN);
}

void MT9V034_SetAutoExposure(char enable)
{
  uint16_t reg =0;
  SCCB_RegRead(MT9V034_I2C_ADDR, MT9V034_AEC_AGC_ENABLE,&reg);
  if(1 == enable)
  {
    SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_AEC_AGC_ENABLE, reg|MT9V034_AEC_ENABLE|MT9V034_AGC_ENABLE);
  }
  else
  {
    SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_AEC_AGC_ENABLE, reg&~(MT9V034_AEC_ENABLE|MT9V034_AGC_ENABLE));
  }
}
void MT9V034_SetFrameRate(uint8_t frameRate)
{
  
}

void MT9V034_Reset(void)
{
  //Reset MT9V034, but register config will not change.
  SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_RESET, 0x0001);
  time_delay_ms(10);
  
  //Unlock MT9V034, allowing user to initiate register settings and readout
  SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_CHIP_CONTROL, 0x0188);
  
  //Reset Again.
  SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_RESET, 0x0001);
  time_delay_ms(10);
}

void MT9V034_SetReservedReg(void)
{
  //Here we write some reserved registers as recommendations from Rev.G datasheet, Table.8
  SCCB_RegWrite(MT9V034_I2C_ADDR, 0x13, 0x2D2E);
  SCCB_RegWrite(MT9V034_I2C_ADDR, 0x20, 0x03C7);
  SCCB_RegWrite(MT9V034_I2C_ADDR, 0x24, 0x001B);
  SCCB_RegWrite(MT9V034_I2C_ADDR, 0x2B, 0x0003);
  SCCB_RegWrite(MT9V034_I2C_ADDR, 0x2F, 0x0003);
}

/***************************************************************  
* 
* �������ƣ�void DMATransDataInit(DMA_CHn CHn,void *SADDR, void *DADDR,PTXn_e ptxn,DMA_BYTEn byten,u32 count,DMA_PORTx2BUFF_cfg cfg) 
* ����˵������ʼ��DMA 
* ����˵����ͨ����ţ�Դ��ַ��Ŀ�ĵ�ַ�������ܽţ��ֽ�����ѭ���������������� 
* �������أ��� 
* �޸�ʱ�䣺2018��3��27�� 
* �� ע�� 
***************************************************************/ 
__ramfunc void DMATransDataInit(DMA_CHn CHn,void *SADDR, void *DADDR,PTXn_e ptxn,DMA_BYTEn byten,u32 count,DMA_Count_cfg cfg) 
{ 
  u8 BYTEs = (byten == DMA_BYTE1 ? 1 : (byten == DMA_BYTE2 ? 2 : (byten == DMA_BYTE4 ? 4 : 16 ) ) ); //���㴫���ֽ���
  //����ʱ�� 
  SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;                        //��DMAģ��ʱ��
  SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;                     //��DMA��·������ʱ��
  // ���� DMA ͨ�� �� ������ƿ� TCD ( Transfer Control Descriptor ) 
  DMA_SADDR(CHn) =    (u32)SADDR;                         // ����  Դ��ַ
  DMA_DADDR(CHn) =    (u32)DADDR;                         // ����Ŀ�ĵ�ַ
  DMA_SOFF(CHn)  =    0;                                  // ����Դ��ַ����
  DMA_DOFF(CHn)  =    BYTEs;                                  // ÿ�δ����Ŀ�ļ�BYUEs
  DMA_ATTR(CHn)  =    (0
                       | DMA_ATTR_SMOD(0x0)                // Դ��ַģ����ֹ  Source address modulo feature is disabled
                         | DMA_ATTR_SSIZE(byten)             // Դ����λ�� ��DMA_BYTEn  ��    SSIZE = 0 -> 8-bit ��SSIZE = 1 -> 16-bit ��SSIZE = 2 -> 32-bit ��SSIZE = 4 -> 16-byte
                           | DMA_ATTR_DMOD(0x0)                // Ŀ���ַģ����ֹ
                             | DMA_ATTR_DSIZE(byten)             // Ŀ������λ�� ��DMA_BYTEn  ��  ���òο�  SSIZE
                               );
  DMA_CITER_ELINKNO(CHn)  = DMA_CITER_ELINKNO_CITER(count); //��ǰ��ѭ������
  DMA_BITER_ELINKNO(CHn)  = DMA_BITER_ELINKYES_BITER(count);//��ʼ��ѭ������
  
  DMA_CR &= ~DMA_CR_EMLM_MASK;                            // CR[EMLM] = 0  disable Minor Loop Mapping
  
  DMA_NBYTES_MLNO(CHn) =   DMA_NBYTES_MLNO_NBYTES(BYTEs); // ͨ��ÿ�δ����ֽ�������������ΪBYTEs���ֽڡ�ע��ֵΪ0��ʾ����4GB 
  
  // ���� DMA ���������Ĳ��� 
  DMA_SLAST(CHn)      =   0;                              //����Դ��ַ�ĸ���ֵ,��ѭ��������ָ�Դ��ַ
  DMA_DLAST_SGA(CHn)  =   0;                              //����Ŀ�ĵ�ַ�ĸ���ֵ,��ѭ��������ָ�Ŀ�ĵ�ַ���߱��ֵ�ַ
  DMA_CSR(CHn)        =   (0
                           | DMA_CSR_DREQ_MASK            //��ѭ��������ֹͣӲ������
                             | DMA_CSR_INTMAJOR_MASK        //��ѭ������������ж�
                               );
  // ���� DMA ����Դ 
  DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR, CHn) = (0
                                            | DMAMUX_CHCFG_ENBL_MASK                        // Enable routing of DMA request 
                                              | DMAMUX_CHCFG_SOURCE((ptxn >> 5) + DMA_Port_A) // ͨ����������Դ:     
                                                );
  //GPIO_Init(GPIOD,12,GPI,0); //����  
  SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK << (ptxn>>5));                                //����PORTx�˿�
  GPIO_PDDR_REG(GPIOX[(ptxn>>5)]) &= ~(1 << (ptxn & 0x1f));                        //���ö˿ڷ���Ϊ����
  PORT_PCR_REG(PORTX[(ptxn>>5)], (ptxn & 0x1F)) = ( 0
                                                   | PORT_PCR_MUX(1)               // ����GPIO
                                                     | PORT_PCR_IRQC(cfg & 0x03 )    // ȷ������ģʽ
                                                       | ((cfg & 0xc0 ) >> 6)          // �����������������裬����û��
                                                         );
  GPIO_PDDR_REG(GPIOX[(ptxn>>5)]) &= ~(1 << (ptxn && 0x1F));  
  
  //�����ж� 
  DMA_EN(CHn);                                      //ʹ��ͨ��CHn Ӳ������
  //DMA_IRQ_EN(CHn);                                //����DMAͨ������
} 





// ��ȡ��Ҫ��ͼ������
__ramfunc void Get_Use_Image1(u8 picture_number)
{
  int i = 0,j = 0,row = 0,line = 0;
  if(picture_number)
  {
    for(i = 0; i  < CAMERA_H; i+=1)  //120�У�ÿ2�вɼ�һ�У�
    {
      for(j = 0;j < CAMERA_W; j+=1)  //188��
      {        
        Image_Use[row][line] = Image_Data[i][j];
        
        line+=1;        
      }      
      line = 0;
      row+=1;      
    } 
  }
  else
  {
    for(i = 0; i  < CAMERA_H; i+=1)  //120�У�ÿ2�вɼ�һ�У�
    {
      for(j = 0;j < CAMERA_W; j+=1)  //188��
      {        
        Image_Use[row][line] = Image_Data_Second[i][j];
        
        line+=1;        
      }      
      line = 0;
      row+=1;      
    } 
  }
}



//���վ�ֵ�ı������ж�ֵ��
void Get_01_Value(void)
{
  int i = 0,j = 0;
  u8 GaveValue;
 /* u32 tv=0;
  // char txt[16];
  
  //�ۼ�
  for(i = 0; i <LCDH; i+=5)
  {    
    for(j = 0; j <LCDW; j+=5)
    {                            
      tv+=Image_Use[i][j];   //�ۼ�  
    } 
  }
  GaveValue=25*tv/(LCDH)/(LCDW);     //��ƽ��ֵ,����Խ��ԽС��ȫ��Լ35��������ĻԼ160��һ������´�Լ100 
  // sprintf(txt,"%03d:%03d",Threshold,GaveValue);//ǰ��Ϊ�����õ���ֵ������Ϊƽ��ֵ  
  //LCD_P6x8Str(80,1,(u8*)txt);
  //���վ�ֵ�ı������ж�ֵ��*/
 // GaveValue=GaveValue*7/10+20;//*7/10+2;//�˴���ֵ���ã����ݻ����Ĺ������趨   ʵ���Ұ���Ϊ0.9��1������Ϊ0.3��0.4
  
 //  GaveValue=GaveValue*1/11;
   //if(GaveValue<0)
  // GaveValue=0;
  //if(GaveValue>245)
  //  GaveValue=245;
  GaveValue=60;
  for(i = 0; i < LCDH; i++)
  {
    for(j = 0; j < LCDW; j++)
    {                                
      if(Image_Use[i][j] >GaveValue)//ƽ��ֵ��ֵ
        //if(Image_Use[i][j] >Threshold) //�����ֵ   ��ֵԽ����ʾ������Խ�࣬��ǳ��ͼ��Ҳ����ʾ����    
        Image_Use[i][j] =1;        
      else                                        
        Image_Use[i][j] =0;
    }    
  }
  
  
  for(i=0;i<120;i++)
  {
    for(j=0;j<120;j++)
    {
      if(Image_Use[i][j]==1&&Image_Use[i-1][j]==1&&Image_Use[i+1][j]==1&&Image_Use[i][j-1]==1&&Image_Use[i+1][j]==1
         &&Image_Use[i][j+1]==1)
      {
        
        xx=i;
        yy=j;
        break;
        
      }
    }
  }
}
//��ʾͼ��OLEDģ��
void Draw_Road(void)
{ 	 
  u8 i = 0, j = 0,temp=0;
  
  //����֡ͷ��־
  for(i=8;i<56;i+=8)//6*8=48�� 
  {
    LCD_Set_Pos(18,i/8+1);//��ʼλ��
    for(j=0;j<LCDW;j++)  //����
    { 
      temp=0;
      if(Pixle[0+i][j]) temp|=1;
      if(Pixle[1+i][j]) temp|=2;
      if(Pixle[2+i][j]) temp|=4;
      if(Pixle[3+i][j]) temp|=8;
      if(Pixle[4+i][j]) temp|=0x10;
      if(Pixle[5+i][j]) temp|=0x20;
      if(Pixle[6+i][j]) temp|=0x40;
      if(Pixle[7+i][j]) temp|=0x80;
      LCD_WrDat(temp); 	  	  	  	  
    }
  }  
}
//�������Ϸ���Χ��������
void Pixle_Filter(void)
{  
  int nr; //��
  int nc; //��
  
  for(nr=1; nr<LCDH-1; nr++)
  {  	    
    for(nc=1; nc<LCDW-1; nc++)
    {
      if((Pixle[nr][nc]==0)&&(Pixle[nr-1][nc]+Pixle[nr+1][nc]+Pixle[nr][nc+1]+Pixle[nr][nc-1]>2))         
      {
        Pixle[nr][nc]=1;
      }	
      else if((Pixle[nr][nc]==1)&&(Pixle[nr-1][nc]+Pixle[nr+1][nc]+Pixle[nr][nc+1]+Pixle[nr][nc-1]<2))         
      {
        Pixle[nr][nc]=0;
      }	
    }	  
  }  
}

/***************************************************************************
*                                                                          *
*  �������ƣ�int Seek_Road(void)                                           *
*  ����˵����Ѱ�Ұ�ɫ����ƫ��ֵ                                            *
*  ����˵������                                                            *
*  �������أ�ֵ�Ĵ�С                                                      *
*  �޸�ʱ�䣺2017-07-16                                                    *
*  ��    ע�����м�Ϊ0������һ���Ҳ��һ����ֵ����1�����                *
*            ��������ӵ�һ�п�ʼ�������ڶ��н�����                        *
*            ������Ϊ��������ֵԽ��˵��Խƫ��ߣ�                        *
*            ������Ϊ��������ֵԽ��˵��Խƫ�ұߡ�                        *
***************************************************************************/ 
/*
void Seek_Road(void)
{  
int nr; //��
int nc; //��
int temp=0;//��ʱ��ֵ
//for(nr=1; nr<MAX_ROW-1; nr++)
temp=0;
for(nr=8; nr<24; nr++)
{  	    
for(nc=MAX_COL/2;nc<MAX_COL;nc=nc+1)
{
if(Pixle[nr][nc])
{
++temp;
      }			   
    }
for(nc=0; nc<MAX_COL/2; nc=nc+1)
{
if(Pixle[nr][nc])
{
--temp;
      }			   
    }		  
  }
OFFSET0=temp;
temp=0;
for(nr=24; nr<40; nr++)
{  	    
for(nc=MAX_COL/2;nc<MAX_COL;nc=nc+1)
{
if(Pixle[nr][nc])
{
++temp;
      }			   
    }
for(nc=0; nc<MAX_COL/2; nc=nc+1)
{
if(Pixle[nr][nc])
{
--temp;
      }			   
    }		  
  }
OFFSET1=temp;    	
temp=0;
for(nr=40; nr<56; nr++)
{  	    
for(nc=MAX_COL/2;nc<MAX_COL;nc=nc+1)
{
if(Pixle[nr][nc])
{
++temp;
      }			   
    }
for(nc=0; nc<MAX_COL/2; nc=nc+1)
{
if(Pixle[nr][nc])
{
--temp;
      }			   
    }		  
  }
OFFSET2=temp;   	
return;  
}

u8 zb[48],yb[48];
void FindTiXing(void)
{
int nr; //��
int nc; //��     

for(nr=0; nr<48; nr++)
{  	    
zb[nr]=0;
yb[nr]=100;   
  }  	
for(nr=0; nr<48; nr++)
{  	    
for(nc=2;nc<MAX_COL-2;nc++)
{
if((Pixle[nr+8][nc-1]==0)&&(Pixle[nr+8][nc]==0)&&(Pixle[nr+8][nc+1]==1)&&(Pixle[nr+8][nc+2]==1))
{
zb[nr]=nc;//����أ�Խ��Խ��
      }
if((Pixle[nr+8][nc-1]==1)&&(Pixle[nr+8][nc]==1)&&(Pixle[nr+8][nc+1]==0)&&(Pixle[nr+8][nc+2]==0))
{
yb[nr]=nc;//�ұ��أ�Խ��ԽС
      }                   
    }	    
  }
TXV=0;
for(nr=0; nr<47; nr++)
{  	    
if((zb[nr]>=zb[nr+1])&&(zb[nr]>0))   TXV++;          
if((yb[nr]<=yb[nr+1])&&(yb[nr]<100)) TXV--;          
  }  	   
return;  
}
*/
/*************************************************************************
* �����������ܿƼ� KV58���ܳ�ĸ��           
*
*  �������ƣ�void SCCB_Init(void)
*  ����˵��������SCCB��������ΪGPIO���ܣ���ʱ���������ݷ���
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2017��12��5��
*  ��    ע��
*************************************************************************/
void SCCB_Init(void)
{ 
  GPIO_Init(PTE, 0,GPO,0);//����ΪGPIO����
  GPIO_Init(PTE, 1,GPO,0);//����ΪGPIO����  
}

/*************************************************************************
* �����������ܿƼ� KV58���ܳ�ĸ��           
*
*  �������ƣ�void SCCB_Wait(void)
*  ����˵����SCCB�ȴ���ʾ
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2017��12��5��
*  ��    ע��
*************************************************************************/
void SCCB_Wait(void)
{
  uint8 i=0;
  for(i=0;i<100;i++)
  { 
    asm ("nop");
  }  
}

/*************************************************************************
* �����������ܿƼ� KV58���ܳ�ĸ��           
*
*  �������ƣ�void SCCB_Star(void)
*  ����˵������������
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2017��12��5��
*  ��    ע��
*************************************************************************/
void SCCB_Star(void)
{
  SCL_Out;
  SDA_Out;
  SCCB_Wait();
  SDA_High;
  SCL_High; 
  SCCB_Wait();
  SDA_Low;
  SCCB_Wait();
  SCL_Low; 
  SCCB_Wait();
}
/*************************************************************************
* �����������ܿƼ� KV58���ܳ�ĸ��           
*
*  �������ƣ�void SCCB_Stop(void)
*  ����˵����ֹͣ����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2017��12��5��
*  ��    ע��
*************************************************************************/
void SCCB_Stop(void)
{
  SCL_Out;
  SDA_Out;
  SCCB_Wait();
  SDA_Low;
  SCCB_Wait();
  SCL_High; 
  SCCB_Wait();
  SDA_High;
  SCCB_Wait();  
}
/*************************************************************************
* �����������ܿƼ� KV58���ܳ�ĸ��           
*
*  �������ƣ�uint8 SCCB_SendByte(uint8 Data)
*  ����˵����SCCB�����ֽں���
*  ����˵����Ҫ���͵��ֽ�
*  �������أ�Ӧ���ź�
*  �޸�ʱ�䣺2017��12��5��
*  ��    ע��
*************************************************************************/
uint8 SCCB_SendByte(uint8 Data)
{
  uint8 i;
  uint8 Ack;
  SDA_Out;
  for( i=0; i<8; i++)
  {
    if(Data & 0x80) SDA_High;
    else            SDA_Low;    
    Data <<= 1;
    SCCB_Wait();
    SCL_High;      
    SCCB_Wait();
    SCL_Low;
    SCCB_Wait();
  }
  SDA_High;
  SDA_In;
  SCCB_Wait();
  
  SCL_High;
  SCCB_Wait();
  Ack = SDA_Data;
  SCL_Low;
  SCCB_Wait();
  return Ack;
}
/*************************************************************** 

* 
* �������ƣ�uint8 SCCB_ReadByte(void) 
* ����˵����SCCB��ȡ�ֽں��� 
* ����˵���� 
* �������أ���ȡ�ֽ� 
* �޸�ʱ�䣺2017��12��5�� 
* �� ע�� 
***************************************************************/ 
uint8 SCCB_ReadByte(void) 
{ 
  uint8 i; 
  uint8_t byte; 
  SCL_Out; 
  SDA_In; //ʹ������
  for( i=0; i<8; i++) 
  { 
    SCL_Low;
    SCCB_Wait(); 
    SCL_High;
    SCCB_Wait();
    byte = (byte<<1)|(SDA_Data & 1);
  }
  SCL_Low; 
  SDA_Out;
  SCCB_Wait(); 
  return byte; 
} 
/*************************************************************** 

* 
* �������ƣ�static void SCCB_Ack(void) 
* ����˵����IIC�лظ��ź� 
* ����˵���� 
* �������أ�void 
* �޸�ʱ�䣺2017��12��5�� 
* �� ע�� 
***************************************************************/ 
static void SCCB_Ack(void) 
{ 
  SCL_Out; 
  SDA_Out;
  SCL_Low;
  SDA_Low;
  SCCB_Wait();
  SCL_High;
  SCCB_Wait();
  SCL_Low;
  SCCB_Wait();
} 
/*************************************************************** 

* 
* �������ƣ�static void SCCB_NAck(void) 
* ����˵����IIC�޻ظ��ź� 
* ����˵���� 
* �������أ�void 
* �޸�ʱ�䣺2017��12��5�� 
* �� ע�� 
***************************************************************/ 
static void SCCB_NAck(void) 
{ 
  SCL_Out; 
  SDA_Out;
  SCL_Low;
  SCCB_Wait();
  SDA_High;
  SCCB_Wait();
  SCL_High;
  SCCB_Wait();
  SCL_Low;
  SCCB_Wait();
} 

/*************************************************************************
* �����������ܿƼ� KV58���ܳ�ĸ��           
*
*  �������ƣ�void SCCB_RegWrite(uint8 Device,uint8 Address,uint16 Data)
*  ����˵�������豸д���� 
*  ����˵����Ҫ���͵��ֽ�
*  �������أ�Ӧ���ź�
*  �޸�ʱ�䣺2017��12��5��
*  ��    ע��
*************************************************************************/
void SCCB_RegWrite(uint8 Device,uint8 Address,uint16 Data)
{
  uint8 i;
  uint8 Ack;
  
  for( i=0; i<3; i++)
  {
    SCCB_Star();
    Ack = SCCB_SendByte(Device);
    if( Ack == 1 )
    {
      continue;
    }
    
    Ack = SCCB_SendByte(Address);
    if( Ack == 1 )
    {
      continue;
    }
    
    Ack = SCCB_SendByte((uint8)(Data>>8));
    Ack = SCCB_SendByte((uint8)Data);
    if( Ack == 1 )
    {
      continue;
    }
    
    SCCB_Stop();
    if( Ack == 0 ) break;
  }
}
/*************************************************************** 

* 
* �������ƣ�uint8_t SCB_RegRead(uint8_t Device,uint8_t Address,uint16_t *Data) 
* ����˵������ȡ���� 
* ����˵���� 
* �������أ�void 
* �޸�ʱ�䣺2017��12��5�� 
* �� ע�� 
***************************************************************/ 
uint8_t SCCB_RegRead(uint8_t Device,uint8_t Address,uint16_t *Data) 
{   
  uint8 Ack = 0;
  Device = Device<<1;
  SCCB_Star();
  Ack += SCCB_SendByte(Device);
  
  Ack += SCCB_SendByte(Address);
  
  SCCB_Star();
  Ack += SCCB_SendByte(Device + 1);
  
  *Data = SCCB_ReadByte();
  SCCB_Ack();
  *Data = *Data<<8;
  
  *Data += SCCB_ReadByte();
  SCCB_NAck();
  
  SCCB_Stop();
  
  return  Ack;
} 
/***************************************************************  
* 
* �������ƣ�int SCCB_Probe(uint8_t chipAddr) 
* ����˵������ѯ�õ�ַ���豸�Ƿ���� 
* ����˵���� 
* �������أ�void 
* �޸�ʱ�䣺2017��12��5�� 
* �� ע�� 
***************************************************************/ 
int SCCB_Probe(uint8_t chipAddr) 
{ 
  uint8_t err;
  err = 0;
  chipAddr <<= 1;
  
  SCCB_Star();
  err = SCCB_SendByte(chipAddr);
  SCCB_Stop();
  
  return err;
}
/***************************************************************
* 
* �������ƣ�SendPicture 
* ����˵��������ͼ����λ�� ����ͬ����λ��ע���޸Ķ�Ӧ�����ݽ���Э��
* ����˵���� 
* �������أ�void 
* �޸�ʱ�䣺2018��3��27�� 
* �� ע�� 
***************************************************************/ 
void UARTSendPicture2(uint8_t tmImage[CAMERA_H][CAMERA_W]) 
{ 
  int i = 0, j = 0; 
  UART_Put_Char(UART_4,0x01); //����֡ͷ��־ WindowsFormsApplication1.exe
  UART_Put_Char(UART_4,0xFE); //����֡ͷ��־ WindowsFormsApplication1.exe
  for(i=0;i < CAMERA_H; i++) 
  { 
    for(j=0;j<CAMERA_H;j++) 
    { 
      //    if(tmImage[i][j]==0xff) 
      //    { 
      //      tmImage[i][j]=0xfe; //��ֹ���ͱ�־λ 
      //    } 
      UART_Put_Char(UART_4,tmImage[i][j]); 
    } 
  }
  UART_Put_Char(UART_4,0xFE); //����֡β��־ 
  UART_Put_Char(UART_4,0x01); //����֡β��־ 
} 

void UARTSendPicture(uint8_t tmImage[CAMERA_H][CAMERA_W]) 
{ 
  int i = 0, j = 0; 
  UART_Put_Char(UART_4,0xFF); //����֡ͷ��־ DEMOK��λ��  
  for(i=0;i < CAMERA_H; i++) 
  { 
    for(j=0;j <CAMERA_W;j++) 
    { 
      if(tmImage[i][j]==0xFF) 
      { 
        tmImage[i][j]=0xFE; //��ֹ���ͱ�־λ 
      } 
      UART_Put_Char(UART_4,tmImage[i][j]); 
    } 
  }
} 
/*
void SendPicture(void)
{
int i = 0, j = 0;
UART_Put_Char(UART_4,0xff);//����֡ͷ��־
for(i=0;i<Frame_Height;i++)      //���
{
for(j=0;j<Frame_Width;j++)    
{
if(Image_Data[i][j]==0xff)
{
Image_Data[i][j]=0xfe;//��ֹ���ͱ�־λ
      }
UART_Put_Char(UART_4,Image_Data[i][j]);
    }
  }
}
*/

/*************************************************************** 
* 
* �������ƣ�uint8_t GetOSTU(uint8_t tmImage[CAMERA_H][CAMERA_W]) 
* ����˵��������ֵ��С 
* ����˵���� 
* �������أ���ֵ��С 
* �޸�ʱ�䣺2018��3��27�� 
* �� ע�� 
�ο���https://blog.csdn.net/zyzhangyue/article/details/45841255
https://www.cnblogs.com/moon1992/p/5092726.html
https://www.cnblogs.com/zhonghuasong/p/7250540.html     
Ostu������������������ͨ��ͳ������ͼ���ֱ��ͼ������ʵ��ȫ����ֵT���Զ�ѡȡ�����㷨����Ϊ��
1) �ȼ���ͼ���ֱ��ͼ������ͼ�����е����ص㰴��0~255��256��bin��ͳ������ÿ��bin�����ص�����
2) ��һ��ֱ��ͼ��Ҳ����ÿ��bin�����ص����������ܵ����ص�
3) i��ʾ�������ֵ��Ҳ��һ���Ҷȼ�����0��ʼ����
4) ͨ����һ����ֱ��ͼ��ͳ��0~i �Ҷȼ�������(��������ֵ�ڴ˷�Χ�����ؽ���ǰ������) ��ռ����ͼ��ı���w0����ͳ��ǰ�����ص�ƽ���Ҷ�u0��ͳ��i~255�Ҷȼ�������(��������ֵ�ڴ˷�Χ�����ؽ�����������) ��ռ����ͼ��ı���w1����ͳ�Ʊ������ص�ƽ���Ҷ�u1��
5) ����ǰ�����غͱ������صķ��� g = w0*w1*(u0-u1) (u0-u1)
6) i++��ת��4)��ֱ��iΪ256ʱ��������
7�������g��Ӧ��iֵ��Ϊͼ���ȫ����ֵ
ȱ��:OSTU�㷨�ڴ������ղ����ȵ�ͼ���ʱ��Ч�������Բ��ã���Ϊ���õ���ȫ��������Ϣ��
***************************************************************/ 
uint8_t GetOSTU(uint8_t tmImage[CAMERA_H][CAMERA_W]) 
{ 
  int16_t i,j; 
  uint32_t Amount = 0; 
  uint32_t PixelBack = 0; 
  uint32_t PixelIntegralBack = 0; 
  uint32_t PixelIntegral = 0; 
  int32_t PixelIntegralFore = 0; 
  int32_t PixelFore = 0; 
  double OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // ��䷽��; 
  int16_t MinValue, MaxValue; 
  uint8_t Threshold = 0;
  uint8_t HistoGram[256];              //  
  
  for (j = 0; j < 256; j++)  HistoGram[j] = 0; //��ʼ���Ҷ�ֱ��ͼ 
  
  for (j = 0; j < CAMERA_H; j++) 
  { 
    for (i = 0; i < CAMERA_W; i++) 
    { 
      HistoGram[tmImage[j][i]]++; //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
    } 
  } 
  
  for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++) ;        //��ȡ��С�Ҷȵ�ֵ
  for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--) ; //��ȡ���Ҷȵ�ֵ
  
  if (MaxValue == MinValue)     return MaxValue;         // ͼ����ֻ��һ����ɫ    
  if (MinValue + 1 == MaxValue)  return MinValue;        // ͼ����ֻ�ж�����ɫ
  
  for (j = MinValue; j <= MaxValue; j++)    Amount += HistoGram[j];        //  ��������
  
  PixelIntegral = 0;
  for (j = MinValue; j <= MaxValue; j++)
  {
    PixelIntegral += HistoGram[j] * j;//�Ҷ�ֵ����
  }
  SigmaB = -1;
  for (j = MinValue; j < MaxValue; j++)
  {
    PixelBack = PixelBack + HistoGram[j];    //ǰ�����ص���
    PixelFore = Amount - PixelBack;         //�������ص���
    OmegaBack = (double)PixelBack / Amount;//ǰ�����ذٷֱ�
    OmegaFore = (double)PixelFore / Amount;//�������ذٷֱ�
    PixelIntegralBack += HistoGram[j] * j;  //ǰ���Ҷ�ֵ
    PixelIntegralFore = PixelIntegral - PixelIntegralBack;//�����Ҷ�ֵ
    MicroBack = (double)PixelIntegralBack / PixelBack;   //ǰ���ҶȰٷֱ�
    MicroFore = (double)PixelIntegralFore / PixelFore;   //�����ҶȰٷֱ�
    Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);//������䷽��
    if (Sigma > SigmaB)                    //����������䷽��g //�ҳ������䷽���Լ���Ӧ����ֵ
    {
      SigmaB = Sigma;
      Threshold = j;
    }
  }
  return Threshold;                        //���������ֵ;
} 
/*************************************************************** 
* 
* �������ƣ�void BinaryImage(uint8_t tmImage[CAMERA_H][CAMERA_W]) 
* ����˵����ͼ�����ݶ�ֵ�� 
* ����˵���� 
* �������أ�void 
* �޸�ʱ�䣺2018��3��27�� 
* �� ע�� 
***************************************************************/ 
void BinaryImage(uint8_t tmImage[CAMERA_H][CAMERA_W],uint8_t ThresholdV) 
{ 
  int i = 0, j = 0; 
  for(i = 0;i < CAMERA_H;i++) 
  { 
    for(j = 0; j< CAMERA_W;j++) 
    { 
      if(tmImage[i][j] >= ThresholdV) 
      { 
        tmImage[i][j] = 0xFE;
      } 
      else 
      { 
        tmImage[i][j] = 0X00;
      } 
    } 
  } 
} 

