#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MAX_INPUTS 20
#define MAX_LEN 100
#define MAX_CHARSET 256
#define DEFAULT_OUTPUT "wordlist.txt"

const char *banner[] = {
"░█████████                                     ░██████                   ░██   ░██    ░██        \n" ,       
"░██     ░██                                   ░██   ░██                        ░██    ░██        \n",
"░██     ░██  ░██████    ░███████   ░███████  ░██         ░█████████████  ░██░████████ ░████████  \n",
"░█████████        ░██  ░██        ░██         ░████████  ░██   ░██   ░██ ░██   ░██    ░██    ░██ \n",
"░██          ░███████   ░███████   ░███████          ░██ ░██   ░██   ░██ ░██   ░██    ░██    ░██ \n",
"░██         ░██   ░██         ░██        ░██  ░██   ░██  ░██   ░██   ░██ ░██   ░██    ░██    ░██ \n",
"░██          ░█████░██  ░███████   ░███████    ░██████   ░██   ░██   ░██ ░██    ░████ ░██    ░██ \n"
};

// Common password patterns and transformations
const char *common_endings[] = {"123", "!", "?", "@", "#", "$", "1", "01", "2023", "2024", "2025", "00"};
const char *separators[] = {"", "_", "-", ".", "~"};

typedef struct {
    char *output_file;
    int quiet;
    int help;
    int no_banner;
    char **keywords;
    int keyword_count;
} config_t;

void print_usage(const char *program_name) {
    printf("Usage: %s [OPTIONS] [KEYWORDS...]\n\n", program_name);
    printf("Options:\n");
    printf("  -o FILE    Output file (default: %s)\n", DEFAULT_OUTPUT);
    printf("  -q         Quiet mode (minimal output)\n");
    printf("  -h         Show this help message\n");
    printf("  -n         No banner\n");
    printf("  -w WORD    Add keyword (can be used multiple times)\n\n");
    printf("Examples:\n");
    printf("  %s john 1990 soccer\n", program_name);
    printf("  %s -o mylist.txt -w alice -w 1985 -w cat\n", program_name);
    printf("  %s -q -o output.txt smith 2000\n", program_name);
    printf("\nIf no keywords are provided via arguments, interactive mode will be used.\n");
}

void to_uppercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void reverse_string(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

void leet_speak(char *str) {
    for (int i = 0; str[i]; i++) {
        switch (tolower(str[i])) {
            case 'a': str[i] = '@'; break;
            case 'e': str[i] = '3'; break;
            case 'i': str[i] = '1'; break;
            case 'o': str[i] = '0'; break;
            case 's': str[i] = '$'; break;
            case 't': str[i] = '7'; break;
        }
    }
}

int collect_keywords_interactive(char ***inputs) {
    int count = 0;
    *inputs = malloc(MAX_INPUTS * sizeof(char*));
    
    printf("\nEnter personal keywords (name, year, pet, team, etc.)\n");
    printf("Press ENTER on empty line to finish:\n\n");

    while (count < MAX_INPUTS) {
        char buffer[MAX_LEN];
        printf("[%d] > ", count + 1);
        fgets(buffer, MAX_LEN, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        if (strlen(buffer) == 0) break;
        
        (*inputs)[count] = strdup(buffer);
        count++;
    }
    
    return count;
}

int generate_wordlist(char **inputs, int count, const char *output_file, int quiet) {
    int total_generated = 0;

    if (count == 0) {
        if (!quiet) printf("No keywords provided!\n");
        return 1;
    }

    FILE *file = fopen(output_file, "w");
    if (file == NULL) {
        if (!quiet) printf("Error: Cannot create %s\n", output_file);
        return 1;
    }

    if (!quiet) {
        printf("\nGenerating wordlist with %d keywords...\n", count);
        printf("Keywords: ");
        for (int i = 0; i < count; i++) {
            printf("%s%s", inputs[i], (i < count-1) ? ", " : "");
        }
        printf("\n");
    }

    // Original words + variants
    for (int i = 0; i < count; i++) {
        char temp[MAX_LEN];
        
        // Original
        fprintf(file, "%s\n", inputs[i]);
        total_generated++;
        
        // Uppercase
        strcpy(temp, inputs[i]);
        to_uppercase(temp);
        if (strcmp(temp, inputs[i]) != 0) {
            fprintf(file, "%s\n", temp);
            total_generated++;
        }
        
        // Lowercase
        strcpy(temp, inputs[i]);
        to_lowercase(temp);
        if (strcmp(temp, inputs[i]) != 0) {
            fprintf(file, "%s\n", temp);
            total_generated++;
        }
        
        // Reversed
        strcpy(temp, inputs[i]);
        reverse_string(temp);
        if (strcmp(temp, inputs[i]) != 0) {
            fprintf(file, "%s\n", temp);
            total_generated++;
        }
        
        // Leet speak
        strcpy(temp, inputs[i]);
        leet_speak(temp);
        if (strcmp(temp, inputs[i]) != 0) {
            fprintf(file, "%s\n", temp);
            total_generated++;
        }
        
        // With common endings
        for (int e = 0; e < 12; e++) {
            fprintf(file, "%s%s\n", inputs[i], common_endings[e]);
            total_generated++;
        }
    }

    // 2-word combinations
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (i == j) continue;
            
            // With different separators
            for (int s = 0; s < 5; s++) {
                fprintf(file, "%s%s%s\n", inputs[i], separators[s], inputs[j]);
                total_generated++;
                
                // Add common endings to combinations
                for (int e = 0; e < 5; e++) {
                    fprintf(file, "%s%s%s%s\n", inputs[i], separators[s], inputs[j], common_endings[e]);
                    total_generated++;
                }
            }
        }
    }

    // 3-word combinations (limited to avoid explosion)
    if (count >= 3) {
        for (int i = 0; i < count && i < 5; i++) {
            for (int j = 0; j < count && j < 5; j++) {
                for (int k = 0; k < count && k < 5; k++) {
                    if (i == j || j == k || i == k) continue;
                    
                    fprintf(file, "%s%s%s\n", inputs[i], inputs[j], inputs[k]);
                    fprintf(file, "%s_%s_%s\n", inputs[i], inputs[j], inputs[k]);
                    total_generated += 2;
                }
            }
        }
    }

    fclose(file);
    
    if (!quiet) {
        printf("\n✓ Generated %d passwords in '%s'\n", total_generated, output_file);
    } else {
        printf("%d\n", total_generated);
    }
    
    return 0;
}

