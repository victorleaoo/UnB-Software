/*
  -> Arquivo para definir as músicas
*/

// Includes
#include "music.h"
#include "buzzer.h"

// Música Mario
struct Music musica_mario(void){
	static struct Note notes[] = { 
		nota(659, 125, 255, 0, 0), notaDelay(125), nota(659, 125, 0, 255, 0), notaDelay(125), nota(659, 125, 0, 0, 255), notaDelay(167),
        nota(523, 125, 255, 255, 0), notaDelay(125), nota(659, 125, 0, 255, 255), notaDelay(167), nota(784, 125, 255, 0, 255), notaDelay(333),
        nota(392, 125, 255, 255, 255), notaDelay(333), nota(523, 125, 0, 0, 0), notaDelay(250), nota(392, 125, 255, 0, 0), notaDelay(250),
        nota(330, 125, 0, 255, 0), notaDelay(250), nota(440, 125, 0, 0, 255), notaDelay(125), nota(494, 125, 0, 255, 255), notaDelay(125),
        nota(466, 125, 0, 0, 0), notaDelay(42), nota(440, 125, 255, 0, 0), notaDelay(125), nota(392, 125, 0, 255, 0), notaDelay(125)
        };

	static struct Music music = {
		.name = "mario", .size = sizeof(notes)/sizeof(*notes),
		.notes = notes
	};
	
	return music;
}

// Música Sonic
struct Music musica_sonic(void){
	static struct Note notes[] = { 
		nota(392, 750, 255, 0, 0), nota(494, 750, 0, 255, 0), nota(523, 750, 0, 0, 255), notaDelay(375), nota(494, 375, 255, 255, 0),
        nota(440, 750, 0, 0, 0), nota(494, 750, 0, 255, 255), nota(523, 750, 255, 255, 255), notaDelay(375), nota(587, 375, 0, 0, 0),
        nota(523, 375, 255, 255, 255), nota(494, 375, 255, 0, 255), nota(523, 375, 255, 0, 0), nota(587, 375, 255, 255, 0), nota(523, 375, 255, 255, 255),
        nota(494, 375, 0, 0, 0), nota(523, 750, 0, 0, 255), nota(659, 750, 0, 255, 0), nota(784, 750, 0, 255, 255), notaDelay(375),
        nota(784, 375, 255, 0, 255), nota(698, 750, 0, 0, 0), nota(659, 750, 255, 255, 255), nota(587, 750, 255, 0, 0), notaDelay(375),
        nota(659, 375, 255, 255, 255), nota(698, 375, 0, 0, 0), nota(659, 375, 255, 0, 0), nota(587, 375, 255, 255, 255), nota(659, 750, 0, 255, 0) 
		};

	static struct Music music = {
		.name = "sonic", .size = sizeof(notes)/sizeof(*notes),
		.notes = notes
	};
	
	return music;
}

// Música Zelda
struct Music musica_zelda(void){
	static struct Note notes[] = { 
		nota(494, 200, 255, 0, 0), notaDelay(200), nota(494, 200, 0, 255, 0), notaDelay(200),
        nota(523, 200, 0, 0, 255), notaDelay(200), nota(587, 400, 255, 255, 255), notaDelay(400),
        nota(659, 200, 0, 0, 0), notaDelay(200), nota(587, 200, 255, 0, 0), notaDelay(200),
        nota(523, 200, 0, 255, 0), notaDelay(200), nota(494, 400, 255, 0, 255), notaDelay(400)
		};

	static struct Music music = {
		.name = "zelda", .size = sizeof(notes)/sizeof(*notes),
		.notes = notes
	};

	return music;
}

// Música Megalovania
struct Music musica_megalovania(void){
	static struct Note notes[] = { 
		nota(659, 200, 255, 0, 0), notaDelay(200),
        nota(622, 200, 0, 255, 0), notaDelay(200),
        nota(587, 200, 0, 0, 255), notaDelay(200),
        nota(523, 200, 255, 255, 0), notaDelay(200),
        nota(494, 400, 255, 0, 255), notaDelay(400),
        nota(523, 200, 0, 255, 255), notaDelay(200),
        nota(587, 200, 255, 255, 255), notaDelay(200),
        nota(622, 400, 255, 0, 0), notaDelay(400),
        nota(659, 200, 0, 255, 0), notaDelay(200),
        nota(622, 200, 0, 0, 255), notaDelay(200),
        nota(587, 400, 255, 255, 0), notaDelay(400),
        nota(659, 200, 255, 0, 255), notaDelay(200),
        nota(622, 200, 0, 255, 255), notaDelay(200),
        nota(587, 200, 255, 255, 255), notaDelay(200),
        nota(587, 200, 0, 0, 0), notaDelay(200),
        nota(523, 200, 255, 0, 0), notaDelay(200),
        nota(494, 400, 0, 255, 0), notaDelay(400),
        nota(523, 200, 0, 0, 255), notaDelay(200),
        nota(587, 200, 0, 255, 0), notaDelay(200),
        nota(659, 200, 255, 0, 255), notaDelay(200),
        nota(622, 200, 0, 255, 255), notaDelay(200),
        nota(587, 200, 255, 255, 255), notaDelay(200),
        nota(523, 200, 0, 0, 0), notaDelay(200)
		};

	static struct Music music = {
		.name = "megalovania", .size = sizeof(notes)/sizeof(*notes),
		.notes = notes
	};

	return music;
}