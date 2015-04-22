struct Vector2D {
	double x;
	double y;

	Vector2D() :x(0.0), y(0.0) {	}

	// sets x and y to zero
	inline void 	Zero();

	// returns true if both x and y are zero
	inline bool 	isZero() const;

	// returns the length of the vector
	inline double 	Length() const;

	// returns the squared length of the vector
	inline double 	LengthSq() const;

	// returns positive if vector 2 is clockwise of this vector,
	// 		   negative if counter-clockwise
	inline int 		Sign(const Vector2D& v2) const;

	// returns the vector that is perpendicular to this one
	inline Vector2D	Perp() const;

	// adjusts x and y so that the length of the vector does not exceed max
	inline void 	Truncate(double max);

	// returns the distance between this vector and the one passed as a parameter
	inline void 	Distance(const Vector2D& v2) const;

	// square version of distance
	inline void 	DistanceSq(const Vector2D& v2) const;

	// returns the vector that is the reverse of this vector
	inline Vector2D GetReverse() const;

	// operators for vector operations
	const Vector2D& operator+=(const Vector2D& rhs);
	const Vector2D& operator-=(const Vector2D& rhs);
	const Vector2D& operator*=(const double& rhs);
	const Vector2D& operator/=(const double& rhs);
	bool operator==(const Vector2D& rhs) const;
	bool operator!=(const Vector2D& rhs) const;
};