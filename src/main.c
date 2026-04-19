#include "game.h"

int main(void)
{
    bool exit_status = EXIT_FAILURE;
    struct Game *game = NULL;

    if (!game_new(&game))
    {
        fprintf(stderr, "Failed to create game.\n");
        return exit_status;
    }

    if (!game_run(game))
    {
        fprintf(stderr, "The game loop terminated with an error.\n");
    }
    else
    {
        exit_status = EXIT_SUCCESS;
    }

    game_free(&game);
    return exit_status;
}
