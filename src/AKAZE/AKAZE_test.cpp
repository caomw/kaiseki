#include "AKAZE.hpp"
#include <DO/Core.hpp>
#include <DO/Graphics.hpp>

using namespace DO;
using namespace std;

#ifdef DATASETS_DIR
const string datasetsDirPath( SP_EVAL(DATASETS_DIR) );
#endif

const int NUM_FOLDERS = 9;
const string folders[NUM_FOLDERS] = { 
  "bark", "bikes", "boat", "graf", "leuven", "trees", "ubc", "wall", "iguazu"
};

int main()
{
  cout << datasetsDirPath << endl;

  for (int i = 1; i <= 6; ++i)
  {
    const string filepath = datasetsDirPath + "/" + folders[3] + "/" + "img" + toString(i) + ".ppm";
    cout << filepath << endl;

    Image<Rgb8> img;
    if (!load(img, filepath))
    {
      cerr << "Error: cannot load image" << endl;
      return -1;
    }

    if (!activeWindow())
      setAntialiasing(openWindow(img.width(), img.height()));
    else
      resizePaintingWindow(activeWindow(), img.width(), img.height());
    display(img);
    getKey();

    vector<OERegion> features;
    AKAZEFeatureDetector detector;
    features = detector.run(img.convert<unsigned char>());

    for (size_t i = 0; i < features.size(); ++i)
      features[i].drawOnScreen(Red8);
    getKey();
  }

  return 0;
}