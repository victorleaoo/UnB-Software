#ifndef BUZZER_H
#define BUZZER_H

#define DELAY_NOTE 0


#define nota(f, d, r, g, b)        \
  (struct Note)                  \
  {                              \
    .freq = f, .duracao = d, .red = r, .green = g, .blue = b \
  }
#define notaDelay(d) nota(DELAY_NOTE, d, 255, 255, 255)

// Structs
struct Note{
  int freq;
  int duracao;
  int red;
  int green;
  int blue;
};
struct Music
{
	const char *name;
	struct Note *notes;
	int size;
};

// Funções
void chama_nota(struct Note note, int i, int size);
void som_nota(int freq, int red, int green, int blue, int i, int size);
void para_buzzer();
void toca_musica(struct Music music);

#endif