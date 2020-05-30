#include "utils/ImageTools.h"
#include "utils/FastImage.h"

float fast_mod_2pi(float x) {
    while(x < 0 ) x += 2*(float)CV_PI;
    while(x > 2*(float)CV_PI) x -= 2*(float)CV_PI;
    return x ;
}

cv::Rect ImageTools::CImageTools::GetDrawingROI( const vector<cv::Point2i>& _points ) {
    int x1 = 100000;
    int y1 = 100000;
    int x2 = 0;
    int y2 = 0;

    FOR (i, (int)_points.size()) {
        x1 = min(x1, _points[i].x);
        y1 = min(y1, _points[i].y);
        x2 = max(x2, _points[i].x);
        y2 = max(y2, _points[i].y);
    }

    return cv::Rect(x1, y1, x2 - x1 + 1, y2 - y1 + 1);
}

cv::Mat ImageTools::CImageTools::TranslateImage( const cv::Mat& _img, PointF _t) {
    if (_t == PointF(0,0))
        return _img;
    else {
        cv::Mat out;
        cv::Mat H = cv::Mat::zeros(2, 3, CV_64FC1);
        H.at<double>(0, 0) = 1.0; H.at<double>(1, 1) = 1.0;
        H.at<double>(0, 2) = _t.x; H.at<double>(1, 2) = _t.y;
        warpAffine(_img, out, H, _img.size(), 1, 0, cv::Scalar(0, 0, 0));
        return out;
    }
}



cv::Mat ImageTools::CImageTools::Float2Unit( const cv::Mat& _img ) {
    cv::Mat outImg_int;
    if (_img.channels() == 3)
        _img.convertTo(outImg_int, CV_8UC3);
    else {
        _img.convertTo(outImg_int, CV_8UC1);
        outImg_int = 255 - outImg_int;
    }
    return outImg_int;
}

cv::Mat ImageTools::CImageTools::ScaleImage( const cv::Mat& _img, float _scale ) {
    cv::Mat out;
    if (abs(_scale-1.0f) < 1e-10f)
        out = _img;
    else {
        cv::Mat img_s;
        cv::resize(_img, img_s, cv::Size(), _scale, _scale);
        out = cv::Mat::zeros(_img.size(), _img.type());
        int x = (_img.cols - img_s.cols)/2;
        int y = (_img.rows- img_s.rows)/2;
        if (_scale < 1.0f)
            img_s.copyTo(out(cv::Rect(x, y, img_s.cols, img_s.rows)));
        else
            img_s(cv::Rect(-x, -y, _img.cols, _img.rows)).copyTo(out);
    }

    return out;
}

cv::Rect ImageTools::CImageTools::Mask2ROI(const cv::Mat& _mask) {
    cv::Mat gray = _mask.clone();
    vector<vector<cv::Point> > contours;
    vector<cv::Vec4i> hierarchy;
    findContours(gray, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
    int xmin = 100000;
    int ymin = 100000;
    int xmax = -1;
    int ymax = -1;
    FOR_u (i, contours.size()) {
        FOR_u (j, contours[i].size()) {
            xmin = min(xmin, contours[i][j].x);
            xmax = max(xmax, contours[i][j].x);
            ymin = min(ymin, contours[i][j].y);
            ymax = max(ymax, contours[i][j].y);
        }
    }
    cv::Rect roi;
    roi.x = xmin;
    roi.y = ymin;
    roi.width = xmax - xmin + 1;
    roi.height = ymax - ymin +1;
    return roi;
}

PointF ImageTools::CImageTools::ROICenter(cv::Rect roi) {
    return PointF(roi.x+0.5f*(roi.width-1),roi.y+0.5f*(roi.height-1));
}

bool ImageTools::CImageTools::IsValidPoint(PointF _p, cv::Size _imgSz) {
    return _p.x >= 0 && _p.y >= 0 && _p.x <= _imgSz.width && _p.y <= _imgSz.height;
}



bool ImageTools::CImageTools::IsValidROI( cv::Rect _roi, cv::Size _imgSz ) {
    if (_roi.x < 0 || _roi.y < 0 || _roi.x +_roi.width-1 >= _imgSz.width
            || _roi.y + _roi.height - 1 >= _imgSz.height) //check
        return false;
    if (_roi.width <= 0 || _roi.height <= 0)
        return false;
    return true;
}

cv::Mat ImageTools::CImageTools::IncreaseContrast( const cv::Mat& _img ) {   // increase contrast
    float alpha = 1.25f;
    float beta = -25.0f;
    cv::Mat img_f, out;
    _img.convertTo(img_f, CV_32F);
    img_f = (img_f + beta) * alpha;
    img_f.convertTo(out, CV_8U);
    return out;
}


cv::Rect ImageTools::CImageTools::RecfityROI( cv::Rect _roi, cv::Size _imgSz ) {
    cv::Rect out;
    int x2, y2;
    x2 = min(_imgSz.width-1, _roi.x + _roi.width-1);
    y2 = min(_imgSz.height-1, _roi.y+_roi.height-1);
    out.x = max(0, _roi.x);
    out.y = max(0, _roi.y);
    out.width = x2 - out.x  + 1;
    out.height = y2 - out.y + 1;
    return out;
}
