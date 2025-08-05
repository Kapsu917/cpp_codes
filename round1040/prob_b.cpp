#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int main()
{

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        long long s;
        cin >> n >> s;

        int c0 = 0, c1 = 0, c2 = 0;
        for (int i = 0; i < n; ++i)
        {
            int val;
            cin >> val;
            if (val == 0)
                c0++;
            else if (val == 1)
                c1++;
            else
                c2++;
        }

        long long total_sum = (long long)c1 * 1 + (long long)c2 * 2;

        if (s < total_sum)
        {
            for (int i = 0; i < c0; ++i)
                cout << 0 << " ";
            for (int i = 0; i < c1; ++i)
                cout << 1 << " ";
            for (int i = 0; i < c2; ++i)
                cout << 2 << (i == c2 - 1 ? "" : " ");
            cout << endl;
        }
        else if (s == total_sum + 1)
        {
            for (int i = 0; i < c0; ++i)
                cout << 0 << " ";
            for (int i = 0; i < c2; ++i)
                cout << 2 << " ";
            for (int i = 0; i < c1; ++i)
                cout << 1 << (i == c1 - 1 ? "" : " ");
            cout << endl;
        }
        else
        {
            cout << -1 << endl;
        }
    }

    return 0;
}
