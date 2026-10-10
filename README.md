# Stock Management in C

A console inventory-management project using linked data structures to organize products and categories, load stock records and save updates to a file.

## Repository guide

| Path | Role |
| --- | --- |
| [src/main.c](src/main.c) | Original command-line application entry point |
| [src/projet.c](src/projet.c) and [src/projet.h](src/projet.h) | Course application and linked-list operations |
| [src/stock.c](src/stock.c) and [include](include/) | Separate stock-library implementation |
| [tests](tests/) | Stock-library tests |
| [docs](docs/) | Project presentation |

The original application and the stock library are two implementation paths. Their APIs are different; combining the application entry point with the library does not produce a valid application build.

## Work with the project

Inspect `main.c` and `projet.h` to follow the original application's load, interactive management and save sequence. The application expects an input filename as its command-line argument.

For the separate library, use:

```sh
make test
```

The existing application target in the Makefile needs reconciliation with the original entry point before it can be advertised as a working build command. Library tests do not establish that the interactive application builds or behaves correctly.
