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
    double left_workload  = left.workload/left.machine_count;
    double right_workload = right.workload/right.machine_count;
    return left_workload < right_workload;
  }
};

typedef std::priority_queue<Cluster,vector<Cluster>,MoreWorkload > MaxHeap;

int AdjustWorkload(vector<int> & workloads,int cluster_num,int machine_num) {
  MaxHeap cluster_workloads;

  // each cluster has at least one machine
  for (int i=0;i<cluster_num;++i) {
    cluster_workloads.push(Cluster(workloads[i],1));
    -- machine_num;// reduce machine number
  }
  // always add machine to the cluster which has maximum workload
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
  vector<int> workloads = {200,450};
  int cluster_num = 2, machine_num = 7;
  assert(AdjustWorkload(workloads,cluster_num,machine_num) == 100);

  // test 2
  workloads = {200,450,300,720};
  cluster_num = 4, machine_num = 10;
  assert( AdjustWorkload(workloads,cluster_num,machine_num) == 200 );
}

int main() {
  UnitTest();
  return 0;
}
