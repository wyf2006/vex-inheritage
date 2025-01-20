#ifndef KALMANFILTER_H
#define KALMANFILTER_H
#include <iostream>
#include <vector>
#include "Matrix.h"

class KalmanFilter {//卡尔曼滤波器
protected:
    Matrix K;// 卡尔曼增益
public:
    Matrix F;// 状态转移矩阵 
    Matrix H;// 观测矩阵
    Matrix Q;// 过程噪声协方差矩阵
    Matrix R;// 测量噪声协方差矩阵
    Matrix B;// 控制输入矩阵
    Matrix u;// 控制向量
    Matrix x;// 状态向量
    Matrix P;// 协方差矩阵

    KalmanFilter(const Matrix& a, const Matrix& b, const Matrix& c, const Matrix& d , const Matrix& e): 
    F(a), H(b), Q(c), R(d),B(e) {}

    void initialize(const std::vector<double>& x0, const Matrix& P0);

    /// @brief 进行预测
    void predict(double u);
    void predict(const Matrix &u);

    /// @brief 更新数值，传入一个向量
    /// @param z 传入的向量，直接使用 vector 即可
    void update(const std::vector<double>& z);
    void update(const Matrix &z);

    /// @brief 获取预测状态
    std::vector<double> getState() const;
};
#endif