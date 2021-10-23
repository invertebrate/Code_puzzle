#include "events.hpp"

void *game_lost(void *data1, void *data2)
{
		printf("GAME LOST :( \n");
		(void)data1;
		(void)data2;
		return (NULL);
}
void *game_won(void *data1, void *data2)
{
		printf("GAME WON!!!\n");
		(void)data1;
		(void)data2;
		return (NULL);
}