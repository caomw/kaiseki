// ========================================================================== //
// This file is part of DO++ MatchPropagation which was presented in:
//
//  Efficient and Scalable 4th-order Match Propagation
//  David Ok, Renaud Marlet, and Jean-Yves Audibert.
//  ACCV 2012, Daejeon, South Korea.
//
// Copyright (c) 2013. David Ok, Imagine (ENPC/CSTB).
// ===========================================================================

#include "StudyOnMikolajczykDataset.hpp"

using namespace std;
using namespace DO;

const int NUM_FOLDERS = 9;
const int NUM_FEAT_EXT = 4;
const int NUM_IMAGES_PER_DATASET = 6;

const string dataset_folder = "C:/Users/David/Desktop/GitHub/FeaturePerf/datasets";
const string folders[NUM_FOLDERS] = { 
  "bark", "bikes", "boat", "graf", "leuven", "trees", "ubc", "wall", "iguazu"
};
const string ext[NUM_FEAT_EXT] = { ".dog", ".haraff", ".hesaff", ".mser" };

class TestFeatures : public StudyOnMikolajczykDataset
{
public:
  TestFeatures(const string& absParentFolderPath,
               const string& name,
               const string& featType)
    : StudyOnMikolajczykDataset(absParentFolderPath, name, featType)
  {}

  void operator()()
  {
    for (int j = 1; j < NUM_IMAGES_PER_DATASET; ++j)
    {
      // View the image pair.
      openWindowForImagePair(0, j);
      PairWiseDrawer drawer(dataset().image(0), dataset().image(j));
      drawer.setVizParams(1.0f, 1.0f, PairWiseDrawer::CatH);
      drawer.displayImages();
      {
        // Read the set of keypoints $/mathcal{X}$ in image 1.
        const vector<Keypoint>& X = dataset().keys(0);
        // Read the set of keypoints $\mathcal{Y}$ in image 2.
        const vector<Keypoint>& Y = dataset().keys(j);
        // Compute initial matches.
        vector<Match> M(computeMatches(X, Y, 1.2f*1.2f));
        // Get inliers and outliers.
        vector<size_t> inliers, outliers;
        getInliersAndOutliers(inliers, outliers, M, dataset().H(j), 1.5f);
        cout << "inliers.size() = " << inliers.size() << endl;
        cout << "outliers.size() = " << outliers.size() << endl;
        // View inliers.
        for (size_t i = 0; i != inliers.size(); ++i)
          drawer.drawMatch(M[inliers[i]]);
        getKey();
      }
      closeWindowForImagePair();
    }
  }
};

int main()
{
  TestFeatures test(dataset_folder, 
                  folders[0], ext[1]);
  test();
  return 0;
}