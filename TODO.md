# TODO

## TODO:
- [ ] Arbitrary precision decimal arithmetic
- [ ] The ENTIRE spreadsheet backend
	- [ ] Create a way of keeping track of which sheet cells have which values
	- [ ] Create types
		- [ ] start with strings only
		- [ ] Auto-detect types
			- [ ] visible way to show you what type you have
			- [ ] make type editing
		- [ ] 2nd. Numbers
		- [ ] 3rd and beyond. Every other type
	- [ ] Formulas
		- [ ] Create variable (sytax: {variable_name})
		- [ ] Refrence cell (row:column, e.g. A30:D3)
			- [ ] Add option to switch lettered columns to numbered columns
			- [ ] add cell refrence function (**OPTIONAL**)
		- [ ] Figure out how to evaluate formulas
			- [ ] GPU accelerated formulas (**DO AT THE END OF THE PROJECT**)
	- [ ] Extrapolation
- [ ] The ENTIRE frontend
	- [ ] Display grid
	- [ ] Edit cells
		- [ ] Edit cell type
	- [ ] Sorting
	- [ ] Extrapolation

## Jacob
Raylib?
  - Draw a grid
  - Render text inside grid cells
  - Figure out what a GPU or a shader is or something

## Vikram
- [ ] create cell storage system
	1. litterally just a 2d array of strings (NOT NULL TERMINATED)
	2. Translate cell names like ZB15 into indexes (i.e. (28, 15))
	3.
	4. Ability to expand the size of the 2d array

```c
int main(void) {
    // 5x4 array
    int *arr = malloc(sizeof(int)*5*4);

struct array {int *data; int width; int height;};

int at(struct array arr,int x,int y,) {
    return arr.data[(y*arr.width) + x];
}
/*
arr = [0 * wid * hgt]
x = 20
y = 10
arr[(y * wid) + x]
*/

}
```
## Language
Write in **C**, Port to **Rust** when done
