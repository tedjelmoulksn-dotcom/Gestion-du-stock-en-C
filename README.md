# C Inventory Structures — Pointers and Memory Management

An academic C project using an inventory example to explore dynamic allocation, doubly linked data structures, pointer-based sorting and list reconstruction.

**C · Heap Allocation · Structs · Pointer Indirection · Linked Lists · Function Pointers · qsort**

The technical focus is the representation and manipulation of data in memory. Product names, prices and quantities provide the application context for implementing the underlying structures.

## Project Overview

| Item | Details |
|---|---|
| Context | First-year Instrumentation engineering coursework |
| Authors | Tedj El Moulk Sinacer and Sarah Dahmoun |
| Execution model | Hosted C console application using the standard library |
| Demonstration | One category with two dynamically allocated product nodes |
| Implemented operations | Display; alphabetical, price and quantity sorting |
| Repository status | Historical source requiring build and type-consistency corrections |

The code demonstrates skills relevant to embedded C: understanding object lifetime, memory ownership, pointer aliasing, bounded storage and type-safe interfaces. It has no microcontroller target, peripheral driver, RTOS integration or measured real-time guarantees.

## Technical Scope

- Define records using `struct` and `typedef`.
- Allocate a list descriptor and nodes with `malloc()`.
- Link nodes using `next` and `previous` pointers.
- Maintain explicit `first` and `last` endpoints.
- Traverse a linked structure through pointer dereferencing.
- Create a temporary array of pointers to existing nodes.
- Pass comparison callbacks to `qsort()`.
- Rebuild list links in the selected order without copying entire product records.

The fixed example keeps attention on node allocation, pointer sorting and relinking. Category/product fields supply the input data for these operations.

## Data Model

| Type | Contents | Role |
|---|---|---|
| `PRODUIT` | Name array, `float` price, `int` quantity | Product payload |
| `NODE_P` | Product payload and two link pointers | Intended doubly linked product node |
| `LISTE_P` | First and last node pointers | Product-list descriptor |
| `CATEGORIE` | Name array and product-list pointer | Category record |
| `NODE_C`, `LISTE_C` | Category-node and list definitions | Declared category-list structures; unused by the example |

The headers use `SIZE = 200` for the fixed name arrays. The implementation separately defines `SIZE = 500` for the temporary sorting array. These represent different capacities and should use distinct names.

### Memory Layout and Ownership

The example allocates:

- one `LISTE_P` descriptor on the heap;
- two `NODE_P` objects on the heap.

The category and initialization records are local variables in `main()`. Product fields are copied into the allocated nodes; the category holds a pointer to the allocated list.

Pointers in the temporary sorting array alias the original nodes. Sorting changes the order of those pointers and subsequent link assignments; it does not relocate or reallocate the nodes.

Actual object sizes depend on integer/pointer widths, alignment and padding. Use `sizeof` in the selected build to establish the descriptor, node and temporary-array footprint.

## Allocation and Link Initialization

The demonstration creates a category named `fruits`, with `Banane` and `Orange` records. It manually initializes the list:

1. Allocate the descriptor and set its endpoints to `NULL`.
2. Allocate the first node and copy its product fields.
3. Set both endpoints to the first node.
4. Allocate the second node.
5. Link the first node forward to the second and the second backward to the first.
6. Update the last-node pointer.

The example makes allocation and linking explicit. To complete that lifecycle, check each allocation before dereferencing it and release every node and descriptor through a defined cleanup path.

## Pointer-Based Sorting

### Algorithm Used by the Source

Each sorting function follows the same broad sequence:

1. Traverse the product list to count nodes.
2. Traverse again and store node addresses in a local pointer array.
3. Sort that array using `qsort()`.
4. Assign the list endpoints from the sorted array.
5. Reconnect neighbouring nodes.
6. Print the reordered list.

| Function | Intended order |
|---|---|
| `tri_alphabetique()` | Product name, ascending |
| `tri_prix_croissant()` | Price, ascending |
| `tri_prix_decroissant()` | Price, descending |
| `tri_quantite_dispo()` | Quantity, descending |

The descending functions reverse the sorted pointer order when rebuilding the links.

### Comparator Indirection

The array contains `NODE_P *` elements. A `qsort` callback receives the address of an array element through `const void *`, requiring an additional level of indirection to recover the node pointer.

The source uses:

```c
NODE_P *produitA = *(NODE_P **)a;
NODE_P *produitB = *(NODE_P **)b;
```

The name comparator then calls `strcmp()`; the quantity comparator explicitly returns a negative value, zero or a positive value.

A const-aware expression for a future cleanup would be:

```c
const NODE_P *product = *(NODE_P * const *)element;
```

This is explanatory guidance, not a modification to the stored source.

### Price Comparator

The current price comparator returns a floating-point subtraction through an `int` return type. Small nonzero differences can become zero after conversion, giving an incorrect ordering.

An illustrative replacement is:

```c
return (price_a > price_b) - (price_a < price_b);
```

Input-domain rules would also need to define how invalid floating-point values are handled. For monetary data, a documented integer smallest-unit representation is another possible design choice.

## List Invariants

A correct doubly linked implementation should preserve:

| Condition | Expected invariant |
|---|---|
| Empty list | `first == NULL` and `last == NULL` |
| Nonempty list | `first->previous == NULL` |
| Nonempty list | `last->next == NULL` |
| Forward neighbour exists | `node->next->previous == node` |
| Backward neighbour exists | `node->previous->next == node` |

