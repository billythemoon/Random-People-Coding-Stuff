#include "commands.h"
#include "terminal/terminal.h"
#include "drivers/vga.h"

typedef struct {
    char *name;
    void (*func)(uint8_t color);
} Command;

static void cmd_help(uint8_t color);
static void cmd_hello(uint8_t color);
static void cmd_test(uint8_t color);

// The command table
static Command commands[] = {
    { "help",  cmd_help  },
    { "hello", cmd_hello },
    { "test",  cmd_test  },
};

static int num_commands = sizeof(commands) / sizeof(commands[0]);

// ---- Command Functions ----

static void cmd_help(uint8_t color) {
    printf("help   - show this message\n", color);
    printf("hello  - say hello\n", color);
    printf("test   - placeholder\n", color);
}

static void cmd_hello(uint8_t color) {
    printf("Hello, world!\n", color);
}

static void cmd_test(uint8_t color) {
    printf("Test command has run successfully\n", color);
}

// ---- dispatcher ----
static int streq(char *a, char *b) {
    while (*a && *b) {
        if (*a != *b) return 0;
        a++; b++;
    }
    return *a == *b;
}

void run_command(char *input, uint8_t color) {
    // Check the input against command table
    for (int i = 0; i < num_commands; i++) {
        if (streq(input, commands[i].name)) {
            commands[i].func(color);
            return;
        }
    }
    printf("Unknown command. Type 'help'.\n", color);
}
