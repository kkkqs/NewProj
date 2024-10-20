#include "Algorithm/Filter/KalmanFilter.hpp"

KalmanFilterInitializer::KalmanFilterInitializer(KalmanFilter* filter): _filter(filter) {}

void KalmanFilterInitializer::initialize(const Matrix& x0, const Matrix& P0) const {
    _filter->x = x0;
    _filter->P = P0;
}

KalmanFilterPredictor::KalmanFilterPredictor(KalmanFilter* filter): _filter(filter),
K(filter->K), F(filter->F), H(filter->H), Q(filter->H), R(filter->R), B(filter->B), u(filter->u), x(filter->x), P(filter->P) {}

void KalmanFilterPredictor::predict(const Matrix& u, const Matrix& z) const {
    x = F*x+(B*u);
    P = F.multiply(P).multiply(F.transpose()).add(Q);
    Matrix S = H*P*(H.transpose())+(R);
    K = P*(H.transpose())*(S.invert());
    x = x+K*(z-H*x);
    Matrix I = Matrix::identity(x.rows());
    P = (I-K*H)*P;
}

KalmanFilter::KalmanFilter(const Matrix& F, const Matrix& H, const Matrix& Q, const Matrix& R, const Matrix& B):
F(F), H(H), Q(Q), R(R),B(B) {
    FilterInitializer = new KalmanFilterInitializer(this);
    FilterPredictor = new KalmanFilterPredictor(this);
}