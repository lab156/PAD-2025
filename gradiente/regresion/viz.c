#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "reg_utils.h"

void fill_buckets(double r, int num_buckets, int *buckets) {
        if ( r < -3.0)                    { buckets[0]++;
        } else if (r >= -3.0 && r < -2.0) { buckets[1]++;
        } else if (r >= -2.0 && r < -1.0) { buckets[2]++;
        } else if (r >= -1.0 && r <  0.0) { buckets[3]++;
        } else if (r >=  0.0 && r <  1.0) { buckets[4]++;
        } else if (r >=  1.0 && r <  2.0) { buckets[5]++;
        } else if (r >=  2.0 && r <  3.0) { buckets[6]++;
        } else                            { buckets[7]++;
        }

}

int main() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    int num_sample = 100000;

    printf("Terminal width: %d\n", w.ws_col);

    /* double data_array[100]; */
    int num_buckets = 8;
    int buckets[num_buckets];
    for (int i=0; i<num_buckets; i++) {buckets[i] = 0;};

    //Generate the random numbers with normal(0,1) distribution
    // and fill buckets
    for (int i=0; i<num_sample; i++) {
        fill_buckets(random_normal(0, 1), 7, buckets);
    }



    int bucket_length;
    for (int i=0; i<num_buckets; i++) {
       bucket_length = (buckets[i])/(4*w.ws_col); 
       printf("%0*d\n", bucket_length, 0);
    }

    return 0;
}
