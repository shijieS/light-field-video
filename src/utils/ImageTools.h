#ifndef IMAGE_TOOLS_H_
#define IMAGE_TOOLS_H_
#include "common.h"

namespace ImageTools
{
	class CImageTools {
	public: 
		static cv::Rect GetDrawingROI(const PointSeti& _points); 
		static cv::Mat TranslateImage( const cv::Mat& _img, PointF _p);
		static cv::Mat ScaleImage(const cv::Mat& _img, float _scale);
		static cv::Mat RandomImage(const cv::Mat& _img);
		static cv::Mat Float2Unit(const cv::Mat& _img);
		static bool IsValidROI(cv::Rect _roi, cv::Size _imgSz);
		static cv::Mat IncreaseContrast(const cv::Mat& _img);
		static cv::Rect RecfityROI(cv::Rect _roi, cv::Size _imgSz);
        static cv::Rect Mask2ROI(const cv::Mat& _mask);
        static PointF ROICenter(cv::Rect roi);
        static bool IsValidPoint(PointF _p, cv::Size _imgSz);
	};
}
#endif //IMAGE_TOOLS_H_
