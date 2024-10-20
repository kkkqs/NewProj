#pragma once
#include <iostream>
#include <vector>
#include "Algorithm/Matrix.hpp"
#include "utils/BaseFilter.hpp"

class KalmanFilter;
class KalmanFilterPredictor;
class KalmanFilterInitializer;

#pragma region Helper
class KalmanFilterInitializer : BaseInitializer<Matrix, Matrix> {
    friend class KalmanFilter;
private:
    KalmanFilter* const _filter;
    KalmanFilterInitializer(KalmanFilter*);
public:
    void initialize(const Matrix& x0, const Matrix& P0) const;
};

class KalmanFilterPredictor : BasePredictor<Matrix, Matrix> {
    friend class KalmanFilter;
private:
    KalmanFilter* const _filter;
    Matrix& K;
    const Matrix& F;
    const Matrix& H;
    const Matrix& Q;
    const Matrix& R;
    const Matrix& B;
    const Matrix& u;
    Matrix& x;
    Matrix& P;
    KalmanFilterPredictor(KalmanFilter*);
public:
    void predict(const Matrix& u, const Matrix& z) const;
};
#pragma endregion

class KalmanFilter: public BaseFilter<KalmanFilterInitializer, KalmanFilterPredictor> {
    friend class KalmanFilterInitializer;
    friend class KalmanFilterPredictor;

private:
    mutable Matrix K;
    Matrix F;
    Matrix H;
    Matrix Q;
    Matrix R;
    Matrix B;
    Matrix u;
    mutable Matrix x;
    mutable Matrix P;

public:
    KalmanFilter(const Matrix& F, const Matrix& H, const Matrix& Q, const Matrix& R, const Matrix& B);
    float getResult() const override {return x[0][0];}
};