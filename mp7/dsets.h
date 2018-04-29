/* Your code here! */

#ifndef DSETS_H_
#define DSETS_H_

#include <vector>

class DisjointSets {
  public:
    void addelements (int num);
    int find (int elem);
    void setunion (int a, int b);
    int size(int elem);

  private:
    std::vector<int> sets;
};

#endif
