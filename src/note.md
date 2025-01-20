6.8测试版：
    测试了修改后的软启动，修改内容是添加实际速度与目标速度同向的速度控制，结果是效果并不显著
    测试了新加入的卡尔曼滤波代码，用于直线行驶，改善now变量，结果是出现未知错误导致程序中断
    从串口反馈数据看具体为：assertion "cols() == B.rows()" failed: file "src/math/Matrix.cpp", line 16, function: Matrix Matrix::multiply(const Matrix &) const