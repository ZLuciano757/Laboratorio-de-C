#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <direct.h>

// variables constantes
#define pixeles 23
#define ANCHO_PANTALLA 1300
#define ALTURA_PANTALLA 600
#define alto 22
#define ancho 52
#define suelo ' '
#define pared '#'
#define enemigo '&'
#define cofre '='
#define salida 'S'
#define cant_vida 100
#define MAX_PATH_LENGTH 1024
#define Cantidad_enemigos_texturas 42
#define Cantidad_jugadores_texturas 22  
#define presuelo "o5*l4379rRpPT168"

// variables
int aux, stage;
int movY [4] = {-1, 1, 0, 0};
int movX [4] = {0, 0, -1, 1};
char mapa [alto][ancho];
char tesoros[4] = {'V', 'P', 'F', 'D'};
int zoom;
int ventanaAncho, ventanaAlto;
bool inicio;
bool entrar;
bool quit;
int Personaje;
int nuevoY;
int nuevoX;

// Guarda las texturas de los enemigos
int enemigosAsignados[alto][ancho];

// cargar las varibles de SDL
SDL_Window *ventana = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texturaSuelo = NULL;
SDL_Texture *texturaPared = NULL;
SDL_Texture *texturaCofre = NULL;
SDL_Texture *texturaSalida = NULL;
SDL_Texture *texturaPelea = NULL;
SDL_Texture *texturaFondotorre = NULL;
SDL_Texture *texturaDerrota = NULL;
SDL_Texture *texturaVictoria = NULL;
SDL_Texture *texturaTierra = NULL;
SDL_Texture *texturaPasto = NULL;
SDL_Texture *texturaPuerta = NULL;
SDL_Texture *texturaVentana = NULL;
SDL_Texture *texturaPiedra1 = NULL;
SDL_Texture *texturaPiedra2 = NULL;
TTF_Font *font = NULL;

Mix_Music* music_titulo = NULL;  
Mix_Music* music_bosque = NULL;
Mix_Music* music_batalla = NULL;
Mix_Music* music_masamorra = NULL;
Mix_Music* ganaste = NULL;
Mix_Music* perdiste = NULL;
Mix_Chunk* matar = NULL;
Mix_Chunk* herido = NULL;
Mix_Chunk* serpiente = NULL;
Mix_Chunk* pasos = NULL;
Mix_Chunk* soundcofre = NULL;
Mix_Chunk* aumpoints = NULL;
Mix_Chunk* aumpicos = NULL;
Mix_Chunk* derrumbe = NULL;

typedef struct {
    SDL_Texture *camino[11];
    SDL_Texture *arbol[6];
    SDL_Texture *ladrillo[6];
    SDL_Texture *arbusto[3];
    SDL_Texture *enemigos[Cantidad_enemigos_texturas];
    SDL_Texture *jugadores[Cantidad_jugadores_texturas];
} TodasTexturas;
TodasTexturas Texturas;

struct jugador{
    int x, y, color, picos, puntos, vida;
};
struct jugador jug;

struct quizzes{
    char* preg[59];
      char* op[59];
        char V[59];
};

const struct quizzes quiz = {
    .preg = {
        "Cual es la capital de Francia?",
        "Cual es el oceano mas grande del mundo?",
        "Quien escribio 'Don Quijote de la Mancha'?",
        "Cual es el pais mas grande del mundo?",
        "En que continente se encuentra Egipto?",
        "Que idioma se habla en Brasil?",
        "Quien pinto la Mona Lisa?",
        "Cual es el metal mas abundante en la Tierra?",
        "Que planeta es conocido como el Planeta Rojo?",
        "Quien fue el primer presidente de Estados Unidos?", //10
        "Que estructura de control se usa para repetir un conjunto de instrucciones?",
        "Como se declara una variable en pseudocodigo?",
        "Que palabra se usa para definir una condicion en pseudocodigo?",
        "Cual es la funcion de la sentencia sino en pseudocodigo?",
        "Que simboliza '//' en pseudocodigo?",
        "Cual es la estructura correcta para un condicional SI?",
        "Como se representa una operacion de entrada en pseudocodigo?",
        "Que operador se usa para asignar un valor a una variable?",
        "Que es un registro?",
        "Que palabra se usa para terminar un bucle?",
        "Como se declara una constante en pseudocodigo?",
        "Que hace la instruccion Escribir en pseudocodigo?",
        "Que estructura se usa para almacenar multiples valores del mismo tipo?",
        "Como se llama una funcion que no devuelve valor?",
        "Que significa la palabra clave 'MOD' en pseudocodigo?",
        "Como se escribe un comentario en pseudocodigo?",
        "Que se usa para indicar el inicio de un bucle que primero analiza una condicion y luego ejecuta codigo de forma repetida?",
        "Que palabra se usa para finalizar una condicion SI en pseudocodigo?",
        "Como se indica una instruccion de salida en pseudocodigo?",
        "Que estructura se usa para decisiones multiples (Mas de dos)?",
        "Que biblioteca estandar se usa para manejar entradas y salidas en C?",
        "Como se declara una variable entera en C?",
        "Que funcion se usa para imprimir en pantalla en C?",
        "Cual es el tipo de dato para un caracter en C?",
        "Que simbolo se usa para comentarios de una linea en C?",
        "Como se llama una funcion que no devuelve ningun valor en C?",
        "Que operador se usa para comparar igualdad en C?",
        "Como se inicia un bucle for en C?",
        "Que palabra clave se usa para definir una estructura en C?",
        "Que operador se usa para acceder a los miembros de una estructura?",
        "Que biblioteca se usa para funciones matematicas en C?",
        "Que funcion se usa para leer una cadena de caracteres?",
        "Que tipo de dato se usa para numeros con decimales?",
        "Como se define una constante en C?",
        "Que funcion se usa para asignar memoria dinamicamente?",
        "Que palabra clave se usa para incluir archivos de encabezado en C?",
        "Cual es el valor de un puntero no inicializado en C?",
        "Que operador se usa para acceder a una direccion de memoria?",
        "Cual es la extension habitual para archivos fuente en C?",
        "Que funcion se usa para liberar la memoria asignada dinamicamente?",
        "Que tipo de datos representa valores verdaderos y falsos en C?",
        "Cual es el operador logico Y (AND) en C?",
        "Como se declara una matriz de 10 enteros en C?",
        "Que palabra clave se usa para definir una enumeracion en C?",
        "Cual es el operador de incremento en C?",
        "Que funcion se usa para comparar dos cadenas en C?",
        "Que palabra clave se usa para crear una funcion en C?",
        "Cual es el valor de retorno tipico para indicar exito en una funcion en C?",
        "Cual es el tamaño de un tipo de dato int en la mayoria de los compiladores de C?"

    },
    .op = {
        "a) Berlin b) Paris",
        "a) Oceano Atlantico b) Oceano Pacifico",
        "a) Miguel de Cervantes b) Gabriel Garcia Marquez",
        "a) Rusia b) India",
        "a) Asia b) Africa",
        "a) Espanol b) Portugues",
        "a) Vincent van Gogh b) Leonardo da Vinci",
        "a) Hierro b) Aluminio",
        "a) Marte b) Jupiter", 
        "a) Abraham Lincoln b) George Washington", //10
        "a) Siempre que b) Para c) For",
        "a) var : nombre; b) nombre : (tipo de dato); c) (tipo de dato) nombre;",
        "a) SI b) IF c) FOR",
        "a) Repetir una instruccion b) Definir una variable c) Proveer una alternativa a SI",
        "a) Inicio de un comentario b) Division c) Concatenacion",
        "a) SI (condicion) entonces b) SI (condicion); c) SI (condicion)(tipo de dato)",
        "a) Leer b) Imprimir c) INPUT",
        "a) = b) := c) ==",
        "a) Una serie de datos b) Tipo de dato c) Dato simple",
        "a) EXIT b) FIN c) BREAK",
        "a) const nombre; b) Nombre = dato c) DEFINE nombre;",
        "a) Detiene el programa b) Devuelve un valor c) Muestra al usuario",
        "a) Variable b) Matriz c) Estructura",
        "a) Procedimiento b) Funcion c) Metodo",
        "a) Modulo b) Modificar c) Modo",
        "a) // comentario b) /* comentario */ c) ' comentario",
        "a) While b) Mientras c) Repetir",
        "a) FIN b) ENDIF c) END",
        "a) PRINT b) ESCRIBIR c) OUTPUT", 
        "a) SWITCH b) SI SINO c) SEGUN",
        "a) stdlib.h b) conio.h c) stdio.h d) string.h",///acaaa
        "a) int numero; b) var numero; c) integer numero; d) num numero;",
        "a) scanf b) cout c) printf d) echo",
        "a) char b) string c) character d) byte",
        "a) // b) /* c) # d) --",
        "a) void b) int c) null d) empty",
        "a) = b) == c) === d) !=",
        "a) for (i = 0; i < n; i++) b) while (i < n) c) repeat (i < n) d) do (i = 0; i < n; i++)",
        "a) class b) struct c) union d) record",
        "a) . b) -> c) :: d) :",
        "a) math.h b) stdlib.h c) conio.h d) string.h",
        "a) gets b) fgets c) scanf d) all of the above",
        "a) int b) float c) char d) void",
        "a) constant b) final c) const d) define",
        "a) malloc b) calloc c) realloc d) all of the above",
        "a) import b) include c) using d) header",
        "a) 0 b) NULL c) undefined d) random",
        "a) * b) & c) d) ^",
        "a) .cpp b) .java c) .c d) .py",
        "a) free b) delete c) release d) remove",
        "a) bool b) int c) boolean d) _Bool",
        "a) || b) && c) ! d) |",
        "a) int array[10]; b) int array; c) int array[] = 10; d) array int[10];",
        "a) enum b) enumeration c) list d) enumlist",
        "a) ++ b) -- c) += d) -=",
        "a) strcmp b) strcpy c) strlen d) strcat",
        "a) void b) function c) define d) int",
        "a) 1 b) 0 c) -1 d) NULL",
        "a) 2 bytes b) 4 bytes c) 8 bytes d) depende del compilador"
    },
    .V = {
        'b',
        'b',
        'a',
        'a',
        'b',
        'b',
        'b',
        'a',
        'a',
        'b', //10
        'b',
        'b',
        'a',
        'c',
        'a',
        'a',
        'a',
        'b',
        'b',
        'b',
        'b',
        'c',
        'b',
        'a',
        'a',
        'a',
        'b',
        'a',
        'b',
        'c',
        'c', //as
        'a',
        'c',
        'a',
        'a',
        'a',
        'b',
        'a',
        'b',
        'a',
        'a',
        'b',
        'b',
        'c',
        'd',
        'b',
        'b',
        'b',
        'c',
        'a',
        'd',
        'b',
        'a',
        'a',
        'a',
        'a',
        'a',
        'b',
        'b'
    }
};

