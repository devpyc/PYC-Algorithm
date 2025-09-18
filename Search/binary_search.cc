#include <bits/stdc++.h>
using namespace std;

// 반복문
int binarySearch(vector<int> &arr, int target)
{
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
        {
            return mid;
        }
        else if (arr[mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return -1;
}

// 재귀 
int binarySearchRecursive(vector<int> &arr, int target, int left, int right)
{
    if (left > right)
        return -1;

    int mid = left + (right - left) / 2;

    if (arr[mid] == target)
    {
        return mid;
    }
    else if (arr[mid] < target)
    {
        return binarySearchRecursive(arr, target, mid + 1, right);
    }
    else
    {
        return binarySearchRecursive(arr, target, left, mid - 1);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cout << "배열의 크기를 입력하세요: ";
    cin >> n;

    vector<int> arr(n);
    cout << "정렬된 배열을 입력하세요: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "찾을 원소의 개수를 입력하세요: ";
    cin >> m;

    cout << "찾을 원소들을 입력하세요: ";
    for (int i = 0; i < m; i++)
    {
        int target;
        cin >> target;

        int result1 = binarySearch(arr, target);
        cout << target << "의 일반 이분 탐색 결과: ";
        if (result1 != -1)
        {
            cout << result1 << "번 인덱스\n";
        }
        else
        {
            cout << "찾지 못함\n";
        }

        int result2 = binarySearchRecursive(arr, target, 0, n - 1);
        cout << target << "의 재귀 이분 탐색 결과: ";
        if (result2 != -1)
        {
            cout << result2 << "번 인덱스\n";
        }
        else
        {
            cout << "찾지 못함\n";
        }

        auto lower = lower_bound(arr.begin(), arr.end(), target);
        auto upper = upper_bound(arr.begin(), arr.end(), target);
        cout << target << "의 개수: " << upper - lower << "\n";
        cout << "----------------\n";
    }

    return 0;
}