/***
An engineer wants to distribute B identical machines across N compute clusters to improve performance.
Each cluster has a predefined workload f nearly identical tasks.
Your gola is to minimize the workload on the single most overloaded machine across all the clusters.
For example, suppose you have :
2 clusters in total, A cluster has workload of 200 tasks/minute, B cluster has 450 tasks/minute
7 machines in total
One optimal solution can be 2 machines on A cluster and 5 machines on B cluster.

Therefore, the most overloaded machine handle 100 tasks/minute.
Notice that the most overloaded value can be rounded up to integer.

Reference: http://chaoxuprime.com/posts/2016-08-02-proportional-apportionment.html
***/
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <cassert>

using namespace std;

struct Cluster{
  Cluster(int wl,int mc) : workload(wl), machine_count(mc) { }
  double workload;
  double machine_count;
};

// Functor to compare Cluster
struct MoreWorkload {
  bool operator()(const Cluster & left, const Cluster & right) {
    // notice that I used double instead of integer here.
    double left_workload = left.machine_count==0? left.workload : left.workload/left.machine_count;
    double right_workload = right.machine_count==0? right.workload : right.workload/right.machine_count;
    return left_workload < right_workload;
  }
};

typedef std::priority_queue<Cluster,vector<Cluster>,MoreWorkload > MaxHeap;

int AdjustWorkload(MaxHeap & cluster_workloads,int cluster_num,int machine_num) {
  for (int i=0;i<machine_num;++i) {
    Cluster max_cluster = cluster_workloads.top();
    cluster_workloads.pop();
    ++ max_cluster.machine_count;
    cluster_workloads.push(max_cluster);
  }

  return cluster_workloads.top().workload/cluster_workloads.top().machine_count;
}

void UnitTest() {
  // test 1
  vector<Cluster> clusters = {Cluster(200,0),Cluster(450,0)};
  MaxHeap max_heap;
  for (const Cluster & c : clusters) max_heap.push(c);
  assert(AdjustWorkload(max_heap,2,7) == 100);

  // test 2
  vector<Cluster> clusters2 = {Cluster(200,0),Cluster(450,0),Cluster(300,0),Cluster(720,0)};
  MaxHeap max_heap2;
  for (const Cluster & c : clusters2) max_heap2.push(c);
  assert( AdjustWorkload(max_heap2,4,10) == 200 );
}

int main() {
  UnitTest();
  return 0;
}
