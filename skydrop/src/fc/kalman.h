/*
 * kalman.h
 *
 *  Created on: Mar 2, 2017
 */

#ifndef FC_KALMAN_H_
#define FC_KALMAN_H_

class KalmanFilter {
public:


	float z_;  		// position
	float v_;  		// velocity
	float aBias_; 	// acceleration

    float zAccelBiasVariance_; 	// assumed fixed.
	float zAccelVariance_;  	// dynamic acceleration variance
	float zVariance_; 			//  z measurement noise variance fixed

	// 3x3 State Covariance matrix
	float Pzz_;
	float Pzv_;
	float Pza_;
	float Pvz_;
	float Pvv_;
	float Pva_;
	float Paz_;
	float Pav_;
	float Paa_;

    KalmanFilter();
    void Configure(float zVariance, float zAccelVariance, float zAccelBiasVariance, float zInitial, float vInitial, float aBiasInitial);
    void Update(float z, float a, float dt, float* pZ, float* pV);

};



#endif /* FC_KALMAN_H_ */
