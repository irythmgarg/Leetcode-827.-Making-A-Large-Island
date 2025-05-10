class Solution {
public:

    // Check if a given cell (newi, newj) is within the grid boundaries
    bool isvalid(int m, int n, int newi, int newj) {
        return newi < m && newi >= 0 && newj < n && newj >= 0;
    }

    // Perform DFS to mark all connected 1's as a unique island with ID `id`
    // and count the number of cells in this island
    void dfs(int i, int j, vector<vector<int>>& grid, int m, int n, int id, set<pair<int, int>>& visited, int &count) {
        visited.insert({i, j});      // Mark cell as visited
        count++;                     // Increment current island size
        grid[i][j] = id;             // Label cell with island ID

        // Possible directions: up, down, right, left
        vector<vector<int>> direction = {{-1,0}, {1,0}, {0,1}, {0,-1}};

        for (auto dir : direction) {
            int newi = i + dir[0];
            int newj = j + dir[1];

            // If neighbor is valid, not visited yet, and is land (1), continue DFS
            if (isvalid(m, n, newi, newj) && visited.find({newi, newj}) == visited.end() && grid[newi][newj] == 1) {
                visited.insert({newi, newj});
                dfs(newi, newj, grid, m, n, id, visited, count);
            }
        }
    }

    int largestIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int ans = 0;  // Stores final maximum island size
        vector<vector<int>> direction = {{-1,0}, {1,0}, {0,1}, {0,-1}};
        int foundLand = 0;  // Check if there's any land in the grid
        unordered_map<int, int> islandSizeMap;  // Map island ID to its size
        int id = 2;  // Start island IDs from 2 (as 0 and 1 are already in use)

        // Step 1: Label each island with a unique ID and store its size
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    foundLand = 1;
                    int size = 0;
                    set<pair<int, int>> visited;
                    dfs(i, j, grid, m, n, id, visited, size);
                    islandSizeMap[id] = size;
                    id++;
                }
            }
        }

        // If no land at all, flipping any 0 gives island of size 1
        if (foundLand == 0) return 1;

        // Step 2: For each water cell (0), try flipping to 1 and calculate max island size
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int tempSize = 0;
                if (grid[i][j] == 0) {
                    unordered_set<int> neighborIslands;

                    for (auto dir : direction) {
                        int newi = i + dir[0];
                        int newj = j + dir[1];

                        // If neighbor is valid and is part of an island (ID > 1)
                        if (isvalid(m, n, newi, newj) && neighborIslands.find(grid[newi][newj]) == neighborIslands.end()) {
                            neighborIslands.insert(grid[newi][newj]);
                            tempSize += islandSizeMap[grid[newi][newj]];
                        }
                    }

                    // Update max island size by adding the flipped cell
                    ans = max(ans, tempSize + 1);
                }
            }
        }

        // Return the maximum of computed answer and the size of any original island (in case we don't flip any 0)
        return max(ans, islandSizeMap[grid[m-1][n-1]]);
    }
};
