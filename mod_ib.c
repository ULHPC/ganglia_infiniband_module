#include <gm_metric.h>
#include <stdio.h>

mmodule ib_module;

static int ib_metric_init ( apr_pool_t *p )
{
    int i;
    
    for (i = 0; ib_module.metrics_info[i].name != NULL; i++) {
        /* Initialize the metadata storage for each of the metrics and then
         *  store one or more key/value pairs.  The define MGROUPS defines
         *  the key for the grouping attribute. */
        MMETRIC_INIT_METADATA(&(ib_module.metrics_info[i]),p);
        MMETRIC_ADD_METADATA(&(ib_module.metrics_info[i]),MGROUP,"infiniband");
    }
    
    return 0;
}

static void ib_metric_cleanup ( void )
{
}

static g_val_t ib_metric_handler ( int metric_index )
{
    g_val_t val;
    unsigned int data;
    /* The metric_index corresponds to the order in which
     the metrics appear in the metric_info array
     */
    switch (metric_index) {
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
    if (data >= 2000000000){
	    if (system( "/usr/sbin/perfquery -R -a")) {
		}
	}
    val.uint32 = data;
    return val;
}

static Ganglia_25metric ib_metric_info[] = 
{
    {0, "ib_bytes_out",  10, GANGLIA_VALUE_UNSIGNED_INT,  "bytes",   "both", "%u", UDP_HEADER_SIZE+8,  "Infiniband number of bytes out"},
    {0, "ib_bytes_in",   10, GANGLIA_VALUE_UNSIGNED_INT,  "bytes",   "both", "%u", UDP_HEADER_SIZE+8,  "Infiniband number of bytes in"},
    {0, "ib_pkts_in",    10, GANGLIA_VALUE_UNSIGNED_INT,  "packets", "both", "%u", UDP_HEADER_SIZE+8,  "Infiniband packets in"},
    {0, "ib_pkts_out",   10, GANGLIA_VALUE_UNSIGNED_INT,  "packets", "both", "%u", UDP_HEADER_SIZE+8,  "Infiniband packets out"},
    {0, NULL}
};

mmodule ib_module =
{
    STD_MMODULE_STUFF,
    ib_metric_init,
    ib_metric_cleanup,
    ib_metric_info,
    ib_metric_handler,
};

