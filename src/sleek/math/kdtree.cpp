#include "kdtree.h"
#include <queue>
#include <stack>
#include <cmath>
#include <limits>
#include <algorithm>
#include <functional>

namespace sleek
{
    namespace math
    {
        kdtree::kdtree() noexcept : root(nullptr)
        {
        }

        kdtree::~kdtree() noexcept
        {
            clear();
        }

        void kdtree::clear() noexcept
        {
            std::stack<kdnode*> nodes;

            if (root)
                nodes.push(root);

            while (!nodes.empty())
            {
                kdnode* node = nodes.top();
                nodes.pop();

                if (node->left)
                    nodes.push(node->left);

                if (node->right)
                    nodes.push(node->right);

                delete node;
            }
            root = nullptr;
        }

        void kdtree::build(const std::vector<vec3f>& points) noexcept
        {
            clear();

            if (points.empty())
                return;

            struct BuildNode {
                int start;
                int end;
                int depth;
                kdnode** link;
            };

            std::vector<kdnode*> nodes(points.size());

            for (size_t i = 0; i < points.size(); ++i)
            {
                nodes[i] = new kdnode();
                nodes[i]->point = points[i];
            }

            std::stack<BuildNode> stack;
            root = new kdnode();
            stack.push({0, static_cast<int>(points.size()), 0, &root});

            while (!stack.empty())
            {
                BuildNode current = stack.top();
                stack.pop();

                int start = current.start;
                int end = current.end;
                int depth = current.depth;
                kdnode** link = current.link;

                if (start >= end)
                {
                    *link = nullptr;
                    continue;
                }

                int axis = depth % 3;
                int mid = (start + end) / 2;

                std::nth_element(nodes.begin() + start, nodes.begin() + mid, nodes.begin() + end,
                    [axis](kdnode* a, kdnode* b) {
                        return a->point[axis] < b->point[axis];
                    });

                *link = nodes[mid];
                (*link)->left = nullptr;
                (*link)->right = nullptr;

                stack.push({mid + 1, end, depth + 1, &((*link)->right)});
                stack.push({start, mid, depth + 1, &((*link)->left)});
            }
        }

        void kdtree::update(const std::vector<vec3f>& newPoints) noexcept
        {
            if (!root || newPoints.empty())
                return;

            std::stack<kdnode*> stack;
            kdnode* current = root;
            size_t index = 0;

            while (current || !stack.empty())
            {
                // Traverse to the leftmost node
                while (current)
                {
                    stack.push(current);
                    current = current->left;
                }

                // Process the current node
                current = stack.top();
                stack.pop();

                // Update the current node's point
                if (index < newPoints.size())
                {
                    current->point = newPoints[index++];
                }

                // Move to the right child
                current = current->right;
            }
        }

        std::vector<std::pair<float, vec3f>> kdtree::findNearestNeighbors(const vec3f& target, int k) const noexcept
        {
            if (!root || k <= 0) return {};

            auto distanceSquared = [](const vec3f& a, const vec3f& b) -> float {
                return glm::dot(a - b, a - b);
            };

            // Custom comparator for the priority queue
            auto comparator = [](const std::pair<float, vec3f>& a, const std::pair<float, vec3f>& b) {
                return a.first < b.first;
            };

            // Use the custom comparator in the priority queue
            std::priority_queue<std::pair<float, vec3f>, 
                                std::vector<std::pair<float, vec3f>>, 
                                decltype(comparator)> maxHeap(comparator);

            std::stack<std::pair<kdnode*, int>> stack;
            stack.push({root, 0});

            while (!stack.empty())
            {
                auto [node, depth] = stack.top();
                stack.pop();

                if (!node)
                    continue;

                float dist = distanceSquared(target, node->point);

                if (maxHeap.size() < k)
                    maxHeap.push({dist, node->point});
                else if (dist < maxHeap.top().first)
                {
                    maxHeap.pop();
                    maxHeap.push({dist, node->point});
                }

                int axis = depth % 3;
                kdnode* nearChild = (target[axis] < node->point[axis]) ? node->left : node->right;
                kdnode* farChild = (target[axis] < node->point[axis]) ? node->right : node->left;

                stack.push({nearChild, depth + 1});

                if (maxHeap.size() < k || std::abs(target[axis] - node->point[axis]) < std::sqrt(maxHeap.top().first))
                {
                    stack.push({farChild, depth + 1});
                }
            }

            std::vector<std::pair<float, vec3f>> result;
            while (!maxHeap.empty())
            {
                result.push_back(maxHeap.top());
                maxHeap.pop();
            }

            return result;
        }

    } // namespace math
} // namespace sleek

/*


class kdnode
{
    public:
        Particle *particle;
        kdnode *left;
        kdnode *right;
        int axis;

        kdnode() : particle(nullptr), left(nullptr), right(nullptr), axis(0)
        {
        }

        kdnode(Particle *p, int a) : particle(p), left(nullptr), right(nullptr), axis(a)
        {
        }
};


class kdtree
{
    private:
        std::vector<kdnode> nodes;
        int nodeIndex;

    public:
        kdtree() : nodeIndex(0)
        {
            nodes.resize(MAX_PARTICLES);
        }

        void build(std::vector<Particle *> &particles)
        {
            nodeIndex = 0;
            buildTree(particles, 0, particles.size(), 0);
        }

        void buildTree(std::vector<Particle *> &particles, int start, int end, int depth)
        {
            if(start >= end)
                return;

            int axis = depth % 2;
            int mid = (start + end) / 2;

            std::nth_element(
                particles.begin() + start,
                particles.begin() + mid,
                particles.begin() + end,
                [axis](const Particle *a, const Particle *b) {
                        return axis == 0 ? a->position.x < b->position.x : a->position.y < b->position.y;
                    });

            nodes[nodeIndex] = kdnode(particles[mid], axis);
            int currentIndex = nodeIndex;
            nodeIndex++;

            if(start < mid)
            {
                nodes[currentIndex].left = &nodes[nodeIndex];
                buildTree(particles, start, mid, depth + 1);
            }
            if(mid + 1 < end)
            {
                nodes[currentIndex].right = &nodes[nodeIndex];
                buildTree(particles, mid + 1, end, depth + 1);
            }
        }

        void findNeighbors(const glm::vec2 &point, float radius, std::vector<Particle *> &neighbors, int max=-1)
        {
            neighbors.clear();
            if(nodeIndex == 0)
                return;

            float radiusSquared = radius * radius;
            std::vector<const kdnode *> stack;
            stack.reserve(32); // Preallocate stack to avoid reallocation
            stack.push_back(&nodes[0]);

            while(!stack.empty())
            {
                if (max >0 && neighbors.size() > max)
                    break;
                
                const kdnode *current = stack.back();
                stack.pop_back();

                float dx = point.x - current->particle->position.x;
                float dy = point.y - current->particle->position.y;
                float distSquared = dx * dx + dy * dy;

                if(distSquared <= radiusSquared)
                {
                    neighbors.push_back(current->particle);
                }

                float axisDist = current->axis == 0 ? dx : dy;
                float axisDistSquared = axisDist * axisDist;

                if(axisDist < 0)
                {
                    if(current->left)
                        stack.push_back(current->left);
                    if(axisDistSquared <= radiusSquared && current->right)
                        stack.push_back(current->right);
                }
                else
                {
                    if(current->right)
                        stack.push_back(current->right);
                    if(axisDistSquared <= radiusSquared && current->left)
                        stack.push_back(current->left);
                }
            }
        }
};

*/