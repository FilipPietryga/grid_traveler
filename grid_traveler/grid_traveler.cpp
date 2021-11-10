#include <iostream>

//The Program should present the mechanism
//of tabularization which is a technique
//used within the dynamic programming style

//ISSUES:
//the program has some non-deterministic issues
//probably having to do with moving the array objects

//create Flat 2D array so that
//we can work with it using
//raw pointers
int* createFlat2DTable(int width, int height, int init) {

    //copy the array (we apply
    //the somewhat "functional" paradigm
    //meaning that we dont want to change
    //the passed array literally but 
    //instead create a new one and
    //return it)
    int* table = new int[width * height];

    //fill the tables with zeros
    for (int i = 0; i < width * height; i++) {
        table[i] = 0;
    }
    return table;
}

//flatten the x,y so that we can use
//the coords as the index for the table
int flattenTheIndices(int width, int x, int y) {
    return width * y + x;
}

//set value at coord in the table
int* addValInFlat2DTable(int* table, int width, int height, int x, int y, int value) {
    
    //create the placeholder
    int* copy = new int;

    //copy the table
    memcpy(copy, table, width * height * sizeof(int));
    copy[flattenTheIndices(width, x, y)] += value;

    //return the new table
    return copy;
}

//used for debbuging purposes
void printTable(int* table, int width, int height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            std::cout << table[flattenTheIndices(width, x, y)] << " ";
        }
        std::cout << std::endl;
    }
    //extra endline
    std::cout << std::endl;
}

//find in how many ways can we go through
//a grid with dimentions of [width, height] 
//from the left-most upper cell to the 
//right-most bottom cell
int gridTraveler(int width, int height) {

    //create the table for tabelarization
    int* table = createFlat2DTable(width, height, 0);
    printTable(table, width, height);

    //set the [1,1] of the table to 1
    //because of the assertion
    //that [0,X] or [X,0] are 0
    //and [1,1] is 0
    table = addValInFlat2DTable(table, width, height, 1, 1, 1);
    printTable(table, width, height);

    //proceed using tabelarization
    for (int y = 1; y < height; y++) {
        for (int x = 1; x < width; x++) {
            int value = table[flattenTheIndices(width, x, y)];
            if (x + 1 < width) {
                table = addValInFlat2DTable(table, width, height, x + 1, y, value);
            }
            if (y + 1 < height) {
                table = addValInFlat2DTable(table, width, height, x, y + 1, value);
            }
            printTable(table, width, height);
        }
        printTable(table, width, height);
    }

    //result at the last cell
    return table[flattenTheIndices(width, width - 1, height - 1)];
}

int main()
{
    int result = gridTraveler(4,4);
    
    std::cout << "You could pass the grid in " << result << " different ways.";
}