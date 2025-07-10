inline double clamp(double d, double min, double max) {
    const double t = d < min ? min : d;
    return t > max ? max : t;
}
