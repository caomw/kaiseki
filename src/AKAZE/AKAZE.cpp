#include "AKAZE.hpp"

#include <AKAZE.h>
#include <config.h>
#include <DO/ImageProcessing.hpp>

using namespace std;

namespace DO {

  vector<OERegion>
  AKAZEFeatureDetector::run(const Image<unsigned char>& image)
  {
    using namespace cv;
    
    // Set nonlinear scale space parameters for AKAZE.
    AKAZEOptions options;
    options.omin = firstOctave;

    Image<unsigned char> temp;
    temp = enlarge(image, 2.);

    if (numOctaves == -1)
    {
      const int l = min(temp.width(), temp.height());
      const int b = 1;
      numOctaves = static_cast<int>(log(l/(2.f*b))/log(2.f));
    }

    options.omax = firstOctave + numOctaves;
    options.nsublevels = numScales;
    options.img_width = temp.width();
    options.img_height = temp.height();

    // Default options
    options.soffset = DEFAULT_SCALE_OFFSET;
    options.dthreshold = DEFAULT_DETECTOR_THRESHOLD;
    options.diffusivity = DEFAULT_DIFFUSIVITY_TYPE;
    options.descriptor = DEFAULT_DESCRIPTOR;
    options.descriptor_size = DEFAULT_LDB_DESCRIPTOR_SIZE;
    options.descriptor_channels = DEFAULT_LDB_CHANNELS;
    options.descriptor_pattern_size = DEFAULT_LDB_PATTERN_SIZE;
    options.sderivatives = DEFAULT_SIGMA_SMOOTHING_DERIVATIVES;
    options.upright = DEFAULT_UPRIGHT;
    options.save_scale_space = DEFAULT_SAVE_SCALE_SPACE;
    options.save_keypoints = DEFAULT_SAVE_KEYPOINTS;
    options.verbosity = DEFAULT_VERBOSITY;

    // Create the nonlinear scale space for AKAZE.
    AKAZE evolution(options);

    // Convert the image to float
    Mat img, img_32, img_rgb;
    img = Mat(temp.height(), temp.width(), CV_8UC1, (void *) temp.data());

    img.convertTo(img_32,CV_32F,1.0/255.0,0);
    img_rgb = Mat(Size(img.cols,img.rows),CV_8UC3);	
    vector<cv::KeyPoint> kpts;

    HighResTimer timer;
    double detectionTime;

    // Create the nonlinear Gaussian scale space.
    timer.restart();
    evolution.Create_Nonlinear_Scale_Space(img_32);
    evolution.Feature_Detection(kpts);
    detectionTime = timer.elapsedMs();
    
    evolution.Show_Computation_Times();

    cout << "Number of points: " << kpts.size() << endl;
    cout << "Time Detector: " << detectionTime << " ms" << endl;

    vector<OERegion> features(kpts.size());
    for (size_t i = 0; i < features.size(); ++i)
    {
      features[i].center().x() = kpts[i].pt.x/2.f;
      features[i].center().y() = kpts[i].pt.y/2.f;
      features[i].extremumValue() = kpts[i].response;
      features[i].orientation() = kpts[i].angle;
      features[i].shapeMat() = Matrix2f::Identity() / pow(kpts[i].size, 2);
    }
    return features;
  }

} /* namespace DO */