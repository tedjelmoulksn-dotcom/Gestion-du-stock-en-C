# Inventory Management in C

Academic inventory application using doubly linked lists to organise categories and products. It supports editing, sorting and CSV persistence.

## Repository guide

| Location | Contents |
|---|---|
| [src/](src/) | Application entry point, original implementation and stock library |
| [include/](include/) | Stock-library public interface |
| [tests/](tests/) | Stock-library tests |
| [docs/](docs/) | Project presentation |
| [versions_intermediaires/](versions_intermediaires/) | Earlier development snapshots |

## Getting started

The current application entry point uses `projet.c`:

```bash
gcc src/main.c src/projet.c -o gestion_stock
./gestion_stock path/to/stock.csv
```

Supply an existing CSV file in `category;product;price;quantity;` format. The stock library and its tests are a separate implementation; the current Makefile application target needs reconciliation with the uploaded entry point.

## Project context

Developed with Sarah Dahmoun at Sup Galilée. Earlier snapshots are kept separately to preserve the development history.
