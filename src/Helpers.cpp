#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <string.h>
#include <sstream>
#include <time.h>

void findAndReplaceAll(std::string& s,const std::string to_replace,const std::string replacement)
{
  size_t pos = s.find(to_replace);;
  while((int)pos > (-1))
  {
    s.replace(pos, to_replace.length(), replacement);
    pos = s.find(to_replace);
  }
}

std::string getTimeString()
{
  time_t raw_time;
  struct tm timeinfo;
  char buffer[20];
  time(&raw_time);
  localtime_s(&timeinfo, &raw_time);
  strftime(buffer, 20, "%Y-%m-%d_%H-%M-%S", &timeinfo);

//  std::string time_str = ctime(&raw_time);
  std::string time_str = std::string(buffer);
  std::cout << "Time str " << time_str;
  time_str = time_str.erase(time_str.length()-1,1);
  findAndReplaceAll(time_str,std::string(" "),std::string("_"));
  findAndReplaceAll(time_str,std::string(":"),std::string("-"));
  return time_str;
}

/**
* Rotate an image
*/
void rotate(cv::Mat& src, double angle, cv::Mat& dst)
{
  if (angle < 0.0001)
  {
    dst = src.clone();
    return;
  }
  int len = cv::max(src.cols, src.rows);
  cv::Point2f pt((float)(len / 2.), (float)(len / 2.));
  cv::Mat r = cv::getRotationMatrix2D(pt, angle, 1.0);

  cv::warpAffine(src, dst, r, cv::Size(len, len));
}