#include <msp430.h> 

void initializeMCU(void){
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    //端子設定
    P1SEL &= ~(BIT0 + BIT6 + BIT3); //3系統の端子をIOに指定
    P1DIR |= BIT0 + BIT6;           //2系統を出力端子に指定
    P1DIR &= ~BIT3;                 //1系統を入力端子に指定

    P1REN |= BIT3;                  //１系統のみPullup,Pulldown有効化
    P1OUT |= BIT3;                  //Pullupに指定

    //P1.3のGPIO割り込み設定
    P1IES |= BIT3;                  //Edge High->Low検出に設定
    P1IE |= BIT3;                   //割り込み許可

}

//GPIO割り込みイベント関数
#pragma vector = PORT1_VECTOR
__interrupt void interruputPort1Test(void)
{
    P1OUT ^= BIT0 + BIT6;   //2系統の出力を反転させる
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
//	    //ボタン押下判定
//	    if ((P1IN & BIT3) == 0){
//            //P1.3が押された時の処理
//            P1OUT &= ~BIT0;     //P1.0消灯
//            P1OUT |= BIT6;      //P1.6点灯
//        }else{
//            P1OUT &= ~BIT6;     //P1.6消灯
//            P1OUT |= BIT0;      //P1.0点灯
//        }
//	}
}




