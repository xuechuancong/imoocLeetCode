#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:

//    三路排序使用
    void sortColors2(vector<int>& nums) {
        int n = static_cast<int>(nums.size());

        int index1 = -1, index2 = n;
        int i = 0;
        while (i < index2 ) {
            if (nums[i] == 0 ) {
                index1 ++;
                swap(nums[i], nums[index1]);
                i ++;
            }
            else if(nums[i] == 1) {
                i ++;
            }
            else if( nums[i] == 2) {
                index2 --;
                swap(nums[i], nums[index2]);
            }

        }
    }

//    基数排序使用
    void sortColors1(vector<int>& nums) {
        int n = static_cast<int>(nums.size());

        vector<int> count(3, 0);
        for (int i = 0; i < n; ++i) {
            count[ nums[i] ] ++;
        }

        int index = 0;
        for (int j = 0; j < count[0]; ++j) {
            nums[index] = 0;
            index ++;
        }

        for (int k = 0; k < count[1]; ++k) {
            nums[index] = 1;
            index ++;
        }

        for (int l = 0; l < count[2]; ++l) {
            nums[index] = 2;
            index ++;
        }
    }

    void sortColors(vector<int>& nums) {
//        基数排序
        int n = static_cast<int>(nums.size());

        vector<int> count(3, 0);
        for (int i = 0; i < n; ++i) {
            count[ nums[i] ] ++;
        }

        int index = 0;
//      改进版本
        for (int m = 0; m < count.size(); ++m) {
            for (int i = 0; i < count[m]; ++i) {
                nums[index] = m;
                index ++;
            }
        }


    }

    int removeDuplicates1(vector<int>& nums) {
        int n = static_cast<int>(nums.size());

        //k是已经无重复数组的最后元素索引
        int k = -1;
        for (int i = 0; i < n; ++i) {

//            处理一下开始元素
            if(i < 1 || nums[i] != nums[k] ) {
                k++;
                swap(nums[ k ], nums[i]);

//                第一次交换完成后检查是否可以进行第二次重复元素交换
                if( nums[i+1] == nums[k] ) {
                    i ++;
                    k ++;

                    swap(nums[i], nums[k]);
                }
            }
        }

        for (int j = k+1; j < n; ++j) {
            nums.pop_back();
        }

        return static_cast<int>(nums.size());
    }

    int removeDuplicates(vector<int>& nums) {

        int n = static_cast<int>(nums.size());

        //k是已经无重复数组的最后元素索引
        int k = 0;
        for (int i = 1; i < n; ++i) {
            if( nums[i] != nums[k] ) {
                k++;
                swap(nums[ k ], nums[i]);
            }
        }

        for (int j = k+1; j < n; ++j) {
            nums.pop_back();
        }

        return static_cast<int>(nums.size());
    }

    int removeElement(vector<int>& nums, int val) {
        int n = static_cast<int>(nums.size());
        int k = 0;
        for (int i = 0; i < n; ++i) {
            if(nums[i] != val ) {
                swap(nums[i], nums[k]);
                k++;
            }
        }

        for (int j = k; j < n; ++j) {
            nums.pop_back();
        }

        return static_cast<int>(nums.size());
    }

    void moveZeroes2(vector<int>& nums) {

        int k = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if(nums[i] ) {
                nums[k] = nums[i];
                k++;
            }
        }

        for (int j = k; j < nums.size(); ++j) {
            nums[j] = 0;
        }
    }

//    时间复杂度O(n)
//      空间复杂度O(1)
    void moveZeroes1(vector<int>& nums) {

        int k = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if(nums[i] ) {
                //nums[k] = nums[i];
                //如果数组中基本没有0(i == k)的话怎么优化？
                if( i != k)
                    swap(nums[i], nums[k ++]);
                else
                    k++;
            }
        }


    }


//        使用辅助空间
    void moveZeroes(vector<int>& nums) {

        vector<int> newList;

        for (int i = 0; i < nums.size(); ++i) {
            if( nums[i] ) {
                newList.push_back(nums[i]);
            }
        }

        for (int j = 0; j < newList.size(); ++j) {
            nums[j] = newList[j];
        }

        for (int l = static_cast<int>(newList.size()); l < nums.size(); ++l) {
            nums[l] = 0;
        }
    }

