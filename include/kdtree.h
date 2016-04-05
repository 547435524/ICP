#ifndef KDTREE_H
#define KDTREE_H
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <iomanip>
#define swap(p1, p2) \
{float t;\
  t = (p1).x; (p1).x = (p2).x; (p2).x = t;\
  t = (p1).y; (p1).y = (p2).y; (p2).y = t;\
  t = (p1).z; (p1).z = (p2).z; (p2).z = t;}
#define printpoint(p) std::setw(4) << (p).x << " " << std::setw(4) << (p).y \
  << " " << std::setw(4) << (p).z
#define printpoints(p) {\
  for (size_t i=0; i<(p).size(); i++) {\
    std::cerr << printpoint((p)[i]) << std::endl;\
  }}

typedef std::vector<pcl::PointXYZ, Eigen::aligned_allocator<pcl::PointXYZ>> point_vector;

class KDTree {
  public:
    static float select(point_vector& points, int dim, size_t start, size_t end,
        size_t k);
    void build_tree(KDTree* root, point_vector& points, size_t start, size_t end,
        unsigned depth);

    unsigned depth;
    float bound;
    KDTree* left;
    KDTree* right;
    KDTree* root;
    point_vector points;

    KDTree() : depth(0), bound(0.f), left(NULL), right(NULL), root(NULL) {}

    void setInputCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
    void nearestKSearch(pcl::PointXYZ point, int k, std::vector<int> nearest_i,
        std::vector<float> nearest_d);

};

std::ostream& operator<<(std::ostream &strm, const KDTree &kdtree) {
  if (kdtree.depth == 0) {
    for (size_t i=0; i<kdtree.points.size(); i++) {
      strm << printpoint(kdtree.points[i]) << std::endl;
    }
  }
  for (unsigned int i=0; i<kdtree.depth; i++) {
    strm << " ";
  }

  /*
  switch (kdtree.depth%3) {
    case 0: strm << "x " ; break;
    case 1: strm << "y " ; break;
    case 2: strm << "z " ; break;
  }
  */
  strm << "KDtree " << kdtree.depth << " ";

  strm << kdtree.bound;
  if (kdtree.left != NULL) {
    strm << std::endl << *kdtree.left;
  }
  if (kdtree.right != NULL) {
    strm << std::endl << *kdtree.right;
  }
  return strm;
}

#endif