The ascending sorting routines do not explicitly clear the new first node's `previous` link. The forward order may appear correct while the backward chain retains a stale link.

The type declarations also need repair: the node typedefs are anonymous, while their link members refer to `struct _NODE_P` and `struct _NODE_C`. Those tags do not identify the anonymous typedef objects.

The intended product-node declaration would be:

```c
typedef struct _NODE_P {
    PRODUIT produit;
    struct _NODE_P *next;
    struct _NODE_P *previous;
} NODE_P;
```

This illustrates the required self-referential type relationship.

## Resource and Embedded-C Considerations

| Mechanism | Engineering consideration |
|---|---|
| Dynamic node allocation | Allocation failure, allocator overhead and explicit ownership must be handled |
| Linked traversal | Access follows pointers; storage is not contiguous |
| Local pointer array | Fixed stack capacity must be checked before filling it |
| Standard-library sorting | Timing and auxiliary-memory behaviour depend on the library implementation |
| Fixed name arrays | Copy operations need length constraints and null-termination guarantees |
| In-place relinking | Every endpoint and neighbour relationship must remain consistent |
| Console output | Standard I/O is part of this hosted demonstration, not a peripheral abstraction |

The temporary array reserves 500 pointers regardless of the actual list size: its array storage alone is `500 × sizeof(NODE_P *)` bytes. Its usable capacity is not enforced in the source.

There are two linear passes before sorting and one linear relinking pass afterward. The total sort cost also depends on the platform's `qsort()` implementation; no portable worst-case timing or real-time bound is asserted.

A microcontroller adaptation could evaluate statically allocated nodes or a fixed-capacity pool, with explicit failure handling. That adaptation is a proposed direction, not an existing feature.

## Repository Structure

| File | Contents |
|---|---|
| [`codes`](codes) | Main function and sample-list initialization; filename has no `.c` extension |
| [`fonction definition.c`](fonction%20definition.c) | Display, comparator and sorting implementations |
| [`fonction_for_main.h`](fonction_for_main.h) | Structures and function declarations |
| [`gestion_de_stock.h`](gestion_de_stock.h) | Near-duplicate structures and declarations |
| `README.md` | Technical overview and implementation review |

French identifiers are retained in the documentation to match the historical source.

## Build Status

The previous README's compile command does not build the stored project as-is.

Current blockers include:

- both source files include `projet.h`, which is absent;
- the main source is stored as `codes`, without a C extension;
- the header declares `tri_alphabetique(CATEGORIE)`, but its implementation expects `CATEGORIE *`;
- the call in `main()` passes the category by value;
- node-link types are inconsistent with their typedefs;
- `SIZE` is reused for different capacities.

### Recommended Restoration

1. Choose one canonical header and repair the self-referential node tags.
2. Update source includes to use that header.
3. Align the alphabetical-sort declaration, implementation and call.
4. Rename `codes` to `main.c`, or explicitly select the C input language.
5. Replace ambiguous capacity macros with separately named constants.
6. Add allocation checks, cleanup and list-boundary handling.

After those corrections, a suggested warning-enabled GCC build would be:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -g \
    main.c "fonction definition.c" -o inventory_demo
```

Use this command after applying the source-layout and API corrections listed above. Compiler diagnostics then provide the first check of type consistency before exercising the list operations.

## Implementation Review

| Finding | Consequence | Proposed correction |
|---|---|---|
| Missing header and inconsistent API | Build failure | Consolidate one header and match function signatures |
| Anonymous node types with unrelated struct tags | Incompatible pointer types | Use tagged self-referential structures |
| Unchecked `malloc()` | Possible null-pointer dereference | Return an explicit allocation error |
| No `free()` cleanup | Incomplete ownership lifecycle | Release nodes and list descriptor |
| Unbounded `strcpy()` | Generalized inputs could exceed name capacity | Define checked copy and length rules |
| Empty-list assumptions | Printing and sorting can dereference invalid data | Handle zero and one-node cases explicitly |
| Unchecked 500-element sorting buffer | Larger lists can overwrite stack storage | Enforce capacity or choose another algorithm |
| Stale backward endpoint after ascending sort | Doubly linked invariants can fail | Clear the new first node's backward link |
| Floating-point subtraction returned as `int` | Distinct prices may compare equal | Use relational comparisons |
| Repeated sorting implementations | Fixes need to be duplicated | Factor out pointer collection and relinking |

## Suggested Verification

List validation should inspect both traversal directions after every reorder. A correct forward printout alone is insufficient: endpoint null links, reciprocal neighbour links and deallocation must remain consistent for the data structure to be reusable.

A future validation pass should cover:

- empty, singleton and multi-node lists;
- duplicate names and equal prices;
- fractional price differences;
- capacity boundaries and allocation failures;
- forward/backward consistency after repeated sorts;
- complete deallocation.

On a compatible host, compiler warnings and memory diagnostics such as AddressSanitizer and UndefinedBehaviorSanitizer can support that work. Inspect diagnostics together with the list invariants and allocation/release paths.

## Authors and Licensing

Developed by **Tedj El Moulk Sinacer** and **Sarah Dahmoun**.

No explicit project licence is included in the repository.
