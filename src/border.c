#include "border.h"
#include "load_media.h"

bool border_new(struct Border **border, SDL_Renderer *renderer, unsigned rows, unsigned columns)
{
    *border = calloc(1, sizeof(struct Border));

    if (*border == NULL)
    {
        fprintf(stderr, "Error in Calloc of New Border.\n");
        return false;
    }

    struct Border *b = *border;

    b->renderer = renderer;
    b->rows = rows;
    b->columns = columns;

    b->left_offset = BORDER_LEFT * 2;
    b->piece_width = PIECE_SIZE * 2;
    b->piece_height = BORDER_HEIGHT * 2;

    if (!load_media_sheet(
            b->renderer, &b->image, "images/borders.png", PIECE_SIZE, BORDER_HEIGHT, &b->src_rect))
    {
        return false;
    }

    return true;
}

void border_free(struct Border **border)
{
    if (!border)
    {
        struct Border *b = *border;

        if (b->src_rect)
        {
            free(b->src_rect);
            b->src_rect = NULL;
        }

        if (b->image)
        {
            SDL_DestroyTexture(b->image);
            b->image = NULL;
        }

        b->renderer = NULL;

        free(b);
        b = NULL;
        *border = NULL;

        printf("Free Border.\n");
    }
}

void border_draw(const struct Border *b)
{
    SDL_FRect dest_rect = {0, 0, b->piece_width, b->piece_height};
    dest_rect.x = -b->left_offset;
    SDL_RenderTexture(b->renderer, b->image, &b->src_rect[0], &dest_rect);
}
