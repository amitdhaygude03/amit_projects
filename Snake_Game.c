#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define WIDTH 40
#define HEIGHT 20
#define SNAKE_MAX_LENGTH 100
#define DELAY 100000

typedef struct {
    int x, y;
} Position;

Position snake[SNAKE_MAX_LENGTH];
int snake_length = 3;
Position food;
int direction = 'd';

void initialize_game() {
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    timeout(100);
    srand(time(NULL));

    for (int i = 0; i < snake_length; i++) {
        snake[i].x = WIDTH / 2 - i;
        snake[i].y = HEIGHT / 2;
    }
    food.x = rand() % (WIDTH - 2) + 1;
    food.y = rand() % (HEIGHT - 2) + 1;
}

void draw_game() {
    clear();
    for (int i = 0; i < WIDTH; i++) mvprintw(0, i, "#");
    for (int i = 0; i < WIDTH; i++) mvprintw(HEIGHT - 1, i, "#");
    for (int i = 0; i < HEIGHT; i++) mvprintw(i, 0, "#");
    for (int i = 0; i < HEIGHT; i++) mvprintw(i, WIDTH - 1, "#");

    mvprintw(food.y, food.x, "@");
    for (int i = 0; i < snake_length; i++) mvprintw(snake[i].y, snake[i].x, "O");

    refresh();
}

void update_snake() {
    Position new_head = snake[0];
    switch (direction) {
        case 'w': new_head.y--; break;
        case 's': new_head.y++; break;
        case 'a': new_head.x--; break;
        case 'd': new_head.x++; break;
    }

    if (new_head.x == 0 || new_head.x == WIDTH - 1 || new_head.y == 0 || new_head.y == HEIGHT - 1) {
        endwin();
        printf("Game Over!\n");
        exit(0);
    }

    for (int i = 0; i < snake_length; i++) {
        if (snake[i].x == new_head.x && snake[i].y == new_head.y) {
            endwin();
            printf("Game Over!\n");
            exit(0);
        }
    }

    for (int i = snake_length; i > 0; i--) {
        snake[i] = snake[i - 1];
    }
    snake[0] = new_head;

    if (new_head.x == food.x && new_head.y == food.y) {
        snake_length++;
        food.x = rand() % (WIDTH - 2) + 1;
        food.y = rand() % (HEIGHT - 2) + 1;
    }
}

int main() {
    initialize_game();
    while (1) {
        draw_game();
        int key = getch();
        if (key == 'w' || key == 's' || key == 'a' || key == 'd') direction = key;
        update_snake();
        usleep(DELAY);
    }
    endwin();
    return 0;
}
