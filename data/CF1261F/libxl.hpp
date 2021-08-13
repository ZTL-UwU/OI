#pragma once

#include <algorithm>
#include <iostream>
#include <ios>
#include <random>
#include <cassert>
#include <map>
#include <vector>
#include <string>
#include <functional>
#include <fstream>

namespace lxl
{
    void loop(int n, std::function<void()> f)
    {
        for (int _ = 0; _ < n; ++_)
        {
            f();
        }
    }

    std::mt19937 raw_rand(std::random_device{}());

    unsigned long long raw_rand_ll() { return (static_cast<unsigned long long>(raw_rand()) << 32) + raw_rand(); }

    template <typename T>
    T mk_rand(T l, T r);

    template <>
    int mk_rand<int>(int l, int r)
    {
        return raw_rand() % (r - l + 1) + l;
    }

    template <>
    unsigned long long mk_rand<unsigned long long>(unsigned long long l, unsigned long long r)
    {
        return raw_rand_ll() % (r - l + 1) + l;
    }

    bool mk_bool(double possibility)
    {
        const auto rng = mk_rand<int>(0, 1e9);
        return rng <= 1e9 * possibility;
    }

    template <typename W>
    struct weighted_graph
    {
        int n, m;
        std::vector<std::vector<std::pair<int, W>>> G;

        void set_vertex(int n)
        {
            this->n = n;
            G.resize(n + 1, std::vector<std::pair<int, W>>());
        }

        void add_edge(const int x, const int y, const W &w = W{}) { G[x].push_back(std::make_pair(y, w)); }

        void mk_weight(std::function<W()> f)
        {
            for (int i = 1; i <= n; ++i)
            {
                for (std::size_t j = 0; j < G[i].size(); ++j)
                {
                    G[i][j].second = f();
                }
            }
        }

        static weighted_graph<W> mk(int n, int m)
        {
            weighted_graph<W> res;
            res.set_vertex(n);
            std::map<std::pair<int, int>, bool> mp;

            assert(n * (n - 1) >= m);

            loop(m, [&]() {
                int x, y;
                do
                {
                    x = mk_rand(1, n);
                    y = mk_rand(1, n - 1);

                    if (y >= x)
                    {
                        y += 1;
                    }
                } while (mp[std::make_pair(x, y)]);
                mp[std::make_pair(x, y)] = true;
                res.add_edge(x, y);
            });
        }

        static weighted_graph<W> mk_tree(int n)
        {
            weighted_graph<W> res;
            res.set_vertex(1);
            if (n == 1)
            {
                return res;
            }

            std::vector<int> purfer, deg;
            purfer.resize(n - 2);
            deg.resize(n + 1);
        }
    };

    using graph = weighted_graph<void>;

    std::string mk_string(std::size_t len, const std::string &char_set)
    {
        std::string res;
        for (std::size_t i = 0; i < len; i++)
        {
            res += char_set[mk_rand<int>(0, char_set.size() - 1)];
        }
        return res;
    }

    template <typename T>
    std::vector<T> mk_list(std::size_t len, std::function<T()> maker)
    {
        std::vector<T> res;
        res.reserve(len);

        for (std::size_t i = 0; i < len; i++)
        {
            res.push_back(maker());
        }
        return res;
    }

    template <typename T>
    std::vector<T> mk_list(std::size_t len, const std::vector<T> &el_set)
    {
        std::vector<T> res;
        res.reserve(len);

        for (std::size_t i = 0; i < len; i++)
        {
            res.push_back(el_set[mk_rand(0, el_set.size() - 1)]);
        }
        return res;
    }

    struct io
    {
        std::ofstream file;
        io(const std::string &name) { file.open(name, std::ios::out); }
    };

} // namespace lxl