// Inicializar SDL
void initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL no se pudo inicializar! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
    
    ventana = SDL_CreateWindow("Criptas Algoritmicas", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO_PANTALLA, ALTURA_PANTALLA, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (ventana == NULL) {
        printf("Window no se pudo inicializar! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        printf("Renderer no se pudo crear! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        printf("SDL2_image no se pudo inicializar! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    if (TTF_Init() == -1) {
        printf("Error al inicializar SDL_ttf: %s\n", TTF_GetError());
    exit(1);
    }

}

// Limpiar recursos
void cleanupSDL() {

    for (int i = 0; i < Cantidad_enemigos_texturas; i++) {
        if (Texturas.enemigos[i]) {
            SDL_DestroyTexture(Texturas.enemigos[i]);
            Texturas.enemigos[i] = NULL;
        }
    }

    for (int i = 0; i < Cantidad_jugadores_texturas; i++) {
        if (Texturas.jugadores[i]) {
            SDL_DestroyTexture(Texturas.jugadores[i]);
            Texturas.jugadores[i] = NULL;
        }
    }

    for (int i = 0; i < 3; i++) {
        if (Texturas.arbusto[i]) {
            SDL_DestroyTexture(Texturas.arbusto[i]);
            Texturas.arbusto[i] = NULL;
        }
    }

    for (int i = 0; i < 10; i++) {
        if (Texturas.camino[i]) {
            SDL_DestroyTexture(Texturas.camino[i]);
            Texturas.camino[i] = NULL;
        }
    }

    for (int i = 0; i < 6; i++) {
        if (Texturas.ladrillo[i]) {
            SDL_DestroyTexture(Texturas.ladrillo[i]);
            Texturas.ladrillo[i] = NULL;
        }
    }

    for (int i = 0; i < 6; i++) {
        if (Texturas.arbol[i]) {
            SDL_DestroyTexture(Texturas.arbol[i]);
            Texturas.arbol[i] = NULL;
        }
    }
    
    SDL_DestroyTexture(texturaPared);
    SDL_DestroyTexture(texturaSuelo);
    SDL_DestroyTexture(texturaCofre);
    SDL_DestroyTexture(texturaSalida);
    SDL_DestroyTexture(texturaPuerta);
    SDL_DestroyTexture(texturaFondotorre);
    SDL_DestroyTexture(texturaPelea);
    SDL_DestroyTexture(texturaVictoria);
    SDL_DestroyTexture(texturaDerrota);
    SDL_DestroyTexture(texturaTierra);
    SDL_DestroyTexture(texturaPasto);
    SDL_DestroyTexture(texturaVentana);
    SDL_DestroyTexture(texturaPiedra1);
    SDL_DestroyTexture(texturaPiedra2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ventana);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

// Cargar recursos
SDL_Texture* loadTexture(const char* path) {
    SDL_Texture* newTexture = IMG_LoadTexture(renderer, path);
    if (newTexture == NULL) {
        printf("No se pudo generar imagen %s! SDL_image Error: %s\n", path, SDL_GetError());
    }
    return newTexture;
}

TTF_Font* loadFont(const char* path, int size) {
    TTF_Font* font = TTF_OpenFont(path, size);
    if (!font) {
        printf("Error al cargar la fuente %s: %s\n", path, TTF_GetError());
    }
    return font;
}

// Función para obtener la ruta de la carpeta donde está el ejecutable
void obtenerRutaEjecutable(char* rutaEjecutable) { 
    // Obtener la ruta completa del ejecutable
    GetModuleFileName(NULL, rutaEjecutable, MAX_PATH_LENGTH);

    // Buscar la última barra invertida en la ruta (directorio)
    char* ultimaBarra = strrchr(rutaEjecutable, '\\');
    if (ultimaBarra) {
        *(ultimaBarra + 1) = '\0';  // Terminar la ruta en la carpeta del ejecutable
    }
}

// Cargar texturas
void cargar_texturas(SDL_Renderer* renderer) {
    // Obtener la ruta del ejecutable
    char rutaEjecutable[MAX_PATH_LENGTH];
    obtenerRutaEjecutable(rutaEjecutable);

    // Construir las rutas completas de las texturas
    char rutaTexto[2048];

    //carga el suelo de la mazmorra
    snprintf(rutaTexto, sizeof(rutaTexto), "%sassets\\imagenes\\elementos\\suelos\\suelo.png", rutaEjecutable);
    texturaSuelo = IMG_LoadTexture(renderer, rutaTexto);
    if (!texturaSuelo) {
        printf("Error al cargar textura suelo: %s\n", SDL_GetError());
        exit(1);  // Termina el programa si la textura no se carga
    }

    // carga la textura de la pared de la mazmorra
    snprintf(rutaTexto, sizeof(rutaTexto), "%sassets\\imagenes\\elementos\\paredes\\pared1.png", rutaEjecutable);
    texturaPared = IMG_LoadTexture(renderer, rutaTexto);
    if (!texturaPared) {
        printf("Error al cargar textura pared: %s\n", SDL_GetError());
        exit(1);
    }

    // Carga todas las texturas posibles de los enemigos
    for (int i = 0; i < Cantidad_enemigos_texturas; i++) {
        snprintf(rutaTexto, sizeof(rutaTexto), "%sassets\\imagenes\\enemigos\\enemigo%d.png", rutaEjecutable, i + 1);
        Texturas.enemigos[i] = IMG_LoadTexture(renderer, rutaTexto);
        if (!Texturas.enemigos[i]) {
            printf("Error al cargar textura enemigo %d: %s\n", i + 1, SDL_GetError());
            exit(1);
        }
    }

    // carga la textura del cofre
    snprintf(rutaTexto, sizeof(rutaTexto), "%sassets\\imagenes\\elementos\\misc\\cofre.png", rutaEjecutable);
    texturaCofre = IMG_LoadTexture(renderer, rutaTexto);
    if (!texturaCofre) {
        printf("Error al cargar textura cofre: %s\n", SDL_GetError());
        exit(1);
    }

    // carga la textura de la salida de la mazmorra 
    snprintf(rutaTexto, sizeof(rutaTexto), "%sassets\\imagenes\\elementos\\misc\\salida.png", rutaEjecutable);
    texturaSalida = IMG_LoadTexture(renderer, rutaTexto);
    if (!texturaSalida) {
        printf("Error al cargar textura salida: %s\n", SDL_GetError());
        exit(1);
    }

    // Carga todas las texturas posibles de los jugadores
    for (int i = 0; i < Cantidad_jugadores_texturas; i++) {
        snprintf(rutaTexto, sizeof(rutaTexto), "%sassets\\imagenes\\jugadores\\jugador%d.png", rutaEjecutable, i + 1);
        Texturas.jugadores[i] = IMG_LoadTexture(renderer, rutaTexto);
        if (!Texturas.jugadores[i]) {
            printf("Error al cargar textura enemigo %d: %s\n", i + 1, SDL_GetError());
            exit(1);
        }
    }

    // cargar textura de fondo de las peleas
    snprintf(rutaTexto, sizeof(rutaTexto), "%sassets\\imagenes\\Fondos\\FondoPelea1.png", rutaEjecutable);
    texturaPelea = IMG_LoadTexture(renderer, rutaTexto);
    if (!texturaPelea) {
        printf("Error al cargar textura Fondo pelea: %s\n", SDL_GetError());
        exit(1);
    }

    // cargar textura de fondo de la victoria
    snprintf(rutaTexto, sizeof(rutaTexto), "%sassets\\imagenes\\Fondos\\FondoVictoria.png", rutaEjecutable);
    texturaVictoria = IMG_LoadTexture(renderer, rutaTexto);
    if (!texturaVictoria) {
        printf("Error al cargar textura Fondo pelea: %s\n", SDL_GetError());
        exit(1);
    }

    // cargar textura de fondo del gameover
    snprintf(rutaTexto, sizeof(rutaTexto), "%sassets\\imagenes\\Fondos\\FondoGameover.png", rutaEjecutable);
    texturaDerrota = IMG_LoadTexture(renderer, rutaTexto);
    if (!texturaDerrota) {
        printf("Error al cargar textura Fondo pelea: %s\n", SDL_GetError());
        exit(1);
    }

    // cargar textura de fondo de la torre
    snprintf(rutaTexto, sizeof(rutaTexto), "%sassets\\imagenes\\Fondos\\fondoTorre.png", rutaEjecutable);
    texturaFondotorre = IMG_LoadTexture(renderer, rutaTexto);
    if (!texturaFondotorre) {
        printf("Error al cargar textura Fondo de la torre: %s\n", SDL_GetError());
        exit(1);
    }

    // textura de los ladrillo de la torre
    for (int i = 0; i < 6; i++) {
        snprintf(rutaTexto, sizeof(rutaTexto), "%sassets\\imagenes\\elementos\\salaInicial\\ladrillo%d.png", rutaEjecutable, i + 1);
        Texturas.ladrillo[i] = IMG_LoadTexture(renderer, rutaTexto);
        if (!Texturas.ladrillo[i]) {
            printf("Error al cargar textura del ladrillo %d: %s\n", i + 1, SDL_GetError());
            exit(1);
        }
    }

    // cargar textura de la tierra de adelante de la torre
    snprintf(rutaTexto, sizeof(rutaTexto), "%sassets\\imagenes\\elementos\\salaInicial\\tierra.png", rutaEjecutable);
    texturaTierra = IMG_LoadTexture(renderer, rutaTexto);
    if (!texturaTierra) {
        printf("Error al cargar textura de la tierra: %s\n", SDL_GetError());
        exit(1);
    }

    // Carga la texturas de la puerta
    snprintf(rutaTexto, sizeof(rutaTexto), "%sassets\\imagenes\\elementos\\salaInicial\\entrada.png", rutaEjecutable);
    texturaPuerta = IMG_LoadTexture(renderer, rutaTexto);
    if (!texturaPuerta) {
        printf("Error al cargar textura de la puerta: %s\n", SDL_GetError());
        exit(1);
    }

    // Carga la textura del pasto de la torre
    snprintf(rutaTexto, sizeof(rutaTexto), "%sassets\\imagenes\\elementos\\salaInicial\\pasto1.png", rutaEjecutable);
    texturaPasto = IMG_LoadTexture(renderer, rutaTexto);
    if (!texturaPasto) {
        printf("Error al cargar textura del pasto: %s\n", SDL_GetError());
        exit(1);
    }

    // carga la textura de la ventana de la torre
    snprintf(rutaTexto, sizeof(rutaTexto), "%sassets\\imagenes\\elementos\\salaInicial\\ventana.png", rutaEjecutable);
    texturaVentana = IMG_LoadTexture(renderer, rutaTexto);
    if (!texturaVentana) {
        printf("Error al cargar textura de la ventana: %s\n", SDL_GetError());
        exit(1);
    }

    // carga las texturas de las piedras de la torre
    snprintf(rutaTexto, sizeof(rutaTexto), "%sassets\\imagenes\\elementos\\salaInicial\\piedras1.png", rutaEjecutable);
    texturaPiedra1 = IMG_LoadTexture(renderer, rutaTexto);
    if (!texturaPiedra1) {
        printf("Error al cargar textura de la piedra1: %s\n", SDL_GetError());
        exit(1);
    }

    snprintf(rutaTexto, sizeof(rutaTexto), "%sassets\\imagenes\\elementos\\salaInicial\\piedras2.png", rutaEjecutable);
    texturaPiedra2 = IMG_LoadTexture(renderer, rutaTexto);
    if (!texturaPiedra2) {
        printf("Error al cargar textura de la piedra2: %s\n", SDL_GetError());
        exit(1);
    }

    // textura de los arbustos de la torre
    for (int i = 0; i < 3; i++) {
        snprintf(rutaTexto, sizeof(rutaTexto), "%sassets\\imagenes\\elementos\\salaInicial\\arbusto%d.png", rutaEjecutable, i + 1);
        Texturas.arbusto[i] = IMG_LoadTexture(renderer, rutaTexto);
        if (!Texturas.arbusto[i]) {
            printf("Error al cargar textura del arbusto %d: %s\n", i + 1, SDL_GetError());
            exit(1);
        }
    }

    // textura de los caminos que hay adelante de la torre
    for (int i = 0; i < 10; i++) {
        snprintf(rutaTexto, sizeof(rutaTexto), "%sassets\\imagenes\\elementos\\salaInicial\\camino%d.png", rutaEjecutable, i + 1);
        Texturas.camino[i] = IMG_LoadTexture(renderer, rutaTexto);
        if (!Texturas.camino[i]) {
            printf("Error al cargar textura del camino %d: %s\n", i + 1, SDL_GetError());
            exit(1);
        }
    }

    // textura del arbol de la torre
    for (int i = 0; i < 6; i++) {
        snprintf(rutaTexto, sizeof(rutaTexto), "%sassets\\imagenes\\elementos\\salaInicial\\arbol%d.png", rutaEjecutable, i + 1);
        Texturas.arbol[i] = IMG_LoadTexture(renderer, rutaTexto);
        if (!Texturas.arbol[i]) {
            printf("Error al cargar textura del arbol %d: %s\n", i + 1, SDL_GetError());
            exit(1);
        }
    }

}

// Notificaciones
void mostrarNotificacion(const char* mensaje, int duracionMs) {
    // Color y fuente
    SDL_Color color = {255, 255, 255, 255};

    // cargar fuente
    char rutaEjecutable[MAX_PATH_LENGTH];
    obtenerRutaEjecutable(rutaEjecutable);
    char rutaTexto[2048];
    
    snprintf(rutaTexto, sizeof(rutaTexto), "%sassets\\fuentes\\pixeleado.ttf", rutaEjecutable);
    TTF_Font* font = TTF_OpenFont(rutaTexto, 24);
    if (!font) {
        printf("Error al cargar la fuente: %s\n", TTF_GetError());
        return;
    }
    // Medir el tamaño del texto
    int textWidth, textHeight;
    if (TTF_SizeText(font, mensaje, &textWidth, &textHeight) != 0) {
        printf("Error al calcular el tamaño del texto: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }

    // Calcular posición y tamaño del cuadro
    int padding = 20; // Espaciado interno
    SDL_Rect panelRect = {
        (ANCHO_PANTALLA - textWidth - 2 * padding) / 2, // Centrar horizontalmente
        (ALTURA_PANTALLA - textHeight - 2 * padding) / 2, // Centrar verticalmente
        textWidth + 2 * padding,
        textHeight + 2 * padding
    };

    // Dibujar fondo del cuadro
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200); // Fondo negro translúcido
    SDL_RenderFillRect(renderer, &panelRect);

    // Crear superficie y textura del texto
    SDL_Surface* surface = TTF_RenderText_Solid(font, mensaje, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // Dibujar texto en el centro del cuadro
    SDL_Rect textRect = {
        panelRect.x + padding,
        panelRect.y + padding,
        textWidth,
        textHeight
    };
    SDL_RenderCopy(renderer, texture, NULL, &textRect);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);

    // Mostrar en pantalla
    SDL_RenderPresent(renderer);
    SDL_Delay(duracionMs); // Esperar la duración especificada
}

// captura la respuesta para las preguntas
char capturarRespuesta() {
    SDL_Event evento;
    char respuesta = '\0';
    while (respuesta == '\0') {
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) {
                exit(0); // Salir del juego si se cierra la ventana
            }
            if (evento.type == SDL_KEYDOWN) {
                switch (evento.key.keysym.sym) {
                    case SDLK_a: respuesta = 'a'; break;
                    case SDLK_b: respuesta = 'b'; break;
                    case SDLK_c: respuesta = 'c'; break;
                    case SDLK_d: respuesta = 'd'; break;
                    default: break; // Ignorar otras teclas
                }
            }
        }
    }
    return respuesta;
}

// muetra texto
void mostrarTexto(const char* mensaje, int x, int y, SDL_Color color, bool centralizar) {

    // cargar fuente
    char rutaEjecutable[MAX_PATH_LENGTH];
    obtenerRutaEjecutable(rutaEjecutable);
    char rutaTexto[2048];
    
    snprintf(rutaTexto, sizeof(rutaTexto), "%sassets\\fuentes\\pixeleado.ttf", rutaEjecutable);
    TTF_Font* font = TTF_OpenFont(rutaTexto, 24);
    if (!font) {
        printf("Error al cargar la fuente: %s\n", TTF_GetError());
        return;
    }
    
    SDL_Surface* surface = TTF_RenderText_Solid(font, mensaje, color);
    if (!surface) {
        printf("Error al crear superficie: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        printf("Error al cargar la textura: %s\n", TTF_GetError());
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
        return;
    }

    // Obtener el ancho y alto del texto
    int anchoTexto, altoTexto;
    SDL_QueryTexture(texture, NULL, NULL, &anchoTexto, &altoTexto);

    int X = x - (anchoTexto / 2);

    if (centralizar == true) {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);  // Habilitar mezcla de transparencia
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);  // Negro con 50% de transparencia (alfa = 128)
        SDL_Rect destRect = {X - 10, y - 5, anchoTexto + 20, altoTexto + 10};
        SDL_RenderFillRect(renderer, &destRect);
        SDL_RenderCopy(renderer, texture, NULL, &(SDL_Rect){X, y, anchoTexto, altoTexto});
    } else if (centralizar == false) {
        SDL_Rect destRect = {x, y, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, NULL, &destRect);
    }
    
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

// mostrar vida, picos, stage y puntos en todo momento
void mostrarInfoJugador() {
    // Color del texto (blanco)
    SDL_Color color = {255, 255, 255, 255};

    // Obtener el tamaño de la ventana
    SDL_GetWindowSize(ventana, &ventanaAncho, &ventanaAlto);
    
    char vidaTexto[50];
    char puntosTexto[50];
    char picosTexto[50];
    char stageTexto[50];
    
    snprintf(vidaTexto, sizeof(vidaTexto), "Vida: %d", jug.vida);
    snprintf(puntosTexto, sizeof(puntosTexto), "Puntos: %d", jug.puntos);
    snprintf(picosTexto, sizeof(picosTexto), "Pico/s: %d", jug.picos);
    snprintf(stageTexto, sizeof(stageTexto), "Stage = %d", stage);

    // Mostrar texto en la pantalla
    mostrarTexto(vidaTexto, 10, 10, color, false);   // Vida en la esquina superior izquierda
    mostrarTexto(puntosTexto, 10, 50, color, false); // Puntos debajo de la vida
    mostrarTexto(picosTexto, 10, 90, color, false); // Picos debajo de puntos
    mostrarTexto(stageTexto, ventanaAncho / 2, 10, color, true); // El Stage en el medio de la pantalla
}

// pantalla de la salida hacia otro piso
void mostrarPantallaSalida(int puntos, int objetivo, bool* avanzar) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Fondo negro
    SDL_RenderClear(renderer);

    SDL_Color blanco = {255, 255, 255, 255};
    char mensaje[200];
    char opciones[100];

    // Mensaje de la salida
    snprintf(mensaje, sizeof(mensaje), "Has encontrado la salida. Puntos: %d/%d", puntos, objetivo);
    mostrarTexto(mensaje, ventanaAncho / 2, ventanaAlto / 3, blanco, true);

    // Opciones
    snprintf(opciones, sizeof(opciones), "Deseas pasar al siguiente nivel? [a] Si ; [b] No");
    mostrarTexto(opciones, ventanaAncho / 2, ventanaAlto / 2, blanco, true);
    SDL_RenderPresent(renderer);

    // Capturar entrada
    bool respuestaValida = false;
    while (!respuestaValida) {
        SDL_Event evento;
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) {
                exit(0); // Salir del juego
            }
            if (evento.type == SDL_KEYDOWN) {
                switch (evento.key.keysym.sym) {
                    case SDLK_a:
                        *avanzar = true;  // Avanzar al siguiente nivel
                        respuestaValida = true;
                        break;
                    case SDLK_b:
                        *avanzar = false; // Permanecer en el nivel actual
                        respuestaValida = true;
                        break;
                    default:
                        break; // Ignorar otras teclas
                }
            }
        }
    }
}

