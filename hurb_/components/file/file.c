#include "file.h"

void file_w(QueueMold data) {
    FILE *fp = fopen("ai_study_file.txt", "a");

    if (fp != NULL) {
        fprintf(fp, "%d,%d\n", data.H, data.T);

        fclose(fp);
    }
}