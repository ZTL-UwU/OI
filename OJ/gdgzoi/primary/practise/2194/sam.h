#include <string.h>
#include <map>
template <int MAXN> // type name and maximum size
class sam
{
    int size;
    int last;
    int z;
    int p;
    int y;

public:
    sam();
    ~sam();
    std::map<int, int> trans[2 * MAXN + 10]; // Transform
    int *link = new int[2 * MAXN + 10]();    // link
    int *max_len = new int[2 * MAXN + 10](); // Max-length
    /*
     * Build a SAM
     * add 'add' to SAM
     */
    void build(int add)
    {
        z = ++size; // New status
        p = last;   // Pointer on link-path
        max_len[z] = max_len[last] + 1;
        for (p = last; p != -1 && !trans[p][add]; p = link[p])
            trans[p][add] = z;
        /*
         * Condition 1
         * v belongs to link-path(u -> S)
         * trans[v][] = NULL
         * -> link[z] = S
         */
        if (p == -1)     // All NULL in the link-path
            link[z] = 0; // link to head
        /*
         * Condition 2
         * v belongs to link-path(u -> S)
         * found !NULL in trans[v][]
         */
        else
        {
            int x = trans[p][add]; // Next status
            /*
             * Condition 2.1
             * max-len[x] = max-len[v] + 1
             * -> link[z] = x
             */
            y = ++size; // New status
            if (max_len[x] == max_len[p] + 1)
                link[z] = x;
            /*
             * Condition 2.2
             * max-len[x] > max-len[v] + 1
             * -> make new status
             */
            else
            {
                max_len[y] = max_len[p] + 1;
                // Copy x's data to y
                trans[y] = trans[x];
                link[y] = link[x];
                for (; p != -1 && !trans[p][add] == x; p = link[p])
                    trans[p][add] = y;
                link[x] = link[z] = y;
            }
        }
        last = z;
    }
    // Get number of different substrings
    int substr(int add)
    {
        build(add);
        return max_len[z] - max_len[link[z]];
    }
};

template <int MAXN> // Make
sam<MAXN>::sam()
{
    memset(link, -1, sizeof(link));
    size = last = 0;
}
template <int MAXN> // Delete
sam<MAXN>::~sam()
{
    for (int i = 0; i < 2 * MAXN + 10; i++)
        trans[i].erase(trans[i].begin(), trans[i].end());
    delete[] link;
    delete[] max_len;
}