// permite moverse por el suelo y no traspasar paredes
void matriz_jug (){
    mapa[jug.y][jug.x] = suelo;
    jug.y = jug.y + movY[aux];
    jug.x = jug.x + movX[aux];
    mapa[jug.y][jug.x] = suelo;
}

// genera el mapa
void generar_mapa (){
    for (int i = 0; i < alto; i++){
        for (int j = 0; j < ancho; j++){
            if (i == 0 || j == 0 || i == alto-1 || j == ancho-1 ){
                mapa [i][j] = pared;   
            }
            else{
                mapa [i][j] = suelo;
            }
        }
    }
    for (int i = 0; i < 100; i++){
        int x = rand() % (ancho - 4) + 2;
        int y = rand() % (alto - 4) + 2;
        mapa[y][x] = pared;
        int ejex [4] = {x,x,x+2,x-2};
        int ejey [4] = {y-2,y+2,y,y};
        int random = rand() % 4;
        if (mapa [ejey[random]][ejex[random]] == suelo){
            mapa [ejey[random]][ejex[random]] = pared;
            mapa [ejey[random] + (y - ejey[random])/2] [ejex[random] + (x - ejex[random])/2] = pared;
        }
    }
    for (int i = 0; i < stage*3 + 2 ; i++){
        int x = rand() % (ancho - 4) + 2;
        int y = rand() % (alto - 4) + 2;
        mapa[y][x] = enemigo;
    }
    for (int i = 0; i < 10-(stage*3); i++){
        int x = rand() % (ancho - 4) + 2;
        int y = rand() % (alto - 4) + 2;
        mapa[y][x] = cofre;
    }
    mapa[rand() % (alto - 4) + 2][rand() % (ancho - 4) + 2] = salida;
}

