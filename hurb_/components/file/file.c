#include "file.h"

void file_w(all_data data) {
    FILE *fp = fopen("ai_study_file.txt", "a");

    if (fp != NULL) {
        fprintf(fp, "%d,%d,%f\n", data.H, data.T, data.rs);

        fclose(fp);
    }
}