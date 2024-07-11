#ifndef kdtree_H
#define kdtree_H

#include <vector>
#include "math.h"

namespace sleek
{
    namespace math
    {
        
        struct kdnode
        {
            kdnode() : left(nullptr), right(nullptr), user(nullptr) {}
            vec3f point;
            kdnode *left;
            kdnode *right;
            void *user;
        };

        class kdtree
        {
            public:
                kdtree() noexcept;
                ~kdtree() noexcept;

                /**
                 * @brief Builds a KD-tree from a vector of 3D points.
                 * 
                 * This function constructs a balanced KD-tree from the given set of points.
                 * It uses an iterative approach to build the tree, which is more memory-efficient
                 * and less prone to stack overflow for large datasets compared to a recursive approach.
                 * 
                 * The function first clears any existing tree structure, then creates a new tree
                 * by recursively partitioning the points along alternating dimensions (x, y, z).
                 * At each level, it selects the median point along the current dimension as the splitting point.
                 * 
                 * @param points A vector of 3D points (vec3f) to be inserted into the KD-tree.
                 * 
                 * @note This function is marked noexcept and will not throw exceptions.
                 *       If the input vector is empty, the function will simply clear any existing tree and return.
                 * 
                 * @complexity Time complexity is O(n log n) where n is the number of points.
                 *             This is due to the sorting operation performed at each level of the tree.
                 *             Space complexity is O(n) for storing the points and the tree structure.
                 * 
                 * @thread_safety This function is not thread-safe. It should not be called concurrently
                 *                with other methods that modify the tree structure.
                 * 
                 * @performance This implementation uses std::nth_element for efficient partitioning,
                 *              which provides better performance than full sorting at each level.
                 * 
                 * @memory The function allocates memory for each node in the tree. In the worst case,
                 *         this could be up to 2n-1 nodes for a completely unbalanced tree, 
                 *         but typically it will be closer to n nodes for a balanced tree.
                 * 
                 * @example
                 *     kdtree tree;
                 *     std::vector<vec3f> points = {{1,2,3}, {4,5,6}, {7,8,9}};
                 *     tree.build(points);
                 */
                void build(const std::vector<vec3f>& points) noexcept;

                /**
                 * @brief Clears the KD-tree, deallocating all nodes.
                 * 
                 * This function removes all nodes from the KD-tree and frees the associated memory.
                 * After calling this function, the tree will be empty and the root will be set to nullptr.
                 * 
                 * The function uses an iterative approach with a stack to perform a post-order traversal
                 * of the tree, ensuring that all child nodes are deleted before their parents.
                 * This method is more efficient and less prone to stack overflow than a recursive approach,
                 * especially for large trees.
                 * 
                 * @note This function is marked noexcept and will not throw exceptions.
                 *       It is safe to call on an empty tree or a tree that has already been cleared.
                 * 
                 * @complexity Time complexity is O(n), where n is the number of nodes in the tree.
                 *             Each node is visited exactly once.
                 *             Space complexity is O(h), where h is the height of the tree, 
                 *             due to the stack used for traversal. In the worst case of an unbalanced tree, 
                 *             this could be O(n), but for a balanced tree, it would be O(log n).
                 * 
                 * @thread_safety This function is not thread-safe. It should not be called concurrently
                 *                with other methods that access or modify the tree structure.
                 * 
                 * @memory This function deallocates all memory associated with the tree nodes.
                 *         After this function completes, the memory used by the tree will be minimal,
                 *         consisting only of the kdtree object itself.
                 * 
                 * @warning Any pointers or references to nodes in the tree will be invalidated after this call.
                 *          Attempting to use such pointers or references may result in undefined behavior.
                 * 
                 * @example
                 *     kdtree tree;
                 *     // ... build the tree ...
                 *     tree.clear();  // Tree is now empty
                 */
                void clear() noexcept;

