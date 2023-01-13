#include <msp430.h> 

void initializeMCU(void){
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    //�[�q�ݒ�
    P1SEL &= ~(BIT0 + BIT6 + BIT3); //3�n���̒[�q��IO�Ɏw��
    P1DIR |= BIT0 + BIT6;           //2�n�����o�͒[�q�Ɏw��
    P1DIR &= ~BIT3;                 //1�n������͒[�q�Ɏw��

    P1REN |= BIT3;                  //�P�n���̂�Pullup,Pulldown�L����
    P1OUT |= BIT3;                  //Pullup�Ɏw��

    //P1.3��GPIO���荞�ݐݒ�
    P1IES |= BIT3;                  //Edge High->Low���o�ɐݒ�
    P1IE |= BIT3;                   //���荞�݋���

}

//GPIO���荞�݃C�x���g�֐�
#pragma vector = PORT1_VECTOR
__interrupt void interruputPort1Test(void)
{
    P1OUT ^= BIT0 + BIT6;   //2�n���̏o�͂𔽓]������
    P1IFG &= ~BIT3;         //clear flag.
}


/**
 * main.c
 */
void main(void)
{
     initializeMCU();
    P1OUT |= BIT0;
    P1OUT &= ~BIT6;

   _BIS_SR(GIE);
   _BIS_SR(SCG1 | SCG0 | CPUOFF | OSCOFF);     //goes into LPM4
   for (;;);

//   for (;;){
//       _BIS_SR(SCG1 | SCG0 | CPUOFF | OSCOFF);     //goes into LPM4
//   }

//	for (;;){
//	    //�{�^����������
//	    if ((P1IN & BIT3) == 0){
//            //P1.3�������ꂽ���̏���
//            P1OUT &= ~BIT0;     //P1.0����
//            P1OUT |= BIT6;      //P1.6�_��
//        }else{
//            P1OUT &= ~BIT6;     //P1.6����
//            P1OUT |= BIT0;      //P1.0�_��
//        }
//	}
}




