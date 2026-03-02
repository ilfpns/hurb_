#include "file.h"

int file_w(QueueMold data) {
    FILE *fp = fopen("ai_study_file.txt", "a");

    if (fp != NULL) {
        fprintf(fp, "H : %d / T : %d\n", data.H, data.T); 

        fclose(fp);
    }

    return 0;
}