                /**
                 * @brief Finds the k nearest neighbors to a target point in the KD-tree.
                 * 
                 * This function implements an iterative K-Nearest Neighbors (KNN) search algorithm
                 * for a KD-tree. It uses a depth-first search approach, simulated with a stack,
                 * to traverse the tree and find the k points closest to the given target point.
                 * 
                 * The function uses a max-heap to maintain the k nearest points found so far,
                 * allowing efficient updates and comparisons as new points are considered.
                 * 
                 * @param target The target point for which to find the nearest neighbors.
                 * @param k The number of nearest neighbors to find.
                 * 
                 * @return A vector containing the k nearest neighbor points, in no particular order.
                 *         The pair contain the distance to the target as first value
                 * 
                 * @note This function is marked noexcept and will not throw exceptions.
                 *       If the tree is empty or k is 0, an empty vector will be returned.
                 * 
                 * @complexity Time complexity is O(log n) on average for balanced trees, 
                 *             where n is the number of points in the tree. 
                 *             In the worst case (unbalanced tree), it can be O(n).
                 *             Space complexity is O(log n) for the stack in balanced trees,
                 *             and O(n) in the worst case for unbalanced trees.
                 * 
                 * @thread_safety This function is const and does not modify the tree structure.
                 *                It is safe to call from multiple threads concurrently, 
                 *                as long as the tree is not being modified simultaneously.
                 * 
                 * @example
                 *     kdtree tree;
                 *     // ... populate the tree ...
                 *     vec3f target(1.0f, 2.0f, 3.0f);
                 *     int k = 5;
                 *     auto neighbors = tree.findNearestNeighbors(target, k);
                 */
                std::vector<std::pair<float, vec3f>> findNearestNeighbors(const vec3f& target, int k) const noexcept;

                /**
                 * @brief Updates the KD-tree with new point positions using an iterative approach.
                 * 
                 * This function efficiently updates the positions of existing nodes in the KD-tree
                 * without altering the tree structure. It employs an iterative in-order traversal,
                 * which is more memory-efficient and less prone to stack overflow compared to 
                 * recursive approaches, especially for large or deep trees.
                 * 
                 * @param newPoints A vector of new 3D points (vec3f) corresponding to the updated positions.
                 *                  The order must match the order of points used in the original build.
                 * 
                 * @note This function assumes that:
                 *       1. The number of points hasn't changed since the last build or update.
                 *       2. The order of points in newPoints corresponds exactly to the order 
                 *          of nodes in the tree's in-order traversal.
                 *       If points have been added, removed, or reordered, use the build() function instead.
                 * 
                 * @warning If the relative positions of points change significantly, the tree may
                 *          become unbalanced over time, potentially reducing query performance.
                 *          In such cases, periodically rebuilding the entire tree using build()
                 *          may be necessary to maintain optimal performance.
                 * 
                 * @complexity Time complexity: O(n), where n is the number of points in the tree.
                 *             Each node is visited exactly once.
                 *             Space complexity: O(h), where h is the height of the tree, 
                 *             due to the stack used for traversal. In a balanced tree, this is O(log n),
                 *             but in the worst case of an unbalanced tree, it could be O(n).
                 * 
                 * @thread_safety This function is not thread-safe. It should not be called concurrently
                 *                with other methods that access or modify the tree structure.
                 * 
                 * @performance This method is generally faster than rebuilding the entire tree,
                 *              especially when the overall structure of the tree doesn't change significantly.
                 *              However, it does not rebalance the tree or optimize its structure.
                 * 
                 * @example
                 *     kdtree tree;
                 *     std::vector<vec3f> initialPoints = {{1,2,3}, {4,5,6}, {7,8,9}};
                 *     tree.build(initialPoints);
                 *     
                 *     // After updating particle positions
                 *     std::vector<vec3f> newPoints = {{1.1,2.1,3.1}, {4.1,5.1,6.1}, {7.1,8.1,9.1}};
                 *     tree.update(newPoints);
                 */
                void update(const std::vector<vec3f>& newPoints) noexcept;
            private:
                kdnode* root;
        };
    }
}

#endif // kdtree_H