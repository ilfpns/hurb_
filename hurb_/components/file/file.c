#include "file.h"

void file_w(QueueMold data) {
    FILE *fp = fopen("ai_study_file.txt", "a");
    int h_add = 0;
    int t_add = 0;

    if (fp != NULL) {
        if (data.H > 25) {
            switch (data.H) {
            case 26:
                h_add += 1;
                break;
            case 27:
                h_add += 2;
                break;
            case 28:
                h_add += 3;
                break;
            case 29:
                h_add += 4;
                break;
            default:
                h_add += 5;
                break;
            }
        }
        if (data.T > 36) {
            switch (t_add) {
            case 37:
                t_add += 1;
                break;
            case 38:
                t_add += 2;
                break;
            case 39:
                t_add += 3;
                break;
            case 40:
                t_add += 4;
                break;
            case 41:
                t_add += 5;
                break;
            case 42:
                t_add += 6;
                break;
            case 43:
                t_add += 7;
                break;
            default:
                t_add += 8;
                break;
            }
        }
        fprintf(fp, "H : %d / T : %d / h : %d / t : %d\n", data.H, data.T, h_add, t_add); 

        fclose(fp);
    }
}