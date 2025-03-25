#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct meta_data {
    float version;
    unsigned int year;
    unsigned int length;
};

int main(int argc, char* argv[]) {
    if (argc != 6) {
        fprintf(stderr, "usage: ./message_writer <filename> <version> <year> <message> <comment>\n");
        return 1;
    }
    const char* filename = argv[1];
    float version = atof(argv[2]);
    unsigned int year = atoi(argv[3]);
    const char* message = argv[4];
    const char* comment = argv[5];

    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    fprintf(fp, "%s\n", comment);

    struct meta_data meta;
    meta.version = version;
    meta.year = year;
    meta.length = strlen(message);

    fwrite(&meta, sizeof(struct meta_data), 1, fp);

    fwrite(message, 1, meta.length + 1, fp);

    fclose(fp);
    printf("Wrote message to %s\n", filename);
    return 0;
}
