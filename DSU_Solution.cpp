/*
Author: Ridham Garg
Thapar Institute of Engineering and Technology, Patiala

Problem: Largest Island (Change at most one 0 to 1)

Approach:
- Use Union-Find (Disjoint Set Union) to group connected land cells (1s).
- For each 0 in the grid, calculate the potential island size by checking unique neighboring components.
- Return the maximum island size possible by flipping one 0 to 1.
*/

class Solution {
public:
    vector<int> parent, size; // DSU structures

    // Find with path compression
    int find(int u) {
        if (u == parent[u])
            return u;
        return parent[u] = find(parent[u]);  
    }

    // Check if (newi, newj) is within grid bounds
    bool isvalid(int m, int n, int newi, int newj) {
        return newi < m && newi >= 0 && newj < n && newj >= 0;
    }

    // Union by size
    void unite(int u, int v) {
        int parentU = find(u);
        int parentV = find(v);

        if (parentU == parentV)
            return;  // Already in the same component

        if (size[parentU] < size[parentV]) {
            parent[parentU] = parentV;
            size[parentV] += size[parentU];
        } else {
            parent[parentV] = parentU;
            size[parentU] += size[parentV];
        }
    }

    // Get the size of the component that u belongs to
    int getSize(int u) {
        return size[find(u)];
    }

    int largestIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        size.resize(m * n);      // Initialize size vector
        parent.resize(m * n);    // Initialize parent vector

        for (int i = 0; i < m * n; i++) {
            size[i] = 1;
            parent[i] = i;
        }

        int ans = 0;
        vector<vector<int>> direction = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}}; // 4-directional movement
        int findy = 0; // Flag to check if there's any 1 in the grid

        // Step 1: Merge all connected 1s
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    findy = 1; // Found at least one 1
                    for (auto dir : direction) {
                        int newi = i + dir[0];
                        int newj = j + dir[1];
                        if (isvalid(m, n, newi, newj) && grid[newi][newj] == 1) {
                            unite(i * n + j, newi * n + newj);
                            ans = max(ans, getSize(newi * n + newj)); // Track max island size
                        }
                    }
                }
            }
        }

        if (findy == 0)
            return 1; // No 1s in the grid, so flipping any 0 will give island of size 1

        // Step 2: Try flipping every 0 and calculate island size
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int tempans = 0; // Potential island size after flip
                if (grid[i][j] == 0) {
                    unordered_set<int> st; // To avoid double counting connected components
                    for (auto dir : direction) {
                        int newi = i + dir[0];
                        int newj = j + dir[1];
                        if (isvalid(m, n, newi, newj) && st.find(find(newi * n + newj)) == st.end() && grid[newi][newj] == 1) {
                            st.insert(find(newi * n + newj));
                            tempans += getSize(newi * n + newj); // Add unique component size
                        }
                    }
                }
                ans = max(ans, tempans + 1); // Add the flipped cell
            }
        }

        return ans;
    }
};
