# Stock Management System - C

A comprehensive inventory management system built in C, featuring object-oriented design patterns with structures and pointers for efficient stock tracking and organization.

## 📋 Overview

This project implements a robust stock management application using C programming language. It leverages structures and pointers to create a maintainable, scalable inventory system capable of handling product categories, pricing, and dynamic quantity tracking.

## ✨ Features

- **Product Management**: Create, update, and delete product entries
- **Stock Tracking**: Monitor inventory levels and stock availability
- **Sorting Capabilities**: 
  - Sort products alphabetically by name
  - Sort products by price (ascending and descending)
  - Sort products by available quantity
- **Modular Design**: Organized function definitions and headers
- **Efficient Memory Management**: Utilizes pointers for dynamic memory allocation
- **Doubly Linked Lists**: Navigate products forward and backward through the list

## 🛠️ Technology Stack

- **Language**: C
- **Paradigm**: Structured programming with OOP principles
- **Memory Management**: Manual memory management with pointers and dynamic allocation
- **Data Structures**: Doubly linked lists for product and category management

## 📦 Project Structure

```
├── README.md                    # Project documentation
├── codes                        # Main program entry point
├── fonction definition.c        # Function implementations for sorting and display
├── fonction_for_main.h          # Header file with function prototypes and structures
├── gestion_de_stock.h           # Stock management structure definitions (duplicate of fonction_for_main.h)
```

## 📄 File Descriptions

| File | Purpose |
|------|---------|
| `codes` | Main program entry point with application logic and initialization |
| `fonction definition.c` | Implementation of sorting functions (alphabetical, by price, by quantity) and product display |
| `fonction_for_main.h` | Header file with function prototypes and data structure definitions |
| `gestion_de_stock.h` | Stock management structure definitions |

## 🚀 Getting Started

### Prerequisites

- GCC compiler or compatible C compiler (tested with GCC)
- Standard C library
- Linux/MacOS/Windows with a terminal

### Installation

```bash
git clone https://github.com/tedjelmoulksn-dotcom/Gestion-du-stock-en-C.git
cd Gestion-du-stock-en-C
```

### Compilation

```bash
gcc -o gestion_stock codes "fonction definition.c"
```

### Usage

```bash
./gestion_stock
```

## 💾 Features Overview

### Sorting Algorithms
- **Alphabetical Sorting**: Sort products by name using `qsort()`
- **Price Sorting**: 
  - Ascending order: Sort products from lowest to highest price
  - Descending order: Sort products from highest to lowest price
- **Quantity Tracking**: Monitor available stock quantities, sorted from highest to lowest

### Data Structures

**PRODUIT** - Represents a single product:
- `nom_produit` - Product name
- `prix_produit` - Product price (float)
- `quantite_produit` - Available quantity (int)

**NODE_P** - Node in the doubly linked list of products:
- Stores a PRODUIT and pointers to next/previous nodes

**CATEGORIE** - Represents a product category:
- `nom_categorie` - Category name
- `list_produits` - Pointer to linked list of products

### Memory Management
- Dynamic memory allocation for nodes using `malloc()`
- Proper pointer linking for bidirectional traversal
- Products organized in doubly linked lists

## 📝 License

This project is provided as-is for educational and personal use.

## 👤 Authors

**Sinacer Tedj El Moulk**  
**Dahmoun Sarah**

---

For questions or contributions, please feel free to reach out or submit an issue.
