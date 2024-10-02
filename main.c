/*
 * main.c
 * Include processing inputs, outputs and applying deep learning models
 */

#include "main.h"

void main(void){
    printf("start\n");
    /* stop watchdog timer */
     WDTCTL = WDTPW | WDTHOLD;

    /* initialize GPIO System */
    init_gpio();

    /* initialize the clock and baudrate */
    init_clock_system();

    /* output consists of 35 classes */
    outputLabels.numRows = OUTPUT_NUM_LABELS;
    outputLabels.numCols = LEA_RESERVED;   // one more column is reserved for LEA
    outputLabels.data = output_buffer;

    uint16_t i;
    for(i=0; i<INPUT_DATA_NUM; i++){
//        printf("i=%"PRId16"\n", i);
        /* GSC dataset consists of 32*32 spectrograms */
        inputFeatures.numRows = INPUT_NUM_ROWS;
        inputFeatures.numCols = INPUT_NUM_COLS;
        inputFeatures.data = input_buffer[i];


        /* apply model saved in neural_network_parameters.h on input */
        apply_model(&outputLabels, &inputFeatures);
        label = argmax(&outputLabels);
        printf("label=%"PRId16"\n", label);
    }
//    __no_operation();
    printf("finish\n");
    return 0;
}
