#include <bits/stdc++.h>
#define PI acos(-1)
#define base complex<double>
using namespace std;

void fft(vector<base> &a, bool invert) {
    int n = a.size();
    
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        while (j >= bit) {
            j -= bit;
            bit >>= 1;
        }
        j += bit;
        if (i < j) swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double angle = 2 * PI / len * (invert ? -1 : 1);
        base wlen(cos(angle), sin(angle));
        for (int i = 0; i < n; i += len) {
            base w(1);
            for (int j = 0; j < len/2; j++) {
                base u = a[i+j];
                base v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (int i = 0; i < n; i++)
            a[i] /= n;
    }
}

vector<int> multiply(vector<int> &a, vector<int> &b) {
    vector<base> fa(a.begin(), a.end());
    vector<base> fb(b.begin(), b.end());
    
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);

    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];

    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cout << "첫 번째 다항식의 차수를 입력하세요: ";
    cin >> n;
    
    cout << "첫 번째 다항식의 계수를 입력하세요 (차수 0부터): ";
    vector<int> a(n + 1);
    for (int i = 0; i <= n; i++)
        cin >> a[i];

    cout << "두 번째 다항식의 차수를 입력하세요: ";
    cin >> m;
    
    cout << "두 번째 다항식의 계수를 입력하세요 (차수 0부터): ";
    vector<int> b(m + 1);
    for (int i = 0; i <= m; i++)
        cin >> b[i];

    vector<int> result = multiply(a, b);

    cout << "곱셈 결과: ";
    for (int i = 0; i <= n + m; i++) {
        if (i > 0 && result[i] >= 0) cout << "+";
        if (result[i]) {
            cout << result[i];
            if (i > 0) cout << "x";
            if (i > 1) cout << "^" << i;
        }
    }
    cout << "\n";

    return 0;
}