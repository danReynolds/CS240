#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>


class Node {
public:
  int x;
  int y;
};

class cmp {
    int value_;
    int coord_;
    bool lt_;
public:
    cmp(Node* a, int coord, bool lt) : coord_(coord), lt_(lt) {
      if (coord_) {
        value_ = a->y;
      }
      else {
        value_ = a->x;
      }
    }
    bool operator()(Node* b) { 
      if (coord_) {
        if (lt_)
          return (b->y >= value_);
        else
          return (b->y <= value_);
      }
      else {
        if (lt_) {
          return (b->x >= value_);
        }
        else
          return (b->x <= value_);
      }
    }
};

bool firstCompare(Node* a, Node* b) {
  return (a->x < b->x);
}

bool secondCompare(Node* a, Node* b) {
  return (a->y < b->y);
}

enum Direction {Horizontal, Vertical};

void construct(std::vector<Node*> xSort, std::vector<Node*> ySort, Direction direction) {
  if (xSort.size() == 1) {
    std::cout << xSort[0]->x << " " << xSort[0]->y << std::endl;
    return;
  }
  else if (xSort.size() == 0) {
    return;
  }

  std::vector<Node*> xleftPartition;
  std::vector<Node*> xrightPartition;
  std::vector<Node*> yleftPartition;
  std::vector<Node*> yrightPartition;

  if (direction == Vertical) {
    Node* mid = xSort[xSort.size()/2];
    cmp cmp_x_lt(mid, 0, true);
    cmp cmp_x_gt(mid, 0, false);
    std::remove_copy_if(xSort.begin(), xSort.end(), std::back_inserter(xleftPartition), cmp_x_lt); //copies over all the ones except for those that are true
    std::remove_copy_if(xSort.begin(), xSort.end(), std::back_inserter(xrightPartition), cmp_x_gt);
    std::remove_copy_if(ySort.begin(), ySort.end(), std::back_inserter(yleftPartition), cmp_x_lt); //copies over all the ones except for those that are true
    std::remove_copy_if(ySort.begin(), ySort.end(), std::back_inserter(yrightPartition), cmp_x_gt);
    construct(xleftPartition, yleftPartition, Horizontal);
    std::cout << mid->x << " " << mid->y<<std::endl;
    construct(xrightPartition, yrightPartition, Horizontal);
  }
  else {
    Node* mid = ySort[ySort.size()/2];
    cmp cmp_y_lt(mid, 1, true);
    cmp cmp_y_gt(mid, 1, false);
    std::remove_copy_if(xSort.begin(), xSort.end(), std::back_inserter(xleftPartition), cmp_y_lt); //copies over all the ones except for those that are true
    std::remove_copy_if(xSort.begin(), xSort.end(), std::back_inserter(xrightPartition), cmp_y_gt);
    std::remove_copy_if(ySort.begin(), ySort.end(), std::back_inserter(yleftPartition), cmp_y_lt); //copies over all the ones except for those that are true
    std::remove_copy_if(ySort.begin(), ySort.end(), std::back_inserter(yrightPartition), cmp_y_gt);
    construct(xleftPartition, yleftPartition, Vertical);
    std::cout << mid->x << " " << mid->y<<std::endl;
    construct(xrightPartition, yrightPartition, Vertical);
  }
}

int main(void) {
  int size;
  int first, second;
  std::cin >> size;
  std::vector<Node*> xSort;
  std::vector<Node*> ySort;

  for(int x = 0; x < size; x++) {
    std::cin >> first;
    std::cin >> second;
    Node* point = new Node();
    point->x = first;
    point->y = second;
    xSort.push_back(point);
    ySort.push_back(point);
  }
  std::sort(xSort.begin(), xSort.end(), firstCompare);
  std::sort(ySort.begin(), ySort.end(), secondCompare);
  construct(xSort, ySort, Vertical);

  return 0;
}
