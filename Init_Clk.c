#include <msp430g2553.h>

/*DCOCTL �Ĵ���*/
/********************************************************************************
* bit7 bit6 bit5 bit4 bit3 bit2 bit1 bit0
* DCO.2 CCO.1 DCO.0 MOD.4 MOD.3 MOD.2 MOD.1 MOD.0
* DCO.0--DCO.2����8��Ƶ��֮һ���ɷֶε���DCOCLKƵ�ʣ���������Ƶ�����10%��
* ��Ƶ����ע��ֱ���������ĵ������塣
* MOD.O--MOD.4������32��DCO�����в����fdco+l���ڸ������������µ�DCO����
* ��ΪfDco���ڣ������л�DCO��DCO+1ѡ�������Ƶ�ʡ����DCO����Ϊ7����ʾ��
* ��ѡ��������ʣ���ʱ��������MOD.O-MOD.4����Ƶ�ʵ�����
* ********************************************************************************/
/*BCSCTL1 �Ĵ���*/
/**********************************************************************************
* bit7 bit6 bit5 bit4 bit3 bit2 bit1 bit0
* XT2OFF XTS DIVA.1 DIVA.0 XT5V Rse1.2 Rse1.1 Rse1.0
*XT2OFF���� XT2 �����Ŀ�����رա�
*XT2OFF=0��XT2����������
*XT2OFF=1��XT2�������ر�(Ĭ��XT2�ر�)��
*XTS���� LFXTl ����ģ�䣬ѡ������ʵ�ʾ����������������
*XTS=0��LFXTl�����ڵ�Ƶģʽ (Ĭ�ϵ�Ƶģʽ)��
*XTS=1��LFXTl�����ڸ�Ƶģʽ(������������Ӧ��Ƶʱ��Դ)��
*DIVA.0��DIVA.l����ACLK��Ƶ��
*0 ����Ƶ��Ĭ�ϲ���Ƶ����
*1 2��Ƶ��
*2 4��Ƶ��
*3 8��Ƶ��
*XT5V��λ����Ϊ0��
*Rse1.0��Rsel.l��Rse1.2��λ����ĳ���ڲ������Ծ������Ƶ�ʡ�
*Rse1=0��ѡ����͵�Ƶ�ʣ�
*Rse1=7��ѡ����͵ı��Ƶ�ʣ�
***********************************************************************************/
/*BCSCTL2 �Ĵ���*/
/***********************************************************************************
* bit7 bit6 bit5 bit4 bit3 bit2 bit1 bit0
*SELM.1 SELM.0 DIVM.1 DIVM.0 SELS DIVS.1 DIVS.0 DCOR
*SELM.1��SELM.0ѡ�� MCLK ʱ��Դ��
*0 ʱ��ԴΪ DCOLCK��Ĭ��ʱ��Դ����
*1 ʱ��ԴΪDCOCLK ;
*2 ʱ��ԴΪLFXTlCLK��
*3 ʱ��ԴΪ LFXT1CLK ��
*DIVM.1��DlVM.0ѡ�� MCLK ��Ƶ��
*0 1��Ƶ��Ĭ��MCLK=DCOCLK����
*1 2��Ƶ��
*2 4��Ƶ��
*3 8��Ƶ��
*DIVS.1��DIVS.0ѡ�� SMCLK ��Ƶ��
*0 1��Ƶ��Ĭ�� SMCLK=MCLK)��
*1 2��Ƶ��
*2 4��Ƶ��
*3 8��Ƶ��
************************************************************************************/
/*BCSCTL3 �Ĵ���*/
/************************************************************************************
* bit7 bit6 bit5 bit4 bit3 bit2 bit1 bit0
* XT2S1 XT2S0 LFXT1S1 LFXT1S0 XCAP1 XCAP0 XT2OF LFXT1OF
* XT2S1��XT2S0��2553��֧�֣�
* LFXT1S1��LFXT1S0ѡ��LFXT1�ķ�Χ��
* XCAP1��XCAP0ѡ��LFXT1��ƥ�����
* 00 1pf
* 01 6pf
* 10 10pf
* 11 12.5pf
************************************************************************************/