// Pone al jugador en la esquina superior izquierda
void inicializar_jug (){
    jug.y = 1;
    jug.x = 1;
    jug.picos = 3;
    jug.puntos = 0;
    jug.vida = cant_vida;
}

// ve que tipo de cofre es
void verificar_cofre (){
    if (pasos != NULL) {
                Mix_PlayChannel(-1, pasos, 2);
    }
    int random = rand() %3 + 1;
    char mensaje[100];
    switch (tesoros [rand()%4]){
        case 'V': 
            jug.vida += random * 10;
            jug.puntos += 200;
            snprintf(mensaje, sizeof(mensaje), "Vendas encontradas. Salud +%d, Puntos +200", random * 10);
        break;
        case 'P': 
            if (aumpicos != NULL) {
                Mix_PlayChannel(-1, aumpicos, 0);
            }
            jug.picos += random;
            if(random == 3){
                jug.picos -= 1;
                jug.puntos += 300;
                snprintf(mensaje, sizeof(mensaje), "Encontraste 2 picos! Puntos +300"); //ya que si es 3, le resta 1
            }
            else {
                snprintf(mensaje, sizeof(mensaje), "Pico/s encontrados: %d, Puntos +200", random);
                jug.puntos += 200;
            }
        break;
        case 'F': 
            if (aumpoints != NULL) {
                Mix_PlayChannel(-1, aumpoints, 0);
            } 
            jug.puntos += random * 1000;
            snprintf(mensaje, sizeof(mensaje), "Bonus de puntos: +%d", random * 1000);
        break;
        case 'D': 
            if (serpiente != NULL) {
                Mix_PlayChannel(-1, serpiente, 0);
            }
            jug.puntos += random * 1500;
            jug.vida -= random*10;
            snprintf(mensaje, sizeof(mensaje), "Una vibora! Vida -%d, Pero conseguiste Puntos +%d", random * 10, random * 1500);
        break;
    }
    mostrarNotificacion(mensaje, 1500); // Mostrar por 2 segundos
}

// muestra las peleas tipo rpg
void mostrarLucha(int jugadorID, int enemigoID) {
    // Obtener el tamaño de la ventana
    SDL_GetWindowSize(ventana, &ventanaAncho, &ventanaAlto);

    // Dibujar el fondo (rellena toda la pantalla)
    SDL_Rect fondoRect = {0, 0, ventanaAncho, ventanaAlto};
    SDL_RenderCopy(renderer, texturaPelea, NULL, &fondoRect);

    // Posición del jugador (izquierda del centro)
    SDL_Rect jugadorRect = {
        ventanaAncho / 4 - 50,          // Aproximadamente un cuarto del ancho de la ventana
        ventanaAlto / 2,               // Justo en el centro vertical
        100,                           // Ancho del sprite
        100                            // Alto del sprite
    };

    // Posición del enemigo (derecha del centro)
    SDL_Rect enemigoRect = {
        ventanaAncho * 3 / 4 - 50,     // Aproximadamente tres cuartos del ancho de la ventana
        ventanaAlto / 2,               // Justo en el centro vertical
        100,                           // Ancho del sprite
        100                            // Alto del sprite
    };

    // Dibujar el jugador
    if (jugadorID >= 0 && jugadorID < Cantidad_jugadores_texturas) {
        SDL_RenderCopy(renderer, Texturas.jugadores[jugadorID], NULL, &jugadorRect);
    } else {
        printf("Error: ID del jugador fuera de rango.\n");
    }

    // Dibujar el enemigo
    if (enemigoID >= 0 && enemigoID < Cantidad_enemigos_texturas) {
        SDL_RenderCopy(renderer, Texturas.enemigos[enemigoID], NULL, &enemigoRect);
    } else {
        printf("Error: ID del enemigo fuera de rango.\n");
    }

    SDL_RenderPresent(renderer);  // Mostrar todo lo renderizado en la pantalla
}

