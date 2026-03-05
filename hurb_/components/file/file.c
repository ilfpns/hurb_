#include "file.h"

static const char *TAG = "File";

// label: 0(쾌적), 1(습함), 2(환기/가스)
void file_w(all_data data, int label) {
    char *filename;

    if (label == 0) {
        filename = "normal.csv";
    } else if (label == 1) {
        filename = "humid.csv";
    } else if (label == 2) {
        filename = "ventilate.csv";
    } else {
        ESP_LOGE(TAG, "존재하지 않는 라벨링 지정");
        return;
    }

    FILE *fp = fopen(filename, "a");

    if (fp != NULL) {
        fprintf(fp, "%d,%d,%f,%d\n", data.H, data.T, data.rs, label);

        fclose(fp);
    } else {
        ESP_LOGE(TAG, "파일 열기 실패");
    }
}