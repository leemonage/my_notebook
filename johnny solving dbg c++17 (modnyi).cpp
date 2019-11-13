template<typename... Ts> void _dbg(const char* s, Ts... ts) {
    auto run=[&s](){for(int b=0;*s&&((b+=(*s=='(')-(*s==')'))!=0||*s!=',');cerr<<*s++);};
    ((run(), cerr << " = " << forward<Ts>(ts) << ",\n"[*s++ == '\0'] ), ...);
}

#ifdef LOCAL
    #define dbg(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
    #define dbg(...)
#endif