// sistema de lucha
void lucha() {
    Mix_HaltMusic();
    if (music_batalla != NULL){
        Mix_PlayMusic (music_batalla, -1);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Fondo negro
    SDL_RenderClear(renderer);

    char mensajePregunta[200];
    char mensajeOpciones[200];
    int random = 0;
    char elegida;
    int random2 = rand() % 20 + 11; // Daño aleatorio
    SDL_Color blanco = {255, 255, 255, 255};

    // Determinar pregunta según el stage
    switch (stage) {
        case 1:
            random = rand() % 10;
            break;
        case 2:
            random = rand() % 20 + 10;
            break;
        case 3:
            random = rand() % 30 + 30;
            break;
    }

    // Preparar mensajes
    snprintf(mensajePregunta, sizeof(mensajePregunta), "Pregunta: %s", quiz.preg[random]);
    snprintf(mensajeOpciones, sizeof(mensajeOpciones), "Opciones: %s ", quiz.op[random]);
    
    // obtiene el centro de la pantalla
    SDL_GetWindowSize(ventana, &ventanaAncho, &ventanaAlto);
    
    // Llamar a la función para mostrar texto y las imágenes del jugador y enemigo
    mostrarLucha(Personaje, enemigosAsignados[nuevoY][nuevoX]);

    // Dibujar mensajes en la pantalla
    mostrarTexto(mensajePregunta, ventanaAncho / 2, 100, blanco, true);
    mostrarTexto(mensajeOpciones, ventanaAncho / 2, 150, blanco, true);
    SDL_RenderPresent(renderer);

    // Capturar respuesta
    bool respuestaValida = false;
    while (!respuestaValida) {
        SDL_Event evento;
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) {
                exit(0);
            }
            if (evento.type == SDL_KEYDOWN) {
                switch (evento.key.keysym.sym) {
                    case SDLK_a: 
                        elegida = 'a'; 
                        respuestaValida = true; 
                        break;
                    case SDLK_b: 
                        elegida = 'b'; 
                        respuestaValida = true; 
                        break;
                    case SDLK_c: 
                        if (stage > 1) { elegida = 'c'; respuestaValida = true; } 
                        break;
                    case SDLK_d: 
                        if (stage > 2) { elegida = 'd'; respuestaValida = true; } 
                        break;
                    default: 
                        break;
                }
            }
        }
    }

    // Comparar respuesta
    if (elegida == quiz.V[random]) {
        if (matar != NULL) {
            Mix_PlayChannel(-1, matar, 0);
        }
        mostrarTexto("Correcto! Monstruo derrotado.", ventanaAncho / 2, 200, blanco, true);
        jug.puntos += 3000;
        matriz_jug();
    } else {
        char mensajeDanio[100];
        if (herido != NULL) {
            Mix_PlayChannel(-1, herido, 0);
        }
        snprintf(mensajeDanio, sizeof(mensajeDanio), "Incorrecto. Vida -%d", random2);
        mostrarTexto(mensajeDanio, ventanaAncho / 2, 200, blanco, true);
        jug.vida -= random2;
        if (jug.vida < 1) {
            stage = 0; // Game over
        }
    }
    
    SDL_RenderPresent(renderer);
    SDL_Delay(2000); // Esperar 2 segundos antes de continuar
    Mix_HaltMusic();
    if (music_masamorra != NULL){
        Mix_PlayMusic (music_masamorra, -1);
    }
}

// Puerta de salida
void salir() {
    bool avanzar = false;
    if (jug.puntos >= stage * 10000) {
        // Mostrar pantalla de salida
        mostrarPantallaSalida(jug.puntos, stage * 10000, &avanzar);

        if (avanzar) {
            stage += 1;  // Pasar al siguiente nivel
            generar_mapa();
        }
    } 
    else {
        // Mostrar mensaje de puntos insuficientes
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_Color blanco = {255, 255, 255, 255};
        char mensaje[200];
        snprintf(mensaje, sizeof(mensaje), "No tienes los puntos suficientes. Puntos: %d/%d", jug.puntos, stage * 10000);
        mostrarTexto(mensaje, ventanaAncho / 2, ventanaAlto / 2, blanco, true);
        SDL_RenderPresent(renderer);

        SDL_Delay(3000); // Mostrar mensaje por 3 segundos
    }
}

// detecta las teclas para moverse
void detectar_movimiento() {
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]){
        aux = 0; // Movimiento arriba
    }
    if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]){
        aux = 1; // Movimiento abajo
    }
    if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]){
        aux = 2; // Movimiento izquierda
    } 
    if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]){
        aux = 3; // Movimiento derecha 
    } 
}

// mueve al jugador por las salas
void mov_jug (){    
    nuevoY = jug.y + movY[aux];
    nuevoX = jug.x + movX[aux];

    if (mapa[nuevoY][nuevoX] != salida) {
        if (mapa[nuevoY][nuevoX] == pared && nuevoY != 0 && nuevoX != 0 && nuevoY != alto - 1 && nuevoX != ancho - 1) {
            if (jug.picos > 0) {
                if (derrumbe != NULL) {
                Mix_PlayChannel(-1, derrumbe, 0);
                }
                jug.picos -= 1;
                jug.puntos += 250;
                mapa[nuevoY][nuevoX] = suelo; // Romper el muro
                matriz_jug();
                mostrarNotificacion("Haz demolido una pared! Picos -1, Puntos + 250", 1000); // Notificación de 2 segundos
            }
        } else if (mapa[nuevoY][nuevoX] == cofre) {
            verificar_cofre();
            matriz_jug();
        } else if (mapa[nuevoY][nuevoX] == enemigo) {
            lucha();
        } else if (mapa[nuevoY][nuevoX] == suelo) {
            matriz_jug();
        }
    }
    else {
        salir();
    }
}

// renderiza al mapa y sigue al jugador (nuevo)
void dibujarMapa() {
    // Obtener tamaño de la ventana
    SDL_GetWindowSize(ventana, &ventanaAncho, &ventanaAlto);

    // Calcular el desplazamiento para centrar al jugador en la pantalla
    int desplazamientoX = (ventanaAncho / 2) - (jug.x * pixeles * zoom + pixeles * zoom / 2);
    int desplazamientoY = (ventanaAlto / 2) - (jug.y * pixeles * zoom + pixeles * zoom / 2);

    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            SDL_Rect roomRect = {
                desplazamientoX + j * pixeles * zoom,
                desplazamientoY + i * pixeles * zoom,
                pixeles * zoom,
                pixeles * zoom
            };

            // Dependiendo de lo que haya en el mapa
            switch (mapa[i][j]) {
                case suelo: // Celda vacía o suelo
                    SDL_RenderCopy(renderer, texturaSuelo, NULL, &roomRect);
                    break;
                case pared: // Celda con pared
                    SDL_RenderCopy(renderer, texturaPared, NULL, &roomRect);
                    break;
                case enemigo: // Celda con un enemigo
                    SDL_RenderCopy(renderer, texturaSuelo, NULL, &roomRect);
                    // Si no se ha asignado una textura para este enemigo
                    if (enemigosAsignados[i][j] == 0) {
                        // Asignar un número aleatorio para seleccionar la textura
                        enemigosAsignados[i][j] = rand() % Cantidad_enemigos_texturas + 1;
                    }
                    // Dibujar la textura del enemigo correspondiente
                    SDL_RenderCopy(renderer, Texturas.enemigos[enemigosAsignados[i][j]], NULL, &roomRect);
                    break;
                case cofre: // Celda con un cofre
                    SDL_RenderCopy(renderer, texturaSuelo, NULL, &roomRect);
                    SDL_RenderCopy(renderer, texturaCofre, NULL, &roomRect);
                    break;
                case salida: // Celda con la salida
                    SDL_RenderCopy(renderer, texturaSuelo, NULL, &roomRect);
                    SDL_RenderCopy(renderer, texturaSalida, NULL, &roomRect);
                    break;
                default:
                    break;
            }
        }
    }

    // Calcular el rectángulo del jugador centrado en la pantalla
    SDL_Rect playerRect = {
        (ventanaAncho - pixeles * zoom) / 2,  // Centro horizontal
        (ventanaAlto - pixeles * zoom) / 2,  // Centro vertical
        pixeles * zoom,                      // Ancho escalado
        pixeles * zoom                       // Alto escalado
    };

    // Dibujar el jugador centrado
    SDL_RenderCopy(renderer, Texturas.jugadores[Personaje], NULL, &playerRect);

    // muestra la info del jugador
    mostrarInfoJugador();

    SDL_RenderPresent(renderer); // Mostrar lo renderizado en la pantalla
}

// hacer zoom al jugador
void AumentarZoom() {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_O] || state[SDL_SCANCODE_KP_PLUS]) {
        if (zoom < 5) {
            zoom++;  // Incrementar el zoom
        }
    }
    if (state[SDL_SCANCODE_I] || state[SDL_SCANCODE_KP_MINUS]) {
        if (zoom > 1) {
            zoom--;  // Decrementar el zoom
        }
    }
}

////------------------------PREMAPA-----------------------------////
// mapa antes de entrar a la torre
char premapa [16][15] = {
    {'*', '*', '*', '*', 'g', '$', '$', '$', '$', '$', 'G', '*', '*', '*', '*'},
    {'*', '*', '*', '*', 'g', '$', '$', 'v', '$', '$', 'G', '*', '*', '*', '*'},
    {'*', 'p', '*', '*', 'g', '$', '$', '$', '$', '$', 'G', '*', '*', '*', '*'},
    {'*', '*', 'R', '*', 'g', '$', '$', '$', '$', 'v', 'G', '*', '*', 'R', '*'},
    {'*', '*', '*', '*', 'g', '$', '$', '$', '$', '$', 'G', '*', '*', '*', '*'},
    {'*', '*', '*', '*', 'g', 'v', '$', '$', '$', '$', 'G', '*', 'r', '*', '*'},
    {'*', '*', '*', '*', 'g', '$', '$', '$', '$', '$', 'G', '*', '*', '*', '*'},
    {'*', 'y', 'u', '*', 'f', 'D', 'D', 'e', 'D', 'D', 'F', '*', 'p', '*', '*'},
    {'*', 'h', 'j', '*', '*', '*', '*', '*', '*', '*', '*', '*', 'P', '*', '*'},
    {'*', 'n', 'm', '*', '*', '*', '*', 'l', '*', 'R', '*', '*', '*', '*', '*'},
    {'*', '*', '*', '*', 'T', '*', '*', '4', '3', '*', '*', '*', '*', '*', '*'},
    {'*', '*', '*', '*', '*', 'l', '*', '6', '8', '*', '*', '*', 'y', 'u', '*'},
    {'*', '*', '*', '*', '1', 'o', '3', '*', '*', '*', '*', '*', 'h', 'j', '*'},
    {'*', '*', 'P', '*', '4', 'o', '5', '*', '*', '*', '*', '*', 'n', 'm', '*'},
    {'*', '*', '*', '*', '6', '7', '8', '*', '*', 'r', '*', '*', '*', '*', '*'},
    {'*', '*', '*', '*', '*', 'T', '*', '*', '*', '*', '*', '*', 'P', '*', '*'}
}; // cam10 = l , T = ar3 , g = lad4, G = lad6 , f = lad1 , F = lad3, D = lad2

