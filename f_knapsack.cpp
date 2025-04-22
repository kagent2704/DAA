#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int value, weight;
    // Sort by value/weight ratio
    bool operator<(Item other) {
        return (double)value / weight > (double)other.value / other.weight;
    }
};

double fractionalKnapsack(int W, vector<Item>& items) {
    sort(items.begin(), items.end());
    double totalValue = 0.0;

    for (Item& item : items) {
        if (W >= item.weight) {
            W -= item.weight;
            totalValue += item.value;
        } else {
            totalValue += item.value * ((double)W / item.weight);
            break;
        }
    }

    return totalValue;
}

int main() {
    int n, W;
    cout << "Enter number of items and knapsack capacity: ";
    cin >> n >> W;

    vector<Item> items(n);
    cout << "Enter value and weight of each item:\n";
    for (int i = 0; i < n; ++i)
        cin >> items[i].value >> items[i].weight;

    cout << "Maximum value in knapsack = " << fractionalKnapsack(W, items) << endl;
    return 0;
}
