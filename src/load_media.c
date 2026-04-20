#include "load_media.h"

bool load_media_sheet(SDL_Renderer *renderer, SDL_Texture **image, const char *file_path, int width, int height, SDL_FRect **src_rects)
{
    if (*image)
    {
        SDL_DestroyTexture(*image);
        *image = NULL;
    }

    if (*src_rects)
    {
        free(*src_rects);
        *src_rects = NULL;
    }

    *image = IMG_LoadTexture(renderer, file_path);
    if (!*image)
    {
        fprintf(stderr, "Error loading texture: %s\n", SDL_GetError());
        return false;
    }

    int max_rows = (*image)->h / height;
    int max_columns = (*image)->w / width;

    if (!SDL_SetTextureScaleMode(*image, SDL_SCALEMODE_NEAREST))
    {
        fprintf(stderr, "Erro setting texture scale mode: %s\n", SDL_GetError());
        return false;
    }

    *src_rects = calloc(1, sizeof(SDL_FRect) * max_rows * max_columns);
    if (*src_rects == NULL)
    {
        fprintf(stderr, "Error in callon of src_rects.\n");
        return false;
    }

    for (int row = 0; row < max_rows; row++)
    {
        for (int column = 0; column < max_columns; column++)
        {
            int index = row * max_columns + column;

            (*src_rects)[index].x = (float)(column * width);
            (*src_rects)[index].y = (float)(row * height);
            (*src_rects)[index].w = (float)width;
            (*src_rects)[index].h = (float)height;
        }
    }

    return true;
}
