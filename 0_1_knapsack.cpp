// 0-1 Knapsack Problem (Dynamic Programming)
#include <iostream>

using namespace std;

#define MAX_ITEMS 100  
#define MAX_WEIGHT 100 

int B[MAX_ITEMS + 1][MAX_WEIGHT + 1]; // DP table to store max profit values; 2D Array

// Knapsack function to compute the maximum profit
void knapsack(int n, int W, int weights[], int profits[]) 
{
    
    // Initialize the first row (0 items) and first column (0 weight capacity) to 0
    for (int w = 0; w <= W; w++) 
    {
        B[0][w] = 0;
    }
    for (int i = 1; i <= n; i++) 
    {
        B[i][0] = 0;
    }

    // Build the DP table using bottom-up approach
    for (int i = 1; i <= n; i++) 
    {
        for (int w = 1; w <= W; w++) 
        {
            if (weights[i - 1] <= w) 
            {
                // Check if including the current item gives a better profit
                B[i][w] = max(profits[i - 1] + B[i - 1][w - weights[i - 1]], B[i - 1][w]);
            } 
            else 
            {
                // If the item cannot be included, carry forward the previous value
                B[i][w] = B[i - 1][w];
            }
        }
    }

    // Print maximum profit
    cout << "Maximum Profit: " << B[n][W] << endl;

    // Traceback to find selected items -- backtrack from the last cell which means that the last item selected is printed first and so on
    int i = n, k = W;
    cout << "Selected items: ";
    while (i > 0 && k > 0) 
    {
        if (B[i][k] != B[i - 1][k]) 
        {
            cout << i << " ";  // 1-based index
            k -= weights[i - 1]; // Reduce the weight capacity
        }
        i--;
    }
    cout << endl;
}

int main() 
{
    int n, W;
    
    // Take user input for number of items and knapsack capacity
    cout << "Enter number of items: ";
    cin >> n;

    // Handle edge case: No items
    if (n == 0) 
    {
        cout << "No items available. Maximum Profit: 0\n";
        return 0;
    }

    cout << "Enter knapsack capacity: ";
    cin >> W;

    // Handle edge case: Zero capacity
    if (W == 0) 
    {
        cout << "Knapsack has zero capacity. Maximum Profit: 0\n";
        return 0;
    }

    int weights[MAX_ITEMS], profits[MAX_ITEMS];

    // Read weights of items
    cout << "Enter item weights: ";
    for (int i = 0; i < n; i++) 
    {
        cin >> weights[i];
    }

    // Read profits of items
    cout << "Enter item profits: ";
    for (int i = 0; i < n; i++) 
    {
        cin >> profits[i];
    }

    // Call the knapsack function
    knapsack(n, W, weights, profits);

    return 0;
}
// Time Complexity: O(n*W), where n is the number of items and W is the knapsack capacity
// Space Complexity: O(n*W)
//input:
//Enter number of items: 4
//Enter knapsack capacity: 8
//Enter weights of items: 3 4 6 5
//Enter profits of items: 2 3 1 4