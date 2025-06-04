//Aiden D'Antuono
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

int main() {

	const int FPS = 60;
	int width = 640;
	int height = 480;
	bool exit = false;

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *eventQueue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *background = NULL;
	ALLEGRO_BITMAP *character = NULL;

	//program init
	if (!al_init())
		return -1;

	//display creation
	display = al_create_display(width, height);

	if (!display)
		return -1;

	//timer creation
	timer = al_create_timer(1.0 / FPS);
	if (!timer)
		return -1;

	//event queue creation
	eventQueue = al_create_event_queue();
	if (!eventQueue)
		return -1;

	//image init
	if (!al_init_image_addon())
		return -1;

	//Load Images
	character = al_load_bitmap("PixelArtCharacter.png");
	background = al_load_bitmap("Grass.png");

	//Register event sources
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_timer_event_source(timer));

	while (!exit) {
		ALLEGRO_EVENT event;
		al_wait_for_event(eventQueue, &event);

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			exit = true;
		}
	}

}