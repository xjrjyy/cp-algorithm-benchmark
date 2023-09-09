#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

template <typename T> struct Fenwick {
    int n;
    std::vector<T> t;
    Fenwick(int n_) : n{n_}, t(n) {}
    void add(int p, T x) {
        for (++p; p <= n; p += p & -p) {
            t[p - 1] += x;
        }
    }
    T sum(int p) const {
        T x{};
        for (; p; p -= p & -p) {
            x += t[p - 1];
        }
        return x;
    }
    T rangeSum(int l, int r) const {
        return sum(r) - sum(l);
    }
};

int main(int argc, char *argv[]) {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    assert(argc >= 4);

    u32 seed = std::stoul(argv[1]);
    std::mt19937 rnd(seed);

    int n = std::stoul(argv[2]), q = std::stoul(argv[3]);
    assert(n >= 1 && q >= 1);

    Fenwick<u32> fen(n);
    for (int i = 0; i < n; ++i) {
        fen.add(i, rnd());
    }

    u32 xor_sum = 0;
    while (q--) {
        int op = rnd() % 2;

        if (op == 0) {
            int p = rnd() % n;
            u32 x = rnd();
            fen.add(p, x);
        }
        if (op == 1) {
            int l = rnd() % n, r = rnd() % n;
            if (l > r) {
                std::swap(l, r);
            }
            ++r;
            u32 ans = fen.rangeSum(l, r);
            xor_sum ^= ans;
        }
    }

    std::clog << "Xor Sum: " << xor_sum << std::endl;

    return 0;
}