// dibuja el fondo de la torre
void renderizarFondo() {
    // Obtener tamaño de la ventana
    int ventanaAncho, ventanaAlto;
    SDL_GetWindowSize(ventana, &ventanaAncho, &ventanaAlto);

    // Posicionamos el fondo en el centro de la pantalla
    SDL_Rect rectFondo = {0, 0, ventanaAncho, ventanaAlto};  // Fondo ocupa toda la pantalla
    SDL_RenderCopy(renderer, texturaFondotorre, NULL, &rectFondo);
}

// para poder moverse
bool esPresuelo(char c) {
    return strchr(presuelo, c) != NULL;  // Busca el carácter en la cadena
}

// matriz premapa
void matriz_jugPREMAZMORRA(){
    jug.y += movY[aux];
    jug.x += movX[aux];
    switch (premapa[jug.y][jug.x]) {
        case '*': premapa[jug.y][jug.x] = '*';
            break;
        case 'l': premapa[jug.y][jug.x] = 'l';
            break;
        case '4': premapa[jug.y][jug.x] = '4';
            break;
        case '3': premapa[jug.y][jug.x] = '3';
            break;
        case '7': premapa[jug.y][jug.x] = '7';
            break;
        case '9': premapa[jug.y][jug.x] = '9';
            break;
        case 'r': premapa[jug.y][jug.x] = 'r';
            break;
        case 'R': premapa[jug.y][jug.x] = 'R';
            break;
        case 'p': premapa[jug.y][jug.x] = 'p';
            break;
        case 'P': premapa[jug.y][jug.x] = 'P';
            break;
        case 'T': premapa[jug.y][jug.x] = 'T';
            break;
        case '1': premapa[jug.y][jug.x] = '1';
            break;
        case '6': premapa[jug.y][jug.x] = '6';
            break;
        case '8': premapa[jug.y][jug.x] = '8';
            break;
        case 'o': premapa[jug.y][jug.x] = 'o';
            break;
        case '5': premapa[jug.y][jug.x] = '5';
            break;
        default:
            break;
    }
}

// muestra titulo en la pantalla principal
void mostrarTitulo() {
    SDL_Color colorB = {255, 255, 255, 255};  // Color del texto principal (blanco)
    SDL_Color colorN = {0, 0, 0, 255};       // Color de la sombra (negro)
    int x = ventanaAncho / 2;
    int y = ventanaAlto / 5;
    char mensaje[60];
    snprintf(mensaje, sizeof(mensaje), "Criptas Algoritmicas");
    char nombre[100];
    snprintf(nombre, sizeof(nombre), "Teruel Axel Josue - Zamparo Luciano Miqueas Gaspar");

    // Cargar fuente
    char rutaEjecutable[MAX_PATH_LENGTH];
    obtenerRutaEjecutable(rutaEjecutable);
    char rutaTexto[2048];

    snprintf(rutaTexto, sizeof(rutaTexto), "%sassets\\fuentes\\arial.ttf", rutaEjecutable);
    TTF_Font* font1 = TTF_OpenFont(rutaTexto, 26);
    if (!font1) {
        printf("Error al cargar la fuente: %s\n", TTF_GetError());
        return;
    }
    
    snprintf(rutaTexto, sizeof(rutaTexto), "%sassets\\fuentes\\fette-unz-fraktur.ttf", rutaEjecutable);
    TTF_Font* font2 = TTF_OpenFont(rutaTexto, 88);
    if (!font2) {
        printf("Error al cargar la fuente: %s\n", TTF_GetError());
        return;
    }

    // Crear superficie para el texto principal
    SDL_Surface* surfacePrincipal = TTF_RenderText_Solid(font2, mensaje, colorB);
    if (!surfacePrincipal) {
        printf("Error al crear superficie del texto principal: %s\n", TTF_GetError());
        TTF_CloseFont(font2);
        return;
    }

    // Crear superficie para la sombra
    SDL_Surface* surfaceSombra = TTF_RenderText_Solid(font2, mensaje, colorN);
    if (!surfaceSombra) {
        printf("Error al crear superficie de la sombra: %s\n", TTF_GetError());
        SDL_FreeSurface(surfacePrincipal);
        TTF_CloseFont(font2);
        return;
    }

    // Crear texturas a partir de las superficies
    SDL_Texture* texturePrincipal = SDL_CreateTextureFromSurface(renderer, surfacePrincipal);
    SDL_Texture* textureSombra = SDL_CreateTextureFromSurface(renderer, surfaceSombra);

    // Obtener dimensiones del texto principal
    int anchoTexto, altoTexto;
    SDL_QueryTexture(texturePrincipal, NULL, NULL, &anchoTexto, &altoTexto);

    int centroX = x - (anchoTexto / 2);

    // Dibujar sombra (ligeramente desplazada)
    int desplazamiento = 5;  // Ajusta el desplazamiento para la sombra
    SDL_Rect rectSombra = {centroX + desplazamiento, y + desplazamiento, anchoTexto, altoTexto};
    SDL_RenderCopy(renderer, textureSombra, NULL, &rectSombra);

    // Dibujar texto principal encima
    SDL_Rect rectTexto = {centroX, y, anchoTexto, altoTexto};
    SDL_RenderCopy(renderer, texturePrincipal, NULL, &rectTexto);

    // Dibujar texto adicional (tu nombre) en la esquina inferior derecha
    SDL_Surface* surfaceNombre = TTF_RenderText_Solid(font1, nombre, colorB);
    SDL_Texture* textureNombre = SDL_CreateTextureFromSurface(renderer, surfaceNombre);
    int anchoNombre, altoNombre;
    SDL_QueryTexture(textureNombre, NULL, NULL, &anchoNombre, &altoNombre);

    SDL_Rect rectNombre = {
        ventanaAncho - anchoNombre - 10,  // Desplazado 10 px desde el borde derecho
        ventanaAlto - altoNombre - 10,   // Desplazado 10 px desde el borde inferior
        anchoNombre,
        altoNombre
    };

    SDL_RenderCopy(renderer, textureNombre, NULL, &rectNombre);

    // Liberar recursos
    SDL_FreeSurface(surfacePrincipal);
    SDL_FreeSurface(surfaceSombra);
    SDL_FreeSurface(surfaceNombre);
    SDL_DestroyTexture(texturePrincipal);
    SDL_DestroyTexture(textureSombra);
    SDL_DestroyTexture(textureNombre);
    TTF_CloseFont(font1);
    TTF_CloseFont(font2);
}

