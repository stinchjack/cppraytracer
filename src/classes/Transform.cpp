#include "Transform.hpp
Transform::setShift (Point &p) {
  doShift = true;
  shift = p;
}

Point Transform::transform(Point &p) {
  
  if (doShift) {
    return p + shift;
  }
  return p;
}


Point Transform::inverseTransform(Point &p) {
  
  if (doShift) {
    return p - shift;
  }
  return p;
}

Vector Transform::transform(Vector &v) {
  
  if (!doScale && !doRotate) {
    return Vector(v);
  }
  if (doScale && !doRotate) {
    return Vector * scale;
  }

}

/*

class RotationMatrix(Matrix):
    """A matrix for rotation about an arbitrary axis.
        See http://math.kennesaw.edu/~plaval/math4490/rotgen.pd"""

    def __init__(self, vector, angle):
        """Class constructor for RotationMatrix.
        :param vector: a cartesian vector as an axis.
        :param angle: the amount of rotation about the axis,
                      in degrees"""
        # rad = mpfr(angle) *(self.pi/mpfr(180))
        rad = radians(angle)
        one = mpfr(1)
        zero = mpfr(0)
        t = one - cos(rad)
        S = sin(rad)
        C = cos(rad)
        u2x = mpfr(vector[1]) * mpfr(vector[1])
        u2y = mpfr(vector[2]) * mpfr(vector[2])
        u2z = mpfr(vector[3]) * mpfr(vector[3])
        ux = mpfr(vector[1])
        uy = mpfr(vector[2])
        uz = mpfr(vector[3])

        c1 = (t * u2x) + C
        c2 = (t * ux * uy) - (S * uz)
        c3 = (t * ux * uz) + (S * uy)

        c4 = (t * ux * uy) + (S * uz)
        c5 = (t * u2y) + C
        c6 = (t * uy * uz) - (S * ux)

        c7 = (t * ux * uz) - (S * uy)
        c8 = (t * uy * uz) + (S * ux)
        c9 = (t * u2z) + C

        self.matrix = [[c1, c2, c3, zero],
                       [c4, c5, c6, zero],
                       [c7, c8, c9, zero],
                       [zero, zero, zero, one]]

        rad = zero - rad
        t = one - cos(rad)
        S = sin(rad)
        C = cos(rad)

        c1 = (t * u2x) + C
        c2 = (t * ux * uy) - (S * uz)
        c3 = (t * ux * uz) + (S * uy)

        c4 = (t * ux * uy) + (S * uz)
        c5 = (t * u2y) + C
        c6 = (t * uy * uz) - (S * ux)

        c7 = (t * ux * uz) - (S * uy)
        c8 = (t * uy * uz) + (S * ux)
        c9 = (t * u2z) + C

        self.inverse = [[c1, c2, c3, zero],
                        [c4, c5, c6, zero],
                        [c7, c8, c9, zero],
                        [zero, zero, zero, one]]
*/
