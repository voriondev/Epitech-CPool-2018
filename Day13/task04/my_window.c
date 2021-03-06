/*
** EPITECH PROJECT, 2018
** MY WINDOW
** File description:
** Draw a window
*/

#include <stdlib.h>
#include <structs.h>
#include <draw_file.h>
#include <SFML/Graphics.h>

t_framebuffer *framebuffer_create(unsigned int width, unsigned int height)
{
    t_framebuffer *array = malloc(sizeof(t_framebuffer));
    array->width = width;
    array->height = height;
    array->pixels = malloc(width * height * 4);
    return (array);
}

window_t *init_frame(int width, int height, int bits, char *file)
{
    window_t *current = malloc(sizeof(window_t));
    sfVideoMode mode = {width, height, bits};
    current->mode = mode;
    char *s = file;
    current->window = sfRenderWindow_create(current->mode, s, sfClose, NULL);
    current->buffer = framebuffer_create(width, height);
    current->texture = sfTexture_createFromFile(file, NULL);
    if(!current->texture)
        exit(EXIT_FAILURE);
    current->sprite = sfSprite_create();

    sfSprite_setTexture(current->sprite, current->texture, sfTrue);
    return (current);
}

int update_frame(window_t *current)
{
    while (sfRenderWindow_pollEvent(current->window, &current->event)) {
        if (current->event.type == sfEvtClosed)
            sfRenderWindow_close(current->window);
        sfRenderWindow_clear(current->window, sfBlack);
        sfRenderWindow_drawSprite(current->window, current->sprite, NULL);
        sfRenderWindow_display(current->window);
    }
    return (0);
}

int draw_window(int width, int height, int bits, char *file)
{
    window_t *current = init_frame(width, height, bits, file);

    if (!current->window)
        return (1);
    while (sfRenderWindow_isOpen(current->window))
        update_frame(current);
    sfSprite_destroy(current->sprite);
    sfTexture_destroy(current->texture);
    sfRenderWindow_destroy(current->window);
    free(current->buffer);
    free(current);
    return (0);
}
