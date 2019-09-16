/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�MK66FX1M0VLQ18���İ�
����    д��CHIUSIR
����    ע��
�������汾��V1.0
�������¡�2016��08��20��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
���������䡿chiusir@163.com
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include "include.h"
#include "PIT.h"
#include "magnet.h"

int spedleft;
int SeCovered=0;
int kzuo,kyou,left,left1,right,right1;
//-------------------------------------------------------------------------*
//������: pit_init
//��  ��: ��ʼ��PIT
//��  ��: pitn:ģ����PIT0��PIT1��PIT2��PIT3
//        cnt �ж�ʱ�䣬��λ1ms
//��  ��: ��
//��  ��: pit_init(PIT0,1000); PIT0�жϣ�1000ms����1s����PIT0_interrupt()һ��
//-------------------------------------------------------------------------*
void PIT_Init(PITn pitn, u32 cnt)
{
    //PIT �õ��� Bus Clock ����Ƶ��

    /* ����ʱ��*/
    SIM_SCGC6       |= SIM_SCGC6_PIT_MASK;                            //ʹ��PITʱ��

    /* PITģ����� PIT Module Control Register (PIT_MCR) */
    PIT_MCR         &= ~(PIT_MCR_MDIS_MASK | PIT_MCR_FRZ_MASK );      //ʹ��PIT��ʱ��ʱ�� ������ģʽ�¼�������

    /* ��ʱ������ֵ���� Timer Load Value Register (PIT_LDVALn) */
    PIT_LDVAL(pitn)  = cnt*bus_clk_M*1000;                            //��������ж�ʱ��

    //��ʱʱ�䵽�˺�TIF �� 1 ��д1��ʱ��ͻ���0
    PIT_Flag_Clear(pitn);                                             //���жϱ�־λ

    /* ��ʱ�����ƼĴ��� Timer Control Register (PIT_TCTRL0) */
    PIT_TCTRL(pitn) |= ( PIT_TCTRL_TEN_MASK | PIT_TCTRL_TIE_MASK );   //ʹ�� PITn��ʱ��,����PITn�ж�

    NVIC_EnableIRQ((IRQn_Type)(pitn + 48));			                                //���������ŵ�IRQ�ж�
}



//-------------------------------------------------------------------------*
//������: PIT0_interrupt
//��  ��: PIT�жϺ���
//��  ��: ��
//��  ��: ��
//��  ��: �ɳ�ʼ���������೤ʱ�����һ��
//-------------------------------------------------------------------------*
short speed=0;
/*
void PIT0_Interrupt()
{
  PIT_Flag_Clear(PIT0);       //���жϱ�־λ
 //�û������������
  LED_Ctrl(LED2, RVS);        //�жϷ�����LED��˸
  //speed=FTM_AB_Get(FTM2);     //������������󣬿��Ի�ȡ�ٶȣ�������ʾ����

}
*/

void PIT1_Interrupt()
{
  PIT_Flag_Clear(PIT1);       //���жϱ�־λ
// /*�û������������
  spedleft=FTM_AB_Get(FTM1);
  SeCovered+=spedleft;

}

void PIT2_Interrupt()
{
  PIT_Flag_Clear(PIT1);       //���жϱ�־λ
  /*�û������������*/
  
}

void PIT3_Interrupt()
{
  PIT_Flag_Clear(PIT3);//���жϱ�־λ
  /*�û������������*/
//  left=maglleft;
//  right=magrright;
//  kzuo=(left-left1)*100;
//  kyou=(right-right1)*100;
//  left1=left;
//  right1=right;
  
}
//������ʱ������ʱ
void pit_time_start(PITn pitn)
{
    //PIT �õ��� Bus Clock ����Ƶ��
    //������� = ����Ƶ�� * ʱ��

    SIM_SCGC6       |= SIM_SCGC6_PIT_MASK;                          //ʹ��PITʱ��

    PIT_MCR         &= ~(PIT_MCR_MDIS_MASK | PIT_MCR_FRZ_MASK );    //ʹ��PIT��ʱ��ʱ�� ������ģʽ�¼�������

    PIT_TCTRL(pitn) &= ~( PIT_TCTRL_TEN_MASK );                     //����PIT ���Ա����ü���ֵ��Ч

    PIT_LDVAL(pitn)  = ~0;                                          //��������ж�ʱ��

    PIT_Flag_Clear(pitn);                                           //���жϱ�־λ

    PIT_TCTRL(pitn) &= ~ PIT_TCTRL_TEN_MASK;                        //��ֹPITn��ʱ����������ռ���ֵ��
    PIT_TCTRL(pitn)  = ( 0
                         | PIT_TCTRL_TEN_MASK                        //ʹ�� PITn��ʱ��
                         //| PIT_TCTRL_TIE_MASK                      //��PITn�ж�
                       );
}

/*!
 *  @brief      ��ȡ PITn��ʱʱ��(��ʱʱ��ر� ��ʱ��)
 *  @param      PITn        ģ��ţ�PIT0~PIT3��
 *  @since      v5.0
 *  Sample usage:
                        uint32 time = pit_time_get(PIT0);                         //��ȡ PITn��ʱʱ��
                        if(time != ~0)       //û��ʱ
                        {
                            printf("\n��ʱʱ��Ϊ��%d us",time*1000/bus_clk_khz);
                        }
 */
uint32 pit_time_get(PITn pitn)
{
    uint32 val;

    val = (~0) - PIT_CVAL(pitn);

    if(PIT_TFLG(pitn)& PIT_TFLG_TIF_MASK)                           //�ж��Ƿ�ʱ�䳬ʱ
    {
        PIT_Flag_Clear(pitn);                                       //���жϱ�־λ
        PIT_TCTRL(pitn) &= ~ PIT_TCTRL_TEN_MASK;                    //��ֹPITn��ʱ����������ռ���ֵ��
        return ~0;
    }

    if(val == (~0))
    {
        val--;              //ȷ�� ������ ~0
    }
    return val;
}