// dibuja la premazmorra y el jugador
void dibujarPREMAZMORRA() {
    // Obtener tamaño de la ventana
    SDL_GetWindowSize(ventana, &ventanaAncho, &ventanaAlto);

    // Ajustar el tamaño de las celdas y el mapa (hacer las celdas más grandes)
    int pixelesCelda = 50; // Tamaño de cada celda (puedes ajustarlo según el tamaño deseado)
    int anchoMapa = 15 * pixelesCelda; 
    int altoMapa = 15 * pixelesCelda;  

    int desplazamientoX = (ventanaAncho - anchoMapa) / 2; 
    int desplazamientoY = ventanaAlto - altoMapa; 

    // Dibujar el fondo
    renderizarFondo(); // Aquí el fondo debería ser renderizado una sola vez (fijo)

    // Dibujar cada celda del mapa
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            SDL_Rect roomRect = {
                desplazamientoX + j * pixelesCelda,  // Posición X
                desplazamientoY + i * pixelesCelda,  // Posición Y
                pixelesCelda,                        // Ancho de la celda
                pixelesCelda                         // Alto de la celda
            };

            // Dependiendo de lo que haya en el mapa, dibujar la textura correspondiente
            switch (premapa[i][j]) {
                case '*':
                    SDL_RenderCopy(renderer, texturaPasto, NULL, &roomRect);
                    break;
                case 'P':
                    SDL_RenderCopy(renderer, texturaPasto, NULL, &roomRect);
                    SDL_RenderCopy(renderer, texturaPiedra2, NULL, &roomRect);
                    break;
                case 'p':
                    SDL_RenderCopy(renderer, texturaPasto, NULL, &roomRect);
                    SDL_RenderCopy(renderer, texturaPiedra1, NULL, &roomRect);
                    break;
                case 'r':
                    SDL_RenderCopy(renderer, texturaPasto, NULL, &roomRect);
                    SDL_RenderCopy(renderer, Texturas.arbusto[0], NULL, &roomRect);
                    break;
                case 'R':
                    SDL_RenderCopy(renderer, texturaPasto, NULL, &roomRect);
                    SDL_RenderCopy(renderer, Texturas.arbusto[1], NULL, &roomRect);
                    break;
                case 'T':
                    SDL_RenderCopy(renderer, texturaPasto, NULL, &roomRect);
                    SDL_RenderCopy(renderer, Texturas.arbusto[2], NULL, &roomRect);
                    break;
                case '1':
                    SDL_RenderCopy(renderer, Texturas.camino[0], NULL, &roomRect);
                    break;
                case '3':
                    SDL_RenderCopy(renderer, Texturas.camino[2], NULL, &roomRect); 
                    break;
                case '4':
                    SDL_RenderCopy(renderer, Texturas.camino[3], NULL, &roomRect);
                    break;
                case '5':
                    SDL_RenderCopy(renderer, Texturas.camino[4], NULL, &roomRect);
                    break;
                case '6':
                    SDL_RenderCopy(renderer, Texturas.camino[5], NULL, &roomRect);
                    break;
                case '7':
                    SDL_RenderCopy(renderer, Texturas.camino[6], NULL, &roomRect);
                    break;
                case '8':
                    SDL_RenderCopy(renderer, Texturas.camino[7], NULL, &roomRect);
                    break;
                case 'l':
                    SDL_RenderCopy(renderer, Texturas.camino[9], NULL, &roomRect);
                    break;
                case 'o':
                    SDL_RenderCopy(renderer, texturaTierra, NULL, &roomRect);
                    break;
                case 'f':
                    SDL_RenderCopy(renderer, Texturas.ladrillo[0], NULL, &roomRect);
                    break;
                case 'D':
                    SDL_RenderCopy(renderer, Texturas.ladrillo[1], NULL, &roomRect);
                    break;
                case 'e':
                    SDL_RenderCopy(renderer, texturaPuerta, NULL, &roomRect);
                    break;
                case 'F':
                    SDL_RenderCopy(renderer, Texturas.ladrillo[2], NULL, &roomRect);
                    break;
                case 'g':
                    SDL_RenderCopy(renderer, Texturas.ladrillo[3], NULL, &roomRect);
                    break;
                case 'v':
                    SDL_RenderCopy(renderer, texturaVentana, NULL, &roomRect);
                    break;
                case '$':
                    SDL_RenderCopy(renderer, Texturas.ladrillo[4], NULL, &roomRect);
                    break;
                case 'G':
                    SDL_RenderCopy(renderer, Texturas.ladrillo[5], NULL, &roomRect);
                    break;
                case 'n':
                    SDL_RenderCopy(renderer, texturaPasto, NULL, &roomRect);
                    SDL_RenderCopy(renderer, Texturas.arbol[0], NULL, &roomRect);
                    break;
                case 'm':
                    SDL_RenderCopy(renderer, texturaPasto, NULL, &roomRect);
                    SDL_RenderCopy(renderer, Texturas.arbol[1], NULL, &roomRect);
                    break;
                case 'h':
                    SDL_RenderCopy(renderer, texturaPasto, NULL, &roomRect);
                    SDL_RenderCopy(renderer, Texturas.arbol[2], NULL, &roomRect);
                    break;
                case 'j':
                    SDL_RenderCopy(renderer, texturaPasto, NULL, &roomRect);
                    SDL_RenderCopy(renderer, Texturas.arbol[3], NULL, &roomRect);
                    break;
                case 'y':
                    SDL_RenderCopy(renderer, texturaPasto, NULL, &roomRect);
                    SDL_RenderCopy(renderer, Texturas.arbol[4], NULL, &roomRect);
                    break;
                case 'u':
                    SDL_RenderCopy(renderer, texturaPasto, NULL, &roomRect);
                    SDL_RenderCopy(renderer, Texturas.arbol[5], NULL, &roomRect);
                    break;
                default:
                    break;
            }
        }
    }

    // dibuja al jugador
    SDL_Rect playerRect = {
        desplazamientoX + jug.x * pixelesCelda,
        desplazamientoY + jug.y * pixelesCelda, 
        pixelesCelda, 
        pixelesCelda
        };

    SDL_RenderCopy(renderer, Texturas.jugadores[Personaje], NULL, &playerRect);

    //dibuja al titulo
    mostrarTitulo();

    SDL_RenderPresent(renderer); // Mostrar lo renderizado en la pantalla
}

//moverse adelante de la torre
void mov_jugPREMAZMORRA() {    
    int nuevoY = jug.y + movY[aux];
    int nuevoX = jug.x + movX[aux];

    if (nuevoY > 15){
        nuevoY -= 1;
    } else if (nuevoX > 15){
        nuevoX -= 1;
    }

    // Si el jugador colisiona con las puertas, activar la entrada
    if (premapa[nuevoY][nuevoX] == 'e') {
        entrar = true;
        quit = false;
    } else if (esPresuelo(premapa[nuevoY][nuevoX])) {
        // Si es suelo, permitir el movimiento
        matriz_jugPREMAZMORRA();
    }
}

// inicializar en la entrada de la torre
void inicializar_jugPREMAZMORRA(){
    jug.y = 13;
    jug.x = 7;
    jug.picos = 0;
    jug.puntos = 0;
    jug.vida = cant_vida;
}

////------------------------PREMAPA-----------------------------////

void mostrarGameover(int jugadorID) {
    // Obtener el tamaño de la ventana
    SDL_GetWindowSize(ventana, &ventanaAncho, &ventanaAlto);

    // Dibujar el fondo (rellena toda la pantalla)
    SDL_Rect fondoRect = {0, 0, ventanaAncho, ventanaAlto};
    SDL_RenderCopy(renderer, texturaPelea, NULL, &fondoRect);

    // Posición del jugador (izquierda del centro)
    SDL_Rect jugadorRect = {
        ventanaAncho / 2.2,          
        ventanaAlto / 2.5,               
        200,                           
        200                         
    };


    // Dibujar el jugador
    if (jugadorID >= 0 && jugadorID < Cantidad_jugadores_texturas) {
        SDL_RenderCopy(renderer, Texturas.jugadores[jugadorID], NULL, &jugadorRect);
    } else {
        printf("Error: ID del jugador fuera de rango.\n");
    }

    SDL_Color blanco = {255, 255, 255, 255};
    char mensajeGameover[70];
    char mensajeSalir[50];

    snprintf(mensajeGameover, sizeof(mensajeGameover), "Game over, no lograste escapar");
    snprintf(mensajeSalir, sizeof(mensajeSalir), "Toca cualquier tecla para salir");

    mostrarTexto(mensajeGameover, ventanaAncho / 2, ventanaAlto / 6, blanco, true);
    mostrarTexto(mensajeSalir, ventanaAncho / 2, ventanaAlto / 4, blanco, true);

    SDL_RenderPresent(renderer);  // Mostrar todo lo renderizado en la pantalla

    SDL_Event evento;
    char boton = '\0';
    while (boton == '\0') {  // El bucle se mantendrá hasta que se presione una tecla
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) {
                exit(0); // Salir del juego si se cierra la ventana
            }

            if (evento.type == SDL_KEYDOWN) {
                boton = evento.key.keysym.sym;
            }
        }
        SDL_Delay(33);  
    }
    
}

void mostrarVictoria(int jugadorID) {
    // Obtener el tamaño de la ventana
    SDL_GetWindowSize(ventana, &ventanaAncho, &ventanaAlto);

    // Dibujar el fondo (rellena toda la pantalla)
    SDL_Rect fondoRect = {0, 0, ventanaAncho, ventanaAlto};
    SDL_RenderCopy(renderer, texturaVictoria, NULL, &fondoRect);

    // Posición del jugador (izquierda del centro)
    SDL_Rect jugadorRect = {
        ventanaAncho / 2.2,          
        ventanaAlto / 2.5,               
        200,                           
        200                         
    };


    // Dibujar el jugador
    if (jugadorID >= 0 && jugadorID < Cantidad_jugadores_texturas) {
        SDL_RenderCopy(renderer, Texturas.jugadores[jugadorID], NULL, &jugadorRect);
    } else {
        printf("Error: ID del jugador fuera de rango.\n");
    }

    SDL_Color blanco = {255, 255, 255, 255};
    char mensajeVictoria[70];
    char mensajePuntos[70];
    char mensajeSalir[50];

    snprintf(mensajeVictoria, sizeof(mensajeVictoria), "Haz Ganado!!");
    snprintf(mensajePuntos, sizeof(mensajePuntos), "Puntos Conseguidos: %d", jug.puntos);
    snprintf(mensajeSalir, sizeof(mensajeSalir), "Toca cualquier tecla para salir");
    

    mostrarTexto(mensajeVictoria, ventanaAncho / 2, ventanaAlto / 7, blanco, true);
    mostrarTexto(mensajePuntos, ventanaAncho / 2, ventanaAlto / 4.5, blanco, true);
    mostrarTexto(mensajeSalir, ventanaAncho / 2, ventanaAlto - 100, blanco, true);

    SDL_RenderPresent(renderer);  // Mostrar todo lo renderizado en la pantalla

    SDL_Event evento;
    char boton = '\0';
    while (boton == '\0') {  // El bucle se mantendrá hasta que se presione una tecla
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) {
                exit(0); // Salir del juego si se cierra la ventana
            }

            if (evento.type == SDL_KEYDOWN) {
                boton = evento.key.keysym.sym;
            }
        }
        SDL_Delay(33);  
    }
    
}

