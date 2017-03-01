BEGIN_NAMESPACE_ACADO

Model::Model(bool const isPWD){
	
	
	// INTRODUCE THE VARIABLES:
	// -------------------------
	
	if(isPWD){
		DifferentialState x,y,z, vx,vy,vz, phi,theta,psi, p,q,r;
		
		AlgebraicState ax,ay,az;
		
		// x, y, z : position
		// vx, vy, vz : linear velocity
		// phi, theta, psi : orientation (Yaw-Pitch-Roll = Euler(3,2,1))
		// p, q, r : angular velocity
		// u1, u2, u3, u4 : velocity of the propellers
		Disturbance u1,u2,u3,u4; // Pour pouvoir recuperer le control
		// vu1, vu2, vu3, vu4 : derivative of u1, u2, u3, u4
		
		
		f << dot(x) == vx;
		f << dot(y) == vy;
		f << dot(z) == vz;
		f << dot(phi) == -cos(phi)*tan(theta)*p+sin(phi)*tan(theta)*q+r;
		f << dot(theta) == sin(phi)*p+cos(phi)*q;
		f << dot(psi) == cos(phi)/cos(theta)*p-sin(phi)/cos(theta)*q;
		f << dot(p) == (d*Cf*(u1*u1-u2*u2)+(Jy-Jz)*q*r)/Jx;
		f << dot(q) == (d*Cf*(u4*u4-u3*u3)+(Jz-Jx)*p*r)/Jy;
		f << dot(r) == (c*(u1*u1+u2*u2-u3*u3-u4*u4)+(Jx-Jy)*p*q)/Jz;
		f << dot(vx) = ax ;
		f << dot(vy) = ay ;
		f << dot(vz) = az ;
		f << ax == Cf*(u1*u1+u2*u2+u3*u3+u4*u4)*sin(theta)/m;
		f << ay == -Cf*(u1*u1+u2*u2+u3*u3+u4*u4)*sin(psi)*cos(theta)/m;
		f << az == Cf*(u1*u1+u2*u2+u3*u3+u4*u4)*cos(psi)*cos(theta)/m - g;
		
		
		ym << cos(theta)*cos(psi)*(ax-g) + cos(theta)*sin(psi)*(ay-g)
				-sin(theta)*(az-g);
		ym << (sin(phi)*sin(theta)*cos(psi) - cos(phi)*sin(psi))*(ax-g)
			+ (sin(phi)*sin(theta)*sin(psi) + cos(phi)*cos(psi))*(ay-g) 
			+ sin(phi)*cos(theta)*(az-g);
		ym << (cos(phi)*sin(theta)*cos(psi) + sin(phi)*sin(psi))*(ax-g)
			+ (cos(phi)*sin(theta)*sin(psi) - sin(phi)*cos(psi))*(ay-g) 
			+ cos(phi)*cos(theta)*(az-g);	
		ym << p;
		ym << q;
		ym << r;
		ym << getStandardPressure(z); 
		
		
		
	}else{
		
		DifferentialState x,y,z,phi,theta,psi;
		
		AlgebraicState ax,ay,az;
		
		// x, y, z : position
		// vx, vy, vz : linear velocity
		// phi, theta, psi : orientation (Yaw-Pitch-Roll = Euler(3,2,1))
		// p, q, r : angular velocity

		Disturbance u_vx, u_vy, u_vz, u_p, u_q, u_r ; // Pour pouvoir recuperer le control

		
		
		f << dot(x) == u_vx;
		f << dot(y) == u_vy;
		f << dot(z) == u_vz;
		f << dot(phi) == -cos(phi)*tan(theta)*u_p+sin(phi)*tan(theta)*u_q+u_r;
		f << dot(theta) == sin(phi)*u_p+cos(phi)*u_q;
		f << dot(psi) == cos(phi)/cos(theta)*u_p-sin(phi)/cos(theta)*u_q;
		f << ax = dot(u_vx);
		f << ay = dot(u_vy);
		f << az = dot(u_vz);
		
		ym << cos(theta)*cos(psi)*(ax-g) + cos(theta)*sin(psi)*(ay-g)
				-sin(theta)*(az-g);
		ym << (sin(phi)*sin(theta)*cos(psi) - cos(phi)*sin(psi))*(ax-g)
			+ (sin(phi)*sin(theta)*sin(psi) + cos(phi)*cos(psi))*(ay-g) 
			+ sin(phi)*cos(theta)*(az-g);
		ym << (cos(phi)*sin(theta)*cos(psi) + sin(phi)*sin(psi))*(ax-g)
			+ (cos(phi)*sin(theta)*sin(psi) - sin(phi)*cos(psi))*(ay-g) 
			+ cos(phi)*cos(theta)*(az-g);	
		ym << p;
		ym << q;
		ym << r;
		ym << getStandardPressure(z);
		
		
		
		
		}

	
	}	
	
	DifferentialEquation Model::getDiffEq() const{
		return f;	
	}
	

	
	OutputFcn Model::getOutPutEq() const{
		return ym
	}
	

	
	
	
