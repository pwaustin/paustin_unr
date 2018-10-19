# kf.py updated file for robot estimation assignment
# pset[3]
# (C) 2017 David Feil-Seifer


import numpy as np
import math
from scipy import stats
import scipy.stats

# kf_update: update state estimate [u, sigma] with new control [xdot] and measurement [z]
# 	parameters:
#			u : 2x1 vector with state estimate (x) at time t-1 and control (xdot) at time t
#			sigma: 2x2 matrix with covariance at time t-1
#			z (int): observed (uncertain) measurement of state (x) at time t
#	returns: [u sigma] updated state with estimate at time t

def kf_update(u, sigma, z):

	#declare vars

	F = np.matrix([[1,1], [0,1]])
	H = np.matrix([1,0])
	I = np.matrix([[1,0], [0,1]])
	sigmaX = np.matrix([[.3,.3], [.3,.7]])
	sigmaZ = np.matrix([10])

	#calculate Kt+1
	
	K = ( ( F * sigma * F.transpose() ) + sigmaX ) * H.transpose() * np.linalg.inv( H * ( ( ( F * sigma * F.transpose() ) + sigmaX ) * H.transpose() ) + sigmaZ )

	#calculate ut+1

	u = (F * u) + ( K * (z - (H*F*u) ) )

	#calculate sigmat+1

	sigma = (I - (K*H)) * (F * sigma * F.transpose() + sigmaX )

	return [u, sigma]


# door_update: update estimate of door locations
# 	parameters:
#			u : 2x1 vector with state estimate (x) at time t-1 and control (xdot) at time t-1
#			sigma: 2x2 matrix with covariance at time t-1
#			d (binary): door sensor at time t-1 
#			door_dist (array of size 10): probability (0..1) that a door exists at each location (0..9)
#	returns: [door_dist] updated door distribution

def door_update(u, sigma, d, door_dist):

	#declare vars

	probSGD = .6
	probSGND = .8
	probNSGD = .4
	probNSGND = .2

	probSGD *= door_dist[int(u.item(0)) / 100]
	probNSGD *= door_dist[int(u.item(0)) / 100]
	probSGND *= 1 - door_dist[int(u.item(0)) / 100]
	probNSGND *= 1 - door_dist[int(u.item(0)) / 100]

	#if sensor is up at this loc, gain some confidence of door here

	if d == 1:
		door_dist[int(u.item(0)) / 100] = probSGD / (probSGD + probNSGND)

	#if sensor is down at this loc, lose some confidence of door here

	else:
		door_dist[int(u.item(0)) / 100] = probNSGD / (probNSGD + probSGND)
		

	return door_dist

