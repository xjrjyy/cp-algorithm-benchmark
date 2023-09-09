#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

int main(int argc, char *argv[]) {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    assert(argc >= 4);

    u32 seed = std::stoul(argv[1]);
    std::mt19937 rnd(seed);

    int n = std::stoul(argv[2]), q = std::stoul(argv[3]);
    assert(n >= 1 && q >= 1);

    std::map<int, u32> mp;
    for (int i = 0; i < n; ++i) {
        mp[i] = rnd();
    }
    mp.emplace(n, 0);

    auto split = [&](int l) {
        auto v = std::prev(mp.upper_bound(l))->second;
        return mp.emplace(l, v).first;
    };

    u32 xor_sum = 0;
    while (q--) {
        int op = rnd() % 2, l = rnd() % n, r = rnd() % n;
        if (l > r) {
            std::swap(l, r);
        }
        ++r;

        if (op == 0) {
            u32 x = rnd();
            auto il = split(l), ir = split(r);
            for (auto it = il; it != ir; it = mp.erase(it));
            mp[l] = x;
        }
        if (op == 1) {
            u32 ans = 0;
            auto il = split(l), ir = split(r);
            for (auto it = il; it != ir; ++it) {
                ans += it->second * u32(std::next(it)->first - it->first);
            }
            xor_sum ^= ans;
        }
    }

    std::clog << "Xor Sum: " << xor_sum << std::endl;

    return 0;
}
