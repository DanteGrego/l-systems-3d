# L-systems paramétricos en 3D

Generador de L-systems en C que dibuja plantas y fractales en tres dimensiones con raylib.

## Características

- Reglas paramétricas y condicionales.
- Parser de expresiones propio: conversión de infija a postfija con una pila y evaluación con variables.
- Tortuga 3D con giros en tres ejes, grosor y color variables, y pila de estados para las ramas.
- Cámara libre para recorrer el resultado.

## Reglas

```
F(s) -> F(s;)F(s;)!;[-&F(s/1.2;)][+^F(s/1.2;)]
```

Una regla con condición tiene la forma `A(x) : x > 1; -> ...`. Cada expresión termina con `;`. Operadores: `+ - * / ^ < >` y `_` (igualdad).

| Símbolo | Acción |
|---|---|
| `F`, `G` | Avanzar dibujando |
| `+`, `-` | Giro en yaw |
| `&`, `^` | Giro en pitch |
| `/`, `\` | Giro en roll |
| `[`, `]` | Guardar y recuperar el estado |
| `#`, `!` | Aumentar y disminuir el grosor (o fijarlo, con un parámetro) |
| `;`, `,` | Aumentar y disminuir el tono (o fijarlo, con un parámetro) |

El axioma, las reglas y la cantidad de iteraciones se definen en `main.c`.

## Compilación (Windows, GCC)

El repositorio incluye raylib 5.5 compilada para 32 bits. Con un GCC de 64 bits, reemplazar `lib` por la carpeta de una raylib de 64 bits.

```
gcc main.c main/*.c utils/*.c -o lsystem.exe -I include -L lib -lraylib -lopengl32 -lgdi32 -lwinmm
```

## Controles

Mouse para mirar; `W`, `A`, `S`, `D` para moverse; `Q` y `E` para bajar y subir; `Esc` para salir.
