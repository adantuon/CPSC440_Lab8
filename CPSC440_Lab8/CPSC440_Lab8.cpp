//Aiden D'Antuono
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <cstdlib>
#include <stdio.h>

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

	//Keyboard Installation
	if (!al_install_keyboard())
		return -1;

	//image init
	if (!al_init_image_addon())
		return -1;

	//Load Images
	character = al_load_bitmap("PixelArtCharacter.png");
	background = al_load_bitmap("Grass.png");

	//Register event sources
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_keyboard_event_source());
	al_register_event_source(eventQueue, al_get_timer_event_source(timer));

	int x = width / 2;
	int y = height / 2;
	int direction = 1;
	int rdirection = 1;
	float facing = 1;
	int speed = 3;
	al_draw_scaled_bitmap(background, 0, 0, 1024, 1024, 0, 0, 640, 480, 0);
	al_draw_rotated_bitmap(character, 32, 32, x, y, 0, 0);
	al_start_timer(timer);
	while (!exit) {
		ALLEGRO_EVENT event;
		al_wait_for_event(eventQueue, &event);

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			exit = true;
		}
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN && direction == facing) {
			switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					if (direction == 1)
						rdirection = -1;
					else
						rdirection = 1;

					direction = 0;
					break;
				case ALLEGRO_KEY_RIGHT:
					if (direction == 2)
						rdirection = -1;
					else
						rdirection = 1;
					direction = 1;

					break;
				case ALLEGRO_KEY_DOWN:
					if (direction == 3)
						rdirection = -1;
					else
						rdirection = 1;

					direction = 2;
					break;
				case ALLEGRO_KEY_LEFT:
					if (direction == 0)
						rdirection = -1;
					else
						rdirection = 1;

					direction = 3;
					break;
				//case ALLEGRO_KEY_SPACE:
			}
		}

		//Direction Based Movement
		if (direction == facing) {
			switch (direction) {
			case 0:
				y -= speed;
				break;
			case 1:
				x += speed;
				break;
			case 2:
				y += speed;
				break;
			case 3:
				x -= speed;
				break;
			}
		}
		else {
			facing += rdirection * .1;
			printf("facing: %f, direction: %i\n", facing, direction);
			if (std::abs(direction - facing) < 0.00001f) {
				facing = direction;
			}
			else if (facing > 3 && rdirection == 1) {
				facing -= 4;
			}
			else if (facing < 0 && rdirection == -1) {
				facing += 4;
			}
		}
		

		if (y <= 32) {
			y = 32;
			direction = 2;
		}
		else if (x >= width - 32) {
			x = width - 32;
			direction = 3;
		}
		else if (y >= height - 32) {
			y = height - 32;
			direction = 0;
		}
		else if (x <= 32) {
			x = 32;
			direction = 1;
		}

		al_draw_scaled_bitmap(background, 0, 0, 1024, 1024, 0, 0, 640, 480, 0);
		al_draw_rotated_bitmap(character, 32, 32, x, y, facing * ALLEGRO_PI / 2, 0);
		al_flip_display();
	}

}