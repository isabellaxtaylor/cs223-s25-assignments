#include <stdio.h>
#include <stdlib.h>

struct meta_data {
    float version;
    unsigned int year;
    unsigned int length;
};

int main(int argc, char* argv[]) {
    FILE* fp = fopen(argv[1], "rb");

    char comment[128];
    if (!fgets(comment, sizeof(comment), fp)) {
        fprintf(stderr, "Error reading comment line\n");
        fclose(fp);
        return 1;
    }
    printf("Comment: %s", comment);

    struct meta_data meta;
    if (fread(&meta, sizeof(struct meta_data), 1, fp) != 1) {
        fprintf(stderr, "Error reading meta data\n");
        fclose(fp);
        return 1;
    }

    printf("Version: %.2f\n", meta.version);
    printf("Year: %d\n", meta.year);
    printf("Length: %d\n", meta.length);

    char* message = malloc(meta.length + 1);
    if (!message) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(fp);
        return 1;
    }

    if (fread(message, 1, meta.length + 1, fp) != meta.length + 1) {
        fprintf(stderr, "Error reading message data\n");
        free(message);
        fclose(fp);
        return 1;
    }

    printf("Message: %s\n", message);

    free(message);
    fclose(fp);
    return 0;
}