void parse_args(int argc, char *argv[], config_t *config) {
    // Initialize config
    config->output_file = strdup(DEFAULT_OUTPUT);
    config->quiet = 0;
    config->help = 0;
    config->no_banner = 0;
    config->keywords = malloc(MAX_INPUTS * sizeof(char*));
    config->keyword_count = 0;
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                free(config->output_file);
                config->output_file = strdup(argv[++i]);
            } else {
                printf("Error: -o requires a filename\n");
                config->help = 1;
            }
        }
        else if (strcmp(argv[i], "-q") == 0) {
            config->quiet = 1;
        }
        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            config->help = 1;
        }
        else if (strcmp(argv[i], "-n") == 0) {
            config->no_banner = 1;
        }
        else if (strcmp(argv[i], "-w") == 0) {
            if (i + 1 < argc && config->keyword_count < MAX_INPUTS) {
                config->keywords[config->keyword_count++] = strdup(argv[++i]);
            } else {
                printf("Error: -w requires a keyword\n");
                config->help = 1;
            }
        }
        else if (argv[i][0] == '-') {
            printf("Unknown option: %s\n", argv[i]);
            config->help = 1;
        }
        else {
            // It's a keyword
            if (config->keyword_count < MAX_INPUTS) {
                config->keywords[config->keyword_count++] = strdup(argv[i]);
            }
        }
    }
}

void cleanup_config(config_t *config) {
    if (config->output_file) free(config->output_file);
    if (config->keywords) {
        for (int i = 0; i < config->keyword_count; i++) {
            if (config->keywords[i]) free(config->keywords[i]);
        }
        free(config->keywords);
    }
}

int main(int argc, char *argv[]) {
    config_t config = {0};
    parse_args(argc, argv, &config);
    
    if (config.help) {
        print_usage(argv[0]);
        cleanup_config(&config);
        return 0;
    }
    
    // Print banner unless quiet or no-banner
    if (!config.quiet && !config.no_banner) {
        for(int i = 0; i < 7; i++) {
            printf("%s", banner[i]);
        }
        printf("\nPassSmith v1.0 - Target-Based Password Generator\n");
        printf("═══════════════════════════════════════════════════\n");
    }
    
    char **keywords = NULL;
    int keyword_count = config.keyword_count;
    
    if (config.keyword_count > 0) {
        // Use keywords from command line
        keywords = config.keywords;
    } else {
        // Interactive mode
        if (config.quiet) {
            fprintf(stderr, "Error: No keywords provided and quiet mode enabled\n");
            cleanup_config(&config);
            return 1;
        }
        keyword_count = collect_keywords_interactive(&keywords);
    }
    
    int result = generate_wordlist(keywords, keyword_count, config.output_file, config.quiet);
    
    // Cleanup
    if (config.keyword_count == 0 && keywords) {
        for (int i = 0; i < keyword_count; i++) {
            if (keywords[i]) free(keywords[i]);
        }
        free(keywords);
    }
    
    cleanup_config(&config);
    return result;
}

