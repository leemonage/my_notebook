// mozhet ne skompilit'sya

long long mul(long long a, long long b, long long mod) {
    auto k = static_cast<long long>(static_cast<long double>(a) * b / mod);
    auto r = a * b - mod * k;
    for (; r < 0; r += mod) { }
    for (; r >= mod; r -= mod) { }
    return r;
}
