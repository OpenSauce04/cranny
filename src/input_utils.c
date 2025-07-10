#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define GETC_TIMEOUT 1 * 10 // Deciseconds

struct termios g_original_term_attrs;

static inline void set_term_attrs(struct termios term_attrs) {
    if (tcsetattr(STDIN_FILENO, TCSANOW, &term_attrs) == -1) {
        printf("ERROR: Failed to set terminal attributes\n");
        exit(1);
    }
}

void reset_termio(void) { set_term_attrs(g_original_term_attrs); }

void setup_termio(void) {
    struct termios term_attrs;
    if (tcgetattr(STDIN_FILENO, &term_attrs) == -1) {
        printf("ERROR: Failed to get terminal attributes\n");
        exit(1);
    }

    g_original_term_attrs = term_attrs;

    // Set terminal to cbreak mode and set stdin read timeout
    term_attrs.c_lflag &= ~(ICANON | ECHO);
    term_attrs.c_cc[VMIN] = 0;
    term_attrs.c_cc[VTIME] = GETC_TIMEOUT;

    set_term_attrs(term_attrs);
}
