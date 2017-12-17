

#include "mbed.h"
#include "SDFileSystem.h"
#include "ILI9340_Driver.h"

Serial pc(USBTX, USBRX);                    // Use Serial interface
SDFileSystem sd(D11, D12, D13, D10, "sd");  // MOSI, MISO, SCK, CS
FILE *fp;                                   // File pointer declear

int main() {

    
    pc.baud(115200);

    // create the Analog object
    AnalogIn    myA1(A1);
    
   

    // set up variables

    long temperature;                      // For calucrate
                             
    while(1) {
        temperature = 0;
        for(int i=0;i<1000;i++){            // For averaging.
            unsigned int a, beta = 3975, units, tens;
    float temperature, resistance;

    a = myA1.read_u16(); /* Read analog value */

    /* Calculate the resistance of the thermistor from analog votage read. */
    resistance = (float) 10000.0 * ((65536.0 / a) - 1.0);

    /* Convert the resistance to temperature using Steinhart's Hart equation */
    temperature =(1/((log(resistance/10000.0)/beta) + (1.0/298.15)))-273.15;

    printf("temperature is %f\n", temperature);

    wait(1);
            
        
        
        
        
        // SD card logger
        fp = fopen("/sd/mylogger.txt", "a");            // File open for "a"ppend
        if (fp == NULL) {                               // Error!
            pc.printf("Unable to write the file\r\n");
        } else {
            pc.printf("%f \r\n",temperature);          // Append data to SD card.
            fprintf(fp, "%f \r\n",temperature);        // Serial monitor.
        }
        fclose(fp);                                     // Cloce file.
        pc.printf("File successfully written!\r\n");    // Serial monitor.

        
        wait(2);
       
        
    }
}
}
