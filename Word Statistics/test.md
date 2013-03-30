## Readme

### Data Structures


The overarching design philosophy I have is object-oriented in
perspective. I designed my `struct`s to behave like objects, with the
following properties:

-   Every structure is contained in its own header file.

-   Every structure has helper functions that handle allocating of
    memory.

-   Every structure has helper functions which “put” and “get”
    references.

This allowed the main function to work as a *tour de force*, where
nothing is defined and everything is used.

The short hand version of my implementation is: a balanced character BST
of ‘a’ through ‘z’ with a nested BST of case insensitive words with a
nested linked list of case sensitive word.

#### `struct char_tree_node`

This is my foundational data structure. It is a binary search tree which
is loaded with character ‘a’ through ‘z’. They’re loaded in such a way
that this particular tree ends up being balanced. Here’s a
representation of the tree after the function `bld_char_tree` is called:

##### `char letter`

Represents the character which this node is responsible for. Every word
in the subtree, defined later in this document, will begin with this
character.

##### `char_tree_node *left, *right`

These represent the edges between two nodes, forming a tree structure.

##### `word_tree_node *words`

This points to a struct which is another nested binary search tree.

#### `struct word_tree_node`


Every character node has a word node. A word node is the principal store
for information of the statistic of a document. Any given word tree is
limited to words which begin with a single character, by virtue of its
“parent” structure, the character tree.

In order to make processing simple, the word tree is stored in its own
file with a header which defines convenience functions for allocation,
insertion, and retrieval.

##### `char *case_insensitive_word`

This string stores the word that this node is representing. It is case
insensitive in that it may change the case when it is inserted or it may
not, but when used you should disregard any case information.

As the spec dictates, this stores any sequence of letters and digits
that starts with a letter, followed by 0 or more letters and/or digits.

##### `int total_instances`

This integer is the number of time that `case_insensitive_word` has
appeared in total. It is case-insensitive instances.

When outputted, this will be called “Total No. Occurrences.”

##### `struct word_tree_node *left, *right`

So as to create a tree structure, these pointers represent a left and
right, where every sub-tree to the left contains values strictly smaller
than the root, and everything to the right is strictly greater than
root.

The “number” of a string is determined lexicographically.

##### `int cases_instances`

Closely linked with the `struct` defined below, this number represents
the number of case-sensitive variations on the word this node represents
exist in the document.

When outputted, this will be called “No. Case-Sensitive Versions.”

##### `struct word_list_node *case_sensitive_list`

This is a singly-linked-list which is defined below.

#### `struct word_list_node`


Every character has a node in a tree. Every character node has a tree of
case-insensitive words. Every case-insensitive node has a case-sensitive
singly-linked-list.

##### `char *case_sensitive_word`

A string which is case-sensitive, used to compare against when deciding
if this is a new or previously discovered case instance.

##### `struct word_list_node *next`

A linked-list needs a pointer to the next element in the list.

### Big-O Analysis


#### Space complexity


Where $r$ is the number of words in a text, $n_0, n_1, ... n_t$
represents the set of case-insensitive words, and $m_0, m_1, ..., m_t$
represents the number of case-sensitive variations on each corresponding
$t$ word.

-   The character tree requires $26 \times 8$ bytes for the characters.

-   Each word tree node’s case-insensitive string requires the number of
    bytes of each of the $n$ words.

-   Each word list node’s case-sensitive string requires the number of
    bytes of each of the $m$ case-sensitive variations.

The “specific” space is:

$$O \left(\sum_{0}^r n_r + m_r \right)$$

The worst case is a double-nested linear time, along with every single
case being unique, resulting in:

$$O(n^3)$$

#### Time complexity


##### Worst case

Where we count assignments and steps with $n$ words:

-   If every word in the document begins with a letter at the bottom of
    the character tree, there will be +4 assignments to get the
    character. Say every word begins with the same one.

-   If every word is lexicographically greater than the previous one or
    lexicographically less the previous one, you end up with a
    “linked-list.”

-   If every word is a unique case-variation, you have to step through
    the whole-linked list every time.

$$O(n^3)$$

##### Best case

-   Every word begins with ‘p’

-   The nested word tree ends up being balanced

-   Every case is the same

This makes the runtime equal to the best case of insert on a BST. Where
$n$ is the number of words:

$$O(\log(n))$$

### Challenges


#### Functionality

The functionality of the program was difficult to write in that it was a
totally new language for me. This was ameliorated somewhat because I
have developed for iOS in Objective-C, in a version of iOS before
automatic reference counting.

Admittedly, I’m still uncertain about what the proper way to both keep
declarations and operations separate (as the C90 standard dictates), and
still keep complex operations from being complicated one-liners.

#### Coding Style and Design

I struggled with what the best way to use C as C is. What I mean is my
solution pastes onto functional programming an object-oriented mindset.
I am still uncertain as to what veteran C programmers would do to solve
this problem. I think that this will be lessened as the semester
continues. In this one experience, however, I have come to like C more
than Java. Objective-C holds a special place in my heart, however.
