#pragma once

#include <vector>
#include <utility>
#include "./index.h"

namespace sleek
{
    namespace math
    {
        struct EdgeMap
        {
            using edge = std::pair<unsigned,unsigned>;
            using poly = index<3>;

            std::map<edge,int> edge_map;
            std::vector<edge> edge_list;

            EdgeMap(const std::vector<poly> &triangle) noexcept
            {
                for(auto f : triangle)
                {
                    add_edge(f.vertex[0],f.vertex[1]);
                    add_edge(f.vertex[1],f.vertex[2]);
                    add_edge(f.vertex[2],f.vertex[0]);
                }
            }

            void add_edge(unsigned i, unsigned j) noexcept
            {
                if(edge_map.find(edge(i,j)) == edge_map.end())
                {
                    edge_map[edge(i,j)] = edge_list.size();
                    edge_map[edge(j,i)] = edge_list.size();
                    edge_list.push_back(edge(i,j));
                }
            }

            int edge_index(edge key) const noexcept
            {
                auto it = edge_map.find(key);
                return it == edge_map.end() ? -1 : it->second;
            }
        };
    }
}
