#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

bool arg_compare(const char* a, const char* b);
char* generate(const char* chars);

size_t* length = NULL;
bool no_special_characters = false;
bool no_exclamation_marks = false;
bool no_number_signs = false;
bool no_dollar_signs = false;
bool no_percent_signs = false;
bool no_ampersands = false;
bool no_hyphens = false;
bool no_periods = false;
bool no_at_signs = false;
bool no_underscores = false;

int main(int argc, char* argv[])
{
    for (int i = 0; i < argc; i++)
    {
        if (arg_compare(argv[i], "h") || arg_compare(argv[i], "help"))
        {
            printf(
                "Usage: <executable> [options]\n"
                "Options:\n"
                "   h, help                 Display this info\n"
                "   length <number>         Generate <length> number of characters\n"
                "   no-special-characters   Prevent generation of non-alphanumeric characters\n"
                "Options to prevent specific special characters from being generated:\n"
                "   no-exclamation-marks   !\n"
                "   no-number-signs        #\n"
                "   no-dollar-signs        $\n"
                "   no-percent-signs       %%\n"
                "   no-ampersands          &\n"
                "   no-hyphens             -\n"
                "   no-periods             .\n"
                "   no-at-signs            @\n"
                "   no-underscores         _\n"
                "Note: All options must be preceded by - or --\n"
            );
            return EXIT_SUCCESS;
        }
    }

    bool next_arg_is_length = false;
    for (int i = 0; i < argc; i++)
    {
        if (next_arg_is_length)
        {
            length = (size_t*) malloc(sizeof(size_t));
            *length = atoll(argv[i]);
            next_arg_is_length = false;
        }
        else if (arg_compare(argv[i], "length"))
            next_arg_is_length = true;
        else if (arg_compare(argv[i], "no-special-characters"))
            no_special_characters = true;
        else if (arg_compare(argv[i], "no-exclamation-marks"))
            no_exclamation_marks = true;
        else if (arg_compare(argv[i], "no-number-signs"))
            no_number_signs = true;
        else if (arg_compare(argv[i], "no-dollar-signs"))
            no_dollar_signs = true;
        else if (arg_compare(argv[i], "no-percent-signs"))
            no_percent_signs = true;
        else if (arg_compare(argv[i], "no-ampersands"))
            no_ampersands = true;
        else if (arg_compare(argv[i], "no-hyphens"))
            no_hyphens = true;
        else if (arg_compare(argv[i], "no-periods"))
            no_periods = true;
        else if (arg_compare(argv[i], "no-at-signs"))
            no_at_signs = true;
        else if (arg_compare(argv[i], "no-underscores"))
            no_underscores = true;
    }

    if (!length)
    {
        length = (size_t*) malloc(sizeof(size_t));
        *length = 15;
    }
    else if (*length < 4)
    {
        printf("Minimum length is 4\n");
        *length = 4;
    }
    *length += 1; // Add space for null terminator

    char* chars = malloc(sizeof(char) * 72);
    strcpy(chars, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");

    if (!no_special_characters)
    {
        if (!no_exclamation_marks)
            strcat(chars, "!");
        if (!no_number_signs)
            strcat(chars, "#");
        if (!no_dollar_signs)
            strcat(chars, "$");
        if (!no_percent_signs)
            strcat(chars, "%");
        if (!no_ampersands)
            strcat(chars, "&");
        if (!no_hyphens)
            strcat(chars, "-");
        if (!no_periods)
            strcat(chars, ".");
        if (!no_at_signs)
            strcat(chars, "@");
        if (!no_underscores)
            strcat(chars, "_");
    }

    srand(time(NULL));

    printf("Generating...\n");
    char* generated_chars = generate(chars);
    printf("%s\n", generated_chars);

    free(length);
    free(generated_chars);

    return EXIT_SUCCESS;
}

char* generate(const char* chars)
{
    for (int i = 0; i < 1000; i++)
    {
        char* string = (char*) calloc(*length, sizeof(char));
        for (int i = 0; i < *length; i++)
            string[i] = chars[rand() % strlen(chars)];

        bool has_upper = false;
        bool has_lower = false;
        bool has_digit = false;
        bool has_special = false;
        for (size_t j = 0; j < *length; j++)
        {
            if (isalpha(string[j]))
            {
                if (isupper(string[j]))
                    has_upper = true;
                else
                    has_lower = true;
            }
            else
            {
                if (isdigit(string[j]))
                    has_digit = true;
                else
                    has_special = true;
            }

            if (has_upper && has_lower && has_digit && (has_special || no_special_characters))
                return string; 
        }

        free(string);
        printf("Regenerating...\n");
    }

    printf("Reached maximum number of generations\n");
    exit(EXIT_SUCCESS);
}

bool arg_compare(const char* a, const char* b)
{
    char* arg = (char*) malloc(sizeof(char) * (strlen(b) + 2));
    strcpy(arg, "-");
    strcat(arg, b);
    if (strcmp(a, arg) == 0)
    {
        free(arg);
        return true;
    }

    arg = (char*) realloc(arg, sizeof(char) * (strlen(b) + 3));
    strcpy(arg, "--");
    strcat(arg, b);
    if (strcmp(a, arg) == 0)
    {
        free(arg);
        return true;
    }

    free(arg);
    return false;
}
