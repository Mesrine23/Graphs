/* This code is from Chapter 4 of the book "Algorithms in C" by Robert Sedgewick. */

typedef char Item;

typedef struct STACKnode* link;

struct STACKnode
{
  Item item;
  link next;
};
