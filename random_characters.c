#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define REGULAR_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"

char* generate();

char* chars;
int counter = 0;

int length = -1;
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
    for (size_t i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--h") == 0 || strcmp(argv[i], "-help") == 0 || strcmp(argv[i], "--help") == 0)
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
            exit(EXIT_SUCCESS);
        }
    }

    bool next_arg_is_length = false;
    for (size_t i = 0; i < argc; i++)
    {
        if (next_arg_is_length)
            length = atoi(argv[i]);
        else if (strcmp(argv[i], "-length") == 0 || strcmp(argv[i], "--length") == 0)
            next_arg_is_length = true;
        else if (strcmp(argv[i], "-no-special-characters") == 0 || strcmp(argv[i], "--no-special-characters") == 0)
            no_special_characters = true;
        else if (strcmp(argv[i], "-no-exclamation-marks") == 0 || strcmp(argv[i], "--no-exclamation-marks") == 0)
            no_exclamation_marks = true;
        else if (strcmp(argv[i], "-no-number-signs") == 0 || strcmp(argv[i], "--no-number-signs") == 0)
            no_number_signs = true;
        else if (strcmp(argv[i], "-no-dollar-signs") == 0 || strcmp(argv[i], "--no-dollar-signs") == 0)
            no_dollar_signs = true;
        else if (strcmp(argv[i], "-no-percent-signs") == 0 || strcmp(argv[i], "--no-percent-signs") == 0)
            no_percent_signs = true;
        else if (strcmp(argv[i], "-no-ampersands") == 0 || strcmp(argv[i], "--no-ampersands") == 0)
            no_ampersands = true;
        else if (strcmp(argv[i], "-no-hyphens") == 0 || strcmp(argv[i], "--no-hyphens") == 0)
            no_hyphens = true;
        else if (strcmp(argv[i], "-no-periods") == 0 || strcmp(argv[i], "--no-periods") == 0)
            no_periods = true;
        else if (strcmp(argv[i], "-no-at-signs") == 0 || strcmp(argv[i], "--no-at-signs") == 0)
            no_at_signs = true;
        else if (strcmp(argv[i], "-no-underscores") == 0 || strcmp(argv[i], "--no-underscores") == 0)
            no_underscores = true;
    }

    if (length == -1)
    {
        length = 15;
    }
    else if (length < 4)
    {
        printf("Minimum length is 4\n");
        length = 4;
    }

    int chars_length = strlen(REGULAR_CHARS);
    if (!no_special_characters)
    {
        if (!no_exclamation_marks)
            chars_length++;
        if (!no_number_signs)
            chars_length++;
        if (!no_dollar_signs)
            chars_length++;
        if (!no_percent_signs)
            chars_length++;
        if (!no_ampersands)
            chars_length++;
        if (!no_hyphens)
            chars_length++;
        if (!no_periods)
            chars_length++;
        if (!no_at_signs)
            chars_length++;
        if (!no_underscores)
            chars_length++;
    }

    chars = malloc(sizeof(char) * chars_length);
    strcpy(chars, REGULAR_CHARS);

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
    printf("%s\n", generate());

    return EXIT_SUCCESS;
}

char* generate()
{
    while (true)
    {
        counter++;
        if (counter > 1000)
        {
            printf("Reached maximum number of generations\n");
            exit(EXIT_SUCCESS);
        }

        char* string = (char*) calloc(length, sizeof(char));
        for (int i = 0; i < length; i++)
            string[i] = chars[rand() % strlen(chars)];

        bool has_upper = false;
        bool has_lower = false;
        bool has_digit = false;
        bool has_special = false;
        for (int i = 0; i < length; i++)
        {
            if (isalpha(string[i]))
            {
                if (isupper(string[i]))
                    has_upper = true;
                else
                    has_lower = true;
            }
            else
            {
                if (isdigit(string[i]))
                    has_digit = true;
                else
                    has_special = true;
            }
        }

        if (has_upper && has_lower && has_digit && (has_special || no_special_characters))
        {
            return string;
        }
        else
        {
            printf("Regenerating...\n");
            free(string);
        }
    }
}
