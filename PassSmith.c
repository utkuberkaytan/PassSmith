#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUTS 20
#define MAX_LEN 50

const char *banner[] = {
"░█████████                                     ░██████                   ░██   ░██    ░██        \n" ,       
"░██     ░██                                   ░██   ░██                        ░██    ░██        \n",
"░██     ░██  ░██████    ░███████   ░███████  ░██         ░█████████████  ░██░████████ ░████████  \n",
"░█████████        ░██  ░██        ░██         ░████████  ░██   ░██   ░██ ░██   ░██    ░██    ░██ \n",
"░██          ░███████   ░███████   ░███████          ░██ ░██   ░██   ░██ ░██   ░██    ░██    ░██ \n",
"░██         ░██   ░██         ░██        ░██  ░██   ░██  ░██   ░██   ░██ ░██   ░██    ░██    ░██ \n",
"░██          ░█████░██  ░███████   ░███████    ░██████   ░██   ░██   ░██ ░██    ░████ ░██    ░██ \n"
};
int target_based() {
    char *inputs[MAX_INPUTS];
    int count = 0;

    printf("\nEnter as many personal keywords as you like (e.g. name, year, team).\nFinish by entering an empty line:\n");

    while (count < MAX_INPUTS) {
        char buffer[MAX_LEN];
        printf("> ");
        fgets(buffer, MAX_LEN, stdin);

        // Yeni satır varsa kes
        buffer[strcspn(buffer, "\n")] = 0;

        if (strlen(buffer) == 0) break;

        inputs[count] = strdup(buffer); // malloc + kopyalama
        count++;
    }

    FILE *file = fopen("wordlist.txt", "w");
    if (file == NULL) {
        printf("Error: Cannot open wordlist.txt\n");
        return 1;
    }

    // Temel varyasyonlar:
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\n", inputs[i]);                // kendisi
        fprintf(file, "%s123\n", inputs[i]);             // sonuna 123
        fprintf(file, "%s!\n", inputs[i]);               // sonuna !
        fprintf(file, "%s?\n", inputs[i]);               // sonuna ?
        fprintf(file, "%s1\n", inputs[i]);               // sonuna 1
    }

    // 2’li kombinasyonlar
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (i == j) continue;

            fprintf(file, "%s%s\n", inputs[i], inputs[j]);
            fprintf(file, "%s_%s\n", inputs[i], inputs[j]);
            fprintf(file, "%s%s123\n", inputs[i], inputs[j]);
        }
    }

    // 3’lü kombinasyonlar
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            for (int k = 0; k < count; k++) {
                if (i == j || j == k || i == k) continue;

                fprintf(file, "%s%s%s\n", inputs[i], inputs[j], inputs[k]);
            }
        }
    }

    printf("\nGenerated %d base words. Check 'wordlist.txt'.\n", count);

    // Belleği temizle
    for (int i = 0; i < count; i++) {
        free(inputs[i]);
    }
    fclose(file);
    return 0;
}
int raw(){
    printf("Raw Activated");
}
int main(){
    for(int i=0; i < 7; i++){
        printf(banner[i]);
    }
    printf("1 - Target Based\n \n");
    printf("2 - Raw\n");
    int choice;
    printf("Select a mod to create wordlist > ");
    scanf("%d", &choice);


    if(choice==1){
        printf("\nYou have selected Target Based.");
        target_based();
    }
    else if(choice==2){
        printf("\nYou have selected Raw.");
        raw();
    }
    else{
        printf("\nInvalid option.");
    }
}