# Leetcode-827.-Making-A-Large-Island

# 🏝️ Largest Island (Leetcode Hard)

## 💡 Problem Statement

You are given an `n x n` binary matrix `grid`. You are allowed to change **at most one** `0` to `1`. Return the size of the largest island in `grid` after applying this change.

An **island** is a group of `1`s connected **4-directionally** (up, down, left, right).

---

## ✅ Example

### Input:
```cpp
grid = [
  [1, 0],
  [0, 1]
]

output 3

Explanation:
Changing one of the 0s to 1 connects the two 1s into a single island of size 3.

🚀 Approach 1: DFS + Recoloring Islands
🔧 Core Idea:
Traverse the grid and use DFS to label each island with a unique ID (2, 3, ...) and record its size.

For each 0, try converting it to 1, then look in 4 directions to gather unique neighboring island IDs.

Sum the sizes of the connected islands and add 1 for the changed 0.

🧮 Time Complexity:
O(n^2) — we visit each cell at most a few times.

🧠 Space Complexity:
O(n^2) — to store island IDs and visited cells.


📌 Pros:
Simple and intuitive.

Works well for small to medium-size grids.

❌ Cons:
DFS recursion depth might be a concern for very large grids.

⚙️ Approach 2: Union-Find (Disjoint Set Union – DSU)
🔧 Core Idea:
Flatten the grid to a 1D array and use Union-Find to group all 1s.

Store the size of each component (island).

For every 0, check 4 neighboring cells. Use their root parents to avoid duplicate inclusion.

Sum the sizes of unique neighboring components and add 1.

🧮 Time Complexity:
O(n^2 * α(n)), where α is the inverse Ackermann function (nearly constant).

🧠 Space Complexity:
O(n^2) — for parent and size arrays.

📌 Pros:
Faster due to DSU operations.

Avoids deep recursion.

❌ Cons:
Slightly more complex to implement and debug.

🛠️ Key Concepts Used
DFS & Grid Traversal

Disjoint Set Union (DSU)

Hashing and Sets

Island Labelling

👨‍💻 Author
Ridham Garg
B.Tech Computer Engineering, Thapar University

🔗 Problem Link
🔗 Largest Island – LeetCode

🧪 Tips for Interview
Mention that labeling islands with unique IDs avoids recomputation.

Always use unordered_set to avoid double-counting neighbors.

If recursion depth is a concern, suggest DSU as an optimized approach.

🙋 Want Help?
You can reach out for questions, explanations, or debugging help by opening an issue or connecting via GitHub!
