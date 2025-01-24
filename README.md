# Pipex

## Resumen del proyecto

El proyecto *Pipex* es una implementación personalizada en C de un mecanismo esencial de UNIX: los *pipes*. El objetivo principal es permitir la comunicación entre procesos mediante la redirección de entrada y salida, replicando el comportamiento de comandos comunes de shell como `|`.

Este proyecto representa una oportunidad para demostrar conocimientos en:

- Programación en C.
- Manejo de procesos, incluyendo llamadas al sistema como `fork`, `execve` y `pipe`.
- Redirección de entrada y salida.
- Gestión eficiente de memoria y tratamiento de errores.

## Funcionalidad principal

El programa ejecuta la siguiente lógica:

```bash
./pipex archivo1 comando1 comando2 archivo2
```

Deberá comportarse de forma equivalente al siguiente comando de shell:

```bash
< archivo1 comando1 | comando2 > archivo2
```

### Ejemplos

1. Ejecución de un conteo de líneas:
   ```bash
   ./pipex infile "ls -l" "wc -l" outfile
   ```
   Equivalente a:
   ```bash
   < infile ls -l | wc -l > outfile
   ```

2. Uso de `grep` y conteo de palabras:
   ```bash
   ./pipex infile "grep a1" "wc -w" outfile
   ```
   Equivalente a:
   ```bash
   < infile grep a1 | wc -w > outfile
   ```

## Funciones permitidas

Las siguientes funciones están permitidas y son utilizadas en la implementación:

- Manejo de archivos: `open`, `close`, `read`, `write`.
- Gestión de memoria: `malloc`, `free`.
- Manejo de errores: `perror`, `strerror`.
- Llamadas al sistema para procesos: `access`, `dup`, `dup2`, `execve`, `exit`, `fork`, `pipe`, `unlink`, `wait`, `waitpid`.
- 
## Estructura del proyecto

- **Archivos entregados:**
  - `Makefile`: Compila el proyecto con las reglas habituales (`all`, `clean`, `fclean`, `re`).
  - Archivos fuente (`*.c`) y de cabecera (`*.h`).

- **Normas del proyecto:**
  - No debe haber fugas de memoria (*leaks*).
  - Todos los errores deben ser manejados adecuadamente.
  - La implementación debe cumplir con la "Norma" establecida.

