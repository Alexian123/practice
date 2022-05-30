int factorial(int n, int r) {
    return n == 0 ? r : factorial(n - 1, n * r);
}