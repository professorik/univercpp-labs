#include<stdio.h>

#define _stars_num 120000

struct star {
    double ra, dec;
    float plx, mura, mudec, hpmag;
};

star Stars[_stars_num];

void skipLine(FILE *f) {
    while (!feof(f)) {
        if (fgetc(f) == '\n') { break; }
    }
}

void convertTxtToBin(const char *input, const char *output) {
    FILE *f = fopen(input, "r");
    if (!f) {
        printf("Error: cannot open the file\n");
        return;
    }
    int n = 0;
    while (!feof(f)) {
        if (fscanf(f, "%lf %lf %f %f %f %f",
                   &Stars[n].ra, &Stars[n].dec, &Stars[n].plx, &Stars[n].mura, &Stars[n].mudec, &Stars[n].hpmag) == 6) {
            if (++n % 10000 == 0)
                printf("load %d stars\r", n);
        } else { skipLine(f); }
    }
    printf("load %d objects\n", n);
    FILE *fw = fopen(output, "wb");
    fwrite(Stars, sizeof(star), n, fw);
    //fcloseall();
    fclose(f);
    fclose(fw);
}

void convertBinToTxt(const char *input, const char *output) {
    FILE *in = fopen(input, "rb");
    if (!in) {
        printf("Error: cannot open the file\n");
        return;
    }
    //it doesn't work (mb some lines are spoiled, n == 114825
    /*
    fseek(in, 0, SEEK_END);
    int n = ftell(in) / sizeof(star);
    fseek(in, 0, 0);
    fread(Stars2, sizeof(star), n, in);
    */
    FILE *out = fopen(output, "w");
    if (!out) {
        printf("Error: cannot open the file\n");
        return;
    }
    fprintf(out, "%s", "RA\tDEC\tPlx\tMuRA\tMuDE\tHpmag\n");
    int i;
    star temp;
    for (i = 0; !feof(in); ++i) {
        if (fread(&temp, sizeof(star), 1, in) == 1) {
            fprintf(out, "%4.8g\t%4.8g\t%4.8g\t%4.8g\t%4.8g\t%4.8g\n", temp.ra, temp.dec, temp.plx, temp.mura, temp.mudec, temp.hpmag);
            if (i % 10000 == 0)
                printf("load %d objects\r", i);
        }
    }
    printf("load %d objects\n", i-1);
    //fcloseall();
    fclose(in);
    fclose(out);
}

int main() {
    convertTxtToBin("HIP2.txt", "hip2.bin");
    //convertBinToTxt("hip2.bin", "hip2_res.txt");
    return 0;
}