/************************************************************************
* ������ : DcoClkSet
* �������� : ��ʱ��DCOCLK��������
* �����β� : ������β�Ϊx��y����ֵ�ο�2553datsheet��28ҳ��DCOƵ�ʱ�
* ��������ֵ : ��
************************************************************************/
void DcoClkSet(unsigned char x,unsigned char y) // msp430g2553datasheet P30
{
  DCOCTL &=~( 0xFF);
  BCSCTL1 &=~( 0xFF);
  unsigned char temp=(x<<4)+y;
  switch(temp){
  case 0x00: {
    DCOCTL &=~( DCO0 + DCO1 + DCO2);
    BCSCTL1 &=~( RSEL0 + RSEL1 + RSEL2 + RSEL3);
    break;
  }
  case 0x03: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 &=~( RSEL0 + RSEL1 + RSEL2 + RSEL3);
    break;
  }
  case 0x13: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 |= ( RSEL0 );
    break;
  }
  case 0x23: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 |= ( RSEL1 );
    break;
  }
  case 0x33: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 |= ( RSEL0 + RSEL1 );
    break;
  }
  case 0x43: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 |= ( RSEL2);
    break;
  }
  case 0x53: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 |= ( RSEL0 + RSEL2 );
    break;
  }
  case 0x63: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 |= ( RSEL1 + RSEL2 );
    break;
  }
  case 0x73: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 |= ( RSEL0 + RSEL1 + RSEL2 );
    break;
  }
  case 0x83: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 |= ( RSEL3);
    break;
  }
  case 0x93: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 |= ( RSEL0+ RSEL3);
    break;
  }
  case 0xA3: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 |= ( RSEL1 + RSEL3);
    break;
  }
  case 0xB3: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 |= ( RSEL0 + RSEL1 + RSEL3);
    break;
  }
  case 0xC3: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 |= ( RSEL2 + RSEL3);
    break;
  }
  case 0xD3: {
    DCOCTL |= ( DCO0 + DCO1 );
    DCOCTL |= ( MOD4 + MOD3 + MOD2 + MOD1 + MOD0 );//΢��DCOCLK
    BCSCTL1 |= ( RSEL0 + RSEL2 + RSEL3);
    break;
  }
  case 0xE3: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 |= ( RSEL1 + RSEL2 + RSEL3);
    break;
  }
  case 0xF3: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 |= ( RSEL0 + RSEL1 + RSEL2 + RSEL3);
    break;
  }
  case 0xF7: {
    DCOCTL |= ( DCO0 + DCO1 + DCO2 );
    BCSCTL1 |= ( RSEL0 + RSEL1 + RSEL2 + RSEL3);
    break;
  }
  default: {
    DCOCTL |= ( DCO0 + DCO1 + DCO2 );
    BCSCTL1 |= ( RSEL0 + RSEL1 + RSEL2 + RSEL3);
  }
  }
}
/********************************************************************
* ������ : MClkSet
* �������� : ��ʱ��MCLK��������
* �����β� : ������β�ΪDiv����ʱ��ԴDCOCLK����Div��Ƶ
* ��������ֵ : ��
********************************************************************/
void MClkSet(unsigned char Div, unsigned char Clk_Source)
{
  unsigned char i;
  switch (Clk_Source)
  {
    case 'V':{
      break;
    }
    case 'L':{
      BCSCTL1 &= ~(XT2OFF);  
      do{
        IFG1 &= ~(OFIFG);                                                                                                                                                                                                                                                                                                                      
        for(i=0; i<100; i++){_NOP();}
      }while((IFG1 & OFIFG) != 0);
      BCSCTL1 |= XTS;
      BCSCTL2 |= SELM1 + SELM0;
      BCSCTL3 &= ~(XCAP0 + XCAP1);
      break;
    }
    case 'D':{
      BCSCTL2 &= ~(SELM1+SELM0); //select DCOCLK for SMCLK
      break;
    }
  }
  switch(Div){ //1��Ƶ
  case 0x01:{
    BCSCTL2 &=~(DIVM1 + DIVM0);
    break;
  }
  case 0x02:{ //2��Ƶ
    BCSCTL2 &=~(DIVM1 + DIVM0);
    BCSCTL2 |=DIVM0;
    break;
  }
  case 0x04:{ //4��Ƶ
    BCSCTL2 &=~(DIVM1 + DIVM0);
    BCSCTL2 |=DIVM1;
    break;
  }
  case 0x08:{ //8��Ƶ
    BCSCTL2 |=(DIVM1 + DIVM0);
    break;
  }
  default :{ //Ĭ�ϲ���Ƶ
    BCSCTL2 &=~(DIVM1 + DIVM0);
  } 
  }
}
/********************************************************************
* ������ : SMClkSet
* �������� : ��ʱ��MCLK��������
* �����β� : ������β�ΪDiv����ʱ��ԴDCOCLK����Div��Ƶ
* ��������ֵ : ��
********************************************************************/
void SMClkSet(unsigned char Div, unsigned char Clk_Source)
{
  unsigned char i;
  switch (Clk_Source)
  {
    case 'V':{
      break;
    }
    case 'L':{
      BCSCTL1 &= ~(XT2OFF);  
      do{
        IFG1 &= ~(OFIFG);                                                                                                                                                                                                                                                                                                                      
        for(i=0; i<100; i++){_NOP();}
      }while((IFG1 & OFIFG) != 0);
      BCSCTL1 |= XTS;
      BCSCTL2 |= SELS;
      BCSCTL3 &= ~(XCAP0 + XCAP1);
      break;
    }
    case 'D':{
      BCSCTL2 &= ~SELS; //select DCOCLK for SMCLK
      break;
    }
  }
  switch(Div)
  {
  case 0x01:{ //1��Ƶ
    BCSCTL2 &=~(DIVS_3);
    break;
  }
  case 0x02:{ //2��Ƶ
    BCSCTL2 &=~(DIVS_3);
    BCSCTL2 |=(DIVS_1);
    break;
  }
  case 0x04:{ //4��Ƶ
    BCSCTL2 &=~(DIVS_3);
    BCSCTL2 |=(DIVS_2);
    break;
  }
  case 0x08:{ //8��Ƶ
    BCSCTL2 |=(DIVS_3);
    break;
  }
  default :{ //Ĭ�ϲ���Ƶ
    BCSCTL2 &=~(DIVS_3);
  } 
  }
}
/********************************************************************
* ������ : AClkSet
* �������� : ��ʱ��MCLK��������
* �����β� : ������β�ΪDiv����ʱ��ԴLFXT1CLK����Div��Ƶ
* ��������ֵ : ��
********************************************************************/
void AClkSet(unsigned char Div)
{
  BCSCTL1 &=~(XTS); //low-frequency mode
  switch(Div){
    case 0x01:{ //1��Ƶ
      BCSCTL1 &=~(DIVA_3);
      break;
    }
    case 0x02:{ //2��Ƶ
      BCSCTL1 &=~(DIVA_3);
      BCSCTL1 |=(DIVA_1);
      break;
    }
    case 0x04:{ //4��Ƶ
      BCSCTL1 &=~(DIVA_3);
      BCSCTL1 |=(DIVA_2);
      break;
    }
    case 0x08:{ //8��Ƶ
      BCSCTL1 |=(DIVA_3);
      break;
    }
    default :{ //Ĭ�ϲ���Ƶ
      BCSCTL1 &=~(DIVA_3);
    } 
  }
  BCSCTL3 |= XT2S0 + LFXT1S0 + XCAP_3; //����ACLKƥ�����
}
/********************************************************************
* ���� : Init_Clk()
* ���� : MSP430ʱ��ϵͳ��ʼ������
* ���� : ��
* ����ֵ : ��
********************************************************************/
void Init_Clk() //ʱ��ϵͳ����
{
  DcoClkSet(13,3); //7.84MHz 2553datasheet ��28ҳ
  AClkSet(0x08); //8��ƵLFXT1CLK
  SMClkSet(0x01, 'D'); //1��ƵDCOCLK
  MClkSet(0x01, 'D'); //1��ƵDCOCLK
}
/************************ end of file *************************/
