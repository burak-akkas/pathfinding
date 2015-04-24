class Vector2D {
private:
	double x;
	double y;

public:
	Vector2D() : x(0.0), y(0.0) { }
	Vector2D(double t_x, double t_y) : x(t_x), y(t_y) { }

	// sets x and y to zero
	void 	Zero();

	// returns true if both x and y are zero
	bool 	isZero();

	// returns the length of the vector
	double 	Length();

	// returns the squared length of the vector
	double 	LengthSq();

	// returns the distance between this vector and the one passed as a parameter
	double 	Distance(const Vector2D& v2);

	// copies given Vector2D
	void copy(Vector2D rhs);

	// Getter
	double getX();
	double getY();

	// Setter
	void setX(double t_x);
	void setY(double t_y);

	// operators for vector operations
	const Vector2D& operator+=(const Vector2D& rhs);
	const Vector2D& operator-=(const Vector2D& rhs);
	const Vector2D& operator*=(const double& rhs);
	const Vector2D& operator/=(const double& rhs);
	bool operator==(const Vector2D& rhs) const;
	bool operator!=(const Vector2D& rhs) const;
};