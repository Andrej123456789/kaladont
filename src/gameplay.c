#include "headers/gameplay.h"

void gameplay(Gameplay* _gameplay, Start* _start)
{
    bool game_finished = false;
    _gameplay->player = 0;

    while (!game_finished)
    {
        char user_input[1024];
        
        printf("Player %lu: ", _gameplay->player);
        scanf("%1023s", user_input);

        printf("%s\n", user_input);

        _gameplay->player += 1;
        if (_gameplay->player > _start->players)
        {
            _gameplay->player = 0;
        }
    } 
}
