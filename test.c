#include <stdio.h>

int main(){
    unsigned int data;
    int i;
    for (i = 0; i<4; i++){
        
        /* The metric_index corresponds to the order in which
         the metrics appear in the metric_info array
         */
        switch (i) {
            case 0: 
            {
                FILE *fi;
                fi = fopen("/sys/class/infiniband/mlx4_0/ports/1/counters/port_xmit_data", "r");
                if (fi != NULL ) fscanf(fi, "%u", &data);
                fclose(fi);
            }
                break;
            case 1:  
            {
                FILE *fi;
                fi = fopen("/sys/class/infiniband/mlx4_0/ports/1/counters/port_rcv_data", "r");
                if (fi != NULL ) fscanf(fi, "%u", &data);
                fclose(fi);
            }
                break;
            case 2:
            {
                FILE *fi;
                fi = fopen("/sys/class/infiniband/mlx4_0/ports/1/counters/port_rcv_packets", "r");
                if (fi != NULL ) fscanf(fi, "%u", &data);
                fclose(fi);
            }
                break;
            case 3:
            {
                FILE *fi;
                fi = fopen("/sys/class/infiniband/mlx4_0/ports/1/counters/port_xmit_packets", "r");
                if (fi != NULL ) fscanf(fi, "%u", &data);
                fclose(fi);
            }
                break;
            default:    /* default case */
                data = 0;
                
        }
        printf("data = %u", data);
    }
    return 0;
}