// 对于一个有序循环数组arr，返回arr中的最小值。
// 有序循环数组是指，有序数组左边任意长度的部分放到右边去，右边的部分拿到左边来。
// 比如数组[1,2,3,3,4]，是有序循环数组，[4,1,2,3,3]也是。
    int getMin(vector<int> arr, int n) {
        //最小值index
        //arr[l] >= arr[r]
        //arr[mid] < arr[r] ? r = mid - 1

        if(n == 0) {
            return -1;
        }

        int l = 0, r = n - 1;


//        此处一旦l <= r， 必须考虑循环终止问题
        while ( l < r ) {

            if(r - l == 1)
                break;

            if(arr[l] < arr[r])
                return arr[l];

            int mid = ( r - l)/2 + l;

            if(arr[mid] < arr[r] ) {
                r = mid;
                continue;
            }
            else if( arr[mid] > arr[l]) {
                l = mid;
                continue;
            }

//            if arr[mid] >=  arr[r]
//            arr[mid] <= arr[l]
//            可得到arr[mid ] == arr[r] == arr[l]
//            此时需要使用遍历方法解决[l, r]

            while (l < r) {
                if( arr[l] == arr[mid]) {
                    l ++;
                    continue;
                }
                else if (arr[l] < arr[mid]) {
                    return arr[l];
                }
                else if (arr[l] > arr[mid]){
                    r = mid;
                    break;
                }
            }
        }

        return min(arr[l], arr[r]);


    }

//    二分搜索直接查找最左边的num
//    1,2,2,3,3,3,3,4,5,6 num = 3
    int findPos2(vector<int> arr, int n, int num) {
        if( n <= 0)
            return -1;

        int l = 0, r = n-1;
        int res = -1;

        while (l <= r) {
            int mid = (r - l)/2 + l;

//            当相等的时候，把r = mid继续二分搜索
            if(num == arr[mid]) {
                r = mid - 1;
                res = mid;
            }
            else if(num < arr[mid]) {
                r = mid - 1;
            }
            else {
                l = mid + 1;
            }
        }
//        此处需要判断一下此处是否为num
//        if(arr[r] != num)
//            return -1;

        return res;


    }
//对于一个有序数组arr，再给定一个整数num，请在arr中找到num这个数出现的最左边的位置
// 给定一个数组arr及它的大小n，同时给定num。请返回所求位置。若该元素在数组中未出现，请返回-1。
    int findPos(vector<int> arr, int n, int num) {
        if(n == 0) {
            return -1;
        }

        //出现在最左边arr[i] > arr[i-1]
        int l = 0, r = n-1;
        int res = -1;
        while (l <= r) {
            int mid = ( r - l )/2 + l;

            if( arr[mid] == num ) {
                res = mid;
            }
            else if ( num < arr[mid]) {
                r = mid - 1;
            }
            else if(num > arr[mid] ) {
                l = mid + 1;
            }
        }

        if( res == 0 || res == -1)
            return res;
//      二分查找到num之后向左遍历，这个方法比较麻烦
        while (arr[res] == arr[res-1]) {
            res --;
            if(res == 0)
                break;
        }

        return res;

    }


//局部最小值
// n == 0 arr[o] is min return 0
// 如果arr[N-1]<arr[N-2]，那么arr[N-1]是局部最小；return n-1
// 如果0<i<N-1，既有arr[i]<arr[i-1]又有arr[i]<arr[i+1]，那么arr[i]是局部最小 return i
    int getLessIndex(vector<int> arr) {
        int n = arr.size();
        if(n <= 0)
            return -1;

        if(n == 1 || arr[0] < arr[1]) {
            return 0;
        }
        else if(arr[n-1] < arr[n-2]) {
            return n - 1;
        }
        else {
//        找到最小值，最小值必然成立[1, n-2]
            int l = 1, r = n-2;
            while (l <= r) {
                int mid = (r - l)/2 + l;
                if(arr[mid] < arr[mid-1] && arr[mid] < arr[mid+1]) {
                    return mid;
                }
                else if(arr[mid] > arr[mid-1]) {
                    r = mid - 1;
                }
                else if(arr[mid] > arr[mid+1]){
                    l = mid + 1;
                }
            }
        }

        return -1;

    }


//二分搜索
    int binarySearch(vector<int> arr, int target) {
        long n = arr.size();

        long l = 0, r = n-1;

        while (l <= r) {
//        每次开始二分搜索之前定义mid
            long mid = (r - l)/2 + l;

            if(arr[mid] == target) {
                return mid;
            }
            else if(target > arr[mid]) {
                l = mid + 1;
            }
            else {
                r = mid - 1;
            }
        }

        return -1;
    }

    int main() {
        std::cout << "Hello, World!" << std::endl;
        return 0;
    }
};

