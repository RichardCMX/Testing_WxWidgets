# Testing_WxWidgets
This repository contains all the experiments and GUI practices I work on.

## Requirements



## Projects index

Here is the list of projects already completed:

- [VentanaBasica](#VentanaBasica)
- [Programa2.cpp](#programa2cpp)
- [Programa3.cpp](#programa3cpp)
- [Programa4.cpp](#programa4cpp)
- [Programa5.cpp](#programa5cpp)
- [Depuración](#depuración)
  - [Tipos de errores en la depuracion](#tipos-de-errores-en-la-depuración)
  - [Importancia de la depuracion](#importancia-de-la-depuración)
- [Conceptos básicos y detalles importantes en depuración](#Conceptos-básicos-y-detalles-importantes-en-depuración)
    - [BreakPoints](#break-points)
    - [Stepping](#stepping)
    - [Inspección de variables y ventanas](#inspección-de-variables-y-ventanas)
    - [CallStack](#call-stack-pila-de-llamadas)
- [GNU debugger](#gnu-debugger-gdb)
- [Valgrind](#valgrind)
    - [MemCheck](#memcheck)
    - [Helgrind](#helgrind)
- [Sanitizers](#sanitizers)
    - [Address Sanitizer](#address-sanitizer-asan)
    - [Thread Sanitizer](#thread-sanitizer-tsan)

## VentanaBasica

VentanaBasica is my first interaction with the entire library on my University programming class "Estructuras Abstractas de Datos y Algoritmos para Ingeniería", here I designed a really basic window with two buttons, one with a flat color and the other one using a random image from my desktop. 

```bash
g++ -g -o programa.exe programa.cpp
gdb programa.exe
```
Se muestra una imagen del debugger en acción:

![GBDrun2](images/GDBrun2.png)