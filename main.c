#include <ncurses.h>
#include <stdio.h>

#define ANCHO 100   // Ancho de la pantalla en píxeles
#define ALTO 100  // Alto de la pantalla en píxeles

// Función para inicializar la "pantalla"
void inicializarPantalla(char pantalla[ALTO][ANCHO]) {
    for (int i = 0; i < ALTO; i++) {
        for (int j = 0; j < ANCHO; j++) {
            pantalla[i][j] = ' ';  // Inicializamos la pantalla con espacios
        }
    }
}

// Función para dibujar la "pantalla" en ncurses
void dibujarPantalla(char pantalla[ALTO][ANCHO]) {
    clear();  // Limpiar la pantalla
    for (int i = 0; i < ALTO; i++) {
        for (int j = 0; j < ANCHO; j++) {
            mvaddch(i, j, pantalla[i][j]);  // Dibujar cada píxel
        }
    }
    refresh();  // Refrescar la pantalla para que los cambios se vean
}

// Función para dibujar un "píxel"
void dibujarPixel(char pantalla[ALTO][ANCHO], int x, int y, char simbolo) {
    if (x >= 0 && x < ANCHO && y >= 0 && y < ALTO) {
        pantalla[y][x] = simbolo;  // Colocar el símbolo en la posición indicada
    }
}

int main() {
    char pantalla[ALTO][ANCHO];  // Pantalla de 40x20
    int x, y;                    // Coordenadas del mouse
    char simbolo = '*';           // El símbolo a dibujar, puede ser cualquier otro

    // Inicializar ncurses
    initscr();            // Inicializar ncurses
    raw();                // Desactivar el buffering de entrada
    keypad(stdscr, TRUE); // Habilitar teclas especiales (como el mouse)
    noecho();             // No mostrar lo que el usuario escribe
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL); // Activar los eventos del mouse

    // Inicializamos la pantalla
    inicializarPantalla(pantalla);
    dibujarPantalla(pantalla);

    while (1) {
        MEVENT evento;  // Estructura para almacenar el evento del mouse

        int ch = getch();  // Obtener la entrada del usuario

        // Verificar si se ha hecho clic con el mouse
        if (ch == KEY_MOUSE) {
            if (getmouse(&evento) == OK) {
                if (evento.bstate & BUTTON1_PRESSED) {  // Si se ha hecho clic
                    x = evento.x;  // Coordenada X del mouse
                    y = evento.y;  // Coordenada Y del mouse

                    // Asegurarse de que el clic esté dentro de los límites de la pantalla
                    if (x >= ANCHO) x = ANCHO - 1;
                    if (y >= ALTO) y = ALTO - 1;

                    // Dibujar un píxel en la posición del clic
                    dibujarPixel(pantalla, x, y, simbolo);
                    dibujarPantalla(pantalla);  // Refrescar la pantalla
                }
            }
        }

        // Si se presiona 'q', salir del programa
        if (ch == 'q') {
            break;
        }
    }

    // Finalizar ncurses
    endwin();
    return 0;
}