///////sonidooo///////

void cargarMusica() {
    char* basePath = SDL_GetBasePath();
    if (basePath == NULL) {
        printf("No se pudo obtener la ruta base. SDL_Error: %s\n", SDL_GetError());
        return;
    }

    char music_tituloPath[2048];
    snprintf(music_tituloPath, sizeof(music_tituloPath), "%sassets\\sounds\\music\\Pantalla_inicio.mp3", basePath);

    char music_bosquePath[2048];
    snprintf(music_bosquePath, sizeof(music_bosquePath), "%sassets\\sounds\\music\\forest.ogg", basePath);

    char music_masamorraPath[2048];
    snprintf(music_masamorraPath, sizeof(music_masamorraPath), "%sassets\\sounds\\music\\mazmorra.ogg", basePath);

    char music_batallaPath[2048];
    snprintf(music_batallaPath, sizeof(music_batallaPath), "%sassets\\sounds\\music\\pelea.ogg", basePath);

    char ganastePath[2048];
    snprintf(ganastePath, sizeof(ganastePath), "%sassets\\sounds\\music\\win.mp3", basePath);

    char perdistePath[2048];
    snprintf(perdistePath, sizeof(perdistePath), "%sassets\\sounds\\music\\perdiste.ogg", basePath);

    music_titulo = Mix_LoadMUS(music_tituloPath);
    if (music_titulo == NULL) {
        printf("No se pudo cargar la música del título. Mix_Error: %s\n", Mix_GetError());
    }

    music_bosque = Mix_LoadMUS(music_bosquePath);
    if (music_bosque == NULL) {
        printf("No se pudo cargar la música del bosque. Mix_Error: %s\n", Mix_GetError());
    }

    music_masamorra = Mix_LoadMUS(music_masamorraPath);
    if (music_masamorra == NULL) {
        printf("No se pudo cargar la música de la mazmorra. Mix_Error: %s\n", Mix_GetError());
    }

    music_batalla = Mix_LoadMUS(music_batallaPath);
    if (music_batalla == NULL) {
        printf("No se pudo cargar la música de batalla. Mix_Error: %s\n", Mix_GetError());
    }

    ganaste = Mix_LoadMUS(ganastePath);
    if (ganaste == NULL) {
        printf("No se pudo cargar la música de victoria. Mix_Error: %s\n", Mix_GetError());
    }

    perdiste = Mix_LoadMUS(perdistePath);
    if (perdiste == NULL) {
        printf("No se pudo cargar la música de derrota. Mix_Error: %s\n", Mix_GetError());
    }

    SDL_free(basePath);
}

void cargarEfectos() {
    char* basePath = SDL_GetBasePath();
    if (basePath == NULL) {
        printf("No se pudo obtener la ruta base. SDL_Error: %s\n", SDL_GetError());
        return;
    }

    char matarPath[2048];
    snprintf(matarPath, sizeof(matarPath), "%sassets\\sounds\\effects\\machete.wav", basePath);

    char heridoPath[2048];
    snprintf(heridoPath, sizeof(heridoPath), "%sassets\\sounds\\effects\\dead.wav", basePath);

    char serpientePath[2048];
    snprintf(serpientePath, sizeof(serpientePath), "%sassets\\sounds\\effects\\snake-hissing-6092.mp3", basePath);

    char pasosPath[2048];
    snprintf(pasosPath, sizeof(pasosPath), "%sassets\\sounds\\effects\\step_lth33.ogg", basePath);

    char soundcofrePath[2048];
    snprintf(soundcofrePath, sizeof(soundcofrePath), "%sassets\\sounds\\effects\\chest-opening-87569.mp3", basePath);

    char aumpointsPath[2048];
    snprintf(aumpointsPath, sizeof(aumpointsPath), "%sassets\\sounds\\effects\\Power Up.wav", basePath);

    char aumpicosPath[2048];
    snprintf(aumpicosPath, sizeof(aumpicosPath), "%sassets\\sounds\\effects\\weapload.wav", basePath);

    char derrumbePath[2048];
    snprintf(derrumbePath, sizeof(derrumbePath), "%sassets\\sounds\\effects\\Falling Rock.wav", basePath);

    matar = Mix_LoadWAV(matarPath);
    if (matar == NULL) {
        printf("No se pudo cargar el efecto de machete. Mix_Error: %s\n", Mix_GetError());
    }

    herido = Mix_LoadWAV(heridoPath);
    if (herido == NULL) {
        printf("No se pudo cargar el efecto de muerto. Mix_Error: %s\n", Mix_GetError());
    }

    serpiente = Mix_LoadWAV(serpientePath);
    if (serpiente == NULL) {
        printf("No se pudo cargar el efecto de serpiente. Mix_Error: %s\n", Mix_GetError());
    }

    pasos = Mix_LoadWAV(pasosPath);
    if (pasos == NULL) {
        printf("No se pudo cargar el efecto de pasos. Mix_Error: %s\n", Mix_GetError());
    }

    soundcofre = Mix_LoadWAV(soundcofrePath);
    if (soundcofre == NULL) {
        printf("No se pudo cargar el efecto de cofre. Mix_Error: %s\n", Mix_GetError());
    }

    aumpoints = Mix_LoadWAV(aumpointsPath);
    if (aumpoints == NULL) {
        printf("No se pudo cargar el efecto de subida de puntos. Mix_Error: %s\n", Mix_GetError());
    }

    aumpicos = Mix_LoadWAV(aumpicosPath);
    if (aumpicos == NULL) {
        printf("No se pudo cargar el efecto de cargar arma. Mix_Error: %s\n", Mix_GetError());
    }

    derrumbe = Mix_LoadWAV(derrumbePath);
    if (derrumbe == NULL) {
        printf("No se pudo cargar el efecto de derrumbe. Mix_Error: %s\n", Mix_GetError());
    }

    SDL_free(basePath);
}

void liberar_musica(Mix_Music** musica) {
    if (*musica != NULL) {
        Mix_FreeMusic(*musica);
        *musica = NULL;
    }
}

/// @brief 
/// @param
/// @return 

// programa principal
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    system ("cls");
    srand ( time (NULL) );
    initSDL();
    cargar_texturas(renderer);
    Mix_OpenAudio (44100, MIX_DEFAULT_FORMAT, 2, 2048);
    cargarMusica();
    cargarEfectos();

    Personaje = rand() % Cantidad_jugadores_texturas;
    
    if (music_titulo != NULL){
        Mix_PlayMusic (music_titulo, 0);
    }

    //pantalla_prejuego() ***abortaado***;
    Mix_HaltMusic();
    liberar_musica (&music_titulo);

    inicializar_jugPREMAZMORRA();
    entrar = false;
    zoom = 2;

    SDL_Event evento;
    quit = true;

    if (music_bosque != NULL){
        Mix_PlayMusic (music_bosque, -1);
    }

    while (!entrar) {
        while (SDL_PollEvent(&evento) != 0) {
            if (evento.type == SDL_QUIT) {
                entrar = true;
            }
        }

        freopen("nul", "w", stderr);

        detectar_movimiento();
        mov_jugPREMAZMORRA();
        aux = 5;

        // Dibujar premapa y jugador
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Fondo negro
        SDL_RenderClear(renderer);

        dibujarPREMAZMORRA();
        SDL_RenderPresent(renderer);
        SDL_Delay(150);  // Controlar la velocidad
    }

    Mix_HaltMusic();
    liberar_musica (&music_bosque);

    if (!quit) {

        inicializar_jug();  // Reinicializar jugador en la mazmorra
        generar_mapa();     // Generar el mapa de la mazmorra
        stage = 1;          // Iniciar en el stage 1

        if (music_masamorra != NULL){
            Mix_PlayMusic (music_masamorra, -1);
        }

        while (!quit) {
            while (SDL_PollEvent(&evento) != 0) {
                if (evento.type == SDL_QUIT) {
                    quit = true;
                }
            }

            detectar_movimiento();
            mov_jug();  // Movimiento en la mazmorra
            aux = 5;

            // Dibujar mazmorra y jugador
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Fondo negro
            SDL_RenderClear(renderer);

            dibujarMapa();
            SDL_RenderPresent(renderer);
            AumentarZoom();

            SDL_Delay(150);  // Controlar la velocidad

            // Condiciones de finalización
            if (stage == 4) {
                Mix_HaltMusic();
                liberar_musica (&music_batalla);
                liberar_musica (&music_masamorra);
                if (ganaste != NULL){
                    Mix_PlayMusic (ganaste, 0);
                }
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Fondo negro
                SDL_RenderClear(renderer);
                mostrarVictoria(Personaje);
                SDL_Delay(1000);
                break;
            }
            if (stage == 0) {
                Mix_HaltMusic();
                liberar_musica (&music_batalla);
                liberar_musica (&music_masamorra);
                if (perdiste != NULL){
                    Mix_PlayMusic (perdiste, 0);
                }
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Fondo negro
                SDL_RenderClear(renderer);
                mostrarGameover(Personaje);
                SDL_Delay(1000);
                break;
            }
        }
    }
    liberar_musica (&perdiste);
    liberar_musica (&ganaste);
    // Limpieza final
    cleanupSDL();
    return 0;
}